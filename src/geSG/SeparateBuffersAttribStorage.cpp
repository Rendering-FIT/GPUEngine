#include <algorithm>
#include <iostream>
#include <geSG/SeparateBuffersAttribStorage.h>
#include <geSG/Array.h>
#include <geGL/VertexArrayObject.h>

using namespace ge::sg;
using namespace ge::gl;
using namespace std;


SeparateBuffersAttribStorage::SeparateBuffersAttribStorage(const AttribConfig &config,
                                                           unsigned numVertices,unsigned numIndices)
   : AttribStorage(config,numVertices,numIndices)
{
   // create VAO
   _vao = new VertexArrayObject;

   // create array buffers
   _arrayBuffers.reserve(config.size());
   unsigned i=0;
   for(auto it=config.begin(); it!=config.end(); it++,i++)
   {
      AttribType t=*it;
      BufferObject *bo=new BufferObject(numVertices*t.getElementSize(),NULL,GL_DYNAMIC_DRAW);
      _vao->addAttrib(bo,i,t.getNumComponents(),t.getGLTypeAsInt(),t.getElementSize(),0,
                      t.getTypeHandling()==AttribType::INTEGER_NORMALIZE,t.getDivisor());
      _arrayBuffers.push_back(bo);
   }

   // create EBO
   if(config.ebo)
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
}


void SeparateBuffersAttribStorage::uploadVertexData(AttribReference &r,const std::vector<Array>& data,
                                                    int fromIndex,int numVertices)
{

   for(int i=0,c=min(_arrayBuffers.size(),data.size()); i<c; i++)
   {
      AttribType t=_attribConfig[i];
      if(t!=data[i].getType()) {
         cout << "Error in SeparateBuffersAttribStorage::uploadVertexData(): data type of\n"
                 "   attribute " << i << " differs from the one passed in the parameter." << endl;
         continue;
      }
      int elementSize=t.getElementSize();
      int offset=fromIndex*elementSize;
      int num=numVertices==-1?data[i].size():numVertices;
      _arrayBuffers[i]->setData((uint8_t*)data[i].data()+offset,num*elementSize,offset);
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
   int elementSize=t.getElementSize();
   int offset=fromIndex*elementSize;
   int num=numIndices==-1?data.size():numIndices;
   _ebo->setData((uint8_t*)data.data()+offset,num*elementSize,offset);
}
