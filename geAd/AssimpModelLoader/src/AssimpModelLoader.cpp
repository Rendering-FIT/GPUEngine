#include "AssimpModelLoader.h"

#include <geSG/Model.h>
#include <geSG/Mesh.h>
#include <geSG/AttributeDescriptor.h>
#include <geSG/Material.h>
#include <geSG/MatrixTransform.h>
#include <geCore/EnumRegister.h>
#include <geCore/StandardSemanticsNames.h>
#include <geSG/Scene.h>
#include <geSG/Animation.h>
#include <geSG/AnimationChannel.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/mesh.h>
#include <assimp/types.h>

#include <UnicodeIOSystem.h>

#include <ste/DAG.h>
#include <ste/stl_extension.h>


#include <memory>
#include <iterator>

//debug
#include <iostream>

using namespace std;
using namespace ge::sg;
using namespace ge::core;

/**
 * Load model with default options (aiProcess_Triangulate | aiProcess_SortByPType).
 *
 * @param modelIdentifier Path to model file.
 */
ge::sg::Scene* AssimpModelLoader::loadScene(const char* modelIdentifier)
{
   return loadScene(modelIdentifier, aiProcess_Triangulate | aiProcess_SortByPType);  // no polygons larger than triangles | meshes with only one primitive type at the time
}

/**
 * Load model.
 *
 * @param modelIdentifier Path to model file.
 * @param options Assimp ai_ options that are forwarded directly to ReadFile method.
 *                See Assimp documentation.
 */
ge::sg::Scene* AssimpModelLoader::loadScene(const char* modelIdentifier, unsigned options)
{
   Assimp::Importer importer;
   importer.SetIOHandler(new UnicodeIOSystem());
   const aiScene *ai_scene = importer.ReadFile(modelIdentifier, options);
   
   if(!ai_scene) return nullptr;

   
   return createScene(ai_scene);
}

ge::sg::Scene* AssimpModelLoader::loadScene(const wchar_t* modelIdentifier)
{
   return loadScene(modelIdentifier, aiProcess_Triangulate | aiProcess_SortByPType);  // no polygons larger than triangles | meshes with only one primitive type at the time
}

ge::sg::Scene* AssimpModelLoader::loadScene(const wchar_t* modelIdentifier, unsigned options)
{
   Assimp::Importer importer;
   importer.SetIOHandler(new UnicodeIOSystem());
   /**
    * This will not work with real wchar_t string, because assimp makes internal deep copy of
    * the file name (string) and this copied string is then sent to custom IOSystem class.
    * Thus if you reinterpret the wchar_t to char the deep copy will not represent the original
    * wchar_t string. You either call the const char* overload or this one but with reinterpreted
    * modelIdentifier from char to wchar_t. Which here gets reinterpreted back.
    * This overload is implemented only for sake of consistent interface, because other model
    * loading libraries might get better use of wchar_t.
    */
   const aiScene *ai_scene = importer.ReadFile(reinterpret_cast<const char*>(modelIdentifier), options);

   if(!ai_scene) return nullptr;


   return createScene(ai_scene);
}


ge::sg::Scene * AssimpModelLoader::createScene(const aiScene *ai_scene)
{
   ge::sg::Scene* scene = new ge::sg::Scene;
   std::shared_ptr<ge::sg::Model> model(std::make_shared<ge::sg::Model>());
   scene->models.push_back(model);
   /* Make list of all things loaded so we can reference them in scene graph.*/
   /*
   * Materials has to be processed before meshes since mesh is referencing material.
   * Since in assimp they are referenced by index we need to save them in exact same order
   * inside model.materials too.
   */
   processSceneMaterials(ai_scene, model.get()); //
   processSceneMeshes(ai_scene, model.get());

   AnimationMap animationMap;
   /* Now reference them in the scene graph.*/
   processScene(ai_scene, model.get(), animationMap);

   /* load animations */
   processAnimations(*ai_scene, *scene, animationMap);


   scene->rootNode = model->rootNode;
   return scene;
}


