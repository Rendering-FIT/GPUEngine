#include <memory>
#include <geAd/Export.h>

namespace osg
{
   class Node;
}
namespace ge {
   namespace rg
   {
      class Model;
   }
   namespace osgImport
   {

      std::shared_ptr<ge::rg::Model> GEAD_EXPORT import(osg::Node *osgGraph);

   }
}
