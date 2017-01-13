#pragma once

#include <memory>

namespace ge
{
   namespace gl{
      class Texture;
      class Context;
   }

   namespace sg
   {
      class MaterialImageComponent;
      class Scene;
      class Mesh;
   }

   namespace glsg
   {
      class GLScene;
   }
}

namespace ge
{
   namespace glsg
   {
      /**
       * Base class for texture factory.
       */
      class TextureFactory
      {
      public:
         /**
          * This function is called with active OpenGL context when the GLSceneProcessor processes
          * MaterialImageComponent.
          */
         virtual std::shared_ptr<ge::gl::Texture> create(ge::sg::MaterialImageComponent* img, std::shared_ptr<ge::gl::Context>& context) = 0;
      };

      /**
       * Used when no custom factory is provided by user. It will generate RGBA8 texture with mipmaps and set min filter to
       * GL_LINEAR_MIPMAP_LINEAR and mag filter to GL_LINEAR
       */
      class DefaultTextureFactory : public TextureFactory
      {
         virtual std::shared_ptr<ge::gl::Texture> create(ge::sg::MaterialImageComponent* img, std::shared_ptr<ge::gl::Context>& context);
      };

      /**
       * Class that creates and initializes the GLScene class. It creates BO for every AttributeDescriptor
       * And TextureObject for every MaterialImageComponent. OpenGL context needs to be ACTIVE before you
       * call process(). You can also supply a custom TextureFactory object to supervise texture and sampler
       * creation.
       */
      class GLSceneProcessor
      {
      public:
         GLSceneProcessor(std::shared_ptr<ge::gl::Context> context = nullptr);

         void process(std::shared_ptr<ge::sg::Scene> scene);
         static std::shared_ptr<ge::glsg::GLScene> processScene(std::shared_ptr<ge::sg::Scene> scene, std::shared_ptr<ge::gl::Context> context, std::shared_ptr<TextureFactory> textureFactory = std::shared_ptr<DefaultTextureFactory>(std::make_shared<DefaultTextureFactory>()));


      protected:
         std::shared_ptr<ge::glsg::GLScene> _glscene;
         std::shared_ptr<TextureFactory> _textureFactory;
         std::shared_ptr<ge::gl::Context> _context;

      private:
         static void processMeshes(std::shared_ptr<ge::sg::Scene>& scene, std::shared_ptr<ge::glsg::GLScene>& glscene, std::shared_ptr<ge::gl::Context> context);
         //static void createGLAttribs(ge::sg::Mesh* mesh, std::shared_ptr<ge::glsg::GLScene>& glscene);
         static void createTextures(std::shared_ptr<sg::Scene> scene, std::shared_ptr<GLScene> glscene, std::shared_ptr<ge::gl::Context> context, std::shared_ptr<TextureFactory> textureFactory);
      };
   }

}