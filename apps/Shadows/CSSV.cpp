#include"CSSV.h"
#include"FastAdjacency.h"

#include<geCore/Dtemplates.h>

CSSV::CSSV(
    std::shared_ptr<ge::gl::Texture>const&shadowMask     ,
    std::shared_ptr<Model>          const&model          ,
    std::shared_ptr<ge::gl::Texture>const&depth          ,
    ShadowVolumesParams             const&svParams       ,
    size_t                          const&maxMultiplicity,
    CSSVParams                      const&params         ):
  ShadowVolumes(depth ,shadowMask,svParams),
  _params      (params                    )
{
  assert(this!=nullptr);

  std::vector<float>vertices;
  model->getVertices(vertices);
  auto adj = std::make_shared<Adjacency>(vertices.data(),vertices.size()/9,maxMultiplicity);

  size_t numVer = 2+adj->getMaxMultiplicity();
  this->_adjacency = std::make_shared<ge::gl::Buffer>(sizeof(float)*4*numVer*adj->getNofEdges());

  float*Ptr=(float*)this->_adjacency->map();

  for(unsigned e=0;e<adj->getNofEdges();++e){
    //A
    for(int k=0;k<3;++k)
      Ptr[(e*numVer+0)*4+k]=adj->getVertices()[adj->getEdge(e,0)+k];
    Ptr[(e*numVer+0)*4+3]=(float)adj->getNofOpposite(e);
    //B
    for(int k=0;k<3;++k)
      Ptr[(e*numVer+1)*4+k]=adj->getVertices()[adj->getEdge(e,1)+k];
    Ptr[(e*numVer+1)*4+3]=1;
    //O
    for(unsigned o=0;o<adj->getNofOpposite(e);++o){
      for(int k=0;k<3;++k)
        Ptr[(e*numVer+2+o)*4+k]=adj->getVertices()[adj->getOpposite(e,o)+k];
      Ptr[(e*numVer+2+o)*4+3]=1;
    }
    for(size_t o=adj->getNofOpposite(e);o<adj->getMaxMultiplicity();++o){
      for(int k=0;k<4;++k)
        Ptr[(e*numVer+2+o)*4+k]=0;
    }
  }
  this->_adjacency->unmap();
  this->_nofEdges = adj->getNofEdges();

  this->_sillhouettes=std::make_shared<ge::gl::Buffer>(
      sizeof(float)*4*4*this->_nofEdges*adj->getMaxMultiplicity(),
      nullptr,GL_DYNAMIC_COPY);
  this->_sillhouettes->clear(GL_R32F,GL_RED,GL_FLOAT);

  this->_dibo=std::make_shared<ge::gl::Buffer>(sizeof(unsigned)*4);
  unsigned*CPtr=(unsigned*)this->_dibo->map();
  CPtr[0]=0;
  CPtr[1]=1;
  CPtr[2]=0;
  CPtr[3]=0;
  this->_dibo->unmap();

  this->_sidesVao=std::make_shared<ge::gl::VertexArray>();
  this->_sidesVao->addAttrib(this->_sillhouettes,0,4,GL_FLOAT);

#include"CSSVShaders.h"

  this->_computeSidesProgram = std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER,
        "#version 450 core\n",
        ge::gl::Shader::define("WORKGROUP_SIZE_X",(int)this->_params.computeSidesWGS),
        ge::gl::Shader::define("MAX_MULTIPLICITY",(int)adj->getMaxMultiplicity()    ),
        ge::gl::Shader::define("LOCAL_ATOMIC"    ,(int)this->_params.localAtomic    ),
        ge::gl::Shader::define("CULL_SIDES"      ,(int)this->_params.cullSides      ),
        computeSrc));

  this->_drawSidesProgram=std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER         ,drawVPSrc),
      std::make_shared<ge::gl::Shader>(GL_TESS_CONTROL_SHADER   ,drawCPSrc),
      std::make_shared<ge::gl::Shader>(GL_TESS_EVALUATION_SHADER,drawEPSrc),
      std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER       ,drawFPSrc));

  this->_nofTriangles=adj->getNofTriangles();
  this->_caps = std::make_shared<ge::gl::Buffer>(sizeof(float)*4*3*this->_nofTriangles);
  Ptr=(float*)this->_caps->map();
  for(unsigned t=0;t<this->_nofTriangles;++t){
    for(unsigned p=0;p<3;++p){
      for(unsigned i=0;i<3;++i)
        Ptr[(t*3+p)*4+i]=adj->getVertices()[(t*3+p)*3+i];
      Ptr[(t*3+p)*4+3]=1;
    }
  }
  this->_caps->unmap();
  this->_capsVao = std::make_shared<ge::gl::VertexArray>();
  this->_capsVao->addAttrib(this->_caps,0,4,GL_FLOAT);

  this->_drawCapsProgram = std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER,capsVPSrc),
      std::make_shared<ge::gl::Shader>(GL_GEOMETRY_SHADER,capsGPSrc),
      std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER,capsFPSrc));
}

