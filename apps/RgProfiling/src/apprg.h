#pragma once
#include "app.h"

#include "ProfilingContext.h"
#include <geGL/Program.h>

class AppRG : public App {
public:
	AppRG();

	virtual void init();
	virtual void draw();
private:
	void createContext();

  // Materials
  std::shared_ptr<ge::rg::StateSet> createStateSet();
  std::shared_ptr<ge::rg::StateSet> whiteStateSet;

  void addCubes(int count);
  void removeCubes(int count);
  
  // mesh
  std::shared_ptr<ge::rg::Mesh> createMesh();
  
  std::shared_ptr<ge::rg::Mesh> mesh;
  std::vector<ge::rg::DrawableId> drawables;

  // transforms
  std::shared_ptr<ge::rg::Transformation> createTransform(int id);

  std::vector<std::shared_ptr<ge::rg::Transformation>> transforms;
  std::shared_ptr<ge::rg::Transformation> cameraTransformation;
	
	// context
	std::shared_ptr<ProfilingContext> context;
	std::shared_ptr<ge::gl::Program> program;
	
};
