#ifndef GE_RG_ATTRIB_TYPE_H
#define GE_RG_ATTRIB_TYPE_H

#include <cstdint>
#include <glm/glm.hpp>
#include <geRG/Export.h>

namespace ge
{
   namespace rg
   {

      /** GLType is enum class that defines types of variables.
       *
       *  The types that have their OpenGL counterpart use the same binary value as OpenGL.
       */
      enum class GLType : uint16_t
      {
         INVALID = 0x0000,
         EMPTY   = 0x0000,

         BYTE            = 0x1400,
         UNSIGNED_BYTE   = 0x1401,
         SHORT           = 0x1402,
         UNSIGNED_SHORT  = 0x1403,
         INT             = 0x1404,
         UNSIGNED_INT    = 0x1405,
         FLOAT           = 0x1406,
         DOUBLE          = 0x140A,
         HALF_FLOAT      = 0x140B,
         FIXED           = 0x140C,

         UNSIGNED_BYTE_3_3_2            = 0x8032,
         UNSIGNED_BYTE_2_3_3_REV        = 0x8362,
         UNSIGNED_SHORT_5_6_5           = 0x8363,
         UNSIGNED_SHORT_5_6_5_REV       = 0x8364,
         UNSIGNED_SHORT_4_4_4_4         = 0x8033,
         UNSIGNED_SHORT_4_4_4_4_REV     = 0x8365,
         UNSIGNED_SHORT_5_5_5_1         = 0x8034,
         UNSIGNED_SHORT_1_5_5_5_REV     = 0x8366,
         UNSIGNED_INT_8_8_8_8           = 0x8035,
         UNSIGNED_INT_8_8_8_8_REV       = 0x8367,
         UNSIGNED_INT_10_10_10_2        = 0x8036,
         UNSIGNED_INT_2_10_10_10_REV    = 0x8368,
         UNSIGNED_INT_24_8              = 0x84FA,
         UNSIGNED_INT_10F_11F_11F_REV   = 0x8C3B,
         UNSIGNED_INT_5_9_9_9_REV       = 0x8C3E,
         FLOAT_32_UNSIGNED_INT_24_8_REV = 0x8DAD,

         MAT2   = 0xff02,
         MAT3   = 0xff03,
         MAT4   = 0xff04,

         MAT2X3 = 0xff05,
         MAT2X4 = 0xff06,
         MAT3X2 = 0xff07,
         MAT3X4 = 0xff08,
         MAT4X2 = 0xff09,
         MAT4X3 = 0xff0A,

         DMAT2   = 0xff0B,
         DMAT3   = 0xff0C,
         DMAT4   = 0xff0D,

         DMAT2X3 = 0xff0E,
         DMAT2X4 = 0xff0F,
         DMAT3X2 = 0xff10,
         DMAT3X4 = 0xff11,
         DMAT4X2 = 0xff12,
         DMAT4X3 = 0xff13,

         STRUCT  = 0xffff,
      };


      /** AttribType class stores the type information of OpenGL attribute data.
       *
       *  AttribType stores data type of the attribute, number of components,
       *  size of a one attribute data item and function to send the attribute to OpenGL.
       */
      class GERG_EXPORT AttribType {
      public:

         /// Specifies how attributes are handled to OpenGL pipeline.
         enum TypeHandling {
            NOT_DEFINED=0,        ///< \brief Attribute handling is not defined.
            INTEGER_CAST=0,       ///< \brief Integer attributes are converted to floats and passed to OpenGL pipeline.
            INTEGER_NORMALIZE=1,  ///< \brief Integer attributes are normalized and passed as floats to OpenGL pipeline.
            USE_FLOAT=0,          ///< Float-point attributes are passed directly to the OpenGL pipeline as floats.
            USE_INTEGER=2,        ///< Integer attributes are passed directly to the OpenGL pipeline as integers.
            USE_DOUBLE=3,         ///< Double precision floats are passed directly to the OpenGL pipeline as doubles.
         };

      protected:

         /** AttribType is stored on 64 bits. Bits distribution is as follows:
          *  - 0..7 - element size
          *  - 8,9 - type handling
          *  - 10 - bgra flag
          *  - 11..15 - number of components
          *  - 16..31 - glType
          *  - 32..63 - divisor
          */
         union {
            uint64_t _data64;
            uint32_t _data32[2];
            uint16_t _data16[4];
         };

