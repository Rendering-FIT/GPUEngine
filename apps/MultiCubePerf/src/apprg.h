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
	void prepareTextures();
	std::shared_ptr<ge::rg::Mesh> createMesh();
	std::shared_ptr<ge::rg::Transformation> createTransform(int id);
	std::shared_ptr<ge::rg::StateSet> createStateSet(int id);
	void prepareDrawables();
	virtual void recomputeMatrices(int count);

	std::shared_ptr<ge::rg::RenderingContext> context;
	std::shared_ptr<ge::gl::Program> program;

	std::shared_ptr<ge::rg::Mesh> meshAllCubes;
	std::shared_ptr<ge::rg::MatrixList> matrixList;
	std::shared_ptr<ge::rg::StateSet> material;
	

	std::shared_ptr<ge::rg::Transformation> cameraTransformation;
	std::vector<std::shared_ptr<ge::rg::Transformation>> trVector;
	std::vector<std::shared_ptr<ge::rg::StateSet>> ssVector;
};