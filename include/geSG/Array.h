#ifndef GE_SG_ARRAY_H
#define GE_SG_ARRAY_H

#include <memory>
#include <vector>
#include <glm/glm.hpp>

namespace ge
{
   namespace sg
   {

      class ValueVisitor
      {
      public:

         virtual void apply(bool&) {}
         virtual void apply(char&) {}
         virtual void apply(short&) {}
         virtual void apply(int&) {}
         virtual void apply(unsigned char&) {}
         virtual void apply(unsigned short&) {}
         virtual void apply(unsigned&) {}
         virtual void apply(float&) {}
         virtual void apply(double&) {}

         virtual void apply(glm::vec2&) {}
         virtual void apply(glm::vec3&) {}
         virtual void apply(glm::vec4&) {}
         virtual void apply(glm::dvec2&) {}
         virtual void apply(glm::dvec3&) {}
         virtual void apply(glm::dvec4&) {}

         virtual void apply(glm::bvec2&) {}
         virtual void apply(glm::bvec3&) {}
         virtual void apply(glm::bvec4&) {}
         virtual void apply(glm::ivec2&) {}
         virtual void apply(glm::ivec3&) {}
         virtual void apply(glm::ivec4&) {}
         virtual void apply(glm::uvec2&) {}
         virtual void apply(glm::uvec3&) {}
         virtual void apply(glm::uvec4&) {}

         virtual void apply(glm::mat2&) {}
         virtual void apply(glm::mat3&) {}
         virtual void apply(glm::mat4&) {}
         virtual void apply(glm::mat2x3&) {}
         virtual void apply(glm::mat2x4&) {}
         virtual void apply(glm::mat3x2&) {}
         virtual void apply(glm::mat3x4&) {}
         virtual void apply(glm::mat4x2&) {}
         virtual void apply(glm::mat4x3&) {}

         virtual void apply(glm::dmat2&) {}
         virtual void apply(glm::dmat3&) {}
         virtual void apply(glm::dmat4&) {}
         virtual void apply(glm::dmat2x3&) {}
         virtual void apply(glm::dmat2x4&) {}
         virtual void apply(glm::dmat3x2&) {}
         virtual void apply(glm::dmat3x4&) {}
         virtual void apply(glm::dmat4x2&) {}
         virtual void apply(glm::dmat4x3&) {}
      };


      class ArrayVisitor
      {
      public:

         virtual void apply(std::vector<bool>&) {}
         virtual void apply(std::vector<char>&) {}
         virtual void apply(std::vector<unsigned char>&) {}
         virtual void apply(std::vector<short>&) {}
         virtual void apply(std::vector<unsigned short>&) {}
         virtual void apply(std::vector<int>&) {}
         virtual void apply(std::vector<unsigned>&) {}
         virtual void apply(std::vector<float>&) {}
         virtual void apply(std::vector<double>&) {}

         virtual void apply(std::vector<glm::vec2>&) {}
         virtual void apply(std::vector<glm::vec3>&) {}
         virtual void apply(std::vector<glm::vec4>&) {}
         virtual void apply(std::vector<glm::dvec2>&) {}
         virtual void apply(std::vector<glm::dvec3>&) {}
         virtual void apply(std::vector<glm::dvec4>&) {}

         virtual void apply(std::vector<glm::bvec2>&) {}
         virtual void apply(std::vector<glm::bvec3>&) {}
         virtual void apply(std::vector<glm::bvec4>&) {}
         virtual void apply(std::vector<glm::ivec2>&) {}
         virtual void apply(std::vector<glm::ivec3>&) {}
         virtual void apply(std::vector<glm::ivec4>&) {}
         virtual void apply(std::vector<glm::uvec2>&) {}
         virtual void apply(std::vector<glm::uvec3>&) {}
         virtual void apply(std::vector<glm::uvec4>&) {}

         virtual void apply(std::vector<glm::mat2>&) {}
         virtual void apply(std::vector<glm::mat3>&) {}
         virtual void apply(std::vector<glm::mat4>&) {}
         virtual void apply(std::vector<glm::mat2x3>&) {}
         virtual void apply(std::vector<glm::mat2x4>&) {}
         virtual void apply(std::vector<glm::mat3x2>&) {}
         virtual void apply(std::vector<glm::mat3x4>&) {}
         virtual void apply(std::vector<glm::mat4x2>&) {}
         virtual void apply(std::vector<glm::mat4x3>&) {}

