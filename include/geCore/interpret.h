#pragma once

#include<geCore/Command.h>
#include<geCore/TypeRegister.h>

namespace ge{
  namespace core{
    class GECORE_EXPORT Statement: public ge::core::Command{
      public:
        enum Type{
          FUNCTION,
          BODY    ,
          WHILE   ,
          IF      ,
        };
      protected:
        Type _type;
      public:
        Statement(Type type);
        virtual ~Statement();
        virtual void operator()()=0;
    };

    class GECORE_EXPORT Function;
    class GECORE_EXPORT FunctionInput{
      public:
        std::shared_ptr<Function>      function    = nullptr                   ;
        bool                           changed     = false                     ;
        ge::core::TypeRegister::TypeID type        = TypeRegister::UNREGISTERED;
        unsigned long long             updateTicks = 0                         ;
        FunctionInput(
            std::shared_ptr<Function>      fce         = nullptr                             ,
            unsigned long long             updateTicks = 0                                   ,
            bool                           changed     = false                               ,
            ge::core::TypeRegister::TypeID type        = ge::core::TypeRegister::UNREGISTERED);
    };

    class GECORE_EXPORT Function: public Statement{
      protected:
        std::vector<FunctionInput>         _inputs                                  ;
        std::map<unsigned,std::string>     _input2Name                              ;
        std::map<std::string,unsigned>     _name2Input                              ;
        std::shared_ptr<ge::core::Accessor>_output      = nullptr                   ;
        ge::core::TypeRegister::TypeID     _outputType  = TypeRegister::UNREGISTERED;
        std::string                        _outputName  = "output"                  ;
        unsigned long long                 _checkTicks  = 0                         ;
        unsigned long long                 _updateTicks = 1                         ;
        void _setOutput(           ge::core::TypeRegister::TypeID type,std::string name = "");
        void _setInput (unsigned i,ge::core::TypeRegister::TypeID type,std::string name = "");
        virtual bool _do();
        bool _inputChanged(unsigned    i    )const;
        bool _inputChanged(std::string input)const;
      public:
        Function(unsigned n);
        template<typename... ARGS>
          Function(unsigned n,std::shared_ptr<ge::core::Accessor>const&output,ARGS... args);
        template<typename... ARGS>
          Function(unsigned n,ARGS... args);
        virtual ~Function();
        virtual void operator()();
        std::shared_ptr<ge::core::Accessor>const&getOutput()const;
        ge::core::TypeRegister::TypeID getOutputType()const;
        bool hasInput(unsigned    i   )const;
        bool hasInput(std::string name)const;
        bool hasOutput()const;
        virtual void bindInput (unsigned    i   ,std::shared_ptr<Function>function=nullptr);
        virtual void bindInput (std::string name,std::shared_ptr<Function>function=nullptr);
        virtual void bindOutput(std::shared_ptr<ge::core::Accessor>data = nullptr);
        FunctionInput&operator[](unsigned    i    );
        FunctionInput&operator[](std::string input);
        std::shared_ptr<ge::core::Accessor>const&getInputData(unsigned i       )const;
        std::shared_ptr<ge::core::Accessor>const&getInputData(std::string input)const;
      private:
        std::string _genDefaultName(unsigned i)const;
        void _defaultNames(unsigned n);
        void _processInputs();
        template<typename... ARGS>
          void _getInputs(
              std::vector<std::pair<std::shared_ptr<Function>,bool>>&){}
        template<typename... ARGS>
          void _getInputs(
              std::vector<std::pair<std::shared_ptr<Function>,bool>>&inputs,
              std::shared_ptr<Function>const&function0){
            inputs.push_back(std::pair<std::shared_ptr<Function>,bool>(function0,false));
          }
        template<typename... ARGS>
          void _getInputs(
              std::vector<std::pair<std::shared_ptr<Function>,bool>>&inputs,
              std::shared_ptr<Function>const&function0,
              std::shared_ptr<Function>const&function1,
              ARGS...args){
            inputs.push_back(std::pair<std::shared_ptr<Function>,bool>(function0,false));
            this->_getInputs(inputs,function1,args...);
          }
        template<typename... ARGS>
          void _getInputs(
              std::vector<std::pair<std::shared_ptr<Function>,bool>>&inputs,
              std::shared_ptr<Function>const&function,
              bool lazy,
              ARGS...args){
            inputs.push_back(std::pair<std::shared_ptr<Function>,bool>(function,lazy));
            this->_getInputs(inputs,args...);
          }
        template<typename... ARGS>
          void _constructor(unsigned n,std::shared_ptr<Function>const&f,ARGS... args){
            std::vector<std::pair<std::shared_ptr<Function>,bool>>inputs;
            this->_getInputs(inputs,f,args...);
            for(unsigned i=0;i<n;++i){
              if(i<inputs.size())
                this->_inputs.push_back(FunctionInput(inputs[i].first,inputs[i].second,inputs[i].first->getOutput()->getId()));
              else
                this->_inputs.push_back(FunctionInput(nullptr,false,0));
            }
          }
        template<typename... ARGS>
          void _constructor(unsigned n,ge::core::TypeRegister::TypeID type,ARGS... args){
            std::vector<ge::core::TypeRegister::TypeID>types;
            ge::core::argsToVector(types,type,args...);
            for(unsigned i=0;i<n;++i){
              if(i<types.size())
                this->_inputs.push_back(FunctionInput(nullptr,false,types[i]));
              else
                this->_inputs.push_back(FunctionInput(nullptr,false,0));
            }
            this->_defaultNames(n);
          }
    };
    template<typename... ARGS>
      Function::Function(unsigned n,std::shared_ptr<ge::core::Accessor>const&output,ARGS... args):Statement(FUNCTION){
        this->_constructor(n,args...);
        this->bindOutput(output);
      }
    template<typename... ARGS>
      Function::Function(unsigned n,ARGS... args):Statement(FUNCTION){
        this->_constructor(n,args...);
      }

