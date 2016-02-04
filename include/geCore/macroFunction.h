#pragma once

#include<geCore/function.h>

namespace ge{
  namespace core{
    class MacroFunction: public Function{
      protected:
        std::vector<FunctionInput*>_in;
        Function::Output*_out = nullptr;
        virtual bool _do();
        std::shared_ptr<Function>_outputFce = nullptr;
        virtual inline FunctionInput      &_getInput(unsigned i);
        virtual inline FunctionInput const&_getInput(unsigned i)const;
        virtual inline decltype(_inputs)::size_type _getNofInputs()const;
        virtual inline Output      &_getOutput();
        virtual inline Output const&_getOutput()const;
      public:
        MacroFunction(unsigned inputs,std::shared_ptr<TypeRegister>const&tr);
        virtual ~MacroFunction();
        inline virtual void operator()();
        inline void setFunctionInput(
            unsigned                       i            ,
            std::shared_ptr<Function>const&fce          ,
            unsigned                       fceInput     ,
            std::string                    name     = "");
        inline void setFunctionOutput(
            std::shared_ptr<Function>const&fce            ,
            std::string                    name = "output");
    };


    inline void MacroFunction::operator()(){
      if(!this->_outputFce){
        std::cerr<<"ERROR: MacroFunction::operator()() - ";
        std::cerr<<"there is no output function"<<std::endl;
        return;
      }
      (*this->_outputFce)();
    }

    inline void MacroFunction::setFunctionInput(
        unsigned                       i       ,
        std::shared_ptr<Function>const&fce     ,
        unsigned                       fceInput,
        std::string                    name    ){
      if(name=="")name=this->_genDefaultName(i);
      this->_in[i]=&fce->_getInput(fceInput);
      this->_name2Input[name]=i   ;
      this->_input2Name[i   ]=name;
    }

    inline void MacroFunction::setFunctionOutput(
        std::shared_ptr<Function>const&fce ,
        std::string                    name){
      this->_output.name = name;
      this->_out         = &fce->_output;
      this->_outputFce   = fce;
    }


    inline FunctionInput      &MacroFunction::_getInput(unsigned i){
      return *this->_in[i];
    }

    inline FunctionInput const&MacroFunction::_getInput(unsigned i)const{
      return *this->_in[i];
    }

    inline decltype(MacroFunction::_inputs)::size_type MacroFunction::_getNofInputs()const{
      return this->_in.size();
    }

    inline Function::Output      &MacroFunction::_getOutput(){
      return *this->_out;
    }
    inline Function::Output const&MacroFunction::_getOutput()const{
      return *this->_out;
    }



  }
}
