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
  }
}

#endif//_COPENGL_HPP_
