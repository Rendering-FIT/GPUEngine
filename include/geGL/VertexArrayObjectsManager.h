#ifndef _VERTEXARRAYOBJECTSMANAGER_H_
#define _VERTEXARRAYOBJECTSMANAGER_H_

#include<iostream>

#include<geGL/OpenGL.h>

#include<vector>
#include<map>

namespace ge
{
  namespace gl
  {
    const std::string VERTEX_ARRAY_OBJECT_MANAGER_DEFAULT_NAME = ""   ;
    const std::string VERTEX_ARRAY_OBJECT_MANAGER_BASE_NAME    = "vao";


    /**
     * @brief This class represents manager of vertex array objects
     * OpenGL 4.5, table 23.3
     */
    class GEGL_EXPORT VertexArrayObjectsManager
    {
      private:
        std::map<std::string,GLuint>_vaos;
        unsigned                    _vaoCount;
        void _prepareVAO(
            std::string  *name,
            GLuint      **vao);
      public:
        /**
         * @brief creates command that clears/deletes vertex array objects inside manager
         *
         * @param command created command that destroys vertex array objects
         */
        void clear(Command **command);
        /**
         * @brief immediately clears manager
         */
        void clearNow();
        /**
         * @brief creates commands that create vertex array object
         *
         * @param command created command that creates vertex array object
         * @param name name of vertex array object
         *
         * @return returns textual representation of vertex array object
         */
        std::string insert(
            Command     **command,
            std::string   name = VERTEX_ARRAY_OBJECT_MANAGER_DEFAULT_NAME);
        /**
         * @brief immediately creates vertex array object
         *
         * @param name optional name of vertex array object
         *
         * @return returns textual representation of vertex array object
         */
        std::string insertNow(
            std::string name = VERTEX_ARRAY_OBJECT_MANAGER_DEFAULT_NAME);
        /**
         * @brief creates command that adds vertex attribute to vertex array object
         *
         * @param command    command
         * @param vaobj      is name of vao where the vertex attribute will be inserted
         * @param buffer     buffer object where the vertex attribute is located
         * @param index      index of vertex attribute inside shader
         * @param size       size of vertex attribute in components
         * @param type       type of vertex attribute
         * @param normalized is vertex attribute normalized
         * @param stride     stride of vertex attributes
         * @param offset     offset of first vertex attribute inside buffer
         * @param divisitor  attribute advances once per divisitor instances of vertices
         */
        void addAttrib(
            Command   **command,
            std::string vaobj,
            GLuint      buffer,
            GLuint      index,
            GLuint      size,
            GLenum      type,
            GLboolean   normalized,
            GLsizei     stride,
            unsigned    offset,
            GLuint      divisitor);
        /**
         * @brief immediately inserts attribute into vertex array object
         *
         * @param vaobj      is name of vao where the vertex attribute will be inserted
         * @param buffer     buffer object where the vertex attribute is located
         * @param index      index of vertex attribute inside shader
         * @param size       size of vertex attribute in components
         * @param type       type of vertex attribute
         * @param normalized is vertex attribute normalized
         * @param stride     stride of vertex attributes
         * @param offset     offset of first vertex attribute inside buffer
         * @param divisitor  attribute advances once per divisitor instances of vertices
         */
        void addAttribNow(
            std::string vaobj,
            GLuint      buffer,
            GLuint      index,
            GLuint      size,
            GLenum      type,
            GLboolean   normalized,
            GLsizei     stride,
            unsigned    offset,
            GLuint      divisitor);
        /**
         * @brief creates command that adds element buffer object into vao
         *
         * @param command generated command
         * @param vaobj   name of vertex array object
         * @param ebo     element buffer object
         */
        void addElementBuffer(
            Command     **command,
            std::string   vaobj,
            GLuint        ebo);
        /**
         * @brief immediately adds element buffer object into vao
         *
         * @param vaobj name of vertex array object
         * @param ebo   element buffer object
         */
        void addElementBufferNow(
            std::string vaobj,
            GLuint      ebo);
            
        /**
         * @brief create command that binds vertex array object
         *
         * @param command generated command that binds selected vertex array object
         * @param vaobj   name of vertex array object
         */
        void bind(
            Command     **command,
            std::string   vaobj);
        /**
         * @brief immediately binds selected vertex array object
         *
         * @param vaobj name of vertex array object
         */
        void bindNow(
            std::string vaobj);
        /**
         * @brief create command that unbinds any vertex array object
         *
         * @param command generated command that unbinds any vertex array
         */
        void unbind(
            Command     **command);
        /**
         * @brief immediately unbinds any vertex array object
         */
        void unbindNow();
    };
//    class LeastRecentlyUseItem
//    {
//      public:
//        unsigned long long value;
//        std::string        name;
//    };
//
//    class GEGL_EXPORT LeastRecentlyUsed
//    {
//      private:
//        std::vector<LeastRecentlyUsedItem*>            _table;
//        std::map<std::string,LeastRecentlyUsedItem*>   _name2Item;
//        std::vector<std::string>                       _markedForDeletion;
//        unsigned long long                             _actualTime;
//        unsigned long long                             _maxTimeDiference;
//      public:
//        /**
//         * @brief creates least recently used table
//         *
//         * @param maxTimeDiference if time of item exceeds this value it's marked for deletion
//         */
//        LeastRecentlyUsed(
//            unsigned long long maxTimeDiference);
//        /**
//         * @brief destroys least recently used table
//         */
//        ~LeastRecentlyUsed();
//        /**
//         * @brief increments time of lru
//         */
//        void incrementGlobalTime();
//        void getMarkedForDeletion(std::vector<std::string>*martedForDeletion);
//        void clearMarkedForDeletion();
//    };

  }
}

#endif//_VERTEXARRAYOBJECTSMANAGER_H_
