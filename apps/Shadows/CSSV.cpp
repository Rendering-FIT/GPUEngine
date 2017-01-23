#include"CSSV.h"
#include"FastAdjacency.h"

#include<geCore/Dtemplates.h>

void CSSV::_createSidesData(std::shared_ptr<Adjacency>const&adj){
  assert(this!=nullptr);
  assert(adj!=nullptr);
  size_t numVer = 2+adj->getMaxMultiplicity();
  this->_adjacency = std::make_shared<ge::gl::Buffer>(sizeof(float)*componentsPerVertex4D*numVer*adj->getNofEdges());

  float      *dstPtr=(float      *)this->_adjacency->map();
  float const*srcPtr=(float const*)adj->getVertices();

  size_t const sizeofVertex3DInBytes = componentsPerVertex3D * sizeof(float);
  for(size_t e=0;e<adj->getNofEdges();++e){
    size_t const floatsPerEdge = verticesPerEdge*componentsPerVertex4D + adj->getMaxMultiplicity()*componentsPerVertex4D;
    auto edgeDstPtr                 = dstPtr + e*floatsPerEdge;
    auto edgeVertexADstPtr          = edgeDstPtr;
    auto edgeVertexBDstPtr          = edgeVertexADstPtr + componentsPerVertex4D;
    auto edgeOppositeVerticesDstPtr = edgeVertexBDstPtr + componentsPerVertex4D;

    auto edgeVertexASrcPtr          = srcPtr + adj->getEdge(e,0);
    auto edgeVertexBSrcPtr          = srcPtr + adj->getEdge(e,1);

    std::memcpy(edgeVertexADstPtr,edgeVertexASrcPtr,sizeofVertex3DInBytes);
    edgeVertexADstPtr[3]=(float)adj->getNofOpposite(e);

    std::memcpy(edgeVertexBDstPtr,edgeVertexBSrcPtr,sizeofVertex3DInBytes);
    edgeVertexBDstPtr[3]=1.f;

    for(size_t o=0;o<adj->getNofOpposite(e);++o){
      auto edgeOppositeVertexDstPtr = edgeOppositeVerticesDstPtr + o*componentsPerVertex4D;
      auto edgeOppositeVertexSrcPtr = srcPtr + adj->getOpposite(e,o);
      std::memcpy(edgeOppositeVertexDstPtr,edgeOppositeVertexSrcPtr,sizeofVertex3DInBytes);
      edgeOppositeVertexDstPtr[3]=1.f;
    }

    size_t const nofEmptyOppositeVertices = adj->getMaxMultiplicity() - adj->getNofOpposite(e);
    auto edgeEmptyOppositeVerticesPtr = edgeOppositeVerticesDstPtr + componentsPerVertex4D*adj->getNofOpposite(e);
    uint8_t byteValue = 0;
    std::memset(edgeEmptyOppositeVerticesPtr,byteValue,nofEmptyOppositeVertices*componentsPerVertex4D*sizeof(float));
  }
  this->_adjacency->unmap();

  this->_nofEdges = adj->getNofEdges();

  this->_sillhouettes=std::make_shared<ge::gl::Buffer>(
      sizeof(float)*componentsPerVertex4D*verticesPerQuad*this->_nofEdges*adj->getMaxMultiplicity(),
      nullptr,GL_DYNAMIC_COPY);
  this->_sillhouettes->clear(GL_R32F,GL_RED,GL_FLOAT);

  this->_sidesVao = std::make_shared<ge::gl::VertexArray>();
  this->_sidesVao->addAttrib(this->_sillhouettes,0,componentsPerVertex4D,GL_FLOAT);
}

void CSSV::_createCapsData (std::shared_ptr<Adjacency>const&adj){
  assert(this!=nullptr);
  assert(adj!=nullptr);
  this->_caps = std::make_shared<ge::gl::Buffer>(sizeof(float)*componentsPerVertex4D*verticesPerTriangle*this->_nofTriangles);
  float      *dstPtr=(float      *)this->_caps->map();
  float const*srcPtr=(float const*)adj->getVertices();
  for(size_t t=0;t<this->_nofTriangles;++t){
    auto triangleDstPtr = dstPtr + t*componentsPerVertex4D*verticesPerTriangle;
    auto triangleSrcPtr = srcPtr + t*componentsPerVertex3D*verticesPerTriangle;
    for(size_t p=0;p<verticesPerTriangle;++p){
      auto vertexDstPtr = triangleDstPtr + p*componentsPerVertex4D;
      auto vertexSrcPtr = triangleSrcPtr + p*componentsPerVertex3D;
      size_t const sizeofVertex3DInBytes = componentsPerVertex3D * sizeof(float);
      std::memcpy(vertexDstPtr,vertexSrcPtr,sizeofVertex3DInBytes);
      vertexDstPtr[3] = 1.f;
    }
  }
  this->_caps->unmap();
  this->_capsVao = std::make_shared<ge::gl::VertexArray>();
  this->_capsVao->addAttrib(this->_caps,0,4,GL_FLOAT);
}



CSSV::CSSV(
    std::shared_ptr<ge::gl::Texture>const&shadowMask     ,
    std::shared_ptr<Model>          const&model          ,
    std::shared_ptr<ge::gl::Texture>const&depth          ,
    ShadowVolumesParams             const&svParams       ,
    size_t                          const&maxMultiplicity,
    CSSVParams                      const&params         ):
  ShadowVolumes(shadowMask,depth,svParams),
  _params      (params                   )
{
  assert(this!=nullptr);

  std::vector<float>vertices;
  model->getVertices(vertices);

  size_t const nofTriangles = vertices.size() / (verticesPerTriangle*componentsPerVertex3D);
  auto adj = std::make_shared<Adjacency>(vertices.data(),nofTriangles,maxMultiplicity);

  this->_nofTriangles=adj->getNofTriangles();

  this->_createSidesData(adj);
  this->_createCapsData(adj);

  struct DrawArraysIndirectCommand{
    uint32_t nofVertices  = 0;
    uint32_t nofInstances = 0;
    uint32_t firstVertex  = 0;
    uint32_t baseInstance = 0;
  };
  DrawArraysIndirectCommand cmd;
  cmd.nofInstances = 1;
  this->_dibo=std::make_shared<ge::gl::Buffer>(sizeof(DrawArraysIndirectCommand),&cmd);

#include"CSSVShaders.h"

  this->_computeSidesProgram = std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER,
        "#version 450 core\n",
        ge::gl::Shader::define("WORKGROUP_SIZE_X",int32_t(this->_params.computeSidesWGS)),
        ge::gl::Shader::define("MAX_MULTIPLICITY",int32_t(adj->getMaxMultiplicity()    )),
        ge::gl::Shader::define("LOCAL_ATOMIC"    ,int32_t(this->_params.localAtomic    )),
        ge::gl::Shader::define("CULL_SIDES"      ,int32_t(this->_params.cullSides      )),
        computeSrc));

  this->_drawSidesProgram=std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER         ,drawVPSrc),
      std::make_shared<ge::gl::Shader>(GL_TESS_CONTROL_SHADER   ,drawCPSrc),
      std::make_shared<ge::gl::Shader>(GL_TESS_EVALUATION_SHADER,drawEPSrc),
      std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER       ,drawFPSrc));

  this->_drawCapsProgram = std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER  ,capsVPSrc),
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

