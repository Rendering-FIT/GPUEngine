#ifndef GE_RG_OBJECT_H
#define GE_RG_OBJECT_H

#include <geRG/Export.h>
#include <geRG/FlexibleArrayList.h>

namespace ge
{
   namespace rg
   {
      class MatrixList;
      class StateSet;
      struct DrawCommand;


      /** ObjectBase is base class for ge::rg::Object.
       *  Because ge::rg::Object is flexible object (see FlexibleArray),
       *  ObjectBase contains fixed part of Object and ObjectDrawCommand
       *  the flexible part.
       */
      class GERG_EXPORT ObjectBase : public ListItemBase {
      public:
         StateSet *stateSet;
         MatrixList *matrixList;
      };


      /** Object is essential class for rendering of meshes (ge::rg::Mesh).
       *
       *  It "instances" the mesh using matrices from MatrixList
       *  while using particular StateSet.
       */
      typedef FlexibleArray<DrawCommand,ObjectBase> Object;
      typedef FlexibleArrayList<Object> ObjectList;
      typedef ObjectList::iterator ObjectId;

   }
}

#endif /* GE_RG_OBJECT_H */
