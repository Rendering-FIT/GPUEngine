#include<geGL/ProgramObject.h>
#include<string>
#include<sstream>
#include<tuple>
#include<array>

using namespace ge::gl;
using namespace ge::gl::opengl;

/**
 * @brief Function converts complex type (GL_FLOAT_VEC3 to GL_FLOAT)
 *
 * @param Type OpenGL Type GL_FLOAT_VEC2, ...
 *
 * @return GL_FLOAT, ...
 */
GLenum ge::gl::complexType2SimpleType(GLenum type){
  switch(type){
    case GL_FLOAT            :return GL_FLOAT       ;
    case GL_FLOAT_VEC2       :return GL_FLOAT       ;
    case GL_FLOAT_VEC3       :return GL_FLOAT       ;
    case GL_FLOAT_VEC4       :return GL_FLOAT       ;
    case GL_DOUBLE           :return GL_DOUBLE      ;
    case GL_DOUBLE_VEC2      :return GL_DOUBLE      ;
    case GL_DOUBLE_VEC3      :return GL_DOUBLE      ;
    case GL_DOUBLE_VEC4      :return GL_DOUBLE      ;
    case GL_INT              :return GL_INT         ;
    case GL_INT_VEC2         :return GL_INT         ;
    case GL_INT_VEC3         :return GL_INT         ;
    case GL_INT_VEC4         :return GL_INT         ;
    case GL_UNSIGNED_INT     :return GL_UNSIGNED_INT;
    case GL_UNSIGNED_INT_VEC2:return GL_UNSIGNED_INT;
    case GL_UNSIGNED_INT_VEC3:return GL_UNSIGNED_INT;
    case GL_UNSIGNED_INT_VEC4:return GL_UNSIGNED_INT;
    case GL_BOOL             :return GL_BOOL        ;
    case GL_BOOL_VEC2        :return GL_BOOL        ;
    case GL_BOOL_VEC3        :return GL_BOOL        ;
    case GL_BOOL_VEC4        :return GL_BOOL        ;
    default                  :return GL_FLOAT       ;//GL_FALSE glbinding...
  }
}

template<size_t TO,size_t FROM = 0>
size_t translateComplexShaderType(size_t what){
  using Element = std::tuple<GLenum,GLenum,GLint>;
  const std::array<Element,20>elements = {
    Element(GL_FLOAT            ,GL_FLOAT       ,1),
    Element(GL_FLOAT_VEC2       ,GL_FLOAT       ,2),
    Element(GL_FLOAT_VEC3       ,GL_FLOAT       ,3),
    Element(GL_FLOAT_VEC4       ,GL_FLOAT       ,4),
    Element(GL_DOUBLE           ,GL_DOUBLE      ,1),
    Element(GL_DOUBLE_VEC2      ,GL_DOUBLE      ,2),
    Element(GL_DOUBLE_VEC3      ,GL_DOUBLE      ,3),
    Element(GL_DOUBLE_VEC4      ,GL_DOUBLE      ,4),
    Element(GL_INT              ,GL_INT         ,1),
    Element(GL_INT_VEC2         ,GL_INT         ,2),
    Element(GL_INT_VEC3         ,GL_INT         ,3),
    Element(GL_INT_VEC4         ,GL_INT         ,4),
    Element(GL_UNSIGNED_INT     ,GL_UNSIGNED_INT,1),
    Element(GL_UNSIGNED_INT_VEC2,GL_UNSIGNED_INT,2),
    Element(GL_UNSIGNED_INT_VEC3,GL_UNSIGNED_INT,3),
    Element(GL_UNSIGNED_INT_VEC4,GL_UNSIGNED_INT,4),
    Element(GL_BOOL             ,GL_BOOL        ,1),
    Element(GL_BOOL_VEC2        ,GL_BOOL        ,2),
    Element(GL_BOOL_VEC3        ,GL_BOOL        ,3),
    Element(GL_BOOL_VEC4        ,GL_BOOL        ,4),
  };
  for(auto const&x:elements)
    if(std::get<FROM>(x)==what)return std::get<TO>(x);
  return -1;
}

