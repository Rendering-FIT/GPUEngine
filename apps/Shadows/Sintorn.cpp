#include"Sintorn.h"

#if 0

#include<sstream>

#define VEC4_PER_SHADOWFRUSTUM 6
#define FLOATS_PER_SHADOWFRUSTUM (VEC4_PER_SHADOWFRUSTUM*4)
#define UINT_BIT_SIZE 32

#define TESTSIZE (5000)

const int DRAWHDB_BINDING_HDBIMAGE = 0;
const int DRAWHDB_BINDING_HDT      = 1;

const int WRITEDEPTHTEXTURE_BINDING_DEPTH = 0;
const int WRITEDEPTHTEXTURE_BINDING_HDT   = 1;

const int HIERARCHICALDEPTHTEXTURE_BINDING_HDTINPUT  = 0;
const int HIERARCHICALDEPTHTEXTURE_BINDING_HDTOUTPUT = 1;

int RASTERIZETEXTURE_BINDING_FINALSTENCILMASK = 0;
int RASTERIZETEXTURE_BINDING_HST              = 1;
int RASTERIZETEXTURE_BINDING_HDT              = 5;
int RASTERIZETEXTURE_BINDING_SHADOWFRUSTA     = 0;

const int MERGETEXTURE_BINDING_HSTINPUT  = 0;
const int MERGETEXTURE_BINDING_HSTOUTPUT = 1;

const int WRITESTENCILTEXTURE_BINDING_FINALSTENCILMASK = 0;
const int WRITESTENCILTEXTURE_BINDING_HSTINPUT         = 1;

