#pragma once

#include <map>
#include <climits>
#include <string>

#include <GPUEngine/geCore/gecore_export.h>

namespace ge {
   namespace core
   {
      class GECORE_EXPORT EnumRegister
      {
      public:

         static const unsigned notRegistered = UINT_MAX;

         EnumRegister();
         unsigned registerConstant(const char * name);
         unsigned registerConstant(const std::string& name);
         unsigned getValue(const char* name) const;
         unsigned getValue(const std::string& name) const;
         std::string getName(unsigned value) const;

      protected:
         unsigned _next;
         std::map<std::string, unsigned> _byName;
         std::map<unsigned, std::string> _byValue;
      };
   }
}
