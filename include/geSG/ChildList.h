#ifndef GE_SG_CHILD_LIST_H
#define GE_SG_CHILD_LIST_H

#include <memory>
#include <list>

namespace ge
{
   namespace sg
   {

      template<typename T>
      struct ChildRec {
         std::shared_ptr<T> child;
         typename std::list<T*>::iterator parentsDeleteIt;
         ChildRec(std::shared_ptr<T> ch,typename std::list<T*>::iterator it)
                  : child(ch),parentsDeleteIt(it)  {}
      };

#if 1
      template<typename T, typename Alloc = std::allocator<T> >
      class ChildList : public std::list<ChildRec<T>, Alloc>
      {
      public:

         struct ChildIterator
         {
         protected:

            typename std::list<ChildRec<T> >::iterator _it;

         public:

            typedef std::ptrdiff_t                     difference_type;
            typedef std::bidirectional_iterator_tag    iterator_category;
            typedef const std::shared_ptr<T>           value_type;
            typedef const std::shared_ptr<T>*          pointer;
            typedef const std::shared_ptr<T>&          reference;

            inline ChildIterator()  {}
            inline ChildIterator(const ChildIterator& it) : _it(it.getInternalIterator())  {}
            inline ChildIterator(typename std::list<ChildRec<T> >::iterator recIt) : _it(recIt)  {}

            inline reference operator*() const  { return _it->child; }
            inline pointer operator->() const   { return std::__addressof(_it->child); }

            inline typename std::list<ChildRec<T> >::iterator getInternalIterator() const  { return _it; }

            ChildIterator& operator++()     { _it++; return *this; }
            ChildIterator  operator++(int)  { ChildIterator tmp = *this; _it++; return tmp; }
            ChildIterator& operator--()     { _it--; return *this; }
            ChildIterator  operator--(int)  { ChildIterator tmp = *this; _it--; return tmp; }

            bool operator==(const ChildIterator& rhs) const  { return _it == rhs._it; }
            bool operator!=(const ChildIterator& rhs) const  { return _it != rhs._it; }
         };


         typedef std::list<ChildRec<T>, Alloc>                  inherited;
         typedef std::reverse_iterator<ChildIterator>       ChildReverseIterator;


         inline ChildIterator         childBegin() const   { return ChildIterator(((ChildList<T,Alloc>*)this)->inherited::begin()); }
         inline ChildIterator         childEnd() const     { return ChildIterator(((ChildList<T,Alloc>*)this)->inherited::end()); }
         inline ChildReverseIterator  childRBegin() const  { return ChildReverseIterator(((ChildList<T,Alloc>*)this)->inherited::rbegin()); }
         inline ChildReverseIterator  childREnd() const    { return ChildReverseIterator(((ChildList<T,Alloc>*)this)->inherited::rend()); }


         inline ChildList()  {}
         inline explicit ChildList(const Alloc& a) : inherited(a)  {}
         inline explicit ChildList(size_t n) : inherited(n)  {}
         inline ChildList(size_t n,const T& value,const Alloc& a = Alloc())
                  : inherited(n,value,a)  {}
         inline ChildList(const ChildList& list) : inherited(list)  {}
         inline ChildList(ChildList&& list) : inherited(std::move(list))  {}
         inline ChildList(std::initializer_list<T> il,const Alloc& a = Alloc())
                  : inherited(il,a)  {}
         template<typename InputIterator>
         inline ChildList(InputIterator first,InputIterator last,const Alloc& a = Alloc())
                  : inherited(first,last,a)  {}

         inline ChildList& operator=(const ChildList& list)  { return inherited::operator=(list); }
         inline ChildList& operator=(ChildList&& list)  { return inherited::operator=(list); }
         inline ChildList& operator=(std::initializer_list<T> il)  { return inherited::operator=(il); }
         inline void assign(size_t n, const T& value)  { inherited::assign(n,value); }

      };

#elif 1
      template<typename T, typename Alloc = std::allocator<T> >
      class ChildList : public std::list<ChildRec<T>, Alloc>
      {
      public:

         struct ChildOnlyIterator
         {
            typedef std::ptrdiff_t                     difference_type;
            typedef std::bidirectional_iterator_tag    iterator_category;
            typedef T                                  value_type;
            typedef T*                                 pointer;
            typedef T&                                 reference;

            typename std::list<ChildRec<T> >::iterator _it;

            inline ChildOnlyIterator()  {}
            inline ChildOnlyIterator(typename std::list<ChildRec<T> >::iterator &recIt) : _it(recIt)  {}