      public:

         inline AttribType()  {}  ///< \brief Default constructor does nothing.
         inline constexpr AttribType(GLType glType,uint8_t numComponents,uint8_t elementSize,
                                     TypeHandling typeHandling,unsigned divisor=0);
                                     ///< Initializes the object by parameters.
         inline constexpr AttribType(GLType glType,uint8_t numComponents,bool bgra,uint8_t elementSize,
                                     TypeHandling typeHandling,unsigned divisor=0);
                                     ///< Initializes the object by parameters.
         inline AttribType(const AttribType& a);  ///< Copy constructor.

         inline AttribType& operator=(AttribType a);       ///< Assignment operator.

         inline GLType glType() const;                     ///< Returns the type of attribute data.
         inline uint16_t glTypeAsInt() const;              ///< Returns type of attribute data as integer value.
         inline void setGLType(GLType value);              ///< Sets the type of attribute data.
         inline unsigned numComponents() const;            ///< Returns the number of components of attribute.
         inline void setNumComponents(unsigned value);     ///< Sets the number of components of attribute.
         inline bool bgra() const;                         ///< Returns BGRA flag used by some special OpenGL attribute formats.
         inline void setBGRA(bool value);                  ///< Sets BGRA flag used by some special OpenGL attribute formats.
         inline unsigned elementSize() const;              ///< \brief Returns the size (in bytes) of single attribute item.
         inline void setElementSize(unsigned value);       ///< \brief Sets the size (in bytes) of single attribute item.
         inline TypeHandling typeHandling() const;         ///< \brief Returns how the attribute is handled to OpenGL.
         inline void setTypeHandling(TypeHandling value);  ///< \brief Sets how the attribute is handled to OpenGL.
         inline uint32_t divisor() const;                  ///< \brief Returns attribute divisor.
         inline void setDivisor(uint32_t value);           ///< \brief Sets attribute divisor.
         inline uint64_t asInt64() const;                  ///< \brief Returns AttribType object content as the 64-bit value.
         inline void setAsInt64(uint64_t value);           ///< \brief Sets AttribType object content by the 64-bit value.

         template<GLType T> static inline AttribType create();
         template<GLType T> static inline AttribType create(uint8_t numComponents);
         template<GLType T> static inline AttribType create(uint8_t numComponents,TypeHandling typeHandling);
         template<typename T> static inline AttribType create();
         template<typename T> static inline AttribType create(TypeHandling typeHandling);
         template<typename T> static inline AttribType create(uint8_t numComponents);
         template<typename T> static inline AttribType create(uint8_t numComponents,TypeHandling typeHandling);
         static inline AttribType createInvalid();  ///< Generates invalid AttribType object.
         static inline AttribType createEmpty();    ///< Generates empty AttribType object.

         inline void invalidate();  ///< Sets the object to invalid AttribType value.
         inline void makeEmpty();   ///< Sets the object to empty AttribType value.

         inline bool operator==(const AttribType a) const;  ///< Comparison operator.
         inline bool operator!=(const AttribType a) const;  ///< Comparison operator.
         inline bool operator< (const AttribType a) const;  ///< Comparison operator.
         inline bool operator> (const AttribType a) const;  ///< Comparison operator.
         inline bool operator<=(const AttribType a) const;  ///< Comparison operator.
         inline bool operator>=(const AttribType a) const;  ///< Comparison operator.

         static const AttribType Invalid;
         static const AttribType Empty;

         static const AttribType Byte;
         static const AttribType BVec2;
         static const AttribType BVec3;
         static const AttribType BVec4;

         static const AttribType UByte;
         static const AttribType UBVec2;
         static const AttribType UBVec3;
         static const AttribType UBVec4;

         static const AttribType Short;
         static const AttribType SVec2;
         static const AttribType SVec3;
         static const AttribType SVec4;

         static const AttribType UShort;
         static const AttribType USVec2;
         static const AttribType USVec3;
         static const AttribType USVec4;

         static const AttribType Int;
         static const AttribType IVec2;
         static const AttribType IVec3;
         static const AttribType IVec4;

