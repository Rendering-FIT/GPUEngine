#ifndef GE_SG_INSTANCING_MATRIX_COLLECTION_H
#define GE_SG_INSTANCING_MATRIX_COLLECTION_H

#include <memory>

namespace ge
{
   namespace sg
   {

      struct InstancingMatrixCollectionGpuData {
         unsigned matrixCollectionOffset64;
         unsigned numMatrices;
      };

      class InstancingMatrixCollection : public std::enable_shared_from_this<InstancingMatrixCollection> {
      protected:

         unsigned _numInstanceRefs;
         unsigned _gpuDataAllocationIndex;   ///< Matrix collection allocation index.
         unsigned _matrixCounter;
         bool     _matrixCounterResetFlag;
         unsigned _gpuMatricesAllocationId;  ///< GPU matrix block allocation id.
         unsigned _numMatricesAllocated;
         std::shared_ptr<InstancingMatrixCollection> _selfRef;

      public:

         void downloadCollectionData(unsigned &matrixCollectionOffset64,unsigned &numMatrices);
         void uploadCollectionData(unsigned matrixCollectionOffset64,unsigned numMatrices);
         static void downloadMatricesFromOffset(float *matrix,unsigned matrixCollectionOffset64,unsigned numMatrices);
         static void uploadMatricesToOffset(const float *matrix,unsigned matrixCollectionOffset64,unsigned numMatrices);
         inline void downloadMatrices(float *matrix,unsigned numMatrices,unsigned startIndex=0);
         inline void uploadMatrices(const float *matrix,unsigned numMatrices,unsigned startIndex=0);

         inline unsigned gpuDataAllocationIndex() const;
         inline unsigned gpuDataOffset4() const;
         inline unsigned matrixCollectionOffset64() const;  ///< Returns offset of the matrix block in InstancingMatrixBuffer.

         inline unsigned matrixCounter() const  { return _matrixCounter; }
         inline void setMatrixCounter(unsigned num)  { _matrixCounter=num; }

         inline bool matrixCounterResetFlag() const  { return _matrixCounterResetFlag; }
         inline void setMatrixCounterResetFlag(bool on)  { _matrixCounterResetFlag=on; }

         inline unsigned numMatricesAllocated() const  { return _numMatricesAllocated; }
         inline void setNumMatricesAllocated(unsigned num)  { _numMatricesAllocated=num; }

         void updateGpuCollectionData(unsigned numMatrices);

         inline void incrementInstanceRefCounter();
         inline void decrementInstanceRefCounter();

         static inline std::shared_ptr<InstancingMatrixCollection> create();
         static inline const std::shared_ptr<InstancingMatrixCollection>& identity();
         InstancingMatrixCollection();
         InstancingMatrixCollection(unsigned gpuDataAllocationIndex,unsigned gpuMatricesAllocationId);
         ~InstancingMatrixCollection();

      };

   }
}


#include <geSG/RenderingContext.h>

namespace ge
{
   namespace sg
   {
      inline void InstancingMatrixCollection::downloadMatrices(float *matrix,unsigned numMatrices,unsigned startIndex)
      { downloadMatricesFromOffset(matrix,matrixCollectionOffset64()+startIndex,numMatrices); }
      inline void InstancingMatrixCollection::uploadMatrices(const float *matrix,unsigned numMatrices,unsigned startIndex)
      { uploadMatricesToOffset(matrix,matrixCollectionOffset64()+startIndex,numMatrices); }
      inline unsigned InstancingMatrixCollection::gpuDataAllocationIndex() const  { return _gpuDataAllocationIndex; }
      inline unsigned InstancingMatrixCollection::gpuDataOffset4() const  { return _gpuDataAllocationIndex*2; }
      inline unsigned InstancingMatrixCollection::matrixCollectionOffset64() const  { return RenderingContext::current()->instancingMatrixAllocationManager()[_gpuMatricesAllocationId].startIndex; }
      inline std::shared_ptr<InstancingMatrixCollection> InstancingMatrixCollection::create()  { return std::make_shared<InstancingMatrixCollection>(); }
      inline const std::shared_ptr<InstancingMatrixCollection>& identity()  { return RenderingContext::current()->identityInstancingMatrix(); }
      inline void InstancingMatrixCollection::incrementInstanceRefCounter()
      { if(_numInstanceRefs==0) _selfRef=shared_from_this(); _numInstanceRefs++; }
      inline void InstancingMatrixCollection::decrementInstanceRefCounter()
      { _numInstanceRefs--; if(_numInstanceRefs==0) _selfRef=nullptr; }
   }
}

#endif // GE_SG_INSTANCING_MATRIX_COLLECTION_H