Sintorn::Sintorn(
    glm::uvec2 const&windowSize,
    std::shared_ptr<Model>const&model,
    uint32_t wavefrontSize,
    uint32_t shadowFrustumusPerWorkGroup){
  this->_useUniformTileSizeInClipSpace=false;
  this->_useUniformTileDivisibility   =false;

  //set wavefront size
  this->_wavefrontSize=wavefrontSize;
  this->_shadowFrustaPerWorkGroup=shadowFrustumusPerWorkGroup;

  this->_windowSize = windowSize;

  //compute tiles sizes in tiles
  this->_numLevels=chooseTileSizes(&this->_tileDivisibility,this->_windowSize,this->_wavefrontSize);


  //compute tile size in pixels
  this->TileSizeInPixels=new unsigned[this->NumLevels*2];
  for(unsigned l=0;l<this->NumLevels;++l)
    for(int k=0;k<2;++k)this->TileSizeInPixels[l*2+k]=1;

  for(unsigned l=0;l<this->NumLevels;++l)
    for(unsigned m=l+1;m<this->NumLevels;++m)
      for(int k=0;k<2;++k)this->TileSizeInPixels[l*2+k]*=this->TileDivisibility[m*2+k];

  //compute tiles sizes in clip space
  this->TileSizeInClipSpace=new float[this->NumLevels*2];
  for(unsigned l=0;l<this->NumLevels;++l)
    for(int k=0;k<2;++k)this->TileSizeInClipSpace[l*2+k]=2;

  /*
  for(unsigned l=0;l<this->NumLevels;++l)
    for(unsigned m=l;m<this->NumLevels;++m)
      for(int k=0;k<2;++k)this->TileSizeInClipSpace[m*2+k]/=this->TileDivisibility[l*2+k];
      */
  for(unsigned l=0;l<this->NumLevels;++l)
    for(int k=0;k<2;++k)this->TileSizeInClipSpace[l*2+k]=2./this->WindowSize[k]*this->TileSizeInPixels[l*2+k];



  //compute level size
  this->TileCount=new unsigned[this->NumLevels*2];
  for(unsigned l=0;l<this->NumLevels;++l)
    for(unsigned k=0;k<2;++k)this->TileCount[l*2+k]=1;
  for(unsigned l=0;l<this->NumLevels;++l)
    for(unsigned m=l;m<this->NumLevels;++m)
      for(unsigned k=0;k<2;++k)this->TileCount[m*2+k]*=this->TileDivisibility[l*2+k];

  //compute level offset
  this->HDBOffset=new unsigned[this->NumLevels];
  for(unsigned l=0;l<this->NumLevels;++l)this->HDBOffset[l]=0;
  for(unsigned l=1;l<this->NumLevels;++l)
    for(unsigned m=l;m<this->NumLevels;++m){
      this->HDBOffset[m]*=this->WavefrontSize;
      this->HDBOffset[m]+=this->WavefrontSize;
    }

  //*
  for(unsigned l=0;l<this->NumLevels;++l)
    std::cerr<<"Offset: "<<this->HDBOffset[l]<<std::endl;
  for(unsigned l=0;l<this->NumLevels;++l)
    std::cerr<<"TileCount: "<<this->TileCount[l*2+0]<<" "<<this->TileCount[l*2+1]<<std::endl;
  for(unsigned l=0;l<this->NumLevels;++l)
    std::cerr<<"TileDivisibility: "<<this->TileDivisibility[l*2+0]<<" "<<this->TileDivisibility[l*2+1]<<std::endl;
  for(unsigned l=0;l<this->NumLevels;++l)
    std::cerr<<"TileSizeInClip: "<<this->TileSizeInClipSpace[l*2+0]<<" "<<this->TileSizeInClipSpace[l*2+1]<<std::endl;
  for(unsigned l=0;l<this->NumLevels;++l)
    std::cerr<<"TileSizeInPixels: "<<this->TileSizeInPixels[l*2+0]<<" "<<this->TileSizeInPixels[l*2+1]<<std::endl;

  // */
  //allocate shadowfrustum buffer
  this->ShadowFrusta=new ge::gl::BufferObject(
      sizeof(float)*FLOATS_PER_SHADOWFRUSTUM*this->Adjacency->NumTriangles,
      NULL,GL_DYNAMIC_COPY);

  //allocate tringels
  this->Triangles=new ge::gl::BufferObject(
      sizeof(float)*4*3*this->Adjacency->NumTriangles,
      NULL,GL_DYNAMIC_COPY);
  float*Ptr=(float*)this->Triangles->map();
  for(unsigned t=0;t<this->Adjacency->NumTriangles;++t)
    for(unsigned p=0;p<3;++p){
      for(unsigned k=0;k<3;++k)
        Ptr[(t*3+p)*4+k]=this->Adjacency->Points[this->Adjacency->Triangles[t*3+p]*3+k];
      Ptr[(t*3+p)*4+3]=1;
    }
  this->Triangles->unmap();


  //allocate hierarchical depth buffer
  unsigned HDBSize=0;
  for(unsigned l=0;l<this->NumLevels;++l){
    HDBSize*=WavefrontSize;
    HDBSize+=WavefrontSize;
  }
  std::cerr<<"HDBSize: "<<HDBSize<<std::endl;
  this->HDB=new ge::gl::BufferObject(
      sizeof(float)*2*HDBSize,
      NULL,GL_DYNAMIC_COPY);
  float Data[]={1,-1};
  //this->HDB->Clear(GL_RG32F,GL_RED,GL_FLOAT,Data);
  glBindBuffer(GL_SHADER_STORAGE_BUFFER,this->HDB->getId());
  glClearBufferData(GL_SHADER_STORAGE_BUFFER,GL_RG32F,GL_RG,GL_FLOAT,Data);
  glBindBuffer(GL_SHADER_STORAGE_BUFFER,0);

  //allocate hierarchical stenil buffer
  this->HSB=new ge::gl::BufferObject(
      sizeof(unsigned)*WavefrontSize/UINT_BIT_SIZE*(HDBSize+1),
      NULL,GL_DYNAMIC_COPY);

  //compile shader programs
  try{
    this->WriteDepthProgram=new ge::gl::ProgramObject(
        ShaderDir+"methods/Sintorn/writedepth.comp",
        ge::gl::ShaderObject::define("LOCAL_TILE_SIZE_X",(int)this->TileDivisibility[(this->NumLevels-1)*2+0])+
        ge::gl::ShaderObject::define("LOCAL_TILE_SIZE_Y",(int)this->TileDivisibility[(this->NumLevels-1)*2+1]));
  }catch(std::string&e){
    std::cerr<<e<<std::endl;
  }
  
  try{
    this->WriteDepthTextureProgram=new ge::gl::ProgramObject(
        ShaderDir+"methods/Sintorn/writedepthtexture.comp",
        ge::gl::ShaderObject::define("LOCAL_TILE_SIZE_X",(int)this->TileDivisibility[(this->NumLevels-1)*2+0])+
        ge::gl::ShaderObject::define("LOCAL_TILE_SIZE_Y",(int)this->TileDivisibility[(this->NumLevels-1)*2+1])+
        ge::gl::ShaderObject::define("WRITEDEPTHTEXTURE_BINDING_DEPTH",WRITEDEPTHTEXTURE_BINDING_DEPTH)+
        ge::gl::ShaderObject::define("WRITEDEPTHTEXTURE_BINDING_HDT"  ,WRITEDEPTHTEXTURE_BINDING_HDT  )+
        "");
  }catch(std::string&e){
    std::cerr<<e<<std::endl;
  }

  try{
    this->HierarchicalDepthProgram=new ge::gl::ProgramObject(
        ShaderDir+"methods/Sintorn/hierarchicaldepthbuffer.comp",
        ge::gl::ShaderObject::define("WAVEFRONT_SIZE",WavefrontSize)+
        ge::gl::ShaderObject::define("DO_NOT_COUNT_WITH_INFINITY"));
  }catch(std::string&e){
    std::cerr<<e<<std::endl;
  }

  try{
    this->HierarchicalDepthTextureProgram=new ge::gl::ProgramObject(
        ShaderDir+"methods/Sintorn/hierarchicaldepthtexture.comp",
        ge::gl::ShaderObject::define("WAVEFRONT_SIZE",WavefrontSize)+
        ge::gl::ShaderObject::define("DO_NOT_COUNT_WITH_INFINITY")+
        ge::gl::ShaderObject::define("HIERARCHICALDEPTHTEXTURE_BINDING_HDTINPUT" ,HIERARCHICALDEPTHTEXTURE_BINDING_HDTINPUT )+
        ge::gl::ShaderObject::define("HIERARCHICALDEPTHTEXTURE_BINDING_HDTOUTPUT",HIERARCHICALDEPTHTEXTURE_BINDING_HDTOUTPUT)+
        "");
  }catch(std::string&e){
    std::cerr<<e<<std::endl;
  }

  try{
    this->WriteStencilProgram=new ge::gl::ProgramObject(
        ShaderDir+"methods/Sintorn/writestencil.comp",
        ge::gl::ShaderObject::define("LOCAL_TILE_SIZE_X",(int)this->TileDivisibility[(this->NumLevels-1)*2+0])+
        ge::gl::ShaderObject::define("LOCAL_TILE_SIZE_Y",(int)this->TileDivisibility[(this->NumLevels-1)*2+1]));
  }catch(std::string&e){
    std::cerr<<e<<std::endl;
  }

  try{
    this->WriteStencilTextureProgram=new ge::gl::ProgramObject(
        ShaderDir+"methods/Sintorn/writestenciltexture.comp",
        ge::gl::ShaderObject::define("LOCAL_TILE_SIZE_X",(int)this->TileDivisibility[(this->NumLevels-1)*2+0])+
        ge::gl::ShaderObject::define("LOCAL_TILE_SIZE_Y",(int)this->TileDivisibility[(this->NumLevels-1)*2+1])+
        ge::gl::ShaderObject::define("WRITESTENCILTEXTURE_BINDING_FINALSTENCILMASK",WRITESTENCILTEXTURE_BINDING_FINALSTENCILMASK)+
        ge::gl::ShaderObject::define("WRITESTENCILTEXTURE_BINDING_HSTINPUT"        ,WRITESTENCILTEXTURE_BINDING_HSTINPUT        )+
        "");
  }catch(std::string&e){
    std::cerr<<e<<std::endl;
  }

  try{
    this->MergeProgram=new ge::gl::ProgramObject(
        ShaderDir+"methods/Sintorn/merge.comp",
        ge::gl::ShaderObject::define("WAVEFRONT_SIZE",WavefrontSize)+
        "");
  }catch(std::string&e){
    std::cerr<<e<<std::endl;
  }

  try{
    this->MergeTextureProgram=new ge::gl::ProgramObject(
        ShaderDir+"methods/Sintorn/mergetexture.comp",
        ge::gl::ShaderObject::define("WAVEFRONT_SIZE"                ,                 WavefrontSize)+
        ge::gl::ShaderObject::define("MERGETEXTURE_BINDING_HSTINPUT" ,MERGETEXTURE_BINDING_HSTINPUT )+
        ge::gl::ShaderObject::define("MERGETEXTURE_BINDING_HSTOUTPUT",MERGETEXTURE_BINDING_HSTOUTPUT)+
        "");
  }catch(std::string&e){
    std::cerr<<e<<std::endl;
  }

  try{
    this->ClearStencilProgram=new ge::gl::ProgramObject(
        ShaderDir+"methods/Sintorn/clearstencil.comp");
  }catch(std::string&e){
    std::cerr<<e<<std::endl;
  }

  try{
    this->SFProgram=new ge::gl::ProgramObject(
        ShaderDir+"methods/Sintorn/shadowfrustum.comp",
        ge::gl::ShaderObject::define("BIAS",0.01f)+
        ge::gl::ShaderObject::define("WAVEFRONT_SIZE",WavefrontSize));
  }catch(std::string&e){
    std::cerr<<e<<std::endl;
  }

  try{
    std::string TileSizeInClipSpaceDefines="";
    if(this->UseUniformTileSizeInClipSpace)
      TileSizeInClipSpaceDefines+=ge::gl::ShaderObject::define("USE_UNIFORM_TILE_SIZE_IN_CLIP_SPACE");
    else{
      for(unsigned l=0;l<this->NumLevels;++l){
        std::stringstream DefineName;
        DefineName<<"TILE_SIZE_IN_CLIP_SPACE"<<l;
        TileSizeInClipSpaceDefines+=ge::gl::ShaderObject::define(DefineName.str(),2,this->TileSizeInClipSpace+l*2);
      }
    }
    std::string TileDivisibilityDefines="";
     if(this->UseUniformTileDivisibility)
      TileDivisibilityDefines+=ge::gl::ShaderObject::define("USE_UNIFORM_TILE_DIVISIBILITY");
    else{
      for(unsigned l=0;l<this->NumLevels;++l){
        std::stringstream DefineName;
        DefineName<<"TILE_DIVISIBILITY"<<l;
        TileDivisibilityDefines+=ge::gl::ShaderObject::define(DefineName.str(),2,this->TileDivisibility+l*2);
      }
    }
    this->RasterizeProgram=new ge::gl::ProgramObject(
        ShaderDir+"methods/Sintorn/rasterize.comp",
        ge::gl::ShaderObject::define("NUMBER_OF_LEVELS",(int)this->NumLevels)+
        ge::gl::ShaderObject::define("NUMBER_OF_LEVELS_MINUS_ONE",(int)this->NumLevels-1)+
        ge::gl::ShaderObject::define("WAVEFRONT_SIZE",(int)WavefrontSize)+
        ge::gl::ShaderObject::define("SHADOWFRUSTUMS_PER_WORKGROUP",(int)this->ShadowFrustaPerWorkGroup)+
        TileSizeInClipSpaceDefines+
        TileDivisibilityDefines
        );

  }catch(std::string&e){
    std::cerr<<e<<std::endl;
  }
  RASTERIZETEXTURE_BINDING_HDT=RASTERIZETEXTURE_BINDING_HST+this->NumLevels;
  
  try{
    std::string TileSizeInClipSpaceDefines="";
    if(this->UseUniformTileSizeInClipSpace)
      TileSizeInClipSpaceDefines+=ge::gl::ShaderObject::define("USE_UNIFORM_TILE_SIZE_IN_CLIP_SPACE");
    else{
      for(unsigned l=0;l<this->NumLevels;++l){
        std::stringstream DefineName;
        DefineName<<"TILE_SIZE_IN_CLIP_SPACE"<<l;
        TileSizeInClipSpaceDefines+=ge::gl::ShaderObject::define(DefineName.str(),2,this->TileSizeInClipSpace+l*2);
      }
    }
    std::string TileDivisibilityDefines="";
     if(this->UseUniformTileDivisibility)
      TileDivisibilityDefines+=ge::gl::ShaderObject::define("USE_UNIFORM_TILE_DIVISIBILITY");
    else{
      for(unsigned l=0;l<this->NumLevels;++l){
        std::stringstream DefineName;
        DefineName<<"TILE_DIVISIBILITY"<<l;
        TileDivisibilityDefines+=ge::gl::ShaderObject::define(DefineName.str(),2,this->TileDivisibility+l*2);
      }
    }
    this->RasterizeTextureProgram=new ge::gl::ProgramObject(
        ShaderDir+"methods/Sintorn/rasterizetexture.comp",
        ge::gl::ShaderObject::define("NUMBER_OF_LEVELS"            ,(int)this->NumLevels               )+
        ge::gl::ShaderObject::define("NUMBER_OF_LEVELS_MINUS_ONE"  ,(int)this->NumLevels-1             )+
        ge::gl::ShaderObject::define("WAVEFRONT_SIZE"              ,(int)WavefrontSize                 )+
        ge::gl::ShaderObject::define("SHADOWFRUSTUMS_PER_WORKGROUP",(int)this->ShadowFrustaPerWorkGroup)+
        TileSizeInClipSpaceDefines+
        TileDivisibilityDefines+
        ge::gl::ShaderObject::define("RASTERIZETEXTURE_BINDING_FINALSTENCILMASK",(int)RASTERIZETEXTURE_BINDING_FINALSTENCILMASK)+
        ge::gl::ShaderObject::define("RASTERIZETEXTURE_BINDING_HST"             ,(int)RASTERIZETEXTURE_BINDING_HST             )+
        ge::gl::ShaderObject::define("RASTERIZETEXTURE_BINDING_HDT"             ,(int)RASTERIZETEXTURE_BINDING_HDT             )+
        ge::gl::ShaderObject::define("RASTERIZETEXTURE_BINDING_SHADOWFRUSTA"    ,(int)RASTERIZETEXTURE_BINDING_SHADOWFRUSTA    )
        );
  }catch(std::string&e){
    std::cerr<<e<<std::endl;
  }
  
  try{
    this->DrawHDBProgram=new ge::gl::ProgramObject(
        ShaderDir+"methods/Sintorn/drawhdb.vp",
        ShaderDir+"methods/Sintorn/drawhdb.gp",
        ShaderDir+"methods/Sintorn/drawhdb.fp",
        ge::gl::ShaderObject::define("WAVEFRONT_SIZE",(int)this->WavefrontSize)+
        ge::gl::ShaderObject::define("TESTSIZE",(int)TESTSIZE)+
        ge::gl::ShaderObject::define("MAX_LEVELS",(int)this->NumLevels)+
        ge::gl::ShaderObject::define("DRAWHDB_BINDING_HDBIMAGE",DRAWHDB_BINDING_HDBIMAGE)+
        ge::gl::ShaderObject::define("DRAWHDB_BINDING_HDT"     ,DRAWHDB_BINDING_HDT     )+
        "");
  }catch(std::string&e){
    std::cerr<<e<<std::endl;
  }

  try{
    this->DrawHSBProgram=new ge::gl::ProgramObject(
        ShaderDir+"methods/Sintorn/drawhsb.vp",
        ShaderDir+"methods/Sintorn/drawhsb.gp",
        ShaderDir+"methods/Sintorn/drawhsb.fp",
        ge::gl::ShaderObject::define("WAVEFRONT_SIZE",(int)this->WavefrontSize)+
        ge::gl::ShaderObject::define("TESTSIZE",(int)TESTSIZE));
  }catch(std::string&e){
    std::cerr<<e<<std::endl;
  }

  try{
    this->CopyHDBProgram=new ge::gl::ProgramObject(
        ShaderDir+"methods/Sintorn/copyhdb2texture.comp",
        ge::gl::ShaderObject::define("WORKGROUP_SIZE",(int)(this->WavefrontSize*10))+
        ge::gl::ShaderObject::define("TESTSIZE",(int)TESTSIZE));
  }catch(std::string&e){
    std::cerr<<e<<std::endl;
  }

  try{
    this->CopyHSBProgram=new ge::gl::ProgramObject(
        ShaderDir+"methods/Sintorn/copyhsb2texture.comp",
        ge::gl::ShaderObject::define("WORKGROUP_SIZE",(int)(WavefrontSize*10))+
        ge::gl::ShaderObject::define("TESTSIZE",(int)TESTSIZE));
  }catch(std::string&e){
    std::cerr<<e<<std::endl;
  }

  this->EmptyVAO=new ge::gl::VertexArrayObject();

  glGenTextures(1,&this->HDBTexture);
  glBindTexture(GL_TEXTURE_2D,this->HDBTexture);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RG32F,TESTSIZE,TESTSIZE,0,GL_RG,
      GL_FLOAT,NULL);

  glGenTextures(1,&this->HSBTexture);
  glBindTexture(GL_TEXTURE_2D,this->HSBTexture);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RG32UI,TESTSIZE,TESTSIZE,0,GL_RG_INTEGER,
      GL_UNSIGNED_INT,NULL);

  glGenTextures(1,&this->FinalStencilMask);
  glBindTexture(GL_TEXTURE_2D,this->FinalStencilMask);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D,0,GL_R32UI,this->WindowSize[0],this->WindowSize[1],0,GL_RED_INTEGER,
      GL_UNSIGNED_BYTE,NULL);

  glGenTextures(1,&this->HDBImage);
  glBindTexture(GL_TEXTURE_2D,this->HDBImage);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RG32F,TESTSIZE,TESTSIZE,0,GL_RG,
      GL_FLOAT,NULL);

  glGenTextures(1,&this->HSBImage);
  glBindTexture(GL_TEXTURE_2D,this->HSBImage);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RG32UI,TESTSIZE,TESTSIZE,0,GL_RG_INTEGER,
      GL_UNSIGNED_INT,NULL);

  this->HDT=new GLuint[this->NumLevels];
  glGenTextures(this->NumLevels,this->HDT);
  for(unsigned l=0;l<this->NumLevels;++l){
    glBindTexture(GL_TEXTURE_2D,this->HDT[l]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_NEAREST);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RG32F,
        this->TileCount[l*2+0],
        this->TileCount[l*2+1],0,GL_RG,GL_FLOAT,NULL);
    float data[2]={1,-1};
    glClearTexImage(this->HDT[l],0,GL_RG,GL_FLOAT,data);
  }

  unsigned RESULT_LENGTH_IN_UINT=this->WavefrontSize/UINT_BIT_SIZE;
  if(RESULT_LENGTH_IN_UINT==0)RESULT_LENGTH_IN_UINT=1;
  this->HST=new GLuint[this->NumLevels];
  glGenTextures(this->NumLevels,this->HST);
  for(unsigned l=0;l<this->NumLevels;++l){
    glBindTexture(GL_TEXTURE_2D,this->HST[l]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_NEAREST);
    glTexImage2D(GL_TEXTURE_2D,0,GL_R32UI,
        this->TileCount[l*2+0]/this->TileCount[0]*RESULT_LENGTH_IN_UINT,
        this->TileCount[l*2+1]/this->TileCount[1],0,GL_RED_INTEGER,GL_UNSIGNED_INT,NULL);
    unsigned data=0;
    glClearTexImage(this->HST[l],0,GL_RED_INTEGER,GL_UNSIGNED_INT,&data);
  }
  std::cerr<<"ANO PO KONSTRUKTORU\n";
}

