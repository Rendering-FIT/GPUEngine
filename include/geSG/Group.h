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
      public:

         typedef ChildListTemplate<Node,Group> ChildList;
         typedef ChildList::ChildIterator ChildIterator;

      protected:

         ChildList _children;

      public:

         META_Node(ge::sg,Group);

         inline ChildIterator childBeginIterator() const  { return _children.childBegin(); }
         inline ChildIterator childEndIterator()   const  { return _children.childEnd(); }

         virtual void addChild(std::shared_ptr<Node> &node);
         virtual void removeChild(ChildIterator it);
         virtual void removeChild(std::shared_ptr<Node> &node);
         virtual void removeAllChildren();
         inline ChildList& getChildren()  { return _children; }

         virtual void traverse(NodeVisitor& visitor);

      };
   }
}

#endif // GE_SG_GROUP_H
