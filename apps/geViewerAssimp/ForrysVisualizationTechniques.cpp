/*#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
namespace ge
{
   namespace core
   {
      template<typename TYPE>
      inline TYPE convertTo(glm::mat4& mat){
         return glm::value_ptr(mat);
      }

      template<typename TYPE>
      inline TYPE convertTo(std::shared_ptr<glm::mat4>& mat){
         return glm::value_ptr(*mat);
      }
   }
}*/

#include <geSG/MatrixTransform.h>
#include <geSG/Mesh.h>
#include <geSG/AttributeDescriptor.h>
#include <geGL/TextureObject.h>

#include <geGL/VertexArrayObject.h>
//#include <geUtil/algorithms.h>
#include <geCore/StandardSemanticsNames.h>

#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>

#include "ForrysVisualizationTechniques.h"
#include "ste/DAG.h"
#include "EnumToGL.h"
#include "GLCommands.h"
#include "MatrixUniformCommands.h"

using namespace ge::sg;

fsg::ForryPhongTechnique::ForryPhongTechnique()
   : VisualizationTechnique()
{

}

fsg::ForryPhongTechnique::ForryPhongTechnique(const ForryPhongTechnique& forryPhongTechnique)
   : VisualizationTechnique()
   , _matrixTransformNode(forryPhongTechnique._matrixTransformNode)
   , _viewMatrixU(forryPhongTechnique._viewMatrixU)
   //TBD make it done
{

}

fsg::ForryPhongTechnique::ForryPhongTechnique(std::shared_ptr<MatrixTransformNode>& matrixNode, std::shared_ptr<ge::gl::ProgramObject>& _phongProgram)
   : VisualizationTechnique()
   , phongProgram(_phongProgram)
   , _matrixTransformNode(matrixNode)
{
   _viewMatrixU = std::make_shared<UniformMatrixGLMShared>(phongProgram->getUniform("viewMatrix").getLocation(), 1, GL_FALSE, std::make_shared<glm::mat4>());
}

void fsg::ForryPhongTechnique::setInput(std::shared_ptr<MatrixTransformNode>& matrixNode)
{
   _matrixTransformNode = matrixNode;
}

void fsg::ForryPhongTechnique::process()
{
   ForryPhongTechnique::ProcessingHelper helper;
   helper.matrixStack.push_back(glm::translate(glm::mat4(), glm::vec3(0,0,0)));
   _renderGraphRoot = std::make_shared<RenderGraphNode>();
   //_materialCmdLists = std::make_shared<CommandLists>();

   processCurrentNode(_matrixTransformNode, _renderGraphRoot, helper);
   //processChildren(std::shared_ptr<MatrixTransformNode> &node);
}

void fsg::ForryPhongTechnique::processCurrentNode(std::shared_ptr<MatrixTransformNode> &node, std::shared_ptr<RenderGraphNode> &rendergraphNode, ProcessingHelper &helper )
{
   //rendergraphNode = std::make_shared<RenderGraphNode>();
   std::shared_ptr<glm::mat4>& currentMatrix = node->data->getRefMatrix();
   if(currentMatrix != nullptr)
   {
      std::vector<glm::mat4>::iterator back = helper.matrixStack.end() - 1;
      glm::mat4 mv = (*back) * (*currentMatrix);
      helper.matrixStack.push_back(mv);
   }
      

   if (!node->data->meshes.empty())
   {
      //process matrix!!!!
      /**
       * Matrices uniforms don't need to be referenced because the paths to the same
       * reference could be different.
       */
      glm::mat4 mv = helper.matrixStack.back();
      std::shared_ptr<glm::mat4> normalMat(std::make_shared<glm::mat4>(glm::transpose(glm::inverse(mv))));
      //std::shared_ptr<CommandList> matrixList(std::make_shared<CommandList>());
      std::shared_ptr<glm::mat4> mat = std::make_shared<glm::mat4>(mv);
      //fsg::UniformMatrix<4, 4, float, glm::mat4> MVP((ge::gl::ProgramObject*)NULL, "mvp",mat, 1, GL_FALSE);
      rendergraphNode->data.matrixCmdList->emplace_back(std::make_shared<fsg::UniformMatrixGLMShared>(phongProgram->getUniform("model").getLocation(), 1, GL_FALSE, mat));
      //rendergraphNode->data.matrixCmdList->push_back(matrixList->back());
      rendergraphNode->data.matrixCmdList->emplace_back(std::make_shared<fsg::UniformMatrixGLMShared>(phongProgram->getUniform("normalMatrix").getLocation(), 1, GL_FALSE, normalMat));

      //process meshes
      for(auto mesh : node->data->meshes)
      {
         //mesh command list
         auto meshIt = helper.meshMap.find(mesh.get());
         if ( meshIt == helper.meshMap.end())
         {
            //mesh command list not found, create one
            _meshCmdLists.push_back(createMeshCommandList(mesh.get()));
            rendergraphNode->data.meshCmdList.push_back(_meshCmdLists.back());
            helper.meshMap[mesh.get()] = _meshCmdLists.back();
         }
         else
         {
            rendergraphNode->data.meshCmdList.push_back(meshIt->second);
         }

         //material command list
         auto matIt = helper.materialMap.find(mesh->material.get());
         if (matIt == helper.materialMap.end())
         {
            //create new one
            _materialCmdLists.push_back(createMaterialCommandList(mesh->material.get()));
            rendergraphNode->data.materialCmdList.push_back(_materialCmdLists.back());
            helper.materialMap[mesh->material.get()] = _materialCmdLists.back();
         } 
         else
         {
            rendergraphNode->data.materialCmdList.push_back(matIt->second);
         }
      }
   }

   //process children

   for (auto childNode : node->children)
   {
      rendergraphNode->children.emplace_back(std::make_shared<RenderGraphNode>());
      processCurrentNode(childNode, rendergraphNode->children.back(), helper);
   }
      

   //pop matrix
   if(currentMatrix != nullptr)
   {
      helper.matrixStack.pop_back();
   }
   

}

