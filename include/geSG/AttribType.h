#ifndef GE_SG_ATTRIB_TYPE_H
#define GE_SG_ATTRIB_TYPE_H

#include <glm/glm.hpp>

namespace ge
{
   namespace sg
   {

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


      class AttribType {
      public:

         enum TypeHandling { NOT_DEFINED=0, INTEGER_CAST=0, INTEGER_NORMALIZE=1, USE_FORMAT=0, USE_IFORMAT=2, USE_LFORMAT=3 };

      protected:

         union {
            struct {
               union {
                  struct {
                     GLType  _glType;
                     int     _numComponents : 5; // range 1..16
                     bool    _bgra : 1;
                     int     _elementSize : 8; // range 1..128
                     TypeHandling  _typeHandling : 2; // four options
                  };
                  uint32_t _attribType32;
               };
               uint32_t  _divisor;
            };
            uint64_t _attribType64;
         };

      public:

         inline AttribType()  {}
         inline AttribType(GLType glType,uint8_t numComponents,uint8_t elementSize,
                           TypeHandling typeHandling,unsigned divisor=0);
         inline AttribType(GLType glType,uint8_t numComponents,bool bgra,uint8_t elementSize,
                           TypeHandling typeHandling,unsigned divisor=0);
         inline AttribType(const AttribType& a);

         inline AttribType& operator=(AttribType a);

         inline GLType getGLType() const  { return _glType; }
         inline uint16_t getGLTypeAsInt() const  { return uint16_t(_glType); }
         inline void setGLType(GLType value)  { _glType = value; }
         inline int getNumComponents() const  { return _numComponents; }
         inline void setNumComponents(int value)  { _numComponents=value; }
         inline bool getBGRA() const  { return _bgra; }
         inline void setBGRA(bool value)  { _bgra=value; }
         inline int getElementSize() const  { return _elementSize; }
         inline void setElementSize(int value)  { _elementSize=value; }
         inline TypeHandling getTypeHandling() const  { return _typeHandling; }
         inline void setTypeHandling(TypeHandling value)  { _typeHandling=value; }
         inline uint32_t getDivisor() const  { return _divisor; }
         inline void setDivisor(uint32_t value)  { _divisor=value; }
         inline uint32_t getAsInt32() const  { return _attribType32; }
         inline void setAsInt32(uint32_t value)  { _attribType32=value; }
         inline uint64_t getAsInt64() const  { return _attribType64; }
         inline void setAsInt64(uint64_t value)  { _attribType64=value; }

         template<GLType T> static inline AttribType create();
         template<GLType T> static inline AttribType create(uint8_t numComponents);
         template<GLType T> static inline AttribType create(uint8_t numComponents,TypeHandling typeHandling);
         template<typename T> static inline AttribType create();
         template<typename T> static inline AttribType create(TypeHandling typeHandling);
         template<typename T> static inline AttribType create(uint8_t numComponents);
         template<typename T> static inline AttribType create(uint8_t numComponents,TypeHandling typeHandling);
         static inline AttribType createInvalid();
         static inline AttribType createEmpty();

         inline void invalidate();
         inline void makeEmpty();

         inline bool operator==(const AttribType a) const;
         inline bool operator!=(const AttribType a) const;
         inline bool operator< (const AttribType a) const;
         inline bool operator> (const AttribType a) const;
         inline bool operator<=(const AttribType a) const;
         inline bool operator>=(const AttribType a) const;

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
      inline AttribType::AttribType(GLType glType,uint8_t numComponents,uint8_t elementSize,
                                    TypeHandling typeHandling,unsigned divisor)
            :_glType(glType),_numComponents(numComponents),_bgra(false)
            ,_elementSize(elementSize),_typeHandling(typeHandling),_divisor(divisor)  {}
      inline AttribType::AttribType(GLType glType,uint8_t numComponents,bool bgra,uint8_t elementSize,
                                    TypeHandling typeHandling,unsigned divisor)
            :_glType(glType),_numComponents(numComponents),_bgra(bgra)
            ,_elementSize(elementSize),_typeHandling(typeHandling),_divisor(divisor)  {}
      inline AttribType::AttribType(const AttribType& a) : _attribType64(a._attribType64)  {}
      inline AttribType& AttribType::operator=(AttribType a) { _attribType64=a._attribType64; return *this; }

