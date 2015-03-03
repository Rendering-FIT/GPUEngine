#include<geGL/ShaderObject.h>

#include<iostream>
#include<stdarg.h>
#include<string>
#include<cstring>
#include<fstream>
#include<sstream>

using namespace ge::gl;

int ShaderObject::fileTypeSwitch(std::string fileName,unsigned numType,...){
  va_list args;//argumenty
  va_start(args,numType);//zacatek argumentu
  for(size_t i=0;i<numType;++i){
    char* ext=(char*)va_arg(args,char*);
    if(fileName.length()-fileName.rfind(ext)==std::strlen(ext)){//nalezl se
      va_end(args);//konec sekvence argumentu
      return i;//vraceni cisla
    }
  }
  va_end(args);//konec sekcence
  return-1;//ani jeden
}

unsigned char*ShaderObject::readWholeFile(int*len,std::string file){
  std::ifstream f(file.data(),std::ifstream::binary);//otevreme soubor
  if(!f.good())throw std::string("file "+file+" is corrupt");
  f.seekg(0,std::ios::end);//jdeme na konec
  *len=f.tellg();//tak tu mame delku (pozice hlavy)
  f.seekg(0,std::ios::beg);//navrat na zacatek
  unsigned char*data=new unsigned char[*len];//alokace dat
  f.read((char*)data,*len);//precteni souboru
  f.close();//zavreme soubor
  return data;
}

GLenum ShaderObject::file2ShaderType(std::string file){
  switch(ShaderObject::fileTypeSwitch(file,12,//number of extensions
        "vert","vp",  //vertex     shader extension
        "frag","fp",  //fragment   shader extension
        "geom","gp",  //geometry   shader extension
        "cont","cp",  //control    shader extension
        "eval","ep",  //evaluation shader extension
        "comp","mp")){//compute    shader extension
    case 0:
    case 1:return GL_VERTEX_SHADER;//vertex shader
    case 2:
    case 3:return GL_FRAGMENT_SHADER;//fragment shader
    case 4:
    case 5:return GL_GEOMETRY_SHADER;//geometry shader
    case 6:
    case 7:return GL_TESS_CONTROL_SHADER;//control shader
    case 8:
    case 9:return GL_TESS_EVALUATION_SHADER;//evaluation shader
    case 10:
    case 11:return GL_COMPUTE_SHADER;//compute shader
    default:return (GLenum)0;//unknown
  }
}
std::string ShaderObject::define(std::string name){
  return"#define "+name+"\n";
}
std::string ShaderObject::define(std::string name,unsigned value){
  std::stringstream result;
  result<<"#define "<<name<<" "<<value<<"u\n";
  return result.str();
}
std::string ShaderObject::define(std::string name,unsigned value0,unsigned value1){
  std::stringstream result;
  result<<"#define "<<name<<" uvec2("<<value0<<"u,"<<value1<<"u)\n";
  return result.str();
}
std::string ShaderObject::define(std::string name,unsigned value0,unsigned value1,unsigned value2){
  std::stringstream result;
  result<<"#define "<<name<<" uvec3("<<value0<<"u,"<<value1<<"u,"<<value2<<"u)\n";
  return result.str();
}
std::string ShaderObject::define(std::string name,unsigned value0,unsigned value1,unsigned value2,unsigned value3){
  std::stringstream result;
  result<<"#define "<<name<<" uvec3("<<value0<<"u,"<<value1<<"u,"<<value2<<"u,"<<value3<<"u)\n";
  return result.str();
}
std::string ShaderObject::define(std::string Name,unsigned vectorSize,unsigned*values){
  if(vectorSize==1)return define(Name,values[0]);
  std::stringstream result;
  result<<"#define "<<Name<<" uvec"<<vectorSize<<"(";
  for(unsigned i=0;i<vectorSize;++i){
    result<<values[i]<<"u";
    if(i==vectorSize-1)result<<")\n";
    else result<<",";
  }
  return result.str();
}
std::string ShaderObject::define(std::string Name,int Value){
  std::stringstream result;
  result<<"#define "<<Name<<" "<<Value<<"\n";
  return result.str();
}
std::string ShaderObject::define(std::string Name,int value0,int value1){
  std::stringstream result;
  result<<"#define "<<Name<<" ivec2("<<value0<<","<<value1<<")\n";
  return result.str();
}
std::string ShaderObject::define(std::string Name,int value0,int value1,int value2){
  std::stringstream result;
  result<<"#define "<<Name<<" ivec3("<<value0<<","<<value1<<","<<value2<<")\n";
  return result.str();
}
std::string ShaderObject::define(std::string Name,int value0,int value1,int value2,int value3){
  std::stringstream result;
  result<<"#define "<<Name<<" ivec3("<<value0<<","<<value1<<","<<value2<<","<<value3<<")\n";
  return result.str();
}
std::string ShaderObject::define(std::string Name,unsigned vectorSize,int*values){
  if(vectorSize==1)return define(Name,values[0]);
  std::stringstream result;
  result<<"#define "<<Name<<" ivec"<<vectorSize<<"(";
  for(unsigned i=0;i<vectorSize;++i){
    result<<values[i];
    if(i==vectorSize-1)result<<")\n";
    else result<<",";
  }
  return result.str();
}
std::string ShaderObject::define(std::string Name,float Value){
  std::stringstream result;
  result<<"#define "<<Name<<" "<<Value<<"\n";
  return result.str();
}
std::string ShaderObject::define(std::string Name,float value0,float value1){
  std::stringstream result;
  result<<"#define "<<Name<<" vec2("<<value0<<","<<value1<<")\n";
  return result.str();
}
std::string ShaderObject::define(std::string Name,float value0,float value1,float value2){
  std::stringstream result;
  result<<"#define "<<Name<<" vec3("<<value0<<","<<value1<<","<<value2<<")\n";
  return result.str();
}
std::string ShaderObject::define(std::string Name,float value0,float value1,float value2,float value3){
  std::stringstream result;
  result<<"#define "<<Name<<" vec3("<<value0<<","<<value1<<","<<value2<<","<<value3<<")\n";
  return result.str();
}
std::string ShaderObject::define(std::string Name,unsigned vectorSize,float*values){
  if(vectorSize==1)return define(Name,values[0]);
  std::stringstream result;
  result<<"#define "<<Name<<" vec"<<vectorSize<<"(";
  for(unsigned i=0;i<vectorSize;++i){
    result<<values[i];
    if(i==vectorSize-1)result<<")\n";
    else result<<",";
  }
  return result.str();
}
std::string ShaderObject::define(std::string Name,std::string Value){
  return"#define "+Name+" "+Value+"\n";
}

