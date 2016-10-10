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

      unsigned ambientColor;
      unsigned diffuseColor;
      unsigned specularColor;
      unsigned emissiveColor;
      unsigned shininess;
      unsigned ambientTexture;
      unsigned diffuseTexture;
      unsigned specularTexture;
      unsigned emissiveTexture;
      unsigned heightTexture;
      unsigned normalTexture;
      unsigned shininessTexture;
      unsigned opacityTexture;
      unsigned displacementTexture;
      unsigned lightmapTexture;
      unsigned reflectionTexture;
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
   static unsigned getSimpleComponentSemantic(char *data, size_t length);
   static unsigned getImageComponentSemantic(unsigned type);
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

};