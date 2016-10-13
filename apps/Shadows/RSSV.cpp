#include"RSSV.h"

#include<geCore/Dtemplates.h>
#include"ProgramExtension.h"
#include"RSSVTiles.h"

const size_t HIERARCHICALDEPTHTEXTURE_BINDING_DEPTH     = 0;
const size_t HIERARCHICALDEPTHTEXTURE_BINDING_HDT       = 1;

const size_t HIERARCHICALDEPTHTEXTURE_BINDING_HDTINPUT  = 0;
const size_t HIERARCHICALDEPTHTEXTURE_BINDING_HDTOUTPUT = 1;

const size_t     WAVEFRONT_SIZE = 64;
const size_t     TILE_EDGE_SIZE = size_t(glm::sqrt(WAVEFRONT_SIZE));
const glm::uvec2 TILE_SIZE      = glm::uvec2(uint32_t(TILE_EDGE_SIZE),uint32_t(TILE_EDGE_SIZE));

RSSV::RSSV(
    glm::uvec2                      const&windowSize          ,
    std::shared_ptr<ge::gl::Texture>const&shadowMask          ,
    std::shared_ptr<ge::gl::Texture>const&depthTexture        ,
    std::shared_ptr<Model>          const&model               ,
    size_t                          const&maxMultiplicity     ,
    size_t                          const&computeSilhouetteWGS,
    bool                            const&localAtomic         ,
    bool                            const&cullSides                          
    ):_windowSize(windowSize),_shadowMask(shadowMask),_depthTexture(depthTexture),_computeSilhouettesWGS(computeSilhouetteWGS){
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
      defineComputeShaderHeader(computeSilhouetteWGS,WAVEFRONT_SIZE),
      ge::gl::Shader::define("MAX_MULTIPLICITY",(int)maxMultiplicity),
      ge::gl::Shader::define("LOCAL_ATOMIC"    ,(int)localAtomic    ),
      ge::gl::Shader::define("CULL_SIDES"      ,(int)cullSides      ),
      _computeSilhouettesSrc);

  std::vector<float>vertices;
  model->getVertices(vertices);
  auto adj = std::make_shared<Adjacency>(vertices.data(),vertices.size()/9,maxMultiplicity);

  size_t numVer = 2+adj->getMaxMultiplicity();
  this->_edges = std::make_shared<ge::gl::Buffer>(sizeof(float)*4*numVer*adj->getNofEdges());

  float*Ptr=(float*)this->_edges->map();

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
  this->_edges->unmap();
  this->_nofEdges = adj->getNofEdges();

  this->_silhouettes=std::make_shared<ge::gl::Buffer>(
      sizeof(float)*4*2*this->_nofEdges,
      nullptr,GL_DYNAMIC_COPY);
  this->_silhouettes->clear(GL_R32F,GL_RED,GL_FLOAT);

  this->_dispatchIndirectBuffer=std::make_shared<ge::gl::Buffer>(sizeof(uint32_t)*3);
  unsigned*CPtr=(unsigned*)this->_dispatchIndirectBuffer->map();
  CPtr[0]=0;
  CPtr[1]=1;
  CPtr[2]=1;
  this->_dispatchIndirectBuffer->unmap();





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
  this->_computeSilhouettesProgram->use();
  this->_computeSilhouettesProgram->set1ui("numEdge",(uint32_t)this->_nofEdges);
  this->_computeSilhouettesProgram->set4fv("lightPosition",glm::value_ptr(lightPosition));
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER,0,this->_edges->getId()                 );
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER,1,this->_silhouettes->getId()           );
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER,2,this->_dispatchIndirectBuffer->getId());
  glDispatchCompute((GLuint)ge::core::getDispatchSize((uint32_t)this->_nofEdges,(uint32_t)this->_computeSilhouettesWGS),1,1);
  glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
}
