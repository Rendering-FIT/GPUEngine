#include"VSSV.h"
#include"FastAdjacency.h"
#include"VSSVShaders.h"

bool greaterVec(glm::vec3 const&a,glm::vec3 const&b){
  return dot(sign(a-b),glm::vec3(4.0f,2.0f,1.0f))>0.f;
}

void swapVec3(glm::vec3&a,glm::vec3&b){
  glm::vec3 z=a;
  a=b;
  b=z;
}

glm::vec4 computePlane(float const*A,float const*B,float const*C){
  glm::vec3 a=glm::vec3(A[0],A[1],A[2]);
  glm::vec3 b=glm::vec3(B[0],B[1],B[2]);
  glm::vec3 c=glm::vec3(C[0],C[1],C[2]);
  glm::vec3 z;
  bool swapped = false;
  if(greaterVec(a,b)){
    swapped = !swapped;
    swapVec3(a,b);
  }
  if(greaterVec(b,c)){
    swapped = !swapped;
    swapVec3(a,b);
  }
  if(greaterVec(a,b)){
    swapped = !swapped;
    swapVec3(a,b);
  }
  auto n = glm::normalize(glm::cross(b-a,c-a));
  auto p = glm::vec4(n,-glm::dot(n,a));
  if(swapped)return -p;
  return p;
}