/**
 * @brief Function converts complex type (GL_FLOAT_VEC3 to 3)
 *
 * @param Type OpenGL Type GL_FLOAT_VEC2, ...
 *
 * @return 2, ...
 */
GLint ge::gl::complexType2Size(GLenum type){
  switch(type){
    case GL_FLOAT            :return 1;
    case GL_FLOAT_VEC2       :return 2;
    case GL_FLOAT_VEC3       :return 3;
    case GL_FLOAT_VEC4       :return 4;
    case GL_DOUBLE           :return 1;
    case GL_DOUBLE_VEC2      :return 2;
    case GL_DOUBLE_VEC3      :return 3;
    case GL_DOUBLE_VEC4      :return 4;
    case GL_INT              :return 1;
    case GL_INT_VEC2         :return 2;
    case GL_INT_VEC3         :return 3;
    case GL_INT_VEC4         :return 4;
    case GL_UNSIGNED_INT     :return 1;
    case GL_UNSIGNED_INT_VEC2:return 2;
    case GL_UNSIGNED_INT_VEC3:return 3;
    case GL_UNSIGNED_INT_VEC4:return 4;
    case GL_BOOL             :return 1;
    case GL_BOOL_VEC2        :return 2;
    case GL_BOOL_VEC3        :return 3;
    case GL_BOOL_VEC4        :return 4;
    default                  :return 0;
  }
}

ProgramObject::ProgramObject(std::vector<std::string>const&data,unsigned version,std::string profile){
  this->_sortAndCompileShaders(data,version,profile);
}

ProgramObject::ProgramObject(
    FunctionTablePointer const&table  ,
    std::vector<std::string>            const&data   ,
    unsigned                                  version,
    std::string                               profile):OpenGLObject(table){
  this->_sortAndCompileShaders(data,version,profile);
}

std::string ProgramObject::uniformsToStr(){
  std::stringstream ss;
  for(auto x:this->_uniformList)
    ss<<x.first<<" ";
  return ss.str();
}

void ProgramObject::setSeparable    (){
  glProgramParameteri(this->_id,GL_PROGRAM_SEPARABLE,GL_TRUE);
  glLinkProgram(this->_id);
}
void ProgramObject::resetSeparable  (){
  glProgramParameteri(this->_id,GL_PROGRAM_SEPARABLE,GL_FALSE);
  glLinkProgram(this->_id);
}
void ProgramObject::setRetrievable  (){
  glProgramParameteri(this->_id,GL_PROGRAM_BINARY_RETRIEVABLE_HINT,GL_TRUE);
  glLinkProgram(this->_id);
}
void ProgramObject::resetRetrievable(){
  glProgramParameteri(this->_id,GL_PROGRAM_BINARY_RETRIEVABLE_HINT,GL_FALSE);
  glLinkProgram(this->_id);
}

void ProgramObject::_createShaderProgram_Prologue(){
  /*
     if(!OpenGL320){
     std::cerr<<std::string("OpenGL 3.2 not available")<<std::endl;
     return;
     }
     */
  this->_id=glCreateProgram();//creates a shader program
  if(!this->_id){//something is wrong
    std::cerr<< std::string("glCreateProgram failed")<<std::endl;
    return;
  }
}

void ProgramObject::_createShaderProgram_Epilogue(){
  glLinkProgram(this->_id);//link shader program
  std::cerr<<this->_getProgramInfo(this->_id);
  GLint Status;//status of linking
  glGetProgramiv(this->_id,GL_LINK_STATUS,&Status);//status
  if(static_cast<GLboolean>(Status)==GL_FALSE){//something is wrong
    std::cerr << std::string("program linking failed")<<std::endl;
    return;
  }
  this->_getParameterList();//get list of shader program parameter

  /*
     if(OpenGL400)
     this->_getSubroutineUniformList();

     if(OpenGL400)
     this->_getBufferList();
     */

  bool hasComputeShader=false;
  for(auto x:this->_shaders)
    if(x->getType()==GL_COMPUTE_SHADER){
      hasComputeShader=true;
      break;
    }
  if(hasComputeShader)
    glGetProgramiv(this->_id,GL_COMPUTE_WORK_GROUP_SIZE,
        this->workGroupSize);
}

