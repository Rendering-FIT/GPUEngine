#ifndef GE_SG_STATE_SET_H
#define GE_SG_STATE_SET_H

#include <memory>
#include <geSG/ParentChildList.h>

namespace ge
{
   namespace sg
   {
      class Node;


      class StateSet : public std::enable_shared_from_this<StateSet>
      {
      public:

         typedef ChildListTemplate<StateSet> ChildList;
         typedef ParentListTemplate<StateSet> ParentList;

         struct StateSetData {
            unsigned indirectBufferOffset;
            unsigned atomicCounterOffset;
         };

      protected:

         ChildList _children;
         ParentList _parents;

         std::array<unsigned,32> _numPrimitivesOfKind;
         std::array<unsigned,32> _stateSetDataIndex;
         unsigned _numPrimitives;

         //uniforms

      public:

         inline unsigned getStateSetBufferIndex(uint16_t mode) const;
         inline void incrementDrawCommandModeCounter(uint16_t mode);
         inline void decrementDrawCommandModeCounter(uint16_t mode);

      };



      inline unsigned StateSet::getStateSetBufferIndex(uint16_t mode) const  { return _stateSetDataIndex[mode]; }
      inline void StateSet::incrementDrawCommandModeCounter(uint16_t mode)  { _numPrimitivesOfKind[mode]++; }
      inline void StateSet::decrementDrawCommandModeCounter(uint16_t mode)  { _numPrimitivesOfKind[mode]--; }

   }
}

#endif // GE_SG_STATE_SET_H
