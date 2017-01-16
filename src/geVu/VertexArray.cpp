#include <geVu/VertexArray.h>

#include <geVu/Buffer.h>

#include <iostream>

using namespace ge::vu;
using namespace std;

VertexArray::VertexArray() {
}

void ge::vu::VertexArray::bind(vk::CommandBuffer cmd){
  for (auto &vbo : vertexBuffers) {
    //std::cout << get<0>(vbo) << (vk::Buffer)*get<1>(vbo)<<"\n";
    cmd.bindVertexBuffers(get<0>(vbo), { *get<1>(vbo) }, { get<2>(vbo) });
  }
  
  if (indexBuffer) {
    //std::cout << (vk::Buffer)*indexBuffer << "\n";
    cmd.bindIndexBuffer(*indexBuffer, indexBufferOffset, vk::IndexType::eUint32);
  }
}

