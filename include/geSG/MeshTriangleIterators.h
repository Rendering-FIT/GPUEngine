#pragma once
#include <geSG/MeshPrimitiveIterator.h>
#include <geSG/Mesh.h>
#include <geSG/AttributeDescriptor.h>

namespace ge
{
   namespace sg
   {

      /**
      * Triangle iterator which iterates over position Attribute descriptor.
      * It is not to be used right now! It assumes the standard semantic names
      * from geCore StandardSemanticsNames.
      */
      class MeshTriangleIterator : public TriangleIterator
      {
      public:
         typedef MeshTriangleIterator self_type;

         MeshTriangleIterator()
            : TriangleIterator()
         {}

         MeshTriangleIterator(Mesh* mesh)
         {
            auto it = std::find_if(mesh->attributes.begin(), mesh->attributes.end(), [](std::shared_ptr<AttributeDescriptor>& attr) { return attr->semantic == AttributeDescriptor::Semantic::position; });
            _Ptr = static_cast<float*>((**it).data.get());
            N = (**it).numComponents;
            _triangle.setToContinuous(_Ptr, N);
         }

         MeshTriangleIterator(float* ptr, unsigned numComponents)
            : TriangleIterator(ptr, numComponents)
         {
         }
      };

      /**
      * Triangle iterator which iterates along the position Attribute descriptor but
      * tries to find indices descriptor at construction time. If it can find the
      * indices it advances the triangle via indices array, if not if advances only in
      * position array. It assumes the standard semantic names from geCore
      * StandardSemanticsNames.
      * In future it should be extended towards other Attributes. At least the float ones.
      */
      class MeshIndexedTriangleIterator : public IndexedTriangleIterator
      {
      public:
         typedef MeshIndexedTriangleIterator self_type;

         MeshIndexedTriangleIterator()
            : IndexedTriangleIterator()
         {}

         MeshIndexedTriangleIterator(Mesh* mesh)
         {
            auto indices = mesh->getAttribute(AttributeDescriptor::Semantic::indices);
            auto positions = mesh->getAttribute(AttributeDescriptor::Semantic::position);

            if(indices && positions)
            {
               unsigned* _Ind = static_cast<unsigned*>(indices->data.get());
               float* _Ptr = static_cast<float*>(positions->data.get());
               unsigned N = positions->numComponents;
               _triangle.setToIndexed(_Ptr, _Ind, N);
            }
            else if(positions)
            {
               float* _Ptr = static_cast<float*>(positions->data.get());
               unsigned N = positions->numComponents;
               _triangle.setToContinuous(_Ptr, N);
            }

         }

         MeshIndexedTriangleIterator(float* ptr, unsigned* ind, unsigned numComponents)
            : IndexedTriangleIterator(ptr, ind, numComponents)
         {}

         MeshIndexedTriangleIterator(const self_type& other)
            : IndexedTriangleIterator(other)
         {}
      };

      /**
      * Constructs the triangle iterator to beginning of position attribute. If it
      * finds the indices array the iterator will be indexed. The position or index
      * array is found by querying the semantic. It assumes the standard semantic names
      * from geCore StandardSemanticsNames.
      */
      inline IndexedTriangleIterator MeshPositionIteratorBegin(Mesh *mesh)
      {
         auto indices = mesh->getAttribute(AttributeDescriptor::Semantic::indices);
         auto positions = mesh->getAttribute(AttributeDescriptor::Semantic::position);

         if(indices && positions)
         {
            unsigned* ind = static_cast<unsigned*>(indices->data.get());
            float* ptr = static_cast<float*>(positions->data.get());
            unsigned N = positions->numComponents;
            return IndexedTriangleIterator(ptr, ind, N);
         }
         else if(positions)
         {
            float* ptr = static_cast<float*>(positions->data.get());
            unsigned N = positions->numComponents;
            return IndexedTriangleIterator(ptr, nullptr, N);
         }

         return IndexedTriangleIterator();
      }

      /**
      * Returns iterator that points after the last triangle of mesh. It creates
      * iterator via MeshPositionIteratorBegin() and then uses mesh->count to updates
      * its position.
      */
      inline IndexedTriangleIterator MeshPositionIteratorEnd(Mesh *mesh)
      {
         IndexedTriangleIterator ret = MeshPositionIteratorBegin(mesh);
         if(ret.getN() == 0)
            return ret;


         ret = ret + static_cast<unsigned>(mesh->count) / 3;

         return ret;
      }

   } //namespace sg
} //namespace ge
