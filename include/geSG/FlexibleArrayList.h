#ifndef GE_SG_FLEXIBLE_ARRAY_LIST_H
#define GE_SG_FLEXIBLE_ARRAY_LIST_H

namespace ge
{
   namespace sg
   {

      class ListItemBase {
      public:
         ListItemBase *next;
         ListItemBase *prev;
      };

      template<typename T,typename BASE>
      class FlexibleArray : public BASE {
      public:

         unsigned count;
         T items[1];
         inline T& operator[](int index);
         inline const T& operator[](int index) const;
         static FlexibleArray<T,BASE>* alloc(int numItems);

      };

      template<typename T,typename BASE>
      inline T& FlexibleArray<T,BASE>::operator[](int index)  { return items[index]; }
      template<typename T,typename BASE>
      inline const T& FlexibleArray<T,BASE>::operator[](int index) const  { return items[index]; }
      template<typename T,typename BASE>
      FlexibleArray<T,BASE>* FlexibleArray<T,BASE>::alloc(int numItems)
      {
         uint8_t *p=new uint8_t[sizeof(FlexibleArray<T,BASE>)-sizeof(unsigned)+numItems*sizeof(unsigned)];
         return new(p) FlexibleArray<T,BASE>();
      }

      template<typename T>
      class FlexibleArrayList {
      public:

         class Iterator {
         public:
            T *node;
            inline T& operator*();
            inline Iterator& operator=(const Iterator & rhs);
            inline bool operator==(const Iterator & rhs) const;
            inline bool operator!=(const Iterator & rhs) const;
            inline Iterator& operator++();
            inline Iterator  operator++(int);
            inline Iterator& operator--();
            inline Iterator  operator--(int);
         };

         typedef Iterator iterator;
         typedef const Iterator const_iterator;

      protected:

         ListItemBase head;

      public:

         inline FlexibleArrayList();
         inline FlexibleArrayList(const FlexibleArrayList &other) = delete;
         inline FlexibleArrayList(FlexibleArrayList &&other);
         inline ~FlexibleArrayList();
         FlexibleArrayList<T>& operator=(FlexibleArrayList<T>&& other);

         inline T* front();
         inline T* back();
         inline const T* front() const;
         inline const T* back() const;

         inline iterator begin();
         inline iterator end();
         inline const_iterator begin() const;
         inline const_iterator end() const;
         inline const_iterator cbegin() const;
         inline const_iterator cend() const;

         inline bool empty() const;
         iterator insert(const_iterator pos,T *item);
         iterator erase(const_iterator pos);
         inline void push_back(T *item);
         inline void push_front(T *item);
         inline void pop_back();
         inline void pop_front();
         void clear();
         void swap(FlexibleArrayList<T> &other);

      };

      template<typename T>
      inline T& FlexibleArrayList<T>::Iterator::operator*()  { return *node; }
      template<typename T>
      inline typename FlexibleArrayList<T>::Iterator& FlexibleArrayList<T>::Iterator::operator=(const Iterator &rhs)  { node=rhs.node; }
      template<typename T>
      inline bool FlexibleArrayList<T>::Iterator::operator==(const FlexibleArrayList<T>::Iterator & rhs) const  { return node==rhs.node; }
      template<typename T>
      inline bool FlexibleArrayList<T>::Iterator::operator!=(const FlexibleArrayList<T>::Iterator & rhs) const  { return node!=rhs.node; }
      template<typename T>
      inline typename FlexibleArrayList<T>::Iterator& FlexibleArrayList<T>::Iterator::operator++()  { node=node->next; return this; }
      template<typename T>
      inline typename FlexibleArrayList<T>::Iterator  FlexibleArrayList<T>::Iterator::operator++(int)  { FlexibleArrayList<T>::Iterator tmp=*this; node=node->next; return tmp; }
      template<typename T>
      inline typename FlexibleArrayList<T>::Iterator& FlexibleArrayList<T>::Iterator::operator--()  { node=node->prev; return this; }
      template<typename T>
      inline typename FlexibleArrayList<T>::Iterator  FlexibleArrayList<T>::Iterator::operator--(int)  { FlexibleArrayList<T>::Iterator tmp=*this; node=node->prev; return tmp; }

