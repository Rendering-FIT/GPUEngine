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


AttribConfigId AttribConfig::getId(const std::vector<AttribType>& attribTypes,bool ebo)
{
   unsigned configSize=unsigned(attribTypes.size());
   if(configSize>4||configSize==0)
      return 0;

   uint16_t r=0;
   AttribType t;

   // indices
   //
   // Use of indices is signalled by ebo boolean.
   // If they are used, they required EBO to use UNSIGNED_INT type.
   //
   // Indices occupy bit 0 of the returned integer.
   if(ebo)  r|=0x1;

   // coordinates
   //
   // Coordinates are expected to be at attribute index 0
   // and we expect that they are always specified.
   //
   // Coordinates occupies bits 1 and 2 of the returned integer.
   t=attribTypes[0];
   if(t==AttribType::Vec3)  r|=0x2;
   else if(t==AttribType::Vec4)  r|=0x4;
   else if(t==AttribType::Vec2)  r|=0x6;
   else return 0;
   if(configSize==1)
      return r;

   // texCoords
   //
   // Texture coordinates are not mandatory.
   // We expect that they are stored at the last attribute index
   // (last index in AttribConfig is occupied by indices flag,
   // so it is just before it).
   //
   // TexCoords occupies bits 8 and 9 of the returned integer.
   unsigned texCoordPossibleIndex=configSize-1;
   t=attribTypes[texCoordPossibleIndex];
   if(t==AttribType::Empty);
   else if(t==AttribType::Vec2)  r|=0x100;
   else if(t==AttribType::HVec2)  r|=0x200;
   else texCoordPossibleIndex=0;
   if(configSize==2&&texCoordPossibleIndex!=0)
      return r;
   int numToParse=texCoordPossibleIndex!=0?int(configSize)-2:int(configSize)-1;

   // normals
   //
   // Normals are not mandatory.
   // If we find some 3-component formats,
   // let's consider them normals, although they may by colors as well.
   //
   // Normals occupies bits 3 and 4 of the returned integer.
   bool normalsFound=true;
   t=attribTypes[1];
   if(t==AttribType::Empty);
   else if(t==AttribType::Vec3)  r|=0x8;
   else if(t==AttribType::HVec3)  r|=0x10;
   else if(t==AttribType::UBVec3)  r|=0x18;
   else normalsFound=false;
   if(normalsFound) {
      numToParse--;
      if(numToParse==0)
         return r;
   }

   // color
   //
   // Colors are not mandatory. If they are specified, they have to use attribute index 1 or 2.
   // Index 1 must be used if there are no normals, index 2 must be used when normals are in use.
   //
   // Color occupies bits 5,6 and 7 of the returned integer.
   t=attribTypes[normalsFound?2:1];
   if(t==AttribType::Empty);
   else if(t==AttribType::Vec3)  r|=0x20;
   else if(t==AttribType::Vec4)  r|=0x40;
   else if(t==AttribType::HVec3)  r|=0x60;
   else if(t==AttribType::HVec4)  r|=0x80;
   else if(t==AttribType::UBVec3)  r|=0xa0;
   else if(t==AttribType::UBVec4)  r|=0xc0;
   //else if(t==Array::makeType(ArrayAdapter::GLType::UNSIGNED_INT_8_8_8_8,1)  r|=0x1c0;
   //else if(t==Array::makeType(ArrayAdapter::GLType::UNSIGNED_INT_8_8_8_8_REV,1)  r|=0x200;
   //else if(t==Array::makeType(ArrayAdapter::GLType::UNSIGNED_BYTE,ArrayAdapter::BGRA)  r|=0x240;
   else return 0;

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
