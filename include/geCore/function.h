#pragma once

#include<geCore/TypeRegister.h>
#include<geCore/statement.h>
#include<geCore/functionRegister.h>

namespace ge{
  namespace core{


    // function: Accessor compositor
    // function: selector of element of Accessor
    //

    class GECORE_EXPORT Function: public Statement{
      public:
        using InputIndex = size_t;
        using Ticks      = uint64_t;
      protected:
        //std::map<InputIndex,std::string>_input2Name  ;
        //std::map<std::string,InputIndex>_name2Input  ;
        //std::string                     _outputName  ;
        //std::string                     _name        ;
        //TypeRegister::TypeID            _fceType     ;
        //std::shared_ptr<TypeRegister>   _typeRegister;
        //std::string _genDefaultName(InputIndex i)const;
        std::shared_ptr<FunctionRegister>_functionRegister;
        FunctionRegister::FunctionID     _id;
      public:
        inline Function(std::shared_ptr<FunctionRegister>const&fr,FunctionRegister::FunctionID id);
        virtual inline ~Function();
        virtual bool bindInput (InputIndex  i   ,std::shared_ptr<Function>function  = nullptr) = 0;
        virtual bool bindInput (std::string name,std::shared_ptr<Function>function  = nullptr) = 0;
        virtual bool bindOutput(                 std::shared_ptr<Accessor>data      = nullptr) = 0;
        virtual bool hasInput (InputIndex  i   )const = 0;
        virtual bool hasInput (std::string name)const = 0;
        virtual bool hasOutput(                )const = 0;
        virtual std::shared_ptr<Accessor>const&getInputData (InputIndex  i    )const = 0;
        virtual std::shared_ptr<Accessor>const&getInputData (std::string input)const = 0;
        virtual std::shared_ptr<Accessor>const&getOutputData(                 )const = 0;
        virtual Ticks getUpdateTicks()const = 0;
        virtual Ticks getCheckTicks ()const = 0;
        virtual void  setUpdateTicks(Ticks ticks) = 0;
        virtual void  setCheckTicks (Ticks ticks) = 0;
        virtual inline std::string doc()const;
        inline TypeRegister::TypeID getInputType (InputIndex  i   )const;
        inline TypeRegister::TypeID getInputType (std::string name)const;
        inline TypeRegister::TypeID getOutputType(                )const;
        inline InputIndex  getNofInputs()const;
        inline std::string getInputName (InputIndex  i   )const;
        inline InputIndex  getInputIndex(std::string name)const;
        inline std::string getOutputName()const;
        inline std::string getName()const;
        inline void setOutputName(std::string name = "");
        inline void setInputName (InputIndex i,std::string name = "");
    };

    inline Function::Function(
        std::shared_ptr<FunctionRegister>const&fr,
        FunctionRegister::FunctionID id):Statement(FUNCTION){
      this->_functionRegister = fr;
      this->_id = id;
    }

    inline Function::~Function(){
    }

    inline std::string Function::doc()const{
      return"";
    }

    inline TypeRegister::TypeID Function::getInputType(InputIndex i)const{
      return this->_functionRegister->getInputType(this->_id,i);
    }

    inline TypeRegister::TypeID Function::getInputType(std::string name)const{
      return this->getInputType(this->_functionRegister->getInputIndex(this->_id,name));
    }

    inline ge::core::TypeRegister::TypeID Function::getOutputType()const{
      return this->_functionRegister->getOutputType(this->_id);
    }

    inline Function::InputIndex Function::getNofInputs()const{
      return this->_functionRegister->getNofInputs(this->_id);
    }

    inline std::string Function::getInputName(InputIndex i)const{
      return this->_functionRegister->getInputName(this->_id,i);
    }

    inline Function::InputIndex Function::getInputIndex(std::string name)const{
      return this->_functionRegister->getInputIndex(this->_id,name);
    }

    inline std::string Function::getOutputName()const{
      return this->_functionRegister->getOutputName(this->_id);
    }

    inline std::string Function::getName()const{
      return this->_functionRegister->getName(this->_id);
    }

    inline void Function::setInputName(InputIndex i,std::string name){
      this->_functionRegister->setInputName(this->_id,i,name);
    }

    inline void Function::setOutputName(std::string name){
      this->_functionRegister->setOutputName(this->_id,name);
    }


    class GECORE_EXPORT AtomicFunctionInput{
      public:
        std::shared_ptr<Function>function    = nullptr;
        bool                     changed     = false  ;
        Function::Ticks          updateTicks = 0      ;
        AtomicFunctionInput(
            std::shared_ptr<Function>const&fce         = nullptr,
            Function::Ticks                updateTicks = 0      ,
            bool                           changed     = false  );
    };

    class StatementFactory;

