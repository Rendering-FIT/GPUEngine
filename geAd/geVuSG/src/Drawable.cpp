#include "geVuSG/Drawable.h"

using namespace ge::vusg;
using namespace std;

void ge::vusg::Drawable::draw(vk::CommandBuffer cb){
  vertexArray->bind(cb);

  if (indexed) {
    cb.drawIndexed(vertexCount,instanceCount, firstIndex, vertexOffset, firstInstance);
  } else {
    cb.draw(vertexCount, instanceCount, firstVertex, firstInstance);
  }
}
