#ifndef GE_SG_NODE_H
#define GE_SG_NODE_H

#include <geSG/ParentChildList.h>

namespace ge
{
   namespace sg
   {
      class Group;
      class StateSet;


      class Node : public std::enable_shared_from_this<Node>
      {
      public:

         typedef ParentListTemplate<Group,Node> ParentList;
         typedef ParentList::ParentIterator ParentIterator;
         typedef ChildPointerTemplate<StateSet,Node> StateSetPointer;

      protected:

         ParentList _parents;
         StateSetPointer _stateSet;

      public:

         inline ParentIterator parentBeginIterator() const  { return _parents.childBegin(); }
         inline ParentIterator parentEndIterator()   const  { return _parents.childEnd(); }
         inline ParentList& getParents()  { return _parents; }

      };
   }
}

#endif // GE_SG_NODE_H
