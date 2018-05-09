#ifndef GE_RG_PARENT_CHILD_LIST_H
#define GE_RG_PARENT_CHILD_LIST_H

#include <algorithm>
#include <list>
#include <memory>
#include <type_traits>

#if defined(__GNUC__) && (__GNUC__==4) && (__GNUC_MINOR__<=9)
// g++ is missing is_trivially_copyable (seen on g++ 4.8.2 and 4.9.2)
namespace std { template<typename T> struct is_trivially_copyable : is_trivial<T> {}; }
#endif

namespace ge
{
   namespace rg
   {
      template<typename ChildT,typename ParentT> class ChildPointerAbstractTemplate;
      template<typename ParentT,typename ChildT> class ParentPointerAbstractTemplate;

      /** Pointer to the child abstraction. */
      template<typename ChildT,typename ParentT>
      class ChildPointerAbstractTemplate {
      public:

         typedef typename std::conditional<std::is_trivially_copyable<ChildT>::value &&
               sizeof(ChildT)<=sizeof(void*),ChildT,const ChildT&>::type ChildParamT;
         typedef typename std::list<ParentPointerAbstractTemplate<ParentT,
               ChildT>>::iterator ParentListDeleteIterator;

         ChildT child;
         ParentListDeleteIterator parentListDeleteIterator;

         inline ChildPointerAbstractTemplate() {}
         inline ChildPointerAbstractTemplate(ChildParamT aChild,
               ParentListDeleteIterator aParentListDeleteIterator)
            : child(aChild),parentListDeleteIterator(aParentListDeleteIterator) {}
      };

      /** Pointer to the parent abstraction. */
      template<typename ParentT,typename ChildT>
      class ParentPointerAbstractTemplate {
      public:

         typedef typename std::conditional<std::is_trivially_copyable<ParentT>::value &&
               sizeof(ParentT)<=sizeof(void*),ParentT,const ParentT&>::type ParentParamT;
         typedef typename std::list<ChildPointerAbstractTemplate<ChildT,
               ParentT>>::iterator ChildListDeleteIterator;

         ParentT parent;
         ChildListDeleteIterator childListDeleteIterator;

         inline ParentPointerAbstractTemplate() {}
         inline ParentPointerAbstractTemplate(ParentParamT aParent,
               ChildListDeleteIterator aChildListDeleteIterator)
            : parent(aParent),childListDeleteIterator(aChildListDeleteIterator) {}
      };



      /** Simple list of children that can have only one parent
       *  (multiple-children-single-parent relation).
       *  The ChildT type will usually by std::shared_ptr of particular child type.
       *  The children's parent pointers should be implemented using ParentPointerTemplate. */
      template<typename ChildT>
      class ChildSimpleListTemplate : public std::list<ChildT> {};

      /** Child's reference to its parent in multiple-children-single-parent relation.
       *  ChildSimpleListTemplate should be used to implement parent's children list. */
      template<typename ParentT,typename ChildT>
      class ParentPointerTemplate : public ParentPointerAbstractTemplate<ParentT,ChildT> {};

      /** Simple list of parents in the relation where each parent can have maximum of one child
       *  (single-child-multiple-parents relation).
       *  ParentT type might be std::weak_ptr of a given parent type, for instance. */
      template<typename ParentT>
      class ParentSimpleListTemplate : public std::list<ParentT> {};

      /** Parent's reference to its child in single-child-multiple-parents relation. */
      template<typename ChildT,typename ParentT>
      class ChildPointerTemplate : public ChildPointerAbstractTemplate<ChildT,ParentT> {};



      template<typename ChildT,typename ParentT> class ChildListTemplate;
      template<typename ParentT,typename ChildT> class ParentListTemplate;

      template<typename ListItemT,typename ChildT,typename ParentT>
      class AbstractListTemplate
      {
      protected:
         std::list<ListItemT> _list;
      public:

         typedef ChildPointerAbstractTemplate<ChildT,ParentT> ChildData;
         typedef ParentPointerAbstractTemplate<ParentT,ChildT> ParentData;

