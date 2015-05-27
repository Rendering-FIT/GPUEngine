#include <string.h>
#include <geSG/InstancingMatrixCollection.h>
#include <geSG/RenderingContext.h>

using namespace ge::sg;



void InstancingMatrixCollection::downloadCollectionData(unsigned &matrixCollectionOffset64,unsigned &numMatrices)
{
   RenderingContext *rc=RenderingContext::current().get();
   const InstancingMatrixControlGpuData *buffer=static_cast<InstancingMatrixControlGpuData*>(
      rc->mapInstancingMatrixControlBuffer(RenderingContext::MappedBufferAccess::READ));
   const InstancingMatrixControlGpuData &data=buffer[_gpuDataAllocationIndex];
   matrixCollectionOffset64=data.matrixBaseOffset64;
   numMatrices=data.numMatrices;
}


void InstancingMatrixCollection::uploadCollectionData(unsigned matrixCollectionOffset64,unsigned numMatrices)
{
   RenderingContext *rc=RenderingContext::current().get();
   InstancingMatrixControlGpuData *buffer=static_cast<InstancingMatrixControlGpuData*>(
      rc->mapInstancingMatrixControlBuffer(RenderingContext::MappedBufferAccess::WRITE));
   InstancingMatrixControlGpuData &data=buffer[_gpuDataAllocationIndex];
   data.matrixBaseOffset64=matrixCollectionOffset64;
   data.numMatrices=numMatrices;
}


void InstancingMatrixCollection::downloadMatricesFromOffset(float *matrix,unsigned matrixCollectionOffset64,unsigned numMatrices)
{
   RenderingContext *rc=RenderingContext::current().get();
   uint8_t *buffer=static_cast<uint8_t*>(rc->mapInstancingMatrixBuffer(RenderingContext::MappedBufferAccess::READ));
   memcpy(matrix,buffer+matrixCollectionOffset64*64,numMatrices*64);
}


void InstancingMatrixCollection::uploadMatricesToOffset(const float *matrix,unsigned matrixCollectionOffset64,unsigned numMatrices)
{
   RenderingContext *rc=RenderingContext::current().get();
   uint8_t *buffer=static_cast<uint8_t*>(rc->mapInstancingMatrixBuffer(RenderingContext::MappedBufferAccess::WRITE));
   memcpy(buffer+matrixCollectionOffset64*64,matrix,numMatrices*64);
}


InstancingMatrixCollection::InstancingMatrixCollection()
   : _numInstanceRefs(0)
   , _matrixCounterResetFlag(true)
   , _gpuMatricesAllocationId(0)
   , _numMatricesAllocated(0)
{
   RenderingContext *rc=RenderingContext::current().get();
   auto &m=rc->instancingMatrixControlAllocationManager();
   m.alloc(&_gpuDataAllocationIndex);
}


InstancingMatrixCollection::InstancingMatrixCollection(unsigned gpuDataAllocationIndex,unsigned gpuMatricesAllocationId)
   : _numInstanceRefs(0)
   , _gpuDataAllocationIndex(gpuDataAllocationIndex)
   , _matrixCounterResetFlag(true)
   , _gpuMatricesAllocationId(gpuMatricesAllocationId)
{
   RenderingContext *rc=RenderingContext::current().get();
   auto &ima=rc->getInstancingMatrixAllocation(gpuMatricesAllocationId);
   _numMatricesAllocated=ima.numElements;
}


InstancingMatrixCollection::~InstancingMatrixCollection()
{
   RenderingContext *rc=RenderingContext::current().get();
   auto &m1=rc->instancingMatrixControlAllocationManager();
   auto &m2=rc->instancingMatrixAllocationManager();
   m1.free(_gpuDataAllocationIndex);
   m2.free(_gpuMatricesAllocationId);
}


void InstancingMatrixCollection::updateGpuCollectionData(unsigned numMatrices)
{
   // get global variables
   RenderingContext *rc=RenderingContext::current().get();
   auto &m=rc->instancingMatrixAllocationManager();

   if(_gpuMatricesAllocationId==0)
      // alloc matrix block
      _gpuMatricesAllocationId=m.alloc(numMatrices,*this);
   else
      if(numMatrices!=m[_gpuMatricesAllocationId].numElements)
      {
         // free old and alloc new matrix block
         // (do we need here an option to keep the matrix block content?)
         m.free(_gpuMatricesAllocationId);
         _gpuMatricesAllocationId=m.alloc(numMatrices,*this);
      }

   // upload numMatrices and startIndex to GPU buffer
   uploadCollectionData(m[_gpuMatricesAllocationId].startIndex,numMatrices);
}



// InstancingMatrixCollection::matrixCollectionOffset64() const documentation
// note: brief description is with the method declaration
/** \fn InstancingMatrixCollection::matrixCollectionOffset64() const
 *
 *  The offset is multiplied by 64 to be usable as matrix index in the GLSL code.
 *
 *  The method returns valid value only after calling updateGpuData(unsigned numMatrices) method
 *  as it performs the memory allocation and reallocation on GPU memory. The offset might change
 *  after each call to updateGpuData(unsigned numMatrices).
 */
