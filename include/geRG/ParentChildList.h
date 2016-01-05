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
      #if defined(__GNUC__) && (__GNUC__==4) && (__GNUC_MINOR__<=8)
         typedef typename std::list<ParentPointerAbstractTemplate<ParentT,
               ChildT>>::iterator ParentListDeleteIterator;
      #else
         typedef typename std::list<ParentPointerAbstractTemplate<ParentT,
               ChildT>>::const_iterator ParentListDeleteIterator;
      #endif

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
      #if defined(__GNUC__) && (__GNUC__==4) && (__GNUC_MINOR__<=8)
         typedef typename std::list<ChildPointerAbstractTemplate<ChildT,
               ParentT>>::iterator ChildListDeleteIterator;
      #else
         typedef typename std::list<ChildPointerAbstractTemplate<ChildT,
               ParentT>>::const_iterator ChildListDeleteIterator;
      #endif

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

         class AbstractIterator
         {
         protected:

            typename std::list<ListItemT>::const_iterator _it;

         public:

            typedef std::ptrdiff_t                     difference_type;
            typedef std::bidirectional_iterator_tag    iterator_category;

            inline AbstractIterator()  {}
            explicit inline AbstractIterator(typename std::list<ListItemT>::const_iterator it) : _it(it)  {}

         #if defined(__GNUC__) && (__GNUC__==4) && (__GNUC_MINOR__<=8)
            inline typename std::list<ListItemT>::iterator getInternalIterator() const  { return *reinterpret_cast<typename std::list<ListItemT>::iterator*>(const_cast<typename std::list<ListItemT>::const_iterator*>(&_it)); }
         #else
            inline typename std::list<ListItemT>::const_iterator getInternalIterator() const  { return _it; }
         #endif

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
            explicit inline ChildIterator(typename std::list<ChildData>::const_iterator it) : inherited(it)  {}

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
            explicit inline ParentIterator(typename std::list<ParentData>::const_iterator it) : inherited(it)  {}

            inline reference operator*() const  { return const_cast<reference>(inherited::_it->parent); }
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
         //inline ChildListTemplate(const ChildListTemplate& list) : inherited(list)  {}
         //inline ChildListTemplate(ChildListTemplate&& list) : inherited(std::move(list))  {}
         //inline ChildListTemplate(std::initializer_list<ChildT> il) : inherited(il)  {}
         //template<typename InputIterator>
         //inline ChildListTemplate(InputIterator first,InputIterator last) : inherited(first,last)  {}

         inline ChildIterator         begin()   { return ChildIterator(inherited::_list.begin()); }
         inline ChildIterator         end()     { return ChildIterator(inherited::_list.end()); }
         inline ChildReverseIterator  rbegin()  { return ChildReverseIterator(inherited::_list.rbegin()); }
         inline ChildReverseIterator  rend()    { return ChildReverseIterator(inherited::_list.rend()); }
         inline const ChildIterator         begin() const  { return ChildIterator(inherited::_list.begin()); }
         inline const ChildIterator         end()   const  { return ChildIterator(inherited::_list.end()); }
         inline const ChildReverseIterator  rbegin() const  { return ChildReverseIterator(inherited::_list.rbegin()); }
         inline const ChildReverseIterator  rend()   const  { return ChildReverseIterator(inherited::_list.rend()); }

         //inline ChildListTemplate& operator=(const ChildListTemplate& list)  { return inheritedList::operator=(list); }
         //inline ChildListTemplate& operator=(ChildListTemplate&& list)  { return inheritedList::operator=(list); }
         //inline ChildListTemplate& operator=(std::initializer_list<ChildT> il)  { return inheritedList::operator=(il); }

         ChildIterator push_back(ChildParamT child,ParentParamT self,
                                 ParentListTemplate<ParentT,ChildT> &parentList);
         ChildIterator push_front(ChildParamT child,ParentParamT self,
                                  ParentListTemplate<ParentT,ChildT> &parentList);
         ChildIterator insert(ChildIterator pos,ChildParamT child,ParentParamT self,
                              ParentListTemplate<ParentT,ChildT> &parentList);
         void insert(ChildIterator posChild,ParentIterator posParent,ChildParamT child,
                     ParentParamT self,ParentListTemplate<ParentT,ChildT> &parentList);
         void pop_back(ParentListTemplate<ParentT,ChildT> &parentList);
         void pop_front(ParentListTemplate<ParentT,ChildT> &parentList);
         void replace(ChildIterator pos,ChildParamT newChild,ParentParamT self,
                      ParentListTemplate<ParentT,ChildT> &oldParentList,
                      ParentListTemplate<ParentT,ChildT> &newParentList);
         void erase(ChildIterator pos,ParentListTemplate<ParentT,ChildT> &parentList);
         void swap(ChildListTemplate<ChildT,ParentT> &list);

      };

      template<typename T> struct ParentChildList_is_shared_ptr : std::false_type {};
      template<typename T> struct ParentChildList_is_shared_ptr<std::shared_ptr<T>> : std::true_type {};

      #define GERG_CHILD_LIST_NAMED_4(_name_suffix_,_plurale_name_,_child_type_,_parent_type_) \
         protected: \
            ChildListTemplate<_child_type_,_parent_type_> _child##_name_suffix_##List; \
            template<typename T=void> inline _parent_type_ list##_name_suffix_##_getSelf(std::false_type)  { return this; } \
            template<typename T=void> inline _parent_type_ list##_name_suffix_##_getSelf(std::true_type)  { return shared_from_this(); } \
         public: \
         \
            typedef ChildListTemplate<_child_type_,_parent_type_> Child##_name_suffix_##List; \
         \
            /* childList(), child???List() */ \
            inline ChildListTemplate<_child_type_,_parent_type_>& \
            child##_name_suffix_##List() \
            { return _child##_name_suffix_##List; } \
         \
            /* childList() const, child???List() const */ \
            inline const ChildListTemplate<_child_type_,_parent_type_>& \
            child##_name_suffix_##List() const \
            { return _child##_name_suffix_##List; } \
         \
            /* addChild(child,self), addChild???(child,self) */ \
            inline ChildListTemplate<_child_type_,_parent_type_>::iterator \
            addChild##_name_suffix_(ChildListTemplate<_child_type_,_parent_type_>::ChildParamT child, \
                                    ChildListTemplate<_child_type_,_parent_type_>::ParentParamT self) \
            { return _child##_name_suffix_##List.push_back(child,self,child->_parent##_name_suffix_##List); } \
         \
            /* addChild(child), addChild???(child) */ \
            inline ChildListTemplate<_child_type_,_parent_type_>::iterator \
            addChild##_name_suffix_(ChildListTemplate<_child_type_,_parent_type_>::ChildParamT child) \
            { return addChild##_name_suffix_(child,list##_name_suffix_##_getSelf(ParentChildList_is_shared_ptr<_parent_type_>())); } \
         \
            /* insertChild(iterator,child,self), insertChild???(iterator,child,self) */ \
            inline ChildListTemplate<_child_type_,_parent_type_>::iterator \
            insertChild##_name_suffix_(ChildListTemplate<_child_type_,_parent_type_>::iterator it, \
                                       ChildListTemplate<_child_type_,_parent_type_>::ChildParamT child, \
                                       ChildListTemplate<_child_type_,_parent_type_>::ParentParamT self) \
            { \
               return _child##_name_suffix_##List.insert(it, \
                     child,self,child->_parent##_name_suffix_##List); \
            } \
         \
            /* insertChild(iterator,child), insertChild???(iterator,child) */ \
            inline ChildListTemplate<_child_type_,_parent_type_>::iterator \
            insertChild##_name_suffix_(ChildListTemplate<_child_type_,_parent_type_>::iterator it, \
                                       ChildListTemplate<_child_type_,_parent_type_>::ChildParamT child) \
            { return insertChild##_name_suffix_(it,child,list##_name_suffix_##_getSelf(ParentChildList_is_shared_ptr<_parent_type_>())); } \
         \
            /* replaceChild(iterator,newChild,self), replaceChild???(iterator,newChild,self) */ \
            inline void replaceChild##_name_suffix_(ChildListTemplate<_child_type_,_parent_type_>::iterator it, \
                  ChildListTemplate<_child_type_,_parent_type_>::ChildParamT newChild, \
                  ChildListTemplate<_child_type_,_parent_type_>::ParentParamT self) \
            { \
               return _child##_name_suffix_##List.replace(it,newChild,self, \
                     (*it)->_parent##_name_suffix_##List,newChild->_parent##_name_suffix_##List); \
            } \
         \
            /* removeChild(iterator), removeChild???(iterator) */ \
            inline void removeChild##_name_suffix_(ChildListTemplate<_child_type_,_parent_type_>::iterator it) \
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
               auto it=_child##_name_suffix_##List.begin(); \
               auto e=_child##_name_suffix_##List.end(); \
               while(it!=e) { \
                  _child##_name_suffix_##List.erase(it,(*it)->_parent##_name_suffix_##List); \
                  it=_child##_name_suffix_##List.begin(); \
               } \
            } \
         \
            /* numChildren(), num???() */ \
            inline unsigned num##_plurale_name_() const \
            { return unsigned(_child##_name_suffix_##List.size()); } \
         \
            /* findChild(child), findChild???(child) */ \
            template<typename T> \
            ChildListTemplate<_child_type_,_parent_type_>::iterator \
            findChild##_name_suffix_(const T child) const \
            { \
               for(auto it=_child##_name_suffix_##List.begin(),e=_child##_name_suffix_##List.end(); \
                   it!=e; it++) \
                  if((*it)==child) \
                     return it; \
            }

      #define GERG_CHILD_LIST_NAMED_3(_name_suffix_,_child_type_,_parent_type_) \
         GERG_CHILD_LIST_NAMED_4(_name_suffix_,Child##_name_suffix_##s,_child_type_,_parent_type_)

      #define GERG_CHILD_LIST_NAMED_2(_name_suffix_,_type_) \
         GERG_CHILD_LIST_NAMED_4(_name_suffix_,Child##_name_suffix_##s,std::shared_ptr<_type_>,_type_*)

      #define GERG_CHILD_LIST_2(_child_type_,_parent_type_) \
         GERG_CHILD_LIST_NAMED_4(,Children,_child_type_,_parent_type_)

      #define GERG_CHILD_LIST_1(_type_) \
         GERG_CHILD_LIST_NAMED_4(,Children,std::shared_ptr<_type_>,_type_*)

      #define GERG_CHILD_LIST_GET_MACRO(_1,_2,_3,_macro_name_,...) _macro_name_

      // note: last parameter "true" kills warning about "ISO C99 requires rest arguments to be used" on g++ 4.8.2
      // note2: second parameter "true" is just empty argument, offsetting the rest of arguments
      #define GERG_CHILD_LIST(...) \
         GERG_CHILD_LIST_GET_MACRO(__VA_ARGS__,true,GERG_CHILD_LIST_2,GERG_CHILD_LIST_1,true)(__VA_ARGS__)

      // note: last parameter "true" kills warning about "ISO C99 requires rest arguments to be used" on g++ 4.8.2
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

         inline ParentIterator         begin()   { return ParentIterator(inherited::_list.begin()); }
         inline ParentIterator         end()     { return ParentIterator(inherited::_list.end()); }
         inline ParentReverseIterator  rbegin()  { return ParentReverseIterator(inherited::_list.rbegin()); }
         inline ParentReverseIterator  rend()    { return ParentReverseIterator(inherited::_list.rend()); }

         inline void push_back(ParentParamT parent,ChildParamT self,ChildListTemplate<ChildT,ParentT> &childList)  { childList.push_back(self,parent,*this); }
         inline void push_front(ParentParamT parent,ChildParamT self,ChildListTemplate<ChildT,ParentT> &childList)  { childList.push_front(self,parent,*this); }
         ParentIterator insert(ParentIterator pos,ParentParamT parent,ChildParamT self,
                               ChildListTemplate<ChildT,ParentT> &childList);
         inline void insert(ParentIterator posP,ChildIterator posCh,ParentParamT parent,
                            ChildParamT self,ChildListTemplate<ChildT,ParentT> &childList);

         void erase(ParentIterator pos,ChildListTemplate<ChildT,ParentT> &childList);

      };

      #define GERG_PARENT_LIST_NAMED_3(_name_suffix_,_parent_type_,_child_type_) \
         protected: \
            ParentListTemplate<_parent_type_,_child_type_> _parent##_name_suffix_##List; \
         public: \
         \
            typedef ParentListTemplate<_parent_type_,_child_type_> Parent##_name_suffix_##List; \
         \
            ParentListTemplate<_parent_type_,_child_type_>& parent##_name_suffix_##List() \
            { return _parent##_name_suffix_##List; } \
         \
            const ParentListTemplate<_parent_type_,_child_type_>& parent##_name_suffix_##List() const \
            { return _parent##_name_suffix_##List; } \
         \
            ParentListTemplate<_parent_type_,_child_type_>::iterator \
            addParent##_name_suffix_(ParentListTemplate<_parent_type_,_child_type_>::ParentParamT parent, \
                  ParentListTemplate<_parent_type_,_child_type_>::ChildParamT self) \
            { \
               return _parent##_name_suffix_##List.insert(_parent##_name_suffix_##List.end(), \
                     parent,self,parent->_child##_name_suffix_##List); \
            } \
         \
            void removeParent##_name_suffix_(ParentListTemplate<_parent_type_,_child_type_>::iterator it) \
            { _parent##_name_suffix_##List.erase(it,(*it)->_child##_name_suffix_##List); }

      #define GERG_PARENT_LIST_NAMED_2(_name_suffix_,_type_) \
         GERG_PARENT_LIST_NAMED_3(_name_suffix_,_type_*,std::shared_ptr<_type_>)

      #define GERG_PARENT_LIST_2(_child_type_,_parent_type_) \
         GERG_PARENT_LIST_NAMED_3(,_child_type_,_parent_type_)

      #define GERG_PARENT_LIST_1(_type_) \
         GERG_PARENT_LIST_NAMED_3(,_type_*,std::shared_ptr<_type_>)

      #define GERG_PARENT_LIST_GET_MACRO(_1,_2,_3,_macro_name_,...) _macro_name_

      // note: last parameter "true" kills warning about "ISO C99 requires rest arguments to be used" on g++ 4.8.2
      // note2: second parameter "true" is just empty argument, offsetting the rest of arguments
      #define GERG_PARENT_LIST(...) \
         GERG_PARENT_LIST_GET_MACRO(__VA_ARGS__,true,GERG_PARENT_LIST_2,GERG_PARENT_LIST_1,true)(__VA_ARGS__)

      // note: last parameter "true" kills warning about "ISO C99 requires rest arguments to be used" on g++ 4.8.2
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
      typename ChildListTemplate<ChildT,ParentT>::ChildIterator ChildListTemplate<ChildT,ParentT>::insert(
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
      void ChildListTemplate<ChildT,ParentT>::pop_back(ParentListTemplate<ParentT,ChildT> &parentList)
      {
         erase(--end(),parentList);
      }

      template<typename ChildT,typename ParentT>
      void ChildListTemplate<ChildT,ParentT>::pop_front(ParentListTemplate<ParentT,ChildT> &parentList)
      {
         erase(begin(),parentList);
      }

      template<typename ChildT,typename ParentT>
      void ChildListTemplate<ChildT,ParentT>::replace(ChildIterator pos,ChildParamT newChild,ParentParamT self,
                     ParentListTemplate<ParentT,ChildT> &oldParentList,ParentListTemplate<ParentT,ChildT> &newParentList)
      {
         oldParentList.getInternalList().erase(pos.getInternalIterator()->parentListDeleteIterator);
         auto parentIt=newParentList.getInternalList().emplace(newParentList.getInternalList().end(),self,pos.getInternalIterator());
         pos.getInternalIterator()->parentListDeleteIterator=parentIt;
         pos.getInternalIterator()->child=newChild;
      }

      template<typename ChildT,typename ParentT>
      void ChildListTemplate<ChildT,ParentT>::erase(ChildIterator pos,ParentListTemplate<ParentT,ChildT> &parentList)
      {
         parentList.getInternalList().erase(pos.getInternalIterator()->parentListDeleteIterator);
         this->getInternalList().erase(pos.getInternalIterator());
      }

      template<typename ParentT,typename ChildT>
      typename ParentListTemplate<ParentT,ChildT>::ParentIterator ParentListTemplate<ParentT,ChildT>::insert(
            typename ParentListTemplate<ParentT,ChildT>::ParentIterator pos,ParentParamT parent,ChildParamT self,
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
      void ParentListTemplate<ParentT,ChildT>::erase(ParentIterator pos,ChildListTemplate<ChildT,ParentT> &childList)
      {
         childList.getInternalList().erase(pos.getInternalIterator()->childListDeleteIterator);
         this->getInternalList().erase(pos.getInternalIterator());
      }

   }
}

#endif // GE_RG_PARENT_CHILD_LIST_H
