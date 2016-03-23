#pragma once

#include<geCore/TypeRegister.h>
#include<geCore/statement.h>

namespace ge{
  namespace core{
    class GECORE_EXPORT Function;
    class GECORE_EXPORT FunctionInput{
      public:
        std::shared_ptr<Function>function    = nullptr;
        bool                     changed     = false  ;
        unsigned long long       updateTicks = 0      ;
        FunctionInput(
            std::shared_ptr<Function>fce         = nullptr,
            unsigned long long       updateTicks = 0      ,
            bool                     changed     = false  );
    };


    // function: Accessor compositor
    // function: selector of element of Accessor
    //

    class MacroFunction;
    class GECORE_EXPORT Function: public Statement{
      protected:
        friend class MacroFunction;
        std::shared_ptr<TypeRegister> _typeRegister   ;
        std::string                   _name           ;
        std::vector<FunctionInput>    _inputs         ;
        std::map<unsigned,std::string>_input2Name     ;
        std::map<std::string,unsigned>_name2Input     ;
        unsigned long long            _checkTicks  = 0;
        unsigned long long            _updateTicks = 1;
        struct Output{
          std::shared_ptr<Accessor>data = nullptr ;
          std::string              name = "output";
        }_output;
        std::string _genDefaultName(unsigned i)const;
        TypeRegister::TypeID _fceType;
      public:
        Function(std::shared_ptr<TypeRegister>const&tr,TypeRegister::TypeID type,std::string name = "");
        Function(std::shared_ptr<TypeRegister>const&tr,TypeRegister::DescriptionList const&typeDescription,std::string name = "");
        virtual ~Function();
        virtual void operator()();
        inline std::shared_ptr<Accessor>const&getOutput()const;
        inline TypeRegister::TypeID getOutputType()const;
        inline std::string getOutputName()const;
        inline bool hasInput(unsigned    i   )const;
        inline bool hasInput(std::string name)const;
        inline bool hasOutput()const;
        bool bindInput (unsigned    i   ,std::shared_ptr<Function>function=nullptr);
        bool bindInput (std::string name,std::shared_ptr<Function>function=nullptr);
        bool bindOutput(std::shared_ptr<ge::core::Accessor>data = nullptr);
        inline std::shared_ptr<Accessor>const&getInputData(unsigned i       )const;
        inline std::shared_ptr<Accessor>const&getInputData(std::string input)const;
        inline TypeRegister::TypeID getInputType(unsigned    i   )const;
        inline TypeRegister::TypeID getInputType(std::string name)const;
        inline decltype(_inputs)::size_type getNofInputs()const;
        virtual inline std::string getInputName (unsigned    i   )const;
        virtual inline unsigned    getInputIndex(std::string name)const;
        virtual inline std::string doc()const;
      protected:
        void _defaultNames(unsigned n);
        void _processInputs();
        void _setOutput(std::string name = "");
        void _setInput (unsigned i,std::string name = "");
        virtual bool _do();
        inline bool _inputChanged(unsigned    i    )const;
        inline bool _inputChanged(std::string input)const;
        virtual inline FunctionInput      &_getInput(unsigned i);
        virtual inline FunctionInput const&_getInput(unsigned i)const;
        virtual inline decltype(_inputs)::size_type _getNofInputs()const;
        virtual inline Output      &_getOutput();
        virtual inline Output const&_getOutput()const;
    };



    class FunctionFactory: public StatementFactory{
      public:
        virtual ~FunctionFactory();
        virtual std::shared_ptr<Statement>operator()(SharedTypeRegister const&)=0;
    };

    inline std::shared_ptr<Accessor>const&Function::getOutput()const{
      return this->_getOutput().data;
    }

    inline ge::core::TypeRegister::TypeID Function::getOutputType()const{
      return this->_typeRegister->getFceReturnTypeId(this->_fceType);
    }

    inline std::string Function::getOutputName()const{
      return this->_getOutput().name;
    }

    inline bool Function::hasInput(unsigned i)const{
      return this->_getInput(i).function!=nullptr;
    }

