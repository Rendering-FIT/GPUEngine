#include"CSSVSOE.h"
#include"FastAdjacency.h"

#include<geCore/Dtemplates.h>

void CSSVSOE::_createSidesData(std::shared_ptr<Adjacency const>const&adj){
  assert(this!=nullptr);
  assert(adj!=nullptr);
  size_t const maxNofOppositeVertices = adj->getMaxMultiplicity();
  size_t const floatsPerEdge = verticesPerEdge*componentsPerVertex3D + maxNofOppositeVertices*componentsPerPlane3D;
  this->_edges = std::make_shared<ge::gl::Buffer>(adj->getNofEdges()*floatsPerEdge*sizeof(float));

  auto const dstPtr = static_cast<float      *>(this->_edges->map());
  auto const srcPtr = static_cast<float const*>(adj->getVertices() );

  size_t const sizeofVertex3DInBytes = componentsPerVertex3D * sizeof(float);
  for(size_t edgeIndex=0;edgeIndex<adj->getNofEdges();++edgeIndex){
    auto const edgeDstPtr    = dstPtr + edgeIndex*floatsPerEdge;
    auto const vertexADstPtr = edgeDstPtr;
    auto const vertexBDstPtr = vertexADstPtr + componentsPerVertex3D;
    auto const planesDstPtr  = vertexBDstPtr + componentsPerVertex3D;

    auto const vertexASrcPtr = srcPtr + adj->getEdgeVertexA(edgeIndex);
    auto const vertexBSrcPtr = srcPtr + adj->getEdgeVertexB(edgeIndex);

    std::memcpy(vertexADstPtr,vertexASrcPtr,sizeofVertex3DInBytes);
    std::memcpy(vertexBDstPtr,vertexBSrcPtr,sizeofVertex3DInBytes);
    size_t const sizeofPlane3DInBytes = componentsPerPlane3D*sizeof(float);
    for(size_t oppositeIndex=0;oppositeIndex<adj->getNofOpposite(edgeIndex);++oppositeIndex){
      auto const planeDstPtr          = planesDstPtr + oppositeIndex*componentsPerPlane3D;
      auto const oppositeVertexSrcPtr = srcPtr + adj->getOpposite(edgeIndex,oppositeIndex);
      auto const plane                = computePlane(toVec3(vertexASrcPtr),toVec3(vertexBSrcPtr),toVec3(oppositeVertexSrcPtr));
      std::memcpy(planeDstPtr,glm::value_ptr(plane),sizeofPlane3DInBytes);
    }
    size_t  const nofEmptyPlanes    = maxNofOppositeVertices - adj->getNofOpposite(edgeIndex);
    auto    const emptyPlanesDstPtr = planesDstPtr + componentsPerPlane3D*adj->getNofOpposite(edgeIndex);
    uint8_t const value             = 0;
    std::memset(emptyPlanesDstPtr,value,sizeofPlane3DInBytes*nofEmptyPlanes);
  }
  this->_edges->unmap();
  this->_nofEdges = adj->getNofEdges();

  this->_sillhouettes=std::make_shared<ge::gl::Buffer>(
      sizeof(float)*componentsPerVertex4D*verticesPerQuad*this->_nofEdges*adj->getMaxMultiplicity(),
      nullptr,GL_DYNAMIC_COPY);
  this->_sillhouettes->clear(GL_R32F,GL_RED,GL_FLOAT);

  this->_sidesVao = std::make_shared<ge::gl::VertexArray>();
  this->_sidesVao->addAttrib(this->_sillhouettes,0,componentsPerVertex4D,GL_FLOAT);
}

void CSSVSOE::_createCapsData (std::shared_ptr<Adjacency const>const&adj){
  assert(this!=nullptr);
  assert(adj!=nullptr);
  this->_caps = std::make_shared<ge::gl::Buffer>(sizeof(float)*componentsPerVertex4D*verticesPerTriangle*this->_nofTriangles);
  auto const dstPtr = static_cast<float      *>(this->_caps->map());
  auto const srcPtr = static_cast<float const*>(adj->getVertices());
  for(size_t t=0;t<this->_nofTriangles;++t){
    auto const triangleDstPtr = dstPtr + t*componentsPerVertex4D*verticesPerTriangle;
    auto const triangleSrcPtr = srcPtr + t*componentsPerVertex3D*verticesPerTriangle;
    for(size_t p=0;p<verticesPerTriangle;++p){
      auto   const vertexDstPtr = triangleDstPtr + p*componentsPerVertex4D;
      auto   const vertexSrcPtr = triangleSrcPtr + p*componentsPerVertex3D;
      size_t const sizeofVertex3DInBytes = componentsPerVertex3D * sizeof(float);
      std::memcpy(vertexDstPtr,vertexSrcPtr,sizeofVertex3DInBytes);
      vertexDstPtr[3] = 1.f;
    }
  }
  this->_caps->unmap();
  this->_capsVao = std::make_shared<ge::gl::VertexArray>();
  this->_capsVao->addAttrib(this->_caps,0,4,GL_FLOAT);
}