typedef void (*GETACTIVEFCE  )(GLuint,GLuint,GLsizei,GLsizei*,GLint*,GLenum*,GLchar*);
typedef GLint(*GETLOCATIONFCE)(GLuint,const GLchar*);
void ProgramObject::_getParameterList(){
  const decltype(&FunctionProvider::glGetActiveAttrib) getActive [] = {
    &FunctionProvider::glGetActiveAttrib,
    &FunctionProvider::glGetActiveUniform,
  };
  const decltype(&FunctionProvider::glGetAttribLocation) getLocation [] = {
    &FunctionProvider::glGetAttribLocation,
    &FunctionProvider::glGetUniformLocation,
  };
  const GLenum Active[]={
    GL_ACTIVE_ATTRIBUTES,
    GL_ACTIVE_UNIFORMS  };
  const GLenum MaxLenght[]={
    GL_ACTIVE_ATTRIBUTE_MAX_LENGTH,
    GL_ACTIVE_UNIFORM_MAX_LENGTH  };
  for(unsigned t=0;t<sizeof(Active)/sizeof(const GLenum);++t){//loop over set of types {attribute,uniform}
    GLuint num;//number of active parameter
    glGetProgramiv(this->_id,Active[t],reinterpret_cast<GLint*>(&num));//number
    if(!num)continue;//there are no active parameters
    GLsizei bufLen;//length of the longest attribute name
    glGetProgramiv(this->_id,MaxLenght[t],&bufLen);
    GLchar*Buffer=new GLchar[bufLen+1];//alocate buffer
    for(GLuint i=0;i<num;++i){//loop over active parameter
      GLenum      type;//type of parameter
      GLint       size;//size of parameter
      std::string name;//name of parameter
      GLint       location;//location of parameter
      GLsizei     length;
      (this->*getActive[t])(this->_id,i,bufLen,&length,&size,&type,Buffer);
      name = chopIndexingInPropertyName(std::string(Buffer));
      location = (this->*getLocation[t])(this->_id,name.c_str());//location
      if(ge::gl::SamplerParam::isSampler(type)){
        GLint binding;
        glGetUniformiv(this->getId(),location,&binding);
        this->_samplerList[name]=std::make_shared<SamplerParam>(
            this->getFunctionTable(),
            name,location,type,binding);
      }
      auto Param = std::make_shared<ProgramObjectParameter>(
          this->getFunctionTable(),
          location,type,name,size);//param
      if(Active[t]==GL_ACTIVE_ATTRIBUTES)this->_attributeList[name]=Param;
      else                               this->_uniformList  [name]=Param;
    }
    delete[]Buffer;//free buffer
  }
}
void ProgramObject::_getSubroutineUniformList(){
  const GLenum ShaderType[]={
    GL_VERTEX_SHADER         ,
    GL_TESS_CONTROL_SHADER   ,
    GL_TESS_EVALUATION_SHADER,
    GL_GEOMETRY_SHADER       ,
    GL_FRAGMENT_SHADER       ,
    GL_COMPUTE_SHADER
  };
  for(unsigned i=0;i<sizeof(ShaderType)/sizeof(const GLenum);++i){//loop over shader types
    GLuint NumSubroutines;//number of subroutines in this shader
    GLsizei MaxSubroutineNameSize;//max legth of name of subroutine
    glGetProgramStageiv(this->_id,ShaderType[i],//get number of sub.
        GL_ACTIVE_SUBROUTINES,reinterpret_cast<GLint*>(&NumSubroutines));
    if(NumSubroutines>0){//there are subroutines
      glGetProgramStageiv(this->_id,ShaderType[i],//max lenght
          GL_ACTIVE_SUBROUTINE_MAX_LENGTH,&MaxSubroutineNameSize);
      char*BufferName=new char[MaxSubroutineNameSize];//allocate buffer

      for(GLuint sub=0;sub<NumSubroutines;++sub){//loop over subroutines
        glGetActiveSubroutineName(this->_id,ShaderType[i],sub,
            MaxSubroutineNameSize,NULL,BufferName);//obtain name of subroutine
        GLuint Location=glGetSubroutineIndex(this->_id,
            ShaderType[i],BufferName);//obtain index of subroutine
        std::string Name=std::string(BufferName);//convert buffer to string
        this->_subroutines[i]->addSubroutine(Name,Location);
      }
      delete[]BufferName;//free buffer
    }

    GLuint NumSubroutineUniforms;//number of subroutine uniforms
    GLint MaxSubroutineUniformNameSize;//max legth of subroutine uniforms

    glGetProgramStageiv(this->_id,ShaderType[i],//get number
        GL_ACTIVE_SUBROUTINE_UNIFORMS,reinterpret_cast<GLint*>(&NumSubroutineUniforms));
    if(NumSubroutineUniforms){//there are subroutine uniforms
      unsigned ActIndex=0;
      glGetProgramStageiv(this->_id,ShaderType[i],//get lenght
          GL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH,&MaxSubroutineUniformNameSize);
      char*BufferName=new char[MaxSubroutineNameSize];//allocate buffer
      for(GLuint sub=0;sub<NumSubroutineUniforms;++sub){
        GLint Size;
        glGetActiveSubroutineUniformiv(this->_id,ShaderType[i],sub,
            GL_UNIFORM_SIZE,&Size);
        GLsizei Length;
        glGetActiveSubroutineUniformName(this->_id,ShaderType[i],sub,
            MaxSubroutineUniformNameSize,&Length,BufferName);//obtain name
        //if(Size>1)BufferName[Length-3]='\0';
        //std::string Name=std::string(BufferName);//convert buffer to string
        std::string Name = chopIndexingInPropertyName(std::string(BufferName));
        GLint NumCompatible;
        glGetActiveSubroutineUniformiv(this->_id,ShaderType[i],sub,
            GL_NUM_COMPATIBLE_SUBROUTINES,&NumCompatible);
        GLint Location;
        Location=glGetSubroutineUniformLocation(this->_id,
            ShaderType[i],Name.c_str());
        ShaderObjectSubroutineUniform ShaderSubroutineUniform=
          ShaderObjectSubroutineUniform(Location,Size,NumCompatible,Name,ActIndex);
        ActIndex+=Size;
        this->_subroutines[i]->addUniform(Name,ShaderSubroutineUniform);
      }
      delete[]BufferName;//free buffer
      this->_subroutines[i]->allocInidices(ActIndex);
    }
  }
}