CSintorn::~CSintorn(){
  //TODO textures HST HDT programs draw
  delete[]this->TileDivisibility;
  delete[]this->TileSizeInClipSpace;
  delete[]this->TileSizeInPixels;
  delete[]this->TileCount;
  delete[]this->HDBOffset;
  delete this->ShadowFrusta;
  delete this->HDB;
  delete this->HSB;
  delete this->WriteDepthProgram;
  delete this->HierarchicalDepthProgram;
  delete this->SFProgram;
  delete this->RasterizeProgram;
  delete this->RasterizeTextureProgram;
  delete this->DrawHDBProgram;
  delete this->EmptyVAO;
}

void CSintorn::GenerateHierarchy(GLuint D,GLuint N,float*L){
  if(this->NumLevels<2)return;

  this->WriteDepthProgram->use();
  this->WriteDepthProgram->set("WindowSize",1,this->WindowSize);
  this->WriteDepthProgram->set("TileDivisibility",this->NumLevels,this->TileDivisibility);
  this->WriteDepthProgram->set("TileSizeInPixels",this->NumLevels,this->TileSizeInPixels);
  this->WriteDepthProgram->set("NumLevels",this->NumLevels);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_RECTANGLE,D);
  this->HDB->bindRange(GL_SHADER_STORAGE_BUFFER,0,
      this->HDBOffset[this->NumLevels-1]*sizeof(float)*2,
      this->TileCount[(this->NumLevels-1)*2+0]*this->TileCount[(this->NumLevels-1)*2+1]*sizeof(float)*2);

  glDispatchCompute(
      this->TileCount[(this->NumLevels-2)*2+0],
      this->TileCount[(this->NumLevels-2)*2+1],
      1);

  glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

  /*
     float*HData=(float*)this->HDB->Map(GL_SHADER_STORAGE_BUFFER,GL_READ_WRITE);
     for(unsigned i=64+64*64;i<64+64*64+64*64*64;++i)
     std::cerr<<HData[i*2+0]<<", "<<HData[i*2+1]<<std::endl;

     this->HDB->UnMap(GL_SHADER_STORAGE_BUFFER);
     exit(0);
  // */
  this->HDB->bindBase(GL_SHADER_STORAGE_BUFFER,0);
  this->HierarchicalDepthProgram->use();
  this->HierarchicalDepthProgram->set("WindowSize",1,this->WindowSize);

  this->HierarchicalDepthProgram->set("TileDivisibility",this->NumLevels,this->TileDivisibility);
  this->HierarchicalDepthProgram->set("TileSizeInPixels",this->NumLevels,this->TileSizeInPixels);

  for(int l=this->NumLevels-2;l>=0;--l){
    this->HierarchicalDepthProgram->set("SrcOffset",this->HDBOffset[l+1]);
    this->HierarchicalDepthProgram->set("DstOffset",this->HDBOffset[l]);
    this->HierarchicalDepthProgram->set("DstLevel",(unsigned)l);
    glDispatchCompute(this->TileCount[l*2+0],this->TileCount[l*2+1],1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
  }
}

