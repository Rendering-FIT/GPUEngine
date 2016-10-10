#include <iostream>
#include <geRG/AttribConfig.h>

using namespace std;
using namespace ge::rg;


AttribConfig::Instance AttribConfig::Instance::invalid(1);
const AttribConfig AttribConfig::invalid;



AttribConfig::~AttribConfig()
{
   _instance->unref();
}


AttribConfig::Instance::~Instance()
{
   assert((referenceCounter==0||this==&invalid) &&
          "Error in AttribConfig::Instance::~Instance(): Reference counter is not zero.\n"
          "   Destructing the object with references may result in application instability.");
}


void AttribConfig::Instance::destroy()
{
   if(renderingContext)
      // remove AttribConfig::Instance from list inside RenderingContext
      // (we must not delete object here as
      // RenderingContext::removeAttribConfigInstance() will take care of it by
      // calling this method again but with renderingContext set to null)
      renderingContext->removeAttribConfigInstance(selfIterator);
   else
      delete this;
}


void AttribConfig::Instance::deleteAllAttribStorages()
{
   // remove AttribStorages while making reference to itself
   // and release it at the end of our work
   // (AttribConfig may be destroyed at the removeReference())
   ref();
   attribStorageList.clear();
   unref();
}


static AttribConfigId getAttribTypeId(const AttribType t)
{
   if(t==AttribType::Empty)
      return 0;
   else
      switch(t.glType()) {
         case GLType::FLOAT:
            switch(t.numComponents()) {
               case 2: return 1;
               case 3: return 2;
               case 4: return 3;
               default: return unsigned(-1);
            }
         case GLType::HALF_FLOAT:
            switch(t.numComponents()) {
               case 2: return 4;
               case 3: return 5;
               case 4: return 6;
               default: return unsigned(-1);
            }
         case GLType::UNSIGNED_BYTE:
            switch(t.numComponents()) {
               case 2: return 7;
               case 3: return 8;
               case 4: return 9;
               default: return unsigned(-1);
            }
         default: return unsigned(-1);
      }
}


AttribConfigId AttribConfig::getId(const std::vector<AttribType>& attribTypes,bool ebo)
{
   unsigned configSize=unsigned(attribTypes.size());

   // remove ending AttribType::Empty's
   while(configSize>=1&&attribTypes[configSize-1]==AttribType::Empty)
      configSize--;

   // return 0 for more than 4 attribs or zero attribs
   if(configSize>7||configSize==0)
      return 0;

   AttribConfigId r=0;
   AttribType t;

   // indices
   // (if they are used, they required EBO to use UNSIGNED_INT type)
   //
   // Indices occupy bit 28 of the returned integer.
   if(ebo)
      r|=0x1<<28;

   // generate id out of attrib types
   // (each attrib occupies 4 bits of returned integer)
   for(unsigned i=0,s=24; i<configSize; i++,s-=4) {
      AttribConfigId id=getAttribTypeId(attribTypes[i]);
      if(id==unsigned(-1))
         return 0;
      r|=id<<s;
   }

   return r;
}


// AttribConfigId type documentation
// note: brief description is with the variable declaration
/** \var AttribConfigId
 *
 *  Complete attribute configuration is stored in AttribConfig::ConfigData struct,
 *  a non-trivial data type.
 *  Using it for map lookups or comparison of two configurations
 *  might be performance expensive.
 *  Thus, frequently used attribute configurations has their
 *  integer-based representation that can be used for faster map lookups
 *  and very fast comparison. This integer-based configuration uses
 *  AttribConfigId type.
 *
 *  Zero value stored in this type means that the attribute configuration
 *  is not one of the supported frequently used attribute configuration.
 *
 *  \sa AttribConfig
 */

// AttribConfig::Configuration::Id documentation
// note: brief description is with the variable declaration
/** \var AttribConfigId AttribConfig::Configuration::id
 *
 *  If it is non-zero, AttribConfig class contains one of known frequently used
 *  attribute configurations. Thus, optimized routines may be used for
 *  operations with attribute configurations such as comparison or lookups,
 *  as it is just comparison of integers or lookup by integer.
 *
 *  If the value is zero, all operations with attribute configurations
 *  have to be performed using the whole attribute setup described by
 *  AttribConfig::Configuration structure.
 *
 *  If one AttribStorage::Configuration contains id equal to zero and
 *  the second non-zero and updateId() was executed on both of them,
 *  they always contain different attribute configurations.
 */

// AttribConfig::ConfigData::ConfigData(const std::vector<AttribType>& attribTypes,bool ebo) documentation
// note: brief description is with the variable declaration
/** \var AttribConfig::Configuration::Configuration(const std::vector<AttribType>& attribTypes,bool ebo)
 *
 *  The constructor automatically computes id member from given parameters.
 */


// AttribConfig::Configuration::Configuration(const std::vector<AttribType>& attribTypes,bool ebo,AttribConfigId id);
// note: brief description is with the variable declaration
/** \var AttribConfig::Configuration::Configuration(const std::vector<AttribType>& attribTypes,bool ebo,AttribConfigId id)
 */

// void AttribConfig::Configuration::updateId()
// note: brief description is with the variable declaration
/** \var void AttribConfig::Configuration::updateId()
 *
 *  The method is expected to be called after each Configuration structure update
 *  whenever id member might become invalid.
 */