VSSV::VSSV(
    size_t                          const&maxMultiplicity  ,
    bool                            const&zfail            ,
    glm::uvec2                      const&windowSize       ,
    std::shared_ptr<ge::gl::Texture>const&depth            ,
    std::shared_ptr<Model>          const&model            ,
    std::shared_ptr<ge::gl::Texture>const&shadowMask       ,
    bool                            const&usePlanes        ,
    bool                            const&useStrips        ,
    bool                            const&useAll           ):
  _windowSize(windowSize),
  _zfail(zfail),
  _usePlanes(usePlanes),
  _useStrips(useStrips),
  _useAllOppositeVertices(useAll)
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

  size_t const floatsPer3DVertex = 3;
  size_t const floatsPer3DPlane  = 4;
  size_t const verticesPerTriangle = 3;
  size_t const floatsPerTriangle = verticesPerTriangle*floatsPer3DVertex;
  size_t const verticesPerEdge = 2;
  size_t const floatsPerNofOppositeVertices = 1;
  size_t const maxNofOppositeVertices = maxMultiplicity;
  size_t const sizeofVertex3DInBytes = floatsPer3DVertex*sizeof(float);
  size_t const sizeofPlane3DInBytes = floatsPer3DPlane*sizeof(float);

  //compute adjacency of the model
  std::vector<float>vertices;
  model->getVertices(vertices);
  auto adj = std::make_shared<Adjacency>(vertices.data(),vertices.size()/floatsPerTriangle,maxMultiplicity);
  this->_maxMultiplicity = adj->getMaxMultiplicity();

  if(!this->_usePlanes){
    //create and fill adjacency buffer on GPU
    //(A,B,M,O0,O1,...)*
    //A - vertex A of an edge
    //B - vertex B of an edge
    //M - multiplicity of an edge
    //On - opposite vertex of an edge
    //n < maxMultiplicity
    size_t const floatsPerEdge = verticesPerEdge*floatsPer3DVertex + floatsPerNofOppositeVertices + maxNofOppositeVertices*floatsPer3DVertex;
    this->_adjacency = std::make_shared<ge::gl::Buffer>(adj->getNofEdges()*floatsPerEdge*sizeof(float));
    float*ptr=(float*)this->_adjacency->map();
    for(size_t edgeIndex=0;edgeIndex<adj->getNofEdges();++edgeIndex){
      auto edgePtr = ptr+edgeIndex*floatsPerEdge;
      auto edgeVertexAPtr = edgePtr;
      auto edgeVertexBPtr = edgeVertexAPtr + floatsPer3DVertex;
      auto edgeNofOppositePtr = edgeVertexBPtr + floatsPer3DVertex;
      auto edgeOppositeVerticesPtr = edgeNofOppositePtr + floatsPerNofOppositeVertices;
      size_t const edgeVertexAIndex = 0;
      size_t const edgeVertexBIndex = 1;
      std::memcpy(edgeVertexAPtr,adj->getVertices()+adj->getEdge(edgeIndex,edgeVertexAIndex),sizeofVertex3DInBytes);
      std::memcpy(edgeVertexBPtr,adj->getVertices()+adj->getEdge(edgeIndex,edgeVertexBIndex),sizeofVertex3DInBytes);
      *edgeNofOppositePtr = float(adj->getNofOpposite(edgeIndex));
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

    //create vertex array for sides
    //divisor = maxMultiplicity -> attrib are modified once per edge
    this->_sidesVao = std::make_shared<ge::gl::VertexArray>();
    GLenum const normalized = GL_FALSE;
    GLuint const divisor = GLuint(adj->getMaxMultiplicity());
    GLintptr offset = 0;
    GLsizei const stride = GLsizei(floatsPerEdge*sizeof(float));
    this->_sidesVao->addAttrib(this->_adjacency,0,floatsPer3DVertex ,GL_FLOAT,stride,offset,normalized,divisor);
    offset += floatsPer3DVertex*sizeof(float);
    this->_sidesVao->addAttrib(this->_adjacency,1,floatsPer3DVertex ,GL_FLOAT,stride,offset,normalized,divisor);
    offset += floatsPer3DVertex*sizeof(float);
    this->_sidesVao->addAttrib(this->_adjacency,2,floatsPerNofOppositeVertices,GL_FLOAT,stride,offset,normalized,divisor);
    offset += floatsPerNofOppositeVertices*sizeof(float);
    for(GLuint oppositeIndex=0;oppositeIndex<adj->getMaxMultiplicity();++oppositeIndex){
      this->_sidesVao->addAttrib(this->_adjacency,3+oppositeIndex,floatsPer3DVertex,GL_FLOAT,stride,offset,normalized,divisor);
      offset += floatsPer3DVertex*sizeof(float);
    }
  }else{
    //create and fill adjacency buffer on GPU
    if(this->_useAllOppositeVertices){
      //(A,B,M,T0,T1,...)*
      //A - vertex A of an edge 3*float
      //B - vertex B of an edge 3*float
      //Tn - triangle planes n*4*float
      //n < maxMultiplicity
      size_t const floatsPerEdge = verticesPerEdge*floatsPer3DVertex + maxNofOppositeVertices*floatsPer3DPlane;
      this->_adjacency = std::make_shared<ge::gl::Buffer>(adj->getNofEdges()*floatsPerEdge*sizeof(float));
      float*ptr=(float*)this->_adjacency->map();
      for(size_t edgeIndex=0;edgeIndex<adj->getNofEdges();++edgeIndex){
        auto edgePtr = ptr+edgeIndex*floatsPerEdge;
        auto edgeVertexAPtr = edgePtr;
        auto edgeVertexBPtr = edgeVertexAPtr + floatsPer3DVertex;
        auto edgeOppositeVerticesPtr = edgeVertexBPtr + floatsPer3DVertex;
        size_t const edgeVertexAIndex = 0;
        size_t const edgeVertexBIndex = 1;
        std::memcpy(edgeVertexAPtr,adj->getVertices()+adj->getEdge(edgeIndex,edgeVertexAIndex),sizeofVertex3DInBytes);
        std::memcpy(edgeVertexBPtr,adj->getVertices()+adj->getEdge(edgeIndex,edgeVertexBIndex),sizeofVertex3DInBytes);
        for(size_t oppositeIndex=0;oppositeIndex<adj->getNofOpposite(edgeIndex);++oppositeIndex)
          std::memcpy(
              edgeOppositeVerticesPtr+oppositeIndex*floatsPer3DPlane,
              glm::value_ptr(computePlane(
                  adj->getVertices()+adj->getEdge(edgeIndex,edgeVertexAIndex),
                  adj->getVertices()+adj->getEdge(edgeIndex,edgeVertexBIndex),
                  adj->getVertices()+adj->getOpposite(edgeIndex,oppositeIndex)
                  )),
              sizeofPlane3DInBytes);
        size_t const nofEmptyOppositeVertices = maxMultiplicity-adj->getNofOpposite(edgeIndex);
        std::memset(
            edgeOppositeVerticesPtr+adj->getNofOpposite(edgeIndex)*floatsPer3DPlane,
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
      this->_sidesVao->addAttrib(this->_adjacency,0,floatsPer3DVertex ,GL_FLOAT,stride,offset,normalized,divisor);
      offset += floatsPer3DVertex*sizeof(float);
      this->_sidesVao->addAttrib(this->_adjacency,1,floatsPer3DVertex ,GL_FLOAT,stride,offset,normalized,divisor);
      offset += floatsPer3DVertex*sizeof(float);
      for(GLuint oppositeIndex=0;oppositeIndex<adj->getMaxMultiplicity();++oppositeIndex){
        this->_sidesVao->addAttrib(this->_adjacency,3+oppositeIndex,floatsPer3DPlane,GL_FLOAT,stride,offset,normalized,divisor);
        offset += floatsPer3DPlane*sizeof(float);
      }
    }else{
      //(A,B,M,T0,T1,...)*
      //A - vertex A of an edge 3*float
      //B - vertex B of an edge 3*float
      //M - multiplicity of an edge 1*float
      //Tn - triangle planes n*4*float
      //n < maxMultiplicity
      size_t const floatsPerEdge = verticesPerEdge*floatsPer3DVertex + floatsPerNofOppositeVertices + maxNofOppositeVertices*floatsPer3DPlane;
      this->_adjacency = std::make_shared<ge::gl::Buffer>(adj->getNofEdges()*floatsPerEdge*sizeof(float));
      float*ptr=(float*)this->_adjacency->map();
      for(size_t edgeIndex=0;edgeIndex<adj->getNofEdges();++edgeIndex){
        auto edgePtr = ptr+edgeIndex*floatsPerEdge;
        auto edgeVertexAPtr = edgePtr;
        auto edgeVertexBPtr = edgeVertexAPtr + floatsPer3DVertex;
        auto edgeNofOppositePtr = edgeVertexBPtr + floatsPer3DVertex;
        auto edgeOppositeVerticesPtr = edgeNofOppositePtr + floatsPerNofOppositeVertices;
        size_t const edgeVertexAIndex = 0;
        size_t const edgeVertexBIndex = 1;
        std::memcpy(edgeVertexAPtr,adj->getVertices()+adj->getEdge(edgeIndex,edgeVertexAIndex),sizeofVertex3DInBytes);
        std::memcpy(edgeVertexBPtr,adj->getVertices()+adj->getEdge(edgeIndex,edgeVertexBIndex),sizeofVertex3DInBytes);
        *edgeNofOppositePtr = float(adj->getNofOpposite(edgeIndex));
        for(size_t oppositeIndex=0;oppositeIndex<adj->getNofOpposite(edgeIndex);++oppositeIndex)
          std::memcpy(
              edgeOppositeVerticesPtr+oppositeIndex*floatsPer3DPlane,
              glm::value_ptr(computePlane(
                  adj->getVertices()+adj->getEdge(edgeIndex,edgeVertexAIndex),
                  adj->getVertices()+adj->getEdge(edgeIndex,edgeVertexBIndex),
                  adj->getVertices()+adj->getOpposite(edgeIndex,oppositeIndex)
                  )),
              sizeofPlane3DInBytes);
        size_t const nofEmptyOppositeVertices = maxMultiplicity-adj->getNofOpposite(edgeIndex);
        std::memset(
            edgeOppositeVerticesPtr+adj->getNofOpposite(edgeIndex)*floatsPer3DPlane,
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
      this->_sidesVao->addAttrib(this->_adjacency,0,floatsPer3DVertex ,GL_FLOAT,stride,offset,normalized,divisor);
      offset += floatsPer3DVertex*sizeof(float);
      this->_sidesVao->addAttrib(this->_adjacency,1,floatsPer3DVertex ,GL_FLOAT,stride,offset,normalized,divisor);
      offset += floatsPer3DVertex*sizeof(float);
      this->_sidesVao->addAttrib(this->_adjacency,2,floatsPerNofOppositeVertices,GL_FLOAT,stride,offset,normalized,divisor);
      offset += floatsPerNofOppositeVertices*sizeof(float);
      for(GLuint oppositeIndex=0;oppositeIndex<adj->getMaxMultiplicity();++oppositeIndex){
        this->_sidesVao->addAttrib(this->_adjacency,3+oppositeIndex,floatsPer3DPlane,GL_FLOAT,stride,offset,normalized,divisor);
        offset += floatsPer3DPlane*sizeof(float);
      }
    }
  }

#include"VSSVShaders.h"
  this->_drawSides = std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER,
        "#version 450\n",
        this->_usePlanes?ge::gl::Shader::define("USE_PLANES_INSTEAD_OF_OPPOSITE_VERTICES"):"",
        this->_useStrips?ge::gl::Shader::define("USE_TRIANGLE_STRIPS"):"",
        this->_useAllOppositeVertices   ?ge::gl::Shader::define("USE_ALL_OPPOSITE_VERTICES"):"",
        _drawSidesVertexShaderSrc));

  this->_emptyVao = std::make_shared<ge::gl::VertexArray>();
#include"CSSVShaders.h"
  this->_blit = std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER,blitVPSrc),
      std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER,blitFPSrc));
}

