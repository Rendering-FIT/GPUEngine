#include"Sintorn.h"
#include"SintornTiles.h"
#include"FastAdjacency.h"
#include<geCore/Dtemplates.h>
#include<sstream>

#define VEC4_PER_SHADOWFRUSTUM 6
#define FLOATS_PER_SHADOWFRUSTUM (VEC4_PER_SHADOWFRUSTUM*4)
#define UINT_BIT_SIZE 32

const size_t DRAWHDB_BINDING_HDBIMAGE = 0;
const size_t DRAWHDB_BINDING_HDT      = 1;

const size_t WRITEDEPTHTEXTURE_BINDING_DEPTH  = 0;
const size_t WRITEDEPTHTEXTURE_BINDING_HDT    = 1;
const size_t WRITEDEPTHTEXTURE_BINDING_NORMAL = 2;

const size_t HIERARCHICALDEPTHTEXTURE_BINDING_HDTINPUT  = 0;
const size_t HIERARCHICALDEPTHTEXTURE_BINDING_HDTOUTPUT = 1;

size_t RASTERIZETEXTURE_BINDING_FINALSTENCILMASK = 0;
size_t RASTERIZETEXTURE_BINDING_HST              = 1;
size_t RASTERIZETEXTURE_BINDING_HDT              = 5;
size_t RASTERIZETEXTURE_BINDING_SHADOWFRUSTA     = 0;

const size_t MERGETEXTURE_BINDING_HSTINPUT  = 0;
const size_t MERGETEXTURE_BINDING_HSTOUTPUT = 1;

const size_t WRITESTENCILTEXTURE_BINDING_FINALSTENCILMASK = 0;
const size_t WRITESTENCILTEXTURE_BINDING_HSTINPUT         = 1;