         static const AttribType UInt;
         static const AttribType UVec2;
         static const AttribType UVec3;
         static const AttribType UVec4;

         static const AttribType Float;
         static const AttribType Vec2;
         static const AttribType Vec3;
         static const AttribType Vec4;

         static const AttribType Double;
         static const AttribType DVec2;
         static const AttribType DVec3;
         static const AttribType DVec4;

         static const AttribType Half;
         static const AttribType HVec2;
         static const AttribType HVec3;
         static const AttribType HVec4;

         static const AttribType Byte_3_3_2;
         static const AttribType Byte_2_3_3_Rev;
         static const AttribType Short_5_6_5;
         static const AttribType Short_5_6_5_Rev;
         static const AttribType Short_4_4_4_4;
         static const AttribType Short_4_4_4_4_Rev;
         static const AttribType Short_5_5_5_1;
         static const AttribType Short_1_5_5_5_Rev;
         static const AttribType Int_8_8_8_8;
         static const AttribType Int_8_8_8_8_Rev;
         static const AttribType Int_10_10_10_2;
         static const AttribType Int_2_10_10_10_Rev;
         static const AttribType Int_24_8;
         static const AttribType Int_10F_11F_11F_Rev;
         static const AttribType Int_5_9_9_9_Rev;
         static const AttribType Float_32_UInt_24_8_Rev;

         static const AttribType Mat2;
         static const AttribType Mat3;
         static const AttribType Mat4;

         static const AttribType Mat2x3;
         static const AttribType Mat2x4;
         static const AttribType Mat3x2;
         static const AttribType Mat3x4;
         static const AttribType Mat4x2;
         static const AttribType Mat4x3;

         static const AttribType DMat2;
         static const AttribType DMat3;
         static const AttribType DMat4;

         static const AttribType DMat2x3;
         static const AttribType DMat2x4;
         static const AttribType DMat3x2;
         static const AttribType DMat3x4;
         static const AttribType DMat4x2;
         static const AttribType DMat4x3;

      };


      // inline and template methods
      inline constexpr AttribType::AttribType(GLType glType,uint8_t numComponents,uint8_t elementSize,
                                              TypeHandling typeHandling,unsigned divisor)
            :_data64(uint64_t(divisor)<<32 | uint32_t(glType)<<16 | uint32_t(numComponents)<<11 |
                     uint32_t(typeHandling)<<8 | elementSize)  {}
      inline constexpr AttribType::AttribType(GLType glType,uint8_t numComponents,bool bgra,uint8_t elementSize,
                                              TypeHandling typeHandling,unsigned divisor)
            :_data64(uint64_t(divisor)<<32 | uint32_t(glType)<<16 | uint32_t(numComponents)<<11 |
                     (bgra?0x0400:0) | uint32_t(typeHandling)<<8 | elementSize)  {}
      inline AttribType::AttribType(const AttribType& a) : _data64(a._data64)  {}
      inline AttribType& AttribType::operator=(AttribType a) { _data64=a._data64; return *this; }

      inline GLType AttribType::glType() const  { return GLType(_data16[1]); }
      inline uint16_t AttribType::glTypeAsInt() const  { return _data16[1]; }
      inline void AttribType::setGLType(GLType value)  { _data16[1]=uint16_t(value); }
      inline unsigned AttribType::numComponents() const  { return (_data16[0]&0xf800)>>11; }
      inline void AttribType::setNumComponents(unsigned value)  { unsigned v=_data16[0]&0x07ff; _data16[0]=uint16_t(v|(value<<11)); }
      inline bool AttribType::bgra() const  { return (_data16[0]&0x0400)!=0; }
      inline void AttribType::setBGRA(bool value)  { if(value) _data16[0]|=0x0400; else _data16[0]&=0xfbff; }
      inline unsigned AttribType::elementSize() const  { return _data16[0]&0x00ff; }
      inline void AttribType::setElementSize(unsigned value)  { unsigned v=_data16[0]&0xff00; _data16[0]=uint16_t(v|(value&0xff)); }
      inline AttribType::TypeHandling AttribType::typeHandling() const  { return TypeHandling((_data16[0]&0x0300)>>8); }
      inline void AttribType::setTypeHandling(AttribType::TypeHandling value)  { auto v=_data16[0]&0xfc00; _data16[0]=uint16_t(v|value); }
      inline uint32_t AttribType::divisor() const  { return _data32[1]; }
      inline void AttribType::setDivisor(uint32_t value)  { _data32[1]=value; }
      inline uint64_t AttribType::asInt64() const  { return _data64; }
      inline void AttribType::setAsInt64(uint64_t value)  { _data64=value; }

