#pragma once

#include <map>
#include <vector>

#include <geSG/Node.h>
#include <geSG/MatrixTransform.h>

#include <geGL/OpenGL.h>
//#include <geCore/Command.h>
#include <geGL/OpenGLCommands.h>

//#include <DAG.h>

#include "VisualizationTechnique.h"
#include "MatrixUniformCommands.h"

namespace ge
{
   namespace gl
   {
      class ProgramObject;
   }
   namespace sg
   {
      class Material;
   }
}

namespace fsg
{

   typedef std::vector<std::shared_ptr<ge::core::Command>> CommandList;
   typedef std::vector<std::shared_ptr<CommandList>> CommandLists;
   

   class ForryPhongTechnique : public VisualizationTechnique
   {
   public:
      ForryPhongTechnique();
      ForryPhongTechnique(const ForryPhongTechnique& forryPhongTechnique);
      ForryPhongTechnique(std::shared_ptr<ge::sg::MatrixTransformNode>& matrixNode, std::shared_ptr<ge::gl::ProgramObject>& _phongProgram);

      virtual void setInput(std::shared_ptr<ge::sg::MatrixTransformNode>& matrixNode);
      //virtual void setOutput(Texture * tex); // set texture for technique output or NULL for default framebuffer
      virtual void process();
      //virtual void operator()();
      virtual void draw();

      virtual std::shared_ptr<glm::mat4>& getViewMatrixRef();

      inline void setDirty(bool dirty = true){ _dirty = dirty; }
      inline bool isDirty(){ return _dirty; }

      struct RenderGraphData
      {
         RenderGraphData()
            : matrixCmdList(std::make_shared<CommandList>())
         {}

         CommandLists materialCmdList;
         CommandLists meshCmdList;
         std::shared_ptr<CommandList> matrixCmdList;
      };
      typedef ste::Node<RenderGraphData> RenderGraphNode;


   protected:
      bool _dirty;
      std::shared_ptr<ge::gl::ProgramObject> phongProgram;
      std::shared_ptr<ge::sg::MatrixTransformNode> _matrixTransformNode;
      //there should be immediate structure used for rendering e.g. commands or render graph
      std::vector<std::shared_ptr<ge::core::Command>> _commandList;
      CommandLists _materialCmdLists;
      CommandLists _meshCmdLists;
      CommandLists _matrixCmdLists;
      std::shared_ptr<RenderGraphNode> _renderGraphRoot;

      //std::shared_ptr<UniformMatrix<4, 4, float, glm::mat4>> _viewMatrixU;
      std::shared_ptr<UniformMatrixGLMShared> _viewMatrixU;

   private:
      struct ProcessingHelper;
      std::shared_ptr<fsg::CommandList> createMeshCommandList(ge::sg::Mesh *mesh);
      std::shared_ptr<fsg::CommandList> createMaterialCommandList(ge::sg::Material* material);
      void processCurrentNode(std::shared_ptr<ge::sg::MatrixTransformNode> &node, std::shared_ptr<RenderGraphNode> &rendergraphNode, ProcessingHelper &helper);
      void drawNode(std::shared_ptr<RenderGraphNode>& renderGraphNode);
      struct ProcessingHelper
      {
         std::map<ge::sg::Material*, std::shared_ptr<CommandList>> materialMap;
         std::map<ge::sg::Mesh*, std::shared_ptr<CommandList>> meshMap;
         std::vector<glm::mat4> matrixStack;
      };
   };

} //namespace fsg