    class GECORE_EXPORT AtomicFunction: public Function{
      public:
        using InputList = std::vector<AtomicFunctionInput>;
        using InputIndex = InputList::size_type;
      protected:
        InputList                _inputs         ;
        unsigned long long       _checkTicks  = 0;
        unsigned long long       _updateTicks = 1;
        std::shared_ptr<Accessor>_outputData = nullptr ;
      public:
        AtomicFunction(std::shared_ptr<FunctionRegister>const&fr,FunctionRegister::FunctionID id);
        AtomicFunction(
            std::shared_ptr<FunctionRegister>const&fr,
            TypeRegister::DescriptionList const&typeDescription,
            std::string name = "",
            std::shared_ptr<StatementFactory>const&factory = nullptr);
        virtual ~AtomicFunction();
        virtual void operator()();
        virtual bool bindInput (InputIndex  i   ,std::shared_ptr<Function>function = nullptr);
        virtual bool bindInput (std::string name,std::shared_ptr<Function>function = nullptr);
        virtual bool bindOutput(                 std::shared_ptr<Accessor>data     = nullptr);
        virtual inline bool hasInput (InputIndex  i   )const;
        virtual inline bool hasInput (std::string name)const;
        virtual inline bool hasOutput(                )const;
        virtual inline std::shared_ptr<Accessor>const&getInputData (InputIndex  i    )const;
        virtual inline std::shared_ptr<Accessor>const&getInputData (std::string input)const;
        virtual inline std::shared_ptr<Accessor>const&getOutputData(                 )const;
        virtual inline Ticks getUpdateTicks()const;
        virtual inline Ticks getCheckTicks ()const;
        virtual inline void  setUpdateTicks(Ticks ticks);
        virtual inline void  setCheckTicks (Ticks ticks);
        virtual inline std::string doc()const;
      protected:
        void _defaultNames(InputIndex n);
        void _processInputs();
        virtual bool _do();
        inline bool _inputChanged(InputIndex  i    )const;
        inline bool _inputChanged(std::string input)const;
        inline AtomicFunctionInput      &_getInput(InputIndex i);
        inline AtomicFunctionInput const&_getInput(InputIndex i)const;
        inline InputIndex _getNofInputs()const;
    };



    class GECORE_EXPORT FunctionFactory: public StatementFactory{
      public:
        virtual ~FunctionFactory();
        virtual std::shared_ptr<Statement>operator()(std::shared_ptr<FunctionRegister> const&)=0;
    };

    inline std::shared_ptr<Accessor>const&AtomicFunction::getOutputData()const{
      return this->_outputData;
    }

    inline bool AtomicFunction::hasInput(InputIndex i)const{
      return this->_getInput(i).function!=nullptr;
    }

    inline bool AtomicFunction::hasInput(std::string name)const{
      return this->hasInput(this->getInputIndex(name));
    }

    inline Function::Ticks AtomicFunction::getUpdateTicks()const{
      return this->_updateTicks;
    }

    inline Function::Ticks AtomicFunction::getCheckTicks ()const{
      return this->_checkTicks;
    }

    inline void AtomicFunction::setUpdateTicks(Function::Ticks ticks){
      this->_checkTicks = ticks;
    }

    inline void AtomicFunction::setCheckTicks(Ticks ticks){
      this->_updateTicks = ticks;
    }

    inline std::string AtomicFunction::doc()const{
      return"";
    }

    inline bool AtomicFunction::hasOutput()const{
      return this->_outputData!=nullptr;
    }

    inline std::shared_ptr<Accessor>const&AtomicFunction::getInputData(InputIndex i)const{
      return this->_getInput(i).function->getOutputData();
    }

    inline std::shared_ptr<Accessor>const&AtomicFunction::getInputData(std::string input)const{
      return this->getInputData(this->_functionRegister->getInputIndex(this->_id,input));
    }

    inline bool AtomicFunction::_inputChanged(InputIndex i)const{
      return this->_getInput(i).changed;
    }

    inline bool AtomicFunction::_inputChanged(std::string input)const{
      return this->_inputChanged(this->_functionRegister->getInputIndex(this->_id,input));
    }

    inline AtomicFunctionInput&AtomicFunction::_getInput(InputIndex i){
      return this->_inputs[i];
    }

    inline AtomicFunctionInput const&AtomicFunction::_getInput(InputIndex i)const{
      return this->_inputs[i];
    }

    inline AtomicFunction::InputIndex AtomicFunction::_getNofInputs()const{
      return this->_inputs.size();
    }
  }
}

#define BEGIN_INTERPRET_FUNCTION_HPP(NAME)\
  class GECORE_EXPORT NAME: public ge::core::AtomicFunction{\
    protected:\
              bool _do();\
    public:\
           static inline std::string name(){return #NAME;}\
    static inline std::shared_ptr<ge::core::AtomicFunction> sharedInstance(std::shared_ptr<ge::core::TypeRegister>const&tr){\
      return std::make_shared<NAME>(tr);\
    }\
    NAME(std::shared_ptr<ge::core::TypeRegister>const&typeRegister)
#define END_INTERPRET_FUNCTION_HPP()\
  }

#define NEW_INTERPRET_FUNCTION_HPP(NAME)\
  BEGIN_INTERPRET_FUNCTION_HPP(NAME);\
END_INTERPRET_FUNCTION_HPP()

#define BEGIN_INTERPRET_FUNCTION_CPP(NAME,TYPE)\
  NAME::NAME(std::shared_ptr<ge::core::TypeRegister>const&tr):AtomicFunction(tr,TYPE,NAME::name()){\

#define MID_INTERPRET_FUNCTION_CPP(NAME)\
  }\
bool NAME::_do(){

#define END_INTERPRET_FUNCTION_CPP()\
}

#define NEW_INTERPRET_FUNCTION_CPP(NAME,...)\
  BEGIN_INTERPRET_FUNCTION_CPP(NAME,__VA_ARGS__)\
BODY_OF_INTERPRET_FUNCTION\
END_INTERPRET_FUNCTION_CPP()

