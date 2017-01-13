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
   class VisualizationTechnique
   {
   public:
      virtual void drawSetup() = 0;
      virtual void draw() = 0;

      virtual ~VisualizationTechnique()
      {
      }
   };

   class CommandListVT : public VisualizationTechnique
   {
   public:
      virtual void processSingleMesh(ge::sg::Mesh* mesh) = 0;
      virtual void applyMaterial(ge::sg::Material* material) = 0;
      virtual void applyMatrixTransform(const ge::sg::MatrixTransform& mt) = 0;
      virtual void drawMesh(ge::sg::Mesh* mesh) = 0;
   };
}