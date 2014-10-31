#ifndef GE_SG_ARRAY_H
#define GE_SG_ARRAY_H

#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include <geSG/AttribType.h>

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

         AttribType  _attribType;
         std::shared_ptr<ArrayDecorator> _arrayDecorator;

      public:

         ArrayAdapter() : _attribType(AttribType::create<GLType::INVALID>()) {}
         ArrayAdapter(const ArrayAdapter& a) : _attribType(a._attribType), _arrayDecorator(a._arrayDecorator) {}
         ArrayAdapter& operator=(const ArrayAdapter &a)  { _attribType=a._attribType; _arrayDecorator=a._arrayDecorator; return *this; }

         template<typename T>
         inline ArrayAdapter(const std::shared_ptr<std::vector<T>> &ptr) : _attribType(AttribType::create<T>()), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<T>>(ptr)) {}
         template<typename T>
         inline ArrayAdapter(const std::shared_ptr<std::vector<T>> &ptr,unsigned short numComponents) : _attribType(AttribType::create<T>(numComponents)), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<T>>(ptr)) {}
         template<typename T>
         inline ArrayAdapter(const std::shared_ptr<std::vector<T>> &ptr,AttribType t) : _attribType(t), _arrayDecorator(std::make_shared<ArrayDecoratorTemplate<T>>(ptr)) {}

         inline ArrayAdapter(const std::shared_ptr<ArrayDecorator> &arrayDecorator,AttribType attribType) : _attribType(attribType), _arrayDecorator(arrayDecorator) {}

         virtual ~ArrayAdapter() {}

         inline void setType(AttribType t) { _attribType=t; }

         inline AttribType getType() const { return _attribType; }
         inline GLType getGLType() const { return _attribType.getGLType(); }
         inline unsigned short getNumComponents() const { return _attribType.getNumComponents(); }
         inline unsigned getSizeOfElement() const { return _attribType.getElementSize(); }

         void clear() { _attribType.invalidate(); _arrayDecorator.reset(); }

         inline void set(const std::nullptr_t ptr) { clear(); }

         template<typename T>
         inline void set(const std::shared_ptr<std::vector<T>> &ptr) { _attribType=AttribType::create<T>(); _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<T>>(ptr); }
         template<typename T>
         inline void set(const std::shared_ptr<std::vector<T>> &ptr,unsigned short numComponents) { _attribType=AttribType::create<T>(numComponents); _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<T>>(ptr); }
         template<typename T>
         inline void set(const std::shared_ptr<std::vector<T>> &ptr,AttribType attribType) { _attribType=attribType; _arrayDecorator=std::make_shared<ArrayDecoratorTemplate<T>>(ptr); }

         inline void set(const std::shared_ptr<ArrayDecorator> &arrayDecorator,AttribType attribType) { _attribType=attribType; _arrayDecorator=arrayDecorator; }

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

         inline void setArrayDecorator(const std::shared_ptr<ArrayDecorator>& decorator) { _arrayDecorator = decorator; }

      };

   }
}

#endif // GE_SG_ARRAY_H