std::shared_ptr<fsg::CommandList> fsg::ForryPhongTechnique::createMeshCommandList(Mesh *mesh)
{
   std::shared_ptr<fsg::CommandList>  meshCmdList = std::make_shared<fsg::CommandList>();

   //////////////////////////////////////////////////////////////////////////
   /* !!!!!Need something to manage this VAO - and delete it after the app ends!!!!!!*/
   //////////////////////////////////////////////////////////////////////////

   ge::gl::VertexArrayObject *VAO = new ge::gl::VertexArrayObject;
   for(auto attribute : mesh->attributes)
   {

      ge::gl::BufferObject *buff = new ge::gl::BufferObject(attribute->size, (char*)(attribute->data.get()) + attribute->offset);
      if(attribute->semantic == AttributeDescriptor::semanticRegister.getValue(ge::core::StandardSemanticNames::indices))
      {
         VAO->addElementBuffer(buff);
      }
      else
      {
         VAO->addAttrib(buff, fsg::semnatic2Attribute(attribute->semantic), attribute->numComponents, fsg::translateEnum(attribute->type), attribute->stride);
      }
   }
   meshCmdList->emplace_back(std::make_shared<ge::gl::BindVertexArray<GLuint>>(VAO->getId()));

   meshCmdList->emplace_back(std::make_shared<ge::gl::DrawElements<GLenum, GLsizei, GLenum, const void*>>(translateEnum(mesh->primitive),mesh->count, GL_UNSIGNED_INT, nullptr));

   return meshCmdList;
}

