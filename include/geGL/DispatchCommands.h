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
        public ge::core::Command,
        public at::Indirect<INDIRECT_TYPE>{
      public:
        DispatchComputeIndirect(
            INDIRECT_TYPE const&indirect):
          at::Indirect<INDIRECT_TYPE>(indirect){}
        virtual~DispatchComputeIndirect(){}
        virtual void operator()(){
          glDispatchComputeIndirect(
            ge::core::convertTo<GLintptr>(this->at::Indirect<INDIRECT_TYPE>::_value)
          );
        }
    };

    template<
      typename NUM_GROUPS_X_TYPE = GLuint,
      typename NUM_GROUPS_Y_TYPE = GLuint,
      typename NUM_GROUPS_Z_TYPE = GLuint>
    class DispatchCompute:
        public ge::core::Command,
        public at::Num_groups_x<NUM_GROUPS_X_TYPE>,
        public at::Num_groups_y<NUM_GROUPS_Y_TYPE>,
        public at::Num_groups_z<NUM_GROUPS_Z_TYPE>{
      public:
        DispatchCompute(
            NUM_GROUPS_X_TYPE const&num_groups_x,
            NUM_GROUPS_Y_TYPE const&num_groups_y,
            NUM_GROUPS_Z_TYPE const&num_groups_z):
          at::Num_groups_x<NUM_GROUPS_X_TYPE>(num_groups_x),
          at::Num_groups_y<NUM_GROUPS_Y_TYPE>(num_groups_y),
          at::Num_groups_z<NUM_GROUPS_Z_TYPE>(num_groups_z){}
        virtual~DispatchCompute(){}
        virtual void operator()(){
          glDispatchCompute(
            ge::core::convertTo<GLuint>(this->at::Num_groups_x<NUM_GROUPS_X_TYPE>::_value),
            ge::core::convertTo<GLuint>(this->at::Num_groups_y<NUM_GROUPS_Y_TYPE>::_value),
            ge::core::convertTo<GLuint>(this->at::Num_groups_z<NUM_GROUPS_Z_TYPE>::_value)
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
