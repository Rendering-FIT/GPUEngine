#ifndef GE_SG_MESH_H
#define GE_SG_MESH_H

#include <vector>
#include <geSG/Array.h>
#include <geSG/AttribsReference.h>
#include <geSG/Node.h>

namespace ge
{
   namespace sg
   {

      class Mesh : public Node
      {
      public:

         enum class ArrayContent : uint8_t { UNKNOWN=0,COORDINATES=1,NORMALS=2,COLORS=3,TEXCOORDS=4,USER=5,OTHER = 0xff };

      protected:

         bool _releaseCpuGeometryDataAfterGpuUpload : 1;
         bool _cpuGeometryDataAvailable : 1;
         bool _gpuGeometryDataAvailable : 1;

         int _glMode;
         std::vector<Array> _attribs;
         std::vector<ArrayContent> _content;
         Array _indices;
         std::vector<int8_t> _attribIndex;

         AttribsReference _attribsReference;

      public:

         META_Node(ge::sg,Mesh);

         inline Mesh() {}
         virtual ~Mesh() {}

         template<typename T>
         inline void setAttribData(unsigned attribIndex,ArrayContent content,AttribType attribType,
                                   const std::shared_ptr<std::vector<T>> &ptr);
         virtual void setAttribData(unsigned attribIndex,ArrayContent content,AttribType attribType,
                                    const std::shared_ptr<ArrayDecorator>& arrayDecorator);

         virtual AttribsConfig getAttribsConfig() const;
      };


      template<typename T>
      inline void Mesh::setAttribData(unsigned attribIndex,ArrayContent content,AttribType attribType,
                                      const std::shared_ptr<std::vector<T>> &ptr)
      {
         setAttribData(attribIndex,content,attribType,std::make_shared<ArrayDecoratorTemplate<T>>(ptr));
      }
   }
}

#endif // GE_SG_MESH_H
