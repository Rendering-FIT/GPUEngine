#ifndef GE_SG_INSTANCING_MATRIX_COLLECTION_H
#define GE_SG_INSTANCING_MATRIX_COLLECTION_H

#include <memory>

namespace ge
{
   namespace sg
   {

      struct InstancingMatrixCollectionGpuData {
         unsigned numMatrices;
         unsigned matrixCollectionOffset64;
      };

      class InstancingMatrixCollection : public std::enable_shared_from_this<InstancingMatrixCollection> {
      protected:

         unsigned _numInstanceRefs;
         unsigned _gpuDataAllocationIndex;
         unsigned _numMatricesAndDirtyFlag;
         unsigned _gpuMatricesAllocationId;
         std::shared_ptr<InstancingMatrixCollection> _selfRef;

      public:

         void download(unsigned &matrixCollectionOffset64,unsigned &numMatrices);
         void upload(unsigned matrixCollectionOffset64,unsigned numMatrices);
         static void downloadMatrices(float *matrix,unsigned matrixCollectionOffset64,unsigned numMatrices);
         static void uploadMatrices(const float *matrix,unsigned matrixCollectionOffset64,unsigned numMatrices);

         inline unsigned numMatrices() const  { return _numMatricesAndDirtyFlag&0x7fffffff; }
         inline void setNumMatrices(unsigned num)  { _numMatricesAndDirtyFlag=(_numMatricesAndDirtyFlag&0x80000000)|num; }

         inline bool gpuNumMatricesDirty() const  { return _numMatricesAndDirtyFlag>=0x80000000; }
         inline void setGpuNumMatricesDirty(bool dirty)  { _numMatricesAndDirtyFlag=(_numMatricesAndDirtyFlag&0x7fffffff)|(dirty<<31); }

         void updateGpuData();

         inline void incrementInstanceRefCounter();
         inline void decrementInstanceRefCounter();

         static inline std::shared_ptr<InstancingMatrixCollection> create();
         InstancingMatrixCollection();
         ~InstancingMatrixCollection();

      };

   }
}


namespace ge
{
   namespace sg
   {
      inline std::shared_ptr<InstancingMatrixCollection> InstancingMatrixCollection::create()  { return std::make_shared<InstancingMatrixCollection>(); }
      inline void InstancingMatrixCollection::incrementInstanceRefCounter()
      { if(_numInstanceRefs==0) _selfRef=shared_from_this(); _numInstanceRefs++; }
      inline void InstancingMatrixCollection::decrementInstanceRefCounter()
      { _numInstanceRefs--; if(_numInstanceRefs==0) _selfRef=nullptr; }
   }
}

#endif // GE_SG_INSTANCING_MATRIX_COLLECTION_H