void AssimpModelLoader::processSceneMeshes(const aiScene* scene, ge::sg::Model *model)
{
   for(unsigned i = 0; i < scene->mNumMeshes; i++)
   {
      shared_ptr<ge::sg::Mesh> mesh(createMesh(scene->mMeshes[i], scene));
      if(mesh)
      {
         mesh->material = model->materials.begin()[scene->mMeshes[i]->mMaterialIndex];
         model->meshes.push_back(mesh);
      }
   }
}

/**
 * TBD: Load other attributes as well. Will be probably done on need to have basis.
 */
ge::sg::Mesh* AssimpModelLoader::createMesh(const aiMesh* aimesh, const aiScene* scene)
{
   ge::sg::Mesh* mesh = new ge::sg::Mesh;
   mesh->count = aimesh->mNumVertices; //should be triangles
   mesh->primitive = translatePrimitiveType(aimesh->mPrimitiveTypes); //should be only one type see importer flags

   //populate indices
   if(aimesh->mNumFaces > 0)
   {
      shared_ptr<ge::sg::AttributeDescriptor> indices(new ge::sg::AttributeDescriptor());
      indices->numComponents = 1;
      indices->stride = 0;
      indices->type = ge::sg::AttributeDescriptor::DataType::UNSIGNED_INT;
      indices->semantic = attributeSemantics.indices;
      //! Beware - default deleter needed
      indices->data = std::shared_ptr<unsigned>(getindices(aimesh, &mesh->count), std::default_delete<unsigned[]>());
      indices->size = sizeof(unsigned) * (int)mesh->count;
      mesh->attributes.push_back(indices);
   }

   //populate vertices
   shared_ptr<ge::sg::AttributeDescriptor> vertices(new ge::sg::AttributeDescriptor());
   vertices->size = sizeof(float) * aimesh->mNumVertices * 3;
   vertices->numComponents = 3;
   vertices->stride = 0;
   vertices->type = ge::sg::AttributeDescriptor::DataType::FLOAT;
   vertices->semantic = attributeSemantics.position;
   vertices->data = std::shared_ptr<float>(new float[aimesh->mNumVertices * 3], std::default_delete<float[]>());
   std::copy(aimesh->mVertices,aimesh->mVertices+aimesh->mNumVertices, static_cast<aiVector3D*>(vertices->data.get()));
   mesh->attributes.push_back(vertices);

   //populate normals
   if (aimesh->mNormals)
   {
      shared_ptr<ge::sg::AttributeDescriptor> normals(new ge::sg::AttributeDescriptor());
      normals->size = sizeof(float) * aimesh->mNumVertices * 3;
      normals->numComponents = 3;
      normals->stride = 0;
      normals->type = ge::sg::AttributeDescriptor::DataType::FLOAT;
      normals->semantic = attributeSemantics.normal;
      normals->data = std::shared_ptr<float>(new float[aimesh->mNumVertices * 3], std::default_delete<float[]>());
      std::copy(aimesh->mNormals, aimesh->mNormals + aimesh->mNumVertices, static_cast<aiVector3D*>(normals->data.get()));
      mesh->attributes.push_back(normals);
   }

   if(aimesh->mTangents)
   {
      shared_ptr<ge::sg::AttributeDescriptor> tangents(new ge::sg::AttributeDescriptor());
      tangents->size = sizeof(float) * aimesh->mNumVertices * 3;
      tangents->numComponents = 3;
      tangents->stride = 0;
      tangents->type = ge::sg::AttributeDescriptor::DataType::FLOAT;
      tangents->semantic = attributeSemantics.tangent;
      tangents->data = std::shared_ptr<float>(new float[aimesh->mNumVertices * 3], std::default_delete<float[]>());
      std::copy(aimesh->mTangents, aimesh->mTangents + aimesh->mNumVertices, static_cast<aiVector3D*>(tangents->data.get()));
      mesh->attributes.push_back(tangents);
   }

   //populate texcoord
   if (aimesh->mTextureCoords)
   {
      for(int i=0; i< AI_MAX_NUMBER_OF_TEXTURECOORDS; i++)
      {
         if(aimesh->mTextureCoords[i])
         {
            shared_ptr<ge::sg::AttributeDescriptor> texcoord(new ge::sg::AttributeDescriptor());
            texcoord->size = sizeof(float) * aimesh->mNumVertices * 2;
            texcoord->numComponents = 2;
            texcoord->stride = 0;
            texcoord->type = ge::sg::AttributeDescriptor::DataType::FLOAT;
            texcoord->semantic = attributeSemantics.texcoord;
            texcoord->data = std::shared_ptr<float>(new float[aimesh->mNumVertices * 2], std::default_delete<float[]>());
            copy_MofN((float*)aimesh->mTextureCoords[i], (float*)texcoord->data.get(), 2, 3, aimesh->mNumVertices*3);
            mesh->attributes.push_back(texcoord);
         }
      }
   }

   return mesh;
}