void CSintorn::GenerateHierarchyTexture(GLuint D,GLuint N,float*L){
  if(this->NumLevels<2)return;
 
  this->WriteDepthTextureProgram->use();
  this->WriteDepthTextureProgram->set("WindowSize",1,this->WindowSize);
  glActiveTexture(GL_TEXTURE0+WRITEDEPTHTEXTURE_BINDING_DEPTH);
  glBindTexture(GL_TEXTURE_RECTANGLE,D);
  glBindImageTexture(
      WRITEDEPTHTEXTURE_BINDING_HDT,
      this->HDT[this->NumLevels-1],0,GL_FALSE,0,GL_READ_WRITE,GL_RG32F);
  glDispatchCompute(
      this->TileCount[(this->NumLevels-2)*2+0],
      this->TileCount[(this->NumLevels-2)*2+1],
      1);

  glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
  
  this->HierarchicalDepthTextureProgram->use();
  this->HierarchicalDepthTextureProgram->set("WindowSize",1,this->WindowSize);
  this->HierarchicalDepthTextureProgram->set("TileDivisibility",this->NumLevels,this->TileDivisibility);
  this->HierarchicalDepthTextureProgram->set("TileSizeInPixels",this->NumLevels,this->TileSizeInPixels);

  
  for(int l=this->NumLevels-2;l>=0;--l){
    this->HierarchicalDepthTextureProgram->set("DstLevel",(unsigned)l);
    glBindImageTexture(HIERARCHICALDEPTHTEXTURE_BINDING_HDTINPUT ,this->HDT[l+1],0,GL_FALSE,0,GL_READ_ONLY ,GL_RG32F);
    glBindImageTexture(HIERARCHICALDEPTHTEXTURE_BINDING_HDTOUTPUT,this->HDT[l  ],0,GL_FALSE,0,GL_WRITE_ONLY,GL_RG32F);
    glDispatchCompute(this->TileCount[l*2+0],this->TileCount[l*2+1],1);
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
  }
  /*
  glActiveTexture(GL_TEXTURE17);
  glBindTexture(GL_TEXTURE_2D,this->HDT[0]);
  float DD0[64*2];
  for(unsigned i=0;i<64;++i){DD0[i*2+0]=DD0[i*2+1]=10;}
  glGetTexImage(GL_TEXTURE_2D,0,GL_RG,GL_FLOAT,DD0);
  for(unsigned i=0;i<64;++i)
    std::cerr<<DD0[i*2+0]<<" "<<DD0[i*2+1]<<std::endl;

  glActiveTexture(GL_TEXTURE17);
  glBindTexture(GL_TEXTURE_2D,this->HDT[1]);
  float DD1[64*64*2];
  for(unsigned i=0;i<64*64;++i){DD1[i*2+0]=DD1[i*2+1]=10;}
  glGetTexImage(GL_TEXTURE_2D,0,GL_RG,GL_FLOAT,DD1);
  for(unsigned i=0;i<64*64;++i)
    std::cerr<<DD1[i*2+0]<<" "<<DD1[i*2+1]<<std::endl;

  glActiveTexture(GL_TEXTURE17);
  glBindTexture(GL_TEXTURE_2D,this->HDT[2]);
  float DD2[64*64*64*2];
  for(unsigned i=0;i<64*64*64;++i){DD2[i*2+0]=DD2[i*2+1]=10;}
  glGetTexImage(GL_TEXTURE_2D,0,GL_RG,GL_FLOAT,DD2);
  for(unsigned i=0;i<64*64*64;++i)
    std::cerr<<DD2[i*2+0]<<" "<<DD2[i*2+1]<<std::endl;

  exit(0);
  */
}