      inline AttribType AttribType::createInvalid()  { return AttribType(GLType::INVALID,0,0,NOT_DEFINED); }
      inline AttribType AttribType::createEmpty()  { return createInvalid(); }
      inline void AttribType::invalidate()  { _glType=GLType::INVALID; _numComponents=0; _bgra=false; _elementSize=0; _typeHandling=NOT_DEFINED; }
      inline void AttribType::makeEmpty()  { invalidate(); }

      inline bool AttribType::operator==(const AttribType a) const  { return _attribType64==a._attribType64; }
      inline bool AttribType::operator!=(const AttribType a) const  { return _attribType64!=a._attribType64; }
      inline bool AttribType::operator< (const AttribType a) const  { return _attribType64<a._attribType64; }
      inline bool AttribType::operator> (const AttribType a) const  { return _attribType64>a._attribType64; }
      inline bool AttribType::operator<=(const AttribType a) const  { return _attribType64<=a._attribType64; }
      inline bool AttribType::operator>=(const AttribType a) const  { return _attribType64>=a._attribType64; }

      template<GLType T> inline AttribType AttribType::create()  { assert(0&&"Missing numComponents parameter or type specialization method."); return AttribType(GLType::INVALID,0,0); }
      template<GLType T> inline AttribType AttribType::create(uint8_t numComponents)  { assert(0&&"Provided GLType does not support numComponents parameter or missing specialization method."); return AttribType(GLType::INVALID,0,0); }
      template<GLType T> inline AttribType AttribType::create(uint8_t numComponents,TypeHandling typeHandling)  { assert(0&&"Provided GLType does not support numComponents and typeHandling parameters specified together, or missing specialization method."); return AttribType(GLType::INVALID,0,0); }
      template<typename T> inline AttribType AttribType::create()  { assert(0&&"Missing numComponents parameter or type specialization method."); return AttribType(GLType::INVALID,0,0); }
      template<typename T> inline AttribType AttribType::create(TypeHandling typeHandling)  { assert(0&&"Provided type does not support typeHandling parameter or missing specialization method."); return AttribType(GLType::INVALID,0,0); }
      template<typename T> inline AttribType AttribType::create(uint8_t numComponents)  { assert(0&&"Provided type does not support numComponents parameter or missing specialization method."); return AttribType(GLType::INVALID,0,0); }
      template<typename T> inline AttribType AttribType::create(uint8_t numComponents,TypeHandling typeHandling)  { assert(0&&"Provided type does not support numComponents and typeHandling parameters specified together, or missing specialization method."); return AttribType(GLType::INVALID,0,0); }

      template<> inline AttribType AttribType::create< int8_t> (uint8_t numComponents)  { return AttribType(GLType::BYTE,          numComponents,1*numComponents,USE_IFORMAT); }
      template<> inline AttribType AttribType::create<uint8_t> (uint8_t numComponents)  { return AttribType(GLType::UNSIGNED_BYTE, numComponents,1*numComponents,USE_IFORMAT); }
      template<> inline AttribType AttribType::create< int16_t>(uint8_t numComponents)  { return AttribType(GLType::SHORT,         numComponents,2*numComponents,USE_IFORMAT); }
      template<> inline AttribType AttribType::create<uint16_t>(uint8_t numComponents)  { return AttribType(GLType::UNSIGNED_SHORT,numComponents,2*numComponents,USE_IFORMAT); }
      template<> inline AttribType AttribType::create< int32_t>(uint8_t numComponents)  { return AttribType(GLType::INT,           numComponents,4*numComponents,USE_IFORMAT); }
      template<> inline AttribType AttribType::create<uint32_t>(uint8_t numComponents)  { return AttribType(GLType::UNSIGNED_INT,  numComponents,4*numComponents,USE_IFORMAT); }
      template<> inline AttribType AttribType::create<float>   (uint8_t numComponents)  { return AttribType(GLType::FLOAT,         numComponents,4*numComponents,USE_FORMAT); }
      template<> inline AttribType AttribType::create<double>  (uint8_t numComponents)  { return AttribType(GLType::DOUBLE,        numComponents,8*numComponents,USE_LFORMAT); }

