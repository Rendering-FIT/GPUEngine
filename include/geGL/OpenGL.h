#ifndef GE_COPENGL_HPP_
#define GE_COPENGL_HPP_

#include <geGL/Export.h>
#include <GL/glew.h>
#include <vector>

namespace ge
{
  namespace gl
  {

    class GEGL_EXPORT Command
    {
      public:
        virtual void apply()=0;
        virtual ~Command(){}
    };


    class GEGL_EXPORT CommandContainer: public Command
    {
      protected:
        Command**_command;
      public:
        CommandContainer(Command**command=NULL);
        ~CommandContainer();
        void apply();
        void set(Command**command=NULL);
        Command**get();
        Command* getCommand();
    };

    class GEGL_EXPORT CommandList: public Command
    {
      protected:
        bool _outOfOrder;
        bool _commutative;
        bool _associative;
        std::vector<Command*> _commands;
        unsigned _commandToExecute;///<index of command that will be executed using step()
      public:
        CommandList(bool outOfOrder=false);
        ~CommandList();
        unsigned add(Command*command);
        Command* getCommand(unsigned i);
        void apply();
        void step();
    };

    class GEGL_EXPORT CommandStatement: public Command
    {
      public:
        bool     isTrue;
    };
    class GEGL_EXPORT CommandIf: public Command
    {
      public:
        CommandStatement *statement;
        Command* trueBranch;
        Command* falseBranch;
        void              apply();
    };
    class GEGL_EXPORT CommandWhile: public Command
    {
      public:
        CommandStatement* statement;
        Command*          body;
        void              apply();
    };
    class GEGL_EXPORT CommandInterpret
    {

    };
  }
}

#endif//_COPENGL_HPP_