std::shared_ptr<fsg::CommandList> fsg::ForryPhongTechnique::createMaterialCommandList(Material* material)
{
   std::shared_ptr<CommandList> materialCommandList = std::make_shared<CommandList>();
   for(auto materialComponent : material->materialComponents)
   {
      if(materialComponent->getType() == ge::sg::MaterialComponent::ComponentType::SIMPLE)
      {
         ge::sg::MaterialSimpleComponent* simpleComp = static_cast<ge::sg::MaterialSimpleComponent*>(materialComponent.get());
         if(simpleComp->semantic == MaterialSimpleComponent::semanticRegister.getValue(ge::core::StandardSemanticNames::ambientColor))
         {
            //ge::gl::UniformV<4, float> *ambient = new ge::gl::UniformV<4, float>(program, "ambientMat", (float*)(simpleComp->data));
            //materialCommandList->add(ambient);
            materialCommandList->emplace_back(std::make_shared<ge::gl::Uniform4fv<>>(phongProgram->getUniform("ambientMat").getLocation(), 1, reinterpret_cast<float*>(simpleComp->data)));
         }
         else if(simpleComp->semantic == MaterialSimpleComponent::semanticRegister.getValue(ge::core::StandardSemanticNames::diffuseColor))
         {
            //ge::gl::UniformV<4, float> *diffuse = new ge::gl::UniformV<4, float>(program, "diffuseMat", (float*)(simpleComp->data));
            //materialCommandList->add(diffuse);
            materialCommandList->emplace_back(std::make_shared<ge::gl::Uniform4fv<>>(phongProgram->getUniform("diffuseMat").getLocation(), 1, reinterpret_cast<float*>(simpleComp->data)));
         }
         else if(simpleComp->semantic == MaterialSimpleComponent::semanticRegister.getValue(ge::core::StandardSemanticNames::shininess))
         {
            //ge::gl::UniformV<1, float> *shininess = new ge::gl::UniformV<1, float>(program, "shininessMat", (float*)(simpleComp->data));
            //materialCommandList->add(shininess);
            materialCommandList->emplace_back(std::make_shared<ge::gl::Uniform1fv<>>(phongProgram->getUniform("shininessMat").getLocation(), 1, reinterpret_cast<float*>(simpleComp->data)));
         }
      }
      else if(materialComponent->getType() == ge::sg::MaterialComponent::ComponentType::IMAGE)
      {
         ge::sg::MaterialImageComponent * imageComp = static_cast<ge::sg::MaterialImageComponent*>(materialComponent.get());
         if(imageComp->semantic == MaterialImageComponent::semanticRegister.getValue(ge::core::StandardSemanticNames::ambientTexture))
         {
         }
         else if(imageComp->semantic == MaterialImageComponent::semanticRegister.getValue(ge::core::StandardSemanticNames::diffuseTexture))
         {
            std::shared_ptr<ge::gl::TextureObject> texture(std::make_shared<ge::gl::TextureObject>(GL_TEXTURE_2D, GL_RGBA8, 1, imageComp->image->getWidth(), imageComp->image->getHeight()));
            glTextureSubImage2DEXT(texture->getId(), GL_TEXTURE_2D, 0, 0, 0, imageComp->image->getWidth(), imageComp->image->getHeight(), translateEnum(imageComp->image->getFormat()), translateEnum(imageComp->image->getDataType()), imageComp->image->getBits());
            //std::shared_ptr<ge::gl::BindTexture> bindTexCmd(std::make_shared<ge::gl::BindTexture>(texture,0));
            materialCommandList->emplace_back(std::make_shared<fsg::BindTexture>(0,texture));
            //maybe we should send sampler as uniform 1ui
         }
         else if(imageComp->semantic == MaterialImageComponent::semanticRegister.getValue(ge::core::StandardSemanticNames::specularTexture))
         {
         }
         else if(imageComp->semantic == MaterialImageComponent::semanticRegister.getValue(ge::core::StandardSemanticNames::emissiveTexture))
         {
         }
         else if(imageComp->semantic == MaterialImageComponent::semanticRegister.getValue(ge::core::StandardSemanticNames::normalTexture))
         {
         }
      }
   }

   return materialCommandList;
}

/**
 * Draws its rendergraph. Rendergraph is created from MatrixTransform subgraph
 * by calling process() method.
 */
void fsg::ForryPhongTechnique::draw()
{
   if(_renderGraphRoot == nullptr) return;

   phongProgram->use();
   (*_viewMatrixU)();
   drawNode(_renderGraphRoot);
}

void fsg::ForryPhongTechnique::drawNode(std::shared_ptr<RenderGraphNode>& renderGraphNode)
{
   //draw inner (node)
   //ge::util::apply(renderGraphNode->data.matrixCmdList->begin(), renderGraphNode->data.matrixCmdList->end());
   std::for_each(renderGraphNode->data.matrixCmdList->begin(), renderGraphNode->data.matrixCmdList->end(), [](std::shared_ptr<ge::core::Command>& x){ (*x)(); });
   auto meshIt = renderGraphNode->data.meshCmdList.begin();
   auto matIt = renderGraphNode->data.materialCmdList.begin();
   while(meshIt != renderGraphNode->data.meshCmdList.end() || matIt != renderGraphNode->data.materialCmdList.end())
   {
      // two* because these are iterators to shared_ptr<>. One * to dereference iterator and second for dereferencing the shared pointer
      std::for_each((**matIt).begin(), (**matIt).end(), [](std::shared_ptr<ge::core::Command>& x){ (*x)(); });
      std::for_each((**meshIt).begin(), (**meshIt).end(), [](std::shared_ptr<ge::core::Command>& x){ (*x)(); });
      //mesh command list has draw command at its end see process node - mesh part
      ++meshIt;
      ++matIt;
   }

   //process children
   for(auto child : renderGraphNode->children)
   {
      drawNode(child);
   }

}

std::shared_ptr<glm::mat4>& fsg::ForryPhongTechnique::getViewMatrixRef()
{
   return _viewMatrixU->value;
}
