#ifndef GE_RG_INSTANCING_MATRICES_H
#define GE_RG_INSTANCING_MATRICES_H

#include <memory>
#include <glm/mat4x4.hpp>
#include <geRG/Export.h>

namespace ge
{
   namespace rg
   {

      struct InstancingMatrixGpuData {
         float matrix[16];
         inline float* asFloats()  { return matrix; }
         inline glm::mat4& asGlmMatrix()  { return *reinterpret_cast<glm::mat4*>(&matrix[0]); }
      };


      struct InstancingMatricesControlGpuData {
         unsigned matrixCollectionOffset64;
         unsigned numMatrices;
      };


      class GERG_EXPORT InstancingMatrices : public std::enable_shared_from_this<InstancingMatrices> {
      protected:

         unsigned _numInstanceRefs;
         unsigned _controlDataAllocationIndex;  ///< Matrix control data allocation index.
         unsigned _matrixCounter;
         bool     _matrixCounterResetFlag;
         unsigned _matrixCollectionAllocationId;     ///< Allocation id of matrix collection (block of matrices).
         unsigned _numMatricesAllocated;
         std::shared_ptr<InstancingMatrices> _selfRef;

      public:

         void downloadCollectionData(unsigned &matrixCollectionOffset64,unsigned &numMatrices);
         void uploadCollectionData(unsigned matrixCollectionOffset64,unsigned numMatrices);
         static void downloadMatricesFromOffset(float *matrix,unsigned matrixCollectionOffset64,unsigned numMatrices);
         static void uploadMatricesToOffset(const float *matrix,unsigned matrixCollectionOffset64,unsigned numMatrices);
         inline void downloadMatrices(float *matrix,unsigned numMatrices,unsigned startIndex=0);
         inline void uploadMatrices(const float *matrix,unsigned numMatrices,unsigned startIndex=0);

         inline unsigned controlDataAllocationIndex() const;
         inline unsigned controlDataOffset4() const;
         inline unsigned matrixCollectionOffset64() const;  ///< Returns offset of the matrix collection (block of matrices) in InstancingMatrixBuffer.

         inline unsigned matrixCounter() const  { return _matrixCounter; }
         inline void setMatrixCounter(unsigned num)  { _matrixCounter=num; }

         inline bool matrixCounterResetFlag() const  { return _matrixCounterResetFlag; }
         inline void setMatrixCounterResetFlag(bool on)  { _matrixCounterResetFlag=on; }

         inline unsigned numMatricesAllocated() const  { return _numMatricesAllocated; }
         inline void setNumMatricesAllocated(unsigned num)  { _numMatricesAllocated=num; }

         void updateGpuControlData(unsigned numMatrices);

         inline void incrementInstanceRefCounter();
         inline void decrementInstanceRefCounter();

         static inline std::shared_ptr<InstancingMatrices> create();
         static inline const std::shared_ptr<InstancingMatrices>& identity();
         InstancingMatrices();
         InstancingMatrices(unsigned controlDataAllocationIndex,unsigned matrixCollectionAllocationId);
         ~InstancingMatrices();

      };

   }
}


#include <geRG/RenderingContext.h>

namespace ge
{
   namespace rg
   {
      inline void InstancingMatrices::downloadMatrices(float *matrix,unsigned numMatrices,unsigned startIndex)
      { downloadMatricesFromOffset(matrix,matrixCollectionOffset64()+startIndex,numMatrices); }
      inline void InstancingMatrices::uploadMatrices(const float *matrix,unsigned numMatrices,unsigned startIndex)
      { uploadMatricesToOffset(matrix,matrixCollectionOffset64()+startIndex,numMatrices); }
      inline unsigned InstancingMatrices::controlDataAllocationIndex() const  { return _controlDataAllocationIndex; }
      inline unsigned InstancingMatrices::controlDataOffset4() const  { return _controlDataAllocationIndex*2; }
      inline unsigned InstancingMatrices::matrixCollectionOffset64() const  { return RenderingContext::current()->instancingMatrixAllocationManager()[_matrixCollectionAllocationId].startIndex; }
      inline std::shared_ptr<InstancingMatrices> InstancingMatrices::create()  { return std::make_shared<InstancingMatrices>(); }
      inline const std::shared_ptr<InstancingMatrices>& identity()  { return RenderingContext::current()->identityInstancingMatrix(); }
      inline void InstancingMatrices::incrementInstanceRefCounter()
      { if(_numInstanceRefs==0) _selfRef=shared_from_this(); _numInstanceRefs++; }
      inline void InstancingMatrices::decrementInstanceRefCounter()
      { _numInstanceRefs--; if(_numInstanceRefs==0) _selfRef=nullptr; }
   }
}

#endif // GE_RG_INSTANCING_MATRICES_H
