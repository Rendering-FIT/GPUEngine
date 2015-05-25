#include <string.h>
#include <geSG/Transformation.h>

using namespace ge::sg;


class Tmp_Transformation : public Transformation {
   static void dummy() {
      static_assert(offsetof(Transformation::SharedDataOffset,_gpuDataOffset64)==0,"_gpuDataOffset64 must be on offset 0 inside SharedDataOffset structure.");
      static_assert(offsetof(Transformation::SharedDataOffset,_refCounter)==sizeof(unsigned),"_refCounter must be on offset 4 inside SharedDataOffset structure.");
   }
};


void Transformation::uploadMatrix(const float *matrix)
{
   float* buffer=RenderingContext::current()->getCpuTransformationBuffer();
   memcpy(&buffer[gpuDataOffset64()*16],matrix,16*sizeof(float));
}


void Transformation::downloadMatrix(float *matrix)
{
   float* buffer=RenderingContext::current()->getCpuTransformationBuffer();
   memcpy(matrix,&buffer[gpuDataOffset64()*16],16*sizeof(float));
}


float* Transformation::getMatrixPtr()
{
   float* buffer=RenderingContext::current()->getCpuTransformationBuffer();
   return &buffer[gpuDataOffset64()*16];
}


void Transformation::allocTransformationGpuData()
{
   if(gpuDataOffset64()!=0)
   {
      // if already allocated, return
      if(_gpuDataOffsetPtr==&_gpuDataOffset64)
         return;

      // remove shared data reference
      _gpuDataOffsetPtr[1]--;
      if(_gpuDataOffsetPtr[1]==0)
      {
         RenderingContext::current()->transformationsAllocationManager().free(_gpuDataOffsetPtr[0]);
         delete reinterpret_cast<SharedDataOffset*>(_gpuDataOffsetPtr);
         _gpuDataOffsetPtr=&_gpuDataOffset64;
      }
   }

   // alloc gpu data
   RenderingContext::current()->transformationsAllocationManager().alloc(&_gpuDataOffset64);
}


void Transformation::shareTransformationFrom(const Transformation &t)
{
   if(gpuDataOffset64()!=0)
   {
      // if already allocated, return
      if(_gpuDataOffsetPtr==t._gpuDataOffsetPtr)
         return;

      if(_gpuDataOffsetPtr==&_gpuDataOffset64)
         // free gpu data
         RenderingContext::current()->transformationsAllocationManager().free(_gpuDataOffset64);
      else
      {
         // remove shared data reference
         _gpuDataOffsetPtr[1]--;
         if(_gpuDataOffsetPtr[1]==0)
         {
            RenderingContext::current()->transformationsAllocationManager().free(_gpuDataOffsetPtr[0]);
            if(t._gpuDataOffsetPtr==&t._gpuDataOffset64)
            {
               // reuse SharedDataOffset struct
               const_cast<Transformation&>(t)._gpuDataOffsetPtr=_gpuDataOffsetPtr;
               _gpuDataOffsetPtr[0]=_gpuDataOffset64;
               _gpuDataOffsetPtr[1]=2;
               return;
            }

            // delete SharedDataOffset struct
            delete reinterpret_cast<SharedDataOffset*>(_gpuDataOffsetPtr);
         }
      }

      if(t._gpuDataOffsetPtr==&t._gpuDataOffset64)
      {
         const_cast<Transformation&>(t)._gpuDataOffsetPtr=reinterpret_cast<unsigned*>(new SharedDataOffset);
         t._gpuDataOffsetPtr[0]=t._gpuDataOffset64;
         t._gpuDataOffsetPtr[1]=2;
         _gpuDataOffsetPtr=t._gpuDataOffsetPtr;
      }
      else
      {
         _gpuDataOffsetPtr=t._gpuDataOffsetPtr;
         _gpuDataOffsetPtr[1]++;
      }
   }

   // alloc gpu data
   RenderingContext::current()->transformationsAllocationManager().alloc(&_gpuDataOffset64);
}


void Transformation::cancelSharedTransformation()
{
   _gpuDataOffsetPtr[1]--;
   if(_gpuDataOffsetPtr[1]==0)
   {
      RenderingContext::current()->transformationsAllocationManager().free(_gpuDataOffsetPtr[0]);
      delete reinterpret_cast<SharedDataOffset*>(_gpuDataOffsetPtr);
   }
   _gpuDataOffsetPtr=&_gpuDataOffset64;
   _gpuDataOffset64=0;
}