      template<typename T>
      inline FlexibleArrayList<T>::FlexibleArrayList()  { head.next=&head; head.prev=&head; }
      template<typename T>
      inline FlexibleArrayList<T>::FlexibleArrayList(FlexibleArrayList &&other)  { head=other.head; other.head.next=&other.head; other.head.prev=&other.head; }
      template<typename T>
      inline FlexibleArrayList<T>::~FlexibleArrayList()  { clear(); }
      template<typename T>
      FlexibleArrayList<T>& FlexibleArrayList<T>::operator=(FlexibleArrayList<T>&& other)
      {
         clear();
         head=other.head;
         other.head.next=&other.head;
         other.head.prev=&other.head;
      }

      template<typename T>
      inline T* FlexibleArrayList<T>::front()  { return head.next; }
      template<typename T>
      inline T* FlexibleArrayList<T>::back()  { return head.prev; }
      template<typename T>
      inline const T* FlexibleArrayList<T>::front() const  { return head.prev; }
      template<typename T>
      inline const T* FlexibleArrayList<T>::back() const  { return head.next; }

      template<typename T>
      inline typename FlexibleArrayList<T>::iterator FlexibleArrayList<T>::begin()  { return head.prev; }
      template<typename T>
      inline typename FlexibleArrayList<T>::iterator FlexibleArrayList<T>::end()  { return head; }
      template<typename T>
      inline typename FlexibleArrayList<T>::const_iterator FlexibleArrayList<T>::begin() const  { return head.prev; }
      template<typename T>
      inline typename FlexibleArrayList<T>::const_iterator FlexibleArrayList<T>::end() const  { return head; }
      template<typename T>
      inline typename FlexibleArrayList<T>::const_iterator FlexibleArrayList<T>::cbegin() const  { return head.prev; }
      template<typename T>
      inline typename FlexibleArrayList<T>::const_iterator FlexibleArrayList<T>::cend() const  { return head; }

      template<typename T>
      bool FlexibleArrayList<T>::empty() const  { return head.next==&head; }
      template<typename T>
      typename FlexibleArrayList<T>::iterator FlexibleArrayList<T>::insert(const_iterator pos,T *item)
      {
         item->next=pos.node;
         item->prev=pos.node->prev;
         pos.node->prev=item;
         item->prev->next=item;
         return item;
      }
      template<typename T>
      typename FlexibleArrayList<T>::iterator FlexibleArrayList<T>::erase(const_iterator pos)
      {
         pos->prev->next=pos->next;
         pos->next->prev=pos->prev;
         FlexibleArrayList<T>::iterator tmp=pos->next;
         delete pos.node;
         return tmp;
      }
      template<typename T>
      inline void FlexibleArrayList<T>::push_back(T *item)  { insert(head,item); }
      template<typename T>
      inline void FlexibleArrayList<T>::push_front(T *item)  { insert(head.next,item); }
      template<typename T>
      void inline FlexibleArrayList<T>::pop_back()  { erase(head.prev); }
      template<typename T>
      inline void FlexibleArrayList<T>::pop_front()  { erase(head.next); }
      template<typename T>
      void FlexibleArrayList<T>::clear()
      {
         T *p1=static_cast<T*>(head.next);
         T *p2;
         while(true) {
            if(p1==&head) break;
            p2=static_cast<T*>(p1->next);
            delete p1;
            if(p2==&head) break;
            p1=static_cast<T*>(p2->next);
            delete p2;
         }
         head.next=&head;
         head.prev=&head;
      }
      template<typename T>
      void FlexibleArrayList<T>::swap(FlexibleArrayList<T> &other)
      {
         if(empty())
         {
            if(other.empty())
               return;
            this->head=other.head;
            other.head.next=&other.head;
            other.head.prev=&other.head;
            return;
         }
         else
            if(other.empty())
            {
               other.head=this->head;
               head.next=&head;
               head.prev=&head;
               return;
            }

         ListItemBase tmp;
         tmp=this->head;
         this->head=other.head;
         other.head=tmp;
      }

   }
}

#endif /* GE_SG_FLEXIBLE_ARRAY_LIST_H */
