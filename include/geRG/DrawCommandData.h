#ifndef GE_SG_DRAW_COMMAND_DATA_H
#define GE_SG_DRAW_COMMAND_DATA_H

#include <geSG/Export.h>

namespace ge
{
   namespace sg
   {

      struct GE_EXPORT DrawCommandData {
         unsigned _glMode;
         unsigned _count;
         unsigned _firstIndex;
         unsigned _baseVertex;
      };

   }
}

#endif // GE_SG_DRAW_COMMAND_DATA_H
