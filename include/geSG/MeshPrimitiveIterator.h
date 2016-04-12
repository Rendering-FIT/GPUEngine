#pragma once

#include <iterator>
#include <array>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

#include <geSG/Mesh.h>
#include <geSG/AttributeDescriptor.h>
#include <geCore/StandardSemanticsNames.h>

#include <algorithm>

namespace ge
{
   namespace sg
   {

      /**
       * Structure representing triangle. It has 3 pointers to array. These
       * should point on the beginning of each vertex's data. Whether it is
       * position, normal or whatever.
       * It is limited to float values now. Because it is used with Iterators,
       * we need to know the underlaying type at compile time. This could be
       * bypassed with one superclass which could the needs to be cast to a
       * specific subclass or with underlaying pointer being void and 
       * additional information about type being provided.
       */
      struct Triangle
      {
         Triangle()
            : v0(nullptr), v1(nullptr), v2(nullptr)
         {}

         /**
          * Set inner pointers (v0-v2) to point to tightly packed vertex data in
          * ptr. Each vertex data is numComponents float long. This is number
          * of vertex data vector components. E.g. if ptr is continuous array of
          * positions x,y,z then stride is 3.
          */
         Triangle& setToContinuous(float *ptr, int numComponents)
         {
            v0 = ptr;
            v1 = v0 + (numComponents);
            v2 = v1 + (numComponents);
            return *this;
         }

         /**
          * Set inner pointers (v0-v2) to point to values in ptr which are not one
          * after another, but are on different indices which corresponds the first
          * three unsigned ints in ind. Indices are num components long so e.g. v0
          * is located on ptr + ind[0]*numcomponents, v1 has ind[1] and so on.
          */
         Triangle& setToIndexed(float *ptr, unsigned* ind, int numComponents)
         {
            v0 = ptr + ind[0] * numComponents;
            v1 = ptr + ind[1] * numComponents;
            v2 = ptr + ind[2] * numComponents;
            return *this;
         }

         /**
          * If you have continuous array of vertex data you can shift all three pointers
          * to point to next "triangle" by giving the number of floats the vertex data has.
          * If you have array of x,y,z then add(3) would shift v0 to point to next data after
          * v2 before the call. If you want to advance more then one triangle then multiply
          * the argument by number of triangles you want to advance.
          * Internal implementation: vx += numComponents*3. 3 because we have 3 vertices of 
          * a triangle.
          */
         Triangle& add(int numComponents)
         {
            v0 += numComponents*3;
            v1 += numComponents*3;
            v2 += numComponents*3;
            return *this;
         }

         /**
          * Not fully implemented yet.
          * Same as add()
          *
          * @see add
          */
         /*friend Triangle operator+(Triangle& t, int numComponents)
         {
            t.v0 += numComponents*3;
            t.v1 += numComponents*3;
            t.v2 += numComponents*3;
         }*/

         float *v0, *v1, *v2;
      };

      /**
       * Base class for mesh triangle iterator. It defines basic operations:
       * increment, equality, addition, dereference and arrow. It is tagged as
       * a forward iterator even though it might not satisfy all the requirements yet.
       */
      class MeshTriangleIteratorBasis : public std::iterator<std::forward_iterator_tag, Triangle>
      {
      public:
         typedef MeshTriangleIteratorBasis self_type;

         virtual self_type& operator++()
         {
            return *this;
         }
         virtual self_type operator++(int)
         {
            self_type tmp = *this;
            operator++();
            return tmp;
         }

         virtual bool operator==(const self_type& rhs)
         {
            return this->_triangle.v0 == rhs._triangle.v0;
         }

         virtual bool operator!=(const self_type& rhs)
         {
            return !operator==(rhs);
         }

         virtual self_type& operator+(int shift)
         {
            return *this;
         }

         virtual const reference operator*()
         {
            return _triangle;
         }

         virtual const pointer operator->()
         {
            return &(operator*());
         }
      protected:
         Triangle _triangle;
      };

      /**
       * Triangle iterator which iterates over position Attribute descriptor.
       * It is not to be used right now! It assumes the standard semantic names
       * from geCore StandardSemanticsNames.
       */
      class MeshTriangleIterator : public MeshTriangleIteratorBasis
      {
      public:
         typedef MeshTriangleIterator self_type;

         MeshTriangleIterator()
            : _Ptr(nullptr)
            , N(0)
         {}