Sintorn::Sintorn(
    glm::uvec2                      const&windowSize,
    std::shared_ptr<ge::gl::Texture>const&depthTexture,
    std::shared_ptr<ge::gl::Texture>const&normalTexture,
    std::shared_ptr<Model>          const&model,
    size_t                                wavefrontSize,
    size_t                                shadowFrustumusPerWorkGroup,
    float                                 bias,
    bool                                  discardBackFacing,
    std::shared_ptr<ge::gl::Texture>const&shadowMask):_windowSize(windowSize),_discardBackFacing(discardBackFacing),_depthTexture(depthTexture),_normalTexture(normalTexture){
  assert(this!=nullptr);

  this->_shadowMask = shadowMask;

  this->_useUniformTileSizeInClipSpace=false;
  this->_useUniformTileDivisibility   =false;

  //set wavefront size
  this->_wavefrontSize=wavefrontSize;
  this->_shadowFrustaPerWorkGroup=shadowFrustumusPerWorkGroup;

  //compute tiles sizes in tiles
  chooseTileSizes(this->_tileDivisibility,this->_windowSize,this->_wavefrontSize);
  this->_nofLevels = this->_tileDivisibility.size();

  //compute tile size in pixels
  this->_tileSizeInPixels.resize(this->_nofLevels,glm::uvec2(1u,1u));
  for(size_t l=0;l<this->_nofLevels;++l)
    for(size_t m=l+1;m<this->_nofLevels;++m)
      this->_tileSizeInPixels[l]*=this->_tileDivisibility[m];

  //compute tiles sizes in clip space
  for(auto const&x:this->_tileSizeInPixels)
    this->_tileSizeInClipSpace.push_back(glm::vec2(2.f)/glm::vec2(windowSize)*glm::vec2(x));

  //compute level size
  this->_tileCount.resize(this->_nofLevels,glm::uvec2(1u,1u));
  for(size_t l=0;l<this->_nofLevels;++l)
    for(size_t m=l;m<this->_nofLevels;++m)
      this->_tileCount[m]*=this->_tileDivisibility[l];

  auto divRoundUp = [](uint32_t x,uint32_t y)->uint32_t{return (x/y)+((x%y)?1:0);};
  this->_usedTiles.resize(this->_nofLevels,glm::uvec2(0u,0u));
  this->_usedTiles.back() = this->_windowSize;
  for(int l=(int)this->_nofLevels-2;l>=0;--l){
    this->_usedTiles[l].x = divRoundUp(this->_usedTiles[l+1].x,this->_tileDivisibility[l+1].x);
    this->_usedTiles[l].y = divRoundUp(this->_usedTiles[l+1].y,this->_tileDivisibility[l+1].y);
  }

  //*
  for(size_t l=0;l<this->_nofLevels;++l)
    std::cerr<<"TileCount: "<<this->_tileCount[l].x<<" "<<this->_tileCount[l].y<<std::endl;
  for(size_t l=0;l<this->_nofLevels;++l)
    std::cerr<<"UsedTiles: "<<this->_usedTiles[l].x<<" "<<this->_usedTiles[l].y<<std::endl;
  for(size_t l=0;l<this->_nofLevels;++l)
    std::cerr<<"TileDivisibility: "<<this->_tileDivisibility[l].x<<" "<<this->_tileDivisibility[l].y<<std::endl;
  for(size_t l=0;l<this->_nofLevels;++l)
    std::cerr<<"TileSizeInClip: "<<this->_tileSizeInClipSpace[l].x<<" "<<this->_tileSizeInClipSpace[l].y<<std::endl;
  for(unsigned l=0;l<this->_nofLevels;++l)
    std::cerr<<"TileSizeInPixels: "<<this->_tileSizeInPixels[l].x<<" "<<this->_tileSizeInPixels[l].y<<std::endl;
  // */
  
  std::vector<float>vertices;
  model->getVertices(vertices);
  this->_nofTriangles = vertices.size()/3/3;
  
  //allocate shadowfrustum buffer
  this->_shadowFrusta=std::make_shared<ge::gl::Buffer>(sizeof(float)*FLOATS_PER_SHADOWFRUSTUM*this->_nofTriangles);

  //allocate triangles
  this->_triangles=std::make_shared<ge::gl::Buffer>(sizeof(float)*4*3*this->_nofTriangles);
  float*Ptr=(float*)this->_triangles->map();
  for(unsigned t=0;t<this->_nofTriangles;++t)
    for(unsigned p=0;p<3;++p){
      for(unsigned k=0;k<3;++k)
        Ptr[(t*3+p)*4+k]=vertices[(t*3+p)*3+k];
      Ptr[(t*3+p)*4+3]=1;
    }
  this->_triangles->unmap();

  //compile shader programs
#include"SintornShaders.h"
  this->WriteDepthTextureProgram=std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(
        GL_COMPUTE_SHADER,
        "#version 450 core\n",
        ge::gl::Shader::define("LOCAL_TILE_SIZE_X",(int)this->_tileDivisibility[this->_nofLevels-1].x),
        ge::gl::Shader::define("LOCAL_TILE_SIZE_Y",(int)this->_tileDivisibility[this->_nofLevels-1].y),
        ge::gl::Shader::define("WRITEDEPTHTEXTURE_BINDING_DEPTH" ,(int)WRITEDEPTHTEXTURE_BINDING_DEPTH ),
        ge::gl::Shader::define("WRITEDEPTHTEXTURE_BINDING_HDT"   ,(int)WRITEDEPTHTEXTURE_BINDING_HDT   ),
        ge::gl::Shader::define("WRITEDEPTHTEXTURE_BINDING_NORMAL",(int)WRITEDEPTHTEXTURE_BINDING_NORMAL),
        ge::gl::Shader::define("DISCARD_BACK_FACING"             ,int(this->_discardBackFacing)   ),
        writeDepthTextureCompSrc));

  this->HierarchicalDepthTextureProgram=std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(
        GL_COMPUTE_SHADER,
        "#version 450 core\n",
        ge::gl::Shader::define("WAVEFRONT_SIZE",(uint32_t)this->_wavefrontSize),
        ge::gl::Shader::define("DO_NOT_COUNT_WITH_INFINITY"),
        ge::gl::Shader::define("HIERARCHICALDEPTHTEXTURE_BINDING_HDTINPUT" ,(int)HIERARCHICALDEPTHTEXTURE_BINDING_HDTINPUT ),
        ge::gl::Shader::define("HIERARCHICALDEPTHTEXTURE_BINDING_HDTOUTPUT",(int)HIERARCHICALDEPTHTEXTURE_BINDING_HDTOUTPUT),
        hierarchicalDepthTextureCompSrc));


  this->WriteStencilTextureProgram=std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(
        GL_COMPUTE_SHADER,
        "#version 450 core\n",
        ge::gl::Shader::define("LOCAL_TILE_SIZE_X",(int)this->_tileDivisibility[this->_nofLevels-1].x),
        ge::gl::Shader::define("LOCAL_TILE_SIZE_Y",(int)this->_tileDivisibility[this->_nofLevels-1].y),
        ge::gl::Shader::define("WRITESTENCILTEXTURE_BINDING_FINALSTENCILMASK",(int)WRITESTENCILTEXTURE_BINDING_FINALSTENCILMASK),
        ge::gl::Shader::define("WRITESTENCILTEXTURE_BINDING_HSTINPUT"        ,(int)WRITESTENCILTEXTURE_BINDING_HSTINPUT        ),
        writeStencilTextureCompSrc));


  this->MergeTextureProgram=std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(
        GL_COMPUTE_SHADER,
        "#version 450 core\n",
        ge::gl::Shader::define("WAVEFRONT_SIZE"                ,(uint32_t)this->_wavefrontSize),
        ge::gl::Shader::define("MERGETEXTURE_BINDING_HSTINPUT" ,(int)MERGETEXTURE_BINDING_HSTINPUT ),
        ge::gl::Shader::define("MERGETEXTURE_BINDING_HSTOUTPUT",(int)MERGETEXTURE_BINDING_HSTOUTPUT),
        mergeTextureCompSrc));

  this->ClearStencilProgram=std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(
        GL_COMPUTE_SHADER,
        clearStencilCompSrc));

  this->SFProgram=std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(
        GL_COMPUTE_SHADER,
        "#version 450 core\n",
        ge::gl::Shader::define("BIAS",bias)+
        ge::gl::Shader::define("WAVEFRONT_SIZE",(uint32_t)this->_wavefrontSize),
        shadowFrustumCompSrc));

  RASTERIZETEXTURE_BINDING_HDT=RASTERIZETEXTURE_BINDING_HST+this->_nofLevels;

  std::string TileSizeInClipSpaceDefines="";
  if(this->_useUniformTileSizeInClipSpace)
    TileSizeInClipSpaceDefines+=ge::gl::Shader::define("USE_UNIFORM_TILE_SIZE_IN_CLIP_SPACE");
  else{
    for(unsigned l=0;l<this->_nofLevels;++l){
      std::stringstream DefineName;
      DefineName<<"TILE_SIZE_IN_CLIP_SPACE"<<l;
      TileSizeInClipSpaceDefines+=ge::gl::Shader::define(DefineName.str(),2,glm::value_ptr(this->_tileSizeInClipSpace[l]));
    }
  }
  std::string TileDivisibilityDefines="";
  if(this->_useUniformTileDivisibility)
    TileDivisibilityDefines+=ge::gl::Shader::define("USE_UNIFORM_TILE_DIVISIBILITY");
  else{
    for(unsigned l=0;l<this->_nofLevels;++l){
      std::stringstream DefineName;
      DefineName<<"TILE_DIVISIBILITY"<<l;
      TileDivisibilityDefines+=ge::gl::Shader::define(DefineName.str(),2,glm::value_ptr(this->_tileDivisibility[l]));
    }
  }
  this->RasterizeTextureProgram=std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(
        GL_COMPUTE_SHADER,
        "#version 450 core\n",
        ge::gl::Shader::define("NUMBER_OF_LEVELS"            ,(int)this->_nofLevels               ),
        ge::gl::Shader::define("NUMBER_OF_LEVELS_MINUS_ONE"  ,(int)this->_nofLevels-1             ),
        ge::gl::Shader::define("WAVEFRONT_SIZE"              ,(int)this->_wavefrontSize           ),
        ge::gl::Shader::define("SHADOWFRUSTUMS_PER_WORKGROUP",(int)this->_shadowFrustaPerWorkGroup),
        TileSizeInClipSpaceDefines,
        TileDivisibilityDefines,
        ge::gl::Shader::define("RASTERIZETEXTURE_BINDING_FINALSTENCILMASK",(int)RASTERIZETEXTURE_BINDING_FINALSTENCILMASK),
        ge::gl::Shader::define("RASTERIZETEXTURE_BINDING_HST"             ,(int)RASTERIZETEXTURE_BINDING_HST             ),
        ge::gl::Shader::define("RASTERIZETEXTURE_BINDING_HDT"             ,(int)RASTERIZETEXTURE_BINDING_HDT             ),
        ge::gl::Shader::define("RASTERIZETEXTURE_BINDING_SHADOWFRUSTA"    ,(int)RASTERIZETEXTURE_BINDING_SHADOWFRUSTA    ),
        rasterizeTextureCompSrc));

   this->_blitProgram = std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER  ,blitCompSrc));

  this->_drawHSTProgram = std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER  ,drawHSTVertSrc),
      std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER,drawHSTFragSrc));

  this->_drawFinalStencilMask = std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER  ,drawHSTVertSrc),
      std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER,drawFinalStencilMaskFragSrc));




  this->_emptyVao=std::make_shared<ge::gl::VertexArray>();

  this->_finalStencilMask = std::make_shared<ge::gl::Texture>(GL_TEXTURE_2D,GL_R32UI,1,this->_windowSize.x,this->_windowSize.y);
  this->_finalStencilMask->texParameteri(GL_TEXTURE_MAG_FILTER,GL_NEAREST);
  this->_finalStencilMask->texParameteri(GL_TEXTURE_MIN_FILTER,GL_NEAREST);

  for(size_t l=0;l<this->_nofLevels;++l){
    this->_HDT.push_back(std::make_shared<ge::gl::Texture>(GL_TEXTURE_2D,GL_RG32F,1,this->_usedTiles[l].x,this->_usedTiles[l].y));
    this->_HDT.back()->texParameteri(GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    this->_HDT.back()->texParameteri(GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_NEAREST);
    float data[2]={1,-1};
    this->_HDT.back()->clear(0,GL_RG,GL_FLOAT,data);
    //glClearTexImage(this->_HDT.back()->getId(),0,GL_RG,GL_FLOAT,data);
  }

  size_t RESULT_LENGTH_IN_UINT=this->_wavefrontSize/UINT_BIT_SIZE;
  if(RESULT_LENGTH_IN_UINT==0)RESULT_LENGTH_IN_UINT=1;

  for(size_t l=0;l<this->_nofLevels;++l){
    this->_HST.push_back(std::make_shared<ge::gl::Texture>(GL_TEXTURE_2D,GL_R32UI,1,GLsizei(this->_usedTiles[l].x*RESULT_LENGTH_IN_UINT),this->_usedTiles[l].y));
    this->_HST.back()->texParameteri(GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    this->_HST.back()->texParameteri(GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_NEAREST);
    uint8_t data[2] = {0,0};
    this->_HST.back()->clear(0,GL_RG_INTEGER,GL_UNSIGNED_BYTE,data);
    //glClearTexImage(this->_HDT.back()->getId(),0,GL_RG,GL_UNSIGNED_INT,&data);
  }
}

Sintorn::~Sintorn(){
}

void Sintorn::GenerateHierarchyTexture(glm::vec4 const&lightPosition){
  if(this->_nofLevels<2)return;

  this->WriteDepthTextureProgram->use();
  this->WriteDepthTextureProgram->set2uiv("windowSize",glm::value_ptr(this->_windowSize));
  this->_depthTexture->bind(WRITEDEPTHTEXTURE_BINDING_DEPTH);
  if(this->_discardBackFacing){
    this->_normalTexture->bind(WRITEDEPTHTEXTURE_BINDING_NORMAL);
    this->WriteDepthTextureProgram->set4fv("lightPosition",glm::value_ptr(lightPosition));
  }
  this->_HDT[this->_nofLevels-1]->bindImage(WRITEDEPTHTEXTURE_BINDING_HDT);
  glDispatchCompute(
      this->_tileCount[this->_nofLevels-2].x,
      this->_tileCount[this->_nofLevels-2].y,
      1);

  glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

  this->HierarchicalDepthTextureProgram->use();
  this->HierarchicalDepthTextureProgram->set2uiv("WindowSize",glm::value_ptr(this->_windowSize));

  this->HierarchicalDepthTextureProgram->set2uiv("TileDivisibility",glm::value_ptr(this->_tileDivisibility.data()[0]),(GLsizei)this->_nofLevels);
  this->HierarchicalDepthTextureProgram->set2uiv("TileSizeInPixels",glm::value_ptr(this->_tileSizeInPixels.data()[0]),(GLsizei)this->_nofLevels);

  for(int l=(int)this->_nofLevels-2;l>=0;--l){
    this->HierarchicalDepthTextureProgram->set1ui("DstLevel",(unsigned)l);
    this->_HDT[l+1]->bindImage(HIERARCHICALDEPTHTEXTURE_BINDING_HDTINPUT );
    this->_HDT[l  ]->bindImage(HIERARCHICALDEPTHTEXTURE_BINDING_HDTOUTPUT);
    glDispatchCompute(this->_usedTiles[l].x,this->_usedTiles[l].y,1);
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
  }
}


void Sintorn::ComputeShadowFrusta(glm::vec4 const&lightPosition,glm::mat4 mvp){
  this->SFProgram->use();
  this->SFProgram->set1ui("NumTriangles",(uint32_t)this->_nofTriangles);
  this->SFProgram->setMatrix4fv("ModelViewProjection",glm::value_ptr(mvp));
  this->SFProgram->set4fv("LightPosition",glm::value_ptr(lightPosition));
  this->SFProgram->setMatrix4fv("TransposeInverseModelViewProjection",glm::value_ptr(glm::inverse(glm::transpose(mvp))));
  this->_triangles->bindBase(GL_SHADER_STORAGE_BUFFER,0);
  this->_shadowFrusta->bindBase(GL_SHADER_STORAGE_BUFFER,1);
  glDispatchCompute(GLuint(this->_nofTriangles/this->_shadowFrustaWGS+1),1,1);
  glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
}

void Sintorn::RasterizeTexture(){
  this->_finalStencilMask->clear(0,GL_RED_INTEGER,GL_UNSIGNED_INT,nullptr);
  //glClearTexImage(this->_finalStencilMask->getId(),0,GL_RED_INTEGER,GL_UNSIGNED_INT,NULL);
  for(size_t l=0;l<this->_nofLevels;++l){
    this->_HST[l]->clear(0,GL_RED_INTEGER,GL_UNSIGNED_INT,nullptr);
    //glClearTexImage(this->_HST[l]->getId(),0,GL_RED_INTEGER,GL_UNSIGNED_INT,NULL);
  }
  glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

  this->RasterizeTextureProgram->use();

  if(this->_useUniformTileDivisibility)
    this->RasterizeTextureProgram->set2uiv("TileDivisibility",glm::value_ptr(this->_tileDivisibility.data()[0]),(GLsizei)this->_nofLevels);
  if(this->_useUniformTileSizeInClipSpace)
    this->RasterizeTextureProgram->set2fv("TileSizeInClipSpace",glm::value_ptr(this->_tileSizeInClipSpace.data()[0]),(GLsizei)this->_nofLevels);

  this->RasterizeTextureProgram->set1ui("NumberOfTriangles",(uint32_t)this->_nofTriangles);

  this->_shadowFrusta->bindBase(GL_SHADER_STORAGE_BUFFER,0);

  for(size_t l=0;l<this->_nofLevels;++l)
    this->_HDT[l]->bind(GLuint(RASTERIZETEXTURE_BINDING_HDT+l));
  for(size_t l=0;l<this->_nofLevels;++l)
    this->_HST[l]->bindImage(GLuint(RASTERIZETEXTURE_BINDING_HST+l));

  this->_finalStencilMask->bindImage(GLuint(RASTERIZETEXTURE_BINDING_FINALSTENCILMASK));

  size_t maxSize = 65536/2;
  size_t workgroups = ge::core::getDispatchSize(this->_nofTriangles,this->_shadowFrustaPerWorkGroup);
  size_t offset = 0;
  while(offset+maxSize<=workgroups){
    this->RasterizeTextureProgram->set1ui("triangleOffset",(uint32_t)offset);
    glDispatchCompute(GLuint(maxSize),1,1);
    offset += maxSize;
  }
  if(offset<workgroups){
    this->RasterizeTextureProgram->set1ui("triangleOffset",(uint32_t)offset);
    glDispatchCompute(GLuint(workgroups-offset),1,1);
  }


  glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
}

void Sintorn::MergeTexture(){
  this->MergeTextureProgram->use();
  this->MergeTextureProgram->set2uiv("WindowSize",glm::value_ptr(this->_windowSize));

  GLsync Sync=0;
  for(size_t l=0;l<this->_nofLevels-1;++l){
    this->MergeTextureProgram->set2uiv("DstTileSizeInPixels",glm::value_ptr(this->_tileSizeInPixels[l]));
    this->MergeTextureProgram->set2uiv("DstTileDivisibility",glm::value_ptr(this->_tileDivisibility[l]));

    this->_HST[l  ]->bindImage(MERGETEXTURE_BINDING_HSTINPUT);
    this->_HST[l+1]->bindImage(MERGETEXTURE_BINDING_HSTOUTPUT);
    if(l>0){
      glClientWaitSync(Sync,0,GL_TIMEOUT_IGNORED);
      glDeleteSync(Sync);
    }
    glDispatchCompute(l==0?1:this->_tileCount[l-1].x,l==0?1:this->_tileCount[l-1].y,1);
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
    if(l<this->_nofLevels
        //*
        -1
        // */
      )Sync=glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE,0);
  }

  //glFinish();
  //glMemoryBarrier(GL_ALL_BARRIER_BITS);

  this->WriteStencilTextureProgram->use();
  this->WriteStencilTextureProgram->set2uiv("WindowSize",glm::value_ptr(this->_windowSize));

  this->_finalStencilMask->bindImage(WRITESTENCILTEXTURE_BINDING_FINALSTENCILMASK);
  this->_HST[this->_nofLevels-1]->bindImage(WRITESTENCILTEXTURE_BINDING_HSTINPUT);

  glClientWaitSync(Sync,0,GL_TIMEOUT_IGNORED);
  glDeleteSync(Sync);

  glDispatchCompute(
      this->_tileCount[this->_nofLevels-2].x,
      this->_tileCount[this->_nofLevels-2].y,
      1);
  glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
  //glFinish();
}

