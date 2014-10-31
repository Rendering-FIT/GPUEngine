#include <geSG/SeparateBuffersAttribsStorage.h>
#include <geGL/VertexArrayObject.h>

using namespace ge::sg;
using namespace ge::gl;
using namespace std;


SeparateBuffersAttribsStorage::SeparateBuffersAttribsStorage(const AttribsConfig &config,unsigned numVertices,unsigned numIndices)
   : AttribsStorage(config,numVertices,numIndices)
{
   // create VAO
   _vao = new VertexArrayObject;

   // create array buffers
   _arrayBuffers.reserve(config.size());
   unsigned i=0;
   for(auto it=config.begin(); it!=config.end(); it++,i++)
   {
      AttribType t=*it;
      BufferObject *bo=new BufferObject(numVertices*t.getElementSize(),NULL,GL_ARRAY_BUFFER,GL_DYNAMIC_DRAW);
      _vao->addAttrib(bo,i,t.getNumComponents(),t.getGLTypeAsInt(),t.getElementSize(),0,t.getTypeHandling()==AttribType::INTEGER_NORMALIZE,t.getDivisor());
      _arrayBuffers.push_back(bo);
   }

   // create EBO
   if(config.ebo)
   {
      _ebo=new BufferObject(numIndices*4,NULL,GL_ELEMENT_ARRAY_BUFFER,GL_DYNAMIC_DRAW);
      _vao->addElementBuffer(_ebo);
   }
   else
      _ebo = NULL;
}


SeparateBuffersAttribsStorage::~SeparateBuffersAttribsStorage()
{
   delete _vao;
   delete _ebo;
   for(auto it=_arrayBuffers.begin(); it!=_arrayBuffers.end(); it++)
      delete *it;
}
