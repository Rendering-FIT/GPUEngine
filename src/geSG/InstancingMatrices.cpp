#include <string.h>
#include <geSG/InstancingMatrices.h>
#include <geSG/RenderingContext.h>

using namespace ge::sg;



void InstancingMatrices::downloadCollectionData(unsigned &matrixCollectionOffset64,unsigned &numMatrices)
{
   RenderingContext *rc=RenderingContext::current().get();
   const InstancingMatricesControlGpuData *buffer=static_cast<InstancingMatricesControlGpuData*>(
      rc->mapInstancingMatricesControlBuffer(RenderingContext::MappedBufferAccess::READ));
   const InstancingMatricesControlGpuData &data=buffer[_controlDataAllocationIndex];
   matrixCollectionOffset64=data.matrixCollectionOffset64;
   numMatrices=data.numMatrices;
}


void InstancingMatrices::uploadCollectionData(unsigned matrixCollectionOffset64,unsigned numMatrices)
{
   RenderingContext *rc=RenderingContext::current().get();
   InstancingMatricesControlGpuData *buffer=static_cast<InstancingMatricesControlGpuData*>(
      rc->mapInstancingMatricesControlBuffer(RenderingContext::MappedBufferAccess::WRITE));
   InstancingMatricesControlGpuData &data=buffer[_controlDataAllocationIndex];
   data.matrixCollectionOffset64=matrixCollectionOffset64;
   data.numMatrices=numMatrices;
}


void InstancingMatrices::downloadMatricesFromOffset(float *matrix,unsigned matrixCollectionOffset64,unsigned numMatrices)
{
   RenderingContext *rc=RenderingContext::current().get();
   uint8_t *buffer=static_cast<uint8_t*>(rc->mapInstancingMatrixBuffer(RenderingContext::MappedBufferAccess::READ));
   memcpy(matrix,buffer+matrixCollectionOffset64*64,numMatrices*64);
}


void InstancingMatrices::uploadMatricesToOffset(const float *matrix,unsigned matrixCollectionOffset64,unsigned numMatrices)
{
   RenderingContext *rc=RenderingContext::current().get();
   uint8_t *buffer=static_cast<uint8_t*>(rc->mapInstancingMatrixBuffer(RenderingContext::MappedBufferAccess::WRITE));
   memcpy(buffer+matrixCollectionOffset64*64,matrix,numMatrices*64);
}


InstancingMatrices::InstancingMatrices()
   : _numInstanceRefs(0)
   , _matrixCounterResetFlag(true)
   , _matrixCollectionAllocationId(0)
   , _numMatricesAllocated(0)
{
   RenderingContext *rc=RenderingContext::current().get();
   auto &m=rc->instancingMatricesControlAllocationManager();
   m.alloc(&_controlDataAllocationIndex);
}


InstancingMatrices::InstancingMatrices(unsigned controlDataAllocationIndex,unsigned matrixCollectionAllocationId)
   : _numInstanceRefs(0)
   , _controlDataAllocationIndex(controlDataAllocationIndex)
   , _matrixCounterResetFlag(true)
   , _matrixCollectionAllocationId(matrixCollectionAllocationId)
{
   RenderingContext *rc=RenderingContext::current().get();
   auto &ima=rc->instancingMatrixAllocation(matrixCollectionAllocationId);
   _numMatricesAllocated=ima.numElements;
}


InstancingMatrices::~InstancingMatrices()
{
   RenderingContext *rc=RenderingContext::current().get();
   auto &m1=rc->instancingMatricesControlAllocationManager();
   auto &m2=rc->instancingMatrixAllocationManager();
   m1.free(_controlDataAllocationIndex);
   m2.free(_matrixCollectionAllocationId);
}


void InstancingMatrices::updateGpuControlData(unsigned numMatrices)
{
   // get global variables
   RenderingContext *rc=RenderingContext::current().get();
   auto &m=rc->instancingMatrixAllocationManager();

   if(_matrixCollectionAllocationId==0)
      // alloc matrix block
      _matrixCollectionAllocationId=m.alloc(numMatrices,*this);
   else
      if(numMatrices!=m[_matrixCollectionAllocationId].numElements)
      {
         // free old and alloc new matrix block
         // (do we need here an option to keep the matrix block content?)
         m.free(_matrixCollectionAllocationId);
         _matrixCollectionAllocationId=m.alloc(numMatrices,*this);
      }

   // upload numMatrices and startIndex to GPU buffer
   uploadCollectionData(m[_matrixCollectionAllocationId].startIndex,numMatrices);
}



// InstancingMatrices::matrixCollectionOffset64() const documentation
// note: brief description is with the method declaration
/** \fn InstancingMatrices::matrixCollectionOffset64() const
 *
 *  The offset is multiplied by 64 to be usable as matrix index in the GLSL code.
 *
 *  The method returns valid value only after calling updateGpuData(unsigned numMatrices) method
 *  as it performs the memory allocation and reallocation on GPU memory. The offset might change
 *  after each call to updateGpuData(unsigned numMatrices).
 */