         MeshTriangleIterator(Mesh* mesh)
         {
            auto it = std::find_if(mesh->attributes.begin(), mesh->attributes.end(), [](std::shared_ptr<AttributeDescriptor>& attr){ return attr->semantic == AttributeDescriptor::semanticRegister.getValue(ge::core::StandardSemanticNames::position); });
            _Ptr = static_cast<float*>((**it).data.get());
            N = (**it).numComponents;
            _triangle.setToContinuous(_Ptr, N);
         }

         MeshTriangleIterator(float* ptr, unsigned numComponents)
            : _Ptr(ptr)
            , N(numComponents)
         {
            _triangle.setToContinuous(_Ptr, N);
         }

         self_type& operator++()
         {
            _triangle.add(N);
            return *this;
         }

         virtual self_type& operator+(int shift)
         {
            _triangle.add(shift*N);
            return *this;
         }
         
         unsigned getN(){ return N; }
         
      private:
         float* _Ptr;
         unsigned N;
      };


      /**
       * Triangle iterator which iterates along the position Attribute descriptor but
       * tries to find indices descriptor at construction time. If it can find the
       * indices it advances the triangle via indices array, if not if advances only in
       * position array. It assumes the standard semantic names from geCore
       * StandardSemanticsNames.
       * In future it should be extended towards other Attributes. At least the float ones.
       */
      class MeshIndexedTriangleIterator : public MeshTriangleIteratorBasis
      {
      public:
         typedef MeshIndexedTriangleIterator self_type;

         MeshIndexedTriangleIterator()
            : MeshTriangleIteratorBasis()
            , _Ptr(nullptr)
            , _Ind(nullptr)
            , N(0)
         {}

         MeshIndexedTriangleIterator(Mesh* mesh)
         {
            auto indices = mesh->getAttribute(ge::core::StandardSemanticNames::indices);
            auto positions = mesh->getAttribute(ge::core::StandardSemanticNames::position);

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
            : _Ptr(ptr)
            , _Ind(ind)
            , N(numComponents)
         {
            if(_Ind) _triangle.setToIndexed(_Ptr, _Ind, N);
            else _triangle.setToContinuous(_Ptr, N);
         }

         MeshIndexedTriangleIterator(const self_type& other)
            : MeshTriangleIteratorBasis(other)
            , _Ptr(other._Ptr)
            , _Ind(other._Ind)
            , N(other.N)
         {}

         self_type& operator++()
         {
            if (_Ind)
            {
               _Ind += 3;
               _triangle.setToIndexed(_Ptr, _Ind, N);
            }
            else
            {
               _triangle.add(N);
            }
            return *this;
         }

         virtual self_type& operator+(int shift)
         {
            if(_Ind){
               _Ind += 3 * shift;
               _triangle.setToIndexed(_Ptr, _Ind, N);
            }
            else
            {
               _triangle.add(shift*N);
            }
            return *this;
         }

         unsigned getN(){ return N; }

      private:
         float* _Ptr;
         unsigned* _Ind;
         unsigned N;
      };

      /**
       * Constructs the triangle iterator to beginning of position attribute. If it
       * finds the indices array the iterator will be indexed. The position or index
       * array is found by querying the semantic. It assumes the standard semantic names
       * from geCore StandardSemanticsNames.
       */
      static MeshIndexedTriangleIterator MeshPositionIteratorBegin(Mesh *mesh)
      {
         auto indices = mesh->getAttribute(ge::core::StandardSemanticNames::indices);
         auto positions = mesh->getAttribute(ge::core::StandardSemanticNames::position);

         if(indices && positions)
         {
            unsigned* ind = static_cast<unsigned*>(indices->data.get());
            float* ptr = static_cast<float*>(positions->data.get());
            unsigned N = positions->numComponents;
            return MeshIndexedTriangleIterator(ptr,ind,N);
         } 
         else if(positions)
         {
            float* ptr = static_cast<float*>(positions->data.get());
            unsigned N = positions->numComponents;
            return MeshIndexedTriangleIterator(ptr, nullptr, N);
         }

         return MeshIndexedTriangleIterator();
      }

      /**
       * Returns iterator that points after the last triangle of mesh. It creates
       * iterator via MeshPositionIteratorBegin() and then uses mesh->count to updates
       * its position.
       */
      static MeshIndexedTriangleIterator MeshPositionIteratorEnd(Mesh *mesh)
      {
         MeshIndexedTriangleIterator ret = MeshPositionIteratorBegin(mesh);
         if(ret.getN() == 0)
            return ret;
         

         ret = ret + static_cast<unsigned>(mesh->count) / 3;

         return ret;
      }

   }
}
