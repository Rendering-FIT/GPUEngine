#include <GPUEngine/geCore/Object.h>

ge::core::Object::Object( const Object& obj,const CopyOp& /*copyop*//*=CopyOp::SHALLOW_COPY*/ )
   : _name(obj._name)
{

}