         virtual void apply(std::vector<glm::dmat2>&) {}
         virtual void apply(std::vector<glm::dmat3>&) {}
         virtual void apply(std::vector<glm::dmat4>&) {}
         virtual void apply(std::vector<glm::dmat2x3>&) {}
         virtual void apply(std::vector<glm::dmat2x4>&) {}
         virtual void apply(std::vector<glm::dmat3x2>&) {}
         virtual void apply(std::vector<glm::dmat3x4>&) {}
         virtual void apply(std::vector<glm::dmat4x2>&) {}
         virtual void apply(std::vector<glm::dmat4x3>&) {}
      };


      class ArrayDecorator
      {
      public:
         virtual void accept(int index,ValueVisitor& visitor) = 0;
         virtual void accept(ArrayVisitor& visitor) = 0;
      };


      template<typename T>
      class ArrayDecoratorTemplate : public ArrayDecorator
      {
      protected:
         std::shared_ptr<std::vector<T>> _array;
      public:

         ArrayDecoratorTemplate() {}
         ArrayDecoratorTemplate(const std::shared_ptr<std::vector<T>> &array) : _array(array) {}

         std::shared_ptr<std::vector<T>> get() { return _array; }
         const std::shared_ptr<std::vector<T>>& get() const { return _array; }

         virtual void set(const std::shared_ptr<std::vector<T>> &array) { _array=array; }

         virtual void accept(int index,ValueVisitor& visitor) { visitor.apply((*_array)[index]); }
         virtual void accept(ArrayVisitor& visitor) { visitor.apply(*_array); }
      };


      template<>
      class ArrayDecoratorTemplate<bool> : public ArrayDecorator
      {
      protected:
         std::shared_ptr<std::vector<bool>> _array;
      public:

         ArrayDecoratorTemplate() {}
         ArrayDecoratorTemplate(const std::shared_ptr<std::vector<bool>> &array) : _array(array) {}

         std::shared_ptr<std::vector<bool>> get() { return _array; }
         const std::shared_ptr<std::vector<bool>>& get() const { return _array; }

         virtual void set(const std::shared_ptr<std::vector<bool>> &array) { _array=array; }

         virtual void accept(int index,ValueVisitor& visitor) { bool tmp=(*_array)[index]; visitor.apply(tmp); (*_array)[index] = tmp; }
         virtual void accept(ArrayVisitor& visitor) { visitor.apply(*_array); }
      };


      class ArrayAdapter
      {
      protected:

         union {
            struct {
               unsigned short _glType;
               unsigned short _glNumComponents;
            };
            unsigned int _arrayType;
         };
         int             _elementSize;
         std::shared_ptr<ArrayDecorator> _arrayDecorator;

      public:

         enum class GLType : unsigned short
         {
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
            UNKNOWN = 0x0000,
         };

         static const unsigned short BGRA = 0x80E1;

         enum class Type : unsigned int
         {
            Empty = 0,
            Unknown = 0,

            Byte  = int(GLType::BYTE) | 1 << 16,
            BVec2 = int(GLType::BYTE) | 2 << 16,
            BVec3 = int(GLType::BYTE) | 3 << 16,
            BVec4 = int(GLType::BYTE) | 4 << 16,

            UByte  = int(GLType::UNSIGNED_BYTE) | 1 << 16,
            UBVec2 = int(GLType::UNSIGNED_BYTE) | 2 << 16,
            UBVec3 = int(GLType::UNSIGNED_BYTE) | 3 << 16,
            UBVec4 = int(GLType::UNSIGNED_BYTE) | 4 << 16,

            Short = int(GLType::SHORT) | 1 << 16,
            SVec2 = int(GLType::SHORT) | 2 << 16,
            SVec3 = int(GLType::SHORT) | 3 << 16,
            SVec4 = int(GLType::SHORT) | 4 << 16,

            UShort = int(GLType::UNSIGNED_SHORT) | 1 << 16,
            USVec2 = int(GLType::UNSIGNED_SHORT) | 2 << 16,
            USVec3 = int(GLType::UNSIGNED_SHORT) | 3 << 16,
            USVec4 = int(GLType::UNSIGNED_SHORT) | 4 << 16,

