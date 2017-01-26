#include"RSSV.h"

#include<geCore/Dtemplates.h>
#include"ProgramExtension.h"
#include"RSSVTiles.h"

const size_t HIERARCHICALDEPTHTEXTURE_BINDING_DEPTH     = 0;
const size_t HIERARCHICALDEPTHTEXTURE_BINDING_HDT       = 1;

const size_t HIERARCHICALDEPTHTEXTURE_BINDING_HDTINPUT  = 0;
const size_t HIERARCHICALDEPTHTEXTURE_BINDING_HDTOUTPUT = 1;

const size_t RASTERIZE_BINDING_HDT         = 0;
const size_t RASTERIZE_BINDING_SSM         = 1;
const size_t RASTERIZE_BINDING_SILHOUETTES = 0;

const size_t     WAVEFRONT_SIZE = 64;
const size_t     TILE_EDGE_SIZE = size_t(glm::sqrt(WAVEFRONT_SIZE));
const glm::uvec2 TILE_SIZE      = glm::uvec2(uint32_t(TILE_EDGE_SIZE),uint32_t(TILE_EDGE_SIZE));

RSSV::RSSV(
    std::shared_ptr<ge::gl::Texture>const&shadowMask     ,
    glm::uvec2                      const&windowSize     ,
    std::shared_ptr<ge::gl::Texture>const&depthTexture   ,
    std::shared_ptr<Model>          const&model          ,
    size_t                          const&maxMultiplicity,
    RSSVParams                      const&params         ):
  _windowSize  (windowSize  ),
  _shadowMask  (shadowMask  ),
  _depthTexture(depthTexture),
  _params      (params      )
{
  assert(this!=nullptr);
  assert(
      (windowSize.x==8    && windowSize.y==8   ) ||
      (windowSize.x==64   && windowSize.y==64  ) ||
      (windowSize.x==512  && windowSize.y==512 ) ||
      (windowSize.x==4096 && windowSize.y==4096) );
  (void)model;
  if(windowSize.x == 8   )this->_nofLevels = 1;
  if(windowSize.x == 64  )this->_nofLevels = 2;
  if(windowSize.x == 512 )this->_nofLevels = 3;
  if(windowSize.x == 4096)this->_nofLevels = 4;

#include"SilhouetteShaders.h"
#include"RSSVShaders.h"

  this->_generateHDT0Program = makeComputeProgram(
      defineComputeShaderHeader(TILE_SIZE,WAVEFRONT_SIZE),
      ge::gl::Shader::define("HIERARCHICALDEPTHTEXTURE_BINDING_DEPTH",(int)HIERARCHICALDEPTHTEXTURE_BINDING_DEPTH),
      ge::gl::Shader::define("HIERARCHICALDEPTHTEXTURE_BINDING_HDT"  ,(int)HIERARCHICALDEPTHTEXTURE_BINDING_HDT  ),
      _generateHDT0Src);
  this->_generateHDTProgram = makeComputeProgram(
      defineComputeShaderHeader(TILE_SIZE,WAVEFRONT_SIZE),
      ge::gl::Shader::define("HIERARCHICALDEPTHTEXTURE_BINDING_HDTINPUT" ,(int)HIERARCHICALDEPTHTEXTURE_BINDING_HDTINPUT ),
      ge::gl::Shader::define("HIERARCHICALDEPTHTEXTURE_BINDING_HDTOUTPUT",(int)HIERARCHICALDEPTHTEXTURE_BINDING_HDTOUTPUT),
      _generateHDTSrc);
  glm::uvec2 hdtSize = TILE_SIZE;
  for(size_t l=0;l<this->_nofLevels;++l){
    this->_HDT.push_back(std::make_shared<ge::gl::Texture>(GL_TEXTURE_2D,GL_RG32F,1,hdtSize.x,hdtSize.y));
    this->_HDT.back()->texParameteri(GL_TEXTURE_MAG_FILTER,GL_NEAREST               );
    this->_HDT.back()->texParameteri(GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_NEAREST);
    float data[2]={1,-1};
    this->_HDT.back()->clear(0,GL_RG,GL_FLOAT,data);
    hdtSize*=TILE_SIZE;
  }


  this->_computeSilhouettesProgram = makeComputeProgram(
      defineComputeShaderHeader(this->_params.computeSilhouetteWGS,WAVEFRONT_SIZE),
      ge::gl::Shader::define("MAX_MULTIPLICITY",int(maxMultiplicity              )),
      ge::gl::Shader::define("LOCAL_ATOMIC"    ,int(this->_params.localAtomic    )),
      ge::gl::Shader::define("CULL_SIDES"      ,int(this->_params.cullSides      )),
      ge::gl::Shader::define("USE_PLANES"      ,int(this->_params.usePlanes      )),
      silhouetteFunctions,
      _computeSilhouettesSrc);

  std::vector<float>vertices;
  model->getVertices(vertices);
  size_t const nofTriangles = vertices.size()/(verticesPerTriangle*componentsPerVertex3D);
  auto adj = std::make_shared<Adjacency>(vertices.data(),nofTriangles,maxMultiplicity);

  size_t const nofVec4PerEdge = verticesPerEdge + adj->getMaxMultiplicity();
  this->_edges = std::make_shared<ge::gl::Buffer>(sizeof(float)*componentsPerVertex4D*nofVec4PerEdge*adj->getNofEdges());

  float      *dstPtr = (float      *)this->_edges->map();
  float const*srcPtr = (float const*)adj->getVertices();

  for(size_t e=0;e<adj->getNofEdges();++e){
    auto dstEdgePtr             = dstPtr + e*nofVec4PerEdge*componentsPerVertex4D;
    auto dstVertexAPtr          = dstEdgePtr;
    auto dstVertexBPtr          = dstVertexAPtr + componentsPerVertex4D;
    auto dstOppositeVerticesPtr = dstVertexBPtr + componentsPerVertex4D;

    auto srcVertexAPtr          = srcPtr + adj->getEdge(e,0);
    auto srcVertexBPtr          = srcPtr + adj->getEdge(e,1);

    size_t const sizeofVertex3DInBytes = componentsPerVertex3D * sizeof(float);

    std::memcpy(dstVertexAPtr,srcVertexAPtr,sizeofVertex3DInBytes);
    dstVertexAPtr[3] = (float)adj->getNofOpposite(e);

    std::memcpy(dstVertexBPtr,srcVertexBPtr,sizeofVertex3DInBytes);
    dstVertexBPtr[3] = 1.f;

    for(size_t o=0;o<adj->getNofOpposite(e);++o){
      auto dstOppositeVertexPtr = dstOppositeVerticesPtr + o*componentsPerVertex4D;
      if(this->_params.usePlanes){
        auto const plane = computePlane(toVec3(srcPtr+adj->getEdgeVertexA(e)),toVec3(srcPtr+adj->getEdgeVertexB(e)),toVec3(srcPtr+adj->getOpposite(e,o)));
        std::memcpy(dstOppositeVertexPtr,&plane,sizeof(plane));
      }else{
        auto srcOppositeVertexPtr = srcPtr + adj->getOpposite(e,o);
        std::memcpy(dstOppositeVertexPtr,srcOppositeVertexPtr,sizeofVertex3DInBytes);
        dstOppositeVertexPtr[3] = 1.f;
      }
    }

    size_t const nofEmptyOppositeVertices = adj->getMaxMultiplicity() - adj->getNofOpposite(e);
    size_t const sizeofEmptyVerticesInBytes = sizeof(float)*componentsPerVertex4D*nofEmptyOppositeVertices;
    auto dstEmptyOppositeVerticesPtr = dstOppositeVerticesPtr + adj->getNofOpposite(e)*componentsPerVertex4D;
    std::memset(dstEmptyOppositeVerticesPtr,0,sizeofEmptyVerticesInBytes);
  }
  this->_edges->unmap();
  this->_nofEdges = adj->getNofEdges();

  this->_silhouettes=std::make_shared<ge::gl::Buffer>(
      sizeof(float)*componentsPerVertex4D*2*this->_nofEdges,
      nullptr,GL_DYNAMIC_COPY);
  this->_silhouettes->clear(GL_R32F,GL_RED,GL_FLOAT);

  struct DispatchIndirectCommand{
    uint32_t nofWorkGroupsX = 0;
    uint32_t nofWorkGroupsY = 0;
    uint32_t nofWorkGroupsZ = 0;
  };
  DispatchIndirectCommand cmd;
  cmd.nofWorkGroupsY = 1;
  cmd.nofWorkGroupsZ = 1;
  this->_dispatchIndirectBuffer=std::make_shared<ge::gl::Buffer>(sizeof(DispatchIndirectCommand),&cmd);

  /*
  this->_rasterizeProgram = makeComputeProgram(
      defineComputeShaderHeader(glm::uvec2(WAVEFRONT_SIZE,this->_silhouettesPerWorkgroup),WAVEFRONT_SIZE),
      ge::gl::Shader::define("NUMBER_OF_LEVELS"             ,(int)this->_nofLevels               ),
      ge::gl::Shader::define("NUMBER_OF_LEVELS_MINUS_ONE"   ,(int)this->_nofLevels-1             ),
      ge::gl::Shader::define("SILHOUETTES_PER_WORKGROUP"    ,(int)this->_silhouettesPerWorkgroup ),
      ge::gl::Shader::define("RASTERIZE_BINDING_SSM"        ,(int)RASTERIZE_BINDING_SSM          ),
      ge::gl::Shader::define("RASTERIZE_BINDING_HDT"        ,(int)RASTERIZE_BINDING_HDT          ),
      ge::gl::Shader::define("RASTERIZE_BINDING_SILHOUETTES",(int)RASTERIZE_BINDING_SILHOUETTES  ),
      _rasterizeSrc);
  */


}