VSSV::~VSSV(){}

void VSSV::create(
    glm::vec4 const&lightPosition,
    glm::mat4 const&view         ,
    glm::mat4 const&projection   ){
  (void)lightPosition;
  (void)view;
  (void)projection;

  if(this->timeStamp)this->timeStamp->stamp("");

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
  this->_drawSides->setMatrix4fv("viewMatrix"      ,glm::value_ptr(view      ));
  this->_drawSides->setMatrix4fv("projectionMatrix",glm::value_ptr(projection));
  this->_drawSides->set4fv("lightPosition",glm::value_ptr(lightPosition));
  this->_sidesVao->bind();
  if(this->_useStrips)
    glDrawArraysInstanced(GL_TRIANGLE_STRIP,0,4,GLsizei(this->_nofEdges*this->_maxMultiplicity));
  else
    glDrawArraysInstanced(GL_TRIANGLES,0,6,GLsizei(this->_nofEdges*this->_maxMultiplicity));
  //glDrawArraysIndirect(GL_PATCHES,NULL);
  this->_sidesVao->unbind();
  if(this->timeStamp)this->timeStamp->stamp("drawSides");

  if(this->_zfail){
    /*
       this->_drawCaps->use();
       this->_drawCaps->setMatrix4fv("mvp",glm::value_ptr(mvp));
       this->_drawCaps->set4fv("lightPosition",glm::value_ptr(lightPosition));
       this->_capsVao->bind();
       glDrawArrays(GL_TRIANGLES,0,(GLsizei)this->_nofTriangles*3);
       this->_capsVao->unbind();

       this->_fbo->unbind();
       if(this->timeStamp)this->timeStamp->stamp("drawCaps");
       */
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

