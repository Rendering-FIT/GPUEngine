#pragma once

#include<geCore/TypeRegister.h>
#include<geCore/Statement.h>
#include<geCore/FunctionRegister.h>
#include<geCore/FunctionFactory.h>

namespace ge{
  namespace core{


    // function: Accessor compositor
    // function: selector of element of Accessor

    class GECORE_EXPORT Function: public Statement{
      public:
        using InputIndex = size_t;
        using Ticks      = uint64_t;
      protected:
        std::shared_ptr<FunctionRegister>_functionRegister;
        FunctionRegister::FunctionID     _id;
        bool _inputBindingCheck(InputIndex i,std::shared_ptr<Function>function)const;
      public:
        inline Function(std::shared_ptr<FunctionRegister>const&fr,FunctionRegister::FunctionID id);
        virtual inline ~Function();
        inline std::shared_ptr<FunctionRegister>const&getFunctionRegister()const;
        inline FunctionRegister::FunctionID getId()const;
        virtual bool bindInput (InputIndex i,std::shared_ptr<Function>const&function = nullptr) = 0;
        virtual bool bindOutput(             std::shared_ptr<Accessor>const&data     = nullptr) = 0;
        virtual bool hasInput (InputIndex i)const = 0;
        virtual bool hasOutput(            )const = 0;
        virtual std::shared_ptr<Accessor>const&getInputData (InputIndex i)const = 0;
        virtual std::shared_ptr<Accessor>const&getOutputData(            )const = 0;
        virtual Ticks getUpdateTicks()const = 0;
        virtual Ticks getCheckTicks ()const = 0;
        virtual void  setUpdateTicks(Ticks ticks) = 0;
        virtual void  setCheckTicks (Ticks ticks) = 0;
        virtual std::shared_ptr<Function>const&getInputFunction(InputIndex i)const = 0;
        virtual inline std::string doc()const;
        inline TypeRegister::TypeID getInputType (InputIndex i)const;
        inline TypeRegister::TypeID getOutputType(            )const;
        inline InputIndex  getNofInputs()const;
        inline InputIndex  getInputIndex(std::string const&name)const;
        inline bool bindInput(std::string const&name,std::shared_ptr<Function>const&function = nullptr);
        inline bool hasInput (std::string const&name)const;
        inline std::shared_ptr<Accessor>const&getInputData (std::string const&input)const ;
        inline TypeRegister::TypeID getInputType (std::string const&name)const;
        inline std::shared_ptr<Function>const&getInputFunction(std::string const&name)const;
    };

    inline Function::Function(
        std::shared_ptr<FunctionRegister>const&fr,
        FunctionRegister::FunctionID id):Statement(FUNCTION){
      this->_functionRegister = fr;
      this->_id = id;
    }

    inline Function::~Function(){
    }

    std::shared_ptr<FunctionRegister>const&Function::getFunctionRegister()const{
      return this->_functionRegister;
    }

    FunctionRegister::FunctionID Function::getId()const{
      return this->_id;
    }

    inline std::string Function::doc()const{
      assert(this!=nullptr);
      return"";
    }

    inline TypeRegister::TypeID Function::getInputType(InputIndex i)const{
      assert(this!=nullptr);
      assert(this->_functionRegister!=nullptr);
      return this->_functionRegister->getInputType(this->_id,i);
    }

    inline ge::core::TypeRegister::TypeID Function::getOutputType()const{
      assert(this!=nullptr);
      assert(this->_functionRegister!=nullptr);
      return this->_functionRegister->getOutputType(this->_id);
    }

    inline Function::InputIndex Function::getNofInputs()const{
      assert(this!=nullptr);
      assert(this->_functionRegister!=nullptr);
      return this->_functionRegister->getNofInputs(this->_id);
    }

    inline Function::InputIndex Function::getInputIndex(std::string const&name)const{
      assert(this!=nullptr);
      assert(this->_functionRegister!=nullptr);
      return this->_functionRegister->getInputIndex(this->_id,name);
    }

    inline bool Function::bindInput (std::string const&name,std::shared_ptr<Function>const&function){
      assert(this!=nullptr);
      return this->bindInput(this->getInputIndex(name),function);
    }

    inline bool Function::hasInput (std::string const&name)const{
      assert(this!=nullptr);
      return this->hasInput(this->getInputIndex(name));
    }

    inline std::shared_ptr<Accessor>const&Function::getInputData (std::string const&input)const{
      assert(this!=nullptr);
      return this->getInputData(this->getInputIndex(input));
    }

    inline TypeRegister::TypeID Function::getInputType (std::string const&name)const{
      assert(this!=nullptr);
      return this->getInputType(this->getInputIndex(name));
    }

    inline std::shared_ptr<Function>const&Function::getInputFunction(std::string const&name)const{
      assert(this!=nullptr);
      return this->getInputFunction(this->getInputIndex(name));
    }



#define DEFINE_FUNCTION_TYPE_KEYWORD(fce,name)\
    namespace ge{\
      namespace core{\
        template<>std::string TypeRegister::getTypeKeyword<decltype(&fce)>(){return name;}\
      }\
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

