#include"CSSVSOE.h"
#include"FastAdjacency.h"

#include<geCore/Dtemplates.h>

struct DrawArraysIndirectCommand{
  uint32_t nofVertices  = 0;
  uint32_t nofInstances = 0;
  uint32_t firstVertex  = 0;
  uint32_t baseInstance = 0;
};

void CSSVSOE::_createSidesData(std::shared_ptr<Adjacency const>const&adj){
  assert(this!=nullptr);
  assert(adj!=nullptr);

  size_t const nofVec4PerEdge = verticesPerEdge + adj->getMaxMultiplicity();
  this->_edges = std::make_shared<ge::gl::Buffer>(sizeof(float)*componentsPerVertex4D*nofVec4PerEdge*adj->getNofEdges());

  auto const dstPtr = static_cast<float      *>(this->_edges->map());
  auto const srcPtr = static_cast<float const*>(adj->getVertices() );

  std::vector<size_t>cardinality;
  cardinality.resize(adj->getMaxMultiplicity());

  for(size_t e=0;e<adj->getNofEdges();++e){
    cardinality.at(adj->getNofOpposite(e)-1)++;

    auto const dstEdgePtr             = dstPtr + e*nofVec4PerEdge*componentsPerVertex4D;
    auto const dstVertexAPtr          = dstEdgePtr;
    auto const dstVertexBPtr          = dstVertexAPtr + componentsPerVertex4D;
    auto const dstOppositeVerticesPtr = dstVertexBPtr + componentsPerVertex4D;

    auto const srcVertexAPtr          = srcPtr + adj->getEdge(e,0);
    auto const srcVertexBPtr          = srcPtr + adj->getEdge(e,1);

    size_t const sizeofVertex3DInBytes = componentsPerVertex3D * sizeof(float);

    std::memcpy(dstVertexAPtr,srcVertexAPtr,sizeofVertex3DInBytes);
    dstVertexAPtr[3] = 1.f;

    std::memcpy(dstVertexBPtr,srcVertexBPtr,sizeofVertex3DInBytes);
    dstVertexBPtr[3] = 1.f;

    for(size_t o=0;o<adj->getNofOpposite(e);++o){
      auto const dstOppositeVertexPtr = dstOppositeVerticesPtr + o*componentsPerVertex4D;
      auto const plane = computePlane(toVec3(srcPtr+adj->getEdgeVertexA(e)),toVec3(srcPtr+adj->getEdgeVertexB(e)),toVec3(srcPtr+adj->getOpposite(e,o)));
      std::memcpy(dstOppositeVertexPtr,&plane,sizeof(plane));
    }

    size_t const nofEmptyOppositeVertices = adj->getMaxMultiplicity() - adj->getNofOpposite(e);
    size_t const sizeofEmptyVerticesInBytes = sizeof(float)*componentsPerVertex4D*nofEmptyOppositeVertices;
    auto dstEmptyOppositeVerticesPtr = dstOppositeVerticesPtr + adj->getNofOpposite(e)*componentsPerVertex4D;
    std::memset(dstEmptyOppositeVerticesPtr,0,sizeofEmptyVerticesInBytes);
  }
  this->_edges->unmap();
  this->_nofEdges = adj->getNofEdges();
  this->_maxMultiplicity = adj->getMaxMultiplicity();

  this->_silhouettes = std::make_shared<ge::gl::Buffer>(
        sizeof(float)*componentsPerVertex3D*2*this->_nofEdges,
        nullptr,GL_DYNAMIC_COPY);

  this->_sidesVao = std::make_shared<ge::gl::VertexArray>();
  this->_sidesVao->addAttrib(this->_silhouettes,0,componentsPerVertex3D,GL_FLOAT);

  std::vector<DrawArraysIndirectCommand>cmds;
  cmds.resize(this->_maxMultiplicity);
  size_t multiplicityOffset = 0;
  for(size_t m=0;m<this->_maxMultiplicity;++m){
    cmds.at(m).nofInstances = 1;
    cmds.at(m).firstVertex  = static_cast<uint32_t>(multiplicityOffset*verticesPerEdge);
    multiplicityOffset += cardinality.at(m);
  }

  this->_dibo=std::make_shared<ge::gl::Buffer>(sizeof(DrawArraysIndirectCommand)*cmds.size(),cmds.data());
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

#include"CSSVSOEShaders.h"
#include"SilhouetteShaders.h"

  this->_computeSidesProgram = std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER,
        "#version 450 core\n",
        ge::gl::Shader::define("WORKGROUP_SIZE_X",int32_t(this->_params.computeSidesWGS)),
        ge::gl::Shader::define("MAX_MULTIPLICITY",int32_t(this->_maxMultiplicity       )),
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
  assert(this->_silhouettes        !=nullptr);

  for(size_t m=0;m<this->_maxMultiplicity;++m)
    this->_dibo->clear(GL_R32UI,m*sizeof(DrawArraysIndirectCommand),sizeof(uint32_t),GL_RED_INTEGER,GL_UNSIGNED_INT);

  glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
  this->_computeSidesProgram
    ->set1ui    ("numEdge"           ,uint32_t(this->_nofEdges)    )
    ->set4fv    ("lightPosition"     ,glm::value_ptr(lightPosition))
    ->bindBuffer("edges"             ,this->_edges                 )
    ->bindBuffer("silhouettes"       ,this->_silhouettes           )
    ->bindBuffer("drawIndirectBuffer",this->_dibo                  )
    ->dispatch((GLuint)ge::core::getDispatchSize(this->_nofEdges,this->_params.computeSidesWGS));

  glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
  glFinish();

#if 1
  auto dptr = static_cast<DrawArraysIndirectCommand const*>(this->_dibo->map());
  for(size_t i=0;i<this->_maxMultiplicity;++i){
    std::cout<<dptr->nofVertices<<" "<<dptr->nofInstances<<" "<<dptr->firstVertex<<" "<<dptr->baseInstance<<std::endl;
    dptr++;
  }
  this->_dibo->unmap();


  auto ptr = static_cast<glm::vec4*>(this->_edges->map());
  for(size_t i=0;i<this->_nofEdges*4;++i){
    std::cout<<ptr->x<<" "<<ptr->y<<" "<<ptr->z<<" "<<ptr->w<<std::endl;
    ptr++;
  }
  this->_edges->unmap();

  auto ptr3 = static_cast<glm::vec3*>(this->_silhouettes->map());
  for(size_t i=0;i<this->_nofEdges*2;++i){
    std::cout<<ptr3->x<<" "<<ptr3->y<<" "<<ptr3->z<<std::endl;
    ptr3++;
  }
  this->_silhouettes->unmap();
#endif
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

  for(size_t m=0;m<this->_maxMultiplicity;++m){
    glStencilOpValueAMD(GL_FRONT_AND_BACK,static_cast<GLuint>(m+1));
    glDrawArraysIndirect(GL_PATCHES,reinterpret_cast<void const*>(m*sizeof(DrawArraysIndirectCommand)));
  }
  glStencilOpValueAMD(GL_FRONT_AND_BACK,1);

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

