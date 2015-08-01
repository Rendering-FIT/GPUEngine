#pragma once

#include<geCore/Command.h>
#include<geGL/Export.h>
#include<GL/glew.h>
#include<geGL/AllAttribs.h>

namespace ge{
  namespace gl{
    template<
      typename INDIRECT_TYPE = GLintptr>
    class DispatchComputeIndirect:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "indirect")return(void*)&this->indirect;
          return NULL;
        }
      public:
        INDIRECT_TYPE indirect;
        DispatchComputeIndirect(
            INDIRECT_TYPE const&indirect){
          this->indirect = indirect;
        }
        virtual~DispatchComputeIndirect(){}
        virtual void operator()(){
          glDispatchComputeIndirect(
            ge::core::convertTo<GLintptr>(this->indirect)
          );
        }
    };

    template<
      typename NUM_GROUPS_X_TYPE = GLuint,
      typename NUM_GROUPS_Y_TYPE = GLuint,
      typename NUM_GROUPS_Z_TYPE = GLuint>
    class DispatchCompute:
        public ge::core::Command{
      protected:
        void*_getAttribAddress(std::string name){
          if(name == "num_groups_x")return(void*)&this->num_groups_x;
          if(name == "num_groups_y")return(void*)&this->num_groups_y;
          if(name == "num_groups_z")return(void*)&this->num_groups_z;
          return NULL;
        }
      public:
        NUM_GROUPS_X_TYPE num_groups_x;
        NUM_GROUPS_Y_TYPE num_groups_y;
        NUM_GROUPS_Z_TYPE num_groups_z;
        DispatchCompute(
            NUM_GROUPS_X_TYPE const&num_groups_x,
            NUM_GROUPS_Y_TYPE const&num_groups_y,
            NUM_GROUPS_Z_TYPE const&num_groups_z){
          this->num_groups_x = num_groups_x;
          this->num_groups_y = num_groups_y;
          this->num_groups_z = num_groups_z;
        }
        virtual~DispatchCompute(){}
        virtual void operator()(){
          glDispatchCompute(
            ge::core::convertTo<GLuint>(this->num_groups_x),
            ge::core::convertTo<GLuint>(this->num_groups_y),
            ge::core::convertTo<GLuint>(this->num_groups_z)
          );
        }
    };

    template<
      typename INDIRECT_TYPE = GLintptr>
    inline DispatchComputeIndirect<
      INDIRECT_TYPE>* newDispatchComputeIndirect(
        INDIRECT_TYPE const&indirect){
        return new DispatchComputeIndirect<
          INDIRECT_TYPE>(
              indirect);
    }
    template<
      typename NUM_GROUPS_X_TYPE = GLuint,
      typename NUM_GROUPS_Y_TYPE = GLuint,
      typename NUM_GROUPS_Z_TYPE = GLuint>
    inline DispatchCompute<
      NUM_GROUPS_X_TYPE,
      NUM_GROUPS_Y_TYPE,
      NUM_GROUPS_Z_TYPE>* newDispatchCompute(
        NUM_GROUPS_X_TYPE const&num_groups_x,
        NUM_GROUPS_Y_TYPE const&num_groups_y,
        NUM_GROUPS_Z_TYPE const&num_groups_z){
        return new DispatchCompute<
          NUM_GROUPS_X_TYPE,
          NUM_GROUPS_Y_TYPE,
          NUM_GROUPS_Z_TYPE>(
              num_groups_x,
              num_groups_y,
              num_groups_z);
    }
  }
}
