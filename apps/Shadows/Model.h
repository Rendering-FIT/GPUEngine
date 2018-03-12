#pragma once

#include<assimp/cimport.h>
#include<assimp/scene.h>
#include<assimp/postprocess.h>

#include<geCore/ErrorPrinter.h>
#include<geGL/geGL.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_access.hpp>


#define USE_FULL_SHADING

#ifdef USE_FULL_SHADING
#include "Material.h"
#include "Texture.h"
//This encodes material index to normal vector .w
#define NUM_NORMAL_COMPONENTS 4
#else
#define NUM_NORMAL_COMPONENTS 3
#endif

class Model{
  public:
    aiScene const*model = nullptr;
    Model(std::string const&name);
    virtual ~Model();
    void getVertices(std::vector<float>&vertices);
	void getNormals(std::vector<float>&normals);
	void getTcoords(std::vector<float>&tcoords);
#ifdef USE_FULL_SHADING
	void getMaterialsTextures(std::vector<Material>& materials, std::vector<Texture>& textures);
	std::string modelDirectory;
protected:
	void _loadTextures(const std::vector<std::string>& texNames, std::vector<Texture>& textures);
#endif

};

class RenderModel: public ge::gl::Context{
  public:
    RenderModel(std::shared_ptr<Model>const&mdl);
    ~RenderModel();
    void draw(glm::mat4 const&projectionView);
    std::shared_ptr<ge::gl::VertexArray>vao = nullptr;
    std::shared_ptr<ge::gl::Buffer>vertices = nullptr;
    std::shared_ptr<ge::gl::Buffer>normals = nullptr;
#ifdef USE_FULL_SHADING
	std::shared_ptr<ge::gl::Buffer>tcoords = nullptr;
	std::vector<uint64_t> textureHandles;
	std::shared_ptr<ge::gl::Buffer>textureHandlesBuffer = nullptr;
	std::shared_ptr<ge::gl::Buffer>materials = nullptr;
	std::vector<std::shared_ptr<ge::gl::Texture>>texObjects;
	std::shared_ptr<ge::gl::Sampler>sampler;
#endif
    std::shared_ptr<ge::gl::Buffer>indices = nullptr;
    std::shared_ptr<ge::gl::Buffer>indexVertices = nullptr;
    std::shared_ptr<ge::gl::Program>program = nullptr;
   
	uint32_t nofVertices = 0;
};