void Sintorn::create(
    glm::vec4 const&lightPosition,
    glm::mat4 const&view      ,
    glm::mat4 const&projection){
  assert(this!=nullptr);
  (void)lightPosition;
  (void)view;
  (void)projection;
  if(this->timeStamp)this->timeStamp->stamp("");
  this->GenerateHierarchyTexture(lightPosition);
  if(this->timeStamp)this->timeStamp->stamp("computeHDT");
  this->ComputeShadowFrusta(lightPosition,projection*view);
  if(this->timeStamp)this->timeStamp->stamp("computeShadowFrusta");
  this->RasterizeTexture();
  if(this->timeStamp)this->timeStamp->stamp("rasterize");
  this->MergeTexture();
  if(this->timeStamp)this->timeStamp->stamp("merge");
  this->blit();
  if(this->timeStamp)this->timeStamp->stamp("blit");
}

void Sintorn::drawHST(size_t l){
  assert(this!=nullptr);
  this->_drawHSTProgram->use();
  this->_HST[l]->bindImage(0);
  this->_emptyVao->bind();
  glDrawArrays(GL_TRIANGLE_STRIP,0,4);
  this->_emptyVao->unbind();
}

void Sintorn::drawFinalStencilMask(){
  assert(this!=nullptr);
  this->_drawFinalStencilMask->use();
  this->_finalStencilMask->bindImage(0);
  this->_emptyVao->bind();
  glDrawArrays(GL_TRIANGLE_STRIP,0,4);
  this->_emptyVao->unbind();
}

void Sintorn::blit(){
  assert(this!=nullptr);
  this->_blitProgram->use();
  this->_finalStencilMask->bindImage(0);
  this->_shadowMask->bindImage(1);
  this->_blitProgram->set2uiv("windowSize",glm::value_ptr(this->_windowSize));
  glDispatchCompute(
      (GLuint)ge::core::getDispatchSize(this->_windowSize.x,8),
      (GLuint)ge::core::getDispatchSize(this->_windowSize.y,8),1);
}
