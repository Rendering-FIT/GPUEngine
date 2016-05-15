#pragma once

#include<geGL/OpenGLFunctionTable.h>

namespace ge{
  namespace gl{
    namespace opengl{
      template<typename T>
        class DSATableDecorator: public T{
          public:
            template<typename...ARGS>
              DSATableDecorator(ARGS&&...args):T(args...){}
            virtual ~DSATableDecorator(){}
          protected:
            virtual bool m_init(){
              if(!T::m_init())return false;
              //if(!this->m_ptr_a)this->m_ptr_a = (TableInterface::MFCE)
              //  &DSATableDecorator::m_a_impl_dsa;
              //if(!this->m_ptr_b)this->m_ptr_b = (TableInterface::MFCE)
              //  &DSATableDecorator::m_b_impl_dsa;
              return true;
            }
            //void m_a_impl_dsa()const{
            //  std::cout<<"a dsa variant"<<std::endl;
            //}
            //void m_b_impl_dsa()const{
            //  std::cout<<"("<<std::endl;
            //  this->a();
            //  std::cout<<")"<<std::endl;
            //}
        };

    }
  }
}

