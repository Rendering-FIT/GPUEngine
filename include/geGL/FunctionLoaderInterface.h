#pragma once

namespace ge{
  namespace gl{
    namespace opengl{
      typedef void(*FUNCTION_POINTER)();
      typedef FUNCTION_POINTER(*GET_PROC_ADDRESS)(char const*);
      class FunctionLoaderInterface{
        public:
          FunctionLoaderInterface(){}
          virtual ~FunctionLoaderInterface(){}
          virtual FUNCTION_POINTER load(char const*fceName)const = 0;
      };
    }
  }
}
