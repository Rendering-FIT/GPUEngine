#ifndef GE_SG_PARENT_CHILD_LIST_H
#define GE_SG_PARENT_CHILD_LIST_H

#include <memory>
#include <list>

namespace ge
{
   namespace sg
   {

      template<typename T,typename ChildListT>
      class ParentPointerAbstractTemplate {
      public:
         std::weak_ptr<T> parent;
         typename ChildListT::iterator childListDeleteIterator;

         inline ParentPointerAbstractTemplate() {}
         inline ParentPointerAbstractTemplate(const std::weak_ptr<T>& aParent,typename ChildListT::iterator aChildListDeleteIterator)
               : parent(aParent),childListDeleteIterator(childListDeleteIterator) {}
         inline ParentPointerAbstractTemplate(const std::shared_ptr<T>& aParent,typename ChildListT::iterator aChildListDeleteIterator)
               : parent(aParent),childListDeleteIterator(aChildListDeleteIterator) {}
      };

      template<typename T,typename ParentListT>
      class ChildPointerAbstractTemplate {
      public:
         std::shared_ptr<T> child;
         typename ParentListT::iterator parentListDeleteIterator;

         inline ChildPointerAbstractTemplate() {}
         inline ChildPointerAbstractTemplate(const std::shared_ptr<T>& aChild,typename ParentListT::iterator aParentListDeleteIterator)
               : child(aChild),parentListDeleteIterator(aParentListDeleteIterator) {}
      };

      template<typename T>
      class ChildSimpleListTemplate : public std::list<std::shared_ptr<T>> {};

      template<typename T,typename ChildT>
      class ParentPointerTemplate : public ParentPointerAbstractTemplate<T,ChildSimpleListTemplate<ChildT>> {};

      template<typename T>
      class ParentSimpleListTemplate : public std::list<std::weak_ptr<T>> {};

      template<typename T,typename ParentT>
      class ChildPointerTemplate : public ChildPointerAbstractTemplate<T,ParentSimpleListTemplate<ParentT>> {};

      #define LIST_PUBLIC_INTERFACE(_list_name_,_list_type_,_item_reference_,_container_type_,_prefix_name_) \
         public: \
            inline _list_type_::iterator _prefix_name_##BeginIterator() { _list_name_.begin(); } \
            inline _list_type_::iterator _prefix_name_##EndIterator() const { _list_name_.end(); } \
            inline _list_type_::reverse_iterator _prefix_name_##RBeginIterator() { _list_name_.rbegin(); } \
            inline _list_type_::reverse_iterator _prefix_name_##REndIterator() const { _list_name_.rend(); } \
            inline _list_type_::iterator _prefix_name_##Append(_item_reference_ item) { return _list_name_.insert(_list_name_.end(),item); } \
            inline void _prefix_name_##Remove(_list_type_::iterator it) { _list_name_.erase(it); } \
            inline _list_type_& _prefix_name_##GetList() { return _list_name_; } \
            static inline _list_type_& _prefix_name_##GetList(_container_type_ *container) { return container->_list_name_; }


      template<typename T,typename ParentT> class ChildListTemplate;
      template<typename T,typename ChildT> class ParentListTemplate;

      template<typename T,typename PointerT>
      class AbstractListTemplate : public std::list<PointerT>
      {
      protected:
         typedef std::list<PointerT> inherited;
      public:

         class AbstractIterator
         {
         protected:

            typename std::list<PointerT>::iterator _it;

         public:

            typedef std::ptrdiff_t                     difference_type;
            typedef std::bidirectional_iterator_tag    iterator_category;

            inline AbstractIterator()  {}
            inline AbstractIterator(typename std::list<PointerT>::iterator it) : _it(it)  {}

            inline typename std::list<PointerT>::iterator getInternalIterator() const  { return _it; }

            inline AbstractIterator& operator++()     { _it++; return *this; }
            inline AbstractIterator  operator++(int)  { AbstractIterator tmp = *this; _it++; return tmp; }
            inline AbstractIterator& operator--()     { _it--; return *this; }
            inline AbstractIterator  operator--(int)  { AbstractIterator tmp = *this; _it--; return tmp; }

