#ifndef GE_SG_MESH_H
#define GE_SG_MESH_H

#include <vector>
#include <geSG/Array.h>
#include <geSG/AttribDataReference.h>
#include <geSG/Node.h>

namespace ge
{
   namespace sg
   {

      class Mesh : public Node
      {
      public:

         enum class ArrayContent : uint8_t { UNKNOWN=0, COORDINATES=1, NORMALS=2, COLORS=3, TEXCOORDS=4, USER=5, OTHER = 0xff };
         struct AttribData { ArrayContent content; ArrayAdapter array; };

      protected:

         bool _releaseCpuGeometryDataAfterGpuUpload : 1;
         bool _cpuGeometryDataAvailable : 1;
         bool _gpuGeometryDataAvailable : 1;

         int _glMode;
         std::vector<AttribData> _attribs;
         ArrayAdapter _indices;
         int8_t _coordinateAttribIndex;
         int8_t _normalAttribIndex;
         int8_t _colorAttribIndex;
         int8_t _texCoordAttribIndex;

         AttribsDataReference _attribsDataReference;

      public:

         META_Node(ge::sg,Mesh);

         inline Mesh() {}
         virtual ~Mesh() {}

         template<typename T>
         inline void setAttribData(unsigned attribIndex, ArrayContent content, ArrayAdapter::ArrayType arrayType,
                                   unsigned elementSize, const std::shared_ptr<std::vector<T>> &ptr);
         virtual void setAttribData(unsigned attribIndex, ArrayContent content, ArrayAdapter::ArrayType arrayType,
                                    unsigned elementSize, const std::shared_ptr<ArrayDecorator>& arrayDecorator);

         virtual uint16_t getArraysConfigID();
      };


      template<typename T>
      inline void Mesh::setAttribData(unsigned attribIndex, ArrayContent content, ArrayAdapter::ArrayType arrayType,
                                      unsigned elementSize, const std::shared_ptr<std::vector<T>> &ptr)
      {
         setAttribData(attribIndex,content,arrayType,elementSize,std::make_shared<ArrayDecoratorTemplate<T>>(ptr));
      }
   }
}

#endif // GE_SG_MESH_H
