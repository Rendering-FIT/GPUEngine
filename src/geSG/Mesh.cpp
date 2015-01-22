#include <iostream>
#include <geSG/Mesh.h>

using namespace std;
using namespace ge::sg;

shared_ptr<Mesh::Factory> Mesh::_factory=make_shared<Mesh::Factory>();



Mesh::~Mesh()
{
}


void Mesh::resetCpuGeometryData()
{
   // empty all attrib data
   _attribArrays.clear();
   _contents.clear();
   _content2attribIndex.clear();
   _indexArray.clear();
   //_drawCommands.clear();

   // indicate that attrib data are now available on cpu, even although they are empty now
   _cpuAttribDataAvailable=true;
}


void Mesh::gpuUploadGeometryData()
{
   // alloc data if not allocated
   if(!_attribReference.valid())
   {
      _attribReference.allocData(computeAttribConfig(),
                                 _attribArrays.size()>=1?_attribArrays[0].size():0,
                                 hasIndices()?_indexArray.size():0,_drawCommandBufferSize);
  }

   // upload attributes
   _attribReference.uploadVertices(_attribArrays);

   // upload indices
   if(hasIndices())
      _attribReference.uploadIndices(_indexArray);

   // upload draw commands
   _attribReference.uploadDrawCommands(_drawCommandBuffer,_drawCommandBufferSize,
                                       _drawCommandOffsetsAndSizes.data(),
                                       _drawCommandOffsetsAndSizes.size()/2);
   _gpuAttribDataAvailable=true;

   // release cpu data if requested
   if(_releaseCpuAttribDataAfterGpuUpload)
   {
      _attribArrays.clear();
      _indexArray.clear();
      //_drawCommands.clear();
      _cpuAttribDataAvailable=false;
   }
}


void Mesh::gpuDownloadGeometryData()
{
   //FIXME: not implemented yet
}


void Mesh::setAttribArray(unsigned attribIndex,ArrayContent content,AttribType attribType,
                         const std::shared_ptr<ArrayDecorator>& arrayDecorator)
{
   // resize _attribArrays if necessary
   if(attribIndex>=_attribArrays.size())
      _attribArrays.resize(attribIndex+1);

   // set attrib
   _attribArrays[attribIndex].set(arrayDecorator,attribType);
   _contents[attribIndex]=content;

   // update _content2attribIndex
   int c=int(content)-1;
   if(c>=_content2attribIndex.size())
      _content2attribIndex.resize(c+1);
   _content2attribIndex[c]=attribIndex;
}


void Mesh::setAttribArrays(const vector<Array> attribs, const vector<ArrayContent> contents)
{
   unsigned n=min(attribs.size(),contents.size());
   _attribArrays.clear();
   _attribArrays.reserve(n);
   _contents.clear();
   _contents.reserve(n);

   for(unsigned i=0; i<n; i++)
      setAttribArray(i,contents[i],attribs[i]);
}


void Mesh::setIndexArray(const Array &array)
{
   if(array.getType()!=AttribType::UInt)
   {
      cout<<"Error in Mesh::setIndexArray(): Array type must be UNSIGNED_INT or INT."<<endl;
      return;
   }
   setIndexArray(static_pointer_cast<ArrayDecoratorTemplate<unsigned>>(array.getArrayDecorator()));
}


void Mesh::setIndexArray(const shared_ptr<ArrayDecoratorTemplate<unsigned>>& arrayDecorator)
{
   _indexArray.set(arrayDecorator,AttribType::UInt);
}


AttribConfigRef Mesh::computeAttribConfig(AttribManager *manager) const
{
   AttribConfig::ConfigData config;
   config.attribTypes.reserve(_attribArrays.size());
   for(auto it=_attribArrays.begin(); it!=_attribArrays.end(); it++)
      config.attribTypes.push_back(it->getType());
   config.ebo = hasIndices();
   config.updateId();
   return manager->getAttribConfig(config);
}


shared_ptr<Mesh> Mesh::Factory::create()
{
   return std::make_shared<Mesh>();
}
