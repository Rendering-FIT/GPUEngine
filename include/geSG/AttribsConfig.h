#ifndef GE_SG_ATTRIBS_CONFIG_H
#define GE_SG_ATTRIBS_CONFIG_H

#include <vector>
#include <geSG/Export.h>
#include <geSG/AttribType.h>

namespace ge
{
   namespace sg
   {
      typedef uint16_t AttribsConfigId; ///< \brief Integer-based type for the most frequently used attribute configurations.


      class GE_EXPORT AttribsConfig : public std::vector<AttribType> {
      public:
         bool ebo;                      ///< Indicates whether element buffer object is used or not.
         AttribsConfigId configId;      ///< \brief Id of one of frequently used attribute configurations.
         inline void updateConfigId();  ///< Updates AttribsConfig::configId member.

         static AttribsConfigId convertToId(const AttribsConfig& attribsConfig);
      };


      // inline methods
      inline void AttribsConfig::updateConfigId()  { configId = convertToId(*this); }

   }
}

#endif // GE_SG_ATTRIBS_CONFIG_H
