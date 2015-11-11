#ifndef GE_RG_DRAW_COMMAND_H
#define GE_RG_DRAW_COMMAND_H

#include <geRG/Export.h>
#include <geRG/AllocationManagers.h>

namespace ge
{
   namespace rg
   {

      /** DrawCommandGpuData is part of DrawCommand state that is stored in GPU buffers,
       *  usually in RenderingContext::drawCommandBuffer().
       *  Allocation management of DrawCommandGpuData buffer is usually provided
       *  by DrawCommandAllocationManager.
       *
       *  \sa Object, RenderingContext::objectBuffer(), ObjectAllocationManager
       */
      struct DrawCommandGpuData {
         unsigned primitiveSetOffset4;
         unsigned matrixListControlOffset4;
         unsigned stateSetOffset4;
      };


      /** DrawCommand structure holds the information of a single
       *  draw command managed by ge::rg::Object.
       */
      struct GERG_EXPORT DrawCommand {
      public:
         unsigned data; // 32-bits, verified by assert in DrawCommand.cpp

         inline unsigned index() const  { return data&0x07ffffff; } // return lowest 27 bits
         inline unsigned mode() const     { return data>>27; } // return upmost 5 bits
         inline void setIndex(unsigned value)  { data=(data&0xf8000000)|value; } // set lowest 27 bits, value must fit to 27 bits
         inline void setMode(unsigned value)     { data=(data&0x07ffffff)|(value<<27); } // set upmost 5 bits
         inline void set(unsigned index,unsigned mode)  { data=index|(mode<<27); } // set data, offset4 must fit to 27 bits

         inline DrawCommand() {}
         inline DrawCommand(unsigned offset4,unsigned mode)  { set(offset4,mode); }
      };


      class GERG_EXPORT DrawCommandAllocationManager : public ItemAllocationManager {
      public:

         inline DrawCommand*& operator[](unsigned pos);
         inline DrawCommand* operator[](unsigned pos) const;
         inline DrawCommandAllocationManager(unsigned capacity);
         inline DrawCommandAllocationManager(unsigned capacity,unsigned numNullObjects);
         bool alloc(DrawCommand* id);  ///< \brief Allocates one draw command and stores its index to the DrawCommand pointed by id parameter.
         bool alloc(unsigned num,DrawCommand *ids);  ///< \brief Allocates number of draw commands. Array pointed by ids must be at least num DrawCommands long.
         inline void free(DrawCommand id);  ///< Frees allocated draw commands. Id must be valid.
         void free(DrawCommand* ids,unsigned num);  ///< Frees allocated draw commands. Ids pointed by ids parameter must be valid.

      public:
         // internal helper methods that forwards the calls
         // when DrawCommandAllocationManager is used inside BufferStorage
         inline bool alloc(unsigned *id)  { return alloc(reinterpret_cast<DrawCommand*>(id)); }
         inline bool alloc(unsigned num,unsigned* ids)  { return alloc(num,reinterpret_cast<DrawCommand*>(ids)); }
      };



      // inline and template methods
      inline DrawCommand*& DrawCommandAllocationManager::operator[](unsigned pos)  { return reinterpret_cast<DrawCommand**>(ItemAllocationManager::data())[pos]; }
      inline DrawCommand* DrawCommandAllocationManager::operator[](unsigned pos) const  { return reinterpret_cast<DrawCommand*const*>(ItemAllocationManager::data())[pos]; }
      inline DrawCommandAllocationManager::DrawCommandAllocationManager(unsigned capacity) : ItemAllocationManager(capacity) {}
      inline DrawCommandAllocationManager::DrawCommandAllocationManager(unsigned capacity,unsigned numNullObjects) : ItemAllocationManager(capacity,numNullObjects) {}
      inline void DrawCommandAllocationManager::free(DrawCommand id)  { ItemAllocationManager::free(id.index()); }

   }
}

#endif /* GE_RG_DRAW_COMMAND_H */
