#include <algorithm>
#include <iostream>
#include <geSG/SeparateBuffersAttribStorage.h>
#include <geSG/Array.h>
#include <geGL/VertexArrayObject.h>

using namespace ge::sg;
using namespace ge::gl;
using namespace std;


SeparateBuffersAttribStorage::SeparateBuffersAttribStorage(const AttribConfigRef &config,
        unsigned numVertices,unsigned numIndices)
   : AttribStorage(config,numVertices,numIndices)
{
   // get ConfigData
   const AttribConfig::ConfigData &configData=config->getConfigData();

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


void SeparateBuffersAttribStorage::bind()
{
   _vao->bind();
}


bool SeparateBuffersAttribStorage::reallocData(AttribReference &r,int numVertices,
        int numIndices,bool preserveContent)
{
   // FIXME: not implemented yet
   return false;
}


void SeparateBuffersAttribStorage::uploadVertices(AttribReference &r,const std::vector<Array>& data,
                                                  int fromIndex,int numVertices)
{
   const AttribConfig::ConfigData &configData=_attribConfig->getConfigData();
   for(int i=0,c=int(min(_arrayBuffers.size(),data.size())); i<c; i++)
   {
      AttribType t=configData.attribTypes[i];
      if(t!=data[i].getType()) {
         cout << "Error in SeparateBuffersAttribStorage::uploadVertexData(): data type of\n"
                 "   attribute " << i << " differs from the one passed in the parameter." << endl;
         continue;
      }
      int elementSize=t.elementSize();
      int srcOffset=fromIndex*elementSize;
      int dstOffset=(_vertexAllocationManager[r.verticesDataId].startIndex+fromIndex)*elementSize;
      int num=numVertices==-1?int(data[i].size()):numVertices;
      _arrayBuffers[i]->setData((uint8_t*)data[i].data()+srcOffset,num*elementSize,dstOffset);
   }
}


void SeparateBuffersAttribStorage::uploadIndices(AttribReference &r,const Array& data,
                                                 int fromIndex,int numIndices)
{
   AttribType t=data.getType();
   if(t!=AttribType::UInt) {
      cout<<"Error in SeparateBuffersAttribStorage::uploadIndices(): data type of\n"
            "   indices is not UInt (unsigned 32-bit int)."<<endl;
      return;
   }
   if(_ebo==NULL) {
      cout<<"Error in SeparateBuffersAttribStorage::uploadIndices(): ebo is null.\n"
            "   SeparateBuffersAttribStorage was probably created with AttribConfig\n"
            "   without ebo member set to true." << endl;
      return;
   }
   int elementSize=t.elementSize();
   int srcOffset=fromIndex*elementSize;
   int dstOffset=(_indexAllocationManager[r.indicesDataId].startIndex+fromIndex)*elementSize;
   int num=numIndices==-1?int(data.size()):numIndices;
   _ebo->setData((uint8_t*)data.data()+srcOffset,num*elementSize,dstOffset);
}