/**
 * Copy indices from all faces into a single consecutive array - a.k.a. element buffer.
 *
 * @param count Output number of indices copied. If not desirable, can be omitted or 
 *              supplied with NULL.
 * @return Pointer to allocated array of indices. The caller has the ownership.
 */
unsigned * AssimpModelLoader::getindices(const aiMesh* aimesh, size_t* count/*=NULL*/)
{
   size_t numIndices = getNumIndices(aimesh);
   unsigned *indices = new unsigned[numIndices];
   unsigned *index = indices;
   //output
   if (count)
   {
   	*count = numIndices;
   }
   
   //copy indices from all faces into a single consecutive array - a.k.a. element buffer
   for(size_t i = 0; i < aimesh->mNumFaces; i++)
   {
      for(unsigned j = 0; j < aimesh->mFaces[i].mNumIndices;j++)
      {
         *index = aimesh->mFaces[i].mIndices[j];
         ++index;
      }
   }

   return indices;
}

size_t AssimpModelLoader::getNumIndices(const aiMesh* aimesh)
{
   size_t count = 0;
   for(unsigned i=0; i<aimesh->mNumFaces ; i++) //for all faces
   {
      count += aimesh->mFaces[i].mNumIndices;
   }
   return count;
}

ge::sg::Mesh::PrimitiveType AssimpModelLoader::translatePrimitiveType(int aiPrimitiveType)
{
   switch(aiPrimitiveType)
   {
      case aiPrimitiveType_POINT: return ge::sg::Mesh::PrimitiveType::POINTS;
      case aiPrimitiveType_LINE: return ge::sg::Mesh::PrimitiveType::LINES;
      case aiPrimitiveType_TRIANGLE: return ge::sg::Mesh::PrimitiveType::TRIANGLES;
      case aiPrimitiveType_POLYGON: return ge::sg::Mesh::PrimitiveType::POLYGON;
      default: return ge::sg::Mesh::PrimitiveType::UNKNOWN;
   }
}


ge::sg::MaterialSimpleComponent::Semantic AssimpModelLoader::getSimpleComponentSemantic(char *data, size_t length)
{
   std::string key(data,length);
   if(key.find("ambient") != std::string::npos) return materialSemantics.ambientColor;
   else if(key.find("diffuse") != std::string::npos) return materialSemantics.diffuseColor;
   else if(key.find("specular") != std::string::npos) return materialSemantics.specularColor;
   else if(key.find("emissive") != std::string::npos) return materialSemantics.emissiveColor;
   else if(key.find("shininess") != std::string::npos) return materialSemantics.shininess;
   else return ge::sg::MaterialSimpleComponent::Semantic::unknown;
   
}