void CSintorn::ComputeShadowFrusta(float*LP,glm::mat4 mvp){
  //std::cerr<<"CSintorn::ComputeShadowFrusta"<<std::endl;
  this->SFProgram->use();
  this->SFProgram->set("NumTriangles",this->Adjacency->NumTriangles);
  this->SFProgram->set("ModelViewProjection",1,GL_FALSE,(const float*)glm::value_ptr(mvp));
  this->SFProgram->set("LightPosition",1,LP);
  this->SFProgram->set("TransposeInverseModelViewProjection",1,GL_FALSE,(float*)glm::value_ptr(glm::inverse(glm::transpose(mvp))));
  this->Triangles->bindBase(GL_SHADER_STORAGE_BUFFER,0);
  this->ShadowFrusta->bindBase(GL_SHADER_STORAGE_BUFFER,1);
  glDispatchCompute(this->Adjacency->NumTriangles/this->SFProgram->workGroupSize[0]+1,1,1);
  /*
     std::cout<<"LP: "<<LP[0]<<" "<<LP[1]<<" "<<LP[2]<<" "<<LP[3]<<std::endl;
     float*D=(float*)this->ShadowFrusta->Map(GL_SHADER_STORAGE_BUFFER,GL_READ_WRITE);
     for(unsigned t=0;t<2;++t){
     for(int k=0;k<VEC4_PER_SHADOWFRUSTUM;++k){
     std::cout	<<D[t*FLOATS_PER_SHADOWFRUSTUM+k*4+0]<<" "
     <<D[t*FLOATS_PER_SHADOWFRUSTUM+k*4+1]<<" "
     <<D[t*FLOATS_PER_SHADOWFRUSTUM+k*4+2]<<" "
     <<D[t*FLOATS_PER_SHADOWFRUSTUM+k*4+3]<<std::endl;
     }
     std::cout<<"##########################################"<<std::endl;
     }
     this->ShadowFrusta->UnMap(GL_SHADER_STORAGE_BUFFER);
  //exit(0);
  // */
  //glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

  glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
}

