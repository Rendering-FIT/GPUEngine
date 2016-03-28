#pragma once

#include<geCore/function.h>

namespace ge{
  namespace core{
    class GECORE_EXPORT MacroFunction: public Function{
      public:
        using FceInput = std::tuple<std::shared_ptr<Function>,FunctionRegister::InputIndex>;
        enum FceInputParts{
          FUNCTION = 0,
          INPUT    = 1,
        };
        using FceInputList = std::vector<FceInput>;
      protected:
        std::vector<FceInputList>_inputMapping;
        std::shared_ptr<Function>_outputMapping;
      public:
        MacroFunction(
            std::shared_ptr<FunctionRegister>const&fr,
            FunctionRegister::FunctionID id,
            std::shared_ptr<Function>const&output,
            std::vector<FceInputList>const&inputs);
        ~MacroFunction();
        virtual inline void operator()();
        virtual bool bindInput (InputIndex  i   ,std::shared_ptr<Function>function  = nullptr);
        virtual bool bindOutput(                 std::shared_ptr<Accessor>data      = nullptr);
        virtual bool hasInput (InputIndex  i   )const;
        virtual bool hasOutput(                )const;
        virtual std::shared_ptr<Accessor>const&getInputData (InputIndex  i    )const;
        virtual std::shared_ptr<Accessor>const&getOutputData(                 )const;
        virtual Ticks getUpdateTicks()const;
        virtual Ticks getCheckTicks ()const;
        virtual void  setUpdateTicks(Ticks ticks);
        virtual void  setCheckTicks (Ticks ticks);
        virtual inline std::string doc()const{return "";}
    };

    inline void MacroFunction::operator()(){
      (*this->_outputMapping)();
    }


    /*
       class GECORE_EXPORT MacroFunction: public Function{
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
       MacroFunction(std::shared_ptr<TypeRegister>const&tr,TypeRegister::TypeID id);
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
       */


    class GECORE_EXPORT FunctionNodeFactory: public FunctionFactory{
      protected:
        std::shared_ptr<Statement>_result  = nullptr;
        unsigned                  _maxUses = 0      ;
        unsigned                  _uses    = 0      ;
        bool                      _first   = true   ;
        std::shared_ptr<FunctionFactory>functionFactory = nullptr;
        std::vector<std::shared_ptr<ResourceFactory>>resourceFactories;
        std::vector<std::shared_ptr<FunctionFactory>>inputFactories;
      public:
        FunctionNodeFactory(std::shared_ptr<StatementFactory>const&fac,unsigned maxUses = 1);
        void addResourceFactory(std::shared_ptr<ResourceFactory>const&factory);
        void addInputFactory(std::shared_ptr<StatementFactory>const&factory);
        virtual ~FunctionNodeFactory();
        void reset();
        virtual std::shared_ptr<Statement>operator()(std::shared_ptr<FunctionRegister>const&fr);
    };

    /*
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
       */


  }
}
