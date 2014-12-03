#ifndef GE_SG_ATTRIB_CONFIG_H
#define GE_SG_ATTRIB_CONFIG_H

#include <vector>
#include <geSG/Export.h>
#include <geSG/AttribType.h>

namespace ge
{
   namespace sg
   {
      typedef uint16_t AttribConfigId;  ///< \brief Integer-based type for the most frequently used attribute configurations.


      class GE_EXPORT AttribConfig : public std::vector<AttribType> {
      public:
         bool ebo;                      ///< Indicates whether element buffer object is used or not.
         AttribConfigId configId;       ///< \brief Id of one of frequently used attribute configurations.
         inline void updateConfigId();  ///< Updates AttribConfig::configId member.

         static AttribConfigId convertToId(const AttribConfig& attribConfig);
      };


      // inline methods
      inline void AttribConfig::updateConfigId()  { configId = convertToId(*this); }

   }
}

#endif // GE_SG_ATTRIB_CONFIG_H
