#include <string.h>
#include <geRG/MatrixList.h>
#include <geRG/RenderingContext.h>

using namespace ge::rg;



void MatrixList::downloadListControlData(unsigned &matrixOffset64,unsigned &numMatrices)
{
   RenderingContext *rc=RenderingContext::current().get();
   const ListControlGpuData *buffer=
      rc->matrixListControlStorage()->map(BufferStorageAccess::READ);
   const ListControlGpuData &data=buffer[_listControlId];
   matrixOffset64=data.startIndex;
   numMatrices=data.numItems;
}


void MatrixList::uploadListControlData(unsigned matrixOffset64,unsigned numMatrices)
{
   RenderingContext *rc=RenderingContext::current().get();
   ListControlGpuData *buffer=
      rc->matrixListControlStorage()->map(BufferStorageAccess::WRITE);
   ListControlGpuData &data=buffer[_listControlId];
   data.startIndex=matrixOffset64;
   data.numItems=numMatrices;
}


void MatrixList::downloadFromOffset(float *matrix,unsigned offset64,unsigned numMatrices)
{
   RenderingContext *rc=RenderingContext::current().get();
   MatrixGpuData *buffer=rc->matrixStorage()->map(BufferStorageAccess::READ);
   memcpy(matrix,buffer+offset64,numMatrices*sizeof(MatrixGpuData));
}


void MatrixList::uploadToOffset(const float *matrix,unsigned offset64,unsigned numMatrices)
{
   RenderingContext *rc=RenderingContext::current().get();
   MatrixGpuData *buffer=rc->matrixStorage()->map(BufferStorageAccess::WRITE);
   memcpy(buffer+offset64,matrix,numMatrices*sizeof(MatrixGpuData));
}


void MatrixList::uploadListControlData()
{
   RenderingContext *rc=RenderingContext::current().get();
   auto ms=rc->matrixStorage();
   uploadListControlData(ms->operator[](_listControlId).startIndex,_numMatrices);
}


MatrixList::MatrixList()
   : _referenceCounter(0)
   , _numMatrices(0)
   , _restartFlag(true)
   , _arrayId(0)
   , _capacity(0)
{
   RenderingContext *rc=RenderingContext::current().get();
   auto m=rc->matrixListControlStorage();
   m->alloc(&_listControlId);
}


MatrixList::MatrixList(unsigned numMatrices)
   : _referenceCounter(0)
   , _numMatrices(0)
   , _restartFlag(true)
   , _arrayId(0)
   , _capacity(0)
{
   RenderingContext *rc=RenderingContext::current().get();
   auto m=rc->matrixListControlStorage();
   m->alloc(&_listControlId);
   setNumMatrices(numMatrices);
}


MatrixList::MatrixList(unsigned listControlId,unsigned matrixArrayId,unsigned numMatrices)
   : _referenceCounter(0)
   , _listControlId(listControlId)
   , _numMatrices(numMatrices)
   , _restartFlag(true)
   , _arrayId(matrixArrayId)
{
   RenderingContext *rc=RenderingContext::current().get();
   auto &a=rc->matrixStorage()->operator[](_arrayId);
   _capacity=a.numItems;
}


MatrixList::~MatrixList()
{
   RenderingContext *rc=RenderingContext::current().get();
   rc->matrixStorage()->free(_arrayId);
   rc->matrixListControlStorage()->free(_listControlId);
}


void MatrixList::setNumMatrices(unsigned num)
{
   if(num>_capacity)
      setCapacity(num);
   _numMatrices=num;
   uploadListControlData();
}


void MatrixList::setCapacity(unsigned num)
{
   if(_capacity==num)
      return;

   // get global variables
   RenderingContext *rc=RenderingContext::current().get();
   auto ms=rc->matrixStorage();

   if(_arrayId==0) {
      // alloc matrix array
      _arrayId=ms->alloc(num,*this);
      _capacity=num;
   } else
      if(num!=ms->operator[](_arrayId).numItems)
      {
         // free old and alloc new matrix array
         // (note: the content of all matrices is destroyed here,
         // do we need here an option to preserve the content?)
         ms->free(_arrayId);
         _arrayId=ms->alloc(num,*this);
         _capacity=num;
      }

   // update ListControlGpuData in GPU buffer
   uploadListControlData();
}



// MatrixList::matrixCollectionOffset64() const documentation
// note: brief description is with the method declaration
/** \fn MatrixList::matrixCollectionOffset64() const
 *
 *  The offset is multiplied by 64 to be usable as matrix index in the GLSL code.
 *
 *  The method returns valid value only after calling updateGpuData(unsigned numMatrices) method
 *  as it performs the memory allocation and reallocation on GPU memory. The offset might change
 *  after each call to updateGpuData(unsigned numMatrices).
 */