         std::list<ListItemT>& getInternalList()  { return _list; }
         const std::list<ListItemT>& getInternalList() const  { return _list; }

         typename std::list<ListItemT>::size_type size() const  { return _list.size(); }
         bool empty() const  { return _list.empty(); }

         class AbstractIterator
         {
         protected:

            typename std::list<ListItemT>::iterator _it;

         public:

            typedef std::ptrdiff_t                     difference_type;
            typedef std::bidirectional_iterator_tag    iterator_category;

            inline AbstractIterator()  {}
            explicit inline AbstractIterator(typename std::list<ListItemT>::iterator it) : _it(it)  {}

            inline typename std::list<ListItemT>::iterator getInternalIterator() const  { return _it; }

            inline AbstractIterator& operator++()     { _it++; return *this; }
            inline AbstractIterator  operator++(int)  { AbstractIterator tmp = *this; _it++; return tmp; }
            inline AbstractIterator& operator--()     { _it--; return *this; }
            inline AbstractIterator  operator--(int)  { AbstractIterator tmp = *this; _it--; return tmp; }

            inline bool operator==(const AbstractIterator& rhs) const  { return _it == rhs._it; }
            inline bool operator!=(const AbstractIterator& rhs) const  { return _it != rhs._it; }
         };

         struct ChildIterator : AbstractIterator
         {
         protected:
            typedef AbstractIterator inherited;

         public:

            typedef ChildT          value_type;
            typedef const ChildT*   pointer;
            typedef const ChildT&   reference;

            inline ChildIterator()  {}
            inline ChildIterator(const ChildIterator& it) : inherited(it.getInternalIterator())  {}
            explicit inline ChildIterator(typename std::list<ChildData>::iterator it) : inherited(it)  {}

            inline reference operator*() const  { return inherited::_it->child; }
            inline pointer operator->() const   { return std::addressof(inherited::_it->child); }
         };

         struct ParentIterator : AbstractIterator
         {
         private:
            typedef AbstractIterator inherited;

         public:

            typedef ParentT          value_type;
            typedef const ParentT*   pointer;
            typedef const ParentT&   reference;

            inline ParentIterator()  {}
            inline ParentIterator(const ParentIterator& it) : inherited(it.getInternalIterator())  {}
            explicit inline ParentIterator(typename std::list<ParentData>::iterator it) : inherited(it)  {}

            inline reference operator*() const  { return inherited::_it->parent; }
            inline pointer operator->() const   { return std::addressof(inherited::_it->parent); }
         };

      };

