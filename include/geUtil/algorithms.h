#pragma once

#ifndef F_CONCEPTS
#define ForwardIterator typename
#define UnsignedInteger typename

#endif // !F_CONCEPTS

namespace ge
{
   namespace util
   {
      template<ForwardIterator FwdIt>
      void apply(FwdIt first, FwdIt last)
      {
         while(first != last)
         {
            (*first)();
            ++first;
         }
      }

      template<ForwardIterator FwdIt, UnsignedInteger Size>
      FwdIt apply_n(FwdIt first, Size count)
      {
         for(Size i=0; i<count ; i++)
         {
            (*first)();
            ++first;
         }
         return first;
      }
   }
}