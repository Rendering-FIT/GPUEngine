#include"VSSV.h"
#include"FastAdjacency.h"
#include"VSSVShaders.h"

size_t const floatsPerNofOppositeVertices = 1;
size_t const sizeofVertex3DInBytes        = componentsPerVertex3D  *sizeof(float);
size_t const sizeofPlane3DInBytes         = componentsPerPlane3D   *sizeof(float);

void VSSV::_createSideDataUsingPoints(std::shared_ptr<Adjacency>const&adj){
  assert(this!=nullptr);
  assert(adj!=nullptr);
  size_t const maxNofOppositeVertices = adj->getMaxMultiplicity();
  //create and fill adjacency buffer on GPU
  //(A,B,M,O0,O1,...)*
  //A - vertex A of an edge
  //B - vertex B of an edge
  //M - multiplicity of an edge
  //On - opposite vertex of an edge
  //n < maxMultiplicity
  size_t const floatsPerEdge = verticesPerEdge*componentsPerVertex3D + floatsPerNofOppositeVertices + maxNofOppositeVertices*componentsPerVertex3D;
  this->_adjacency = std::make_shared<ge::gl::Buffer>(adj->getNofEdges()*floatsPerEdge*sizeof(float));

  
  auto const dstPtr = static_cast<float      *>(this->_adjacency->map());
  auto const srcPtr = static_cast<float const*>(adj->getVertices()     );

  for(size_t edgeIndex=0;edgeIndex<adj->getNofEdges();++edgeIndex){
    auto const edgeDstPtr             = dstPtr + edgeIndex*floatsPerEdge;
    auto const vertexADstPtr          = edgeDstPtr;
    auto const vertexBDstPtr          = vertexADstPtr + componentsPerVertex3D;
    auto const nofOppositeDstPtr      = vertexBDstPtr + componentsPerVertex3D;
    auto const oppositeVerticesDstPtr = nofOppositeDstPtr + floatsPerNofOppositeVertices;

    auto const vertexASrcPtr = srcPtr + adj->getEdgeVertexA(edgeIndex);
    auto const vertexBSrcPtr = srcPtr + adj->getEdgeVertexB(edgeIndex);
    std::memcpy(vertexADstPtr,vertexASrcPtr,sizeofVertex3DInBytes);
    std::memcpy(vertexBDstPtr,vertexBSrcPtr,sizeofVertex3DInBytes);
    *nofOppositeDstPtr = float(adj->getNofOpposite(edgeIndex));
    for(size_t oppositeIndex=0;oppositeIndex<adj->getNofOpposite(edgeIndex);++oppositeIndex)
      std::memcpy(
          oppositeVerticesDstPtr+oppositeIndex*componentsPerVertex3D,
          adj->getVertices()+adj->getOpposite(edgeIndex,oppositeIndex),
          sizeofVertex3DInBytes);
    size_t const nofEmptyOppositeVertices = maxNofOppositeVertices-adj->getNofOpposite(edgeIndex);
    auto const emptyOppositeVerticesDstPtr = oppositeVerticesDstPtr + adj->getNofOpposite(edgeIndex)*componentsPerVertex3D;
    std::memset(
        emptyOppositeVerticesDstPtr,
        0,
        sizeofVertex3DInBytes*nofEmptyOppositeVertices);
  }
  this->_adjacency->unmap();
  this->_nofEdges = adj->getNofEdges();

  //create vertex array for sides
  //divisor = maxMultiplicity -> attrib are modified once per edge
  this->_sidesVao = std::make_shared<ge::gl::VertexArray>();
  GLenum const normalized = GL_FALSE;
  GLuint const divisor = GLuint(adj->getMaxMultiplicity());
  GLintptr offset = 0;
  GLsizei const stride = GLsizei(floatsPerEdge*sizeof(float));
  this->_sidesVao->addAttrib(this->_adjacency,0,componentsPerVertex3D ,GL_FLOAT,stride,offset,normalized,divisor);
  offset += componentsPerVertex3D*sizeof(float);
  this->_sidesVao->addAttrib(this->_adjacency,1,componentsPerVertex3D ,GL_FLOAT,stride,offset,normalized,divisor);
  offset += componentsPerVertex3D*sizeof(float);
  this->_sidesVao->addAttrib(this->_adjacency,2,floatsPerNofOppositeVertices,GL_FLOAT,stride,offset,normalized,divisor);
  offset += floatsPerNofOppositeVertices*sizeof(float);
  for(GLuint oppositeIndex=0;oppositeIndex<adj->getMaxMultiplicity();++oppositeIndex){
    this->_sidesVao->addAttrib(this->_adjacency,3+oppositeIndex,componentsPerVertex3D,GL_FLOAT,stride,offset,normalized,divisor);
    offset += componentsPerVertex3D*sizeof(float);
  }
}

