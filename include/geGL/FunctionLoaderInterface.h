#pragma once

namespace ge{
  namespace gl{
    namespace opengl{
      class FunctionLoaderInterface{
        public:
          typedef void(*FUNCTION_POINTER)();
          FunctionLoaderInterface(){}
          virtual ~FunctionLoaderInterface(){}
          virtual FUNCTION_POINTER load(char const*fceName)const = 0;
      };
    }
  }
}