            Int   = int(GLType::INT) | 1 << 16,
            IVec2 = int(GLType::INT) | 2 << 16,
            IVec3 = int(GLType::INT) | 3 << 16,
            IVec4 = int(GLType::INT) | 4 << 16,

            UInt  = int(GLType::UNSIGNED_INT) | 1 << 16,
            UVec2 = int(GLType::UNSIGNED_INT) | 2 << 16,
            UVec3 = int(GLType::UNSIGNED_INT) | 3 << 16,
            UVec4 = int(GLType::UNSIGNED_INT) | 4 << 16,

            Float = int(GLType::FLOAT) | 1 << 16,
            Vec2  = int(GLType::FLOAT) | 2 << 16,
            Vec3  = int(GLType::FLOAT) | 3 << 16,
            Vec4  = int(GLType::FLOAT) | 4 << 16,

            Double = int(GLType::DOUBLE) | 1 << 16,
            DVec2  = int(GLType::DOUBLE) | 2 << 16,
            DVec3  = int(GLType::DOUBLE) | 3 << 16,
            DVec4  = int(GLType::DOUBLE) | 4 << 16,

            Half   = int(GLType::HALF_FLOAT) | 1 << 16,
            HVec2  = int(GLType::HALF_FLOAT) | 2 << 16,
            HVec3  = int(GLType::HALF_FLOAT) | 3 << 16,
            HVec4  = int(GLType::HALF_FLOAT) | 4 << 16,

            Mat2   = int(GLType::MAT2) | 1 << 16,
            Mat3   = int(GLType::MAT3) | 1 << 16,
            Mat4   = int(GLType::MAT4) | 1 << 16,

            Mat2x3 = int(GLType::MAT2X3) | 1 << 16,
            Mat2x4 = int(GLType::MAT2X4) | 1 << 16,
            Mat3x2 = int(GLType::MAT3X2) | 1 << 16,
            Mat3x4 = int(GLType::MAT3X4) | 1 << 16,
            Mat4x2 = int(GLType::MAT4X2) | 1 << 16,
            Mat4x3 = int(GLType::MAT4X3) | 1 << 16,

            DMat2   = int(GLType::DMAT2) | 1 << 16,
            DMat3   = int(GLType::DMAT3) | 1 << 16,
            DMat4   = int(GLType::DMAT4) | 1 << 16,

            DMat2x3 = int(GLType::DMAT2X3) | 1 << 16,
            DMat2x4 = int(GLType::DMAT2X4) | 1 << 16,
            DMat3x2 = int(GLType::DMAT3X2) | 1 << 16,
            DMat3x4 = int(GLType::DMAT3X4) | 1 << 16,
            DMat4x2 = int(GLType::DMAT4X2) | 1 << 16,
            DMat4x3 = int(GLType::DMAT4X3) | 1 << 16,

            Struct = int(GLType::STRUCT) | 1 << 16,
         };

      protected:

         template<typename T>
         static inline GLType makeGLType() { return GLType::UNKNOWN; }
         template<typename T>
         static inline unsigned short getNumComponentsOfType() { return 1; }

         template<typename T>
         static inline unsigned makeType(unsigned short numComponents) { return unsigned(makeGLType<T>()) | unsigned(numComponents)<<16; }
         template<typename T>
         static inline unsigned makeType() { return unsigned(makeGLType<T>()) | unsigned(getNumComponentsOfType<T>())<<16; }

         static inline unsigned makeType(GLType glType,unsigned short numComponents) { return unsigned(glType) | unsigned(numComponents)<<16; }
         static inline unsigned makeType(unsigned short glType,unsigned short numComponents) { return unsigned(glType) | unsigned(numComponents)<<16; }

      public:

         ArrayAdapter() : _arrayType(unsigned(Type::Unknown)), _elementSize(0) {}
         ArrayAdapter(const ArrayAdapter& a) : _arrayType(a._arrayType), _elementSize(a._elementSize), _arrayDecorator(a._arrayDecorator) {}
         ArrayAdapter& operator=(const ArrayAdapter &a)  { _arrayType=a._arrayType; _elementSize=a._elementSize; _arrayDecorator=a._arrayDecorator; return *this; }