void CSintorn::Rasterize(){
  //std::cerr<<"CSintorn::Rasterize"<<std::endl;
  /*this->ClearStencilProgram->Use();
    this->ClearStencilProgram->Set("WindowSize",1,this->WindowSize);
    this->ClearStencilProgram->Set("FinalStencilMask",12);
    glBindImageTexture(12,this->FinalStencilMask,0,GL_FALSE,0,GL_READ_WRITE,GL_R32UI);
    glDispatchCompute(
    this->WindowSize[0]/this->ClearStencilProgram->WorkGroupSize[0]+1,
    this->WindowSize[1]/this->ClearStencilProgram->WorkGroupSize[1]+1,
    1);*/
  glClearTexImage(this->FinalStencilMask,0,GL_RED_INTEGER,GL_UNSIGNED_INT,NULL);
  glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

  this->HSB->clear(GL_R32UI,GL_RED,GL_UNSIGNED_INT);

  this->RasterizeProgram->use();
  this->RasterizeProgram->set("TileDivisibility",this->NumLevels,this->TileDivisibility);
  if(this->UseUniformTileSizeInClipSpace)
    this->RasterizeProgram->set("TileSizeInClipSpace",this->NumLevels,this->TileSizeInClipSpace);
  this->RasterizeProgram->set("NumberOfTriangles",this->Adjacency->NumTriangles);

  this->ShadowFrusta->bindBase(GL_SHADER_STORAGE_BUFFER,0);
  this->HDB->bindBase(GL_SHADER_STORAGE_BUFFER,1);
  this->HSB->bindBase(GL_SHADER_STORAGE_BUFFER,2);

  this->RasterizeProgram->set("FinalStencilMask",12);
  glBindImageTexture(12,this->FinalStencilMask,0,GL_FALSE,0,GL_READ_WRITE,GL_R32UI);

  glDispatchCompute(
      this->Adjacency->NumTriangles/this->ShadowFrustaPerWorkGroup+
      (this->Adjacency->NumTriangles%this->ShadowFrustaPerWorkGroup?1:0)
      ,1,1);

  glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
}

void CSintorn::RasterizeTexture(){
  glClearTexImage(this->FinalStencilMask,0,GL_RED_INTEGER,GL_UNSIGNED_INT,NULL);
  for(unsigned l=0;l<this->NumLevels;++l){
    glClearTexImage(this->HST[l],0,GL_RED_INTEGER,GL_UNSIGNED_INT,NULL);
  }
  glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

  this->RasterizeTextureProgram->use();
  this->RasterizeTextureProgram->set("TileDivisibility",this->NumLevels,this->TileDivisibility);
  if(this->UseUniformTileSizeInClipSpace)
    this->RasterizeTextureProgram->set("TileSizeInClipSpace",this->NumLevels,this->TileSizeInClipSpace);
  this->RasterizeTextureProgram->set("NumberOfTriangles",this->Adjacency->NumTriangles);

  this->ShadowFrusta->bindBase(GL_SHADER_STORAGE_BUFFER,0);

  for(unsigned l=0;l<this->NumLevels;++l)
    glBindImageTexture(RASTERIZETEXTURE_BINDING_HDT+l,this->HDT[l],0,GL_FALSE,0,GL_READ_WRITE,GL_RG32F);
  for(unsigned l=0;l<this->NumLevels;++l)
    glBindImageTexture(RASTERIZETEXTURE_BINDING_HST+l,this->HST[l],0,GL_FALSE,0,GL_READ_WRITE,GL_R32UI);

  glBindImageTexture(RASTERIZETEXTURE_BINDING_FINALSTENCILMASK,this->FinalStencilMask,0,GL_FALSE,0,GL_READ_WRITE,GL_R32UI);

  glDispatchCompute(
      this->Adjacency->NumTriangles/this->ShadowFrustaPerWorkGroup+
      (this->Adjacency->NumTriangles%this->ShadowFrustaPerWorkGroup?1:0)
      ,1,1);

  glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
}

