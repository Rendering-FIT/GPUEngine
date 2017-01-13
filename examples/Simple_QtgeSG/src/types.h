#pragma once

namespace std
{
   template <class > class allocator;
   template<class _Ty, class _Alloc = allocator<_Ty> > class vector;
   template<typename> class shared_ptr;
}

namespace ge
{
   namespace core
   {
      class Command;
   }
}

namespace fsg
{
   typedef std::vector<std::shared_ptr<ge::core::Command>> CommandList;
   typedef std::vector<std::shared_ptr<CommandList>> CommandLists;
}