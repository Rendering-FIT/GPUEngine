#include <string.h>
#include <geRG/Transformation.h>

using namespace ge::rg;

// offsetof workaround for MSVC (problem seen on MSVC 2015 Update 1),
// offsetof should return std::size_t while on MSVC it returns size_t,
// aliasing with our ge::rg::size_t, leading to compilation error
#if defined(_MSC_VER) && _MSC_VER<2000
# if defined(offsetof)
# undef offsetof
# endif
#define offsetof(type,member) ((std::size_t) &(((type*)0)->member))
#endif


class Tmp_Transformation : public Transformation {
   static void dummy() {
      static_assert(offsetof(Transformation::SharedDataOffset,_gpuDataOffset64)==0,"_gpuDataOffset64 must be on offset 0 inside SharedDataOffset structure.");
      static_assert(offsetof(Transformation::SharedDataOffset,_refCounter)==sizeof(unsigned),"_refCounter must be on offset 4 inside SharedDataOffset structure.");
      static_assert(sizeof(float[16])==sizeof(glm::mat4),"glm::mat4 memory placement is not equal to float[16].");
   }
};


void Transformation::uploadMatrix(const float *matrix)
{
   float* buffer=RenderingContext::current()->cpuTransformationBuffer();
   memcpy(&buffer[gpuDataOffset64()*16],matrix,16*sizeof(float));
}


void Transformation::downloadMatrix(float *matrix)
{
   float* buffer=RenderingContext::current()->cpuTransformationBuffer();
   memcpy(matrix,&buffer[gpuDataOffset64()*16],16*sizeof(float));
}


float* Transformation::getMatrixPtr()
{
   float* buffer=RenderingContext::current()->cpuTransformationBuffer();
   return &buffer[gpuDataOffset64()*16];
}


Transformation::Transformation()
   : _gpuDataOffsetPtr(&_gpuDataOffset64)
   , _gpuDataOffset64(0)
{
   allocTransformationGpuData();
}


Transformation::Transformation(const Transformation &t,unsigned constructionFlags)
   : enable_shared_from_this<Transformation>()
   , _gpuDataOffsetPtr(&_gpuDataOffset64)
   , _gpuDataOffset64(0)
{
   if((constructionFlags&SHARE_MATRIX)!=0)
      shareTransformationFrom(t);
   if((constructionFlags&SHARE_MATRIX_LIST)!=0)
      _matrixList=t._matrixList;
   if((constructionFlags&COPY_CHILDREN)!=0)
      assignChildList(t.childList());
}


Transformation::~Transformation()
{
   RenderingContext::current()->transformationAllocationManager().free(_gpuDataOffsetPtr[0]);
   if(_gpuDataOffsetPtr!=&_gpuDataOffset64) {
      if(--_gpuDataOffsetPtr[1]==0)
         delete reinterpret_cast<SharedDataOffset*>(_gpuDataOffsetPtr);
   }
   removeAllChildren();
}


void Transformation::allocTransformationGpuData()
{
   // test gpu data existence
   if(gpuDataOffset64()!=0)
   {
      // if using local _gpuDataOffset64 (not sharing), return
      if(_gpuDataOffsetPtr==&_gpuDataOffset64)
         return;

      // remove shared data reference
      if(--_gpuDataOffsetPtr[1]==0)
      {
         // destroy SharedDataOffset
         RenderingContext::current()->transformationAllocationManager().free(_gpuDataOffsetPtr[0]);
         delete reinterpret_cast<SharedDataOffset*>(_gpuDataOffsetPtr);
         _gpuDataOffsetPtr=&_gpuDataOffset64;
      }
   }

   // alloc gpu data
   RenderingContext::current()->transformationAllocationManager().alloc(&_gpuDataOffset64);
}


void Transformation::shareTransformationFrom(const Transformation &t)
{
   // test gpu data existence
   if(gpuDataOffset64()!=0)
   {
      // if already sharing with t, return
      if(_gpuDataOffsetPtr==t._gpuDataOffsetPtr)
         return;

      if(_gpuDataOffsetPtr==&_gpuDataOffset64)
         // free local gpu data
         RenderingContext::current()->transformationAllocationManager().free(_gpuDataOffset64);
      else
      {
         // remove shared data reference
         if(--_gpuDataOffsetPtr[1]==0)
         {
            RenderingContext::current()->transformationAllocationManager().free(_gpuDataOffsetPtr[0]);

            // test if t is using its local _gpuDataOffset64 (not sharing)
            if(t._gpuDataOffsetPtr==&t._gpuDataOffset64)
            {
               // reuse SharedDataOffset struct
               _gpuDataOffsetPtr[0]=t._gpuDataOffset64;
               _gpuDataOffsetPtr[1]=2;
               const_cast<Transformation&>(t)._gpuDataOffsetPtr=_gpuDataOffsetPtr;
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

   if(t._gpuDataOffsetPtr==&t._gpuDataOffset64)
   {
      // alloc new SharedDataOffset
      // and connect t and ourselves to it
      const_cast<Transformation&>(t)._gpuDataOffsetPtr=reinterpret_cast<unsigned*>(new SharedDataOffset);
      t._gpuDataOffsetPtr[0]=t._gpuDataOffset64;
      t._gpuDataOffsetPtr[1]=2;
      _gpuDataOffsetPtr=t._gpuDataOffsetPtr;
   }
   else
   {
      // connect ourselves to SharedDataOffset of t
      _gpuDataOffsetPtr=t._gpuDataOffsetPtr;
      _gpuDataOffsetPtr[1]++;
   }
}
