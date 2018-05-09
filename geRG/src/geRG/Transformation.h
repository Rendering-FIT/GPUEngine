#ifndef GE_RG_TRANSFORMATION_H
#define GE_RG_TRANSFORMATION_H

#include <memory>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <geRG/Export.h>
#include <geRG/ParentChildList.h>

namespace ge
{
   namespace rg
   {
      class MatrixList;


      /** Transformation class maintains 4x4 matrix transformation.
       *
       *  Matrix data are generally placed in the GPU buffer.
       *  Each Transformation usually has its own matrix, but
       *  number of Transformation objects may be configured to share
       *  the same matrix if desired.
       *
       *  Transformation objects are organized in a graph structure,
       *  allowing for hierarchical transformations.
       */
      class GERG_EXPORT Transformation : public std::enable_shared_from_this<Transformation> {
      public:

         // parent and child list
         // (child list is list<shared_ptr<Transformation> and
         // parent list is list<Transformation*>)
         GERG_CHILD_LIST(Transformation)
         GERG_PARENT_LIST(Transformation)

      protected:

         /** SharedDataOffset is used whenever two or more Transformation objects
          *  share the same transformation matrix.
          *
          *  The matrix is usually stored in RenderingContext::cpuTransformationBuffer() buffer
          *  (cpu buffer is used temporarily until gpu transformation processing is implemented).
          *  Transformation::_gpuDataOffset64 is used as the index (or offset multiplied by 64)
          *  to the matrix of particular Transformation. If two or more Transformations share
          *  the matrix, they need to share _gpuDataOffset64 variable as well.
          *  SharedDataOffset structure is allocated in such case
          *  and all Transformation objects use the SharedDataOffset::_gpuDataOffset64
          *  variable instead.
          */
         struct SharedDataOffset {
            unsigned _gpuDataOffset64;  ///< Index (or offset multiplied by 64) to the matrix buffer. Zero value is reserved for non-allocated matrix.
            unsigned _refCounter;       ///< Reference counter. It contains number of attached Transformation objects.
         };

         unsigned *_gpuDataOffsetPtr;  ///< Points either to _gpuDataOffset64 member or to externally allocated SharedDataOffset::_gpuDataOffset64.
         unsigned _gpuDataOffset64;    ///< Index (or offset multiplied by 64) to the matrix buffer where the transformation matrix is stored. Zero value is reserved for non-allocated matrix.
         std::shared_ptr<MatrixList> _matrixList;  ///< MatrixList, if attached, will receive the transformation computed by multiplication of all parent Transformations.

      public:

         void uploadMatrix(const float *matrix);  ///< Uploads transformation matrix. The parameter matrix must point to array of 16 floats. The uploaded matrix is generally stored in GPU buffers, but it depends on implementation.
         inline void uploadMatrix(const glm::mat4& matrix);    ///< Uploads transformation matrix. The matrix is generally stored in GPU buffers, but it depends on implementation.
         void downloadMatrix(float *matrix);      ///< Downloads transformation matrix. The memory pointed by parameter matrix will receive 16 floats. The matrix is generally stored in GPU buffers, but it depends on implementation.
         inline void downloadMatrix(glm::mat4& matrix);  ///< Downloads transformation matrix. The source matrix is generally stored in GPU buffers, but it depends on implementation.
         float* getMatrixPtr();                   ///< Returns pointer on transformation matrix composed of 16 floats. Use the method with caution as there can be various requirements for the method to work correctly, like that certain buffers must be mapped, etc..

         inline unsigned gpuDataOffset64() const;  ///< Returns index (or offset multiplied by 64) to the matrix buffer where the transformation matrix is stored.
         void allocTransformationGpuData();        ///< Reallocates internal data in a way that there is no transformation matrix sharing. The method does not preserve transformation matrix. It is usually not necessary to call the method as it is called from the default constructor automatically.
         void shareTransformationFrom(const Transformation &shareFrom);  ///< Reallocates internal data in a way that the transformation matrix is shared from shareFrom. It is usually not necessary to call the method as it is called from shareFrom() and copy constructor.

         inline const std::shared_ptr<MatrixList>& getOrCreateMatrixList() const;  ///< Returns MatrixList. If no MatrixList is attached, one is created and before return.
         inline const std::shared_ptr<MatrixList>& matrixList() const;             ///< Returns MatrixList. It returns empty shared_ptr if no MatrixList was created or assigned yet.
         inline void setMatrixList(std::shared_ptr<MatrixList>& matrixList);       ///< Sets MatrixList.

         enum ConstructionFlags { SHARE_MATRIX=0x1, SHARE_MATRIX_LIST=0x2,
                                  COPY_CHILDREN=0x4, SHARE_AND_COPY_ALL=0x7 };
         Transformation();  ///< Default constructor.
         Transformation(const Transformation &shareFrom,unsigned constructionFlags=SHARE_AND_COPY_ALL);  ///< Copy constructor. The parameter constructionFlags allows to copy only certain parts of object state.
         ~Transformation();  ///< Destructor.
         static inline std::shared_ptr<Transformation> shareFrom(const Transformation& t);  ///< Constructs Transformation object that shares the transformation matrix with object given by t parameter.
      };
   }
}


#include <geRG/MatrixList.h>

namespace ge
{
   namespace rg
   {
      inline void Transformation::uploadMatrix(const glm::mat4& matrix)  { uploadMatrix(glm::value_ptr(matrix)); }
      inline void Transformation::downloadMatrix(glm::mat4& matrix)  { downloadMatrix(glm::value_ptr(matrix)); }
      inline unsigned Transformation::gpuDataOffset64() const  { return *_gpuDataOffsetPtr; }
      inline const std::shared_ptr<MatrixList>& Transformation::getOrCreateMatrixList() const
      { if(_matrixList==nullptr) const_cast<Transformation*>(this)->_matrixList=std::make_shared<MatrixList>(); return _matrixList; }
      inline const std::shared_ptr<MatrixList>& Transformation::matrixList() const  { return _matrixList; }
      inline void Transformation::setMatrixList(std::shared_ptr<MatrixList>& matrixList)  { _matrixList=matrixList; }
      inline std::shared_ptr<Transformation> Transformation::shareFrom(const Transformation& t)
      { return std::make_shared<Transformation>(t,Transformation::SHARE_MATRIX); }
   }
}

#endif // GE_RG_TRANSFORMATION_H
