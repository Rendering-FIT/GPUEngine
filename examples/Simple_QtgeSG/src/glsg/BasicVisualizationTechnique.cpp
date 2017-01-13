#include <glsg/BasicVisualizationTechnique.h>
#include <geUtil/MatrixStack.h>
#include <geCore/StandardSemanticsNames.h>
#include <glsg/MatrixUniformCommands.h>
#include <glsg/GLScene.h>
#include <glsg/GLCommands.h>
#include <glsg/EnumToGL.h>
#include <algorithm>
#include <ste/DAG.h>
#include <geSG/MatrixTransform.h>

#include <glm/gtc/matrix_transform.hpp>

//using namespace ll;
using namespace fsg;
using namespace std;
using namespace ge::sg;
using namespace ge::glsg;
using namespace ge::core;

BasicVisualizationTechnique::BasicVisualizationTechnique()
   //: renderGraph(std::make_shared<ForrysSimpleRG>())
{
}

void BasicVisualizationTechnique::setInput(std::shared_ptr<GLScene>& glscene)
{
   this->glscene = glscene;
}

void BasicVisualizationTechnique::reset()
{
   processingHelper.reset();
   VAOConatainer.clear();
}

void BasicVisualizationTechnique::process()
{
   if(!glscene || !phongProgram) return;
   reset();
   //helper structure needed for pairing the materials with their cmdLists etc.
   createMaterialsCmdLists();
   createMeshesCmdLists();
}

void BasicVisualizationTechnique::processSingleMesh(ge::sg::Mesh* mesh)
{
   createMeshCommandList(mesh);
   createMaterialCommandList(mesh->material.get());
}

void BasicVisualizationTechnique::drawSetup()
{
   if(!glscene || !phongProgram) return;

   phongProgram->use();
   (*prespectiveMatrixUniform)();
   (*viewMatrixUniform)();
   (*sceneAmbientLight)();
}

void BasicVisualizationTechnique::drawNode(std::shared_ptr<ge::sg::MatrixTransformNode> MTNode, ge::util::MatrixStack& matrix_stack)
{
   //push new matrix
   if(MTNode->data->getRefMatrix() != nullptr)
   {
      matrix_stack.push(*MTNode->data->getRefMatrix());
   }

   //creates model and normal matrices and apply them
   modelMatrixUniform->value = matrix_stack.back();
   normalMatrixUniform->value = glm::transpose(glm::inverse(modelMatrixUniform->value));

   (*modelMatrixUniform)();
   (*normalMatrixUniform)();

   //draw all meshes
   for (auto mesh : MTNode->data->meshes)
   {
      auto meshIt = processingHelper.meshMap.find(mesh.get());
      auto matIt = processingHelper.materialMap.find(mesh->material.get());
      if(meshIt != processingHelper.meshMap.end() && matIt != processingHelper.materialMap.end())
      {
         std::for_each((*matIt).second->begin(), (*matIt).second->end(), [](std::shared_ptr<ge::core::Command>& x){ (*x)(); });
         std::for_each((*meshIt).second->begin(), (*meshIt).second->end(), [](std::shared_ptr<ge::core::Command>& x){ (*x)(); });

      }
   }

   //traverse children
   for (auto childMT : MTNode->children)
   {
      drawNode(childMT, matrix_stack);
   }

   //pop the matrix
   matrix_stack.pop();

}

void BasicVisualizationTechnique::draw()
{
   if(!glscene || !phongProgram) return;

   phongProgram->use();
   (*prespectiveMatrixUniform)();
   (*viewMatrixUniform)();
   (*sceneAmbientLight)();

   ge::util::MatrixStack matrixStack;

   drawNode(glscene->scene->rootNode, matrixStack);
}

void BasicVisualizationTechnique::applyMaterial(ge::sg::Material* material)
{
   auto matIt = processingHelper.materialMap.find(material);
   if(matIt == processingHelper.materialMap.end())
   {
      cerr << "material not found\n";
   }
   for_each((*matIt).second->begin(), (*matIt).second->end(), [](shared_ptr<ge::core::Command>& x){ (*x)(); });
}

void BasicVisualizationTechnique::applyMatrixTransform(const ge::sg::MatrixTransform& mt)
{
   modelMatrixUniform->value = mt.getMatrix();
   normalMatrixUniform->value = glm::transpose(glm::inverse(modelMatrixUniform->value));

   (*modelMatrixUniform)();
   (*normalMatrixUniform)();
}

void BasicVisualizationTechnique::drawMesh(ge::sg::Mesh* mesh)
{
   auto meshIt = processingHelper.meshMap.find(mesh);
   if(meshIt == processingHelper.meshMap.end())
   {
      cerr << "mesh not found\n";
   }
   std::for_each((*meshIt).second->begin(), (*meshIt).second->end(), [](std::shared_ptr<ge::core::Command>& x){ (*x)(); });
}

