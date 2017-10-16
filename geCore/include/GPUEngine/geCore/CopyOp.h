#ifndef GE_COPYOP
#define GE_COPYOP

#include <GPUEngine/geCore/gecore_export.h>

namespace ge
{
   namespace core
   {

class Object;

class GECORE_EXPORT CopyOp
{
public:
   enum Options
   {
      SHALLOW_COPY                = 0,
      DEEP_COPY_OBJECTS           = 1<<0,
      DEEP_COPY                   = 0x7FFFFFFF
   };

   inline CopyOp(unsigned flags=SHALLOW_COPY):_flags(flags) {}
   virtual ~CopyOp(){}

   virtual Object* operator() (const Object* obj) const;

   unsigned getFlags() const { return _flags; }
   void setFlags(unsigned flags) { _flags = flags; }

protected:
   unsigned _flags;
};

   }
}

#endif //GE_COPYOP
