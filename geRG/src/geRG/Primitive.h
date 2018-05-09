#ifndef GE_RG_PRIMITIVE_H
#define GE_RG_PRIMITIVE_H

#include <vector>
#include <geRG/Export.h>

namespace ge
{
   namespace rg
   {

      /** PrimitiveGpuData represents part of the primitive data that is stored
       *  in gpu buffers (usually RenderingContext::primitiveStorage()).
       */
      struct PrimitiveGpuData {
         unsigned countAndIndexedFlag; ///< Number of vertices of the primitive and indexing flag on the highest bit indicating whether glDrawArrays or glDrawElements should be used for rendering.
         unsigned first;               ///< Index of the first vertex or first index of the primitive.
         unsigned vertexOffset;        ///< Offset of the start of the allocated block of vertices or indices within AttribStorage. Thus, the real start index is first+vertexOffset. The value is computed and updated automatically.

         inline PrimitiveGpuData()  {}
         constexpr inline PrimitiveGpuData(unsigned countAndIndexedFlag,unsigned first);
         constexpr inline PrimitiveGpuData(unsigned count,unsigned first,bool indexed);
         constexpr inline PrimitiveGpuData(const PrimitiveGpuData&) = default;

         constexpr inline unsigned count() const  { return countAndIndexedFlag&0x7fffffff; }
         constexpr inline bool indexed() const  { return (countAndIndexedFlag&0x80000000)!=0; }
      };


      /** Primitive carries mode and offset of particular primitive draw data.
       *
       *  Mode is OpenGL mode, such as GL_TRIANGLES, GL_PATCH, GL_LINE_STRIP. The upmost
       *  bit is used to distinguish between glDrawArrays and glDrawElements draw commands,
       *  e.g. whether EBO is used or not.
       *
       *  Offset points to the buffer of PrimitiveGpuData where the rest of primitive
       *  data is stored.
       *
       *  Offset is given in multiple of 4 because shaders access memory as int array,
       *  thus index is memory offset divided by four. Real memory offset is
       *  computed as offset4()*4.
       *
       *  Implementation note: The structure contains single 32-bit integer as we want to
       *  make sure it occupies only 4 bytes. (Bit fields are known not to be
       *  always tightly packed on MSVC.)
       */
      struct GERG_EXPORT Primitive {
      protected:

         unsigned data; // 32-bits, verified by assert in Primitive.cpp

      public:

         constexpr inline unsigned offset4() const  { return data&0x07ffffff; } // return the lowest 27 bits
         constexpr inline unsigned mode() const     { return data>>27; } // return upmost 5 bits
         inline void setOffset4(unsigned value)  { data=(data&0xf8000000)|value; } // set lowest 27 bits, value must fit to 27 bits
         inline void setMode(unsigned value)     { data=(data&0x07ffffff)|(value<<27); } // set upmost 5 bits
         inline void set(unsigned mode,unsigned offset4)  { data=(mode<<27)|offset4; } // set data, offset4 must fit to 27 bits

         inline Primitive()  {}
         constexpr inline Primitive(unsigned mode,unsigned offset4) : data((mode<<27)|offset4)  {}
      };


      typedef std::vector<Primitive> PrimitiveList;



      // inline methods
      constexpr inline PrimitiveGpuData::PrimitiveGpuData(unsigned countAndIndexedFlag_,unsigned first_)
         : countAndIndexedFlag(countAndIndexedFlag_), first(first_), vertexOffset(0)  {}
      constexpr inline PrimitiveGpuData::PrimitiveGpuData(unsigned count,unsigned first_,bool indexed)
         : countAndIndexedFlag(count|(indexed?0x80000000:0)), first(first_), vertexOffset(0)  {}

   }
}

#endif /* GE_RG_PRIMITIVE_H */