      inline AttribType AttribType::createInvalid()  { return AttribType::Invalid; }
      inline AttribType AttribType::createEmpty()  { return AttribType::Empty; }
      inline void AttribType::invalidate()  { *this=AttribType::Invalid; }
      inline void AttribType::makeEmpty()  { *this=AttribType::Empty; }

      inline bool AttribType::operator==(const AttribType a) const  { return _data64==a._data64; }
      inline bool AttribType::operator!=(const AttribType a) const  { return _data64!=a._data64; }
      inline bool AttribType::operator< (const AttribType a) const  { return _data64<a._data64; }
      inline bool AttribType::operator> (const AttribType a) const  { return _data64>a._data64; }
      inline bool AttribType::operator<=(const AttribType a) const  { return _data64<=a._data64; }
      inline bool AttribType::operator>=(const AttribType a) const  { return _data64>=a._data64; }

      template<GLType T> inline AttribType AttribType::create()  { assert(0&&"Missing numComponents parameter or type specialization method."); return AttribType::createInvalid(); }
      template<GLType T> inline AttribType AttribType::create(uint8_t numComponents)  { assert(0&&"Provided GLType does not support numComponents parameter or missing specialization method."); return AttribType::createInvalid(); }
      template<GLType T> inline AttribType AttribType::create(uint8_t numComponents,TypeHandling typeHandling)  { assert(0&&"Provided GLType does not support numComponents and typeHandling parameters specified together, or missing specialization method."); return AttribType::createInvalid(); }
      template<typename T> inline AttribType AttribType::create()  { assert(0&&"Missing numComponents parameter or type specialization method."); return AttribType::createInvalid(); }
      template<typename T> inline AttribType AttribType::create(TypeHandling typeHandling)  { assert(0&&"Provided type does not support typeHandling parameter or missing specialization method."); return AttribType::createInvalid(); }
      template<typename T> inline AttribType AttribType::create(uint8_t numComponents)  { assert(0&&"Provided type does not support numComponents parameter or missing specialization method."); return AttribType::createInvalid(); }
      template<typename T> inline AttribType AttribType::create(uint8_t numComponents,TypeHandling typeHandling)  { assert(0&&"Provided type does not support numComponents and typeHandling parameters specified together, or missing specialization method."); return AttribType::createInvalid(); }

      template<> inline AttribType AttribType::create< int8_t> ()  { return AttribType(GLType::BYTE,          1,1*1,USE_INTEGER); }
      template<> inline AttribType AttribType::create<uint8_t> ()  { return AttribType(GLType::UNSIGNED_BYTE, 1,1*1,USE_INTEGER); }
      template<> inline AttribType AttribType::create< int16_t>()  { return AttribType(GLType::SHORT,         1,2*1,USE_INTEGER); }
      template<> inline AttribType AttribType::create<uint16_t>()  { return AttribType(GLType::UNSIGNED_SHORT,1,2*1,USE_INTEGER); }
      template<> inline AttribType AttribType::create< int32_t>()  { return AttribType(GLType::INT,           1,4*1,USE_INTEGER); }
      template<> inline AttribType AttribType::create<uint32_t>()  { return AttribType(GLType::UNSIGNED_INT,  1,4*1,USE_INTEGER); }
      template<> inline AttribType AttribType::create<float>   ()  { return AttribType(GLType::FLOAT,         1,4*1,USE_FLOAT); }
      template<> inline AttribType AttribType::create<double>  ()  { return AttribType(GLType::DOUBLE,        1,8*1,USE_DOUBLE); }