         template<typename T>
         inline ArrayAdapter(const std::shared_ptr<std::vector<T>> &ptr) : _arrayType(makeType<T>()), _elementSize(sizeof(T)), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<T>>(ptr)) {}
         template<typename T>
         inline ArrayAdapter(const std::shared_ptr<std::vector<T>> &ptr,unsigned short numComponents) : _arrayType(makeType<T>(numComponents)), _elementSize(sizeof(T)*numComponents/getNumComponentsOfType<T>()), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<T>>(ptr)) {}
         template<typename T>
         inline ArrayAdapter(const std::shared_ptr<std::vector<T>> &ptr,unsigned short numComponents,GLType glType) : _arrayType(makeType(glType,numComponents)), _elementSize(sizeof(T)*numComponents/getNumComponentsOfType<T>()), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<T>>(ptr)) {}
         template<typename T>
         inline ArrayAdapter(const std::shared_ptr<std::vector<T>> &ptr,unsigned short numComponents,unsigned glType) : _arrayType(makeType(glType,numComponents)), _elementSize(sizeof(T)*numComponents/getNumComponentsOfType<T>()), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<T>>(ptr)) {}
         template<typename T>
         inline ArrayAdapter(const std::shared_ptr<std::vector<T>> &ptr,unsigned short numComponents,GLType glType,unsigned sizeOfElement) : _arrayType(makeType(glType,numComponents)), _elementSize(sizeOfElement), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<T>>(ptr)) {}
         template<typename T>
         inline ArrayAdapter(const std::shared_ptr<std::vector<T>> &ptr,unsigned short numComponents,unsigned glType,unsigned sizeOfElement) : _arrayType(makeType(glType,numComponents)), _elementSize(sizeOfElement), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<T>>(ptr)) {}

         virtual ~ArrayAdapter() {}

         inline void setType(Type t) { _arrayType = unsigned(t); }
         inline void setType(unsigned t) { _arrayType = t; }
         inline void setType(GLType t,unsigned short numComponents) { _glType=(unsigned short)(t); _glNumComponents=numComponents; }
         inline void setType(unsigned t,unsigned short numComponents) { _glType=t; _glNumComponents=numComponents; }
         inline void setSizeOfElement(unsigned size) { _elementSize = size; }

         inline Type getType() const { return Type(_arrayType); }
         inline unsigned getTypeAsInt() const { return _arrayType; }
         inline GLType getGLType() const { return GLType(_glType); }
         inline unsigned short getGLTypeAsInt() const { return _glType; }
         inline unsigned short getNumComponents() const { return _glNumComponents; }
         inline unsigned getSizeOfElement() const { return _elementSize; }

         void clear() { _arrayType=unsigned(Type::Unknown); _elementSize=0; _arrayDecorator.reset(); }

         inline void set(const std::nullptr_t ptr) { clear(); }

         template<typename T>
         inline void set(const std::shared_ptr<std::vector<T>> &ptr) { _arrayType=makeType<T>(); _elementSize=sizeof(T); _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<T>>(ptr); }
         template<typename T>
         inline void set(const std::shared_ptr<std::vector<T>> &ptr,unsigned short numComponents) { _arrayType=makeType<T>(numComponents); _elementSize=sizeof(T)*numComponents/getNumComponentsOfType<T>(); _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<T>>(ptr); }
         template<typename T>
         inline void set(const std::shared_ptr<std::vector<T>> &ptr,unsigned short numComponents,GLType glType) { set(ptr,numComponents,unsigned(glType)); }
         template<typename T>
         inline void set(const std::shared_ptr<std::vector<T>> &ptr,unsigned short numComponents,unsigned glType) { _arrayType=makeType(glType,numComponents); _elementSize=sizeof(T)*numComponents/getNumComponentsOfType<T>(); _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<T>>(ptr); }
         template<typename T>
         inline void set(const std::shared_ptr<std::vector<T>> &ptr,unsigned short numComponents,GLType glType,unsigned sizeOfElement) { set(ptr,numComponents,unsigned(glType),sizeOfElement); }
         template<typename T>
         inline void set(const std::shared_ptr<std::vector<T>> &ptr,unsigned short numComponents,unsigned glType,unsigned sizeOfElement) { _arrayType=makeType(glType,numComponents); _elementSize=sizeOfElement; _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<T>>(ptr); }

         template<typename T>
         inline ArrayAdapter& operator=(const std::shared_ptr<std::vector<T>> &ptr)  { set(ptr); return *this; }

         template<typename T>
         inline std::shared_ptr<std::vector<T>> get() { return static_cast<ArrayDecoratorTemplate<T>*>(_arrayDecorator.get())->get(); }
         template<typename T>
         inline const std::shared_ptr<std::vector<T>>& get() const { return static_cast<ArrayDecoratorTemplate<T>*>(_arrayDecorator)->get(); }

         template<typename T>
         inline std::shared_ptr<ArrayDecoratorTemplate<T>> getArrayDecorator() { return std::static_pointer_cast<ArrayDecoratorTemplate<T>>(_arrayDecorator); }
         template<typename T>
         inline const std::shared_ptr<ArrayDecoratorTemplate<T>>& getArrayDecorator() const { return std::static_pointer_cast<ArrayDecoratorTemplate<T>>(_arrayDecorator); }
      };

      template<> inline ArrayAdapter::GLType ArrayAdapter::makeGLType<char>()  { return ArrayAdapter::GLType::BYTE; }
      template<> inline ArrayAdapter::GLType ArrayAdapter::makeGLType<short>() { return ArrayAdapter::GLType::SHORT; }
      template<> inline ArrayAdapter::GLType ArrayAdapter::makeGLType<int>()   { return ArrayAdapter::GLType::INT; }
      template<> inline ArrayAdapter::GLType ArrayAdapter::makeGLType<unsigned char>()  { return ArrayAdapter::GLType::UNSIGNED_BYTE; }
      template<> inline ArrayAdapter::GLType ArrayAdapter::makeGLType<unsigned short>() { return ArrayAdapter::GLType::UNSIGNED_SHORT; }
      template<> inline ArrayAdapter::GLType ArrayAdapter::makeGLType<unsigned>()       { return ArrayAdapter::GLType::UNSIGNED_INT; }
      template<> inline ArrayAdapter::GLType ArrayAdapter::makeGLType<float>()  { return ArrayAdapter::GLType::FLOAT; }
      template<> inline ArrayAdapter::GLType ArrayAdapter::makeGLType<double>() { return ArrayAdapter::GLType::DOUBLE; }
      template<> inline ArrayAdapter::GLType ArrayAdapter::makeGLType<glm::vec2>() { return ArrayAdapter::GLType::FLOAT; }
      template<> inline ArrayAdapter::GLType ArrayAdapter::makeGLType<glm::vec3>() { return ArrayAdapter::GLType::FLOAT; }
      template<> inline ArrayAdapter::GLType ArrayAdapter::makeGLType<glm::vec4>() { return ArrayAdapter::GLType::FLOAT; }
      template<> inline ArrayAdapter::GLType ArrayAdapter::makeGLType<glm::dvec2>() { return ArrayAdapter::GLType::DOUBLE; }
      template<> inline ArrayAdapter::GLType ArrayAdapter::makeGLType<glm::dvec3>() { return ArrayAdapter::GLType::DOUBLE; }
      template<> inline ArrayAdapter::GLType ArrayAdapter::makeGLType<glm::dvec4>() { return ArrayAdapter::GLType::DOUBLE; }
      template<> inline ArrayAdapter::GLType ArrayAdapter::makeGLType<glm::ivec2>() { return ArrayAdapter::GLType::INT; }
      template<> inline ArrayAdapter::GLType ArrayAdapter::makeGLType<glm::ivec3>() { return ArrayAdapter::GLType::INT; }
      template<> inline ArrayAdapter::GLType ArrayAdapter::makeGLType<glm::ivec4>() { return ArrayAdapter::GLType::INT; }
      template<> inline ArrayAdapter::GLType ArrayAdapter::makeGLType<glm::uvec2>() { return ArrayAdapter::GLType::UNSIGNED_INT; }
      template<> inline ArrayAdapter::GLType ArrayAdapter::makeGLType<glm::uvec3>() { return ArrayAdapter::GLType::UNSIGNED_INT; }
      template<> inline ArrayAdapter::GLType ArrayAdapter::makeGLType<glm::uvec4>() { return ArrayAdapter::GLType::UNSIGNED_INT; }

      template<> inline unsigned short ArrayAdapter::getNumComponentsOfType<glm::vec2>()  { return 2; }
      template<> inline unsigned short ArrayAdapter::getNumComponentsOfType<glm::vec3>()  { return 3; }
      template<> inline unsigned short ArrayAdapter::getNumComponentsOfType<glm::vec4>()  { return 4; }
      template<> inline unsigned short ArrayAdapter::getNumComponentsOfType<glm::dvec2>()  { return 2; }
      template<> inline unsigned short ArrayAdapter::getNumComponentsOfType<glm::dvec3>()  { return 3; }
      template<> inline unsigned short ArrayAdapter::getNumComponentsOfType<glm::dvec4>()  { return 4; }
      template<> inline unsigned short ArrayAdapter::getNumComponentsOfType<glm::ivec2>()  { return 2; }
      template<> inline unsigned short ArrayAdapter::getNumComponentsOfType<glm::ivec3>()  { return 3; }
      template<> inline unsigned short ArrayAdapter::getNumComponentsOfType<glm::ivec4>()  { return 4; }
      template<> inline unsigned short ArrayAdapter::getNumComponentsOfType<glm::uvec2>()  { return 2; }
      template<> inline unsigned short ArrayAdapter::getNumComponentsOfType<glm::uvec3>()  { return 3; }
      template<> inline unsigned short ArrayAdapter::getNumComponentsOfType<glm::uvec4>()  { return 4; }

