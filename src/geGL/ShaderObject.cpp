#include<geGL/ShaderObject.h>

#include<geCore/Text.h>
#include<iostream>
#include<stdarg.h>
#include<string>
#include<cstring>
#include<fstream>
#include<sstream>

using namespace ge::gl;

GLenum ge::gl::file2ShaderType(std::string fileName){
  switch(fileTypeSwitch(fileName,12,//number of extensions
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

int ge::gl::fileTypeSwitch(std::string fileName,unsigned numType,...){
  va_list args;//argumenty
  va_start(args,numType);//zacatek argumentu
  for(unsigned i=0;i<numType;++i){
    char* ext=(char*)va_arg(args,char*);
    if(fileName.length()-fileName.rfind(ext)==std::strlen(ext)){//nalezl se
      va_end(args);//konec sekvence argumentu
      return i;//vraceni cisla
    }
  }
  va_end(args);//konec sekcence
  return-1;//ani jeden
}

/*std::string ShaderObject::_readShader(std::string const& file){
  std::ifstream f(file.c_str(), std::ios_base::in | std::ios_base::binary);
  if(!f.good()){
    std::cerr<<"ERROR: cannot open: "<<file<<std::endl;
    return "";
  }
  f.seekg(0,std::ios::end);
  std::size_t size=f.tellg();
  f.seekg(0,std::ios::beg);
  char*buffer=new char[size+1];
  f.read(buffer,size);
  buffer[size]='\0';
  std::string result(buffer);
  delete[]buffer;
  f.close();
  return result;
}*/

std::string ShaderObject::_appendAfterVersion(
    std::string source,
    std::string defs){
   if(defs=="")return source;
  auto versionPosition=source.find("#version");
  auto lineEndPosition=source.find("\n",versionPosition);
  source.insert(lineEndPosition+1,defs);
  return source;
}

std::string ShaderObject::_setVersion(
    std::string source ,
    unsigned    version,
    std::string profile){
  if(version==0)return source;
  std::basic_string<char>::size_type Position=0;
  while((Position=source.find("#version",Position))!=std::string::npos){
    auto LineEndPosition=source.find("\n",Position);
    source.erase(Position,LineEndPosition-Position);
  }
  std::stringstream result;
  result<<"#version "<<version<<" "<<profile<<"\n";
  result<<source;
  return result.str();
}

ShaderObject::ShaderObject(GLenum type,std::string source):Shader(){
  this->create(type,source);
}

ShaderObject::ShaderObject(std::string file){
  std::string source = ge::core::loadTextFile(file);//this->_readShader(file);
  GLenum type = file2ShaderType(file);
  this->create(type,source);
  if(!this->getCompileStatus())
    std::cerr<<"ERROR: "<<this->getInfoLog()<<std::endl;
}

ShaderObject::ShaderObject(
    std::string file,
    GLenum      type){
  std::string source = ge::core::loadTextFile(file);//this->_readShader(file);
  this->create(type,source);
  if(!this->getCompileStatus())
    std::cerr<<"ERROR: "<<this->getInfoLog()<<std::endl;
}

ShaderObject::ShaderObject(
    std::string file,
    std::string defs){
  std::string source = ge::core::loadTextFile(file);//this->_readShader(file);
  source = this->_appendAfterVersion(source,defs);
  GLenum type = file2ShaderType(file);
  this->create(type,source);
  if(!this->getCompileStatus())
    std::cerr<<"ERROR: "<<this->getInfoLog()<<std::endl;
}

ShaderObject::ShaderObject(
    std::string file   ,
    std::string defs   ,
    unsigned    version,
    std::string profile){
  std::string source = ge::core::loadTextFile(file);//this->_readShader(file);
  source = this->_appendAfterVersion(source,defs);
  source = this->_setVersion(source,version,profile);
  GLenum type = file2ShaderType(file);
  this->create(type,source);
  if(!this->getCompileStatus())
    std::cerr<<"ERROR: "<<this->getInfoLog()<<std::endl;
}

ShaderObject::ShaderObject(
    std::string file   ,
    unsigned    version,
    std::string profile){
  std::string source = ge::core::loadTextFile(file);//this->_readShader(file);
  source = this->_setVersion(source,version,profile);
  GLenum type = file2ShaderType(file);
  this->create(type,source);
  if(!this->getCompileStatus())
    std::cerr<<"ERROR: "<<this->getInfoLog()<<std::endl;
}

ShaderObject::~ShaderObject(){
}

void ShaderObject::setVersion(unsigned version,std::string profile){
  std::string source=this->getSource();
  source = this->_setVersion(source,version,profile);
  this->compile(source);
  if(!this->getCompileStatus())
    std::cerr<<"ERROR: "<<this->getInfoLog()<<std::endl;
}

void ShaderObject::appendAfterVersion(std::string defs){
  std::string source=this->getSource();
  source = this->_appendAfterVersion(source,defs);
  this->compile(source);
  if(!this->getCompileStatus())
    std::cerr<<"ERROR: "<<this->getInfoLog()<<std::endl;
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

std::string ShaderObject::include(std::string file){
  return ge::core::loadTextFile(file);//ShaderObject::_readShader(file);
}


