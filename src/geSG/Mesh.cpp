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
   _indexArray.clear();
   _content2attribIndex.clear();

   // indicate that attrib data are now available on cpu, even although they are empty now
   _cpuAttribDataAvailable=true;
}


void Mesh::gpuUploadGeometryData()
{
   // alloc data if not allocated
   if(!_attribReference.valid())
   {
      //AttribConfig ac(getAttribConfig());
      //_attribReference.allocData(,,ac.hasIndices()?);
   }

   // upload attributes
   _attribReference.uploadVertexData(_attribArrays);

   // upload indices
   if(hasIndices())
      _attribReference.uploadIndices(_indexArray);
   _gpuAttribDataAvailable=true;

   // release cpu data if requested
   if(_releaseCpuAttribDataAfterGpuUpload)
   {
      _attribArrays.clear();
      _indexArray.clear();
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
   _indexArray.setArrayDecorator(arrayDecorator);
}


AttribConfig Mesh::getAttribConfig() const
{
   AttribConfig r;
   r.reserve(_attribArrays.size());
   for(auto it=_attribArrays.begin(); it!=_attribArrays.end(); it++)
      r.push_back(it->getType());
   r.ebo = hasIndices();
   r.updateConfigId();
   return r;
}


shared_ptr<Mesh> Mesh::Factory::create()
{
   return std::make_shared<Mesh>();
}
