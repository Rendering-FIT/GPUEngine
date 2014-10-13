#ifndef GE_SG_STATE_SET_H
#define GE_SG_STATE_SET_H

#include <memory>
#include <geSG/ParentChildList.h>

namespace ge
{
   namespace sg
   {
      class Node;


      class StateSet : public std::enable_shared_from_this<StateSet>
      {
      public:

         typedef ParentSimpleListTemplate<Node> ParentList;

      protected:

         ParentList _parents;

         LIST_PUBLIC_INTERFACE(_parents,ParentList,std::weak_ptr<Node>&,StateSet,parents);

      public:

      };
   }
}

#endif // GE_SG_STATE_SET_H