            inline bool operator==(const AbstractIterator& rhs) const  { return _it == rhs._it; }
            inline bool operator!=(const AbstractIterator& rhs) const  { return _it != rhs._it; }
         };

         inline void assign(size_t n, const T& value)  { inherited::assign(n,value); }
      };

      template<typename T,typename ParentT=T>
      class ChildListTemplate : public AbstractListTemplate<T,ChildPointerAbstractTemplate<T,ParentListTemplate<ParentT,T>>>
      {
      public:
         typedef ChildPointerAbstractTemplate<T,ParentListTemplate<ParentT,T>> ChildData;
      protected:
         typedef AbstractListTemplate<T,ChildData> inherited;
		 typedef AbstractListTemplate<T,ChildData>::inherited inheritedList;
	  public:

         struct ChildIterator : inherited::AbstractIterator
         {
         protected:
            typedef typename AbstractListTemplate<T,ChildData>::AbstractIterator inherited;

         public:

            typedef const std::shared_ptr<T>           value_type;
            typedef const std::shared_ptr<T>*          pointer;
            typedef const std::shared_ptr<T>&          reference;

            inline ChildIterator()  {}
            inline ChildIterator(const ChildIterator& it) : inherited(it.getInternalIterator())  {}
            inline ChildIterator(typename std::list<ChildData>::iterator it) : inherited(it)  {}

            inline reference operator*() const  { return inherited::_it->child; }
            inline pointer operator->() const   { return std::__addressof(inherited::_it->child); }
         };

         typedef std::reverse_iterator<ChildIterator>  ChildReverseIterator;


         inline ChildListTemplate()  {}
         inline explicit ChildListTemplate(size_t n) : inheritedList(n)  {}
         inline ChildListTemplate(size_t n,const T& value)
                  : inherited(n,value)  {}
         inline ChildListTemplate(const ChildListTemplate& list) : inherited(list)  {}
         inline ChildListTemplate(ChildListTemplate&& list) : inherited(std::move(list))  {}
         inline ChildListTemplate(std::initializer_list<T> il) : inherited(il)  {}
         template<typename InputIterator>
         inline ChildListTemplate(InputIterator first,InputIterator last) : inherited(first,last)  {}

         inline ChildIterator         childBegin() const   { return ChildIterator(((ChildListTemplate<T,ParentT>*)this)->inherited::begin()); }
         inline ChildIterator         childEnd() const     { return ChildIterator(((ChildListTemplate<T,ParentT>*)this)->inherited::end()); }
         inline ChildReverseIterator  childRBegin() const  { return ChildReverseIterator(((ChildListTemplate<T,ParentT>*)this)->inherited::rbegin()); }
         inline ChildReverseIterator  childREnd() const    { return ChildReverseIterator(((ChildListTemplate<T,ParentT>*)this)->inherited::rend()); }

         inline ChildListTemplate& operator=(const ChildListTemplate& list)  { return inheritedList::operator=(list); }
         inline ChildListTemplate& operator=(ChildListTemplate&& list)  { return inheritedList::operator=(list); }
         inline ChildListTemplate& operator=(std::initializer_list<T> il)  { return inheritedList::operator=(il); }

      };

      template<typename T,typename ChildT=T>
      class ParentListTemplate : public AbstractListTemplate<T,ParentPointerAbstractTemplate<T,ChildListTemplate<ChildT,T>>>
      {
      public:
         typedef ParentPointerAbstractTemplate<T,ChildListTemplate<ChildT,T>> ParentData;
      protected:
         typedef AbstractListTemplate<T,ParentData> inherited;
		 typedef AbstractListTemplate<T,ParentData>::inherited inheritedList;
      public:

         struct ParentIterator : public inherited::AbstractIterator
         {
         private:
            typedef typename AbstractListTemplate<T,ParentData>::AbstractIterator inherited;

         public:

            typedef const std::weak_ptr<T>           value_type;
            typedef const std::weak_ptr<T>*          pointer;
            typedef const std::weak_ptr<T>&          reference;

            inline ParentIterator()  {}
            inline ParentIterator(const ParentIterator& it) : inherited(it.getInternalIterator())  {}
            inline ParentIterator(typename std::list<ParentData>::iterator it) : inherited(it)  {}

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
