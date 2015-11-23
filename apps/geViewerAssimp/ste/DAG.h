#pragma once

#include <vector>
#include <memory>

#include  "stl_extension.h"

namespace ste
{

   /*template<typename T>
   struct is_shared_ptr : std::false_type {};

   template<typename T>
   struct is_shared_ptr<std::shared_ptr<T::element_type>> : std::true_type {};*/

   template<typename Data>
   class Node
   {
   public:
      typedef std::vector<int>::size_type size_type; //need to supply vector int because we can't have template inside template... vector<shared_ptr<Node<Data>>>::size_type doesn't compile
      typedef std::vector<std::shared_ptr<Node>> ChildContainer;
      typedef typename std::vector<std::shared_ptr<Node>>::iterator ChildIterator;

      //using size_type = std::vector<std::shared_ptr<Node>>::size_type;
      //typedef int size_type;

      Node();
      Node(Data data);

      ChildIterator addChild(Data child);

      //template<typename Other/*,typename*/>
      //Other getDataAsOther();

      template<typename Other>
      typename std::enable_if<!is_shared<Data>::value, Other>::type getDataAsOther()
      {
         return static_cast<Other>(data);
      }

      template<typename Other>
      typename std::enable_if<is_shared<Data>::value, Other>::type getDataAsOther()
      {

         return std::static_pointer_cast<Other>(data);
      }

      /*template<class T, typename Other>
      Other getDataAsOther();*/


      //////////////////////////////////////////////////////////////////////////
      // Members
      Data data;
      ChildContainer children;

      //////////////////////////////////////////////////////////////////////////
      // Operators
      Data& operator*();
      Node& operator[](size_type pos);
      Data* operator->();
      //const Node& operator[](size_type pos) const;
   };

   template<typename Data>
   ste::Node<Data>::Node()
   {

   }

   template<typename Data>
   ste::Node<Data>::Node(Data data)
   {
      this->data = data;
   }

   template <typename Data>
   typename std::vector<std::shared_ptr<Node<Data>>>::iterator Node<Data>::addChild(Data child)
   {
      this->children.emplace_back(ste::Node<Data>(child));
      return children.end() - 1;
   }

   template<typename Data>
   Data& ste::Node<Data>::operator*()
   {
      return data;
   }

   template<typename Data>
   Node<Data>& Node<Data>::operator[](size_type pos)
   {
      return *children[pos].get();
   }

   /*template<typename Data>
   const Node& operator[](Node::size_type pos) const
   {
      return children[pos];
   }*/

   template<typename Data>
   Data* ste::Node<Data>::operator->()
   {
      return &data;
   }

//////////////////////////////////////////////////////////////////////////

   template<typename Data>
   class NodeIntrusive : public Data
   {
   public:
      std::vector<std::shared_ptr<NodeIntrusive> > children;
   };

}//namespace ste