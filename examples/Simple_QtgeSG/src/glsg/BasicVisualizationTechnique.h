#pragma once

#include <types.h>
#include <VisualizationTechnique.h>
#include <geSG/Scene.h>
#include <geGL/Program.h>
#include <glsg/MatrixUniformCommands.h>
#include <glsg/GLScene.h>
#include <geUtil/MatrixStack.h>

#include <unordered_map>
#include <geGL/VertexArray.h>


namespace ge
{
   namespace glsg
   {
      class GLAttribute;

      class VAOChecker : public ge::core::Command
      {
      public:
         VAOChecker(GLuint id)
            : _id(id)
         {

         }

         virtual void operator()()
         {
            GLboolean check;
            check = gl->glIsVertexArray(_id);
            if(!check)
            {
               std::cerr << _id << " not VAO\n";
            }
         }

         std::shared_ptr<ge::gl::Context> gl;
         GLuint _id;
      };

      class BasicVisualizationTechnique : public fsg::CommandListVT
      {
      public:
         enum effect
         {
            NONE = 0,
            DIFF_TEX = 1,
         };

         BasicVisualizationTechnique();
         virtual void setInput(std::shared_ptr<ge::glsg::GLScene>& glscene);

         virtual void reset();
         virtual void process();
         virtual void processSingleMesh(ge::sg::Mesh* mesh) override;
         virtual void drawSetup() override;
         virtual void draw();

         virtual void applyMaterial(ge::sg::Material* material) override;
         virtual void applyMatrixTransform(const ge::sg::MatrixTransform& mt) override;
         virtual void drawMesh(ge::sg::Mesh* mesh) override;

         void initMatrixUniforms();

         void updatePerspective(float fovy, float aspectRatio, float near, float far);

         static GLuint semantic2Attribute(sg::AttributeDescriptor::Semantic semantic);

         std::shared_ptr<ge::gl::Program> phongProgram;
         std::shared_ptr<fsg::UniformMatrixGLMShared> prespectiveMatrixUniform;
         std::shared_ptr<fsg::UniformMatrixGLMShared> viewMatrixUniform;

      protected:
         void drawNode(std::shared_ptr<ge::sg::MatrixTransformNode> MTNode, ge::util::MatrixStack& matrix_stack);

         void createMaterialsCmdLists();
         void createMeshesCmdLists();

         std::shared_ptr<ge::glsg::GLScene> glscene;

         std::shared_ptr<fsg::UniformMatrixGLM> modelMatrixUniform;
         std::shared_ptr<fsg::UniformMatrixGLM> normalMatrixUniform;
         std::shared_ptr<fsg::Uniform4fGLM> sceneAmbientLight;

      private:
         struct ProcessingHelper
         {
            std::unordered_map<ge::sg::Material*, std::shared_ptr<fsg::CommandList>> materialMap;
            std::unordered_map<ge::sg::Mesh*, std::shared_ptr<fsg::CommandList>> meshMap;

            inline void reset()
            {
               materialMap.clear();
               materialMap.clear();
            }
         };

         void createMeshCommandList(ge::sg::Mesh* mesh);
         void createMaterialCommandList(ge::sg::Material* material);

         std::shared_ptr<ge::gl::Texture> getOrCreateTexture(sg::MaterialImageComponent *img);
         GLScene::GLAttribArray& getOrCreateGLAttribArray(sg::Mesh* mesh);

         ProcessingHelper processingHelper;
         std::vector<std::shared_ptr<ge::gl::VertexArray>> VAOConatainer;
      };
   }
}