      template<> inline AttribType AttribType::create< int8_t> (uint8_t numComponents)  { return AttribType(GLType::BYTE,          numComponents,uint8_t(1*numComponents),USE_INTEGER); }
      template<> inline AttribType AttribType::create<uint8_t> (uint8_t numComponents)  { return AttribType(GLType::UNSIGNED_BYTE, numComponents,uint8_t(1*numComponents),USE_INTEGER); }
      template<> inline AttribType AttribType::create< int16_t>(uint8_t numComponents)  { return AttribType(GLType::SHORT,         numComponents,uint8_t(2*numComponents),USE_INTEGER); }
      template<> inline AttribType AttribType::create<uint16_t>(uint8_t numComponents)  { return AttribType(GLType::UNSIGNED_SHORT,numComponents,uint8_t(2*numComponents),USE_INTEGER); }
      template<> inline AttribType AttribType::create< int32_t>(uint8_t numComponents)  { return AttribType(GLType::INT,           numComponents,uint8_t(4*numComponents),USE_INTEGER); }
      template<> inline AttribType AttribType::create<uint32_t>(uint8_t numComponents)  { return AttribType(GLType::UNSIGNED_INT,  numComponents,uint8_t(4*numComponents),USE_INTEGER); }
      template<> inline AttribType AttribType::create<float>   (uint8_t numComponents)  { return AttribType(GLType::FLOAT,         numComponents,uint8_t(4*numComponents),USE_FLOAT); }
      template<> inline AttribType AttribType::create<double>  (uint8_t numComponents)  { return AttribType(GLType::DOUBLE,        numComponents,uint8_t(8*numComponents),USE_DOUBLE); }

      template<> inline AttribType AttribType::create< int8_t> (uint8_t numComponents,TypeHandling typeHandling)  { return AttribType(GLType::BYTE,          numComponents,uint8_t(1*numComponents),typeHandling); }
      template<> inline AttribType AttribType::create<uint8_t> (uint8_t numComponents,TypeHandling typeHandling)  { return AttribType(GLType::UNSIGNED_BYTE, numComponents,uint8_t(1*numComponents),typeHandling); }
      template<> inline AttribType AttribType::create< int16_t>(uint8_t numComponents,TypeHandling typeHandling)  { return AttribType(GLType::SHORT,         numComponents,uint8_t(2*numComponents),typeHandling); }
      template<> inline AttribType AttribType::create<uint16_t>(uint8_t numComponents,TypeHandling typeHandling)  { return AttribType(GLType::UNSIGNED_SHORT,numComponents,uint8_t(2*numComponents),typeHandling); }
      template<> inline AttribType AttribType::create< int32_t>(uint8_t numComponents,TypeHandling typeHandling)  { return AttribType(GLType::INT,           numComponents,uint8_t(4*numComponents),typeHandling); }
      template<> inline AttribType AttribType::create<uint32_t>(uint8_t numComponents,TypeHandling typeHandling)  { return AttribType(GLType::UNSIGNED_INT,  numComponents,uint8_t(4*numComponents),typeHandling); }

      template<> inline AttribType AttribType::create<glm::vec2> ()  { return AttribType(GLType::FLOAT,2,4*2, USE_FLOAT); }
      template<> inline AttribType AttribType::create<glm::vec3> ()  { return AttribType(GLType::FLOAT,3,4*3, USE_FLOAT); }
      template<> inline AttribType AttribType::create<glm::vec4> ()  { return AttribType(GLType::FLOAT,4,4*4, USE_FLOAT); }
      template<> inline AttribType AttribType::create<glm::dvec2>()  { return AttribType(GLType::DOUBLE,2,8*2,USE_DOUBLE); }
      template<> inline AttribType AttribType::create<glm::dvec3>()  { return AttribType(GLType::DOUBLE,3,8*3,USE_DOUBLE); }
      template<> inline AttribType AttribType::create<glm::dvec4>()  { return AttribType(GLType::DOUBLE,4,8*4,USE_DOUBLE); }
      template<> inline AttribType AttribType::create<glm::ivec2>()  { return AttribType(GLType::INT,2,4*2,   USE_INTEGER); }
      template<> inline AttribType AttribType::create<glm::ivec3>()  { return AttribType(GLType::INT,3,4*3,   USE_INTEGER); }
      template<> inline AttribType AttribType::create<glm::ivec4>()  { return AttribType(GLType::INT,4,4*4,   USE_INTEGER); }
      template<> inline AttribType AttribType::create<glm::uvec2>()  { return AttribType(GLType::UNSIGNED_INT,2,4*2,USE_INTEGER); }
      template<> inline AttribType AttribType::create<glm::uvec3>()  { return AttribType(GLType::UNSIGNED_INT,3,4*3,USE_INTEGER); }
      template<> inline AttribType AttribType::create<glm::uvec4>()  { return AttribType(GLType::UNSIGNED_INT,4,4*4,USE_INTEGER); }

