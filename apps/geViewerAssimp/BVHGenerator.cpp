#include <geSG/AttributeDescriptor.h>
#include <geSG/Mesh.h>
#include <geCore/StandardSemanticsNames.h>
#include <algorithm>
#include <vector>
#include "BVHGenerator.h"
#include "MatrixStack.h"


std::shared_ptr<ge::util::BVHGenerator::BSMTNode> ge::util::BVHGenerator::generateBoundingSpheresHierarchy(std::shared_ptr<ge::sg::MatrixTransformNode>& node)
{
   ge::util::MatrixStack matrixStack;
   return generateBSforMT(node, matrixStack);
}

std::shared_ptr<ge::util::BVHGenerator::BSMTNode> ge::util::BVHGenerator::generateBSforMT(std::shared_ptr<ge::sg::MatrixTransformNode>& MT, ge::util::MatrixStack& matrixStack)
{
   std::shared_ptr<BSMTNode> currentNode(std::make_shared<BSMTNode>(std::make_shared<MatrixTransformBoundingSphere>()));
   currentNode->data->MTNode->insideThing = MT;
   matrixStack.push(*MT->data->getRefMatrix());

   //create BS for every mesh
   for (auto mesh : MT->data->meshes)
   {
      std::shared_ptr<MeshBS> meshBS(std::make_shared<MeshBS>());
      meshBS = generateMeshBS(mesh, matrixStack);
      currentNode->data->meshBS.push_back(meshBS);
   }

   //create BS for child MT nodes by recursive descent... Descent, that was a game!
   for (auto childMTNode : MT->children)
   {
      currentNode->children.push_back(generateBSforMT(childMTNode, matrixStack));
   }

   //once all child BS are computed, let's compute the current node
   computeBSforCurrentNode(currentNode);

   matrixStack.pop();

   return currentNode;
}

void ge::util::BVHGenerator::computeBSforCurrentNode(std::shared_ptr<ste::Node<std::shared_ptr<MatrixTransformBoundingSphere>>>& currentNode)
{
   unsigned size = (currentNode->data->meshBS.size() + currentNode->children.size());

   //no meshes and no children found so this should be sphere vith 0 radius located at (0,0,0)
   if(size == 0)
   {
      return;
   }
   glm::vec3 center;
   unsigned numBS = 0;

   for(auto meshBS : currentNode->data->meshBS)
   {
      if(meshBS->radius >= 0.0f)
      {
         ++numBS;
         center += meshBS->center;
      }
      
   }

   for(auto child : currentNode->children)
   {
      if(child->data->MTNode->radius >= 0.0f)
      {
         ++numBS;
         center += child->data->MTNode->center;
      }
   }

   center /= (float)numBS;

   float radiusMax = -1.0f;

   for(auto meshBS : currentNode->data->meshBS)
   {
      if(meshBS->radius >= 0.0f)
      {
         float radius = glm::distance(center, meshBS->center) + meshBS->radius;
         radiusMax = radiusMax >= radius ? radiusMax : radius;
      }
   }

   for(auto child : currentNode->children)
   {
      if(child->data->MTNode->radius >= 0.0f)
      {
         float radius = glm::distance(center, child->data->MTNode->center) + child->data->MTNode->radius;
         radiusMax = radiusMax >= radius ? radiusMax : radius;
      }
   }

   (***currentNode)/*->data*/.MTNode->center = center;
   currentNode->data->MTNode->radius = radiusMax;
}

//ge::sg::BoundingSphere ge::util::BVHGenerator::generateBSforLocalMeshes(std::shared_ptr<ge::sg::MatrixTransformNode>& MT)
//{
//   std::vector<std::shared_ptr<ge::sg::BoundingSphere>> meshesBSs;
//   meshesBSs.reserve(MT->data->meshes.size());
//
//   for(auto mesh : MT->data->meshes )
//   {
//      meshesBSs.push_back(generateMeshBS(mesh));
//   }
//
//   ge::sg::BoundingSphere meshesBS =  mergeBS(meshesBSs);
//
//   return meshesBS;
//}

std::shared_ptr<ge::util::BVHGenerator::MeshBS> ge::util::BVHGenerator::generateMeshBS(std::shared_ptr<ge::sg::Mesh>& mesh, ge::util::MatrixStack& matrixStack)
{
   auto attrIt = std::find_if(mesh->attributes.begin(), mesh->attributes.end(), [](std::shared_ptr<ge::sg::AttributeDescriptor>& attr){ return attr->semantic == ge::sg::AttributeDescriptor::Semantic::POSITION; });
   unsigned size = (*attrIt)->size / (*attrIt)->getSize(sg::AttributeDescriptor::DataType::FLOAT);

   std::shared_ptr<MeshBS> bs(std::make_shared<MeshBS>(mesh));

   if((*attrIt)->numComponents < 1 || size < 1) return bs;


   glm::vec3 center;
   float radius = 0.0f;

   if((*attrIt)->type == ge::sg::AttributeDescriptor::DataType::FLOAT)
   {
      unsigned numcomp = (*attrIt)->numComponents;
      std::shared_ptr<float> buff = std::static_pointer_cast<float>((*attrIt)->data);
      center = computeMeshCenter<float>(buff, size, numcomp);
      radius = computeRadiusFromCenter<float>(buff,size,numcomp,center);
   }

   bs->center = center;
   bs->radius = radius;
   bs->insideThing = mesh;

   bs->transform(matrixStack.back());


   return bs;
}

ge::sg::BoundingSphere ge::util::BVHGenerator::mergeBS(std::vector<std::shared_ptr<ge::sg::BoundingSphere>>& spheres)
{
   glm::vec3 newCenter;
   float newRadius = 0.0f;

   //compute new center
   for(auto BS : spheres)
   {
      newCenter += (*BS).center;
   }

   newCenter /= spheres.size() + 1;

   for(auto BS : spheres)
   {
      float rad = glm::distance(newCenter, BS->center) + BS->radius;
      newRadius = newRadius >= rad ? newRadius : rad;
   }
   ge::sg::BoundingSphere ret;
   ret.center = newCenter;
   ret.radius = newRadius;
   return ret;
}