            inline reference operator*() const  { return _it->child; }
            inline pointer operator->() const   { return std::__addressof(_it->child); }

            inline typename std::list<ChildRec<T> >::iterator getInternalIterator() const  { return _it; }

            ChildOnlyIterator& operator++()     { _it++; return *this; }
            ChildOnlyIterator  operator++(int)  { ChildOnlyIterator tmp = *this; _it++; return tmp; }
            ChildOnlyIterator& operator--()     { _it--; return *this; }
            ChildOnlyIterator  operator--(int)  { ChildOnlyIterator tmp = *this; _it--; return tmp; }

            bool operator==(const ChildOnlyIterator& rhs) const  { return _it == rhs._it; }
            bool operator!=(const ChildOnlyIterator& rhs) const  { return _it != rhs._it; }
         };

         struct ChildOnlyConstIterator
         {
            typedef std::ptrdiff_t                     difference_type;
            typedef std::bidirectional_iterator_tag    iterator_category;
            typedef T                                  value_type;
            typedef const T*                           pointer;
            typedef const T&                           reference;

            typename std::list<ChildRec<T> >::const_iterator _it;

            inline ChildOnlyConstIterator()  {}
            inline ChildOnlyConstIterator(const ChildOnlyIterator& it) : _it(it.getInternalIterator())  {}
            inline ChildOnlyConstIterator(const ChildOnlyConstIterator& it) : _it(it.getInternalIterator())  {}
            inline ChildOnlyConstIterator(typename std::list<ChildRec<T> >::iterator& recIt) : _it(recIt)  {}
            inline ChildOnlyConstIterator(typename std::list<ChildRec<T> >::const_iterator recIt) : _it(recIt)  {}

            inline reference operator*() const  { return _it->child; }
            inline pointer operator->() const   { return std::__addressof(_it->child); }

            inline typename std::list<ChildRec<T> >::const_iterator getInternalIterator() const  { return _it; }

            ChildOnlyConstIterator& operator++()     { _it++; return *this; }
            ChildOnlyConstIterator  operator++(int)  { ChildOnlyConstIterator tmp = *this; _it++; return tmp; }
            ChildOnlyConstIterator& operator--()     { _it--; return *this; }
            ChildOnlyConstIterator  operator--(int)  { ChildOnlyConstIterator tmp = *this; _it--; return tmp; }

            bool operator==(const ChildOnlyConstIterator& rhs) const  { return _it == rhs._it; }
            bool operator!=(const ChildOnlyConstIterator& rhs) const  { return _it != rhs._it; }
         };


         typedef std::list<ChildRec<T>, Alloc>                  inherited;
         typedef std::reverse_iterator<ChildOnlyIterator>       ChildOnlyReverseIterator;
         typedef std::reverse_iterator<ChildOnlyConstIterator>  ChildOnlyConstReverseIterator;


         inline ChildOnlyIterator       begin()        { return ChildOnlyIterator(inherited::begin()); }
         inline ChildOnlyIterator       end()          { return ChildOnlyIterator(inherited::end()); }
         inline ChildOnlyConstIterator  begin() const  { return ChildOnlyConstIterator(inherited::begin()); }
         inline ChildOnlyConstIterator  end() const    { return ChildOnlyConstIterator(inherited::end()); }
         inline ChildOnlyReverseIterator       rbegin()        { return ChildOnlyReverseIterator(inherited::rbegin()); }
         inline ChildOnlyReverseIterator       rend()          { return ChildOnlyReverseIterator(inherited::rend()); }
         inline ChildOnlyConstReverseIterator  rbegin() const  { return ChildOnlyConstReverseIterator(inherited::rbegin()); }
         inline ChildOnlyConstReverseIterator  rend() const    { return ChildOnlyConstReverseIterator(inherited::rend()); }
         inline ChildOnlyConstIterator         cbegin() const   { return ChildOnlyConstIterator(inherited::cbegin()); }
         inline ChildOnlyConstIterator         cend() const     { return ChildOnlyConstIterator(inherited::cend()); }
         inline ChildOnlyConstReverseIterator  crbegin() const  { return ChildOnlyConstReverseIterator(inherited::crbegin()); }
         inline ChildOnlyConstReverseIterator  crend() const    { return ChildOnlyConstReverseIterator(inherited::crend()); }


