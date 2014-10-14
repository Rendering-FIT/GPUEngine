#include<geGL/ShaderObjectsManager.h>

#include<stdarg.h>
#include<string>
#include<cstring>
#include<fstream>
#include<sstream>

namespace ge
{
  namespace gl
  {
    char*ShaderObjectManager::_readWholeFile(int*length,std::string fileName){
      std::ifstream f(fileName.data(),std::ifstream::binary);//open file
      if(!f.good())throw std::string("File "+fileName+" is corrupt");
      f.seekg(0,std::ios::end);//go to the end of file
      *length=f.tellg();//get length
      f.seekg(0,std::ios::beg);//go to the start of file
      char*data=new char[*length];//allocate date
      f.read(data,*length);//read file
      f.close();//close file
      return data;//return data
    }
    int ShaderObjectManager::_fileTypeSwitch(std::string fileName,unsigned numType,...){
      va_list args;//arguments
      va_start(args,numType);//start of arguments
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
    GLenum ShaderObjectManager::_fileToShaderType(std::string fileName){
      switch(this->_fileTypeSwitch(fileName,12,//number of extensions
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
        default:return 0;//unknown
      }
    }
    void ShaderObjectManager::_appendAfterVersion(
        std::string *text,
        std::string  definitions){
      if(definitions==SHADER_OBJECT_MANAGER_DEFAULT_DEFINITIONS)return;//empty definitions
      int versionPosition=0;//position of version
      int lineEndPosition=0;//position of first line end after version
      versionPosition=text->find(SHADER_OBJECT_MANAGER_VERSION_KEYWORD);
      lineEndPosition=text->find(SHADER_OBJECT_MANAGER_LINE_END,versionPosition);
      text->insert(lineEndPosition+1,definitions);
    }
    void ShaderObjectManager::_setVersion(
        std::string *text,
        unsigned     version,
        std::string  profile){
      if(version==SHADER_OBJECT_MANAGER_DEFAULT_VERSION)return;
      int position=0;
      while((position=text->find(SHADER_OBJECT_MANAGER_VERSION_KEYWORD,position))>=0){
        int lineEndPosition=text->find(SHADER_OBJECT_MANAGER_LINE_END,position);
        text->erase(position,lineEndPosition-position);
      }
      std::stringstream result;
      result<<SHADER_OBJECT_MANAGER_VERSION_KEYWORD<<" "<<version<<" "<<profile;
      result<<SHADER_OBJECT_MANAGER_LINE_END;
      result<<*text;
      *text=result.str();
    }
    bool ShaderObjectManager::_prepareSource(
        GLuint       **shader,
        GLchar      ***string,
        std::string    text,
        std::string   *name,
        std::string    definitions,
        unsigned       version,
        std::string    profile){
      //FIXME maybe create new command for these actions espetially for loading file
      //does a shader with same name exist?
      if(this->_shaders.count(*name)!=0)return false;
      //set version
      this->_setVersion(&text,version,profile);
      //append definitions
      this->_appendAfterVersion(&text,definitions);
      //is name the default name
      if(*name==SHADER_OBJECT_MANAGER_DEFAULT_NAME){
        //stringstream for conversion of numbers to string
        std::stringstream shaderName;
        //create new name using base name and ordering number
        shaderName<<SHADER_OBJECT_MANAGER_BASE_NAME<<this->_shaderCount;
        //set name
        *name=shaderName.str();
      }
      //allocate shader inside manager
      this->_shaders.insert(std::pair<std::string,GLuint>(*name,0));
      //get address of shader inside manager
      *shader=&this->_shaders[*name];
      //allocate array of sources
      *string=new GLchar*[1];
      //allocate characters of source inside array of sources
      (*string)[0]=new GLchar[text.length()+1];
      //copy source
      memcpy((*string)[0],text.c_str(),text.length());
      //put string end to the end of source
      string[0][text.length()]='\0';
      //increment counter of shader
      this->_shaderCount++;//increment shader count
      //preparation was successful
      return true;
    }

    void ShaderObjectManager::clear(Command **command){
      CommandList*commandList = new CommandList(true);
      std::map<std::string,GLuint>::iterator ii     = this->_shaders.begin();
      std::map<std::string,GLuint>::iterator ii_end = this->_shaders.end();
      for(;ii!=ii_end;++ii)
        commandList->commands.push_back(new DeleteShader(&ii->second));
      *command=commandList;
    }
    std::string ShaderObjectManager::insert(
        Command     **command,
        GLenum        type,
        std::string   text,
        std::string   name,
        std::string   definitions,
        unsigned      version,
        std::string profile){
      GLuint  *shader;
      GLchar **string;
      if(this->_prepareSource(&shader,&string,text,&name,definitions,version,profile)){
        CommandList*commandList = new CommandList(false);
        commandList->commands.push_back(new CreateShader (shader,type));
        commandList->commands.push_back(new ShaderSource (shader,1,string,NULL));
        commandList->commands.push_back(new CompileShader(shader));
        *command = commandList;
      }else
        *command = NULL;
      return name;
    }
    void ShaderObjectManager::insert(
        Command     **command,
        std::string   fileName,
        std::string   name,
        std::string   definitions,
        unsigned      version,    
        std::string   profile){
      int length;
      this->insert(
          command,
          this->_fileToShaderType(fileName),
          this->_readWholeFile(&length,fileName),
          name,
          definitions,
          version,
          profile);
    }
    std::string ShaderObjectManager::insertNow(
        GLenum        type,
        std::string   text,
        std::string   name,        
        std::string   definitions,
        unsigned      version,
        std::string   profile){    
      GLuint  *shader;
      GLchar **string;
      if(this->_prepareSource(&shader,&string,text,&name,definitions,version,profile)){
        *shader = glCreateShader(type);
        glShaderSource(*shader,1,(const GLchar**)string,NULL);
        glCompileShader(*shader);
        delete[]string[1];
        delete[]string;
      }
      return name;
    }
    void ShaderObjectManager::insert(
        std::string   fileName,
        std::string   name,
        std::string   definitions,
        unsigned      version,
        std::string   profile){
      int length;
      this->insertNow(
          this->_fileToShaderType(fileName),
          this->_readWholeFile(&length,fileName),
          name,
          definitions,
          version,
          profile);
    }

    std::string define(std::string name){
      return"#define "+name+SHADER_OBJECT_MANAGER_LINE_END;
    }

    std::string ShaderObjectManager::define(
        std::string name,
        unsigned    value){
      std::stringstream result;
      result<<"#define "<<name<<" "<<value<<"u\n";
      return result.str();
    }
    std::string ShaderObjectManager::define(
        std::string name,
        unsigned    value0,
        unsigned    value1){
      std::stringstream result;
      result<<"#define "<<name<<" uvec2("<<value0<<"u,"<<value1<<"u)\n";
      return result.str();
    }
    std::string ShaderObjectManager::define(
        std::string name,
        unsigned    value0,
        unsigned    value1,
        unsigned    value2){
      std::stringstream result;
      result<<"#define "<<name<<" uvec3("<<value0<<"u,"<<value1<<"u,"<<value2<<"u)\n";
      return result.str();
    }
    std::string ShaderObjectManager::define(
        std::string name,
        unsigned    value0,
        unsigned    value1,
        unsigned    value2,
        unsigned    value3){
      std::stringstream result;
      result<<"#define "<<name<<" uvec4("<<value0<<"u,"<<value1<<"u,"<<value2<<"u,"<<value3<<"u)\n";
      return result.str();
    }
    std::string ShaderObjectManager::define(
        std::string name,
        int         value){
      std::stringstream result;
      result<<"#define "<<name<<" "<<value<<"\n";
      return result.str();
    }
    std::string ShaderObjectManager::define(
        std::string name,
        int         value0,
        int         value1){
      std::stringstream result;
      result<<"#define "<<name<<" ivec2("<<value0<<"u,"<<value1<<"u)\n";
      return result.str();
    }
    std::string ShaderObjectManager::define(
        std::string name,
        int         value0,
        int         value1,
        int         value2){
      std::stringstream result;
      result<<"#define "<<name<<" ivec3("<<value0<<"u,"<<value1<<"u,"<<value2<<"u)\n";
      return result.str();
    }
    std::string ShaderObjectManager::define(
        std::string name,
        int         value0,
        int         value1,
        int         value2,
        int         value3){
      std::stringstream result;
      result<<"#define "<<name<<" ivec4("<<value0<<"u,"<<value1<<"u,"<<value2<<"u,"<<value3<<"u)\n";
      return result.str();
    }

    std::string ShaderObjectManager::define(std::string name,float value){
      std::stringstream result;
      result<<"#define "<<name<<" "<<value<<"\n";
      return result.str();
    }
    std::string ShaderObjectManager::define(
        std::string name,
        float       value0,
        float       value1){
      std::stringstream result;
      result<<"#define "<<name<<" vec2("<<value0<<"u,"<<value1<<"u)\n";
      return result.str();
    }
    std::string ShaderObjectManager::define(
        std::string name,
        float       value0,
        float       value1,
        float       value2){
      std::stringstream result;
      result<<"#define "<<name<<" vec3("<<value0<<"u,"<<value1<<"u,"<<value2<<"u)\n";
      return result.str();
    }
    std::string ShaderObjectManager::define(
        std::string name,
        float       value0,
        float       value1,
        float       value2,
        float       value3){
      std::stringstream result;
      result<<"#define "<<name<<" vec4("<<value0<<"u,"<<value1<<"u,"<<value2<<"u,"<<value3<<"u)\n";
      return result.str();
    }

    std::string ShaderObjectManager::define(std::string name,std::string value){
      return"#define "+name+" "+value+"\n";
    }

  }//ogl
}//ge