    inline bool Function::hasInput(std::string name)const{
      return this->hasInput(this->getInputIndex(name));
    }

    inline std::string Function::doc()const{
      return"";
    }

    inline bool Function::hasOutput()const{
      return this->_getOutput().data!=nullptr;
    }

    inline std::shared_ptr<Accessor>const&Function::getInputData(unsigned i       )const{
      return this->_getInput(i).function->getOutput();
    }

    inline std::shared_ptr<Accessor>const&Function::getInputData(std::string input)const{
      return this->getInputData(this->_name2Input.find(input)->second);
    }

    inline TypeRegister::TypeID Function::getInputType(unsigned    i   )const{
      return this->_typeRegister->getFceArgTypeId(this->_fceType,i);
    }

    inline TypeRegister::TypeID Function::getInputType(std::string name)const{
      return this->_typeRegister->getFceArgTypeId(this->_fceType,this->getInputIndex(name));
    }

    inline decltype(Function::_inputs)::size_type Function::getNofInputs()const{
      return this->_inputs.size();
    }

    inline bool Function::_inputChanged(unsigned i)const{
      return this->_getInput(i).changed;
    }

    inline bool Function::_inputChanged(std::string input)const{
      return this->_inputChanged(this->_name2Input.find(input)->second);
    }

    inline FunctionInput&Function::_getInput(unsigned i){
      return this->_inputs[i];
    }

    inline FunctionInput const&Function::_getInput(unsigned i)const{
      return this->_inputs[i];
    }

    inline decltype(Function::_inputs)::size_type Function::_getNofInputs()const{
      return this->_inputs.size();
    }

    inline Function::Output      &Function::_getOutput(){
      return this->_output;
    }

    inline Function::Output const&Function::_getOutput()const{
      return this->_output;
    }

    inline std::string Function::getInputName(unsigned i)const{
      if(i>=this->_getNofInputs()){
        std::cerr<<"ERROR: "<<this->_name<<"::getInputName("<<i<<") - ";
        std::cerr<<"input out of range"<<std::endl;
        return "";
      }
      return this->_input2Name.find(i)->second;
    }

    inline unsigned Function::getInputIndex(std::string name)const{
      auto ii=this->_name2Input.find(name);
      if(ii==this->_name2Input.end()){
        std::cerr<<"ERROR: "<<this->_name<<"::getInputIndex(\""<<name<<"\") - ";
        std::cerr<<"there is no input with that name"<<std::endl;
        return -1;
      }
      return ii->second;
    }



  }
}

#define BEGIN_INTERPRET_FUNCTION_HPP(NAME)\
  class GECORE_EXPORT NAME: public ge::core::Function{\
    protected:\
              bool _do();\
    public:\
           static inline std::string name(){return #NAME;}\
    static inline std::shared_ptr<ge::core::Function> sharedInstance(std::shared_ptr<ge::core::TypeRegister>const&tr){\
      return std::make_shared<NAME>(tr);\
    }\
    NAME(std::shared_ptr<ge::core::TypeRegister>const&typeRegister)
#define END_INTERPRET_FUNCTION_HPP()\
  }

#define NEW_INTERPRET_FUNCTION_HPP(NAME)\
  BEGIN_INTERPRET_FUNCTION_HPP(NAME);\
END_INTERPRET_FUNCTION_HPP()

#define BEGIN_INTERPRET_FUNCTION_CPP(NAME,TYPE)\
  NAME::NAME(std::shared_ptr<ge::core::TypeRegister>const&tr):Function(tr,TYPE,NAME::name()){\

#define MID_INTERPRET_FUNCTION_CPP(NAME)\
  }\
bool NAME::_do(){

#define END_INTERPRET_FUNCTION_CPP()\
}

#define NEW_INTERPRET_FUNCTION_CPP(NAME,...)\
  BEGIN_INTERPRET_FUNCTION_CPP(NAME,__VA_ARGS__)\
BODY_OF_INTERPRET_FUNCTION\
END_INTERPRET_FUNCTION_CPP()

