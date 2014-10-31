#include <geSG/Mesh.h>

using namespace std;
using namespace ge::sg;


void Mesh::setAttribData(unsigned attribIndex,ArrayContent content,AttribType attribType,
                         const std::shared_ptr<ArrayDecorator>& arrayDecorator)
{
   if(attribIndex>=_attribs.size())
      _attribs.resize(attribIndex+1);

   _attribs[attribIndex].content=content;
   _attribs[attribIndex].array.set(arrayDecorator,attribType);
}


AttribsConfig Mesh::getAttribsConfig() const
{
   AttribsConfig r;
   r.reserve(_attribs.size());
   for(auto it=_attribs.begin(); it!=_attribs.end(); it++)
      r.push_back(it->array.getType());
   r.ebo = _indices.getType() != AttribType::Empty;
   return r;
}
