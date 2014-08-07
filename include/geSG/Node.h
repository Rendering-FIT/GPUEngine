#ifndef GE_SG_NODE_H
#define GE_SG_NODE_H

#include <geSG/ParentChildList.h>

namespace ge
{
   namespace sg
   {
      class Group;


      class Node : public std::enable_shared_from_this<Node>
      {
      public:

         typedef ParentListTemplate<Group,Node> ParentList;
         typedef ParentList::ParentIterator ParentIterator;

      protected:

         ParentList _parents;

      public:

         inline ParentIterator parentBeginIterator() const  { return _parents.childBegin(); }
         inline ParentIterator parentEndIterator()   const  { return _parents.childEnd(); }
         inline ParentList& getParents()  { return _parents; }

      };
   }
}

#endif // GE_SG_NODE_H
