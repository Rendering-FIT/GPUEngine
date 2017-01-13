#include <SimpleVT.h>

#include <glsg/GLScene.h>
#include <geSG/Material.h>
#include <geGL/VertexArray.h>
#include <geGL/Texture.h>
#include <glsg/EnumToGL.h>
#include <geGL/geGL.h>

using namespace std;
using namespace fsg;
using namespace ge::gl;
using namespace ge::sg;
using namespace ge::glsg;

/**
 * Sets the scene to visualize.
 * \param scene GLScene to visualize.
 */
void fsg::SimpleVT::setScene(std::shared_ptr<ge::glsg::GLScene>& scene)
{
   glscene = scene;
}

/**
 * Creates VAOs, preps uniforms and textures that the VT needs for visualization.
 */
void fsg::SimpleVT::processScene()
{
   for(auto& meshIt: glscene->GLMeshes)
   {
      //mesh geometry
      shared_ptr<VertexArray> VAO = make_shared<VertexArray>(gl->getFunctionTable());
      for(auto& glattrib: meshIt.second)
      {
         if(glattrib.attributeDescriptor->semantic == AttributeDescriptor::Semantic::indices)
         {
            VAO->addElementBuffer(glattrib.BO);
         }
         else
         {
            int attribLocation = semantic2Attribute(glattrib.attributeDescriptor->semantic);
            if(attribLocation != -1)
            {
               VAO->addAttrib(glattrib.BO, attribLocation, glattrib.attributeDescriptor->numComponents, translateEnum(glattrib.attributeDescriptor->type), (GLsizei)glattrib.attributeDescriptor->stride);
            }
         }
      }
      VAOContainer[meshIt.first] = VAO;

      //material
      Material * mat = meshIt.first->material.get();

      //one way to get the component you want but the more frequently used way is bellow
      auto component = mat->getComponent<MaterialSimpleComponent>(MaterialSimpleComponent::Semantic::diffuseColor);
      if(component)
      {
         unsigned sizeinbytes = component->size * component->getSize(component->dataType);
         colorContainer[mat] = make_unique<unsigned char[]>(sizeinbytes);
         //memcpy(colorContainer[mat].get(), component->data.get(), sizeinbytes); //this is the same as below but less general
         std::copy_n(component->data.get(), sizeinbytes, colorContainer[mat].get());
      }

      for(auto& comp: mat->materialComponents)
      {
         if(comp->getType() == MaterialComponent::ComponentType::IMAGE)
         {
            auto imageComponent = static_cast<MaterialImageComponent*>(comp.get());
            diffuseTextureConatiner[meshIt.first] = glscene->textures[imageComponent];
         }
      }
   }
} 

/**
 * Currently does nothing.
 */
void SimpleVT::drawSetup()
{
}

/**
 * Use provided shader and draws the provided scene.
 */
void SimpleVT::draw()
{
   program->use();
   if(!glscene) return;
   for(auto& meshIt : glscene->GLMeshes)
   {
      Mesh* mesh = meshIt.first;
      program->set4fv("color", reinterpret_cast<const float*>(colorContainer[mesh->material.get()].get()));
      
      Texture *texture = diffuseTextureConatiner[meshIt.first].get();
      texture->bind(0);

      VertexArray * VAO = VAOContainer[mesh].get();
      VAO->bind();
      gl->glDrawElements(translateEnum(mesh->primitive), mesh->count, translateEnum(mesh->getAttribute(AttributeDescriptor::Semantic::indices)->type), 0);
      VAO->unbind();
   }
}

/**
 * Internal helper function that returns attribute position for given semantic or -1
 * if the attrib is not to be used by this VT.
 */
int SimpleVT::semantic2Attribute(AttributeDescriptor::Semantic semantic)
{
   switch (semantic)
   {
      case AttributeDescriptor::Semantic::position: return 0;
      case AttributeDescriptor::Semantic::texcoord: return 2;
      default: return -1;
   }
}