      template<typename ChildT,typename ParentT>
      class ChildListTemplate : public AbstractListTemplate<
            ChildPointerAbstractTemplate<ChildT,ParentT>,ChildT,ParentT>
      {
      protected:
         typedef AbstractListTemplate<ChildPointerAbstractTemplate<
               ChildT,ParentT>,ChildT,ParentT> inherited;
      public:

         typedef typename inherited::ChildIterator ChildIterator;
         typedef std::reverse_iterator<ChildIterator> ChildReverseIterator;
         typedef typename inherited::ParentIterator ParentIterator;
         typedef std::reverse_iterator<ParentIterator> ParentReverseIterator;

         typedef ChildIterator iterator;
         typedef ChildReverseIterator reverse_iterator;

         typedef typename ChildPointerAbstractTemplate<ChildT,ParentT>::ChildParamT ChildParamT;
         typedef typename ParentPointerAbstractTemplate<ParentT,ChildT>::ParentParamT ParentParamT;

         inline ChildListTemplate()  {}
         ChildListTemplate(const ChildListTemplate& list) = delete;
         ChildListTemplate(ChildListTemplate&& list) = delete;
         ChildListTemplate(std::initializer_list<ChildT> il) = delete;

         ChildListTemplate& operator=(const ChildListTemplate& list) = delete;
         ChildListTemplate& operator=(ChildListTemplate&& list) = delete;
         ChildListTemplate& operator=(std::initializer_list<ChildT> il) = delete;

         inline ChildIterator         begin()   { return ChildIterator(inherited::_list.begin()); }
         inline ChildIterator         end()     { return ChildIterator(inherited::_list.end()); }
         inline ChildReverseIterator  rbegin()  { return ChildReverseIterator(inherited::_list.rbegin()); }
         inline ChildReverseIterator  rend()    { return ChildReverseIterator(inherited::_list.rend()); }
         inline const ChildIterator         begin() const  { return ChildIterator(const_cast<ChildListTemplate*>(this)->_list.begin()); }
         inline const ChildIterator         end()   const  { return ChildIterator(const_cast<ChildListTemplate*>(this)->_list.end()); }
         inline const ChildReverseIterator  rbegin() const  { return ChildReverseIterator(const_cast<ChildListTemplate*>(this)->_list.rbegin()); }
         inline const ChildReverseIterator  rend()   const  { return ChildReverseIterator(const_cast<ChildListTemplate*>(this)->_list.rend()); }

         ChildIterator push_back(ChildParamT child,ParentParamT self,
                                 ParentListTemplate<ParentT,ChildT> &parentList);
         ChildIterator push_front(ChildParamT child,ParentParamT self,
                                  ParentListTemplate<ParentT,ChildT> &parentList);
         ChildIterator insert(ChildIterator pos,ChildParamT child,ParentParamT self,
                              ParentListTemplate<ParentT,ChildT> &parentList);
         void insert(ChildIterator posChild,ParentIterator posParent,ChildParamT child,
                     ParentParamT self,ParentListTemplate<ParentT,ChildT> &parentList);
         inline void pop_back(ParentListTemplate<ParentT,ChildT> &parentList);
         inline void pop_front(ParentListTemplate<ParentT,ChildT> &parentList);
         void replace(ChildIterator pos,ChildParamT newChild,
                      ParentListTemplate<ParentT,ChildT> &oldParentList,
                      ParentListTemplate<ParentT,ChildT> &newParentList);
         void erase(ChildIterator pos,ParentListTemplate<ParentT,ChildT> &parentList);

         inline const ChildT& front()  { return inherited::_list.front().child; }
         inline const ChildT& back()  { return inherited::_list.back().child; }

      };

      template<typename T> struct ParentChildList_is_shared_ptr : std::false_type {};
      template<typename T> struct ParentChildList_is_shared_ptr<std::shared_ptr<T>> : std::true_type {};

