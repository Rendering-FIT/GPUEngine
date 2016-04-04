#pragma once

#include<geCore/TypeRegister.h>
#include<geCore/statement.h>
#include<geCore/functionRegister.h>

namespace ge{
  namespace core{


    // function: Accessor compositor
    // function: selector of element of Accessor
    //
    class GECORE_EXPORT FunctionFactory: public StatementFactory{
      public:
        FunctionFactory(std::string name = "",unsigned maxUses = 1);
        virtual ~FunctionFactory();
        virtual std::shared_ptr<Statement>operator()(std::shared_ptr<FunctionRegister> const&)=0;
    };

    class GECORE_EXPORT Function: public Statement{
      public:
        using InputIndex = size_t;
        using Ticks      = uint64_t;
      protected:
        std::shared_ptr<FunctionRegister>_functionRegister;
        FunctionRegister::FunctionID     _id;
        bool _inputBindingCheck(InputIndex i,std::shared_ptr<Function>function)const;
      public:
        template<typename TYPE>
          static inline std::shared_ptr<StatementFactory>factory(std::string name){
            class Factory: public FunctionFactory{
              public:
                Factory(std::string name,Uses maxUses = 1):FunctionFactory(name,maxUses){}
                virtual ~Factory(){}
                virtual std::shared_ptr<Statement>operator()(std::shared_ptr<FunctionRegister> const&fr){
                  return std::make_shared<TYPE>(fr,fr->getFunctionId(this->_name));
                }
            };
            return std::make_shared<Factory>(name);
          }
        inline Function(std::shared_ptr<FunctionRegister>const&fr,FunctionRegister::FunctionID id);
        virtual inline ~Function();
        virtual bool bindInput (InputIndex  i   ,std::shared_ptr<Function>function  = nullptr) = 0;
        virtual bool bindOutput(                 std::shared_ptr<Accessor>data      = nullptr) = 0;
        virtual bool hasInput (InputIndex  i   )const = 0;
        virtual bool hasOutput(                )const = 0;
        virtual std::shared_ptr<Accessor>const&getInputData (InputIndex  i    )const = 0;
        virtual std::shared_ptr<Accessor>const&getOutputData(                 )const = 0;
        virtual Ticks getUpdateTicks()const = 0;
        virtual Ticks getCheckTicks ()const = 0;
        virtual void  setUpdateTicks(Ticks ticks) = 0;
        virtual void  setCheckTicks (Ticks ticks) = 0;
        virtual inline std::string doc()const;
        inline TypeRegister::TypeID getInputType (InputIndex  i   )const;
        inline TypeRegister::TypeID getOutputType(                )const;
        inline InputIndex  getNofInputs()const;
        inline std::string getInputName (InputIndex  i   )const;
        inline InputIndex  getInputIndex(std::string name)const;
        inline std::string getOutputName()const;
        inline std::string getName()const;
        inline void setOutputName(std::string name = "");
        inline void setInputName (InputIndex i,std::string name = "");
        inline bool bindInput (std::string name,std::shared_ptr<Function>function  = nullptr);
        inline bool hasInput (std::string name)const;
        inline std::shared_ptr<Accessor>const&getInputData (std::string input)const ;
        inline TypeRegister::TypeID getInputType (std::string name)const;
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

    inline bool Function::bindInput (std::string name,std::shared_ptr<Function>function){
      return this->bindInput(this->getInputIndex(name),function);
    }

    inline bool Function::hasInput (std::string name)const{
      return this->hasInput(this->getInputIndex(name));
    }

    inline std::shared_ptr<Accessor>const&Function::getInputData (std::string input)const{
      return this->getInputData(this->getInputIndex(input));
    }

    inline TypeRegister::TypeID Function::getInputType (std::string name)const{
      return this->getInputType(this->getInputIndex(name));
    }


    class GECORE_EXPORT FunctionInput{
      public:
        bool changed                = false;
        Function::Ticks updateTicks = 0    ;
        inline FunctionInput(
            Function::Ticks updateTicks = 0    ,
            bool            changed     = false){
          this->changed     = changed    ;
          this->updateTicks = updateTicks;
        }
        virtual inline ~FunctionInput(){}
    };

    class GECORE_EXPORT AtomicFunctionInput: public FunctionInput{
      public:
        std::shared_ptr<Function>function    = nullptr;
        AtomicFunctionInput(
            std::shared_ptr<Function>const&fce         = nullptr,
            Function::Ticks                updateTicks = 0      ,
            bool                           changed     = false  );
        virtual ~AtomicFunctionInput();
    };

    class StatementFactory;

