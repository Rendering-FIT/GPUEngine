#pragma once
#include "app.h"

#include <geRG/RenderingContext.h>
#include <geGL/Program.h>

class AppRG : public App {
public:
	AppRG(Options const& o = Options());

	virtual void init();
	virtual void draw();
private:
	void prepareRgContext();


  // Materials
  void createTextures();
  std::shared_ptr<ge::rg::StateSet> createStateSet(std::shared_ptr<ge::gl::Texture> tex);
  void createStateSets();

  std::vector<std::shared_ptr<ge::gl::Texture>> textures;
  std::vector<std::shared_ptr<ge::rg::StateSet>> texStateSets;
  std::shared_ptr<ge::rg::StateSet> whiteStateSet;

  // state init
  virtual void interactive(int cubes, int textures, DrawMode mode);
  virtual void calibrate(int cubes, int textures, DrawMode mode);
  virtual void test(int cubes, int textures, DrawMode mode);

  virtual void addCubes(int count);
  
  // mesh
  std::shared_ptr<ge::rg::Mesh> createMesh();
  void prepareDrawables();
  void clear();
  
  std::shared_ptr<ge::rg::Mesh> mesh;
  std::vector<ge::rg::DrawableId> drawables;

  // transforms
  std::shared_ptr<ge::rg::Transformation> createTransform(int id);
  virtual void recomputeMatrices(int count);

  std::vector<std::shared_ptr<ge::rg::Transformation>> transforms;
  std::shared_ptr<ge::rg::Transformation> cameraTransformation;
	
	// context
	std::shared_ptr<ge::rg::RenderingContext> context;
	std::shared_ptr<ge::gl::Program> program;
	
};