         inline ChildList()  {}
         inline explicit ChildList(const Alloc& a) : inherited(a)  {}
         inline explicit ChildList(size_t n) : inherited(n)  {}
         inline ChildList(size_t n,const T& value,const Alloc& a = Alloc())
                  : inherited(n,value,a)  {}
         inline ChildList(const ChildList& list) : inherited(list)  {}
         inline ChildList(ChildList&& list) : inherited(std::move(list))  {}
         inline ChildList(std::initializer_list<T> il,const Alloc& a = Alloc())
                  : inherited(il,a)  {}
         template<typename InputIterator>
         inline ChildList(InputIterator first,InputIterator last,const Alloc& a = Alloc())
                  : inherited(first,last,a)  {}

         inline ChildList& operator=(const ChildList& list)  { return inherited::operator=(list); }
         inline ChildList& operator=(ChildList&& list)  { return inherited::operator=(list); }
         inline ChildList& operator=(std::initializer_list<T> il)  { return inherited::operator=(il); }
         inline void assign(size_t n, const T& value)  { inherited::assign(n,value); }

      };

#else
      template<typename T, typename _Alloc = std::allocator<T> >
      class ChildList : protected std::list<ChildRec<T>, _Alloc>
      {
      public:

         struct Iterator
         {
            typedef std::ptrdiff_t                     difference_type;
            typedef std::bidirectional_iterator_tag    iterator_category;
            typedef T                                  value_type;
            typedef T*                                 pointer;
            typedef T&                                 reference;

            typename std::list<ChildRec<T> >::iterator _it;

            inline Iterator()  {}
            inline Iterator(typename std::list<ChildRec<T> >::iterator &recIt) : _it(recIt)  {}

            inline reference operator*() const  { return _it->child; }
            inline pointer operator->() const   { return std::__addressof(_it->child); }

            Iterator& operator++()     { _it++; return *this; }
            Iterator  operator++(int)  { Iterator __tmp = *this; _it++; return __tmp; }
            Iterator& operator--()     { _it--; return *this; }
            Iterator  operator--(int)  { Iterator __tmp = *this; _it--; return __tmp; }

            bool operator==(const Iterator& __x) const  { return _it == __x._it; }
            bool operator!=(const Iterator& __x) const  { return _it != __x._it; }
         };

         struct ConstIterator
         {
            typedef std::ptrdiff_t                     difference_type;
            typedef std::bidirectional_iterator_tag    iterator_category;
            typedef T                                  value_type;
            typedef const T*                           pointer;
            typedef const T&                           reference;

            typename std::list<ChildRec<T> >::const_iterator _it;

            inline ConstIterator()  {}
            inline ConstIterator(const Iterator& __x) : _it(__x)  {}
            inline ConstIterator(typename std::list<ChildRec<T> >::const_iterator &recIt) : _it(recIt)  {}

            inline reference operator*() const  { return _it->child; }
            inline pointer operator->() const   { return std::__addressof(_it->child); }

            ConstIterator& operator++()     { _it++; return *this; }
            ConstIterator  operator++(int)  { ConstIterator __tmp = *this; _it++; return __tmp; }
            ConstIterator& operator--()     { _it--; return *this; }
            ConstIterator  operator--(int)  { ConstIterator __tmp = *this; _it--; return __tmp; }

            bool operator==(const ConstIterator& __x) const  { return _it == __x._it; }
            bool operator!=(const ConstIterator& __x) const  { return _it != __x._it; }
         };


         typedef std::list<ChildRec<T>, _Alloc>             _Base;
         typedef typename _Alloc::template rebind<T>::other _Tp_alloc_type;

         typedef T                                          value_type;
         typedef typename _Tp_alloc_type::pointer           pointer;
         typedef typename _Tp_alloc_type::const_pointer     const_pointer;
         typedef typename _Tp_alloc_type::reference         reference;
         typedef typename _Tp_alloc_type::const_reference   const_reference;
         typedef Iterator                                   iterator;
         typedef ConstIterator                              const_iterator;
         typedef std::reverse_iterator<const_iterator>      const_reverse_iterator;
         typedef std::reverse_iterator<iterator>            reverse_iterator;
         typedef size_t                                     size_type;
         typedef std::ptrdiff_t                             difference_type;
         typedef _Alloc                                     allocator_type;

         inline ChildList()  {}
         inline explicit ChildList(const allocator_type& __a) : _Base(__a)  {}
         inline explicit ChildList(size_type __n) : _Base(__n)  {}
         inline ChildList(size_type __n, const value_type& __value,
                          const allocator_type& __a = allocator_type())
                          : _Base(__n, __value, __a)  {}
         inline ChildList(const ChildList& __x) : _Base(__x)  {}
         inline ChildList(ChildList&& __x) : _Base(std::move(__x))  {}
         inline ChildList(std::initializer_list<value_type> __l,
                          const allocator_type& __a = allocator_type())
                          : _Base(__l, __a)  {}

