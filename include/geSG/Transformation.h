#ifndef GE_SG_TRANSFORMATION_H
#define GE_SG_TRANSFORMATION_H

#include <memory>
#include <geSG/ParentChildList.h>

namespace ge
{
   namespace sg
   {
      class InstancingMatrixCollection;


      struct TransformationThreadGpuData {
         unsigned transformationIndicesOffset4;
         unsigned computedMatrixOffset64;
      };

      class Transformation {
      public:

         typedef ChildListTemplate<Transformation> ChildList;
         typedef ParentListTemplate<Transformation> ParentList;

      protected:

         struct SharedDataOffset {
            unsigned _dataOffset16;
            unsigned _refCounter;
         };

         unsigned _dataOffset16;
         SharedDataOffset *_sharedDataOffset;
         ChildList _children;
         ParentList _parents;
         std::shared_ptr<InstancingMatrixCollection> _instancingMatrixCollection;

      public:

         enum ConstructionFlags { SHARE_MATRIX=0x1, SHARE_INSTANCING_MATRIX_COLLECTION=0x2,
                                  COPY_CHILDREN=0x4, SHARE_AND_COPY_ALL=0x7 };
         Transformation();
         Transformation(const Transformation &t,unsigned constructionFlags=SHARE_AND_COPY_ALL);
         ~Transformation();

         void shareTransformationFrom(const Transformation &t);


         void allocGpuObject(unsigned numChildren);

         void uploadMatrix(const float *values);
         void downloadMatrix(float *values);
         void uploadParentRefs();

         inline unsigned matrixOffset64();


         ChildList::iterator addChild(std::shared_ptr<Transformation> m);
         void removeChild(ChildList::iterator it);
         void removeChild(std::shared_ptr<Transformation> m);

         inline void instanceRef();
         inline void instanceUnref();
      };

   }
}


namespace ge
{
   namespace sg
   {
   }
}

#endif // GE_SG_TRANSFORMATION_H