void ProgramObject::_getBufferList(){
  GLint nofBuffers=0;
  glGetProgramInterfaceiv(
      this->getId(),
      GL_SHADER_STORAGE_BLOCK,
      GL_ACTIVE_RESOURCES,
      &nofBuffers);
  for(GLint i=0;i<nofBuffers;++i){
    auto params = std::make_shared<ProgramObjectBufferParams>(
        this->getFunctionTable(),
        this->getId(),i);
    this->_bufferList[params->getName()]=params;
    this->_bufferNames.push_back(params->getName());
  }
}

/**
 * @brief Sets subroutine with name SubroutineName as active in Uniform
 *
 * @param shaderType type of shader
 * @param uniform uniform name
 * @param subroutineName subroutine name
 */
void ProgramObject::setSubroutine(
    GLenum ShaderType,
    std::string Uniform,
    unsigned OffSet,
    std::string SubroutineName){
  int WH=0;
  switch(ShaderType){
    case GL_VERTEX_SHADER         :WH=0;break;
    case GL_TESS_CONTROL_SHADER   :WH=1;break;
    case GL_TESS_EVALUATION_SHADER:WH=2;break;
    case GL_GEOMETRY_SHADER       :WH=3;break;
    case GL_FRAGMENT_SHADER       :WH=4;break;
    case GL_COMPUTE_SHADER        :WH=5;break;
  }
  this->_subroutines[WH]->set(ShaderType,Uniform,OffSet,SubroutineName);
}


