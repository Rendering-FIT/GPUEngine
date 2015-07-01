#ifndef GE_SG_NODE_VISITOR_H
#define GE_SG_NODE_VISITOR_H

namespace ge
{
   namespace sg
   {
      class Node;
      class Mesh;
      class Group;
      class MatrixTransform;


      class NodeVisitor
      {
      protected:

      public:

         virtual void apply(Node& node);
         virtual void apply(Group& node);
         virtual void apply(MatrixTransform& node);

      };
   }
}

#endif // GE_SG_NODE_VISITOR_H