      template<> inline AttribType AttribType::create<glm::ivec2>(TypeHandling typeHandling)  { return AttribType(GLType::INT,2,4*2,typeHandling); }
      template<> inline AttribType AttribType::create<glm::ivec3>(TypeHandling typeHandling)  { return AttribType(GLType::INT,3,4*3,typeHandling); }
      template<> inline AttribType AttribType::create<glm::ivec4>(TypeHandling typeHandling)  { return AttribType(GLType::INT,4,4*4,typeHandling); }
      template<> inline AttribType AttribType::create<glm::uvec2>(TypeHandling typeHandling)  { return AttribType(GLType::UNSIGNED_INT,2,4*2,typeHandling); }
      template<> inline AttribType AttribType::create<glm::uvec3>(TypeHandling typeHandling)  { return AttribType(GLType::UNSIGNED_INT,3,4*3,typeHandling); }
      template<> inline AttribType AttribType::create<glm::uvec4>(TypeHandling typeHandling)  { return AttribType(GLType::UNSIGNED_INT,4,4*4,typeHandling); }

      template<> inline AttribType AttribType::create<GLType::UNSIGNED_BYTE> (uint8_t numComponents)  { return AttribType(GLType::UNSIGNED_BYTE, numComponents,uint8_t(1*numComponents),USE_INTEGER); }
      template<> inline AttribType AttribType::create<GLType::BYTE>          (uint8_t numComponents)  { return AttribType(GLType::BYTE,          numComponents,uint8_t(1*numComponents),USE_INTEGER); }
      template<> inline AttribType AttribType::create<GLType::UNSIGNED_SHORT>(uint8_t numComponents)  { return AttribType(GLType::UNSIGNED_SHORT,numComponents,uint8_t(2*numComponents),USE_INTEGER); }
      template<> inline AttribType AttribType::create<GLType::SHORT>         (uint8_t numComponents)  { return AttribType(GLType::SHORT,         numComponents,uint8_t(2*numComponents),USE_INTEGER); }
      template<> inline AttribType AttribType::create<GLType::UNSIGNED_INT>  (uint8_t numComponents)  { return AttribType(GLType::UNSIGNED_INT,  numComponents,uint8_t(4*numComponents),USE_INTEGER); }
      template<> inline AttribType AttribType::create<GLType::INT>           (uint8_t numComponents)  { return AttribType(GLType::INT,           numComponents,uint8_t(4*numComponents),USE_INTEGER); }
      template<> inline AttribType AttribType::create<GLType::FLOAT>         (uint8_t numComponents)  { return AttribType(GLType::FLOAT,         numComponents,uint8_t(4*numComponents),USE_FLOAT); }
      template<> inline AttribType AttribType::create<GLType::DOUBLE>        (uint8_t numComponents)  { return AttribType(GLType::DOUBLE,        numComponents,uint8_t(8*numComponents),USE_FLOAT); }
      template<> inline AttribType AttribType::create<GLType::HALF_FLOAT>    (uint8_t numComponents)  { return AttribType(GLType::HALF_FLOAT,    numComponents,uint8_t(2*numComponents),USE_FLOAT); }
      template<> inline AttribType AttribType::create<GLType::FIXED>         (uint8_t numComponents)  { return AttribType(GLType::FIXED,         numComponents,uint8_t(4*numComponents),USE_FLOAT); }