#if 0
      template<> inline unsigned ArrayAdapter::getSizeOfType<ArrayAdapter::GLType::BYTE>()           { return 1; }
      template<> inline unsigned ArrayAdapter::getSizeOfType<ArrayAdapter::GLType::UNSIGNED_BYTE>()  { return 1; }
      template<> inline unsigned ArrayAdapter::getSizeOfType<ArrayAdapter::GLType::SHORT>()          { return 2; }
      template<> inline unsigned ArrayAdapter::getSizeOfType<ArrayAdapter::GLType::UNSIGNED_SHORT>() { return 2; }
      template<> inline unsigned ArrayAdapter::getSizeOfType<ArrayAdapter::GLType::INT>()            { return 4; }
      template<> inline unsigned ArrayAdapter::getSizeOfType<ArrayAdapter::GLType::UNSIGNED_INT>()   { return 4; }
      template<> inline unsigned ArrayAdapter::getSizeOfType<ArrayAdapter::GLType::FLOAT>()          { return 4; }
      template<> inline unsigned ArrayAdapter::getSizeOfType<ArrayAdapter::GLType::DOUBLE>()         { return 8; }
      template<> inline unsigned ArrayAdapter::getSizeOfType<ArrayAdapter::GLType::HALF_FLOAT>()     { return 2; }
      template<> inline unsigned ArrayAdapter::getSizeOfType<ArrayAdapter::GLType::FIXED>()          { return 4; }
      template<> inline unsigned ArrayAdapter::getSizeOfType<ArrayAdapter::GLType::UNSIGNED_BYTE_3_3_2>()        { return 1; }
      template<> inline unsigned ArrayAdapter::getSizeOfType<ArrayAdapter::GLType::UNSIGNED_BYTE_2_3_3_REV>()    { return 1; }
      template<> inline unsigned ArrayAdapter::getSizeOfType<ArrayAdapter::GLType::UNSIGNED_SHORT_5_6_5>()       { return 2; }
      template<> inline unsigned ArrayAdapter::getSizeOfType<ArrayAdapter::GLType::UNSIGNED_SHORT_5_6_5_REV>()   { return 2; }
      template<> inline unsigned ArrayAdapter::getSizeOfType<ArrayAdapter::GLType::UNSIGNED_SHORT_4_4_4_4>()     { return 2; }
      template<> inline unsigned ArrayAdapter::getSizeOfType<ArrayAdapter::GLType::UNSIGNED_SHORT_4_4_4_4_REV>() { return 2; }
      template<> inline unsigned ArrayAdapter::getSizeOfType<ArrayAdapter::GLType::UNSIGNED_SHORT_5_5_5_1>()     { return 2; }
      template<> inline unsigned ArrayAdapter::getSizeOfType<ArrayAdapter::GLType::UNSIGNED_SHORT_1_5_5_5_REV>() { return 2; }
      template<> inline unsigned ArrayAdapter::getSizeOfType<ArrayAdapter::GLType::UNSIGNED_INT_8_8_8_8>()           { return 4; }
      template<> inline unsigned ArrayAdapter::getSizeOfType<ArrayAdapter::GLType::UNSIGNED_INT_8_8_8_8_REV>()       { return 4; }
      template<> inline unsigned ArrayAdapter::getSizeOfType<ArrayAdapter::GLType::UNSIGNED_INT_10_10_10_2>()        { return 4; }
      template<> inline unsigned ArrayAdapter::getSizeOfType<ArrayAdapter::GLType::UNSIGNED_INT_2_10_10_10_REV>()    { return 4; }
      template<> inline unsigned ArrayAdapter::getSizeOfType<ArrayAdapter::GLType::UNSIGNED_INT_24_8>()              { return 4; }
      template<> inline unsigned ArrayAdapter::getSizeOfType<ArrayAdapter::GLType::UNSIGNED_INT_10F_11F_11F_REV>()   { return 4; }
      template<> inline unsigned ArrayAdapter::getSizeOfType<ArrayAdapter::GLType::UNSIGNED_INT_5_9_9_9_REV>()       { return 4; }
      template<> inline unsigned ArrayAdapter::getSizeOfType<ArrayAdapter::GLType::FLOAT_32_UNSIGNED_INT_24_8_REV>() { return 8; }
      template<> inline unsigned ArrayAdapter::getSizeOfType<ArrayAdapter::GLType::MAT2>()   { return  4*4; }
      template<> inline unsigned ArrayAdapter::getSizeOfType<ArrayAdapter::GLType::MAT3>()   { return  9*4; }
      template<> inline unsigned ArrayAdapter::getSizeOfType<ArrayAdapter::GLType::MAT4>()   { return 16*4; }
      template<> inline unsigned ArrayAdapter::getSizeOfType<ArrayAdapter::GLType::MAT2X3>() { return  6*4; }
      template<> inline unsigned ArrayAdapter::getSizeOfType<ArrayAdapter::GLType::MAT2X4>() { return  8*4; }
      template<> inline unsigned ArrayAdapter::getSizeOfType<ArrayAdapter::GLType::MAT3X2>() { return  6*4; }
      template<> inline unsigned ArrayAdapter::getSizeOfType<ArrayAdapter::GLType::MAT3X4>() { return 12*4; }
      template<> inline unsigned ArrayAdapter::getSizeOfType<ArrayAdapter::GLType::MAT4X2>() { return  8*4; }
      template<> inline unsigned ArrayAdapter::getSizeOfType<ArrayAdapter::GLType::MAT4X3>() { return 12*4; }
      template<> inline unsigned ArrayAdapter::getSizeOfType<ArrayAdapter::GLType::DMAT2>()   { return  4*8; }
      template<> inline unsigned ArrayAdapter::getSizeOfType<ArrayAdapter::GLType::DMAT3>()   { return  9*8; }
      template<> inline unsigned ArrayAdapter::getSizeOfType<ArrayAdapter::GLType::DMAT4>()   { return 16*8; }
      template<> inline unsigned ArrayAdapter::getSizeOfType<ArrayAdapter::GLType::DMAT2X3>() { return  6*8; }
      template<> inline unsigned ArrayAdapter::getSizeOfType<ArrayAdapter::GLType::DMAT2X4>() { return  8*8; }
      template<> inline unsigned ArrayAdapter::getSizeOfType<ArrayAdapter::GLType::DMAT3X2>() { return  6*8; }
      template<> inline unsigned ArrayAdapter::getSizeOfType<ArrayAdapter::GLType::DMAT3X4>() { return 12*8; }
      template<> inline unsigned ArrayAdapter::getSizeOfType<ArrayAdapter::GLType::DMAT4X2>() { return  8*8; }
      template<> inline unsigned ArrayAdapter::getSizeOfType<ArrayAdapter::GLType::DMAT4X3>() { return 12*8; }
#endif
   }
}

#endif // GE_SG_ARRAY_H
