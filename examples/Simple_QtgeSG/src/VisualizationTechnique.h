#pragma once

namespace ge{
   namespace sg{
      class MatrixTransform;
      class Material;
      class Mesh;
   }
}

namespace fsg
{
   /**
    * Base class for Visualization techniques (VT). VTs are used to visualize something, mainly
    * the scene graph or some part of scene in some user pre defined way. VT could stand for visualizing
    * the ge::sg::Scene (or some processed variation such as ge::glsg::GLScene) via phong shading. It could
    * be use to render skybox without even knowing the scene etc.
    * The VTs are the corner stones of visualization. The rendering part of frame should be a sequence of
    * VT::draw() calls.
    */
   class VisualizationTechnique
   {
   public:
      virtual void drawSetup() = 0;
      virtual void draw() = 0;

      virtual ~VisualizationTechnique()
      {
      }
   };

   /**
    * Not usable yet - no commands.
    */
   class CommandListVT : public VisualizationTechnique
   {
   public:
      virtual void processSingleMesh(ge::sg::Mesh* mesh) = 0;
      virtual void applyMaterial(ge::sg::Material* material) = 0;
      virtual void applyMatrixTransform(const ge::sg::MatrixTransform& mt) = 0;
      virtual void drawMesh(ge::sg::Mesh* mesh) = 0;
   };
}