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

         virtual void accept(int index,ValueVisitor& visitor) { bool tmp=(*_array)[index]; visitor.apply(tmp); (*_array)[index] = tmp; }
         virtual void accept(ArrayVisitor& visitor) { visitor.apply(*_array); }
      };

      class ArrayAdapter
      {
      protected:

         virtual ~ArrayAdapter() {}

         enum class Type : unsigned char; // forward declaration

         Type    _arrayType;
         int     _elementSize;
         std::shared_ptr<ArrayDecorator> _arrayDecorator;

      public:

         enum class Type : unsigned char
         {
            Unknown = 0,

            Bool     = 1,

            Byte     = 2,
            Short    = 3,
            Int      = 4,

            UByte    = 5,
            UShort   = 6,
            UInt     = 7,

            Float    = 8,
            Double   = 9,

            Vec2     = 10,
            Vec3     = 11,
            Vec4     = 12,

            DVec2    = 13,
            DVec3    = 14,
            DVec4    = 15,

            BVec2    = 16,
            BVec3    = 17,
            BVec4    = 18,

            IVec2    = 19,
            IVec3    = 20,
            IVec4    = 21,

            UVec2    = 22,
            UVec3    = 23,
            UVec4    = 24,

            Mat2     = 25,
            Mat3     = 26,
            Mat4     = 27,

            Mat2x3   = 28,
            Mat2x4   = 29,
            Mat3x2   = 30,
            Mat3x4   = 31,
            Mat4x2   = 32,
            Mat4x3   = 33,

            DMat2    = 34,
            DMat3    = 35,
            DMat4    = 36,

            DMat2x3  = 37,
            DMat2x4  = 38,
            DMat3x2  = 39,
            DMat3x4  = 40,
            DMat4x2  = 41,
            DMat4x3  = 42,

            Struct   = 43,
         };

         ArrayAdapter() : _arrayType(Type::Unknown), _elementSize(0) {}
         ArrayAdapter(const ArrayAdapter& a) : _arrayType(a._arrayType), _elementSize(a._elementSize), _arrayDecorator(a._arrayDecorator) {}

         ArrayAdapter(const std::shared_ptr<std::vector<bool>> &ptr) : _arrayType(Type::Bool), _elementSize(sizeof(bool)), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<bool>>(ptr)) {}

         ArrayAdapter(const std::shared_ptr<std::vector<char>> &ptr) :  _arrayType(Type::Byte),  _elementSize(sizeof(char)),  _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<char>>(ptr)) {}
         ArrayAdapter(const std::shared_ptr<std::vector<short>> &ptr) : _arrayType(Type::Short), _elementSize(sizeof(short)), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<short>>(ptr)) {}
         ArrayAdapter(const std::shared_ptr<std::vector<int>> &ptr) :   _arrayType(Type::Int),   _elementSize(sizeof(int)),   _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<int>>(ptr)) {}

         ArrayAdapter(const std::shared_ptr<std::vector<unsigned char>> &ptr) :  _arrayType(Type::UByte),  _elementSize(sizeof(unsigned char)),  _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<unsigned char>>(ptr)) {}
         ArrayAdapter(const std::shared_ptr<std::vector<unsigned short>> &ptr) : _arrayType(Type::UShort), _elementSize(sizeof(unsigned short)), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<unsigned short>>(ptr)) {}
         ArrayAdapter(const std::shared_ptr<std::vector<unsigned>> &ptr) :       _arrayType(Type::UInt),   _elementSize(sizeof(unsigned)),       _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<unsigned>>(ptr)) {}

         ArrayAdapter(const std::shared_ptr<std::vector<float>> &ptr) :  _arrayType(Type::Float),  _elementSize(sizeof(float)),  _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<float>>(ptr)) {}
         ArrayAdapter(const std::shared_ptr<std::vector<double>> &ptr) : _arrayType(Type::Double), _elementSize(sizeof(double)), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<double>>(ptr)) {}

         ArrayAdapter(const std::shared_ptr<std::vector<glm::vec2>> &ptr) : _arrayType(Type::Vec2), _elementSize(sizeof(glm::vec2)), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<glm::vec2>>(ptr)) {}
         ArrayAdapter(const std::shared_ptr<std::vector<glm::vec3>> &ptr) : _arrayType(Type::Vec3), _elementSize(sizeof(glm::vec3)), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<glm::vec3>>(ptr)) {}
         ArrayAdapter(const std::shared_ptr<std::vector<glm::vec4>> &ptr) : _arrayType(Type::Vec4), _elementSize(sizeof(glm::vec4)), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<glm::vec4>>(ptr)) {}

         ArrayAdapter(const std::shared_ptr<std::vector<glm::dvec2>> &ptr) : _arrayType(Type::DVec2), _elementSize(sizeof(glm::dvec2)), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<glm::dvec2>>(ptr)) {}
         ArrayAdapter(const std::shared_ptr<std::vector<glm::dvec3>> &ptr) : _arrayType(Type::DVec3), _elementSize(sizeof(glm::dvec3)), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<glm::dvec3>>(ptr)) {}
         ArrayAdapter(const std::shared_ptr<std::vector<glm::dvec4>> &ptr) : _arrayType(Type::DVec4), _elementSize(sizeof(glm::dvec4)), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<glm::dvec4>>(ptr)) {}

         ArrayAdapter(const std::shared_ptr<std::vector<glm::bvec2>> &ptr) : _arrayType(Type::BVec2), _elementSize(sizeof(glm::bvec2)), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<glm::bvec2>>(ptr)) {}
         ArrayAdapter(const std::shared_ptr<std::vector<glm::bvec3>> &ptr) : _arrayType(Type::BVec3), _elementSize(sizeof(glm::bvec3)), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<glm::bvec3>>(ptr)) {}
         ArrayAdapter(const std::shared_ptr<std::vector<glm::bvec4>> &ptr) : _arrayType(Type::BVec4), _elementSize(sizeof(glm::bvec4)), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<glm::bvec4>>(ptr)) {}

         ArrayAdapter(const std::shared_ptr<std::vector<glm::ivec2>> &ptr) : _arrayType(Type::IVec2), _elementSize(sizeof(glm::ivec2)), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<glm::ivec2>>(ptr)) {}
         ArrayAdapter(const std::shared_ptr<std::vector<glm::ivec3>> &ptr) : _arrayType(Type::IVec3), _elementSize(sizeof(glm::ivec3)), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<glm::ivec3>>(ptr)) {}
         ArrayAdapter(const std::shared_ptr<std::vector<glm::ivec4>> &ptr) : _arrayType(Type::IVec4), _elementSize(sizeof(glm::ivec4)), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<glm::ivec4>>(ptr)) {}

         ArrayAdapter(const std::shared_ptr<std::vector<glm::uvec2>> &ptr) : _arrayType(Type::UVec2), _elementSize(sizeof(glm::uvec2)), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<glm::uvec2>>(ptr)) {}
         ArrayAdapter(const std::shared_ptr<std::vector<glm::uvec3>> &ptr) : _arrayType(Type::UVec3), _elementSize(sizeof(glm::uvec3)), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<glm::uvec3>>(ptr)) {}
         ArrayAdapter(const std::shared_ptr<std::vector<glm::uvec4>> &ptr) : _arrayType(Type::UVec4), _elementSize(sizeof(glm::uvec4)), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<glm::uvec4>>(ptr)) {}

         ArrayAdapter(const std::shared_ptr<std::vector<glm::mat2>> &ptr) : _arrayType(Type::Mat2), _elementSize(sizeof(glm::mat2)), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<glm::mat2>>(ptr)) {}
         ArrayAdapter(const std::shared_ptr<std::vector<glm::mat3>> &ptr) : _arrayType(Type::Mat3), _elementSize(sizeof(glm::mat3)), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<glm::mat3>>(ptr)) {}
         ArrayAdapter(const std::shared_ptr<std::vector<glm::mat4>> &ptr) : _arrayType(Type::Mat4), _elementSize(sizeof(glm::mat4)), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<glm::mat4>>(ptr)) {}

         ArrayAdapter(const std::shared_ptr<std::vector<glm::mat2x3>> &ptr) : _arrayType(Type::Mat2x3), _elementSize(sizeof(glm::mat2x3)), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<glm::mat2x3>>(ptr)) {}
         ArrayAdapter(const std::shared_ptr<std::vector<glm::mat2x4>> &ptr) : _arrayType(Type::Mat2x4), _elementSize(sizeof(glm::mat2x4)), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<glm::mat2x4>>(ptr)) {}
         ArrayAdapter(const std::shared_ptr<std::vector<glm::mat3x2>> &ptr) : _arrayType(Type::Mat3x2), _elementSize(sizeof(glm::mat3x2)), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<glm::mat3x2>>(ptr)) {}
         ArrayAdapter(const std::shared_ptr<std::vector<glm::mat3x4>> &ptr) : _arrayType(Type::Mat3x4), _elementSize(sizeof(glm::mat3x4)), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<glm::mat3x4>>(ptr)) {}
         ArrayAdapter(const std::shared_ptr<std::vector<glm::mat4x2>> &ptr) : _arrayType(Type::Mat4x2), _elementSize(sizeof(glm::mat4x2)), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<glm::mat4x2>>(ptr)) {}
         ArrayAdapter(const std::shared_ptr<std::vector<glm::mat4x3>> &ptr) : _arrayType(Type::Mat4x3), _elementSize(sizeof(glm::mat4x3)), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<glm::mat4x3>>(ptr)) {}

         ArrayAdapter(const std::shared_ptr<std::vector<glm::dmat2>> &ptr) : _arrayType(Type::DMat2), _elementSize(sizeof(glm::dmat2)), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<glm::dmat2>>(ptr)) {}
         ArrayAdapter(const std::shared_ptr<std::vector<glm::dmat3>> &ptr) : _arrayType(Type::DMat3), _elementSize(sizeof(glm::dmat3)), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<glm::dmat3>>(ptr)) {}
         ArrayAdapter(const std::shared_ptr<std::vector<glm::dmat4>> &ptr) : _arrayType(Type::DMat4), _elementSize(sizeof(glm::dmat4)), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<glm::dmat4>>(ptr)) {}

         ArrayAdapter(const std::shared_ptr<std::vector<glm::dmat2x3>> &ptr) : _arrayType(Type::DMat2x3), _elementSize(sizeof(glm::dmat2x3)), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<glm::dmat2x3>>(ptr)) {}
         ArrayAdapter(const std::shared_ptr<std::vector<glm::dmat2x4>> &ptr) : _arrayType(Type::DMat2x4), _elementSize(sizeof(glm::dmat2x4)), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<glm::dmat2x4>>(ptr)) {}
         ArrayAdapter(const std::shared_ptr<std::vector<glm::dmat3x2>> &ptr) : _arrayType(Type::DMat3x2), _elementSize(sizeof(glm::dmat3x2)), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<glm::dmat3x2>>(ptr)) {}
         ArrayAdapter(const std::shared_ptr<std::vector<glm::dmat3x4>> &ptr) : _arrayType(Type::DMat3x4), _elementSize(sizeof(glm::dmat3x4)), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<glm::dmat3x4>>(ptr)) {}
         ArrayAdapter(const std::shared_ptr<std::vector<glm::dmat4x2>> &ptr) : _arrayType(Type::DMat4x2), _elementSize(sizeof(glm::dmat4x2)), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<glm::dmat4x2>>(ptr)) {}
         ArrayAdapter(const std::shared_ptr<std::vector<glm::dmat4x3>> &ptr) : _arrayType(Type::DMat4x3), _elementSize(sizeof(glm::dmat4x3)), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<glm::dmat4x3>>(ptr)) {}

         template<typename StructType>
         ArrayAdapter(const std::shared_ptr<std::vector<StructType>> &ptr) : _arrayType(Type::Struct), _elementSize(sizeof(StructType)), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<StructType>>(ptr)) {}

         void clear() { _arrayType=Type::Unknown; _elementSize=0; _arrayDecorator.reset(); }

         inline void set(const std::nullptr_t ptr) { clear(); }

         void set(const std::shared_ptr<std::vector<bool>> &ptr) { _arrayType=Type::Bool; _elementSize=sizeof(bool); _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<bool>>(ptr); }

         void set(const std::shared_ptr<std::vector<char>> &ptr) {  _arrayType=Type::Byte;  _elementSize=sizeof(char);  _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<char>>(ptr); }
         void set(const std::shared_ptr<std::vector<short>> &ptr) { _arrayType=Type::Short; _elementSize=sizeof(short); _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<short>>(ptr); }
         void set(const std::shared_ptr<std::vector<int>> &ptr) {   _arrayType=Type::Int;   _elementSize=sizeof(int);   _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<int>>(ptr); }

         void set(const std::shared_ptr<std::vector<unsigned char>> &ptr) {  _arrayType=Type::UByte;  _elementSize=sizeof(unsigned char);  _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<unsigned char>>(ptr); }
         void set(const std::shared_ptr<std::vector<unsigned short>> &ptr) { _arrayType=Type::UShort; _elementSize=sizeof(unsigned short); _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<unsigned short>>(ptr); }
         void set(const std::shared_ptr<std::vector<unsigned>> &ptr) {       _arrayType=Type::UInt;   _elementSize=sizeof(unsigned);       _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<unsigned>>(ptr); }

         void set(const std::shared_ptr<std::vector<float>> &ptr) {  _arrayType=Type::Float;  _elementSize=sizeof(float);  _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<float>>(ptr); }
         void set(const std::shared_ptr<std::vector<double>> &ptr) { _arrayType=Type::Double; _elementSize=sizeof(double); _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<double>>(ptr); }

         void set(const std::shared_ptr<std::vector<glm::vec2>> &ptr) { _arrayType=Type::Vec2; _elementSize=sizeof(glm::vec2); _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<glm::vec2>>(ptr); }
         void set(const std::shared_ptr<std::vector<glm::vec3>> &ptr) { _arrayType=Type::Vec3; _elementSize=sizeof(glm::vec3); _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<glm::vec3>>(ptr); }
         void set(const std::shared_ptr<std::vector<glm::vec4>> &ptr) { _arrayType=Type::Vec4; _elementSize=sizeof(glm::vec4); _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<glm::vec4>>(ptr); }

         void set(const std::shared_ptr<std::vector<glm::dvec2>> &ptr) { _arrayType=Type::DVec2; _elementSize=sizeof(glm::dvec2); _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<glm::dvec2>>(ptr); }
         void set(const std::shared_ptr<std::vector<glm::dvec3>> &ptr) { _arrayType=Type::DVec3; _elementSize=sizeof(glm::dvec3); _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<glm::dvec3>>(ptr); }
         void set(const std::shared_ptr<std::vector<glm::dvec4>> &ptr) { _arrayType=Type::DVec4; _elementSize=sizeof(glm::dvec4); _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<glm::dvec4>>(ptr); }

         void set(const std::shared_ptr<std::vector<glm::bvec2>> &ptr) { _arrayType=Type::BVec2; _elementSize=sizeof(glm::bvec2); _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<glm::bvec2>>(ptr); }
         void set(const std::shared_ptr<std::vector<glm::bvec3>> &ptr) { _arrayType=Type::BVec3; _elementSize=sizeof(glm::bvec3); _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<glm::bvec3>>(ptr); }
         void set(const std::shared_ptr<std::vector<glm::bvec4>> &ptr) { _arrayType=Type::BVec4; _elementSize=sizeof(glm::bvec4); _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<glm::bvec4>>(ptr); }

         void set(const std::shared_ptr<std::vector<glm::ivec2>> &ptr) { _arrayType=Type::IVec2; _elementSize=sizeof(glm::ivec2); _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<glm::ivec2>>(ptr); }
         void set(const std::shared_ptr<std::vector<glm::ivec3>> &ptr) { _arrayType=Type::IVec3; _elementSize=sizeof(glm::ivec3); _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<glm::ivec3>>(ptr); }
         void set(const std::shared_ptr<std::vector<glm::ivec4>> &ptr) { _arrayType=Type::IVec4; _elementSize=sizeof(glm::ivec4); _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<glm::ivec4>>(ptr); }

         void set(const std::shared_ptr<std::vector<glm::uvec2>> &ptr) { _arrayType=Type::UVec2; _elementSize=sizeof(glm::uvec2); _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<glm::uvec2>>(ptr); }
         void set(const std::shared_ptr<std::vector<glm::uvec3>> &ptr) { _arrayType=Type::UVec3; _elementSize=sizeof(glm::uvec3); _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<glm::uvec3>>(ptr); }
         void set(const std::shared_ptr<std::vector<glm::uvec4>> &ptr) { _arrayType=Type::UVec4; _elementSize=sizeof(glm::uvec4); _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<glm::uvec4>>(ptr); }

         void set(const std::shared_ptr<std::vector<glm::mat2>> &ptr) { _arrayType=Type::Mat2; _elementSize=sizeof(glm::mat2); _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<glm::mat2>>(ptr); }
         void set(const std::shared_ptr<std::vector<glm::mat3>> &ptr) { _arrayType=Type::Mat3; _elementSize=sizeof(glm::mat3); _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<glm::mat3>>(ptr); }
         void set(const std::shared_ptr<std::vector<glm::mat4>> &ptr) { _arrayType=Type::Mat4; _elementSize=sizeof(glm::mat4); _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<glm::mat4>>(ptr); }

         void set(const std::shared_ptr<std::vector<glm::mat2x3>> &ptr) { _arrayType=Type::Mat2x3; _elementSize=sizeof(glm::mat2x3); _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<glm::mat2x3>>(ptr); }
         void set(const std::shared_ptr<std::vector<glm::mat2x4>> &ptr) { _arrayType=Type::Mat2x4; _elementSize=sizeof(glm::mat2x4); _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<glm::mat2x4>>(ptr); }
         void set(const std::shared_ptr<std::vector<glm::mat3x2>> &ptr) { _arrayType=Type::Mat3x2; _elementSize=sizeof(glm::mat3x2); _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<glm::mat3x2>>(ptr); }
         void set(const std::shared_ptr<std::vector<glm::mat3x4>> &ptr) { _arrayType=Type::Mat3x4; _elementSize=sizeof(glm::mat3x4); _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<glm::mat3x4>>(ptr); }
         void set(const std::shared_ptr<std::vector<glm::mat4x2>> &ptr) { _arrayType=Type::Mat4x2; _elementSize=sizeof(glm::mat4x2); _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<glm::mat4x2>>(ptr); }
         void set(const std::shared_ptr<std::vector<glm::mat4x3>> &ptr) { _arrayType=Type::Mat4x3; _elementSize=sizeof(glm::mat4x3); _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<glm::mat4x3>>(ptr); }

         void set(const std::shared_ptr<std::vector<glm::dmat2>> &ptr) { _arrayType=Type::DMat2; _elementSize=sizeof(glm::dmat2); _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<glm::dmat2>>(ptr); }
         void set(const std::shared_ptr<std::vector<glm::dmat3>> &ptr) { _arrayType=Type::DMat3; _elementSize=sizeof(glm::dmat3); _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<glm::dmat3>>(ptr); }
         void set(const std::shared_ptr<std::vector<glm::dmat4>> &ptr) { _arrayType=Type::DMat4; _elementSize=sizeof(glm::dmat4); _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<glm::dmat4>>(ptr); }

         void set(const std::shared_ptr<std::vector<glm::dmat2x3>> &ptr) { _arrayType=Type::DMat2x3; _elementSize=sizeof(glm::dmat2x3); _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<glm::dmat2x3>>(ptr); }
         void set(const std::shared_ptr<std::vector<glm::dmat2x4>> &ptr) { _arrayType=Type::DMat2x4; _elementSize=sizeof(glm::dmat2x4); _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<glm::dmat2x4>>(ptr); }
         void set(const std::shared_ptr<std::vector<glm::dmat3x2>> &ptr) { _arrayType=Type::DMat3x2; _elementSize=sizeof(glm::dmat3x2); _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<glm::dmat3x2>>(ptr); }
         void set(const std::shared_ptr<std::vector<glm::dmat3x4>> &ptr) { _arrayType=Type::DMat3x4; _elementSize=sizeof(glm::dmat3x4); _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<glm::dmat3x4>>(ptr); }
         void set(const std::shared_ptr<std::vector<glm::dmat4x2>> &ptr) { _arrayType=Type::DMat4x2; _elementSize=sizeof(glm::dmat4x2); _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<glm::dmat4x2>>(ptr); }
         void set(const std::shared_ptr<std::vector<glm::dmat4x3>> &ptr) { _arrayType=Type::DMat4x3; _elementSize=sizeof(glm::dmat4x3); _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<glm::dmat4x3>>(ptr); }

         template<typename StructType>
         void set(const std::shared_ptr<std::vector<StructType>> &ptr) { _arrayType=Type::Struct; _elementSize=sizeof(StructType); _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<StructType>>(ptr); }

         inline ArrayAdapter& operator=(const ArrayAdapter& aa) { _arrayType=aa._arrayType; _elementSize=aa._elementSize; _arrayDecorator=aa._arrayDecorator; return *this; }
         inline ArrayAdapter& operator=(const std::nullptr_t ptr) { clear(); return *this; }

         inline ArrayAdapter& operator=(const std::shared_ptr<std::vector<bool>> &ptr) { set(ptr); return *this; }

         inline ArrayAdapter& operator=(const std::shared_ptr<std::vector<char>> &ptr)  { set(ptr); return *this; }
         inline ArrayAdapter& operator=(const std::shared_ptr<std::vector<short>> &ptr) { set(ptr); return *this; }
         inline ArrayAdapter& operator=(const std::shared_ptr<std::vector<int>> &ptr)   { set(ptr); return *this; }

         inline ArrayAdapter& operator=(const std::shared_ptr<std::vector<unsigned char>> &ptr)  { set(ptr); return *this; }
         inline ArrayAdapter& operator=(const std::shared_ptr<std::vector<unsigned short>> &ptr) { set(ptr); return *this; }
         inline ArrayAdapter& operator=(const std::shared_ptr<std::vector<unsigned>> &ptr)       { set(ptr); return *this; }

         inline ArrayAdapter& operator=(const std::shared_ptr<std::vector<float>> &ptr)  { set(ptr); return *this; }
         inline ArrayAdapter& operator=(const std::shared_ptr<std::vector<double>> &ptr) { set(ptr); return *this; }

         inline ArrayAdapter& operator=(const std::shared_ptr<std::vector<glm::vec2>> &ptr) { set(ptr); return *this; }
         inline ArrayAdapter& operator=(const std::shared_ptr<std::vector<glm::vec3>> &ptr) { set(ptr); return *this; }
         inline ArrayAdapter& operator=(const std::shared_ptr<std::vector<glm::vec4>> &ptr) { set(ptr); return *this; }

         inline ArrayAdapter& operator=(const std::shared_ptr<std::vector<glm::dvec2>> &ptr) { set(ptr); return *this; }
         inline ArrayAdapter& operator=(const std::shared_ptr<std::vector<glm::dvec3>> &ptr) { set(ptr); return *this; }
         inline ArrayAdapter& operator=(const std::shared_ptr<std::vector<glm::dvec4>> &ptr) { set(ptr); return *this; }

         inline ArrayAdapter& operator=(const std::shared_ptr<std::vector<glm::bvec2>> &ptr) { set(ptr); return *this; }
         inline ArrayAdapter& operator=(const std::shared_ptr<std::vector<glm::bvec3>> &ptr) { set(ptr); return *this; }
         inline ArrayAdapter& operator=(const std::shared_ptr<std::vector<glm::bvec4>> &ptr) { set(ptr); return *this; }

         inline ArrayAdapter& operator=(const std::shared_ptr<std::vector<glm::ivec2>> &ptr) { set(ptr); return *this; }
         inline ArrayAdapter& operator=(const std::shared_ptr<std::vector<glm::ivec3>> &ptr) { set(ptr); return *this; }
         inline ArrayAdapter& operator=(const std::shared_ptr<std::vector<glm::ivec4>> &ptr) { set(ptr); return *this; }

         inline ArrayAdapter& operator=(const std::shared_ptr<std::vector<glm::uvec2>> &ptr) { set(ptr); return *this; }
         inline ArrayAdapter& operator=(const std::shared_ptr<std::vector<glm::uvec3>> &ptr) { set(ptr); return *this; }
         inline ArrayAdapter& operator=(const std::shared_ptr<std::vector<glm::uvec4>> &ptr) { set(ptr); return *this; }

         inline ArrayAdapter& operator=(const std::shared_ptr<std::vector<glm::mat2>> &ptr) { set(ptr); return *this; }
         inline ArrayAdapter& operator=(const std::shared_ptr<std::vector<glm::mat3>> &ptr) { set(ptr); return *this; }
         inline ArrayAdapter& operator=(const std::shared_ptr<std::vector<glm::mat4>> &ptr) { set(ptr); return *this; }

         inline ArrayAdapter& operator=(const std::shared_ptr<std::vector<glm::mat2x3>> &ptr) { set(ptr); return *this; }
         inline ArrayAdapter& operator=(const std::shared_ptr<std::vector<glm::mat2x4>> &ptr) { set(ptr); return *this; }
         inline ArrayAdapter& operator=(const std::shared_ptr<std::vector<glm::mat3x2>> &ptr) { set(ptr); return *this; }
         inline ArrayAdapter& operator=(const std::shared_ptr<std::vector<glm::mat3x4>> &ptr) { set(ptr); return *this; }
         inline ArrayAdapter& operator=(const std::shared_ptr<std::vector<glm::mat4x2>> &ptr) { set(ptr); return *this; }
         inline ArrayAdapter& operator=(const std::shared_ptr<std::vector<glm::mat4x3>> &ptr) { set(ptr); return *this; }

         inline ArrayAdapter& operator=(const std::shared_ptr<std::vector<glm::dmat2>> &ptr) { set(ptr); return *this; }
         inline ArrayAdapter& operator=(const std::shared_ptr<std::vector<glm::dmat3>> &ptr) { set(ptr); return *this; }
         inline ArrayAdapter& operator=(const std::shared_ptr<std::vector<glm::dmat4>> &ptr) { set(ptr); return *this; }

         inline ArrayAdapter& operator=(const std::shared_ptr<std::vector<glm::dmat2x3>> &ptr) { set(ptr); return *this; }
         inline ArrayAdapter& operator=(const std::shared_ptr<std::vector<glm::dmat2x4>> &ptr) { set(ptr); return *this; }
         inline ArrayAdapter& operator=(const std::shared_ptr<std::vector<glm::dmat3x2>> &ptr) { set(ptr); return *this; }
         inline ArrayAdapter& operator=(const std::shared_ptr<std::vector<glm::dmat3x4>> &ptr) { set(ptr); return *this; }
         inline ArrayAdapter& operator=(const std::shared_ptr<std::vector<glm::dmat4x2>> &ptr) { set(ptr); return *this; }
         inline ArrayAdapter& operator=(const std::shared_ptr<std::vector<glm::dmat4x3>> &ptr) { set(ptr); return *this; }

         template<typename StructType>
         inline ArrayAdapter& operator=(const std::shared_ptr<std::vector<StructType>> &ptr) { set(ptr); return *this; }
      };
   }
}

#endif // GE_SG_ARRAY_H
