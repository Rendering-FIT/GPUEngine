#ifndef GE_SG_PARENT_CHILD_LIST_H
#define GE_SG_PARENT_CHILD_LIST_H

#include <memory>
#include <list>

namespace ge
{
   namespace sg
   {

      template<typename T,typename ParentT> class ChildListTemplate;
      template<typename T,typename ChildT> class ParentListTemplate;

      template<typename T,typename ParentT=T>
      struct ChildRecTemplate
      {
         std::shared_ptr<T> child;
         typename ParentListTemplate<ParentT,T>::iterator peerIt;
         ChildRecTemplate(std::shared_ptr<T> node,typename ParentListTemplate<ParentT,T>::iterator it)
                  : child(node),peerIt(it) {}
      };

      template<typename T,typename ChildT=T>
      struct ParentRecTemplate
      {
         std::weak_ptr<T> parent;
         typename ChildListTemplate<ChildT,T>::iterator peerIt;
         ParentRecTemplate(std::weak_ptr<T> node,typename ChildListTemplate<ChildT,T>::iterator it)
                  : parent(node),peerIt(it) {}
      };

      template<typename T,typename Rec>
      class ParentChildListTemplate : public std::list<Rec>
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
      class ChildListTemplate : public ParentChildListTemplate<T,ChildRecTemplate<T,ParentT>>
      {
      protected:
         typedef ParentChildListTemplate<T,ChildRecTemplate<T,ParentT>> inherited;
         typedef typename inherited::inherited inheritedList;
      public:

         struct ChildIterator : inherited::ParentChildIterator
         {
         protected:
            typedef typename ParentChildListTemplate<T,ChildRecTemplate<T,ParentT>>::ParentChildIterator inherited;

         public:

            typedef const std::shared_ptr<T>           value_type;
            typedef const std::shared_ptr<T>*          pointer;
            typedef const std::shared_ptr<T>&          reference;

            inline ChildIterator()  {}
            inline ChildIterator(const ChildIterator& it) : inherited(it.getInternalIterator())  {}
            inline ChildIterator(typename std::list<ChildRecTemplate<T,ParentT>>::iterator recIt) : inherited(recIt)  {}

            inline reference operator*() const  { return inherited::_it->child; }
            inline pointer operator->() const   { return std::__addressof(inherited::_it->child); }
         };

         typedef std::reverse_iterator<ChildIterator>  ChildReverseIterator;


         inline ChildListTemplate()  {}
         //inline explicit ChildListTemplate(const Alloc& a) : inherited(a)  {}
         inline explicit ChildListTemplate(size_t n) : inheritedList(n)  {}
         inline ChildListTemplate(size_t n,const T& value)
                  : inherited(n,value,std::allocator<ChildRecTemplate<T,ParentT>>())  {}
         inline ChildListTemplate(const ChildListTemplate& list) : inherited(list)  {}
         inline ChildListTemplate(ChildListTemplate&& list) : inherited(std::move(list))  {}
         inline ChildListTemplate(std::initializer_list<T> il)
                  : inherited(il,std::allocator<ChildRecTemplate<T,ParentT>>())  {}
         template<typename InputIterator>
         inline ChildListTemplate(InputIterator first,InputIterator last)
                  : inherited(first,last,std::allocator<ChildRecTemplate<T,ParentT>>())  {}

         inline ChildIterator         childBegin() const   { return ChildIterator(((ChildListTemplate<T,ParentT>*)this)->inherited::begin()); }
         inline ChildIterator         childEnd() const     { return ChildIterator(((ChildListTemplate<T,ParentT>*)this)->inherited::end()); }
         inline ChildReverseIterator  childRBegin() const  { return ChildReverseIterator(((ChildListTemplate<T,ParentT>*)this)->inherited::rbegin()); }
         inline ChildReverseIterator  childREnd() const    { return ChildReverseIterator(((ChildListTemplate<T,ParentT>*)this)->inherited::rend()); }

         inline ChildListTemplate& operator=(const ChildListTemplate& list)  { return inheritedList::operator=(list); }
         inline ChildListTemplate& operator=(ChildListTemplate&& list)  { return inheritedList::operator=(list); }
         inline ChildListTemplate& operator=(std::initializer_list<T> il)  { return inheritedList::operator=(il); }

      };

      template<typename T,typename ChildT=T>
      class ParentListTemplate : public ParentChildListTemplate<T,ParentRecTemplate<T,ChildT>>
      {
      protected:
         typedef ParentChildListTemplate<T,ParentRecTemplate<T,ChildT>> inherited;
         typedef typename inherited::inherited inheritedList;
      public:

         struct ParentIterator : public inherited::ParentChildIterator
         {
         private:
            typedef typename ParentChildListTemplate<T,ParentRecTemplate<T,ChildT>>::ParentChildIterator inherited;

         public:

            typedef const std::weak_ptr<T>           value_type;
            typedef const std::weak_ptr<T>*          pointer;
            typedef const std::weak_ptr<T>&          reference;

            inline ParentIterator()  {}
            inline ParentIterator(const ParentIterator& it) : inherited(it.getInternalIterator())  {}
            inline ParentIterator(typename std::list<ParentRecTemplate<T,ChildT>>::iterator recIt) : inherited(recIt)  {}

            inline reference operator*() const  { return inherited::_it->parent; }
            inline pointer operator->() const   { return std::__addressof(inherited::_it->parent); }
         };

         typedef std::reverse_iterator<ParentIterator>  ParentReverseIterator;


         inline ParentIterator         childBegin() const   { return ParentIterator(((ParentListTemplate<T,ChildT>*)this)->begin()); }
         inline ParentIterator         childEnd() const     { return ParentIterator(((ParentListTemplate<T,ChildT>*)this)->end()); }
         inline ParentReverseIterator  childRBegin() const  { return ParentReverseIterator(((ParentListTemplate<T,ChildT>*)this)->rbegin()); }
         inline ParentReverseIterator  childREnd() const    { return ParentReverseIterator(((ParentListTemplate<T,ChildT>*)this)->rend()); }
      };

   }
}

#endif // GE_SG_PARENT_CHILD_LIST_H