ge::sg::MaterialImageComponent::Semantic AssimpModelLoader::getImageComponentSemantic(unsigned type)
{
   switch(type)
   {
      case aiTextureType_DIFFUSE: return materialSemantics.diffuseTexture;
      case aiTextureType_SPECULAR: return materialSemantics.specularTexture;
      case aiTextureType_AMBIENT: return materialSemantics.ambientTexture;
      case aiTextureType_EMISSIVE: return materialSemantics.emissiveTexture;
      case aiTextureType_HEIGHT: return materialSemantics.heightTexture;
      case aiTextureType_NORMALS: return materialSemantics.normalTexture;
      case aiTextureType_SHININESS: return materialSemantics.shininessTexture;
      case aiTextureType_OPACITY: return materialSemantics.opacityTexture;
      case aiTextureType_DISPLACEMENT: return materialSemantics.opacityTexture;
      case aiTextureType_LIGHTMAP: return materialSemantics.lightmapTexture;
      case aiTextureType_REFLECTION: return materialSemantics.reflectionTexture;
      case aiTextureType_UNKNOWN:
      case aiTextureType_NONE: 
      default: return ge::sg::MaterialImageComponent::Semantic::unknown;
   }
}

void AssimpModelLoader::processSceneMaterials(const aiScene * scene, ge::sg::Model* model)
{
   for(unsigned i = 0; i < scene->mNumMaterials; i++)
   {
      std::shared_ptr<ge::sg::Material> mat(createMaterial(scene->mMaterials[i], scene));
      if(mat)
      {
         model->materials.push_back(mat);
      }
   }
}

/**
 * Processes some of the materials.
 * It processes textures and materials beginning with "$clr" and "$mat"
 * TBD: Process all of them. Will be done if needed.
 */
ge::sg::Material* AssimpModelLoader::createMaterial(aiMaterial* aimat, const aiScene * scene)
{
   ge::sg::Material *mat = new ge::sg::Material;
   //for each property
   for(unsigned int i = 0; i < aimat->mNumProperties; i++)
   {
      aiMaterialProperty* matprop = aimat->mProperties[i];
      if(matprop->mSemantic == 0) //non-texture property
      {
         std::string key(matprop->mKey.data, matprop->mKey.length);
         ge::sg::MaterialSimpleComponent *matComp = new ge::sg::MaterialSimpleComponent;
         if(key.find("$clr") != std::string::npos)
         {
            matComp->semantic = getSimpleComponentSemantic(matprop->mKey.data, matprop->mKey.length);
            matComp->dataType = ge::sg::MaterialSimpleComponent::DataType::FLOAT;
            matComp->size = 3;
            matComp->data.reset(new unsigned char[matprop->mDataLength]);
            std::copy_n(matprop->mData, matprop->mDataLength, matComp->data.get());
            mat->materialComponents.push_back(std::unique_ptr<ge::sg::MaterialComponent>(matComp));
         }
         else if(key.find("$mat") != std::string::npos)
         {
            matComp->semantic = getSimpleComponentSemantic(matprop->mKey.data, matprop->mKey.length);
            matComp->dataType = ge::sg::MaterialSimpleComponent::DataType::FLOAT;
            matComp->size = 1;
            matComp->data.reset(new unsigned char[matprop->mDataLength]);
            std::copy_n(matprop->mData, matprop->mDataLength, matComp->data.get());
            mat->materialComponents.push_back(std::unique_ptr<ge::sg::MaterialComponent>(matComp));
         }
      }
      else //textures (images)
      {
         aiString aistring;
         aiGetMaterialString(aimat, (matprop->mKey.data), matprop->mSemantic, matprop->mIndex, &aistring);
         if(aistring.length > 0)
         {
            ge::sg::MaterialImageComponent *imgComp = new ge::sg::MaterialImageComponent;
            imgComp->filePath = aistring.C_Str(); //copy constructor of std::string
            imgComp->semantic = getImageComponentSemantic(matprop->mSemantic);
            mat->materialComponents.push_back(std::unique_ptr<ge::sg::MaterialImageComponent>(imgComp));
         }
      }
   }

   return mat;
}

