#pragma once

#include <VisualizationTechnique.h>
#include <geSG/AttributeDescriptor.h>
#include <geGL/Generated/OpenGLTypes.h>

#include <memory>
#include <unordered_map>


namespace ge
{
   namespace gl
   {
      class Texture;
      class Context;
      class VertexArray;
      class Program;
   }
   namespace sg {
      class Scene;
   }
   namespace glsg
   {
      class GLScene;
   }
}

namespace fsg
{
   /**
    * This VT is used to simply draw a textured object. It only uses positions and normals.
    * The shaders needs vertices vec3 on 0 and texcoords vec2 on 2 position. You can inspect
    * the shaders in resource directory of this example.
    * The usage of the VT is to supply the GLScene, then call the processScene. Once this is done
    * you can call drawSetup and draw each frame. You need to have OpenGL context <b>active</b>.
    */
   class SimpleVT : public VisualizationTechnique
   {
   public:
      virtual void setScene(std::shared_ptr<ge::glsg::GLScene>& scene);
      virtual void processScene();
      void drawSetup() override;
      void draw() override;

      static int semantic2Attribute(ge::sg::AttributeDescriptor::Semantic semantic);

      std::shared_ptr<ge::gl::Context> gl;
      std::shared_ptr<ge::gl::Program> program;

   protected:
      std::shared_ptr<ge::glsg::GLScene> glscene;
      std::unordered_map<ge::sg::Mesh*, std::shared_ptr<ge::gl::VertexArray>> VAOContainer;
      std::unordered_map<ge::sg::Material*, std::unique_ptr<unsigned char[]>> colorContainer;
      std::unordered_map<ge::sg::Mesh*, std::shared_ptr<ge::gl::Texture>> diffuseTextureConatiner;

   };
}