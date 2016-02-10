#include <geRG/Basics.h>

#if defined(__GNUC__) && (__GNUC__==4) && (__GNUC_MINOR__<=8)
// g++ 4.8 does not like constexpr here (g++ bug)
// (the variable was forward-declarared as extern in geRG/Basics.h)
const std::shared_ptr<void> ge::rg::_nullSharedPtr;
#else
constexpr std::shared_ptr<void> ge::rg::_nullSharedPtr;
#endif
