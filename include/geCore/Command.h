#pragma once

#include <geCore/Export.h>
#include <geCore/Functor.h>
#include<iostream>
#include<vector>
#include<map>
#include<memory>

namespace ge{
  namespace core{
    class GECORE_EXPORT Command : public Functor{
      protected:
        virtual void*_getAttribAddress(std::string){return NULL;}
      public:
        virtual void operator()(){};
        virtual ~Command(){};
        template<typename T>T&getAttrib(std::string name){
          return *((T*)this->_getAttribAddress(name));
        }
    };

    class GECORE_EXPORT CommandContainer: public Command
    {
      protected:
        Command**_command;
      public:
        CommandContainer(Command**command=NULL);
        virtual ~CommandContainer();
        virtual void operator()();
        void set(Command**command=NULL);
        Command**get();
        Command* getCommand();
    };


    class GECORE_EXPORT CommandList: public std::vector<Command*>, public Command{
      public:
        CommandList();
        virtual ~CommandList();
        virtual void operator()();
    };

    class GECORE_EXPORT SharedCommandList: public std::vector<std::shared_ptr<Command>>, public Command{
      public:
        SharedCommandList();
        virtual ~SharedCommandList();
        virtual void operator()();
    };

    /*
    class GECORE_EXPORT CommandList: public Command
    {
      protected:
        bool _outOfOrder;
        bool _commutative;
        bool _associative;
        std::vector<Command*> _commands;
        unsigned _commandToExecute;///<index of command that will be executed using step()
      public:
        CommandList(bool outOfOrder=false);
        virtual ~CommandList();
        virtual unsigned add(Command*command);
        Command* getCommand(unsigned i);
        unsigned size();
        virtual void operator()();
        void step();
    };

    class GECORE_EXPORT SharedCommandList: public Command{
      protected:
        std::vector<std::shared_ptr<Command>>_commands;
      public:
        SharedCommandList();
        virtual ~SharedCommandList();
        std::shared_ptr<Command>&getCommand(unsigned i);
        unsigned size();
        virtual void operator()();
    };*/

    class GECORE_EXPORT CommandListWithAccessor: public CommandList{
      protected:
        std::map<std::string,Command*>_name2Command;
      public:
        CommandListWithAccessor();
        virtual Command*operator[](std::string name);
        virtual unsigned add(Command*command,std::string name="");
    };

    class GECORE_EXPORT CommandStatement: public Command
    {
      public:
        bool     isTrue;
    };
    class GECORE_EXPORT CommandIf: public Command
    {
      public:
        CommandStatement *statement;
        Command* trueBranch;
        Command* falseBranch;
        virtual void operator()();
    };
    class GECORE_EXPORT CommandWhile: public Command
    {
      public:
        CommandStatement* statement;
        Command*          body;
        virtual void operator()();
    };
    class GECORE_EXPORT CommandInterpret
    {

    };

  }
}
