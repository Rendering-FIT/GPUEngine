#pragma once

#include <iterator>
#define GLM_ENABLE EXPERIMENTAL
#include <glm/glm.hpp>


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

         /**
          *
          */
         float* operator[](const unsigned i) const
         {
            assert(i >= 0 && i < 3);
            return (&v0)[i];
         }

         float *v0, *v1, *v2;
      };

      /**
       * Base class for mesh triangle iterator. It defines basic operations:
       * increment, equality, addition, dereference and arrow. It is tagged as
       * a forward iterator even though it might not satisfy all the requirements yet.
       */
      class TriangleIteratorBasis : public std::iterator<std::forward_iterator_tag, Triangle>
      {
      public:
         typedef TriangleIteratorBasis self_type;

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

         virtual bool operator==(const self_type& rhs) const
         {
            return this->_triangle.v0 == rhs._triangle.v0;
         }

         virtual bool operator!=(const self_type& rhs) const
         {
            return !operator==(rhs);
         }

         /*self_type operator+(int ) const
         {
            return{*this};
         }*/

         virtual reference operator*()
         {
            return _triangle;
         }

         virtual pointer operator->()
         {
            return &(operator*());
         }
      protected:
         Triangle _triangle;
      };

      /**
       * Triangle Iterator that iteratex over a plain float array with a set N component vertices.
       */
      class TriangleIterator : public TriangleIteratorBasis
      {
      public:
         typedef TriangleIterator self_type;

         TriangleIterator()
            : _Ptr(nullptr)
            , N(0)
         {}

         TriangleIterator(float* ptr, unsigned numComponents)
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

         self_type operator+(int shift) const
         {
            self_type ret{*this};
            ret->add(shift*N);
            return ret;
         }

         virtual self_type& operator+=(int shift)
         {
            _triangle.add(shift*N);
            return *this;
         }

         friend size_t operator-(const self_type& lhs, const self_type& rhs)
         {
            return (lhs._triangle.v0 - rhs._triangle.v0) / (lhs.N);
         }
         
         unsigned getN(){ return N; }
         
      protected:
         float* _Ptr;
         unsigned N;
      };

      /**
       * Triangle iterator that iterates over an indexed geometry with unsigned as index type
       * and float array as the actual vertex array with N as a number of floats per vertex.
       */
      class IndexedTriangleIterator : public TriangleIteratorBasis
      {
      public:
         typedef IndexedTriangleIterator self_type;

         IndexedTriangleIterator()
            : TriangleIteratorBasis()
            , _Ptr(nullptr)
            , _Ind(nullptr)
            , N(0)
         {}

         IndexedTriangleIterator(float* ptr, unsigned* ind, unsigned numComponents)
            : _Ptr(ptr)
            , _Ind(ind)
            , N(numComponents)
         {
            if(_Ind) _triangle.setToIndexed(_Ptr, _Ind, N);
            else _triangle.setToContinuous(_Ptr, N);
         }

         IndexedTriangleIterator(const self_type& other)
            : TriangleIteratorBasis(other)
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

         self_type operator+(int shift) const
         {
            self_type ret{*this};
            if(ret._Ind) {
               ret._Ind += 3 * shift;
               ret._triangle.setToIndexed(ret._Ptr, ret._Ind, ret.N);
            }
            else
            {
               ret._triangle.add(shift*N);
            }
            return ret;
         }

         virtual self_type& operator+=(int shift)
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
         
         friend size_t operator-(const self_type& lhs, const self_type& rhs)
         {
            if(lhs._Ind && rhs._Ind)
               return (lhs._Ind - rhs._Ind)/3;
            return (lhs._triangle.v0 - rhs._triangle.v0) / (3 * lhs.getN());
         }

         unsigned getN() const { return N; }

      protected:
         float* _Ptr;
         unsigned* _Ind;
         unsigned N;
      };
   }
}
