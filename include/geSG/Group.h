#ifndef GE_SG_GROUP_H
#define GE_SG_GROUP_H

#include <geSG/Node.h>
#include <geSG/ParentChildList.h>

namespace ge
{
   namespace sg
   {
      class Group : public Node
      {
      protected:

         ChildList<Node,Group> _children;

      public:

         typedef ChildList<Node,Group>::ChildIterator ChildIterator;

         inline ChildIterator childBeginIterator() const  { return _children.childBegin(); }
         inline ChildIterator childEndIterator()   const  { return _children.childEnd(); }

         virtual void addChild(std::shared_ptr<Node> &node);
         virtual void removeChild(ChildIterator it);
         virtual void removeChild(std::shared_ptr<Node> &node);
         virtual void removeAllChildren();
         inline ChildList<Node,Group>& getChildren()  { return _children; }

      };
   }
}

#endif // GE_SG_GROUP_H
