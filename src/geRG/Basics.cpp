#include <geRG/Basics.h>

using namespace std;
using namespace ge::rg;


aligned_storage<sizeof(shared_ptr<void>),
      alignment_of<shared_ptr<void>>::value>::type GERG_EXPORT ge::rg::_nullSharedPtr;


static struct _NullSharedPtrInitializer {
   inline _NullSharedPtrInitializer()
   {
      ::new(&_nullSharedPtr)shared_ptr<void>();
   }
   inline ~_NullSharedPtrInitializer()
   {
      nullSharedPtr<void>().~shared_ptr();
   }
} _nullSharedPtrInitializer;