    class GECORE_EXPORT Body: public Statement{
      protected:
        std::vector<std::shared_ptr<Statement>>_statements;
      public:
        Body();
        virtual ~Body();
        void addStatement(std::shared_ptr<Statement>const&statement);
        std::vector<std::shared_ptr<Statement>>::size_type size()const;
        typedef std::vector<std::shared_ptr<Statement>>::const_iterator Iterator;
        Iterator begin()const;
        Iterator end  ()const;
        virtual void operator()();
    };

    class GECORE_EXPORT While: public Statement{
      protected:
        std::shared_ptr<Function >_condition = nullptr;
        std::shared_ptr<Statement>_body      = nullptr;
      public:
        While(std::shared_ptr<Function>const&condition = nullptr,std::shared_ptr<Statement>const&body = nullptr);
        virtual ~While();
        void setBody     (std::shared_ptr<Statement>const&body      = nullptr);
        void setCondition(std::shared_ptr<Function >const&condition = nullptr);
        std::shared_ptr<Function >const&getCondition()const;
        std::shared_ptr<Statement>const&getBody     ()const;
        virtual void operator()();
    };

    class GECORE_EXPORT If: public Statement{
      protected:
        std::shared_ptr<Function >_condition = nullptr;
        std::shared_ptr<Statement>_trueBody  = nullptr;
        std::shared_ptr<Statement>_falseBody = nullptr;
      public:
        If(
            std::shared_ptr<Function >const&condition = nullptr,
            std::shared_ptr<Statement>const&trueBody  = nullptr,
            std::shared_ptr<Statement>const&falseBody = nullptr);
        virtual ~If();
        void setCondition(std::shared_ptr<Function >const&condition = nullptr);
        void setTrueBody (std::shared_ptr<Statement>const&trueBody  = nullptr);
        void setFalseBody(std::shared_ptr<Statement>const&falseBody = nullptr);
        std::shared_ptr<Function >const&getCondition()const;
        std::shared_ptr<Statement>const&getTrueBody ()const;
        std::shared_ptr<Statement>const&getFalseBody()const;
        virtual void operator()();
    };
  }
}