void AssimpModelLoader::copy_MofN(float* src, float * dst, unsigned m, unsigned n, unsigned count)
{
   unsigned cnt = 0;
   if (n < m)
   {
      m = n;
   }
   int rest = n - m - 1;
   int j = 0;
   for(unsigned i=0; i<count ; ++i)
   {
      if(cnt < m)
      {
         dst[j] = src[i];
         ++j;
         ++cnt;
      }
      else
      {
         i += rest;
         cnt = 0;
      }
   }
}

void AssimpModelLoader::processScene(const aiScene * scene, ge::sg::Model* model, AssimpModelLoader::AnimationMap& animationMap)
{
   if(!scene->mRootNode) return;
   shared_ptr<ge::sg::MatrixTransformNode> rootMatrixNode = std::make_shared<ge::sg::MatrixTransformNode>();
   model->rootNode = rootMatrixNode;
   aiNode *currentNode = scene->mRootNode;
   std::string name(currentNode->mName.C_Str());
   animationMap[name] = {currentNode, rootMatrixNode};
   /* this doesn't solve the case when this node has children but they have no meshes*/
   if(currentNode->mNumChildren > 0 || currentNode->mNumMeshes > 0)
   {
      std::shared_ptr<ge::sg::MatrixTransform> MT = createMatrixTransform(currentNode->mTransformation);
      rootMatrixNode->data = MT;
      fillTransformWithMeshes(currentNode, model, MT.get());
      aiNode *parent = currentNode;
      for(unsigned i = 0; i<scene->mRootNode->mNumChildren; i++)
      {
         currentNode = parent->mChildren[i];
         processNode(currentNode, model, rootMatrixNode.get(),animationMap);
      }
   }
}

std::shared_ptr<ge::sg::MatrixTransform> AssimpModelLoader::createMatrixTransform(const aiMatrix4x4& mTransformation)
{
   return std::make_shared<ge::sg::MatrixTransform>(std::make_shared<glm::mat4>(
      mTransformation.a1, mTransformation.b1, mTransformation.c1, mTransformation.d1,
      mTransformation.a2, mTransformation.b2, mTransformation.c2, mTransformation.d2,
      mTransformation.a3, mTransformation.b3, mTransformation.c3, mTransformation.d3,
      mTransformation.a4, mTransformation.b4, mTransformation.c4, mTransformation.d4
      ));
}

void AssimpModelLoader::fillTransformWithMeshes(const aiNode * node, ge::sg::Model *model, ge::sg::MatrixTransform * matrixTransform)
{
   for(unsigned i=0; i<node->mNumMeshes ; i++)
   {
      matrixTransform->meshes.push_back(model->meshes[node->mMeshes[i]]);
   }
}

void AssimpModelLoader::processNode(aiNode * ainode, ge::sg::Model *model, ge::sg::MatrixTransformNode* parentMatrixNode, AssimpModelLoader::AnimationMap& animationMap)
{
   if(ainode->mNumChildren > 0 || ainode->mNumMeshes > 0)
   {
      shared_ptr<ge::sg::MatrixTransformNode> childNode = make_shared<ge::sg::MatrixTransformNode>();
      parentMatrixNode->children.push_back(childNode);
      std::shared_ptr<ge::sg::MatrixTransform> MT = createMatrixTransform(ainode->mTransformation);
      childNode->data = MT;
      std::string name(ainode->mName.C_Str());
      animationMap[name] = {ainode, childNode};
      fillTransformWithMeshes(ainode, model, MT.get());
      for(unsigned i = 0; i < ainode->mNumChildren; i++)
      {
         aiNode *currentNode = ainode->mChildren[i];
         processNode(currentNode, model, childNode.get(),animationMap);
      }
   }
}