         template<typename _InputIterator>
         inline ChildList(_InputIterator __first, _InputIterator __last,
                          const allocator_type& __a = allocator_type())
                          : _Base(__first, __last, __a)  {}

         inline ChildList& operator=(const ChildList& __x)  { return _Base::operator=(__x); }
         inline ChildList& operator=(ChildList&& __x)  { return _Base::operator=(__x); }
         inline ChildList& operator=(std::initializer_list<value_type> __l)  { return _Base::operator=(__l); }
         inline void assign(size_type __n, const value_type& __val)  { _Base::assign(__n, __val); }

         template<typename _InputIterator>
         inline void assign(_InputIterator __first, _InputIterator __last)  { _Base::assign(__first, __last); }
         inline void assign(std::initializer_list<value_type> __l)  { _Base::assign(__l); }
         inline allocator_type get_allocator() const  { return _Base::get_allocator(); }

         inline iterator begin()  { return _Base::begin(); }
         inline const_iterator begin() const  { return _Base::begin(); }
         inline iterator end()  { return _Base::end(); }
         inline const_iterator end() const  { return _Base::end(); }
         inline reverse_iterator rbegin()  { return _Base::rbegin(); }
         inline const_reverse_iterator rbegin() const  { return _Base::rbegin(); }
         inline reverse_iterator rend()  { return _Base::rend(); }
         inline const_reverse_iterator rend() const  { return _Base::rend(); }
         inline const_iterator cbegin() const  { return _Base::cbegin(); }
         inline const_iterator cend() const  { return _Base::cend(); }
         inline const_reverse_iterator crbegin() const  { return _Base::crbegin(); }
         inline const_reverse_iterator crend() const  { return _Base::crend(); }

         inline bool empty() const  { return _Base::empty(); }
         inline size_type size() const  { return _Base::size(); }
         inline size_type max_size() const  { return _Base::max_size(); }
         inline void resize(size_type __new_size)  { _Base::resize(__new_size); }
         inline void resize(size_type __new_size, const value_type& __x)  { _Base::resize(__new_size, __x); }

         inline reference front()  { return _Base::front(); }
         inline const_reference front() const  { return _Base::front(); }
         inline reference back()  { return _Base::back(); }
         inline const_reference back() const  { return _Base::back(); }
         inline void push_front(const value_type& __x)  { _Base::push_front(__x); }
         inline void push_front(value_type&& __x)  { _Base::push_front(__x); }
         template<typename... _Args>
         inline void emplace_front(_Args&&... __args)  { _Base::emplace_front(__args...); }
         inline void pop_front()  { _Base::pop_front(); }
         inline void push_back(const value_type& __x)  { _Base::push_back(__x); }
         inline void push_back(value_type&& __x)  { _Base::push_back(__x); }
         template<typename... _Args>
         inline void emplace_back(_Args&&... __args)  { _Base::emplace_back(__args...); }
         inline void pop_back()  { _Base::pop_back(); }
         template<typename... _Args>
         inline iterator emplace(iterator __position, _Args&&... __args)  { _Base::emplace(__position, __args...); }

         inline iterator insert(iterator __position, const value_type& __x)  { return _Base::insert(__position, __x); }
         inline iterator insert(iterator __position, value_type&& __x)  { return _Base::insert(__position, __x); }
         inline void insert(iterator __p, std::initializer_list<value_type> __l)  { _Base::insert(__p, __l); }
         inline void insert(iterator __position, size_type __n, const value_type& __x)  { _Base::insert(__position, __n, __x); }
         template<typename _InputIterator>
         inline void insert(iterator __position, _InputIterator __first, _InputIterator __last)
               { _Base::insert(__position,__first,__last); }
         inline iterator erase(iterator __position)  { return _Base::erase(__position); }
         inline iterator erase(iterator __first, iterator __last)  { return _Base::erase(__first,__last); }