CSSVSOE::CSSVSOE(
    std::shared_ptr<ge::gl::Texture>const&shadowMask     ,
    std::shared_ptr<Model>          const&model          ,
    std::shared_ptr<ge::gl::Texture>const&depth          ,
    ShadowVolumesParams             const&svParams       ,
    size_t                          const&maxMultiplicity,
    CSSVSOEParams                   const&params         ):
  ShadowVolumes(shadowMask,depth,svParams),
  _params      (params                   )
{
  assert(this!=nullptr);

  std::vector<float>vertices;
  model->getVertices(vertices);

  size_t const nofTriangles = vertices.size() / (verticesPerTriangle*componentsPerVertex3D);
  auto const adj = std::make_shared<Adjacency const>(vertices.data(),nofTriangles,maxMultiplicity);

  this->_nofTriangles=adj->getNofTriangles();

  this->_createSidesData(adj);

  this->_createCapsData(adj);

  struct DrawArraysIndirectCommand{
    uint32_t nofVertices  = 0;
    uint32_t nofInstances = 0;
    uint32_t firstVertex  = 0;
    uint32_t baseInstance = 0;
  };
  DrawArraysIndirectCommand cmd[2];
  cmd[0].nofInstances = 1;
  cmd[1].nofInstances = 1;
  this->_dibo=std::make_shared<ge::gl::Buffer>(sizeof(DrawArraysIndirectCommand),&cmd);

#include"CSSVSOEShaders.h"
#include"SilhouetteShaders.h"

  this->_computeSidesProgram = std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER,
        "#version 450 core\n",
        ge::gl::Shader::define("WORKGROUP_SIZE_X",int32_t(this->_params.computeSidesWGS)),
        ge::gl::Shader::define("MAX_MULTIPLICITY",int32_t(adj->getMaxMultiplicity()    )),
        silhouetteFunctions,
        computeSrc));

  this->_drawSidesProgram=std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER         ,drawVPSrc),
      std::make_shared<ge::gl::Shader>(GL_TESS_CONTROL_SHADER   ,drawCPSrc),
      std::make_shared<ge::gl::Shader>(GL_TESS_EVALUATION_SHADER,drawEPSrc));

  this->_drawCapsProgram = std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER  ,capsVPSrc),
      std::make_shared<ge::gl::Shader>(GL_GEOMETRY_SHADER,
        "#version 450\n",
        silhouetteFunctions,
        capsGPSrc));
}

CSSVSOE::~CSSVSOE(){}

void CSSVSOE::_computeSides(glm::vec4 const&lightPosition){
  assert(this                      !=nullptr);
  assert(this->_dibo               !=nullptr);
  assert(this->_computeSidesProgram!=nullptr);
  assert(this->_edges              !=nullptr);
  assert(this->_sillhouettes       !=nullptr);
  this->_dibo->clear(GL_R32UI,0,sizeof(uint32_t),GL_RED_INTEGER,GL_UNSIGNED_INT);

  glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
  this->_computeSidesProgram
    ->set1ui    ("numEdge"           ,uint32_t(this->_nofEdges)    )
    ->set4fv    ("lightPosition"     ,glm::value_ptr(lightPosition))
    ->bindBuffer("edges"             ,this->_edges                 )
    ->bindBuffer("silhouettes"       ,this->_sillhouettes          )
    ->bindBuffer("drawIndirectBuffer",this->_dibo                  )
    ->dispatch((GLuint)ge::core::getDispatchSize(this->_nofEdges,this->_params.computeSidesWGS));

  glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
  glFinish();
}

void CSSVSOE::drawSides(
    glm::vec4 const&lightPosition   ,
    glm::mat4 const&viewMatrix      ,
    glm::mat4 const&projectionMatrix){
  assert(this                   !=nullptr);
  assert(this->_drawSidesProgram!=nullptr);
  assert(this->_sidesVao        !=nullptr);
  assert(this->_dibo            !=nullptr);

  this->_computeSides(lightPosition);
  if(this->timeStamp)this->timeStamp->stamp("compute");

  this->_sidesVao->bind();
  auto mvp = projectionMatrix * viewMatrix;

  this->_drawSidesProgram
    ->setMatrix4fv("mvp"          ,glm::value_ptr(mvp          ))
    ->set4fv      ("lightPosition",glm::value_ptr(lightPosition));
  this->_dibo->bind(GL_DRAW_INDIRECT_BUFFER);
  glPatchParameteri(GL_PATCH_VERTICES,2);
  this->_drawSidesProgram->use();
  glDrawArraysIndirect(GL_PATCHES,NULL);
  this->_sidesVao->unbind();
}

void CSSVSOE::drawCaps(
    glm::vec4 const&lightPosition   ,
    glm::mat4 const&viewMatrix      ,
    glm::mat4 const&projectionMatrix){
  assert(this                  !=nullptr);
  assert(this->_drawCapsProgram!=nullptr);
  assert(this->_capsVao        !=nullptr);
  auto mvp = projectionMatrix * viewMatrix;
  this->_drawCapsProgram
    ->setMatrix4fv("mvp"          ,glm::value_ptr(mvp          ))
    ->set4fv      ("lightPosition",glm::value_ptr(lightPosition));
  this->_drawCapsProgram->use();
  this->_capsVao->bind();
  glDrawArrays(GL_TRIANGLES,0,(GLsizei)this->_nofTriangles*3);
  this->_capsVao->unbind();
}

