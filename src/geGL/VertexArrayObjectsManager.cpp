#include<geGL/VertexArrayObjectsManager.h>
#include<geGL/VertexArrayObjectsCommands.h>

#include<stdarg.h>
#include<string>
#include<cstring>
#include<fstream>
#include<sstream>

namespace ge
{
  namespace gl
  {
    void VertexArrayObjectsManager::_prepareVAO(std::string*name,GLuint**vao){
      if(*name==VERTEX_ARRAY_OBJECT_MANAGER_DEFAULT_NAME){
        std::stringstream vaoName;
        vaoName<<VERTEX_ARRAY_OBJECT_MANAGER_BASE_NAME<<this->_vaoCount;
        *name=vaoName.str();
      }
      this->_vaos.insert(std::pair<std::string,GLuint>(*name,0));
      *vao=&this->_vaos[*name];
    }

    std::string VertexArrayObjectsManager::insert(
        ge::core::Command     **command,
        std::string   name){
      GLuint *vao;
      this->_prepareVAO(&name,&vao);
      *command = new GenVertexArrays(1,vao);
      return name;
    }
    std::string VertexArrayObjectsManager::insertNow(
        std::string   name){
      GLuint *vao;
      this->_prepareVAO(&name,&vao);
      glGenVertexArrays(1,vao);
      return name;
    }
    void VertexArrayObjectsManager::addAttrib(
        ge::core::Command   **command,
        std::string vaobj,
        GLuint      /*buffer*/,
        GLuint      /*index*/,
        GLuint      /*size*/,
        GLenum      /*type*/,
        GLboolean   /*normalized*/,
        GLsizei     /*stride*/,
        unsigned    /*offset*/,
        GLuint      /*divisitor*/){
      GLuint*vao=&this->_vaos[vaobj];
      ge::core::CommandList*commandList=new ge::core::CommandList(false);
      commandList->add(new BindVertexArray(*vao));
      *command=commandList;
    }


  }//ogl
}//ge