         inline void swap(ChildList& __x)  { _Base::swap(__x); }
         inline void clear()  { _Base::clear(); }
         inline void splice(iterator __position, ChildList&& __x)  { _Base::splice(__position,__x); }
         inline void splice(iterator __position, ChildList& __x)  { _Base::splice(__position,__x); }
         inline void splice(iterator __position, ChildList&& __x, iterator __i)  { _Base::splice(__position,__x,__i); }
         inline void splice(iterator __position, ChildList& __x, iterator __i)  { _Base::splice(__position,__x,__i); }
         inline void splice(iterator __position, ChildList&& __x, iterator __first, iterator __last)  { _Base::splice(__position,__x,__first,__last); }
         inline void splice(iterator __position, ChildList& __x, iterator __first, iterator __last)  { _Base::splice(__position,__x,__first,__last); }
         inline void remove(const T& __value)  { _Base::remove(__value); }
         template<typename _Predicate>
         inline void remove_if(_Predicate p)  { _Base::remove_if(p); }
         inline void unique()  { _Base::unique(); }
         template<typename _BinaryPredicate>
         inline void unique(_BinaryPredicate p)  {_Base::unique(p); }
         inline void merge(ChildList&& __x)  { _Base::merge(__x); }
         inline void merge(ChildList& __x)  { _Base::merge(__x); }
         template<typename _StrictWeakOrdering>
         inline void merge(ChildList&& l, _StrictWeakOrdering comp)  { _Base::merge(l,comp); }
         template<typename _StrictWeakOrdering>
         inline void merge(ChildList& __x, _StrictWeakOrdering __comp)  { _Base::merge(__x,__comp); }
         inline void reverse()  { _Base::reverse(); }
         inline void sort()  { _Base::sort(); }
         template<typename _StrictWeakOrdering>
         inline void sort(_StrictWeakOrdering comp)  { _Base::sort(comp); }
      };

      template<typename T>
      inline bool operator==(const typename ChildList<T>::const_iterator& __x,
                             const typename ChildList<T>::iterator& __y)
                            { return __x._it == __y._it; }

      template<typename T>
      inline bool operator!=(const typename ChildList<T>::iterator& __x,
                             const typename ChildList<T>::const_iterator& __y)
                            { return __x._it != __y._it; }

      template<typename _Tp, typename _Alloc>
      inline bool operator==(const ChildList<_Tp, _Alloc>& __x, const ChildList<_Tp, _Alloc>& __y)
      { return operator==((const typename ChildList<_Tp, _Alloc>::_Base&)__x,
                          (const typename ChildList<_Tp, _Alloc>::_Base&)__y); }
      template<typename _Tp, typename _Alloc>
      inline bool operator<(const ChildList<_Tp, _Alloc>& __x, const ChildList<_Tp, _Alloc>& __y)
      { return operator<((const typename ChildList<_Tp, _Alloc>::_Base&)__x,
                         (const typename ChildList<_Tp, _Alloc>::_Base&)__y); }
      template<typename _Tp, typename _Alloc>
      inline bool operator!=(const ChildList<_Tp, _Alloc>& __x, const ChildList<_Tp, _Alloc>& __y)
      { return operator!=((const typename ChildList<_Tp,_Alloc>::_Base&)__x,
                          (const typename ChildList<_Tp,_Alloc>::_Base&)__y); }
      template<typename _Tp, typename _Alloc>
      inline bool operator>(const ChildList<_Tp, _Alloc>& __x, const ChildList<_Tp, _Alloc>& __y)
      { return operator>((const typename ChildList<_Tp,_Alloc>::_Base&)__x,
                         (const typename ChildList<_Tp,_Alloc>::_Base&)__y); }
      template<typename _Tp, typename _Alloc>
      inline bool operator<=(const ChildList<_Tp, _Alloc>& __x, const ChildList<_Tp, _Alloc>& __y)
      { return operator<=((const typename ChildList<_Tp,_Alloc>::_Base&)__x,
                          (const typename ChildList<_Tp,_Alloc>::_Base&)__y); }
      template<typename _Tp, typename _Alloc>
      inline bool operator>=(const ChildList<_Tp, _Alloc>& __x, const ChildList<_Tp, _Alloc>& __y)
      { return operator>=((const typename ChildList<_Tp,_Alloc>::_Base&)__x,
                          (const typename ChildList<_Tp,_Alloc>::_Base&)__y); }
      template<typename _Tp, typename _Alloc>
      inline void swap(ChildList<_Tp, _Alloc>& __x, ChildList<_Tp, _Alloc>& __y)
      { return operator>=((const typename ChildList<_Tp,_Alloc>::_Base&)__x,
                          (const typename ChildList<_Tp,_Alloc>::_Base&)__y); }
#endif
   }
}

#endif // GE_SG_CHILD_LIST_H