      #define GERG_CHILD_LIST_NAMED_4(_name_suffix_,_plurale_name_,_child_type_,_parent_type_) \
         public: \
         \
            class Child##_name_suffix_##List : public ChildListTemplate<_child_type_,_parent_type_> { \
            public: \
               Child##_name_suffix_##List() = default; \
               Child##_name_suffix_##List(const Child##_name_suffix_##List& other) = delete; \
               ~Child##_name_suffix_##List() \
               { \
                  auto it=begin(); \
                  while(it!=end()) { \
                     erase(it,(*it)->_parent##_name_suffix_##List); \
                     it=begin(); \
                  } \
               } \
            }; \
         \
         protected: \
            Child##_name_suffix_##List _child##_name_suffix_##List; \
            template<typename T=void> inline _parent_type_ list##_name_suffix_##_getSelf(std::false_type)  { return this; } \
            template<typename T=void> inline _parent_type_ list##_name_suffix_##_getSelf(std::true_type)  { return shared_from_this(); } \
         public: \
         \
            /* childList(), child???List() */ \
            inline Child##_name_suffix_##List& \
            child##_name_suffix_##List() \
            { return _child##_name_suffix_##List; } \
         \
            /* childList() const, child???List() const */ \
            inline const Child##_name_suffix_##List& \
            child##_name_suffix_##List() const \
            { return _child##_name_suffix_##List; } \
         \
            /* addChild(child,self), addChild???(child,self) */ \
            inline Child##_name_suffix_##List::iterator \
            addChild##_name_suffix_(Child##_name_suffix_##List::ChildParamT child, \
                                    Child##_name_suffix_##List::ParentParamT self) \
            { return _child##_name_suffix_##List.push_back(child,self,child->_parent##_name_suffix_##List); } \
         \
            /* addChild(child), addChild???(child) */ \
            inline Child##_name_suffix_##List::iterator \
            addChild##_name_suffix_(Child##_name_suffix_##List::ChildParamT child) \
            { return addChild##_name_suffix_(child,list##_name_suffix_##_getSelf(ParentChildList_is_shared_ptr<_parent_type_>())); } \
         \
            /* insertChild(iterator,child,self), insertChild???(iterator,child,self) */ \
            inline Child##_name_suffix_##List::iterator \
            insertChild##_name_suffix_(Child##_name_suffix_##List::iterator it, \
                                       Child##_name_suffix_##List::ChildParamT child, \
                                       Child##_name_suffix_##List::ParentParamT self) \
            { \
               return _child##_name_suffix_##List.insert(it, \
                     child,self,child->_parent##_name_suffix_##List); \
            } \
         \
            /* insertChild(iterator,child), insertChild???(iterator,child) */ \
            inline Child##_name_suffix_##List::iterator \
            insertChild##_name_suffix_(Child##_name_suffix_##List::iterator it, \
                                       Child##_name_suffix_##List::ChildParamT child) \
            { return insertChild##_name_suffix_(it,child,list##_name_suffix_##_getSelf(ParentChildList_is_shared_ptr<_parent_type_>())); } \
         \
            /* replaceChild(iterator,newChild,self), replaceChild???(iterator,newChild,self) */ \
            inline void replaceChild##_name_suffix_(Child##_name_suffix_##List::iterator it, \
                  Child##_name_suffix_##List::ChildParamT newChild) \
            { \
               return _child##_name_suffix_##List.replace(it,newChild, \
                     (*it)->_parent##_name_suffix_##List,newChild->_parent##_name_suffix_##List); \
            } \
         \
            /* removeChild(iterator), removeChild???(iterator) */ \
            inline void removeChild##_name_suffix_(Child##_name_suffix_##List::iterator it) \
            { _child##_name_suffix_##List.erase(it,(*it)->_parent##_name_suffix_##List); } \
         \
            /* removeChild(child), removeChild???(child) */ \
            template<typename T> \
            inline void removeChild##_name_suffix_(const T child) \
            { removeChild##_name_suffix_(findChild##_name_suffix_(child)); } \
         \
            /* removeAllChildren(), removeAll???() */ \
            void removeAll##_plurale_name_() \
            { \
               std::list<ChildPointerAbstractTemplate<_child_type_,_parent_type_>> childList; \
               childList.swap(_child##_name_suffix_##List.getInternalList()); \
               for(auto it=childList.begin(),e=childList.end(); it!=e; it++) { \
                  it->child->_parent##_name_suffix_##List.getInternalList().erase( \
                        it->parentListDeleteIterator); \
               } \
            } \
         \
            /* numChildren(), num???() */ \
            inline unsigned num##_plurale_name_() const \
            { return unsigned(_child##_name_suffix_##List.size()); } \
         \
            /* findChild(child), findChild???(child) */ \
            template<typename T> \
            Child##_name_suffix_##List::iterator \
            findChild##_name_suffix_(const T child) const \
            { \
               for(auto it=_child##_name_suffix_##List.begin(),e=_child##_name_suffix_##List.end(); \
                   it!=e; it++) \
                  if((*it)==child) \
                     return it; \
            } \
         \
            /* assignChildList(first,last), assignChild???List(first,last) */ \
            template<typename InputIt> \
            void assignChild##_name_suffix_##List(InputIt first,InputIt last) \
            { \
               removeAll##_plurale_name_(); \
               for(auto it=first; it!=last; it++) \
                  addChild##_name_suffix_(*it); \
            } \
         \
            /* assignChildList(list), assignChild???List(list) */ \
            inline void \
            assignChild##_name_suffix_##List(const Child##_name_suffix_##List& other) \
            { assignChild##_name_suffix_##List(other.begin(),other.end()); }

      #define GERG_CHILD_LIST_NAMED_3(_name_suffix_,_child_type_,_parent_type_) \
         GERG_CHILD_LIST_NAMED_4(_name_suffix_,Child##_name_suffix_##s,_child_type_,_parent_type_)

      #define GERG_CHILD_LIST_NAMED_2(_name_suffix_,_type_) \
         GERG_CHILD_LIST_NAMED_4(_name_suffix_,Child##_name_suffix_##s,std::shared_ptr<_type_>,_type_*)

      #define GERG_CHILD_LIST_2(_child_type_,_parent_type_) \
         GERG_CHILD_LIST_NAMED_4(,Children,_child_type_,_parent_type_)

      #define GERG_CHILD_LIST_1(_type_) \
         GERG_CHILD_LIST_NAMED_4(,Children,std::shared_ptr<_type_>,_type_*)

      #define GERG_CHILD_LIST_GET_MACRO(_1,_2,_3,_macro_name_,...) _macro_name_
      #define GERG_CHILD_LIST_MSVC_WORKAROUND(x) x

      // note1: last parameter "true" kills warning about "ISO C99 requires rest arguments to be used" on g++ (seen on version 4.8.2)
      // note2: second parameter "true" is just empty argument, offsetting the rest of arguments
      // note3: GERG_CHILD_LIST_MSVC_WORKAROUND workarounds different expansion behaviour of MSVC (seen on version 2015.0 (no update))
      #define GERG_CHILD_LIST(...) \
         GERG_CHILD_LIST_MSVC_WORKAROUND(GERG_CHILD_LIST_GET_MACRO( \
               __VA_ARGS__,true,GERG_CHILD_LIST_2,GERG_CHILD_LIST_1,true)(__VA_ARGS__))

      // note: last parameter "true" kills warning about "ISO C99 requires rest arguments to be used" on g++ (seen on version 4.8.2)
      #define GERG_CHILD_LIST_NAMED(...) \
         GERG_CHILD_LIST_GET_MACRO(__VA_ARGS__,GERG_CHILD_LIST_NAMED_3,GERG_CHILD_LIST_NAMED_2,true)(__VA_ARGS__)

      template<typename ParentT,typename ChildT>
      class ParentListTemplate : public AbstractListTemplate<
            ParentPointerAbstractTemplate<ParentT,ChildT>,ChildT,ParentT>
      {
      protected:
         typedef AbstractListTemplate<ParentPointerAbstractTemplate<
               ParentT,ChildT>,ChildT,ParentT> inherited;
      public:

         typedef typename inherited::ChildIterator ChildIterator;
         typedef std::reverse_iterator<ChildIterator> ChildReverseIterator;
         typedef typename inherited::ParentIterator ParentIterator;
         typedef std::reverse_iterator<ParentIterator> ParentReverseIterator;

         typedef ParentIterator iterator;
         typedef ParentReverseIterator reverse_iterator;

         typedef typename ParentPointerAbstractTemplate<ParentT,ChildT>::ParentParamT ParentParamT;
         typedef typename ChildPointerAbstractTemplate<ChildT,ParentT>::ChildParamT ChildParamT;

         inline ParentListTemplate()  {}
         ParentListTemplate(const ParentListTemplate& list) = delete;
         ParentListTemplate(ParentListTemplate&& list) = delete;
         ParentListTemplate(std::initializer_list<ChildT> il) = delete;

         ParentListTemplate& operator=(const ParentListTemplate& list) = delete;
         ParentListTemplate& operator=(ParentListTemplate&& list) = delete;
         ParentListTemplate& operator=(std::initializer_list<ChildT> il) = delete;

         inline ParentIterator         begin()   { return ParentIterator(inherited::_list.begin()); }
         inline ParentIterator         end()     { return ParentIterator(inherited::_list.end()); }
         inline ParentReverseIterator  rbegin()  { return ParentReverseIterator(inherited::_list.rbegin()); }
         inline ParentReverseIterator  rend()    { return ParentReverseIterator(inherited::_list.rend()); }
         inline const ParentIterator         begin() const  { return ParentIterator(const_cast<ParentListTemplate*>(this)->_list.begin()); }
         inline const ParentIterator         end()   const  { return ParentIterator(const_cast<ParentListTemplate*>(this)->_list.end()); }
         inline const ParentReverseIterator  rbegin() const  { return ParentReverseIterator(const_cast<ParentListTemplate*>(this)->_list.rbegin()); }
         inline const ParentReverseIterator  rend()   const  { return ParentReverseIterator(const_cast<ParentListTemplate*>(this)->_list.rend()); }

         inline void push_back(ParentParamT parent,ChildParamT self,ChildListTemplate<ChildT,ParentT> &childList)  { childList.push_back(self,parent,*this); }
         inline void push_front(ParentParamT parent,ChildParamT self,ChildListTemplate<ChildT,ParentT> &childList)  { childList.push_front(self,parent,*this); }
         ParentIterator insert(ParentIterator pos,ParentParamT parent,ChildParamT self,
                               ChildListTemplate<ChildT,ParentT> &childList);
         inline void insert(ParentIterator posP,ChildIterator posCh,ParentParamT parent,
                            ChildParamT self,ChildListTemplate<ChildT,ParentT> &childList);
         inline void pop_back(ChildListTemplate<ChildT,ParentT> &childList);
         inline void pop_front(ChildListTemplate<ChildT,ParentT> &childList);
         void replace(ParentIterator pos,ParentParamT newParent,
                      ChildListTemplate<ChildT,ParentT> &oldChildList,
                      ChildListTemplate<ChildT,ParentT> &newChildList);
         void erase(ParentIterator pos,ChildListTemplate<ChildT,ParentT> &childList);

         inline const ParentT& front()  { return inherited::_list.front().parent; }
         inline const ParentT& back()  { return inherited::_list.back().parent; }

      };

      #define GERG_PARENT_LIST_NAMED_3(_name_suffix_,_parent_type_,_child_type_) \
         public: \
         \
            class Parent##_name_suffix_##List : public ParentListTemplate<_parent_type_,_child_type_> { \
            public: \
               Parent##_name_suffix_##List() = default; \
               Parent##_name_suffix_##List(const Parent##_name_suffix_##List& other) = delete; \
               ~Parent##_name_suffix_##List() \
               { \
                  auto it=begin(); \
                  while(it!=end()) { \
                     erase(it,(*it)->_child##_name_suffix_##List); \
                     it=begin(); \
                  } \
               } \
            }; \
         \
         protected: \
            Parent##_name_suffix_##List _parent##_name_suffix_##List; \
         public: \
         \
            Parent##_name_suffix_##List& parent##_name_suffix_##List() \
            { return _parent##_name_suffix_##List; } \
         \
            const Parent##_name_suffix_##List& parent##_name_suffix_##List() const \
            { return _parent##_name_suffix_##List; } \
         \
            Parent##_name_suffix_##List::iterator \
            addParent##_name_suffix_(Parent##_name_suffix_##List::ParentParamT parent, \
                  Parent##_name_suffix_##List::ChildParamT self) \
            { \
               return _parent##_name_suffix_##List.insert(_parent##_name_suffix_##List.end(), \
                     parent,self,parent->_child##_name_suffix_##List); \
            } \
         \
            void removeParent##_name_suffix_(Parent##_name_suffix_##List::iterator it) \
            { _parent##_name_suffix_##List.erase(it,(*it)->_child##_name_suffix_##List); }

      #define GERG_PARENT_LIST_NAMED_2(_name_suffix_,_type_) \
         GERG_PARENT_LIST_NAMED_3(_name_suffix_,_type_*,std::shared_ptr<_type_>)

      #define GERG_PARENT_LIST_2(_child_type_,_parent_type_) \
         GERG_PARENT_LIST_NAMED_3(,_child_type_,_parent_type_)

      #define GERG_PARENT_LIST_1(_type_) \
         GERG_PARENT_LIST_NAMED_3(,_type_*,std::shared_ptr<_type_>)

      #define GERG_PARENT_LIST_GET_MACRO(_1,_2,_3,_macro_name_,...) _macro_name_
      #define GERG_PARENT_LIST_MSVC_WORKAROUND(x) x

      // note1: last parameter "true" kills warning about "ISO C99 requires rest arguments to be used" on g++ (seen on version 4.8.2)
      // note2: second parameter "true" is just empty argument, offsetting the rest of arguments
      // note3: GERG_PARENT_LIST_MSVC_WORKAROUND workarounds different expansion behaviour of MSVC (seen on version 2015.0 (no update))
      #define GERG_PARENT_LIST(...) \
         GERG_PARENT_LIST_MSVC_WORKAROUND(GERG_PARENT_LIST_GET_MACRO( \
               __VA_ARGS__,true,GERG_PARENT_LIST_2,GERG_PARENT_LIST_1,true)(__VA_ARGS__))

      // note: last parameter "true" kills warning about "ISO C99 requires rest arguments to be used" on g++ (seen on version 4.8.2)
      #define GERG_PARENT_LIST_NAMED(...) \
         GERG_PARENT_LIST_GET_MACRO(__VA_ARGS__,GERG_PARENT_LIST_NAMED_3,GERG_PARENT_LIST_NAMED_2,true)(__VA_ARGS__)


      template<typename ChildT,typename ParentT>
      typename ChildListTemplate<ChildT,ParentT>::ChildIterator
      ChildListTemplate<ChildT,ParentT>::push_back(ChildParamT child,ParentParamT self,
            ParentListTemplate<ParentT,ChildT> &parentList)
      {
         auto parentIt=parentList.getInternalList().emplace(parentList.getInternalList().end(),self,this->getInternalList().end());
         auto childIt =this->getInternalList().emplace(this->getInternalList().end(),child,parentIt);
         parentIt->childListDeleteIterator=childIt;
         return ChildIterator(childIt);
      }

      template<typename ChildT,typename ParentT>
      typename ChildListTemplate<ChildT,ParentT>::ChildIterator
      ChildListTemplate<ChildT,ParentT>::push_front(ChildParamT child,ParentParamT self,
            ParentListTemplate<ParentT,ChildT> &parentList)
      {
         auto parentIt=parentList.getInternalList().emplace(parentList.getInternalList().begin(),self,this->getInternalList().begin());
         auto childIt =this->getInternalList().emplace(this->getInternalList().begin(),child,parentIt);
         parentIt->childListDeleteIterator=childIt;
         return childIt;
      }

      template<typename ChildT,typename ParentT>
      typename ChildListTemplate<ChildT,ParentT>::ChildIterator
      ChildListTemplate<ChildT,ParentT>::insert(
            ChildIterator pos,ChildParamT child,ParentParamT self,
            ParentListTemplate<ParentT,ChildT> &parentList)
      {
         auto parentIt=parentList.getInternalList().emplace(parentList.getInternalList().end(),self,this->getInternalList().end());
         auto childIt=this->getInternalList().emplace(pos.getInternalIterator(),child,parentIt);
         parentIt->childListDeleteIterator=childIt;
         return ChildIterator(childIt);
      }

      template<typename ChildT,typename ParentT>
      void ChildListTemplate<ChildT,ParentT>::insert(ChildIterator posCh,ParentIterator posP,
            ChildParamT child,ParentParamT self,ParentListTemplate<ParentT,ChildT> &parentList)
      {
         auto parentIt=parentList.emplace(posP,self,this->end());
         auto childIt =this->emplace(posCh,child,parentIt);
         parentIt->childListDeleteIterator=childIt;
         posCh=childIt;
         posP =parentIt;
      }

      template<typename ChildT,typename ParentT>
      inline void ChildListTemplate<ChildT,ParentT>::pop_back(ParentListTemplate<ParentT,ChildT> &parentList)
      {
         erase(--end(),parentList);
      }

      template<typename ChildT,typename ParentT>
      inline void ChildListTemplate<ChildT,ParentT>::pop_front(ParentListTemplate<ParentT,ChildT> &parentList)
      {
         erase(begin(),parentList);
      }

      template<typename ChildT,typename ParentT>
      void ChildListTemplate<ChildT,ParentT>::replace(ChildIterator pos,ChildParamT newChild,
                     ParentListTemplate<ParentT,ChildT> &oldParentList,ParentListTemplate<ParentT,ChildT> &newParentList)
      {
         newParentList.getInternalList().splice(newParentList.getInternalList().end(),
                                                oldParentList.getInternalList(),
                                                pos.getInternalIterator()->parentListDeleteIterator);
         pos.getInternalIterator()->child=newChild;
      }

      template<typename ChildT,typename ParentT>
      void ChildListTemplate<ChildT,ParentT>::erase(ChildIterator pos,ParentListTemplate<ParentT,ChildT> &parentList)
      {
         std::list<ParentPointerAbstractTemplate<ParentT,ChildT>> temporaryParentReference;
         temporaryParentReference.splice(temporaryParentReference.begin(),
                                         parentList.getInternalList(),
                                         pos.getInternalIterator()->parentListDeleteIterator);
         std::list<ChildPointerAbstractTemplate<ChildT,ParentT>> temporaryChildReference;
         temporaryChildReference.splice(temporaryChildReference.begin(),this->getInternalList(),
                                        pos.getInternalIterator());
      }

      template<typename ParentT,typename ChildT>
      typename ParentListTemplate<ParentT,ChildT>::ParentIterator
      ParentListTemplate<ParentT,ChildT>::insert(
            typename ParentListTemplate<ParentT,ChildT>::ParentIterator pos,
            ParentParamT parent,ChildParamT self,
            ChildListTemplate<ChildT,ParentT> &childList)
      {
         auto childIt =childList.getInternalList().emplace(childList.getInternalList().end(),self,this->getInternalList().end());
         auto parentIt=this->getInternalList().emplace(pos.getInternalIterator(),parent,childIt);
         childIt->parentListDeleteIterator=parentIt;
         return ParentIterator(parentIt);
      }

      template<typename ParentT,typename ChildT>
      inline void ParentListTemplate<ParentT,ChildT>::insert(ParentIterator posP,ChildIterator posCh,
            ParentParamT parent,ChildParamT self,ChildListTemplate<ChildT,ParentT> &childList)
      { childList.insert(posCh,posP,self,parent,*this); }

      template<typename ParentT,typename ChildT>
      inline void ParentListTemplate<ParentT,ChildT>::pop_back(ChildListTemplate<ChildT,ParentT> &childList)
      {
         erase(--end(),childList);
      }

      template<typename ParentT,typename ChildT>
      inline void ParentListTemplate<ParentT,ChildT>::pop_front(ChildListTemplate<ChildT,ParentT> &childList)
      {
         erase(begin(),childList);
      }

      template<typename ParentT,typename ChildT>
      void ParentListTemplate<ParentT,ChildT>::replace(ParentIterator pos,ParentParamT newParent,
                     ChildListTemplate<ChildT,ParentT> &oldChildList,
                     ChildListTemplate<ChildT,ParentT> &newChildList)
      {
         newChildList.getInternalList().splice(newChildList.getInternalList().end(),
                                               oldChildList.getInternalList(),
                                               pos.getInternalIterator()->childListDeleteIterator);
         pos.getInternalIterator()->parent=newParent;
      }

      template<typename ParentT,typename ChildT>
      void ParentListTemplate<ParentT,ChildT>::erase(ParentIterator pos,ChildListTemplate<ChildT,ParentT> &childList)
      {
         std::list<ChildPointerAbstractTemplate<ChildT,ParentT>> temporaryChildReference;
         temporaryChildReference.splice(temporaryChildReference.begin(),
                                        childList.getInternalList(),
                                        pos.getInternalIterator()->childListDeleteIterator);
         std::list<ParentPointerAbstractTemplate<ParentT,ChildT>> temporaryParentReference;
         temporaryParentReference.splice(temporaryParentReference.begin(),this->getInternalList(),
                                         pos.getInternalIterator());
      }

   }
}

#endif // GE_RG_PARENT_CHILD_LIST_H