void CSintorn::Merge(){
  //std::cerr<<"CSintorn::Merge"<<std::endl;
  this->HSB->bindBase(GL_SHADER_STORAGE_BUFFER,0);
  this->MergeProgram->use();
  this->MergeProgram->set("WindowSize",1,this->WindowSize);
  this->MergeProgram->set("TileDivisibility",this->NumLevels,this->TileDivisibility);
  this->MergeProgram->set("TileSizeInPixels",this->NumLevels,this->TileSizeInPixels);

  GLsync Sync=0;
  for(unsigned l=0;l<this->NumLevels
      /*
      -1
      // */
      ;++l){
    this->MergeProgram->set("SrcTileSizeInPixels",1,this->TileSizeInPixels+(l==0?0:l-1)*2);
    this->MergeProgram->set("DstTileSizeInPixels",1,this->TileSizeInPixels+l*2);
    this->MergeProgram->set("DstTileDivisibility",1,this->TileDivisibility+l*2);
    this->MergeProgram->set("SrcOffset",this->HDBOffset[l==0?0:l-1]+(l>0));
    this->MergeProgram->set("DstOffset",this->HDBOffset[l]+1);
    this->MergeProgram->set("SrcLevel",l);
    if(l>0){
      glClientWaitSync(Sync,0,GL_TIMEOUT_IGNORED);
      glDeleteSync(Sync);
    }
    glDispatchCompute(l==0?1:this->TileCount[(l-1)*2+0],l==0?1:this->TileCount[(l-1)*2+1],1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    if(l<this->NumLevels-1)Sync=glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE,0);
  }

  this->WriteStencilProgram->use();
  this->WriteStencilProgram->set("WindowSize",1,this->WindowSize);
  this->WriteStencilProgram->set("TileDivisibility",this->NumLevels,this->TileDivisibility);
  this->WriteStencilProgram->set("TileSizeInPixels",this->NumLevels,this->TileSizeInPixels);
  this->WriteStencilProgram->set("NumLevels",this->NumLevels
      /*
      -1
      // */
      );
  this->WriteStencilProgram->set("Offset",this->HDBOffset[this->NumLevels-1
      /*
      -1
      // */
      ]+1u);
  this->WriteStencilProgram->set("FinalStencilMask",12);
  glBindImageTexture(12,this->FinalStencilMask,0,GL_FALSE,0,GL_READ_WRITE,GL_R32UI);

  this->HSB->bindBase(GL_SHADER_STORAGE_BUFFER,0);
  glDispatchCompute(
      this->TileCount[(this->NumLevels-2)*2+0],
      this->TileCount[(this->NumLevels-2)*2+1],
      1);
  glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
  //glFinish();


  /*
     unsigned*Ptr=(unsigned*)this->HSB->Map(GL_SHADER_STORAGE_BUFFER,GL_READ_WRITE);
     for(unsigned i=0;i<1+64+64*64+64*64*64;++i)
     std::cerr<<std::hex<<Ptr[i*2+0]<<" "<<Ptr[i*2+1]<<std::endl;
     this->HSB->UnMap(GL_SHADER_STORAGE_BUFFER);
     exit(0);*/

  /*
     unsigned D[512*512];
     for(unsigned i=0;i<512*512;++i)D[i]=0;
     glBindTexture(GL_TEXTURE_2D,this->FinalStencilMask);
     glTexSubImage2D(GL_TEXTURE_2D,0,0,0,512,512,GL_RED_INTEGER,
     GL_UNSIGNED_INT,D);
     glFinish();*/
}

void CSintorn::MergeTexture(){
  this->HSB->bindBase(GL_SHADER_STORAGE_BUFFER,0);
  this->MergeTextureProgram->use();
  this->MergeTextureProgram->set("WindowSize",1,this->WindowSize);

  GLsync Sync=0;
  for(unsigned l=0;l<this->NumLevels-1;++l){
    this->MergeTextureProgram->set("DstTileSizeInPixels",1,this->TileSizeInPixels+l*2);
    this->MergeTextureProgram->set("DstTileDivisibility",1,this->TileDivisibility+l*2);
    glBindImageTexture(MERGETEXTURE_BINDING_HSTINPUT ,this->HST[l  ],0,GL_FALSE,0,GL_READ_WRITE,GL_R32UI);
    glBindImageTexture(MERGETEXTURE_BINDING_HSTOUTPUT,this->HST[l+1],0,GL_FALSE,0,GL_READ_WRITE,GL_R32UI);
    if(l>0){
      glClientWaitSync(Sync,0,GL_TIMEOUT_IGNORED);
      glDeleteSync(Sync);
    }
    glDispatchCompute(l==0?1:this->TileCount[(l-1)*2+0],l==0?1:this->TileCount[(l-1)*2+1],1);
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
    if(l<this->NumLevels
        //*
        -1
        // */
        )Sync=glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE,0);
  }

  //glFinish();
  //glMemoryBarrier(GL_ALL_BARRIER_BITS);

  this->WriteStencilTextureProgram->use();
  this->WriteStencilTextureProgram->set("WindowSize",1,this->WindowSize);
  glBindImageTexture(WRITESTENCILTEXTURE_BINDING_FINALSTENCILMASK,this->FinalStencilMask      ,0,GL_FALSE,0,GL_READ_WRITE,GL_R32UI);
  glBindImageTexture(WRITESTENCILTEXTURE_BINDING_HSTINPUT        ,this->HST[this->NumLevels-1],0,GL_FALSE,0,GL_READ_WRITE,GL_R32UI);

  glClientWaitSync(Sync,0,GL_TIMEOUT_IGNORED);
  glDeleteSync(Sync);

  glDispatchCompute(
      this->TileCount[(this->NumLevels-2)*2+0],
      this->TileCount[(this->NumLevels-2)*2+1],
      1);
  glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
  //glFinish();
}

