#ifndef GE_RG_BASICS_H
#define GE_RG_BASICS_H

#include <cstddef>
#include <memory>

namespace ge
{
   namespace rg
   {
      using size_t=std::size_t;
      constexpr const size_t size_max=-1; // do not remove const - it is required by MSVC 2013

      extern const std::shared_ptr<void> _nullSharedPtr;
      template<typename T>
      inline const std::shared_ptr<T>& nullSharedPtr()  { return *reinterpret_cast<const std::shared_ptr<T>*>(&_nullSharedPtr); }
   }
}

#endif /* GE_RG_BASICS_H */
