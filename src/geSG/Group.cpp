#include <algorithm>
#include <geSG/Group.h>

using namespace std;
using namespace ge::sg;


void Group::addChild(shared_ptr<Node> &node)
{
   auto it1 = node->getParents().emplace(node->getParents().end(),
                                         static_pointer_cast<Group>(shared_from_this()),
                                         ChildList::iterator());
   auto it2 = _children.emplace(_children.end(),node,it1);
   it1->childListDeleteIterator = it2;
}


void Group::removeChild(ChildIterator it)
{
   auto ii = it.getInternalIterator();
   ii->child->getParents().erase(ii->parentListDeleteIterator);
   _children.erase(ii);
}


void Group::removeChild(shared_ptr<Node> &node)
{
   struct IsLookedForChildRec
   {
      Node* _lookedForNode;
      inline bool operator()(const ChildList::ChildData& rec) const
      {
         return rec.child.get() == _lookedForNode;
      }
      IsLookedForChildRec(const shared_ptr<Node>& lookedForNode) : _lookedForNode(lookedForNode.get())  {}
   };
   auto it = find_if(_children.begin(),_children.end(),IsLookedForChildRec(node));
   if(it!=_children.end())
      removeChild(it);
}


void Group::removeAllChildren()
{
   auto eIt = childEndIterator();
   ChildIterator it;
   while((it=childBeginIterator())!=eIt)
      removeChild(it);
}


void Group::traverse(NodeVisitor& visitor)
{
   for(auto it=childBeginIterator(); it!=childEndIterator(); it++)
      (*it)->accept(visitor);
}
