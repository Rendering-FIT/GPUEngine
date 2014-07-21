#ifndef _COPENGL_HPP_
#define _COPENGL_HPP_

#include<GL/glew.h>
#include<vector>

namespace ge
{
  namespace ogl
  {
    class Command
    {
      public:
        virtual void apply()=0;
    };
    class CommandContainer: public Command
    {
      public:
        Command     * command;
        bool          ref;
        void init ();
        void free ();
        void apply();
    };
    class CommandList: public Command
    {
      public:
        bool alterable;
        std::vector<Command*>commands;
        void apply();
    };
  }
}

#endif//_COPENGL_HPP_