ge::sg::AnimationChannel* AssimpModelLoader::createMovementAnimationChannel(aiNodeAnim* ai_node_anim, ge::sg::Scene& scene, double frame_time, AssimpModelLoader::AnimationMap& animationMap)
{
   ge::sg::MovementAnimationChannel* channel = new ge::sg::MovementAnimationChannel;
   //findTarget();
   auto it = animationMap.find(std::string(ai_node_anim->mNodeName.C_Str()));
   if(it == animationMap.end())
   {
      std::cerr << "animation target not found: " << ai_node_anim->mNodeName.C_Str() << std::endl;
      return channel;
   }
   channel->setTarget(it->second.second->data->getRefMatrix());
   std::transform(ai_node_anim->mPositionKeys, ai_node_anim->mPositionKeys + ai_node_anim->mNumPositionKeys, std::back_inserter(channel->positionKF), [frame_time](aiVectorKey key){ return ge::sg::MovementAnimationChannel::Vec3KeyFrame(ge::core::toTimeUnit<double,ratio<1>>(key.mTime*frame_time), glm::vec3(key.mValue.x, key.mValue.y, key.mValue.z)); });
   std::transform(ai_node_anim->mScalingKeys, ai_node_anim->mScalingKeys + ai_node_anim->mNumScalingKeys, std::back_inserter(channel->scaleKF), [frame_time](aiVectorKey key){ return ge::sg::MovementAnimationChannel::Vec3KeyFrame(ge::core::toTimeUnit<double, ratio<1>>(key.mTime*frame_time), glm::vec3(key.mValue.x, key.mValue.y, key.mValue.z)); });
   std::transform(ai_node_anim->mRotationKeys, ai_node_anim->mRotationKeys + ai_node_anim->mNumRotationKeys, std::back_inserter(channel->orientationKF), [frame_time](aiQuatKey key){ return ge::sg::MovementAnimationChannel::QuatKeyFrame(ge::core::toTimeUnit<double, ratio<1>>(key.mTime*frame_time), glm::quat(key.mValue.w, key.mValue.x, key.mValue.y, key.mValue.z)); });


   return channel;
}

ge::sg::Animation * AssimpModelLoader::createAnimation(aiAnimation& m_animation, ge::sg::Scene& scene, AssimpModelLoader::AnimationMap& animationMap)
{
   double frameTime = 1.0 / m_animation.mTicksPerSecond; //one anim tick in s
   ge::sg::Animation* animation = new ge::sg::Animation;
   animation->duration = ge::core::toTimeUnit<double,std::ratio<1>>((m_animation.mDuration) / m_animation.mTicksPerSecond * 1000.);
   for (unsigned i = 0; i < m_animation.mNumChannels; ++i)
   {
      animation->channels.emplace_back(createMovementAnimationChannel(m_animation.mChannels[i],scene,frameTime, animationMap));
   }
   return animation;
}

void AssimpModelLoader::processAnimations(const aiScene& ai_scene, ge::sg::Scene& scene, AssimpModelLoader::AnimationMap& animationMap)
{
   for (unsigned i = 0; i < ai_scene.mNumAnimations; ++i)
   {
      //two allocations in shared_ptr
      scene.animations.emplace_back(createAnimation(*ai_scene.mAnimations[i], scene,animationMap));
   }
}

