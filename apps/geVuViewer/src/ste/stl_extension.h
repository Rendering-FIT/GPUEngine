#pragma once
#include "concepts.h"

#include <memory>

namespace ste
{
   template <class T> struct is_shared : std::false_type {};
   template <class T> struct is_shared<std::shared_ptr<T>> : std::true_type{};


   template<ForwardIterator I, OutputStream OS>
   void print_range(I first, I last, OS& output)
   {
      for(I it = first; it != last; ++it)
      {
         output << (*it) << " ";
      }
   }

   template <Number T> int sgn(T val) {
      return (T(0) < val) - (val < T(0));
   }

   template<typename SrcType, typename DstType>
   void copy_MofN(SrcType* src, DstType * dst, unsigned m, unsigned n, unsigned count)
   {
      unsigned cnt = 0;
      if(n < m)
      {
         m = n;
      }
      int rest = n - m - 1;
      int j = 0;
      for(int i = 0; i < count; ++i)
      {
         if(cnt < m)
         {
            dst[j] = src[i];
            ++j;
            ++cnt;
         }
         else
         {
            i += rest;
            cnt = 0;
         }
      }
   }

   template<InputIterator InputIt, OutputIterator OutputIt, FunctionObject Transform>
   OutputIt transform_copy(InputIt first, InputIt last, OutputIt d_first, Transform trans)
   {
      while(first != last) {
         *d_first++ = trans(*first++);
      }
      return d_first;
   }

}// namespace ste;

//undef concepts since some of them may colide with some names from other libraries
#include "concepts_undef.h"