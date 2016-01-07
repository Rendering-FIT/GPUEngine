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
         unsigned vertexOffset;        ///< Offset of the start of the allocated block of vertices or indices within AttribStorage. Thus, the real start index is first+vertexOffset.

         inline PrimitiveGpuData() = default;
         inline PrimitiveGpuData(unsigned countAndIndexedFlag,unsigned first,
                                 unsigned vertexOffset);
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
       *  Implementation note: The structure provides setters and getters as we want to
       *  make sure the structure occupies only 4 bytes. (Bit fields are known to not be
       *  always tightly packed on MSVC.)
       */
      struct GERG_EXPORT Primitive {
      protected:
         unsigned data; // 32-bits, verified by assert in Primitive.cpp
      public:
         inline unsigned offset4() const  { return data&0x07ffffff; } // return the lowest 27 bits
         inline unsigned mode() const     { return data>>27; } // return upmost 5 bits
         inline void setOffset4(unsigned value)  { data=(data&0xf8000000)|value; } // set lowest 27 bits, value must fit to 27 bits
         inline void setMode(unsigned value)     { data=(data&0x07ffffff)|(value<<27); } // set upmost 5 bits
         inline void set(unsigned offset4,unsigned mode)  { data=offset4|(mode<<27); } // set data, offset4 must fit to 27 bits

         inline Primitive() {}
         inline Primitive(unsigned offset4,unsigned mode)  { set(offset4,mode); }
      };


      typedef std::vector<Primitive> PrimitiveList;



      // inline methods
      inline PrimitiveGpuData::PrimitiveGpuData(unsigned countAndIndexedFlag,unsigned first,unsigned vertexOffset)
      { this->countAndIndexedFlag=countAndIndexedFlag; this->first=first; this->vertexOffset=vertexOffset; }

   }
}

#endif /* GE_RG_PRIMITIVE_H */
