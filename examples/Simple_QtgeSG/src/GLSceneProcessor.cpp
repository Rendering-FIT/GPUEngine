#include <glsg/GLSceneProcessor.h>

#include <glsg/GLScene.h>
#include <glsg/GLAttribute.h>
#include <glsg/EnumToGL.h>
#include <geSG/Scene.h>
#include <geSG/AttributeDescriptor.h>
#include <geGL/BufferObject.h>
#include <geSG/Image.h>
#include <geGL/TextureObject.h>

using namespace ge::glsg;
using namespace ge::sg;
using namespace ge::gl;
using namespace std;

GLSceneProcessor::GLSceneProcessor()
   : _glscene(nullptr)
   , _textureFactory(make_shared<DefaultTextureFactory>())
{
}

void GLSceneProcessor::process(std::shared_ptr<ge::sg::Scene> scene)
{
   _glscene = make_shared<GLScene>();
   processMeshes(scene, _glscene);
   createTextures(scene, _glscene, _textureFactory);
   _glscene->scene = scene;
}

std::shared_ptr<ge::glsg::GLScene> GLSceneProcessor::processScene(std::shared_ptr<ge::sg::Scene> scene, std::shared_ptr<TextureFactory> textureFactory)
{
   shared_ptr<GLScene> glscene(make_shared<GLScene>());
   processMeshes(scene, glscene);
   createTextures(scene, glscene, textureFactory);
   glscene->scene = scene;

   return glscene;
}

void GLSceneProcessor::processMeshes(std::shared_ptr<ge::sg::Scene>& scene, std::shared_ptr<ge::glsg::GLScene>& glscene)
{
   for(auto model : scene->models)
   {
      for(auto mesh : model->meshes)
      {
         glscene->GLMeshes[mesh.get()] = GLScene::GLAttribArray();
         for(auto attribute : mesh->attributes)
         {

            shared_ptr<ge::gl::BufferObject> buff(make_shared<BufferObject>(attribute->size, (char*)(attribute->data.get()) + attribute->offset));
            glscene->GLMeshes[mesh.get()].emplace_back(attribute, buff);

         }
      }
   }
}

void GLSceneProcessor::createTextures(std::shared_ptr<Scene> scene, std::shared_ptr<GLScene> glscene, std::shared_ptr<TextureFactory> textureFactory)
{
   for(auto model : scene->models)
   {
      for(auto material : model->materials)
      {
         //continue if we already processed this material
         for(auto materialComponent : material->materialComponents)
         {
            if(materialComponent->getType() == ge::sg::MaterialComponent::ComponentType::IMAGE)
            {
               MaterialImageComponent *img = static_cast<MaterialImageComponent*>(materialComponent.get());
               glscene->textures[img] = textureFactory->create(img);
            }
         }
      }
   }
}

std::shared_ptr<ge::gl::TextureObject> DefaultTextureFactory::create(ge::sg::MaterialImageComponent* img)
{
   int w = (int)img->image->getWidth();
   int h = (int)img->image->getHeight();
   int l = 0;
   while(h > 0 || w > 0)
   {
      h >>= 1;
      w >>= 1;
      ++l;
   }
   shared_ptr<TextureObject> tex(make_shared<TextureObject>(GL_TEXTURE_2D, GL_RGBA8, l, (GLsizei)img->image->getWidth(), (GLsizei)img->image->getHeight()));
   //copying data might not be needed
   glTextureSubImage2DEXT(tex->getId(), GL_TEXTURE_2D, 0, 0, 0, (GLsizei)img->image->getWidth(), (GLsizei)img->image->getHeight(), translateEnum(img->image->getFormat()), translateEnum(img->image->getDataType()), img->image->getBits());
   glGenerateTextureMipmap(tex->getId());
   glTextureParameteri(tex->getId(), GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTextureParameteri(tex->getId(), GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   return tex;
}