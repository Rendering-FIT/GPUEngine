#ifndef GE_RG_DRAWABLE_H
#define GE_RG_DRAWABLE_H

#include <memory>
#include <geRG/Export.h>
#include <geRG/FlexibleArrayList.h>

namespace ge
{
   namespace rg
   {
      class MatrixList;
      class StateSet;
      struct DrawCommand;


      /** DrawableBase is base class for ge::rg::Drawable.
       *  Because ge::rg::Drawable is flexible object (see FlexibleArray),
       *  DrawableBase contains fixed part of the object, followed by
       *  the flexible part. The flexible part is array of DrawCommands.
       */
      class GERG_EXPORT DrawableBase : public ListItemBase {
      public:
         StateSet *stateSet;
         MatrixList* matrixList;
      };


      /** Drawable is essential class for rendering of meshes (ge::rg::Mesh).
       *
       *  It "instances" the mesh using matrices from MatrixList
       *  while using particular StateSet.
       */
      typedef FlexibleArray<DrawCommand,DrawableBase> Drawable;
      typedef FlexibleArrayList<Drawable> DrawableList;
      typedef DrawableList::iterator DrawableId;

   }
}

#endif /* GE_RG_DRAWABLE_H */
