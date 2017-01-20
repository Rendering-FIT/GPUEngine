#include"CSSV.h"
#include"FastAdjacency.h"

#include<geCore/Dtemplates.h>

CSSV::CSSV(
    size_t                          const&maxMultiplicity,
    bool                            const&zfail          ,
    glm::uvec2                      const&windowSize     ,
    std::shared_ptr<ge::gl::Texture>const&depth          ,
    std::shared_ptr<Model>          const&model          ,
    std::shared_ptr<ge::gl::Texture>const&shadowMask     ,
    CSSVParams                      const&params         ):
  _windowSize(windowSize),
  _zfail(zfail),
  _params(params)
{
  assert(this!=nullptr);
  this->_timeStamper = std::make_shared<TimeStamp>(nullptr);

  this->_fbo = std::make_shared<ge::gl::Framebuffer>();
  this->_fbo->attachTexture(GL_DEPTH_ATTACHMENT,depth);
  this->_fbo->attachTexture(GL_STENCIL_ATTACHMENT,depth);
  assert(this->_fbo->check());

  this->_maskFbo = std::make_shared<ge::gl::Framebuffer>();
  this->_maskFbo->attachTexture(GL_STENCIL_ATTACHMENT,depth);
  this->_maskFbo->attachTexture(GL_COLOR_ATTACHMENT0,shadowMask);
  this->_maskFbo->drawBuffers(1,GL_COLOR_ATTACHMENT0);

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

  this->_computeSides = std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER,
        "#version 450 core\n",
        ge::gl::Shader::define("WORKGROUP_SIZE_X",(int)this->_params.computeSidesWGS),
        ge::gl::Shader::define("MAX_MULTIPLICITY",(int)adj->getMaxMultiplicity()    ),
        ge::gl::Shader::define("LOCAL_ATOMIC"    ,(int)this->_params.localAtomic    ),
        ge::gl::Shader::define("CULL_SIDES"      ,(int)this->_params.cullSides      ),
        computeSrc));

  this->_drawSides=std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER         ,drawVPSrc),
      std::make_shared<ge::gl::Shader>(GL_TESS_CONTROL_SHADER   ,drawCPSrc),
      std::make_shared<ge::gl::Shader>(GL_TESS_EVALUATION_SHADER,drawEPSrc),
      std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER       ,drawFPSrc));


  this->_emptyVao = std::make_shared<ge::gl::VertexArray>();
  this->_blit = std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER,blitVPSrc),
      std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER,blitFPSrc));


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

  this->_drawCaps = std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER,capsVPSrc),
      std::make_shared<ge::gl::Shader>(GL_GEOMETRY_SHADER,capsGPSrc),
      std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER,capsFPSrc));


}

CSSV::~CSSV(){
}

void CSSV::create(glm::vec4 const&lightPosition,
    glm::mat4 const&view,
    glm::mat4 const&projection){
  auto mvp = projection*view;

  if(this->timeStamp)this->timeStamp->stamp("");
  this->_dibo->clear(GL_R32UI,0,sizeof(unsigned),GL_RED_INTEGER,GL_UNSIGNED_INT);

  glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
  this->_computeSides->use();
  this->_computeSides->set1ui("numEdge",(uint32_t)this->_nofEdges);
  this->_computeSides->set4fv("lightPosition",glm::value_ptr(lightPosition));
  //this->_computeSides->setMatrix4fv("mvp",glm::value_ptr(mvp));
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER,0,this->_adjacency->getId());
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER,1,this->_sillhouettes->getId());
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER,2,this->_dibo->getId());

  glDispatchCompute((GLuint)ge::core::getDispatchSize((uint32_t)this->_nofEdges,(uint32_t)this->_params.computeSidesWGS),1,1);

  glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
  glFinish();
  if(this->timeStamp)this->timeStamp->stamp("compute");

  this->_fbo->bind();
  glEnable(GL_STENCIL_TEST);
  glStencilFunc(GL_ALWAYS,0,0);

  if(this->_zfail){
    glStencilOpSeparate(GL_FRONT,GL_KEEP,GL_INCR_WRAP,GL_KEEP);
    glStencilOpSeparate(GL_BACK,GL_KEEP,GL_DECR_WRAP,GL_KEEP);
  }else{
    glStencilOpSeparate(GL_FRONT,GL_KEEP,GL_KEEP,GL_INCR_WRAP);
    glStencilOpSeparate(GL_BACK,GL_KEEP,GL_KEEP,GL_DECR_WRAP);
  }
  glDepthFunc(GL_LESS);
  glDepthMask(GL_FALSE);
  glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
  this->_drawSides->use();
  this->_drawSides->setMatrix4fv("mvp",glm::value_ptr(mvp));
  this->_drawSides->set4fv("lightPosition",glm::value_ptr(lightPosition));
  this->_sidesVao->bind();
  this->_dibo->bind(GL_DRAW_INDIRECT_BUFFER);
  glPatchParameteri(GL_PATCH_VERTICES,2);
  glDrawArraysIndirect(GL_PATCHES,NULL);
  this->_sidesVao->unbind();
  if(this->timeStamp)this->timeStamp->stamp("drawSides");

  if(this->_zfail){
    this->_drawCaps->use();
    this->_drawCaps->setMatrix4fv("mvp",glm::value_ptr(mvp));
    this->_drawCaps->set4fv("lightPosition",glm::value_ptr(lightPosition));
    this->_capsVao->bind();
    glDrawArrays(GL_TRIANGLES,0,(GLsizei)this->_nofTriangles*3);
    this->_capsVao->unbind();

    this->_fbo->unbind();
    if(this->timeStamp)this->timeStamp->stamp("drawCaps");
  }

  glDisable(GL_DEPTH_TEST);
  this->_maskFbo->bind();
  glClear(GL_COLOR_BUFFER_BIT);
  glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);
  glStencilFunc(GL_EQUAL,0,0xff);
  glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
  glDepthFunc(GL_ALWAYS);
  glDepthMask(GL_FALSE);
  this->_blit->use();
  this->_emptyVao->bind();
  glDrawArrays(GL_TRIANGLE_STRIP,0,4);
  this->_emptyVao->unbind();
  this->_maskFbo->unbind();
  glDepthFunc(GL_LESS);
  glDisable(GL_STENCIL_TEST);
  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);

  if(this->timeStamp)this->timeStamp->stamp("blit");
}

