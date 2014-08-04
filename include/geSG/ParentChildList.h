#ifndef GE_SG_CHILD_LIST_H
#define GE_SG_CHILD_LIST_H

#include <memory>
#include <list>

namespace ge
{
   namespace sg
   {

      template<typename T> class ParentList;
      template<typename T> class ChildList;

      template<typename T>
      struct ChildRec
      {
         std::shared_ptr<T> child;
         typename ParentList<T>::iterator peerIt;
         ChildRec(std::shared_ptr<T> node,typename ParentList<T>::iterator it)
                  : child(node),peerIt(it) {}
      };

      template<typename T>
      struct ParentRec
      {
         std::weak_ptr<T> parent;
         typename ChildList<T>::iterator peerIt;
         ParentRec(std::shared_ptr<T> node,typename ChildList<T>::iterator it)
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

      template<typename T>
      class ChildList : public ParentChildList<T,ChildRec<T>>
      {
      protected:
         typedef ParentChildList<T,ChildRec<T>> inherited;
         typedef typename inherited::inherited inheritedList;
      public:

         struct ChildIterator : inherited::ParentChildIterator
         {
         protected:
            typedef typename ParentChildList<T,ChildRec<T>>::ParentChildIterator inherited;

         public:

            typedef const std::shared_ptr<T>           value_type;
            typedef const std::shared_ptr<T>*          pointer;
            typedef const std::shared_ptr<T>&          reference;

            inline ChildIterator()  {}
            inline ChildIterator(const ChildIterator& it) : inherited(it.getInternalIterator())  {}
            inline ChildIterator(typename std::list<ChildRec<T>>::iterator recIt) : inherited(recIt)  {}

            inline reference operator*() const  { return inherited::_it->child; }
            inline pointer operator->() const   { return std::__addressof(inherited::_it->child); }
         };

         typedef std::reverse_iterator<ChildIterator>  ChildReverseIterator;


         inline ChildList()  {}
         //inline explicit ChildList(const Alloc& a) : inherited(a)  {}
         inline explicit ChildList(size_t n) : inheritedList(n)  {}
         inline ChildList(size_t n,const T& value)
                  : inherited(n,value,std::allocator<ChildRec<T>>())  {}
         inline ChildList(const ChildList& list) : inherited(list)  {}
         inline ChildList(ChildList&& list) : inherited(std::move(list))  {}
         inline ChildList(std::initializer_list<T> il)
                  : inherited(il,std::allocator<ChildRec<T>>())  {}
         template<typename InputIterator>
         inline ChildList(InputIterator first,InputIterator last)
                  : inherited(first,last,std::allocator<ChildRec<T>>())  {}

         inline ChildIterator         childBegin() const   { return ChildIterator(); }//ChildIterator(((ChildList<T>*)this)->inherited::begin()); }
         inline ChildIterator         childEnd() const     { return ChildIterator(((ChildList<T>*)this)->inherited::end()); }
         inline ChildReverseIterator  childRBegin() const  { return ChildReverseIterator(((ChildList<T>*)this)->inherited::rbegin()); }
         inline ChildReverseIterator  childREnd() const    { return ChildReverseIterator(((ChildList<T>*)this)->inherited::rend()); }

         inline ChildList& operator=(const ChildList& list)  { return inheritedList::operator=(list); }
         inline ChildList& operator=(ChildList&& list)  { return inheritedList::operator=(list); }
         inline ChildList& operator=(std::initializer_list<T> il)  { return inheritedList::operator=(il); }

      };

      template<typename T>
      class ParentList : public ParentChildList<T,ParentRec<T>>
      {
      protected:
         typedef ParentChildList<T,ParentRec<T>> inherited;
         typedef typename inherited::inherited inheritedList;
      public:

         struct ParentIterator : public inherited::ParentChildIterator
         {
         private:
            typedef typename ParentChildList<T,ParentRec<T>>::ParentChildIterator inherited;

         public:

            typedef const std::weak_ptr<T>           value_type;
            typedef const std::weak_ptr<T>*          pointer;
            typedef const std::weak_ptr<T>&          reference;

            inline ParentIterator()  {}
            inline ParentIterator(const ParentIterator& it) : inherited(it.getInternalIterator())  {}
            inline ParentIterator(typename std::list<ParentRec<T>>::iterator recIt) : inherited(recIt)  {}

            inline reference operator*() const  { return inherited::_it->parent; }
            inline pointer operator->() const   { return std::__addressof(inherited::_it->parent); }
         };

         typedef std::reverse_iterator<ParentIterator>  ParentReverseIterator;


         inline ParentIterator         childBegin() const   { return ParentIterator(((ParentList<T>*)this)->begin()); }
         inline ParentIterator         childEnd() const     { return ParentIterator(((ParentList<T>*)this)->end()); }
         inline ParentReverseIterator  childRBegin() const  { return ParentReverseIterator(((ParentList<T>*)this)->rbegin()); }
         inline ParentReverseIterator  childREnd() const    { return ParentReverseIterator(((ParentList<T>*)this)->rend()); }
      };

   }
}

#endif // GE_SG_CHILD_LIST_H