//throw std::string("Wrong file extension for shader");
void ShaderObject::_loadFile(std::string File){
  int length;//lenght of file in bytes
  char*Buffer=(char*)ShaderObject::readWholeFile(&length,File);//read whole file
  this->_text=std::string((char*)Buffer,length);//convert to std::string
  delete[]Buffer;//free buffer data
}

ShaderObject::ShaderObject(std::string File){
  this->_type=file2ShaderType(File);
  this->_loadFile(File);
  this->_compileShader();
}

ShaderObject::ShaderObject(GLenum type,std::string text){
  this->_text = text;//text
  this->_type = type;//type
  this->_compileShader();
}

ShaderObject::ShaderObject(std::string File,std::string defs){
  this->_type=file2ShaderType(File);
  this->_loadFile(File);
  this->appendAfterVersion(defs);
  this->_compileShader();
}

ShaderObject::ShaderObject(std::string File,std::string defs,unsigned version,std::string Profile){
  this->_type=file2ShaderType(File);
  this->_loadFile(File);
  this->appendAfterVersion(defs);
  this->setVersion(version,Profile);
  this->_compileShader();
}

ShaderObject::ShaderObject(std::string File,unsigned version,std::string Profile){
  this->_type=file2ShaderType(File);
  this->_loadFile(File);
  this->setVersion(version,Profile);
  this->_compileShader();
}

ShaderObject::~ShaderObject(){
  glDeleteShader(this->_id);//deletes a shader
}

void ShaderObject::_compileShader(){
  this->_id=glCreateShader(this->_type);//get shader id
  if(!this->_id)//something is wrong
    throw std::string("glCreateShader failed");//+GetGLError());//error message
  GLchar*ptr[1]={(GLchar*)this->_text.data()};//retype
  glShaderSource(this->_id,1,(const GLchar**)ptr,NULL);//load shader text
  glCompileShader(this->_id);//compile shader
  std::string Log=this->_getShaderInfo(this->_id);
  if(!Log.empty())std::cerr<<Log<<std::endl;//print out log
  GLint Status;//status of compilation
  glGetShaderiv(this->_id,GL_COMPILE_STATUS,&Status);//get status
  if((GLboolean)Status==GL_FALSE)//something is wrong
    throw std::string("Shader compilation failed");//+GetGLError());//error message
}

std::string ShaderObject::_getShaderInfo(GLuint ID){
  int Len=0;//length of message
  glGetShaderiv(ID,GL_INFO_LOG_LENGTH,&Len);//gets length of message
  if(Len<=1)return"";
  std::string Info(Len,' ');//create string of Len length
  glGetShaderInfoLog(ID,Len,NULL,&Info[0]);//get message
  return Info;//return message
}

void ShaderObject::setVersion(unsigned version,std::string profile){
  if(version==0)return;
  int Position=0;
  while((Position=this->_text.find("#version",Position))>=0){
    int LineEndPosition=this->_text.find("\n",Position);
    this->_text.erase(Position,LineEndPosition-Position);
  }

  std::stringstream result;
  result<<"#version "<<version<<" "<<profile<<"\n";
  result<<this->_text;
  this->_text=result.str();
}

void ShaderObject::appendAfterVersion(std::string defs){
  if(defs=="")return;
  int versionPosition=0;
  int LineEndPosition=0;
  versionPosition=this->_text.find("#version");
  LineEndPosition=this->_text.find("\n",versionPosition);
  this->_text.insert(LineEndPosition+1,defs);
}

void ShaderObject::recompile(){
  glDeleteShader(this->_id);
  this->_compileShader();
}

GLenum ShaderObject::getType(){
  return this->_type;
}

std::string ShaderObject::getText(){
  return this->_text;
}