RSSV::~RSSV(){}

void RSSV::create(
    glm::vec4 const&lightPosition,
    glm::mat4 const&view         ,
    glm::mat4 const&projection   ){
  assert(this!=nullptr);
  (void)lightPosition;
  (void)view;
  (void)projection;
  if(this->timeStamp)this->timeStamp->stamp("");
  this->_generateHDT();
  if(this->timeStamp)this->timeStamp->stamp("computeHDT");
  this->_computeSilhouettes(lightPosition);
  if(this->timeStamp)this->timeStamp->stamp("computeSilhouettes");
  this->_rasterize(lightPosition,view,projection);
  if(this->timeStamp)this->timeStamp->stamp("rasterize");
}

void RSSV::_generateHDT(){
  assert(this!=nullptr);
  this->_generateHDT0Program->use();
  this->_generateHDT0Program->set2uiv("windowSize",glm::value_ptr(this->_windowSize));
  this->_depthTexture->bind(HIERARCHICALDEPTHTEXTURE_BINDING_DEPTH);
  this->_HDT[this->_nofLevels-1]->bindImage(HIERARCHICALDEPTHTEXTURE_BINDING_HDT);
  glm::uvec2 wgs = this->_windowSize/TILE_SIZE;

  glDispatchCompute(wgs.x,wgs.y,1);
  glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
  this->_generateHDTProgram->use();
  this->_generateHDTProgram->set2uiv("windowSize",glm::value_ptr(this->_windowSize));

  for(int l=(int)this->_nofLevels-2;l>=0;--l){
    this->_HDT[l+1]->bindImage(HIERARCHICALDEPTHTEXTURE_BINDING_HDTINPUT );
    this->_HDT[l  ]->bindImage(HIERARCHICALDEPTHTEXTURE_BINDING_HDTOUTPUT);
    glDispatchCompute(wgs.x,wgs.y,1);
    wgs/=TILE_SIZE;
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
  }
}

