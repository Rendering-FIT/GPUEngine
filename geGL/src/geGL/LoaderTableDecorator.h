#pragma once

#include<geGL/FunctionLoaderInterface.h>
#include<geGL/OpenGLFunctionTable.h>
#include<cassert>

namespace ge{
  namespace gl{
    template<typename T>
      class LoaderTableDecorator: public T{
        public:
          template<typename...ARGS>
            LoaderTableDecorator(
                std::shared_ptr<FunctionLoaderInterface>const&functionLoader,
                ARGS&&...args):T(args...){
              assert(this!=nullptr);
              this->m_functionLoader = functionLoader;
            }
          virtual ~LoaderTableDecorator(){}
        protected:
          std::shared_ptr<FunctionLoaderInterface>m_functionLoader = nullptr;
          virtual bool m_init(){
            assert(this!=nullptr);
            if(!T::m_init())return false;
            assert(this->m_functionLoader!=nullptr);
#include<geGL/Generated/LoaderLoadingCalls.h>
            return true;
          }
#include<geGL/Generated/LoaderImplementation.h>
      };
  }
}
