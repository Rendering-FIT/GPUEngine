#ifndef GE_RG_MATRIX_LIST_H
#define GE_RG_MATRIX_LIST_H

#include <memory>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <geRG/Export.h>
#include <geRG/MatrixGpuData.h>

namespace ge
{
   namespace rg
   {

      /** ListControlGpuData is used to access control data of a list.
       *  The structure is usually stored in GPU memory.
       *  ListControlGpuData is used, for example, by MatrixList.
       */
      struct ListControlGpuData {
         unsigned startIndex;  ///< Index into the buffer pointing to the first item. To get the offset, multiply it by the size of item.
         unsigned numItems;    ///< Number of items in the list.
      };


      /** MatrixList class represents a group of transformation matrices.
       *  The matrices are stored inside GPU buffer and used for instanced rendering.
       *
       *  MatrixList is usually attached to one or more Transformations in transformation graph.
       *  The transformation graph is traversed before rendering matrices are computed and
       *  each Transformation with attached MatrixList will append computed transformation
       *  to the MatrixList. The computed matrix is equal to multiplication of all transformations
       *  from the root to the current transformation node. Each matrix that is appended to
       *  the MatrixList "instantiate" Drawables that are referencing the MatrixList.
       */
      class GERG_EXPORT MatrixList : public std::enable_shared_from_this<MatrixList> {
      protected:

         unsigned _referenceCounter;  ///< Number of references. As long as the counter is non-zero, MatrixList is prevented from being destroyed. \sa _self
         unsigned _listControlId;     ///< Index into the buffer containing ListControlGpuData.
         unsigned _numMatrices;       ///< Number of matrices. The value is kept in synchrony with ListControlGpuData::numItems. Its value can range from 0 to _capacity.
         bool     _restartFlag;       ///< Internal flip-flop flag used, for example, when evaluating number of matrices in the Transformation graph by RenderingContext::evaluateTransformationGraph() method.
         unsigned _startIndex;
         //unsigned _arrayId;           ///< Allocation id of matrix array. The matrices are usually stored in RenderingContext::matrixStorage().
         //unsigned _capacity;          ///< Current capacity of MatrixList. Maximum number of matrices that can be stored in the MatrixList until it is reallocated.
         std::shared_ptr<MatrixList> _self;  ///< Reference to itself. It is used by _referenceCounter to prevent the object from deleting whenever there are references.
                                             ///< Reference counter approach is used instead of standard shared_ptr external references to
                                             ///< conserve memory and atomic memory access penalty as MatrixLists are heavily referenced by other geRG classes such as Drawables.

      public:

         inline void downloadMatrixData(float     *matrix,unsigned index,unsigned numMatrices);
         inline void uploadMatrixData(const float *matrix,unsigned index,unsigned numMatrices);
         static void downloadMatrixDataFromOffset(float   *matrix,unsigned offset64,unsigned numMatrices);
         static void uploadMatrixDataToOffset(const float *matrix,unsigned offset64,unsigned numMatrices);
         void downloadListControlData(unsigned &matrixOffset64,unsigned &numMatrices);
         void uploadListControlData(unsigned matrixOffset64,unsigned numMatrices);
         void uploadListControlData();

         inline unsigned listControlId() const;       ///< Returns index of list allocation data (MatrixAllocationGpuData). The allocation data are usually stored in RenderingContext::matrixAllocationStorage().
         inline unsigned listControlOffset4() const;  ///< Returns offset (multiplied by 4) of list allocation data (MatrixAllocationGpuData). The allocation data are usually stored in RenderingContext::matrixListAllocationStorage().

         inline unsigned startIndex() const;         ///< Returns index to the beginning of the matrix list (array of matrices) that are stored in RenderingContext::matrixListStorage().
         inline void setStartIndex(unsigned value);

         inline unsigned numMatrices() const;
         inline void setNumMatrices(unsigned num);

         inline bool restartFlag() const;
         inline void setRestartFlag(bool on);

         //inline unsigned capacity() const;
         //inline void setCapacity(unsigned num);

         inline void incrementReferenceCounter();
         inline void decrementReferenceCounter();
         inline unsigned referenceCounter() const;

         static inline std::shared_ptr<MatrixList> create();  ///< Factory method, returning new MatrixList object.
         static inline const std::shared_ptr<MatrixList>& createEmpty();  ///< Factory method, returning empty MatrixList object. The returned object is singleton for the given ge::rg::GraphicsContext.
         MatrixList();
         MatrixList(unsigned listControlId,unsigned startIndex,unsigned numMatrices);
         ~MatrixList();

      };

   }
}


#include <geRG/RenderingContext.h>

namespace ge
{
   namespace rg
   {

      inline void MatrixList::downloadMatrixData(float *matrix,unsigned index,unsigned numMatrices)
      { downloadMatrixDataFromOffset(matrix,_startIndex+index,numMatrices); }
      inline void MatrixList::uploadMatrixData(const float *matrix,unsigned index,unsigned numMatrices)
      { uploadMatrixDataToOffset(matrix,_startIndex+index,numMatrices); }

      inline unsigned MatrixList::listControlId() const  { return _listControlId; }
      inline unsigned MatrixList::listControlOffset4() const  { return _listControlId*2; }
      inline unsigned MatrixList::startIndex() const  { return _startIndex; }
      inline void MatrixList::setStartIndex(unsigned value)  { _startIndex=value; }
      inline unsigned MatrixList::numMatrices() const  { return _numMatrices; }
      inline void MatrixList::setNumMatrices(unsigned num)  { _numMatrices=num; }
      inline bool MatrixList::restartFlag() const  { return _restartFlag; }
      inline void MatrixList::setRestartFlag(bool on)  { _restartFlag=on; }
      //inline unsigned MatrixList::capacity() const  { return _capacity; }
      //inline void MatrixList::setCapacity(unsigned num)  { _capacity=num; }
      inline std::shared_ptr<MatrixList> MatrixList::create()  { return std::make_shared<MatrixList>(); }
      inline const std::shared_ptr<MatrixList>& createEmpty()  { return RenderingContext::current()->emptyMatrixList(); }
      inline void MatrixList::incrementReferenceCounter()  { if(++_referenceCounter==1) _self=shared_from_this(); }
      inline void MatrixList::decrementReferenceCounter()  { if(--_referenceCounter==0) _self.reset(); }
      inline unsigned MatrixList::referenceCounter() const  { return _referenceCounter; }

   }
}

#endif // GE_RG_MATRIX_LIST_H
