#ifndef GE_OBJECT
#define GE_OBJECT

#include <string>
#include <memory>

#include <GPUEngine/geCore/CopyOp.h>

namespace ge
{
   namespace core
   {

#define META_GE_Object(type) \
   virtual ge::core::Object* cloneType() const {return new type ();} \
   virtual ge::core::Object* clone(const ge::core::CopyOp& copyOp) const { return new type (*this, copyOp); }

class GECORE_EXPORT Object
{
public:
   Object(){}
   Object(const Object&,const CopyOp& copyop=CopyOp::SHALLOW_COPY);
   virtual ~Object(){}

   virtual Object* cloneType() const = 0;
   virtual Object* clone(const CopyOp&) const = 0;

   std::string getName() const { return _name; }
   void setName(const std::string& name) { _name = name; }

protected:
   std::string _name;
};

template<typename T>
T* clone(const T* t, const ge::core::CopyOp& copyop=ge::core::CopyOp::SHALLOW_COPY)
{
   if (t)
   {
      std::unique_ptr<ge::core::Object> obj(t->clone(copyop));

      T* ptr = dynamic_cast<T*>(obj.get());
      if (ptr)
      {
         obj.release();
         return ptr;
      }
      else
      {
         //cerr<<"Warning: osg::clone(const T*, osg::CopyOp&) cloned object not of type T, returning NULL."<<std::endl;
         return 0;
      }
   }
   else
   {
      //cerr<<"Warning: osg::clone(const T*, osg::CopyOp&) passed null object to clone, returning NULL."<<std::endl;
      return 0;
   }
}

template<typename T>
T* cloneType(const T* t)
{
   if (t)
   {
      std::unique_ptr<ge::core::Object> obj = t->cloneType();

      T* ptr = dynamic_cast<T*>(obj.get());
      if (ptr)
      {
         obj.release();
         return ptr;
      }
      else
      {
         //cerr<<"Warning: osg::cloneType(const T*) cloned object not of type T, returning NULL."<<std::endl;
         return 0;
      }
   }
   else
   {
      //cerr<<"Warning: osg::cloneType(const T*) passed null object to clone, returning NULL."<<std::endl;
      return 0;
   }
}

   }
}

#endif //GE_OBJECT
