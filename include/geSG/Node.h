#ifndef GE_SG_NODE_H
#define GE_SG_NODE_H

#include <geSG/ParentChildList.h>

namespace ge
{
   namespace sg
   {
      class Node
      {
      protected:

         ChildList<Node> _children;
         ParentList<Node> _parents;

      public:

         typedef ChildList<Node>::ChildIterator ChildIterator;
         typedef ParentList<Node>::ParentIterator ParentIterator;

         inline ChildIterator childBeginIterator() const  { return _children.childBegin(); }
         inline ChildIterator childEndIterator()   const  { return _children.childEnd(); }
         inline ParentIterator parentBeginIterator() const  { return _parents.childBegin(); }
         inline ParentIterator parentEndIterator()   const  { return _parents.childEnd(); }

         virtual void addChild(std::shared_ptr<Node> &node);
         virtual void removeChild(ChildIterator it);
         virtual void removeChild(std::shared_ptr<Node> &node);
         virtual void removeAllChildren();

      };
   }
}

#endif // GE_SG_NODE_H
