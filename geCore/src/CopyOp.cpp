#include <GPUEngine/geCore/Object.h>

using namespace ge::core;

#define COPY_OP( TYPE, FLAG ) \
   TYPE* CopyOp::operator() (const TYPE* obj) const \
{ \
   if (obj && _flags&FLAG) \
   return ge::core::clone(obj, *this); \
    else \
    return const_cast<TYPE*>(obj); \
}

COPY_OP(Object, DEEP_COPY_OBJECTS)
