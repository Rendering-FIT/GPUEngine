#include <glsg/GLSceneProcessor.h>

#include <glsg/GLScene.h>
#include <glsg/GLAttribute.h>
#include <glsg/EnumToGL.h>
#include <geSG/Scene.h>
#include <geSG/AttributeDescriptor.h>
#include <geGL/Buffer.h>
#include <geSG/Image.h>
#include <geSG/DefaultImage.h>
#include <geGL/Texture.h>

using namespace ge::glsg;
using namespace ge::sg;
using namespace ge::gl;
using namespace std;

GLSceneProcessor::GLSceneProcessor(std::shared_ptr<ge::gl::Context> context)
   : _glscene(nullptr)
   , _textureFactory(make_shared<DefaultTextureFactory>())
   , _context(context)
{
   if(!context) _context = ge::gl::getDefaultContext();
}

void GLSceneProcessor::process(std::shared_ptr<ge::sg::Scene> scene)
{
   _glscene = make_shared<GLScene>();
   processMeshes(scene, _glscene, _context);
   createTextures(scene, _glscene, _context, _textureFactory);
   _glscene->scene = scene;
}

std::shared_ptr<ge::glsg::GLScene> GLSceneProcessor::processScene(std::shared_ptr<ge::sg::Scene> scene, std::shared_ptr<ge::gl::Context> context, std::shared_ptr<TextureFactory> textureFactory)
{
   shared_ptr<GLScene> glscene(make_shared<GLScene>());
   processMeshes(scene, glscene, context);
   createTextures(scene, glscene, context, textureFactory);
   glscene->scene = scene;

   return glscene;
}

void GLSceneProcessor::processMeshes(std::shared_ptr<ge::sg::Scene>& scene, std::shared_ptr<ge::glsg::GLScene>& glscene, std::shared_ptr<ge::gl::Context> context)
{
   for(auto model : scene->models)
   {
      for(auto mesh : model->meshes)
      {
         glscene->GLMeshes[mesh.get()] = GLScene::GLAttribArray();
         for(auto attribute : mesh->attributes)
         {

            shared_ptr<ge::gl::Buffer> buff(make_shared<Buffer>(context->getFunctionTable(), attribute->size, (char*)(attribute->data.get()) + attribute->offset));
            glscene->GLMeshes[mesh.get()].emplace_back(attribute, buff);

         }
      }
   }
}

void GLSceneProcessor::createTextures(std::shared_ptr<Scene> scene, std::shared_ptr<GLScene> glscene, std::shared_ptr<ge::gl::Context> context, std::shared_ptr<TextureFactory> textureFactory)
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
               //if the image of MaterialImageComponent hasn't been created
               if(img && !img->image)
               {
                  img->image = make_shared<ge::sg::DefaultImage>();
               }
               glscene->textures[img] = textureFactory->create(img, context);
            }
         }
      }
   }
}

std::shared_ptr<ge::gl::Texture> DefaultTextureFactory::create(ge::sg::MaterialImageComponent* img, std::shared_ptr<ge::gl::Context>& context)
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
   shared_ptr<Texture> tex(make_shared<Texture>(context->getFunctionTable(),GL_TEXTURE_2D, GL_RGBA8, l, (GLsizei)img->image->getWidth(), (GLsizei)img->image->getHeight()));
   //copying data might not be needed
   context->glTextureSubImage2DEXT(tex->getId(), GL_TEXTURE_2D, 0, 0, 0, (GLsizei)img->image->getWidth(), (GLsizei)img->image->getHeight(), translateEnum(img->image->getFormat()), translateEnum(img->image->getDataType()), img->image->getBits());
   context->glGenerateTextureMipmap(tex->getId());
   context->glTextureParameteri(tex->getId(), GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   context->glTextureParameteri(tex->getId(), GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   return tex;
}