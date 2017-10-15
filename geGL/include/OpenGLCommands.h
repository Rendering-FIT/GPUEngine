#pragma once

#include<tuple>
#include<geCore/Dtemplates.h>
#include<geCore/Command.h>
#include<geGL/OpenGL.h>

namespace ge{
  namespace gl{
    //function with non void return value
    template<typename OUTPUT_TO,typename...ARGS_TO,typename OUTPUT_FROM,typename... ARGS_FROM,std::size_t...I,typename std::enable_if<!std::is_same<OUTPUT_TO,void>::value,unsigned>::type = 0>
      void callProviderMethod(OUTPUT_FROM o,std::tuple<ARGS_FROM...>const&args,OUTPUT_TO(Context::*f)(ARGS_TO...)const,ge::core::index_sequence<I...>){
        assert(getDefaultContext()!=nullptr);
        auto prov = &*getDefaultContext();
        assert(prov!=nullptr);
        assert(o!=nullptr);
        *o = (OUTPUT_TO)(prov->*f)(ge::core::convertTo<ARGS_TO,ARGS_FROM>(std::get<I>(args))...);
      }

    template<typename OUTPUT_TO,typename...ARGS_TO,typename OUTPUT_FROM,typename... ARGS_FROM,typename std::enable_if<!std::is_same<OUTPUT_TO,void>::value,unsigned>::type = 0>
      std::shared_ptr<ge::core::Command>createCommand(OUTPUT_TO(Context::*fce)(ARGS_TO...)const,OUTPUT_FROM output,ARGS_FROM...args){
        class FunctionCommand: public ge::core::Command{
          public:
            OUTPUT_FROM _output;
            std::tuple<ARGS_FROM...>_args;
            OUTPUT_TO(Context::*_impl)(ARGS_TO...)const;
            FunctionCommand(OUTPUT_TO(Context::*f)(ARGS_TO...)const,OUTPUT_FROM o,ARGS_FROM...ar){
              assert(this!=nullptr);
              this->_output = o;
              this->_args = std::tuple<ARGS_FROM...>(ar...);
              this->_impl = f;
            }
            virtual void operator()(){
              assert(this!=nullptr);
              callProviderMethod(this->_output,this->_args,this->_impl,typename ge::core::make_index_sequence<sizeof...(ARGS_FROM)>::type{});
            }
        };
        auto ret = std::make_shared<FunctionCommand>(fce,output,args...);
        assert(ret!=nullptr);
        return std::dynamic_pointer_cast<ge::core::Command>(ret);
      }

    //void functions
    template<typename...TO,typename...FROM,std::size_t...I>
      void callProviderMethod(std::tuple<FROM...>const&args,void(Context::*f)(TO...),ge::core::index_sequence<I...>){
        assert(getDefaultContext()!=nullptr);
        auto prov = &*getDefaultContext();
        assert(prov!=nullptr);
        (prov->*f)(ge::core::convertTo<TO,FROM>(std::get<I>(args))...);
      }

    template<typename...TO,typename...FROM>
      std::shared_ptr<ge::core::Command>createCommand(void(Context::*fce)(TO...),FROM...args){
        class FunctionCommand: public ge::core::Command{
          public:
            std::tuple<FROM...>_args;
            void(Context::*_impl)(TO...);
            FunctionCommand(void(Context::*f)(TO...),FROM...ar){
              assert(this!=nullptr);
              this->_args = std::tuple<FROM...>(ar...);
              this->_impl = f;
            }
            virtual void operator()(){
              assert(this!=nullptr);
              callProviderMethod(this->_args,this->_impl,typename ge::core::make_index_sequence<sizeof...(FROM)>::type{});
            }
        };
        auto ret = std::make_shared<FunctionCommand>(fce,args...);
        assert(ret!=nullptr);
        return std::dynamic_pointer_cast<ge::core::Command>(ret);
      }
  }
}


