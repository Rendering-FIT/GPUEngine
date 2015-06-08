#include <geSG/Mesh.h>

using namespace ge::sg;

static_assert(sizeof(Mesh::DrawCommandControlData)<=4,
              "Mesh::DrawCommandControlData size is bigger than 4 bytes.\n"
              "Consider its bits reallocation or rewising this assert.");