      template<> inline AttribType AttribType::create<glm::vec2> ()  { return AttribType(GLType::FLOAT,2,4*2, USE_FORMAT); }
      template<> inline AttribType AttribType::create<glm::vec3> ()  { return AttribType(GLType::FLOAT,3,4*3, USE_FORMAT); }
      template<> inline AttribType AttribType::create<glm::vec4> ()  { return AttribType(GLType::FLOAT,4,4*4, USE_FORMAT); }
      template<> inline AttribType AttribType::create<glm::dvec2>()  { return AttribType(GLType::DOUBLE,2,8*2,USE_LFORMAT); }
      template<> inline AttribType AttribType::create<glm::dvec3>()  { return AttribType(GLType::DOUBLE,3,8*3,USE_LFORMAT); }
      template<> inline AttribType AttribType::create<glm::dvec4>()  { return AttribType(GLType::DOUBLE,4,8*4,USE_LFORMAT); }
      template<> inline AttribType AttribType::create<glm::ivec2>()  { return AttribType(GLType::INT,2,4*2,   USE_IFORMAT); }
      template<> inline AttribType AttribType::create<glm::ivec3>()  { return AttribType(GLType::INT,3,4*3,   USE_IFORMAT); }
      template<> inline AttribType AttribType::create<glm::ivec4>()  { return AttribType(GLType::INT,4,4*4,   USE_IFORMAT); }
      template<> inline AttribType AttribType::create<glm::uvec2>()  { return AttribType(GLType::UNSIGNED_INT,2,4*2,USE_IFORMAT); }
      template<> inline AttribType AttribType::create<glm::uvec3>()  { return AttribType(GLType::UNSIGNED_INT,3,4*3,USE_IFORMAT); }
      template<> inline AttribType AttribType::create<glm::uvec4>()  { return AttribType(GLType::UNSIGNED_INT,4,4*4,USE_IFORMAT); }

      template<> inline AttribType AttribType::create< int8_t> (uint8_t numComponents,TypeHandling typeHandling)  { return AttribType(GLType::BYTE,          numComponents,1*numComponents,typeHandling); }
      template<> inline AttribType AttribType::create<uint8_t> (uint8_t numComponents,TypeHandling typeHandling)  { return AttribType(GLType::UNSIGNED_BYTE, numComponents,1*numComponents,typeHandling); }
      template<> inline AttribType AttribType::create< int16_t>(uint8_t numComponents,TypeHandling typeHandling)  { return AttribType(GLType::SHORT,         numComponents,2*numComponents,typeHandling); }
      template<> inline AttribType AttribType::create<uint16_t>(uint8_t numComponents,TypeHandling typeHandling)  { return AttribType(GLType::UNSIGNED_SHORT,numComponents,2*numComponents,typeHandling); }
      template<> inline AttribType AttribType::create< int32_t>(uint8_t numComponents,TypeHandling typeHandling)  { return AttribType(GLType::INT,           numComponents,4*numComponents,typeHandling); }
      template<> inline AttribType AttribType::create<uint32_t>(uint8_t numComponents,TypeHandling typeHandling)  { return AttribType(GLType::UNSIGNED_INT,  numComponents,4*numComponents,typeHandling); }

      template<> inline AttribType AttribType::create<glm::ivec2>(TypeHandling typeHandling)  { return AttribType(GLType::INT,2,4*2,typeHandling); }
      template<> inline AttribType AttribType::create<glm::ivec3>(TypeHandling typeHandling)  { return AttribType(GLType::INT,3,4*3,typeHandling); }
      template<> inline AttribType AttribType::create<glm::ivec4>(TypeHandling typeHandling)  { return AttribType(GLType::INT,4,4*4,typeHandling); }
      template<> inline AttribType AttribType::create<glm::uvec2>(TypeHandling typeHandling)  { return AttribType(GLType::UNSIGNED_INT,2,4*2,typeHandling); }
      template<> inline AttribType AttribType::create<glm::uvec3>(TypeHandling typeHandling)  { return AttribType(GLType::UNSIGNED_INT,3,4*3,typeHandling); }
      template<> inline AttribType AttribType::create<glm::uvec4>(TypeHandling typeHandling)  { return AttribType(GLType::UNSIGNED_INT,4,4*4,typeHandling); }

