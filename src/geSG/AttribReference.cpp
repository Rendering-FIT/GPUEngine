#include <geSG/AttribReference.h>

using namespace ge::sg;

static_assert(sizeof(AttribReference::DrawCommandControlData)<=4,
              "AttribReference::DrawCommandControlData size is bigger than 4 bytes.\n"
              "Consider its bits reallocation or rewising this assert.");
