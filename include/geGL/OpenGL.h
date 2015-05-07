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
      public:
        Command     * command;
        bool          ref;
        void reset();
        void free ();
        void apply();
    };


    class GEGL_EXPORT CommandList: public Command
    {
      protected:
        bool outOfOrder;
        bool commutative;
        bool associative;
        std::vector<Command*> commands;
        unsigned commandToExecute;///<index of command that will be executed using step()
      public:
        /**
         * @brief constructs command list
         *
         * @param outOfOrder if it is set to true, commands can be executed out of order
         */
        CommandList(bool outOfOrder=false);
        void apply();
        void step();
        void add(Command*command);
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
        Command          *trueBranch;
        Command          *falseBranch;
        void              apply();
    };
    class GEGL_EXPORT CommandWhile: public Command
    {
      public:
        CommandStatement *statement;
        Command          *body;
        void              apply();
    };
    class GEGL_EXPORT CommandInterpret
    {

    };
  }
}

#endif//_COPENGL_HPP_