      template<> inline AttribType AttribType::create<GLType::UNSIGNED_BYTE> (uint8_t numComponents)  { return AttribType(GLType::UNSIGNED_BYTE, numComponents,1*numComponents,USE_IFORMAT); }
      template<> inline AttribType AttribType::create<GLType::BYTE>          (uint8_t numComponents)  { return AttribType(GLType::BYTE,          numComponents,1*numComponents,USE_IFORMAT); }
      template<> inline AttribType AttribType::create<GLType::UNSIGNED_SHORT>(uint8_t numComponents)  { return AttribType(GLType::UNSIGNED_SHORT,numComponents,2*numComponents,USE_IFORMAT); }
      template<> inline AttribType AttribType::create<GLType::SHORT>         (uint8_t numComponents)  { return AttribType(GLType::SHORT,         numComponents,2*numComponents,USE_IFORMAT); }
      template<> inline AttribType AttribType::create<GLType::UNSIGNED_INT>  (uint8_t numComponents)  { return AttribType(GLType::UNSIGNED_INT,  numComponents,4*numComponents,USE_IFORMAT); }
      template<> inline AttribType AttribType::create<GLType::INT>           (uint8_t numComponents)  { return AttribType(GLType::INT,           numComponents,4*numComponents,USE_IFORMAT); }
      template<> inline AttribType AttribType::create<GLType::FLOAT>         (uint8_t numComponents)  { return AttribType(GLType::FLOAT,         numComponents,4*numComponents,USE_FORMAT); }
      template<> inline AttribType AttribType::create<GLType::DOUBLE>        (uint8_t numComponents)  { return AttribType(GLType::DOUBLE,        numComponents,8*numComponents,USE_FORMAT); }
      template<> inline AttribType AttribType::create<GLType::HALF_FLOAT>    (uint8_t numComponents)  { return AttribType(GLType::HALF_FLOAT,    numComponents,2*numComponents,USE_FORMAT); }
      template<> inline AttribType AttribType::create<GLType::FIXED>         (uint8_t numComponents)  { return AttribType(GLType::FIXED,         numComponents,4*numComponents,USE_FORMAT); }

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
      template<> inline AttribType AttribType::create<GLType::UNSIGNED_INT_10F_11F_11F_REV>  ()  { return AttribType(GLType::UNSIGNED_INT_10F_11F_11F_REV,  3,4,USE_FORMAT); }
      template<> inline AttribType AttribType::create<GLType::UNSIGNED_INT_5_9_9_9_REV>      ()  { return AttribType(GLType::UNSIGNED_INT_5_9_9_9_REV,      4,4,INTEGER_NORMALIZE); }
      template<> inline AttribType AttribType::create<GLType::FLOAT_32_UNSIGNED_INT_24_8_REV>()  { return AttribType(GLType::FLOAT_32_UNSIGNED_INT_24_8_REV,2,8,INTEGER_NORMALIZE); }

      template<> inline AttribType AttribType::create<GLType::UNSIGNED_BYTE> (uint8_t numComponents,TypeHandling typeHandling)  { return AttribType(GLType::UNSIGNED_BYTE, numComponents,1*numComponents,typeHandling); }
      template<> inline AttribType AttribType::create<GLType::BYTE>          (uint8_t numComponents,TypeHandling typeHandling)  { return AttribType(GLType::BYTE,          numComponents,1*numComponents,typeHandling); }
      template<> inline AttribType AttribType::create<GLType::UNSIGNED_SHORT>(uint8_t numComponents,TypeHandling typeHandling)  { return AttribType(GLType::UNSIGNED_SHORT,numComponents,2*numComponents,typeHandling); }
      template<> inline AttribType AttribType::create<GLType::SHORT>         (uint8_t numComponents,TypeHandling typeHandling)  { return AttribType(GLType::SHORT,         numComponents,2*numComponents,typeHandling); }
      template<> inline AttribType AttribType::create<GLType::UNSIGNED_INT>  (uint8_t numComponents,TypeHandling typeHandling)  { return AttribType(GLType::UNSIGNED_INT,  numComponents,4*numComponents,typeHandling); }
      template<> inline AttribType AttribType::create<GLType::INT>           (uint8_t numComponents,TypeHandling typeHandling)  { return AttribType(GLType::INT,           numComponents,4*numComponents,typeHandling); }

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

#endif // GE_SG_ATTRIB_TYPE_H
