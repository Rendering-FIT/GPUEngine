#pragma once

#include <geSG/Mesh.h>
#include <geSG/Material.h>
#include <geSG/Node.h>
#include <geSG/MatrixTransform.h>
#include <memory>
#include <geSG/Scene.h>
#include <assimp/anim.h>

namespace fsg{
   class AnimationChannel;
   class Animation;
}

namespace ge
{
   namespace sg
   {
      class AnimationChannel;
      class Model;
   }
}
struct aiMesh;
struct aiNode;
struct aiScene;
struct aiMaterial;


template<typename TReal>
class aiMatrix4x4t;
typedef aiMatrix4x4t<float> aiMatrix4x4;
template <typename TReal>
class aiVector3t;
typedef aiVector3t<float> aiVector3D;

class AssimpModelLoader
{
public:

   struct MaterialSemantics
   {
      MaterialSemantics();

      ge::sg::MaterialSimpleComponent::Semantic ambientColor;
      ge::sg::MaterialSimpleComponent::Semantic diffuseColor;
      ge::sg::MaterialSimpleComponent::Semantic specularColor;
      ge::sg::MaterialSimpleComponent::Semantic emissiveColor;
      ge::sg::MaterialSimpleComponent::Semantic shininess;
      ge::sg::MaterialImageComponent::Semantic ambientTexture;
      ge::sg::MaterialImageComponent::Semantic diffuseTexture;
      ge::sg::MaterialImageComponent::Semantic specularTexture;
      ge::sg::MaterialImageComponent::Semantic emissiveTexture;
      ge::sg::MaterialImageComponent::Semantic heightTexture;
      ge::sg::MaterialImageComponent::Semantic normalTexture;
      ge::sg::MaterialImageComponent::Semantic shininessTexture;
      ge::sg::MaterialImageComponent::Semantic opacityTexture;
      ge::sg::MaterialImageComponent::Semantic displacementTexture;
      ge::sg::MaterialImageComponent::Semantic lightmapTexture;
      ge::sg::MaterialImageComponent::Semantic reflectionTexture;
   };

   struct AttributeSemantics
   {
      AttributeSemantics();

      ge::sg::AttributeDescriptor::Semantic position;
      ge::sg::AttributeDescriptor::Semantic normal;
      ge::sg::AttributeDescriptor::Semantic tangent;
      ge::sg::AttributeDescriptor::Semantic binormal;
      ge::sg::AttributeDescriptor::Semantic indices;
      ge::sg::AttributeDescriptor::Semantic texcoord;
   };

   static ge::sg::Scene* loadScene(const char* modelIdentifier);
   static ge::sg::Scene* loadScene(const char* modelIdentifier, unsigned options);
   static ge::sg::Scene* loadScene(const wchar_t* modelIdentifier);
   static ge::sg::Scene* loadScene(const wchar_t* modelIdentifier, unsigned options);
   static void registerSemantics();

   typedef std::map<std::string, std::pair<aiNode*, std::shared_ptr<ge::sg::MatrixTransformNode> >> AnimationMap;

protected:
   static ge::sg::Scene * createScene(const aiScene *ai_scene);
   static ge::sg::Mesh* createMesh(const aiMesh* aimesh, const aiScene* scene); //need scene for materials
   static void processSceneMeshes(const aiScene* scene, ge::sg::Model *model);
   static unsigned *getindices(const aiMesh* aimesh, size_t* count=NULL);
   static size_t getNumIndices(const aiMesh* aimesh);
   static ge::sg::Mesh::PrimitiveType translatePrimitiveType(int aiPrimitiveType);
   static ge::sg::MaterialSimpleComponent::Semantic getSimpleComponentSemantic(char *data, size_t length);
   static ge::sg::MaterialImageComponent::Semantic getImageComponentSemantic(unsigned type);
   static void processSceneMaterials(const aiScene * scene, ge::sg::Model* model);
   static ge::sg::Material* createMaterial(aiMaterial* aimat, const aiScene * scene);
   static void copy_MofN(float* src, float * dst, unsigned m, unsigned n, unsigned count);
   static void processScene(const aiScene * scene, ge::sg::Model* model, AnimationMap& animationMap);
   static std::shared_ptr<ge::sg::MatrixTransform> createMatrixTransform(const aiMatrix4x4& mTransformation);
   static void fillTransformWithMeshes(const aiNode * node, ge::sg::Model *model, ge::sg::MatrixTransform * matrixTransform);
   static void processNode(aiNode * ainode, ge::sg::Model *model, ge::sg::MatrixTransformNode* parentMatrixNode, AnimationMap& animationMap);
   static ge::sg::AnimationChannel* createMovementAnimationChannel(aiNodeAnim* ai_node_anim, ge::sg::Scene& scene, double frame_time, AnimationMap& animationMap);
   static ge::sg::Animation * createAnimation(aiAnimation& m_animation, ge::sg::Scene& scene, AnimationMap& animationMap);
   static void processAnimations(const aiScene& ai_scene, ge::sg::Scene& scene, AnimationMap& animationMap);

   static MaterialSemantics materialSemantics;
   static AttributeSemantics attributeSemantics;

};