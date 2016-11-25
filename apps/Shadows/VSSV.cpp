#include"VSSV.h"
#include"FastAdjacency.h"

VSSV::VSSV(
    size_t                          const&maxMultiplicity,
    bool                            const&zfail          ,
    glm::uvec2                      const&windowSize     ,
    std::shared_ptr<ge::gl::Texture>const&depth          ,
    std::shared_ptr<Model>          const&model          ,
    std::shared_ptr<ge::gl::Texture>const&shadowMask     ):_windowSize(windowSize),_zfail(zfail){
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

  //compute adjacency of the model
  std::vector<float>vertices;
  model->getVertices(vertices);
  size_t const floatsPer3DVertex = 3;
  size_t const verticesPerTriangle = 3;
  size_t const floatsPerTriangle = verticesPerTriangle*floatsPer3DVertex;
  auto adj = std::make_shared<Adjacency>(vertices.data(),vertices.size()/floatsPerTriangle,maxMultiplicity);

  size_t const verticesPerEdge = 2;
  size_t const multiplicityFloats = 1;
  size_t const maxNofOppositeVertices = maxMultiplicity;
  size_t const floatsPerEdge = verticesPerEdge*floatsPer3DVertex + multiplicityFloats + maxNofOppositeVertices*floatsPer3DVertex;
  size_t const sizeofVertex3DInBytes = floatsPer3DVertex*sizeof(float);

  //create and fill adjacency buffer on GPU
  //(A,B,M,O0,O1,...)*
  //A - vertex A of an edge
  //B - vertex B of an edge
  //M - multiplicity of an edge
  //On - opposite vertex of an edge
  //n < maxMultiplicity
  this->_adjacency = std::make_shared<ge::gl::Buffer>(adj->getNofEdges()*floatsPerEdge*sizeof(float));
  float*ptr=(float*)this->_adjacency->map();
  for(size_t edgeIndex=0;edgeIndex<adj->getNofEdges();++edgeIndex){
    auto edgePtr = ptr+edgeIndex*floatsPerEdge;
    auto edgeVertexAPtr = edgePtr;
    auto edgeVertexBPtr = edgeVertexAPtr + floatsPer3DVertex;
    auto edgeMultiplicityPtr = edgeVertexBPtr + floatsPer3DVertex;
    auto edgeOppositeVerticesPtr = edgeMultiplicityPtr + multiplicityFloats;
    size_t const edgeVertexAIndex = 0;
    size_t const edgeVertexBIndex = 1;
    std::memcpy(edgeVertexAPtr,adj->getVertices()+adj->getEdge(edgeIndex,edgeVertexAIndex),sizeofVertex3DInBytes);
    std::memcpy(edgeVertexBPtr,adj->getVertices()+adj->getEdge(edgeIndex,edgeVertexBIndex),sizeofVertex3DInBytes);
    *edgeMultiplicityPtr = float(adj->getNofOpposite(edgeIndex));
    for(size_t oppositeIndex=0;oppositeIndex<adj->getNofOpposite(edgeIndex);++oppositeIndex)
      std::memcpy(
          edgeOppositeVerticesPtr+oppositeIndex*floatsPer3DVertex,
          adj->getVertices()+adj->getOpposite(edgeIndex,oppositeIndex),
          sizeofVertex3DInBytes);
    size_t const nofEmptyOppositeVertices = maxMultiplicity-adj->getNofOpposite(edgeIndex);
    std::memset(
        edgeOppositeVerticesPtr+adj->getNofOpposite(edgeIndex)*floatsPer3DVertex,
        0,
        sizeofVertex3DInBytes*nofEmptyOppositeVertices);
  }
  this->_adjacency->unmap();
  this->_nofEdges = adj->getNofEdges();

}

VSSV::~VSSV(){}

void VSSV::create(
    glm::vec4 const&lightPosition,
    glm::mat4 const&view         ,
    glm::mat4 const&projection   ){
  (void)lightPosition;
  (void)view;
  (void)projection;
}