void VSSV::_createCapDataUsingPoints(std::shared_ptr<Adjacency>const&adj){
  assert(this!=nullptr);
  assert(adj!=nullptr);
  //create and fill adjacency buffer on GPU
  //(A,B,C)*
  //A - vertex A of an triangle
  //B - vertex B of an triangle
  //C - vertex C of an triangle

  size_t const sizeofTriangleInBytes = componentsPerVertex3D*verticesPerTriangle*sizeof(float);
  this->_caps = std::make_shared<ge::gl::Buffer>(adj->getNofTriangles()*sizeofTriangleInBytes,adj->getVertices());

  this->_capsVao = std::make_shared<ge::gl::VertexArray>();
  GLsizei const stride     = GLsizei(sizeofTriangleInBytes);
  GLenum  const normalized = GL_FALSE;
  size_t  const nofCapsPerTriangle = 2;
  GLuint  const divisor    = GLuint(nofCapsPerTriangle);
  for(size_t i=0;i<verticesPerTriangle;++i){
    GLintptr offset = sizeofVertex3DInBytes * i;
    GLuint   index = GLuint(i);
    this->_capsVao->addAttrib(this->_caps,index,componentsPerVertex3D,GL_FLOAT,stride,offset,normalized,divisor);
  }

  this->_nofTriangles = adj->getNofTriangles();
}



void VSSV::_createSideDataUsingAllPlanes(std::shared_ptr<Adjacency>const&adj){
  assert(this!=nullptr);
  assert(adj!=nullptr);
  size_t const maxNofOppositeVertices = adj->getMaxMultiplicity();
  //(A,B,M,T0,T1,...)*
  //A - vertex A of an edge 3*float
  //B - vertex B of an edge 3*float
  //Tn - triangle planes n*4*float
  //n < maxMultiplicity
  size_t const floatsPerEdge = verticesPerEdge*componentsPerVertex3D + maxNofOppositeVertices*componentsPerPlane3D;
  this->_adjacency = std::make_shared<ge::gl::Buffer>(adj->getNofEdges()*floatsPerEdge*sizeof(float));
  float*ptr=(float*)this->_adjacency->map();
  for(size_t edgeIndex=0;edgeIndex<adj->getNofEdges();++edgeIndex){
    auto edgePtr                 = ptr + edgeIndex*floatsPerEdge;
    auto edgeVertexAPtr          = edgePtr;
    auto edgeVertexBPtr          = edgeVertexAPtr + componentsPerVertex3D;
    auto edgeOppositeVerticesPtr = edgeVertexBPtr + componentsPerVertex3D;
    size_t const edgeVertexAIndex = 0;
    size_t const edgeVertexBIndex = 1;
    std::memcpy(edgeVertexAPtr,adj->getVertices()+adj->getEdge(edgeIndex,edgeVertexAIndex),sizeofVertex3DInBytes);
    std::memcpy(edgeVertexBPtr,adj->getVertices()+adj->getEdge(edgeIndex,edgeVertexBIndex),sizeofVertex3DInBytes);
    for(size_t oppositeIndex=0;oppositeIndex<adj->getNofOpposite(edgeIndex);++oppositeIndex)
      std::memcpy(
          edgeOppositeVerticesPtr+oppositeIndex*componentsPerPlane3D,
          glm::value_ptr(computePlane(
              toVec3(adj->getVertices()+adj->getEdge(edgeIndex,edgeVertexAIndex) ),
              toVec3(adj->getVertices()+adj->getEdge(edgeIndex,edgeVertexBIndex) ),
              toVec3(adj->getVertices()+adj->getOpposite(edgeIndex,oppositeIndex))
              )),
          sizeofPlane3DInBytes);
    size_t const nofEmptyOppositeVertices = maxNofOppositeVertices-adj->getNofOpposite(edgeIndex);
    std::memset(
        edgeOppositeVerticesPtr+adj->getNofOpposite(edgeIndex)*componentsPerPlane3D,
        0,
        sizeofPlane3DInBytes*nofEmptyOppositeVertices);
  }
  this->_adjacency->unmap();
  this->_nofEdges = adj->getNofEdges();

  //create vertex array for sides
  //divisor = maxMultiplicity -> attrib are modified once per edge
  this->_sidesVao = std::make_shared<ge::gl::VertexArray>();
  GLenum const normalized = GL_FALSE;
  GLuint const divisor = GLuint(adj->getMaxMultiplicity());
  GLintptr offset = 0;
  GLsizei const stride = GLsizei(floatsPerEdge*sizeof(float));
  this->_sidesVao->addAttrib(this->_adjacency,0,componentsPerVertex3D ,GL_FLOAT,stride,offset,normalized,divisor);
  offset += componentsPerVertex3D*sizeof(float);
  this->_sidesVao->addAttrib(this->_adjacency,1,componentsPerVertex3D ,GL_FLOAT,stride,offset,normalized,divisor);
  offset += componentsPerVertex3D*sizeof(float);
  for(GLuint oppositeIndex=0;oppositeIndex<adj->getMaxMultiplicity();++oppositeIndex){
    this->_sidesVao->addAttrib(this->_adjacency,3+oppositeIndex,componentsPerPlane3D,GL_FLOAT,stride,offset,normalized,divisor);
    offset += componentsPerPlane3D*sizeof(float);
  }
}