std::string ProgramObject::_getProgramInfo(GLuint ID){
  int Len=0;//length of message
  glGetProgramiv(ID,GL_INFO_LOG_LENGTH,&Len);//gets length of message
  if(Len<=1)return"";
  std::string Info(Len,' ');//create string of Len length
  glGetProgramInfoLog(ID,Len,NULL,&Info[0]);//get message
  return Info;//return message
}

void ProgramObject::_compileShaders(
    std::vector<std::string>shaders,
    std::vector<std::string>defs,
    unsigned version,
    std::string profile){

  this->_createShaderProgram_Prologue();//create shader program
  try{
    for(unsigned s=0;s<shaders.size();++s)
      this->attachShader(std::make_shared<ShaderObject>(shaders[s],defs[s],version,profile));
  }catch(std::string&e){
    this->_shaders.clear();
    std::cerr<<e<<std::endl;
    return;
  }
  this->_createShaderProgram_Epilogue();//gets attributes and uniforms
}

void ProgramObject::_sortAndCompileShaders(
    std::vector<std::string>strings,
    unsigned version,
    std::string profile){
  unsigned NumShaders=0;
  for(unsigned s=0;s<strings.size();++s)//loop over strings
    if(file2ShaderType(strings[s])!=0)//it is not definition
      NumShaders++;//increment shader count
  std::vector<std::string>shaderSources;
  std::vector<std::string>defs;
  for(unsigned s=0;s<NumShaders;++s)defs.push_back("");//initialize definitions
  int ActShader=-1;
  for(unsigned s=0;s<strings.size();++s){//loop over strings
    if(file2ShaderType(strings[s])!=0){//it is shaders
      ActShader++;//increment shader index
      shaderSources.push_back(strings[s]);//insert shader
    }else{//it is definitions
      if(ActShader<0){//there was no shader
        std::cerr<<std::string("bad arguments")<<std::endl;//throw error
        return;
      }else defs[ActShader]+=strings[s];//set definitinos
    }
  }
  this->_compileShaders(shaderSources,defs,version,profile);//compile
}

/**
 * @brief Sets version of every shader in shader program
 *
 * @param version version
 * @param profile profile
 */
void ProgramObject::setVersion(unsigned version,std::string profile){
  for(auto x:this->_shaders)
    x->setVersion(version,profile);
}

/**
 * @brief Sets version in specific shader of shader program 
 *
 * @param type shader type
 * @param version version
 * @param profile profile
 */
void ProgramObject::setVersion(GLenum type,unsigned version,std::string profile){
  for(auto x:this->_shaders)
    if(x->getType()==type)
      x->setVersion(version,profile);
}

/**
 * @brief Appends definitions after version in every shader of program
 *
 * @param defs definitions
 */
void ProgramObject::appendAfterVersion(std::string defs){
  for(auto x:this->_shaders)
    x->appendAfterVersion(defs);
}

/**
 * @brief Appends definitions after version in specific shader
 *
 * @param type type of shader
 * @param defs definitions
 */
void ProgramObject::appendAfterVersion(GLenum type,std::string defs){
  for(auto x:this->_shaders)
    if(x->getType()==type)
      x->appendAfterVersion(defs);
}

void ProgramObject::_deleteProgram(){
  for(auto x:this->_shaders)
    this->detachShader(x);
  glDeleteProgram(this->_id);//deletes shader program
  this->_shaders      .clear();
  this->_attributeList.clear();
  this->_uniformList  .clear();
  this->_bufferList   .clear();
  this->_bufferNames  .clear();
  this->_samplerList  .clear();
}

/**
 * @brief Relink program
 */

/**
 * @brief Destructor
 */
ProgramObject::~ProgramObject(){
  this->_deleteProgram();
}

/**
 * @brief Attach shader to program
 *
 * @param shader shader
 */
void ProgramObject::attachShader(std::shared_ptr<ShaderObject>const&shader){
  this->_shaders.insert(shader);
  glAttachShader(this->getId(),shader->getId());
}

/**
 * @brief Detach shader from program
 *
 * @param shader shader
 */
