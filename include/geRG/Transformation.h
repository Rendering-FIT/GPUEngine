#ifndef GE_RG_TRANSFORMATION_H
#define GE_RG_TRANSFORMATION_H

#include <memory>
#include <geRG/Export.h>
#include <geRG/ParentChildList.h>

namespace ge
{
   namespace rg
   {
      class MatrixList;


      struct TransformationThreadGpuData {
         unsigned transformationIndicesOffset4;
         unsigned computedMatrixOffset64;
      };


      /** Transformation class maintains 4x4 matrix transformation.
       *
       *  Matrix data are usually placed in the GPU buffer.
       *  Each Transformation may point to its own matrix or
       *  number of Transformation objects may point to the same matrix
       *  if sharing of the value is required.
       *
       *  Transformation objects are organized in graph structure,
       *  allowing for hierarchical transformations.
       */
      class GERG_EXPORT Transformation : public std::enable_shared_from_this<Transformation> {
      public:

         GERG_CHILD_LIST(Transformation*,std::shared_ptr<Transformation>)
         GERG_PARENT_LIST(std::shared_ptr<Transformation>,Transformation*)

      protected:

         struct SharedDataOffset {
            unsigned _gpuDataOffset64;
            unsigned _refCounter;
         };

         unsigned *_gpuDataOffsetPtr;  ///< It points either to _gpuDataOffset64 member or to externally allocated SharedDataOffset::_gpuDataOffset64.
         unsigned _gpuDataOffset64;
         std::shared_ptr<MatrixList> _matrixList;

         void cancelSharedTransformation();

      public:

         void uploadMatrix(const float *matrix);
         void downloadMatrix(float *matrix);
         float* getMatrixPtr();

         inline unsigned gpuDataOffset64() const;
         void allocTransformationGpuData();
         void shareTransformationFrom(const Transformation &t);

         inline std::shared_ptr<MatrixList>& getOrCreateMatrixList();
         inline const std::shared_ptr<MatrixList>& getOrCreateMatrixList() const;
         inline std::shared_ptr<MatrixList>& matrixList();
         inline const std::shared_ptr<MatrixList>& matrixList() const;
         inline void setMatrixList(std::shared_ptr<MatrixList>& ml);

         enum ConstructionFlags { SHARE_MATRIX=0x1, SHARE_INSTANCING_MATRIX_COLLECTION=0x2,
                                  COPY_CHILDREN=0x4, SHARE_AND_COPY_ALL=0x7 };
         inline Transformation();
         //inline Transformation(const Transformation &t,unsigned constructionFlags=SHARE_AND_COPY_ALL);
         inline ~Transformation();

         /*ChildList::iterator addChild(std::shared_ptr<Transformation> &m);
         void removeChild(ChildList::iterator it);
         void removeChild(std::shared_ptr<Transformation> m);*/
         inline ChildList& getChildren();
         inline const ChildList& getChildren() const;
         inline ParentList& getParents();
         inline const ParentList& getParents() const;

         inline void instanceRef();
         inline void instanceUnref();
      };

   }
}


#include <geRG/MatrixList.h>

namespace ge
{
   namespace rg
   {
      inline unsigned Transformation::gpuDataOffset64() const  { return *_gpuDataOffsetPtr; }
      inline std::shared_ptr<MatrixList>& Transformation::getOrCreateMatrixList()
      { if(_matrixList==nullptr) _matrixList=std::make_shared<MatrixList>(); return _matrixList; }
      inline const std::shared_ptr<MatrixList>& Transformation::getOrCreateMatrixList() const
      { if(_matrixList==nullptr) const_cast<Transformation*>(this)->_matrixList=std::make_shared<MatrixList>(); return _matrixList; }
      inline std::shared_ptr<MatrixList>& Transformation::matrixList()  { return _matrixList; }
      inline const std::shared_ptr<MatrixList>& Transformation::matrixList() const  { return _matrixList; }
      inline void Transformation::setMatrixList(std::shared_ptr<MatrixList>& ml)  { _matrixList=ml; }
      inline Transformation::Transformation() : _gpuDataOffsetPtr(&_gpuDataOffset64), _gpuDataOffset64(0)  {}
      inline Transformation::~Transformation()  { RenderingContext::current()->transformationAllocationManager().free(_gpuDataOffsetPtr[0]);
         if(_gpuDataOffsetPtr!=&_gpuDataOffset64) { _gpuDataOffsetPtr[1]--; if((--_gpuDataOffsetPtr[1])==0) delete reinterpret_cast<SharedDataOffset*>(_gpuDataOffsetPtr); } removeAllChildren(); }
      inline Transformation::ChildList& Transformation::getChildren()  { return _childList; }
      inline const Transformation::ChildList& Transformation::getChildren() const  { return _childList; }
      inline Transformation::ParentList& Transformation::getParents()  { return _parentList; }
      inline const Transformation::ParentList& Transformation::getParents() const  { return _parentList; }
   }
}

#endif // GE_RG_TRANSFORMATION_H
