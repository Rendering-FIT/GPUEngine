#ifndef GE_SG_NODE_H
#define GE_SG_NODE_H

#include <geSG/ParentChildList.h>
#include <geSG/NodeVisitor.h>

namespace ge
{
   namespace sg
   {
      class Group;
      class StateSet;

#define META_Node(library,name) \
      virtual ge::sg::Node* cloneType() const { return new name (); } \
      /*virtual Object* clone(const CopyOp& copyop) const { return new name (*this,copyop); }*/ \
      virtual bool isSameKindAs(const ge::sg::Node* obj) const { return dynamic_cast<const name *>(obj)!=NULL; } \
      virtual const char* className() const { return #name; } \
      virtual const char* libraryName() const { return #library; } \
      virtual void accept(ge::sg::NodeVisitor& nv) { nv.apply(*this); } \


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

         META_Node(ge::sg,Node);

         inline ParentIterator parentBeginIterator() const  { return _parents.childBegin(); }
         inline ParentIterator parentEndIterator()   const  { return _parents.childEnd(); }
         inline ParentList& getParents()  { return _parents; }

         inline Node() {}
         virtual ~Node() {}

         virtual void traverse(NodeVisitor& visitor) {}

      };
   }
}

#endif // GE_SG_NODE_H
