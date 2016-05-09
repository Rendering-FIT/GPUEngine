#include <geRG/ProgressStamp.h>

using namespace ge::rg;


class ProgressStamp_tmp : public ProgressStamp {
   ProgressStamp_tmp()
   {
      static_assert(sizeof(ProgressStamp::_value)==8,
                    "ProgressStamp::_value (long long) is not of 8 bytes in size.\n"
                    "Change compiler settings or adjust the code.");
   }
};
