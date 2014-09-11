#ifndef GE_SG_MESH_H
#define GE_SG_MESH_H

#include <geSG/Node.h>
#include <geSG/Array.h>

namespace ge
{
   namespace sg
   {
      class Mesh : public Node
      {
      protected:
         enum class StoreType : unsigned char { UNINITIALIZED = 0, CNCT = 1, VECTOR = 2 };
         enum class ArrayContent : unsigned char { UNKNOWN = 0, COORDINATES, NORMALS, COLORS, TEXCOORDS, INDICES };
         struct CustomData { ArrayContent content; ArrayAdapter array; };
         StoreType _storeType;
         union {
            struct {
               ArrayAdapter _coords;
               ArrayAdapter _normals;
               ArrayAdapter _colors;
               ArrayAdapter _texCoords;
               ArrayAdapter _indices;
            } cnct;
            std::vector<CustomData> _arrays;
         };
         //std::shared_ptr<VAO> _vao;
         int _glMode;
         int _vaoIndex;
         int _vaoNumElements;
         int _eboIndex;
         int _eboNumElements;
      public:
      };
   }
}

#endif // GE_SG_MESH_H
