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

    class GECORE_EXPORT Box: public Statement{
      public:
        using InputIndex = size_t;
      protected:
        std::map<InputIndex,std::string>_input2Name;
        std::map<std::string,InputIndex>_name2Input;
        std::string _outputName                    ;
      public:
        inline Box():Statement(FUNCTION){}
        virtual inline ~Box(){}
        virtual bool bindInput (InputIndex  i   ,std::shared_ptr<Function>function = nullptr)=0;
        virtual bool bindInput (std::string name,std::shared_ptr<Function>function = nullptr)=0;
        virtual bool bindOutput(                 std::shared_ptr<Accessor>data     = nullptr)=0;
        virtual bool hasInput (InputIndex  i   )const=0;
        virtual bool hasInput (std::string name)const=0;
        virtual bool hasOutput(                )const=0;
        virtual std::shared_ptr<Accessor>const&getInputData (InputIndex  i    )const;
        virtual std::shared_ptr<Accessor>const&getInputData (std::string input)const;
        virtual std::shared_ptr<Accessor>const&getOutputData(                 )const;
        virtual TypeRegister::TypeID getInputType (InputIndex  i   )const;
        virtual TypeRegister::TypeID getInputType (std::string name)const;
        virtual TypeRegister::TypeID getOutputType(                )const;
        virtual std::string doc()const;
        inline InputIndex  getNofInputs()const;
        inline std::string getInputName (InputIndex  i   )const;
        inline InputIndex  getInputIndex(std::string name)const;
        inline std::string getOutputName()const;
    };

    //class MacroFunction;
    class GECORE_EXPORT Function: public Statement{
      public:
        using InputList = std::vector<FunctionInput>;
        using InputIndex = InputList::size_type;
      protected:
//        friend class MacroFunction;
        std::shared_ptr<TypeRegister>   _typeRegister   ;
        std::string                     _name           ;
        InputList                       _inputs         ;
        std::map<InputIndex,std::string>_input2Name     ;
        std::map<std::string,InputIndex>_name2Input     ;
        unsigned long long              _checkTicks  = 0;
        unsigned long long              _updateTicks = 1;
        struct Output{
          std::shared_ptr<Accessor>data = nullptr ;
          std::string              name = "output";
        }_output;
        std::string _genDefaultName(InputIndex i)const;
        TypeRegister::TypeID _fceType;
      public:
        Function(std::shared_ptr<TypeRegister>const&tr,TypeRegister::TypeID type,std::string name = "");
        Function(std::shared_ptr<TypeRegister>const&tr,TypeRegister::DescriptionList const&typeDescription,std::string name = "");
        virtual ~Function();
        virtual void operator()();
        inline std::shared_ptr<Accessor>const&getOutputData()const;
        inline TypeRegister::TypeID getOutputType()const;
        inline std::string getOutputName()const;
        inline bool hasInput(InputIndex  i   )const;
        inline bool hasInput(std::string name)const;
        inline bool hasOutput()const;
        bool bindInput (InputIndex  i   ,std::shared_ptr<Function>function=nullptr);
        bool bindInput (std::string name,std::shared_ptr<Function>function=nullptr);
        bool bindOutput(std::shared_ptr<ge::core::Accessor>data = nullptr);
        inline std::shared_ptr<Accessor>const&getInputData(InputIndex  i    )const;
        inline std::shared_ptr<Accessor>const&getInputData(std::string input)const;
        inline TypeRegister::TypeID getInputType(InputIndex  i   )const;
        inline TypeRegister::TypeID getInputType(std::string name)const;
        inline InputIndex getNofInputs()const;
        virtual inline std::string getInputName (InputIndex  i   )const;
        virtual inline InputIndex  getInputIndex(std::string name)const;
        virtual inline std::string doc()const;
      protected:
        void _defaultNames(InputIndex n);
        void _processInputs();
        void _setOutput(std::string name = "");
        void _setInput (InputIndex i,std::string name = "");
        virtual bool _do();
        inline bool _inputChanged(InputIndex  i    )const;
        inline bool _inputChanged(std::string input)const;
        inline FunctionInput      &_getInput(InputIndex i);
        inline FunctionInput const&_getInput(InputIndex i)const;
        inline InputIndex _getNofInputs()const;
        inline Output      &_getOutput();
        inline Output const&_getOutput()const;
    };



    class GECORE_EXPORT FunctionFactory: public StatementFactory{
      public:
        virtual ~FunctionFactory();
        virtual std::shared_ptr<Statement>operator()(SharedTypeRegister const&)=0;
    };

    inline std::shared_ptr<Accessor>const&Function::getOutputData()const{
      /*
      ___;
      std::cerr<<this<<std::endl;
      std::cerr<<this->_name<<std::endl;
      if(this->_output.data==nullptr)___;
      ___;
      return this->_output.data;
      // */
      return this->_getOutput().data;
    }

    inline ge::core::TypeRegister::TypeID Function::getOutputType()const{
      return this->_typeRegister->getFceReturnTypeId(this->_fceType);
    }

    inline std::string Function::getOutputName()const{
      return this->_getOutput().name;
    }

    inline bool Function::hasInput(InputIndex i)const{
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

    inline std::shared_ptr<Accessor>const&Function::getInputData(InputIndex i)const{
      return this->_getInput(i).function->getOutputData();
    }

    inline std::shared_ptr<Accessor>const&Function::getInputData(std::string input)const{
      return this->getInputData(this->_name2Input.find(input)->second);
    }

    inline TypeRegister::TypeID Function::getInputType(InputIndex i)const{
      return this->_typeRegister->getFceArgTypeId(this->_fceType,i);
    }

    inline TypeRegister::TypeID Function::getInputType(std::string name)const{
      return this->_typeRegister->getFceArgTypeId(this->_fceType,this->getInputIndex(name));
    }

    inline Function::InputIndex Function::getNofInputs()const{
      return this->_inputs.size();
    }

    inline bool Function::_inputChanged(InputIndex i)const{
      return this->_getInput(i).changed;
    }

    inline bool Function::_inputChanged(std::string input)const{
      return this->_inputChanged(this->_name2Input.find(input)->second);
    }

    inline FunctionInput&Function::_getInput(InputIndex i){
      return this->_inputs[i];
    }

    inline FunctionInput const&Function::_getInput(InputIndex i)const{
      return this->_inputs[i];
    }

    inline Function::InputIndex Function::_getNofInputs()const{
      return this->_inputs.size();
    }

    inline Function::Output      &Function::_getOutput(){
      return this->_output;
    }

    inline Function::Output const&Function::_getOutput()const{
      return this->_output;
    }

    inline std::string Function::getInputName(InputIndex i)const{
      if(i>=this->_getNofInputs()){
        std::cerr<<"ERROR: "<<this->_name<<"::getInputName("<<i<<") - ";
        std::cerr<<"input out of range"<<std::endl;
        return "";
      }
      return this->_input2Name.find(i)->second;
    }

    inline Function::InputIndex Function::getInputIndex(std::string name)const{
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