void ProgramObject::detachShader(std::shared_ptr<ShaderObject>const&shader){
  glDetachShader(this->getId(),shader->getId());
}

void err(std::string error){
  std::cerr<<"ERROR: "<<error<<std::endl;
}

/**
 * @brief Gets uniform meta data
 *
 * @param name uniform name
 *
 * @return meta data (location,type,name,size)
 */
ProgramObjectParameter const&ProgramObject::getUniform  (std::string name,bool printErrors)const{
  auto i=this->_uniformList.find(name);
  if(i==this->_uniformList.end()){
    if(printErrors)err("ProgramObject::getUniform("+name+") - there is no such uniform");
    //TODO there should be zeroth element n this->_uniformList that represents
    //non existing uniform in order to prevent multi threading to fail
    static const ProgramObjectParameter er(this->getFunctionTable());
    return er;
  }
  return *i->second;
}

/**
 * @brief Gets attribute meta data
 *
 * @param name attribute name
 *
 * @return meta data (location,type,name,size)
 */
ProgramObjectParameter const&ProgramObject::getAttribute(std::string name,bool printErrors)const{
  auto i=this->_attributeList.find(name);
  if(i==this->_attributeList.end()){
    if(printErrors)err("ProgramObject::getAttribute("+name+") - there is no such attribute");
    //TODO there should be zeroth element n this->_attributeList that represents
    //non existing uniform in order to prevent multi threading to fail
    static const ProgramObjectParameter er(this->getFunctionTable());
    return er;
  }
  return *i->second;
}

/**
 * @brief Gets buffer meta data
 *
 * @param name buffer name
 *
 * @return meta data (binding,name,params)
 */
ProgramObjectBufferParams const&ProgramObject::getBuffer(std::string name,bool printErrors)const{
  auto i=this->_bufferList.find(name);
  if(i==this->_bufferList.end()){
    if(printErrors)err("ProgramObject::getBuffer("+name+") - there is no such buffer");
    static const ProgramObjectBufferParams er(this->getFunctionTable());
    return er;
  }
  return *i->second;
}

/**
 * @brief Gets number of uniforms
 *
 * @return number of uniforms
 */
decltype(ProgramObject::_uniformList)::size_type ProgramObject::getNofUniforms()const{
  return this->_uniformList.size();
}

/**
 * @brief Gets number of attributes
 *
 * @return number of attributes
 */
decltype(ProgramObject::_attributeList)::size_type ProgramObject::getNofAttributes()const{
  return this->_attributeList.size();
}

/**
 * @brief gets number of buffers
 *
 * @return number of buffers
 */
decltype(ProgramObject::_bufferNames)::size_type ProgramObject::getNofBuffers()const{
  return this->_bufferNames.size();
}

void ProgramObject::bindSSBO(std::string name,ge::gl::BufferObject*buffer){
  buffer->bindBase(GL_SHADER_STORAGE_BUFFER,this->getBuffer(name).getBinding());
}
void ProgramObject::bindSSBO(std::string name,ge::gl::BufferObject*buffer,GLintptr offset,GLsizeiptr size){
  buffer->bindRange(GL_SHADER_STORAGE_BUFFER,this->getBuffer(name).getBinding(),offset,size);
}

GLenum ProgramObject::getSamplerBinding(std::string uniform){
  return GL_TEXTURE0+this->_samplerList[uniform]->getBinding();
}

void ProgramObject::bindTexture(std::string uniform,ge::gl::TextureObject*texture){
  texture->bind(GL_TEXTURE0+this->_samplerList[uniform]->getBinding());
}
void ProgramObject::bindImage(
    std::string           uniform,
    ge::gl::TextureObject*texture,
    GLint                 level  ,
    GLenum                format ,
    GLenum                access ,
    GLboolean             layered,
    GLint                 layer  ){
  texture->bindImage(this->_samplerList[uniform]->getBinding(),level,format,access,layered,layer);
}

/**
 * @brief Sets this program as active
 */
void ProgramObject::use()const{
  glUseProgram(this->_id);
}

