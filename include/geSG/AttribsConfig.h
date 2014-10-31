#ifndef GE_SG_ATTRIBS_CONFIG_H
#define GE_SG_ATTRIBS_CONFIG_H

#include <vector>
#include <geSG/Export.h>
#include <geSG/AttribType.h>

namespace ge
{
   namespace sg
   {
      typedef uint16_t AttribsConfigId;


      class GE_EXPORT AttribsConfig : public std::vector<AttribType> {
      public:
         bool ebo;
         AttribsConfigId convertToId() const;
      };

   }
}

#endif // GE_SG_ATTRIBS_CONFIG_H