void AssimpModelLoader::registerSemantics()
{
   materialSemantics.ambientColor = ge::sg::MaterialSimpleComponent::Semantic::ambientColor;
   materialSemantics.diffuseColor = ge::sg::MaterialSimpleComponent::Semantic::diffuseColor;
   materialSemantics.specularColor = ge::sg::MaterialSimpleComponent::Semantic::specularColor;
   materialSemantics.emissiveColor = ge::sg::MaterialSimpleComponent::Semantic::emissiveColor;
   materialSemantics.shininess = ge::sg::MaterialSimpleComponent::Semantic::shininess;
   materialSemantics.ambientTexture = ge::sg::MaterialImageComponent::Semantic::ambientTexture;
   materialSemantics.diffuseTexture = ge::sg::MaterialImageComponent::Semantic::diffuseTexture;
   materialSemantics.specularTexture = ge::sg::MaterialImageComponent::Semantic::specularTexture;
   materialSemantics.emissiveTexture = ge::sg::MaterialImageComponent::Semantic::emissiveTexture;
   materialSemantics.heightTexture = ge::sg::MaterialImageComponent::Semantic::heightTexture;
   materialSemantics.normalTexture = ge::sg::MaterialImageComponent::Semantic::normalTexture;
   materialSemantics.shininessTexture = ge::sg::MaterialImageComponent::Semantic::shininessTexture;
   materialSemantics.opacityTexture = ge::sg::MaterialImageComponent::Semantic::opacityTexture;
   materialSemantics.displacementTexture = ge::sg::MaterialImageComponent::Semantic::displacementTexture;
   materialSemantics.lightmapTexture = ge::sg::MaterialImageComponent::Semantic::lightmapTexture;
   materialSemantics.reflectionTexture = ge::sg::MaterialImageComponent::Semantic::reflectionTexture;

   attributeSemantics.position = ge::sg::AttributeDescriptor::Semantic::position;
   attributeSemantics.normal = ge::sg::AttributeDescriptor::Semantic::normal;
   attributeSemantics.tangent = ge::sg::AttributeDescriptor::Semantic::tangent;
   attributeSemantics.binormal = ge::sg::AttributeDescriptor::Semantic::binormal;
   attributeSemantics.indices = ge::sg::AttributeDescriptor::Semantic::indices;
   attributeSemantics.texcoord = ge::sg::AttributeDescriptor::Semantic::texcoord;
}

AssimpModelLoader::AttributeSemantics AssimpModelLoader::attributeSemantics;

AssimpModelLoader::MaterialSemantics AssimpModelLoader::materialSemantics;

AssimpModelLoader::MaterialSemantics::MaterialSemantics()
   : ambientColor(ge::sg::MaterialSimpleComponent::Semantic::ambientColor)
   , diffuseColor(ge::sg::MaterialSimpleComponent::Semantic::diffuseColor)
   , specularColor(ge::sg::MaterialSimpleComponent::Semantic::specularColor)
   , emissiveColor(ge::sg::MaterialSimpleComponent::Semantic::emissiveColor)
   , shininess(ge::sg::MaterialSimpleComponent::Semantic::shininess)
   , ambientTexture(ge::sg::MaterialImageComponent::Semantic::ambientTexture)
   , diffuseTexture(ge::sg::MaterialImageComponent::Semantic::diffuseTexture)
   , specularTexture(ge::sg::MaterialImageComponent::Semantic::specularTexture)
   , emissiveTexture(ge::sg::MaterialImageComponent::Semantic::emissiveTexture)
   , heightTexture(ge::sg::MaterialImageComponent::Semantic::heightTexture)
   , normalTexture(ge::sg::MaterialImageComponent::Semantic::normalTexture)
   , shininessTexture(ge::sg::MaterialImageComponent::Semantic::shininessTexture)
   , opacityTexture(ge::sg::MaterialImageComponent::Semantic::opacityTexture)
   , displacementTexture(ge::sg::MaterialImageComponent::Semantic::displacementTexture)
   , lightmapTexture(ge::sg::MaterialImageComponent::Semantic::lightmapTexture)
   , reflectionTexture(ge::sg::MaterialImageComponent::Semantic::reflectionTexture)
{}

AssimpModelLoader::AttributeSemantics::AttributeSemantics()
   : position(ge::sg::AttributeDescriptor::Semantic::position)
   , normal(ge::sg::AttributeDescriptor::Semantic::normal)
   , tangent(ge::sg::AttributeDescriptor::Semantic::tangent)
   , binormal(ge::sg::AttributeDescriptor::Semantic::binormal)
   , indices(ge::sg::AttributeDescriptor::Semantic::indices)
   , texcoord(ge::sg::AttributeDescriptor::Semantic::texcoord)
{}