void CSintorn::CopyHDB(){
  this->HDB->bindBase(GL_SHADER_STORAGE_BUFFER,0);
  glBindImageTexture(0,this->HDBImage,0,GL_FALSE,0,GL_READ_WRITE,GL_RG32F);
  this->CopyHDBProgram->use();
  this->CopyHDBProgram->set("HDBSize",(GLuint)(this->HDB->getSize()/sizeof(unsigned)));
  glDispatchCompute(this->HDB->getSize()/sizeof(unsigned)/(this->WavefrontSize*10)+1,1,1);
}
void CSintorn::CopyHSB(){
  this->HSB->bindBase(GL_SHADER_STORAGE_BUFFER,0);
  glBindImageTexture(0,this->HSBImage,0,GL_FALSE,0,GL_READ_WRITE,GL_RG32UI);
  this->CopyHSBProgram->use();
  this->CopyHSBProgram->set("HSBSize",(GLuint)(this->HSB->getSize()/sizeof(unsigned)));
  glDispatchCompute(this->HSB->getSize()/sizeof(unsigned)/(this->WavefrontSize*10)+1,1,1);
}

void CSintorn::DrawHDB(unsigned Level,unsigned DrawNear){
  //this->CopyHDB();
  glBindImageTexture(DRAWHDB_BINDING_HDBIMAGE,this->HDBImage,0,GL_FALSE,0,GL_READ_WRITE,GL_RG32F);

  for(unsigned l=0;l<this->NumLevels;++l)
    glBindImageTexture(DRAWHDB_BINDING_HDT+l,this->HDT[l],0,GL_FALSE,0,GL_READ_WRITE,GL_RG32F);

  this->DrawHDBProgram->use();
  this->DrawHDBProgram->set("TileDivisibility",this->NumLevels,this->TileDivisibility);
  this->DrawHDBProgram->set("TileSizeInPixels",this->NumLevels,this->TileSizeInPixels);
  this->DrawHDBProgram->set("LevelOffset",this->NumLevels,this->HDBOffset);
  this->DrawHDBProgram->set("NumLevels",this->NumLevels);
  this->DrawHDBProgram->set("Level",Level);
  this->DrawHDBProgram->set("DrawNear",DrawNear);

  glDisable(GL_DEPTH_TEST);
  glDepthMask(GL_FALSE);
  glBindFramebuffer(GL_FRAMEBUFFER,0);
  glClear(GL_COLOR_BUFFER_BIT);
  this->EmptyVAO->bind();
  this->HDB->bindBase(GL_SHADER_STORAGE_BUFFER,0);
  glDrawArrays(GL_POINTS,0,1);
  this->EmptyVAO->unbind();
  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);

}

void CSintorn::DrawHSB(unsigned Level){

  //quick workarroud
  /*unsigned*Data=new unsigned[(TESTSIZE*TESTSIZE)*2];
    unsigned*Stencil=(unsigned*)this->HSB->Map(GL_SHADER_STORAGE_BUFFER,GL_READ_WRITE);
  //std::cerr.precision(1);
  for(unsigned i=0;i<this->HSB->Size/(sizeof(unsigned)*2);++i){
  Data[i*2+0]=Stencil[i*2+0];
  Data[i*2+1]=Stencil[i*2+1];
  }*/
  //Data[0]=0xff0000ff;//Stencil[i*2+0];
  //Data[1]=0xcafbafcf;//Stencil[i*2+1];
  //Data[2]=0xffaaffaa;//Stencil[i*2+0];
  //Data[3]=0xcafbafcf;//Stencil[i*2+1];

  /*
     std::cerr<<"AHOJ\n";
     for(unsigned i=0;i<(1+64);++i)
     std::cerr<<std::hex<<Stencil[i*2+0]<<" "<<Stencil[i*2+1]<<std::endl;
     std::cerr<<"NEHOJ\n";
  // */

  /*
     this->HSB->UnMap(GL_SHADER_STORAGE_BUFFER);

     glBindTexture(GL_TEXTURE_2D,this->HSBTexture);
     glPixelStorei(GL_UNPACK_ROW_LENGTH,TESTSIZE);
     glTexSubImage2D(GL_TEXTURE_2D,0,0,0,TESTSIZE,TESTSIZE,GL_RG_INTEGER,
     GL_UNSIGNED_INT,Data);
     glPixelStorei(GL_UNPACK_ROW_LENGTH,0);
     delete[]Data;
     */
  //glMemoryBarrier(GL_ALL_BARRIER_BITS);
  //glFinish();
  //glFlush();

  //this->CopyHSB();
  glBindImageTexture(11,this->HSBImage,0,GL_FALSE,0,GL_READ_WRITE,GL_RG32UI);

  glActiveTexture(GL_TEXTURE16);
  glBindTexture(GL_TEXTURE_2D,this->HSBTexture);

  this->DrawHSBProgram->use();
  this->DrawHSBProgram->set("TileDivisibility",this->NumLevels,this->TileDivisibility);
  this->DrawHSBProgram->set("TileSizeInPixels",this->NumLevels,this->TileSizeInPixels);
  this->DrawHSBProgram->set("LevelOffset",this->NumLevels,this->HDBOffset);
  this->DrawHSBProgram->set("NumLevels",this->NumLevels);
  this->DrawHSBProgram->set("Level",Level);

  this->DrawHSBProgram->set("FinalStencilMask",12);
  glBindImageTexture(12,this->FinalStencilMask,0,GL_FALSE,0,GL_READ_WRITE,GL_R32UI);
  glBindImageTexture(10,this->HST[2],0,GL_FALSE,0,GL_READ_WRITE,GL_R32UI);


  glDisable(GL_DEPTH_TEST);
  glDepthMask(GL_FALSE);
  glBindFramebuffer(GL_FRAMEBUFFER,0);
  glClear(GL_COLOR_BUFFER_BIT);
  this->EmptyVAO->bind();
  this->HSB->bindBase(GL_SHADER_STORAGE_BUFFER,0);
  glDrawArrays(GL_POINTS,0,1);
  this->EmptyVAO->unbind();
  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);

}


#endif
