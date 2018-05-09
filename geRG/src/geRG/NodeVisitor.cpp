#include <geSG/NodeVisitor.h>
#include <geSG/MatrixTransform.h>

using namespace ge::sg;


void NodeVisitor::apply(Node& node)
{
   node.traverse(*this);
}


void NodeVisitor::apply(Group& node)
{
   apply(static_cast<Node&>(node));
}


void NodeVisitor::apply(MatrixTransform& node)
{
   apply(static_cast<Group&>(node));
}