CSSV::~CSSV(){}

void CSSV::_computeSides(glm::vec4 const&lightPosition){
  assert(this!=nullptr);
  assert(this->_dibo!=nullptr);
  assert(this->_computeSidesProgram!=nullptr);
  assert(this->_adjacency!=nullptr);
  assert(this->_sillhouettes!=nullptr);
  this->_dibo->clear(GL_R32UI,0,sizeof(unsigned),GL_RED_INTEGER,GL_UNSIGNED_INT);

  glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
  this->_computeSidesProgram->use();
  this->_computeSidesProgram->set1ui("numEdge",(uint32_t)this->_nofEdges);
  this->_computeSidesProgram->set4fv("lightPosition",glm::value_ptr(lightPosition));
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER,0,this->_adjacency->getId());
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER,1,this->_sillhouettes->getId());
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER,2,this->_dibo->getId());

  glDispatchCompute((GLuint)ge::core::getDispatchSize((uint32_t)this->_nofEdges,(uint32_t)this->_params.computeSidesWGS),1,1);

  glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
  glFinish();
}

void CSSV::drawSides(
    glm::vec4 const&lightPosition   ,
    glm::mat4 const&viewMatrix      ,
    glm::mat4 const&projectionMatrix){
  assert(this!=nullptr);
  assert(this->_drawSidesProgram!=nullptr);
  assert(this->_sidesVao!=nullptr);
  assert(this->_dibo!=nullptr);

  this->_computeSides(lightPosition);
  if(this->timeStamp)this->timeStamp->stamp("compute");

  auto mvp = projectionMatrix * viewMatrix;
  this->_drawSidesProgram->use();
  this->_drawSidesProgram->setMatrix4fv("mvp",glm::value_ptr(mvp));
  this->_drawSidesProgram->set4fv("lightPosition",glm::value_ptr(lightPosition));
  this->_sidesVao->bind();
  this->_dibo->bind(GL_DRAW_INDIRECT_BUFFER);
  glPatchParameteri(GL_PATCH_VERTICES,2);
  glDrawArraysIndirect(GL_PATCHES,NULL);
  this->_sidesVao->unbind();
}

void CSSV::drawCaps(
    glm::vec4 const&lightPosition   ,
    glm::mat4 const&viewMatrix      ,
    glm::mat4 const&projectionMatrix){
  assert(this!=nullptr);
  assert(this->_drawCapsProgram!=nullptr);
  assert(this->_capsVao!=nullptr);
  auto mvp = projectionMatrix * viewMatrix;
  this->_drawCapsProgram->use();
  this->_drawCapsProgram->setMatrix4fv("mvp",glm::value_ptr(mvp));
  this->_drawCapsProgram->set4fv("lightPosition",glm::value_ptr(lightPosition));
  this->_capsVao->bind();
  glDrawArrays(GL_TRIANGLES,0,(GLsizei)this->_nofTriangles*3);
  this->_capsVao->unbind();
}

