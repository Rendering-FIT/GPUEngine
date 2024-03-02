#pragma once

namespace std
{
   template<typename T> class shared_ptr;
}

namespace ste
{
   template<typename Data> class Node;
}
namespace ge{
   namespace sg
   {
      class MatrixTransformBase;
      /**
       * Basic graph node typedef.
       */
      typedef ste::Node<std::shared_ptr<ge::sg::MatrixTransformBase>> MatrixTransformNode;
   }
}