void RSSV::_computeSilhouettes(glm::vec4 const&lightPosition){
  assert(this!=nullptr);
  this->_dispatchIndirectBuffer->clear(GL_R32UI,0,sizeof(unsigned),GL_RED_INTEGER,GL_UNSIGNED_INT);
  glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
  this->_computeSilhouettesProgram
    ->set1ui    ("numEdge"               ,uint32_t(this->_nofEdges)    )
    ->set4fv    ("lightPosition"         ,glm::value_ptr(lightPosition))
    ->bindBuffer("edges"                 ,this->_edges                 )
    ->bindBuffer("silhouettes"           ,this->_silhouettes           )
    ->bindBuffer("dispatchIndirectBuffer",this->_dispatchIndirectBuffer)
    ->dispatch(GLuint(ge::core::getDispatchSize(this->_nofEdges,this->_params.computeSilhouetteWGS)));
  glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
  /*
  auto ptr = (float*)this->_silhouettes->map();
  for(size_t i=0;i<10;++i){
    std::cout<<ptr[i*7+0]<<" "<<ptr[i*7+1]<<" "<<ptr[i*7+2]<<std::endl;
    std::cout<<ptr[i*7+3]<<" "<<ptr[i*7+4]<<" "<<ptr[i*7+5]<<std::endl;
    std::cout<<ptr[i*7+6]<<std::endl;
  }
  this->_silhouettes->unmap();
  // */
  /*
  auto ptr = (float*)this->_edges->map();
  for(size_t i=0;i<10;++i){
    for(size_t k=0;k<4;++k){
      for(size_t l=0;l<4;++l)
        std::cout<<ptr[(i*4+k)*4+l]<<" ";
      std::cout<<std::endl;
    }
    std::cout<<std::endl;
  }
  this->_edges->unmap();
  // */

}

void RSSV::_rasterize(glm::vec4 const&lightPosition,glm::mat4 const&view,glm::mat4 const&projection){
  assert(this!=nullptr);
  (void)lightPosition;
  (void)view;
  (void)projection;
}