int ProgramObject::_floatMatrixType2Index(GLenum type){
  if(type<=GL_FLOAT_MAT4)return type-GL_FLOAT_MAT2;
  int index=type-GL_FLOAT_MAT2x3;
  if(index<0)return index;
  return index+GL_FLOAT_MAT4-GL_FLOAT_MAT2+1;
}

int ProgramObject::_doubleMatrixType2Index(GLenum type){
  if(type>GL_DOUBLE_MAT4x3||type<GL_DOUBLE_MAT2)return-1;
  return type-GL_DOUBLE_MAT2;
}


#define MATRIXBODYA(TYPE)\
  if(!this->_uniformList.count(name))return;\
auto param=this->_uniformList[name];\
int index=this->_##TYPE##MatrixType2Index(param->getType());\
if(index<0)return;\

#define MATRIXBODY(FCE,TYPE)\
  MATRIXBODYA(TYPE)\
(this->*FCE[index])(param->getLocation(),count,transpose,value)

#define MATRIXBODYDSA(FCE,TYPE)\
  MATRIXBODYA(TYPE)\
(this->*FCE[index])(this->_id,param->getLocation(),count,transpose,value)


void ProgramObject::set(
    std::string   name,
    GLsizei       count,
    GLboolean     transpose,
    const GLfloat*value){
  const decltype(&FunctionProvider::glUniformMatrix4fv) matrixfFce[] = {
    &FunctionProvider::glUniformMatrix2fv  ,
    &FunctionProvider::glUniformMatrix3fv  ,
    &FunctionProvider::glUniformMatrix4fv  ,
    &FunctionProvider::glUniformMatrix2x3fv,
    &FunctionProvider::glUniformMatrix3x2fv,
    &FunctionProvider::glUniformMatrix2x4fv,
    &FunctionProvider::glUniformMatrix4x2fv,
    &FunctionProvider::glUniformMatrix3x4fv,
    &FunctionProvider::glUniformMatrix4x3fv,
  };
  MATRIXBODY(matrixfFce,float);
}

void ProgramObject::set(
    std::string    name,
    GLsizei        count,
    GLboolean      transpose,
    const GLdouble*value){
  const decltype(&FunctionProvider::glUniformMatrix4dv) matrixdFce[] = {
    &FunctionProvider::glUniformMatrix2dv  ,
    &FunctionProvider::glUniformMatrix3dv  ,
    &FunctionProvider::glUniformMatrix4dv  ,
    &FunctionProvider::glUniformMatrix2x3dv,
    &FunctionProvider::glUniformMatrix3x2dv,
    &FunctionProvider::glUniformMatrix2x4dv,
    &FunctionProvider::glUniformMatrix4x2dv,
    &FunctionProvider::glUniformMatrix3x4dv,
    &FunctionProvider::glUniformMatrix4x3dv,
  };
  MATRIXBODY(matrixdFce,double);
}

void ProgramObject::setdsa(
    std::string   name,
    GLsizei       count,
    GLboolean     transpose,
    const GLfloat*value){
  const decltype(&FunctionProvider::glProgramUniformMatrix4fv) matrixfFceDsa[] = {
    &FunctionProvider::glProgramUniformMatrix2fv  ,
    &FunctionProvider::glProgramUniformMatrix3fv  ,
    &FunctionProvider::glProgramUniformMatrix4fv  ,
    &FunctionProvider::glProgramUniformMatrix2x3fv,
    &FunctionProvider::glProgramUniformMatrix3x2fv,
    &FunctionProvider::glProgramUniformMatrix2x4fv,
    &FunctionProvider::glProgramUniformMatrix4x2fv,
    &FunctionProvider::glProgramUniformMatrix3x4fv,
    &FunctionProvider::glProgramUniformMatrix4x3fv,
  };
  MATRIXBODYDSA(matrixfFceDsa,float);
}

