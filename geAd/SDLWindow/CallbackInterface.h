#pragma once

namespace ge{
  namespace util{
    class CallbackInterface{
      public:
        virtual ~CallbackInterface(){}
        virtual void operator()() = 0;
    };
  }
}
