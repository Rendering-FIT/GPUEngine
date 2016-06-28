#include <string.h>
#include <geRG/MatrixList.h>
#include <geRG/RenderingContext.h>

using namespace ge::rg;



void MatrixList::downloadMatrixDataFromOffset(float *matrix,unsigned offset64,unsigned numMatrices)
{
   RenderingContext *rc=RenderingContext::current().get();
   MatrixGpuData *buffer=rc->matrixStorage()->map(BufferStorageAccess::READ);
   memcpy(matrix,buffer+offset64,numMatrices*sizeof(MatrixGpuData));
}


void MatrixList::uploadMatrixDataToOffset(const float *matrix,unsigned offset64,unsigned numMatrices)
{
   RenderingContext *rc=RenderingContext::current().get();
   MatrixGpuData *buffer=rc->matrixStorage()->map(BufferStorageAccess::WRITE);
   memcpy(buffer+offset64,matrix,numMatrices*sizeof(MatrixGpuData));
}


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


void MatrixList::uploadListControlData()
{
   uploadListControlData(_startIndex,_numMatrices);
}


MatrixList::MatrixList()
   : _referenceCounter(0)
   , _numMatrices(0)
   , _restartFlag(true)
   , _startIndex(0)
   //, _arrayId(0)
   //, _capacity(0)
{
   RenderingContext *rc=RenderingContext::current().get();
   auto m=rc->matrixListControlStorage();
   m->alloc(&_listControlId);
}


MatrixList::MatrixList(unsigned listControlId,unsigned startIndex,unsigned numMatrices)
   : _referenceCounter(0)
   , _listControlId(listControlId)
   , _numMatrices(numMatrices)
   , _restartFlag(true)
   //, _arrayId(matrixArrayId)
   , _startIndex(startIndex)
{
   //RenderingContext *rc=RenderingContext::current().get();
   //auto &a=rc->matrixStorage()->operator[](_arrayId);
   //_capacity=a.numItems;
}


MatrixList::~MatrixList()
{
   RenderingContext *rc=RenderingContext::current().get();
   //rc->matrixStorage()->free(_arrayId);
   rc->matrixListControlStorage()->free(_listControlId);
}
