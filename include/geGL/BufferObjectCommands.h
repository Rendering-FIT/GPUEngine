#pragma once

#include<geCore/Command.h>
#include<geGL/Export.h>
#include<GL/glew.h>
#include<geGL/BufferObject.h>

namespace ge{
  namespace gl{
    namespace bo{
      
      template<typename TYPE>
      class Shared{
        protected:
          std::shared_ptr<TYPE>_obj;
        public:
          Shared(std::shared_ptr<TYPE>&obj){this->_obj=obj;}
          std::shared_ptr<TYPE>&get(){return this->_obj;}
      };

      class GEGL_EXPORT SharedBuffer{
        protected:
          std::shared_ptr<BufferObject>_buffer;
        public:
          SharedBuffer(std::shared_ptr<BufferObject>buffer);
          std::shared_ptr<BufferObject>&getBuffer();
      };


      class BufferData{
        private:
          GLsizeiptr    _size;
          const GLvoid* _data;
        public:
          BufferData(
              GLsizeiptr    size = 0   ,
              const GLvoid* data = NULL);
          void set(
              GLsizeiptr    size = 0   ,
              const GLvoid* data = NULL);
          GLsizeiptr    getSize();
          const GLvoid* getData();
      };

      template<typename SIZE,typename DATA,typename FLAGS>
      class Constr: public ge::core::Command{
        private:
          std::shared_ptr<BufferObject>_buffer;
          SIZE                         _size  ;
          DATA                         _data  ;
          FLAGS                        _flags ;
        public:
          Constr(std::shared_ptr<BufferObject>&buffer,SIZE&size,DATA&data,FLAGS&flags){
            this->_buffer = buffer;
            this->_size   = size  ;
            this->_data   = data  ;
            this->_flags  = flags ;
          }
          void operator()();
          std::shared_ptr<BufferObject>&getBuffer(){return this->_buffer;}
          SIZE  &getSize (){return this->_size  ;}
          DATA  &getData (){return this->_data  ;}
          FLAGS &getFlags(){return this->_flags ;}
      };
      template<>
      void Constr<GLsizeiptr,const GLvoid*,GLbitfield>::operator()(){
        this->_buffer = std::make_shared<BufferObject>(this->_size,this->_data,this->_flags);
      }
      template<>
      void Constr<std::shared_ptr<GLsizeiptr>,const GLvoid*,GLbitfield>::operator()(){
        this->_buffer = std::make_shared<BufferObject>(*this->_size,this->_data,this->_flags);
      }
      template<>
      void Constr<GLsizeiptr,std::shared_ptr<const GLvoid*>,GLbitfield>::operator()(){
        this->_buffer = std::make_shared<BufferObject>(this->_size,*this->_data,this->_flags);
      }
      template<>
      void Constr<std::shared_ptr<GLsizeiptr>,std::shared_ptr<const GLvoid*>,GLbitfield>::operator()(){
        this->_buffer = std::make_shared<BufferObject>(*this->_size,*this->_data,this->_flags);
      }
      template<>
      void Constr<GLsizeiptr,const GLvoid*,std::shared_ptr<GLbitfield>>::operator()(){
        this->_buffer = std::make_shared<BufferObject>(this->_size,this->_data,*this->_flags);
      }
      template<>
      void Constr<std::shared_ptr<GLsizeiptr>,const GLvoid*,std::shared_ptr<GLbitfield>>::operator()(){
        this->_buffer = std::make_shared<BufferObject>(*this->_size,this->_data,*this->_flags);
      }
      template<>
      void Constr<GLsizeiptr,std::shared_ptr<const GLvoid*>,std::shared_ptr<GLbitfield>>::operator()(){
        this->_buffer = std::make_shared<BufferObject>(this->_size,*this->_data,*this->_flags);
      }
      template<>
      void Constr<std::shared_ptr<GLsizeiptr>,std::shared_ptr<const GLvoid*>,std::shared_ptr<GLbitfield>>::operator()(){
        this->_buffer = std::make_shared<BufferObject>(*this->_size,*this->_data,*this->_flags);
      }

      class GEGL_EXPORT Constructor: public ge::core::Command, public Shared<BufferObject>{
        private:
          std::shared_ptr<BufferData>_data ;
          std::shared_ptr<GLbitfield>_flags;
        public:
          Constructor(
              std::shared_ptr<BufferObject>buffer,
              std::shared_ptr<BufferData>  data  ,
              std::shared_ptr<GLbitfield>  flags );
          Constructor(
              std::shared_ptr<BufferObject>buffer                ,
              std::shared_ptr<BufferData>  data                  ,
              GLbitfield                   flags = GL_STATIC_DRAW);
          Constructor(
              std::shared_ptr<BufferObject>buffer                ,
              GLsizeiptr                   size                  ,
              const GLvoid*                data  = NULL          ,
              GLbitfield                   flags = GL_STATIC_DRAW);

          void operator()();
          std::shared_ptr<BufferData>&getData ();
          std::shared_ptr<GLbitfield>&getFlags();
      };

      class GEGL_EXPORT Map: public ge::core::Command, public SharedBuffer{
        private:
          std::shared_ptr<GLvoid*>   _ptr   ;
          std::shared_ptr<GLbitfield>_access;
          std::shared_ptr<GLintptr>  _offset;
          std::shared_ptr<GLsizeiptr>_size  ;
        public:
          Map(
              std::shared_ptr<BufferObject>buffer                                   ,
              std::shared_ptr<GLvoid*>     ptr                                      ,
              GLbitfield                   access = GL_MAP_READ_BIT|GL_MAP_WRITE_BIT);
          Map(
              std::shared_ptr<BufferObject>buffer                                   ,
              std::shared_ptr<GLvoid*>     ptr                                      ,
              GLintptr                     offset                                   ,
              GLsizeiptr                   size                                     ,
              GLbitfield                   access = GL_MAP_READ_BIT|GL_MAP_WRITE_BIT);
          void operator()();
          std::shared_ptr<GLvoid*   >&getPtr();
          std::shared_ptr<GLbitfield>&getAccess();
          std::shared_ptr<GLintptr  >&getOffset();
          std::shared_ptr<GLsizeiptr>&getSize  ();
      };

      class GEGL_EXPORT Unmap: public ge::core::Command, public SharedBuffer{
        public:
          Unmap(std::shared_ptr<BufferObject>buffer);
          void operator()();
      };

      class GEGL_EXPORT SetData: public ge::core::Command, public SharedBuffer{
        private:
          const GLvoid*_data  ;
          GLsizeiptr   _size  ;
          GLintptr     _offset;
        public:
          SetData(const GLvoid*data,GLsizeiptr size,GLintptr offset);


      };
    }
  }
}
