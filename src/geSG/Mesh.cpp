#include <geSG/Mesh.h>

using namespace std;
using namespace ge::sg;


void Mesh::setAttribData(unsigned attribIndex,ArrayContent content,AttribType attribType,
                         const std::shared_ptr<ArrayDecorator>& arrayDecorator)
{
   // resize _attribs if necessary
   if(attribIndex>=_attribs.size())
      _attribs.resize(attribIndex+1);

   // set attrib
   _attribs[attribIndex].set(arrayDecorator,attribType);
   _content[attribIndex]=content;

   // update _attribIndex
   int c=int(content)-1;
   if(c>=_attribIndex.size())
      _attribIndex.resize(c+1);
   _attribIndex[c]=attribIndex;
}


AttribsConfig Mesh::getAttribsConfig() const
{
   AttribsConfig r;
   r.reserve(_attribs.size());
   for(auto it=_attribs.begin(); it!=_attribs.end(); it++)
      r.push_back(it->getType());
   r.ebo = _indices.getType() != AttribType::Empty;
   r.updateConfigId();
   return r;
}
