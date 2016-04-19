#include <iostream>
#include <geRG/AttribConfig.h>

using namespace std;
using namespace ge::rg;

shared_ptr<AttribConfig::Factory> AttribConfig::_factory=make_shared<AttribConfig::Factory>();
const AttribConfigRef AttribConfigRef::invalid{};


AttribConfig::~AttribConfig()
{
   if(_referenceCounter!=0)
   {
      if(_referenceCounter>0)
         cout<<"Error in AttribConfig::~AttribConfig(): Reference counter is not zero.\n"
               "   Destructing object with references may result in application instability." << endl;
      else
         cout<<"Error in AttribConfig::~AttribConfig(): Reference counter underflow." << endl;
   }
}


void AttribConfig::destroy()
{
   assert(_referenceCounter==0 && "Wrong usage of AttribConfig::destroy.");

   if(_renderingContext!=NULL)
      _renderingContext->removeAttribConfig(_selfIterator);
   delete this;
}


void AttribConfig::detachFromRenderingContext()
{
   _renderingContext=NULL;
}


void AttribConfig::deleteAllAttribStorages()
{
   // remove AttribStorages while making reference to itself
   // and release it at the end of our work
   // (AttribConfig may be destroyed at the removeReference())
   addReference();
   _attribStorages.clear();
   removeReference();
}


bool AttribConfig::allocData(Mesh& mesh,int numVertices,int numIndices,unsigned numPrimitives)
{
   // iterate AttribStorage list
   // and look if there is one with enough empty space
   AttribStorageList::iterator storageIt=_attribStorages.end();
   for(auto it=_attribStorages.begin(); it!=_attribStorages.end(); it++)
   {
      if((*it)->vertexAllocationManager().numItemsAvailableAtTheEnd()>=unsigned(numVertices) &&
         (*it)->indexAllocationManager().numItemsAvailableAtTheEnd()>=unsigned(numIndices))
      {
         storageIt=it;
         break;
      }
   }

   // is there no suitable AttribStorage?
   if(storageIt==_attribStorages.end())
   {
      // create a new AttribStorage
      auto v=numVertices>_defaultStorageNumVertices?numVertices:_defaultStorageNumVertices;
      auto i=this->_configData.ebo?
            numIndices>_defaultStorageNumIndices?numIndices:_defaultStorageNumIndices:
            0;
      _attribStorages.push_front(AttribStorage::factory()->create(this->createReference(),v,i));
      storageIt=_attribStorages.begin();
   }

   // perform allocation in the choosen AttribStorage
   bool r=(*storageIt)->allocData(mesh,numVertices,numIndices);
   if(!r) {
      cerr<<"Error: AttribConfig::allocData() failed to allocate space for mesh\n"
            "   in AttribStorage ("<<numVertices<<" vertices and "<<numIndices
          <<" indices requested)." << endl;
      return false;
   }

   // perform allocation of draw commands
   r=_renderingContext->allocPrimitives(mesh,numPrimitives);
   if(!r)
      cerr<<"Error: AttribConfig::allocData() failed to allocate space for Mesh\n"
            "   in PrimitiveStorage ("<<numPrimitives<<" primitives requested)." << endl;

   return r;
}


bool AttribConfig::reallocData(Mesh& /*mesh*/,int /*numVertices*/,int /*numIndices*/,unsigned /*numPrimitives*/,bool /*preserveContent*/)
{
   // Used strategy:
   // - if new arrays are smaller, we keep data in place and free the remaning space
   // - if new arrays are bigger and can be enlarged on the place, we do it
   // - otherwise we try to allocate new place for the data in the same AttribStorage
   // - if we do not succeed in the current AttribStorage, we move the data to
   //   some other AttribStorage
   // - if no AttribStorage accommodate us, we allocate new AttribStorage

   // FIXME: not implemented yet
   return false;
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
   int numToParse=texCoordPossibleIndex!=0?configSize-2:configSize-1;

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


AttribConfig* AttribConfig::Factory::create(const std::vector<AttribType>& attribTypes,bool ebo,
                                            AttribConfigId id,RenderingContext *manager,
                                            AttribConfigList::iterator selfIterator)
{
   return new AttribConfig(attribTypes,ebo,id,manager,selfIterator);
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

// AttribConfig::ConfigData::Id documentation
// note: brief description is with the variable declaration
/** \var AttribConfigId AttribConfig::ConfigData::id
 *
 *  If it is non-zero, AttribConfig class contains one of known frequently used
 *  attribute configurations. Thus, optimized routines may be used for
 *  operations with attribute configurations such as comparison or lookups,
 *  as it is just comparison of integers or lookup by integer.
 *
 *  If the value is zero, all operations with attribute configurations
 *  have to be performed using the whole attribute setup described by
 *  AttribConfig::ConfigData structure.
 *
 *  If one AttribStorage::ConfigData contains id equal to zero and
 *  the second non-zero and updateId() was executed on both of them,
 *  they always contain different attribute configurations.
 */

// AttribConfig::ConfigData::ConfigData(const std::vector<AttribType>& attribTypes,bool ebo) documentation
// note: brief description is with the variable declaration
/** \var AttribConfig::ConfigData::ConfigData(const std::vector<AttribType>& attribTypes,bool ebo)
 *
 *  Constructor automatically computes id member from given parameters.
 */


// AttribConfig::ConfigData::ConfigData(const std::vector<AttribType>& attribTypes,bool ebo,AttribConfigId id);
// note: brief description is with the variable declaration
/** \var AttribConfig::ConfigData::ConfigData(const std::vector<AttribType>& attribTypes,bool ebo,AttribConfigId id)
 */

// void AttribConfig::ConfigData::updateId()
// note: brief description is with the variable declaration
/** \var void AttribConfig::ConfigData::updateId()
 *
 *  The method is expected to be called after each ConfigData structure update
 *  whenever id member might become invalid.
 */
