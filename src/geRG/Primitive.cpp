#include <geRG/Primitive.h>

using namespace ge::rg;

static_assert(sizeof(Primitive)<=4,
              "Primitive size is bigger than 4 bytes.\n"
              "Consider class redesign or rewising this assert.");
