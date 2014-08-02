#ifndef GE_SG_NODE_H
#define GE_SG_NODE_H

#include <geSG/ChildList.h>

namespace ge
{
   namespace sg
   {
      class Node
      {
         ChildList<Node> _children;
         std::list<Node*> _parents;

      public:

         typedef ChildList<Node>::ChildIterator ChildIterator;

         inline ChildIterator childBeginIterator() const  { return _children.childBegin(); }
         inline ChildIterator childEndIterator()   const  { return _children.childEnd(); }

         virtual void addChild(std::shared_ptr<Node> &node);
         virtual void removeChild(ChildIterator it);
         virtual void removeChild(std::shared_ptr<Node> &node);

      };
   }
}

#endif // GE_SG_NODE_H