      template<> inline AttribType AttribType::create<GLType::UNSIGNED_BYTE_3_3_2>           ()  { return AttribType(GLType::UNSIGNED_BYTE_3_3_2,           3,1,INTEGER_NORMALIZE); }
      template<> inline AttribType AttribType::create<GLType::UNSIGNED_BYTE_2_3_3_REV>       ()  { return AttribType(GLType::UNSIGNED_BYTE_2_3_3_REV,       3,1,INTEGER_NORMALIZE); }
      template<> inline AttribType AttribType::create<GLType::UNSIGNED_SHORT_5_6_5>          ()  { return AttribType(GLType::UNSIGNED_SHORT_5_6_5,          3,2,INTEGER_NORMALIZE); }
      template<> inline AttribType AttribType::create<GLType::UNSIGNED_SHORT_5_6_5_REV>      ()  { return AttribType(GLType::UNSIGNED_SHORT_5_6_5_REV,      3,2,INTEGER_NORMALIZE); }
      template<> inline AttribType AttribType::create<GLType::UNSIGNED_SHORT_4_4_4_4>        ()  { return AttribType(GLType::UNSIGNED_SHORT_4_4_4_4,        4,2,INTEGER_NORMALIZE); }
      template<> inline AttribType AttribType::create<GLType::UNSIGNED_SHORT_4_4_4_4_REV>    ()  { return AttribType(GLType::UNSIGNED_SHORT_4_4_4_4_REV,    4,2,INTEGER_NORMALIZE); }
      template<> inline AttribType AttribType::create<GLType::UNSIGNED_SHORT_5_5_5_1>        ()  { return AttribType(GLType::UNSIGNED_SHORT_5_5_5_1,        4,2,INTEGER_NORMALIZE); }
      template<> inline AttribType AttribType::create<GLType::UNSIGNED_SHORT_1_5_5_5_REV>    ()  { return AttribType(GLType::UNSIGNED_SHORT_1_5_5_5_REV,    4,2,INTEGER_NORMALIZE); }
      template<> inline AttribType AttribType::create<GLType::UNSIGNED_INT_8_8_8_8>          ()  { return AttribType(GLType::UNSIGNED_INT_8_8_8_8,          4,4,INTEGER_NORMALIZE); }
      template<> inline AttribType AttribType::create<GLType::UNSIGNED_INT_8_8_8_8_REV>      ()  { return AttribType(GLType::UNSIGNED_INT_8_8_8_8_REV,      4,4,INTEGER_NORMALIZE); }
      template<> inline AttribType AttribType::create<GLType::UNSIGNED_INT_10_10_10_2>       ()  { return AttribType(GLType::UNSIGNED_INT_10_10_10_2,       4,4,INTEGER_NORMALIZE); }
      template<> inline AttribType AttribType::create<GLType::UNSIGNED_INT_2_10_10_10_REV>   ()  { return AttribType(GLType::UNSIGNED_INT_2_10_10_10_REV,   4,4,INTEGER_NORMALIZE); }
      template<> inline AttribType AttribType::create<GLType::UNSIGNED_INT_24_8>             ()  { return AttribType(GLType::UNSIGNED_INT_24_8,             2,4,INTEGER_NORMALIZE); }
      template<> inline AttribType AttribType::create<GLType::UNSIGNED_INT_10F_11F_11F_REV>  ()  { return AttribType(GLType::UNSIGNED_INT_10F_11F_11F_REV,  3,4,USE_FLOAT); }
      template<> inline AttribType AttribType::create<GLType::UNSIGNED_INT_5_9_9_9_REV>      ()  { return AttribType(GLType::UNSIGNED_INT_5_9_9_9_REV,      4,4,INTEGER_NORMALIZE); }
      template<> inline AttribType AttribType::create<GLType::FLOAT_32_UNSIGNED_INT_24_8_REV>()  { return AttribType(GLType::FLOAT_32_UNSIGNED_INT_24_8_REV,2,8,INTEGER_NORMALIZE); }

