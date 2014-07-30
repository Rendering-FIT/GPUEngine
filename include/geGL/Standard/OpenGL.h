#ifndef GE_COPENGL_HPP_
#define GE_COPENGL_HPP_

#include <geGL/Export.h>
#include <GL/glew.h>
#include <vector>

namespace ge
{
  namespace ogl
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
        bool alterable;
        std::vector<Command*>commands;
        void apply();
    };
  }
}

#endif//_COPENGL_HPP_
