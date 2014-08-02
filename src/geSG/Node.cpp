#include <algorithm>
#include <geSG/Node.h>

using namespace ge::sg;


void Node::addChild(std::shared_ptr<Node> &node)
{
   auto it = node->_parents.insert(node->_parents.end(),node.get());
   _children.emplace_back(node,it);
}


void Node::removeChild(ChildIterator it)
{
   auto ii = it.getInternalIterator();
   ii->child->_parents.erase(ii->parentsDeleteIt);
   _children.erase(ii);
}


void Node::removeChild(std::shared_ptr<Node> &node)
{
   struct IsLookedForChildRec
   {
      Node* _lookedForNode;
      inline bool operator()(const ChildRec<Node>& rec) const
      {
         return rec.child.get() == _lookedForNode;
      }
      IsLookedForChildRec(const std::shared_ptr<Node>& lookedForNode) : _lookedForNode(lookedForNode.get())  {}
   };
   ChildList<Node>::iterator it = std::find_if(_children.begin(),_children.end(),IsLookedForChildRec(node));
   if(it!=_children.end())
      removeChild(it);
}