void VSSV::_createSideDataUsingPlanes(std::shared_ptr<Adjacency>const&adj){
  assert(this!=nullptr);
  assert(adj!=nullptr);
  size_t const maxNofOppositeVertices = adj->getMaxMultiplicity();
  //(A,B,M,T0,T1,...)*
  //A - vertex A of an edge 3*float
  //B - vertex B of an edge 3*float
  //M - multiplicity of an edge 1*float
  //Tn - triangle planes n*4*float
  //n < maxMultiplicity
  size_t const floatsPerEdge = verticesPerEdge*componentsPerVertex3D + floatsPerNofOppositeVertices + maxNofOppositeVertices*componentsPerPlane3D;
  this->_adjacency = std::make_shared<ge::gl::Buffer>(adj->getNofEdges()*floatsPerEdge*sizeof(float));
  float*ptr=(float*)this->_adjacency->map();
  for(size_t edgeIndex=0;edgeIndex<adj->getNofEdges();++edgeIndex){
    auto edgePtr = ptr+edgeIndex*floatsPerEdge;
    auto edgeVertexAPtr = edgePtr;
    auto edgeVertexBPtr = edgeVertexAPtr + componentsPerVertex3D;
    auto edgeNofOppositePtr = edgeVertexBPtr + componentsPerVertex3D;
    auto edgeOppositeVerticesPtr = edgeNofOppositePtr + floatsPerNofOppositeVertices;
    size_t const edgeVertexAIndex = 0;
    size_t const edgeVertexBIndex = 1;
    std::memcpy(edgeVertexAPtr,adj->getVertices()+adj->getEdge(edgeIndex,edgeVertexAIndex),sizeofVertex3DInBytes);
    std::memcpy(edgeVertexBPtr,adj->getVertices()+adj->getEdge(edgeIndex,edgeVertexBIndex),sizeofVertex3DInBytes);
    *edgeNofOppositePtr = float(adj->getNofOpposite(edgeIndex));
    for(size_t oppositeIndex=0;oppositeIndex<adj->getNofOpposite(edgeIndex);++oppositeIndex)
      std::memcpy(
          edgeOppositeVerticesPtr+oppositeIndex*componentsPerPlane3D,
          glm::value_ptr(computePlane(
              toVec3(adj->getVertices()+adj->getEdge(edgeIndex,edgeVertexAIndex) ),
              toVec3(adj->getVertices()+adj->getEdge(edgeIndex,edgeVertexBIndex) ),
              toVec3(adj->getVertices()+adj->getOpposite(edgeIndex,oppositeIndex))
              )),
          sizeofPlane3DInBytes);
    size_t const nofEmptyOppositeVertices = maxNofOppositeVertices-adj->getNofOpposite(edgeIndex);
    std::memset(
        edgeOppositeVerticesPtr+adj->getNofOpposite(edgeIndex)*componentsPerPlane3D,
        0,
        sizeofPlane3DInBytes*nofEmptyOppositeVertices);
  }
  this->_adjacency->unmap();
  this->_nofEdges = adj->getNofEdges();

  //create vertex array for sides
  //divisor = maxMultiplicity -> attrib are modified once per edge
  this->_sidesVao = std::make_shared<ge::gl::VertexArray>();
  GLenum const normalized = GL_FALSE;
  GLuint const divisor = GLuint(adj->getMaxMultiplicity());
  GLintptr offset = 0;
  GLsizei const stride = GLsizei(floatsPerEdge*sizeof(float));
  this->_sidesVao->addAttrib(this->_adjacency,0,componentsPerVertex3D ,GL_FLOAT,stride,offset,normalized,divisor);
  offset += componentsPerVertex3D*sizeof(float);
  this->_sidesVao->addAttrib(this->_adjacency,1,componentsPerVertex3D ,GL_FLOAT,stride,offset,normalized,divisor);
  offset += componentsPerVertex3D*sizeof(float);
  this->_sidesVao->addAttrib(this->_adjacency,2,floatsPerNofOppositeVertices,GL_FLOAT,stride,offset,normalized,divisor);
  offset += floatsPerNofOppositeVertices*sizeof(float);
  for(GLuint oppositeIndex=0;oppositeIndex<adj->getMaxMultiplicity();++oppositeIndex){
    this->_sidesVao->addAttrib(this->_adjacency,3+oppositeIndex,componentsPerPlane3D,GL_FLOAT,stride,offset,normalized,divisor);
    offset += componentsPerPlane3D*sizeof(float);
  }
}