      template<> inline AttribType AttribType::create<GLType::UNSIGNED_BYTE> (uint8_t numComponents,TypeHandling typeHandling)  { return AttribType(GLType::UNSIGNED_BYTE, numComponents,uint8_t(1*numComponents),typeHandling); }
      template<> inline AttribType AttribType::create<GLType::BYTE>          (uint8_t numComponents,TypeHandling typeHandling)  { return AttribType(GLType::BYTE,          numComponents,uint8_t(1*numComponents),typeHandling); }
      template<> inline AttribType AttribType::create<GLType::UNSIGNED_SHORT>(uint8_t numComponents,TypeHandling typeHandling)  { return AttribType(GLType::UNSIGNED_SHORT,numComponents,uint8_t(2*numComponents),typeHandling); }
      template<> inline AttribType AttribType::create<GLType::SHORT>         (uint8_t numComponents,TypeHandling typeHandling)  { return AttribType(GLType::SHORT,         numComponents,uint8_t(2*numComponents),typeHandling); }
      template<> inline AttribType AttribType::create<GLType::UNSIGNED_INT>  (uint8_t numComponents,TypeHandling typeHandling)  { return AttribType(GLType::UNSIGNED_INT,  numComponents,uint8_t(4*numComponents),typeHandling); }
      template<> inline AttribType AttribType::create<GLType::INT>           (uint8_t numComponents,TypeHandling typeHandling)  { return AttribType(GLType::INT,           numComponents,uint8_t(4*numComponents),typeHandling); }

      template<> inline AttribType AttribType::create<GLType::MAT2>()  { return AttribType(GLType::MAT2,4, 4*4, NOT_DEFINED); }
      template<> inline AttribType AttribType::create<GLType::MAT3>()  { return AttribType(GLType::MAT3,9, 4*9, NOT_DEFINED); }
      template<> inline AttribType AttribType::create<GLType::MAT4>()  { return AttribType(GLType::MAT4,16,4*16,NOT_DEFINED); }

      template<> inline AttribType AttribType::create<GLType::MAT2X3>()  { return AttribType(GLType::MAT2X3,6, 4*6, NOT_DEFINED); }
      template<> inline AttribType AttribType::create<GLType::MAT2X4>()  { return AttribType(GLType::MAT2X4,8, 4*8, NOT_DEFINED); }
      template<> inline AttribType AttribType::create<GLType::MAT3X2>()  { return AttribType(GLType::MAT3X2,6, 4*6, NOT_DEFINED); }
      template<> inline AttribType AttribType::create<GLType::MAT3X4>()  { return AttribType(GLType::MAT3X4,12,4*12,NOT_DEFINED); }
      template<> inline AttribType AttribType::create<GLType::MAT4X2>()  { return AttribType(GLType::MAT4X2,8, 4*8, NOT_DEFINED); }
      template<> inline AttribType AttribType::create<GLType::MAT4X3>()  { return AttribType(GLType::MAT4X3,12,4*12,NOT_DEFINED); }

      template<> inline AttribType AttribType::create<GLType::DMAT2>()  { return AttribType(GLType::DMAT2,4, 8*4, NOT_DEFINED); }
      template<> inline AttribType AttribType::create<GLType::DMAT3>()  { return AttribType(GLType::DMAT3,9, 8*9, NOT_DEFINED); }
      template<> inline AttribType AttribType::create<GLType::DMAT4>()  { return AttribType(GLType::DMAT4,16,8*16,NOT_DEFINED); }

      template<> inline AttribType AttribType::create<GLType::DMAT2X3>()  { return AttribType(GLType::DMAT2X3,6, 8*6, NOT_DEFINED); }
      template<> inline AttribType AttribType::create<GLType::DMAT2X4>()  { return AttribType(GLType::DMAT2X4,8, 8*8, NOT_DEFINED); }
      template<> inline AttribType AttribType::create<GLType::DMAT3X2>()  { return AttribType(GLType::DMAT3X2,6, 8*6, NOT_DEFINED); }
      template<> inline AttribType AttribType::create<GLType::DMAT3X4>()  { return AttribType(GLType::DMAT3X4,12,8*12,NOT_DEFINED); }
      template<> inline AttribType AttribType::create<GLType::DMAT4X2>()  { return AttribType(GLType::DMAT4X2,8, 8*8, NOT_DEFINED); }
      template<> inline AttribType AttribType::create<GLType::DMAT4X3>()  { return AttribType(GLType::DMAT4X3,12,8*12,NOT_DEFINED); }

      template<> inline AttribType AttribType::create<GLType::INVALID>()  { return AttribType(GLType::INVALID,0,0,NOT_DEFINED); }
      template<> inline AttribType AttribType::create<GLType::INVALID>(uint8_t numComponents)  { return AttribType(GLType::INVALID,numComponents,0,NOT_DEFINED); }

   }
}

#endif // GE_RG_ATTRIB_TYPE_H