void BasicVisualizationTechnique::initMatrixUniforms()
{
   prespectiveMatrixUniform = std::make_shared<UniformMatrixGLMShared>(phongProgram->getUniform("projectionMatrix").getLocation(), 1, GL_FALSE, std::make_shared<glm::mat4>());
   viewMatrixUniform = std::make_shared<UniformMatrixGLMShared>(phongProgram->getUniform("viewMatrix").getLocation(), 1, GL_FALSE, std::make_shared<glm::mat4>());
   modelMatrixUniform = std::make_shared<UniformMatrixGLM>(phongProgram->getUniform("modelMatrix").getLocation(), 1, GL_FALSE, glm::mat4());
   normalMatrixUniform = std::make_shared<UniformMatrixGLM>(phongProgram->getUniform("normalMatrix").getLocation(), 1, GL_FALSE, glm::mat4());
   sceneAmbientLight = make_shared<Uniform4fGLM>(phongProgram->getUniform("ambientLight").getLocation(),1,glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
   phongProgram->use();
   phongProgram->set("lightPos",0.0f,0.0f,1.f,1.0f);
   phongProgram->set("lightCol", 1.f, 1.f, 1.f, 1.f);
}

void BasicVisualizationTechnique::updatePerspective(float fovy, float aspectRatio, float near, float far)
{
   *prespectiveMatrixUniform->value = glm::perspective(fovy, aspectRatio, near, far);
}

void BasicVisualizationTechnique::createMaterialsCmdLists()
{
   for (auto model : glscene->scene->models)
   {
      for (auto material : model->materials)
      {
         createMaterialCommandList(material.get());
      } // for material
   } // for model

}

void BasicVisualizationTechnique::createMeshesCmdLists()
{
   for (auto model : glscene->scene->models)
   {
      for (auto mesh : model->meshes)
      {
         createMeshCommandList(mesh.get());
      }
   }
}

void BasicVisualizationTechnique::createMeshCommandList(ge::sg::Mesh* mesh)
{
   if(processingHelper.meshMap.find(mesh) != processingHelper.meshMap.end()) return;

   std::shared_ptr<fsg::CommandList>  meshCmdList = std::make_shared<fsg::CommandList>();

   shared_ptr<ge::gl::VertexArrayObject> VAO(make_shared<ge::gl::VertexArray>());
   GLScene::GLAttribArray& aa = getOrCreateGLAttribArray(mesh);
   for(auto glattribute : aa)
   {

      if(glattribute.attributeDescriptor->semantic == idofstring(AttributeDescriptor::Semantic, StandardSemanticNames::indices))
      {
         VAO->addElementBuffer(glattribute.BO.get());
      }
      else
      {
         GLuint attribPosition = this->semantic2Attribute(glattribute.attributeDescriptor->semantic);
         if(attribPosition != ge::core::EnumRegister::notRegistered)
         {
            VAO->addAttrib(glattribute.BO.get(), attribPosition, glattribute.attributeDescriptor->numComponents, translateEnum(glattribute.attributeDescriptor->type), (GLsizei)glattribute.attributeDescriptor->stride);
         }
      }
   }

   //meshCmdList->emplace_back(std::make_shared<VAOChecker>(VAO->getId() ) );
   VAOConatainer.push_back(VAO);
   VAO->bind();
   gl->gldra
   meshCmdList->emplace_back(std::make_shared<ge::gl::BindVertexArray<GLuint>>(VAO->getId()));
   meshCmdList->emplace_back(std::make_shared<ge::gl::DrawElements<GLenum, GLsizei, GLenum, const void*>>(translateEnum(mesh->primitive), (GLsizei)mesh->count, GL_UNSIGNED_INT, nullptr));
   meshCmdList->emplace_back(std::make_shared<ge::gl::BindVertexArray<GLuint>>(0));

   processingHelper.meshMap[mesh] = meshCmdList;
}

void BasicVisualizationTechnique::createMaterialCommandList(ge::sg::Material* material)
{
   if(processingHelper.materialMap.find(material) != processingHelper.materialMap.end()) return;

   std::shared_ptr<fsg::CommandList> materialCommandList(std::make_shared<fsg::CommandList>());
   GLuint effect_mask = NONE;
   for(auto materialComponent : material->materialComponents)
   {
      if(materialComponent->getType() == ge::sg::MaterialComponent::ComponentType::SIMPLE)
      {
         ge::sg::MaterialSimpleComponent* simpleComp = static_cast<ge::sg::MaterialSimpleComponent*>(materialComponent.get());
         if(simpleComp->semantic == MaterialSimpleComponent::semanticRegister.getValue(ge::core::StandardSemanticNames::ambientColor))
         {
            materialCommandList->emplace_back(std::make_shared<ge::gl::Uniform4fv<>>(phongProgram->getUniform("ambientMat").getLocation(), 1, reinterpret_cast<float*>(simpleComp->data)));
         }
         else if(simpleComp->semantic == MaterialSimpleComponent::semanticRegister.getValue(ge::core::StandardSemanticNames::diffuseColor))
         {
            materialCommandList->emplace_back(std::make_shared<ge::gl::Uniform4fv<>>(phongProgram->getUniform("diffuseMat").getLocation(), 1, reinterpret_cast<float*>(simpleComp->data)));
         }
         else if(simpleComp->semantic == MaterialSimpleComponent::semanticRegister.getValue(ge::core::StandardSemanticNames::shininess))
         {
            materialCommandList->emplace_back(std::make_shared<ge::gl::Uniform1fv<>>(phongProgram->getUniform("shininessMat").getLocation(), 1, reinterpret_cast<float*>(simpleComp->data)));
         }
      }
      else if(materialComponent->getType() == ge::sg::MaterialComponent::ComponentType::IMAGE)
      {
         ge::sg::MaterialImageComponent * imageComp = static_cast<ge::sg::MaterialImageComponent*>(materialComponent.get());
         if(imageComp->semantic == MaterialSimpleComponent::semanticRegister.getValue(ge::core::StandardSemanticNames::ambientTexture))
         {
         }
         else if(imageComp->semantic == MaterialSimpleComponent::semanticRegister.getValue(ge::core::StandardSemanticNames::diffuseTexture))
         {

            std::shared_ptr<ge::gl::TextureObject> texture = getOrCreateTexture(imageComp);
            materialCommandList->emplace_back(std::make_shared<fsg::BindTexture>(0, texture));
            effect_mask |= DIFF_TEX;
            //maybe we should send sampler as uniform 1ui
         }
         else if(imageComp->semantic == MaterialSimpleComponent::semanticRegister.getValue(ge::core::StandardSemanticNames::specularTexture))
         {
         }
         else if(imageComp->semantic == MaterialSimpleComponent::semanticRegister.getValue(ge::core::StandardSemanticNames::emissiveTexture))
         {
         }
         else if(imageComp->semantic == MaterialSimpleComponent::semanticRegister.getValue(ge::core::StandardSemanticNames::normalTexture))
         {
         }
      }
   } //for material component
   materialCommandList->emplace_back(std::make_shared<ge::gl::Uniform1ui<>>(phongProgram->getUniform("effect_mask").getLocation(), effect_mask));
   processingHelper.materialMap[material] = materialCommandList;
}

std::shared_ptr<ge::gl::TextureObject> BasicVisualizationTechnique::getOrCreateTexture(MaterialImageComponent* img)
{
   std::shared_ptr<ge::gl::TextureObject> texture;
   auto texit = glscene->textures.find(img);
   if(texit == glscene->textures.end())
   {
      cerr << "Basic VT: texture not loaded!\n";
      texture = make_shared<ge::gl::TextureObject>(GL_TEXTURE_2D, GL_RGBA8, 1, (GLsizei)img->image->getWidth(), (GLsizei)img->image->getHeight());
      glscene->textures[img] = texture;
   }
   else
   {
      texture = texit->second;
   }

   return texture;
}

ge::glsg::GLScene::GLAttribArray& BasicVisualizationTechnique::getOrCreateGLAttribArray(Mesh* mesh)
{
   
   auto attit = glscene->GLMeshes.find(mesh);
   if(attit == glscene->GLMeshes.end())
   {
      cerr << "Basic VT: GL attribute not created!\n";
      ge::glsg::GLScene::GLAttribArray attribAray;
      for(auto attribute : mesh->attributes)
      {
         shared_ptr<ge::gl::BufferObject > buff(make_shared<ge::gl::BufferObject>(attribute->size, (char*)(attribute->data.get()) + attribute->offset));
         attribAray.emplace_back(attribute, buff);
      }
      glscene->GLMeshes[mesh] = attribAray;
   }

   //can't use iterator because it could point to an end()
   //can't use attribAray ref because it will be deleted at the end of this function
   return glscene->GLMeshes[mesh];
}

GLuint BasicVisualizationTechnique::semantic2Attribute(AttributeDescriptor::Semantic semantic)
{
   if(semantic == idofstring(AttributeDescriptor::Semantic, StandardSemanticNames::position))
      return 0;
   else if(semantic == idofstring(AttributeDescriptor::Semantic, StandardSemanticNames::normal))
      return 1;
   else if(semantic == idofstring(AttributeDescriptor::Semantic, StandardSemanticNames::texcoord))
      return 2;
   //return not registered if attribute is not used with this VT
   return ge::core::EnumRegister::notRegistered;
}