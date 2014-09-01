#ifndef GE_COPENGL_HPP_
#define GE_COPENGL_HPP_

#include <geGL/Export.h>
#include <GL/glew.h>
#include <vector>

namespace ge
{
  namespace gl
  {

    class GE_EXPORT Command
    {
      public:
        virtual void apply()=0;
    };


    class GE_EXPORT CommandContainer: public Command
    {
      public:
        Command     * command;
        bool          ref;
        void reset();
        void free ();
        void apply();
    };


    class GE_EXPORT CommandList: public Command
    {
      public:
        /**
         * @brief constructs command list
         *
         * @param outOfOrder if it is set to true, commands can be executed out of order
         */
        CommandList(bool outOfOrder);
        void apply();

        /*virtual unsigned addCommand(Command* command);
          virtual unsigned insertCommand(Command* command, unsigned after);
          virtual void clear();
          virtual void erase();*/

        bool outOfOrder; ///<
        std::vector<Command*> commands;

        /*std::vector<Command*>& getCommands() { return _commands; }
          bool getAlterable() const { return _alterable; }
          void setAlterable(bool val) { _alterable = val; }*/
      protected:
    };
    class GE_EXPORT CommandStatement: public Command
    {
      public:
        bool     isTrue;
    };
    class GE_EXPORT CommandIf: public Command
    {
      public:
        CommandStatement *statement;
        Command          *trueBranch;
        Command          *falseBranch;
        void              apply();
    };
    class GE_EXPORT CommandWhile: public Command
    {
      public:
        CommandStatement *statement;
        Command          *body;
        void              apply();
    };
  }
}

#endif//_COPENGL_HPP_
