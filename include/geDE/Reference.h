#pragma once

#include<geDE/AtomicFunction.h>
#include<geDE/FunctionRegister.h>

namespace ge{
  namespace de{
    class GEDE_EXPORT Reference: public AtomicFunction{
      public:
        Reference(
            std::shared_ptr<FunctionRegister>const&fr            ,
            TypeId                                 id            ,
            bool                                   ignore = false);
      protected:
        virtual bool _do();
    };
    template<>inline std::string keyword<Reference>(){return "Reference";}
  }
}