void ProgramObject::setdsa(
    std::string    name,
    GLsizei        count,
    GLboolean      transpose,
    const GLdouble*value){
  const decltype(&FunctionProvider::glProgramUniformMatrix4dv) matrixdFceDsa[] = {
    &FunctionProvider::glProgramUniformMatrix2dv  ,
    &FunctionProvider::glProgramUniformMatrix3dv  ,
    &FunctionProvider::glProgramUniformMatrix4dv  ,
    &FunctionProvider::glProgramUniformMatrix2x3dv,
    &FunctionProvider::glProgramUniformMatrix3x2dv,
    &FunctionProvider::glProgramUniformMatrix2x4dv,
    &FunctionProvider::glProgramUniformMatrix4x2dv,
    &FunctionProvider::glProgramUniformMatrix3x4dv,
    &FunctionProvider::glProgramUniformMatrix4x3dv,
  };
  MATRIXBODYDSA(matrixdFceDsa,double);
}

  DEF_PROGRAMOBJECT_SET(1,f)
  DEF_PROGRAMOBJECT_SET(2,f)
  DEF_PROGRAMOBJECT_SET(3,f)
  DEF_PROGRAMOBJECT_SET(4,f)
  DEF_PROGRAMOBJECT_SET(1,d)
  DEF_PROGRAMOBJECT_SET(2,d)
  DEF_PROGRAMOBJECT_SET(3,d)
  DEF_PROGRAMOBJECT_SET(4,d)
  DEF_PROGRAMOBJECT_SET(1,i)
  DEF_PROGRAMOBJECT_SET(2,i)
  DEF_PROGRAMOBJECT_SET(3,i)
  DEF_PROGRAMOBJECT_SET(4,i)
  DEF_PROGRAMOBJECT_SET(1,ui)
  DEF_PROGRAMOBJECT_SET(2,ui)
  DEF_PROGRAMOBJECT_SET(3,ui)
  DEF_PROGRAMOBJECT_SET(4,ui)
  DEF_PROGRAMOBJECT_SET(1,boolean)
  DEF_PROGRAMOBJECT_SET(2,boolean)
  DEF_PROGRAMOBJECT_SET(3,boolean)
  DEF_PROGRAMOBJECT_SET(4,boolean)
  DEF_PROGRAMOBJECT_SETV(f)
  DEF_PROGRAMOBJECT_SETV(d)
  DEF_PROGRAMOBJECT_SETV(i)
  DEF_PROGRAMOBJECT_SETV(ui)
DEF_PROGRAMOBJECT_SETV(boolean)


  DEF_PROGRAMOBJECT_SETDSA(1,f)
  DEF_PROGRAMOBJECT_SETDSA(2,f)
  DEF_PROGRAMOBJECT_SETDSA(3,f)
  DEF_PROGRAMOBJECT_SETDSA(4,f)
  DEF_PROGRAMOBJECT_SETDSA(1,d)
  DEF_PROGRAMOBJECT_SETDSA(2,d)
  DEF_PROGRAMOBJECT_SETDSA(3,d)
  DEF_PROGRAMOBJECT_SETDSA(4,d)
  DEF_PROGRAMOBJECT_SETDSA(1,i)
  DEF_PROGRAMOBJECT_SETDSA(2,i)
  DEF_PROGRAMOBJECT_SETDSA(3,i)
  DEF_PROGRAMOBJECT_SETDSA(4,i)
  DEF_PROGRAMOBJECT_SETDSA(1,ui)
  DEF_PROGRAMOBJECT_SETDSA(2,ui)
  DEF_PROGRAMOBJECT_SETDSA(3,ui)
  DEF_PROGRAMOBJECT_SETDSA(4,ui)
  DEF_PROGRAMOBJECT_SETDSA(1,boolean)
  DEF_PROGRAMOBJECT_SETDSA(2,boolean)
  DEF_PROGRAMOBJECT_SETDSA(3,boolean)
  DEF_PROGRAMOBJECT_SETDSA(4,boolean)
  DEF_PROGRAMOBJECT_SETDSAV(f)
  DEF_PROGRAMOBJECT_SETDSAV(d)
  DEF_PROGRAMOBJECT_SETDSAV(i)
  DEF_PROGRAMOBJECT_SETDSAV(ui)
DEF_PROGRAMOBJECT_SETDSAV(boolean)

