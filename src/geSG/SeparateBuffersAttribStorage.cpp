#include <iostream>
#include <geSG/SeparateBuffersAttribStorage.h>
#include <geGL/VertexArrayObject.h>

using namespace ge::sg;
using namespace ge::gl;
using namespace std;


SeparateBuffersAttribStorage::SeparateBuffersAttribStorage(const AttribConfigRef &config,
        unsigned numVertices,unsigned numIndices)
   : AttribStorage(config,numVertices,numIndices)
{
   // get ConfigData
   const AttribConfig::ConfigData &configData=config->configData();

   // create VAO
   _vao = new VertexArrayObject;

   // create array buffers
   _arrayBuffers.reserve(configData.attribTypes.size());
   unsigned i=0;
   for(auto it=configData.attribTypes.begin(); it!=configData.attribTypes.end(); it++,i++)
   {
      AttribType t=*it;
      BufferObject *bo=new BufferObject(numVertices*t.elementSize(),NULL,GL_DYNAMIC_DRAW);
      _vao->addAttrib(bo,i,t.numComponents(),t.glTypeAsInt(),t.elementSize(),0,
                      t.typeHandling()==AttribType::INTEGER_NORMALIZE,t.divisor());
      _arrayBuffers.push_back(bo);
   }

   // create EBO
   if(configData.ebo)
   {
      _ebo=new BufferObject(numIndices*4,NULL,GL_DYNAMIC_DRAW);
      _vao->addElementBuffer(_ebo);
   }
   else
   {
      if(numIndices>0)
         cout<<"Warning in SeparateBuffersAttribStorage constructor: If config parameter\n"
               "   specifies to not use indices (AttribConfig::ebo),\n"
               "   numIndices parameter must be zero.\n"<<endl;
      _ebo = NULL;
   }
}


SeparateBuffersAttribStorage::~SeparateBuffersAttribStorage()
{
   delete _vao;
   delete _ebo;
   for(auto it=_arrayBuffers.begin(); it!=_arrayBuffers.end(); it++)
      delete *it;
}


void SeparateBuffersAttribStorage::bind() const
{
   _vao->bind();
}


bool SeparateBuffersAttribStorage::reallocData(Mesh &mesh,int numVertices,
        int numIndices,bool preserveContent)
{
   // FIXME: not implemented yet
   return false;
}


void SeparateBuffersAttribStorage::uploadVertices(Mesh &mesh,const void*const *attribList,
                                                  unsigned attribListSize,
                                                  int numVertices,int fromIndex)
{
   const AttribConfig::ConfigData &configData=_attribConfig->configData();
   unsigned c=_arrayBuffers.size();
   assert(c==attribListSize && "Number of attributes passed in parameters and stored inside "
                               "AttribStorage must match.");
   for(unsigned i=0; i<c; i++)
   {
      AttribType t=configData.attribTypes[i];
      int elementSize=t.elementSize();
      int srcOffset=fromIndex*elementSize;
      int dstOffset=(_vertexAllocationManager[mesh.verticesDataId()].startIndex+fromIndex)*elementSize;
      const void *data=attribList[i];
      _arrayBuffers[i]->setData(((uint8_t*)data)+srcOffset,
                                numVertices*elementSize,dstOffset);
   }
}


void SeparateBuffersAttribStorage::uploadIndices(Mesh &mesh,const void *indices,
                                                 int numIndices,int fromIndex)
{
   if(_ebo==nullptr) {
      cout<<"Error in SeparateBuffersAttribStorage::uploadIndices(): ebo is null.\n"
            "   SeparateBuffersAttribStorage was probably created with AttribConfig\n"
            "   without ebo member set to true." << endl;
      return;
   }
   const int elementSize=4;
   int srcOffset=fromIndex*elementSize;
   int dstOffset=(_indexAllocationManager[mesh.indicesDataId()].startIndex+fromIndex)*elementSize;
   _ebo->setData((uint8_t*)indices+srcOffset,numIndices*elementSize,dstOffset);
}
