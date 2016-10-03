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


class Model{
  public:
    aiScene const*model = nullptr;
    Model(std::string const&name);
    virtual ~Model();
    void getVertices(std::vector<float>&vertices);
};

class RenderModel: public ge::gl::Context{
  public:
    RenderModel(std::shared_ptr<Model>const&mdl);
    ~RenderModel();
    void draw(glm::mat4 const&projectionView);
    std::shared_ptr<ge::gl::VertexArray>vao = nullptr;
    std::shared_ptr<ge::gl::Buffer>vertices = nullptr;
    std::shared_ptr<ge::gl::Buffer>normals = nullptr;
    std::shared_ptr<ge::gl::Buffer>indices = nullptr;
    std::shared_ptr<ge::gl::Buffer>indexVertices = nullptr;
    std::shared_ptr<ge::gl::Program>program = nullptr;
    uint32_t nofVertices = 0;
};
