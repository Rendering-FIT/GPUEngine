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
      protected:

         ParentList<Group,Node> _parents;

      public:

         typedef ParentList<Group,Node>::ParentIterator ParentIterator;

         inline ParentIterator parentBeginIterator() const  { return _parents.childBegin(); }
         inline ParentIterator parentEndIterator()   const  { return _parents.childEnd(); }
         inline ParentList<Group,Node>& getParents()  { return _parents; }

      };
   }
}

#endif // GE_SG_NODE_H
