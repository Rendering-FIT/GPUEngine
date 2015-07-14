#pragma once

#include<memory>

namespace ge{
  namespace gl{
    template<typename TYPE>
      class Shared{
        protected:
          std::shared_ptr<TYPE>_object;
        public:
          Shared(const std::shared_ptr<TYPE>&object){this->set(object);}
          std::shared_ptr<TYPE>&get(){return this->_object;}
          void set(const std::shared_ptr<TYPE>&object){this->_object=object;}
      };
  }
}
