#ifndef GE_SG_CHILD_LIST_H
#define GE_SG_CHILD_LIST_H

#include <memory>
#include <list>

namespace ge
{
   namespace sg
   {

      template<typename T,typename ParentT> class ChildList;
      template<typename T,typename ChildT> class ParentList;

      template<typename T,typename ParentT=T>
      struct ChildRec
      {
         std::shared_ptr<T> child;
         typename ParentList<ParentT,T>::iterator peerIt;
         ChildRec(std::shared_ptr<T> node,typename ParentList<ParentT,T>::iterator it)
                  : child(node),peerIt(it) {}
      };

      template<typename T,typename ChildT=T>
      struct ParentRec
      {
         std::weak_ptr<T> parent;
         typename ChildList<ChildT,T>::iterator peerIt;
         ParentRec(std::weak_ptr<T> node,typename ChildList<ChildT,T>::iterator it)
                  : parent(node),peerIt(it) {}
      };

      template<typename T,typename Rec>
      class ParentChildList : public std::list<Rec>
      {
      protected:
         typedef std::list<Rec> inherited;
      public:

         struct ParentChildIterator
         {
         protected:

            typename std::list<Rec>::iterator _it;

         public:

            typedef std::ptrdiff_t                     difference_type;
            typedef std::bidirectional_iterator_tag    iterator_category;

            inline ParentChildIterator()  {}
            inline ParentChildIterator(typename std::list<Rec>::iterator recIt) : _it(recIt)  {}

            inline typename std::list<Rec>::iterator getInternalIterator() const  { return _it; }

            ParentChildIterator& operator++()     { _it++; return *this; }
            ParentChildIterator  operator++(int)  { ParentChildIterator tmp = *this; _it++; return tmp; }
            ParentChildIterator& operator--()     { _it--; return *this; }
            ParentChildIterator  operator--(int)  { ParentChildIterator tmp = *this; _it--; return tmp; }

            bool operator==(const ParentChildIterator& rhs) const  { return _it == rhs._it; }
            bool operator!=(const ParentChildIterator& rhs) const  { return _it != rhs._it; }
         };

         inline void assign(size_t n, const T& value)  { inherited::assign(n,value); }
      };

      template<typename T,typename ParentT=T>
      class ChildList : public ParentChildList<T,ChildRec<T,ParentT>>
      {
      protected:
         typedef ParentChildList<T,ChildRec<T,ParentT>> inherited;
         typedef typename inherited::inherited inheritedList;
      public:

         struct ChildIterator : inherited::ParentChildIterator
         {
         protected:
            typedef typename ParentChildList<T,ChildRec<T,ParentT>>::ParentChildIterator inherited;

         public:

            typedef const std::shared_ptr<T>           value_type;
            typedef const std::shared_ptr<T>*          pointer;
            typedef const std::shared_ptr<T>&          reference;

            inline ChildIterator()  {}
            inline ChildIterator(const ChildIterator& it) : inherited(it.getInternalIterator())  {}
            inline ChildIterator(typename std::list<ChildRec<T,ParentT>>::iterator recIt) : inherited(recIt)  {}

            inline reference operator*() const  { return inherited::_it->child; }
            inline pointer operator->() const   { return std::__addressof(inherited::_it->child); }
         };

         typedef std::reverse_iterator<ChildIterator>  ChildReverseIterator;


         inline ChildList()  {}
         //inline explicit ChildList(const Alloc& a) : inherited(a)  {}
         inline explicit ChildList(size_t n) : inheritedList(n)  {}
         inline ChildList(size_t n,const T& value)
                  : inherited(n,value,std::allocator<ChildRec<T,ParentT>>())  {}
         inline ChildList(const ChildList& list) : inherited(list)  {}
         inline ChildList(ChildList&& list) : inherited(std::move(list))  {}
         inline ChildList(std::initializer_list<T> il)
                  : inherited(il,std::allocator<ChildRec<T,ParentT>>())  {}
         template<typename InputIterator>
         inline ChildList(InputIterator first,InputIterator last)
                  : inherited(first,last,std::allocator<ChildRec<T,ParentT>>())  {}

         inline ChildIterator         childBegin() const   { return ChildIterator(((ChildList<T,ParentT>*)this)->inherited::begin()); }
         inline ChildIterator         childEnd() const     { return ChildIterator(((ChildList<T,ParentT>*)this)->inherited::end()); }
         inline ChildReverseIterator  childRBegin() const  { return ChildReverseIterator(((ChildList<T,ParentT>*)this)->inherited::rbegin()); }
         inline ChildReverseIterator  childREnd() const    { return ChildReverseIterator(((ChildList<T,ParentT>*)this)->inherited::rend()); }

         inline ChildList& operator=(const ChildList& list)  { return inheritedList::operator=(list); }
         inline ChildList& operator=(ChildList&& list)  { return inheritedList::operator=(list); }
         inline ChildList& operator=(std::initializer_list<T> il)  { return inheritedList::operator=(il); }

      };

      template<typename T,typename ChildT=T>
      class ParentList : public ParentChildList<T,ParentRec<T,ChildT>>
      {
      protected:
         typedef ParentChildList<T,ParentRec<T,ChildT>> inherited;
         typedef typename inherited::inherited inheritedList;
      public:

         struct ParentIterator : public inherited::ParentChildIterator
         {
         private:
            typedef typename ParentChildList<T,ParentRec<T,ChildT>>::ParentChildIterator inherited;

         public:

            typedef const std::weak_ptr<T>           value_type;
            typedef const std::weak_ptr<T>*          pointer;
            typedef const std::weak_ptr<T>&          reference;

            inline ParentIterator()  {}
            inline ParentIterator(const ParentIterator& it) : inherited(it.getInternalIterator())  {}
            inline ParentIterator(typename std::list<ParentRec<T,ChildT>>::iterator recIt) : inherited(recIt)  {}

            inline reference operator*() const  { return inherited::_it->parent; }
            inline pointer operator->() const   { return std::__addressof(inherited::_it->parent); }
         };

         typedef std::reverse_iterator<ParentIterator>  ParentReverseIterator;


         inline ParentIterator         childBegin() const   { return ParentIterator(((ParentList<T,ChildT>*)this)->begin()); }
         inline ParentIterator         childEnd() const     { return ParentIterator(((ParentList<T,ChildT>*)this)->end()); }
         inline ParentReverseIterator  childRBegin() const  { return ParentReverseIterator(((ParentList<T,ChildT>*)this)->rbegin()); }
         inline ParentReverseIterator  childREnd() const    { return ParentReverseIterator(((ParentList<T,ChildT>*)this)->rend()); }
      };

   }
}

#endif // GE_SG_CHILD_LIST_H