    class GECORE_EXPORT AtomicFunction: public Function{
      public:
        using InputList  = std::vector<AtomicFunctionInput>;
        using InputIndex = InputList::size_type;
      protected:
        InputList                _inputs               ;
        unsigned long long       _checkTicks  = 0      ;
        unsigned long long       _updateTicks = 1      ;
        std::shared_ptr<Accessor>_outputData  = nullptr;
      public:
        AtomicFunction(
            std::shared_ptr<FunctionRegister>const&fr,
            FunctionRegister::FunctionID           id);
        AtomicFunction(
            std::shared_ptr<FunctionRegister>const&fr                       ,
            TypeRegister::DescriptionList const&   typeDescription          ,
            std::string                            name            = ""     ,
            std::shared_ptr<StatementFactory>const&factory         = nullptr);
        AtomicFunction(
            std::shared_ptr<FunctionRegister>const&fr    ,
            FunctionRegister::FunctionID           id    ,
            std::shared_ptr<Accessor>const&        output);
        virtual ~AtomicFunction();
        virtual void operator()();
        virtual bool bindInput (InputIndex i,std::shared_ptr<Function>function = nullptr);
        virtual bool bindOutput(             std::shared_ptr<Accessor>data     = nullptr);
        virtual inline bool hasInput (InputIndex  i   )const;
        virtual inline bool hasOutput(                )const;
        virtual inline std::shared_ptr<Accessor>const&getInputData (InputIndex i)const;
        virtual inline std::shared_ptr<Accessor>const&getOutputData(            )const;
        virtual inline Ticks getUpdateTicks()const;
        virtual inline Ticks getCheckTicks ()const;
        virtual inline void setUpdateTicks(Ticks ticks);
        virtual inline void setCheckTicks (Ticks ticks);
        virtual inline std::string doc()const;
      protected:
        void _processInputs();
        virtual bool _do();
        inline bool _inputChanged(InputIndex  i    )const;
        inline bool _inputChanged(std::string input)const;
    };



    inline std::shared_ptr<Accessor>const&AtomicFunction::getOutputData()const{
      return this->_outputData;
    }

    inline bool AtomicFunction::hasInput(InputIndex i)const{
      return this->_inputs[i].function!=nullptr;
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
      return this->_inputs[i].function->getOutputData();
    }

    inline bool AtomicFunction::_inputChanged(InputIndex i)const{
      return this->_inputs[i].changed;
    }

    inline bool AtomicFunction::_inputChanged(std::string input)const{
      return this->_inputChanged(this->_functionRegister->getInputIndex(this->_id,input));
    }

    template<typename OUTPUT,typename...ARGS>
      inline std::vector<ge::core::TypeRegister::DescriptionElement>getDescription(
          std::shared_ptr<ge::core::TypeRegister>const&tr,
          OUTPUT(*)(ARGS...)){
        std::vector<ge::core::TypeRegister::DescriptionElement>result;
        result.push_back(ge::core::TypeRegister::FCE);
        result.push_back(tr->getTypeId(ge::core::TypeRegister::getTypeKeyword<OUTPUT>()));
        result.push_back(sizeof...(ARGS));
        std::vector<ge::core::TypeRegister::DescriptionElement> ar(tr->getTypeId(ge::core::TypeRegister::getTypeKeyword<ARGS>())...);
        for(auto x:ar)result.push_back(x);
        return result;
      }

    template<typename OUTPUT,typename...ARGS,std::size_t...I>
      OUTPUT uber_call(Function*mf,OUTPUT(*FCE)(ARGS...),ge::core::index_sequence<I...>){
#if defined(_MSC_VER) && _MSC_VER<1900
        return FCE((ARGS&...)(*mf->getInputData(I))...);
#else
        return FCE((ARGS&)(*mf->getInputData(I))...);
#endif
      }

    template<typename OUTPUT,typename...ARGS>
      void registerBasicFunction(
          std::shared_ptr<ge::core::FunctionRegister>const&fr,
          const std::string name,
          OUTPUT(*FCE)(ARGS...)){
        static const std::string ss=name;
        auto tr = fr->getTypeRegister();
        auto tid = tr->addType("",getDescription(tr,FCE));

        class BasicFunction: public ge::core::AtomicFunction{
          public:
            BasicFunction(
                std::shared_ptr<ge::core::FunctionRegister>const&f ,
                FunctionRegister::FunctionID                     id):AtomicFunction(f,id){}
            virtual ~BasicFunction(){}
          protected:
            virtual bool _do(){
              typedef OUTPUT(*FF)(ARGS...);
              FF f=reinterpret_cast<FF>(this->_functionRegister->getImplementation(this->_id));
              (OUTPUT&)(*this->getOutputData()) = uber_call(this,f,typename ge::core::make_index_sequence<sizeof...(ARGS)>::type{});
              return true;
            }
        };
        auto f=fr->addFunction(tid,name,ge::core::Function::factory<BasicFunction>(name));
        fr->addImplementation(f,reinterpret_cast<void(*)()>(FCE));
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