VSSV::VSSV(
    std::shared_ptr<ge::gl::Texture>const&shadowMask     ,
    std::shared_ptr<Model>          const&model          ,
    std::shared_ptr<ge::gl::Texture>const&depth          ,
    ShadowVolumesParams             const&svParams       ,
    size_t                          const&maxMultiplicity,
    VSSVParams                      const&params         ):
  ShadowVolumes(shadowMask,depth,svParams),
  _params      (params                    )
{
  assert(this!=nullptr);

  //compute adjacency of the model
  std::vector<float>vertices;
  model->getVertices(vertices);
  size_t const nofTriangles = vertices.size()/(componentsPerVertex3D*verticesPerTriangle);
  auto adj = std::make_shared<Adjacency>(vertices.data(),nofTriangles,maxMultiplicity);
  this->_maxMultiplicity = adj->getMaxMultiplicity();

  //create and fill adjacency buffer for sides on GPU
  if(this->_params.usePlanes){
    if(this->_params.useAllOppositeVertices){
      this->_createSideDataUsingAllPlanes(adj);
    }else{
      this->_createSideDataUsingPlanes(adj);
    }
  }else{
    this->_createSideDataUsingPoints(adj);
  }

#include"VSSVShaders.h"
#include"SilhouetteShaders.h"

  this->_drawSidesProgram = std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER,
        "#version 450\n",
        this->_params.usePlanes             ?ge::gl::Shader::define("USE_PLANES"               ):"",
        this->_params.useStrips             ?ge::gl::Shader::define("USE_TRIANGLE_STRIPS"      ):"",
        this->_params.useAllOppositeVertices?ge::gl::Shader::define("USE_ALL_OPPOSITE_VERTICES"):"",
        silhouetteFunctions,
        _drawSidesVertexShaderSrc));

  this->_createCapDataUsingPoints(adj);

  this->_drawCapsProgram = std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER,
        "#version 450\n",
        silhouetteFunctions,
        _drawCapsVertexShaderSrc));
}

VSSV::~VSSV(){}

void VSSV::drawSides(
    glm::vec4 const&lightPosition   ,
    glm::mat4 const&viewMatrix      ,
    glm::mat4 const&projectionMatrix){
  assert(this!=nullptr);
  assert(this->_drawSidesProgram!=nullptr);
  assert(this->_sidesVao!=nullptr);
  this->_drawSidesProgram->use();
  this->_drawSidesProgram->setMatrix4fv("viewMatrix"      ,glm::value_ptr(viewMatrix      ));
  this->_drawSidesProgram->setMatrix4fv("projectionMatrix",glm::value_ptr(projectionMatrix));
  this->_drawSidesProgram->set4fv      ("lightPosition"   ,glm::value_ptr(lightPosition   ));
  this->_sidesVao->bind();
  if(this->_params.useStrips)
    glDrawArraysInstanced(GL_TRIANGLE_STRIP,0,4,GLsizei(this->_nofEdges*this->_maxMultiplicity));
  else
    glDrawArraysInstanced(GL_TRIANGLES     ,0,6,GLsizei(this->_nofEdges*this->_maxMultiplicity));
  this->_sidesVao->unbind();
}

void VSSV::drawCaps(
    glm::vec4 const&lightPosition,
    glm::mat4 const&viewMatrix         ,
    glm::mat4 const&projectionMatrix   ){
  assert(this!=nullptr);
  assert(this->_drawCapsProgram!=nullptr);
  assert(this->_capsVao!=nullptr);
  this->_drawCapsProgram->use();
  this->_drawCapsProgram->setMatrix4fv("viewMatrix"      ,glm::value_ptr(viewMatrix      ));
  this->_drawCapsProgram->setMatrix4fv("projectionMatrix",glm::value_ptr(projectionMatrix));
  this->_drawCapsProgram->set4fv      ("lightPosition"   ,glm::value_ptr(lightPosition   ));
  this->_capsVao->bind();
  size_t  const nofCapsPerTriangle = 2;
  GLuint  const nofInstances = GLuint(nofCapsPerTriangle * this->_nofTriangles);
  GLsizei const nofVertices  = GLsizei(verticesPerTriangle);
  GLint   const firstVertex  = 0;
  glDrawArraysInstanced(GL_TRIANGLES,firstVertex,nofVertices,nofInstances);
  this->_capsVao->unbind();
}

