#pragma once

#include<geCore/Command.h>
#include<geGL/Export.h>
#include<GL/glew.h>
#include<geGL/AllAttribs.h>

namespace ge{
  namespace gl{
    class TextureBarrier:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          return NULL;
        }
      public:
        TextureBarrier(
            ){
        }
        virtual~TextureBarrier(){}
        virtual void operator()(){
          glTextureBarrier(

          );
        }
    };

    template<
      typename BARRIERS_TYPE = GLbitfield>
    class MemoryBarrierByRegion:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "barriers")return(void*)&this->barriers;
          return NULL;
        }
      public:
        BARRIERS_TYPE barriers;
        MemoryBarrierByRegion(
            BARRIERS_TYPE const&barriers){
          this->barriers = barriers;
        }
        virtual~MemoryBarrierByRegion(){}
        virtual void operator()(){
          glMemoryBarrierByRegion(
            ge::core::convertTo<GLbitfield>(this->barriers)
          );
        }
    };

    template<
      typename BARRIERS_TYPE = GLbitfield>
    class MemoryBarrier:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "barriers")return(void*)&this->barriers;
          return NULL;
        }
      public:
        BARRIERS_TYPE barriers;
        MemoryBarrier(
            BARRIERS_TYPE const&barriers){
          this->barriers = barriers;
        }
        virtual~MemoryBarrier(){}
        virtual void operator()(){
          glMemoryBarrier(
            ge::core::convertTo<GLbitfield>(this->barriers)
          );
        }
    };


    template<
      typename BARRIERS_TYPE = GLbitfield>
    inline MemoryBarrierByRegion<
      BARRIERS_TYPE>* newMemoryBarrierByRegion(
        BARRIERS_TYPE const&barriers){
        return new MemoryBarrierByRegion<
          BARRIERS_TYPE>(
              barriers);
    }
    template<
      typename BARRIERS_TYPE = GLbitfield>
    inline MemoryBarrier<
      BARRIERS_TYPE>* newMemoryBarrier(
        BARRIERS_TYPE const&barriers){
        return new MemoryBarrier<
          BARRIERS_TYPE>(
              barriers);
    }
  }
}
