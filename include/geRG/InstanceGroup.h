#ifndef GE_RG_INSTANCE_GROUP_H
#define GE_RG_INSTANCE_GROUP_H

#include <cstdint>
#include <geRG/Export.h>
#include <geRG/FlexibleArrayList.h>
#include <geRG/AllocationManagers.h>

namespace ge
{
   namespace rg
   {
      class InstancingMatrices;
      class StateSet;


      class GERG_EXPORT InstanceGroupBase : public ListItemBase {
      public:
         StateSet *stateSet;
         InstancingMatrices *instancingMatrices;
      };


      struct GERG_EXPORT InstanceData {
      public:
         uint32_t data;

         inline uint32_t index() const  { return data&0x07ffffff; } // return lowest 27 bits
         inline uint16_t mode() const     { return data>>27; } // return upmost 5 bits
         inline void setIndex(uint32_t value)  { data=(data&0xf8000000)|value; } // set lowest 27 bits, value must fit to 27 bits
         inline void setMode(uint16_t value)     { data=(data&0x07ffffff)|(uint32_t(value)<<27); } // set upmost 5 bits
         inline void set(uint32_t index,uint16_t mode)  { data=index|(uint32_t(mode)<<27); } // set data, offset4 must fit to 27 bits

         inline InstanceData() {}
         inline InstanceData(uint32_t offset4,uint16_t mode)  { set(offset4,mode); }
      };


      class GERG_EXPORT InstanceAllocationManager : public ItemAllocationManager {
      public:
         inline InstanceData*& operator[](size_type pos);
         inline InstanceData* operator[](size_type pos) const;
         inline InstanceAllocationManager(unsigned capacity);
         inline InstanceAllocationManager(unsigned capacity,unsigned numNullObjects);
         bool alloc(InstanceData *id);  ///< \brief Allocates one instance and stores the instance's index to the InstanceData pointed by id parameter.
         bool alloc(unsigned num,InstanceData *ids);  ///< \brief Allocates number of instances.
         inline void free(InstanceData id);  ///< Frees allocated instances. Id must be valid.
         void free(InstanceData* ids,unsigned num);  ///< Frees allocated instances. Ids pointed by ids parameter must be valid.
      };


      typedef FlexibleArray<InstanceData,InstanceGroupBase> InstanceGroup;
      typedef FlexibleArrayList<InstanceGroup> InstanceGroupList;
      typedef InstanceGroupList::iterator InstanceGroupId;



      // inline and template methods
      inline InstanceData*& InstanceAllocationManager::operator[](size_type pos)  { return reinterpret_cast<InstanceData**>(ItemAllocationManager::data())[pos]; }
      inline InstanceData* InstanceAllocationManager::operator[](size_type pos) const  { return reinterpret_cast<InstanceData*const*>(ItemAllocationManager::data())[pos]; }
      inline InstanceAllocationManager::InstanceAllocationManager(unsigned capacity) : ItemAllocationManager(capacity) {}
      inline InstanceAllocationManager::InstanceAllocationManager(unsigned capacity,unsigned numNullObjects) : ItemAllocationManager(capacity,numNullObjects) {}
      inline void InstanceAllocationManager::free(InstanceData id)  { ItemAllocationManager::free(id.index()); }

   }
}

#endif /* GE_RG_INSTANCE_GROUP_H */
