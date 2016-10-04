#pragma once

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_access.hpp>

#include<geGL/geGL.h>

class Shading: ge::gl::Context{
  public:
    Shading(
        std::shared_ptr<ge::gl::Texture>const&color     ,
        std::shared_ptr<ge::gl::Texture>const&position  ,
        std::shared_ptr<ge::gl::Texture>const&normal    ,
        std::shared_ptr<ge::gl::Texture>const&shadowMask);
    ~Shading();
    void draw(glm::vec4 const&lightPosition,glm::vec3 const&cameraPosition,bool useShadows);
  protected:
    std::shared_ptr<ge::gl::Texture>_color      = nullptr;
    std::shared_ptr<ge::gl::Texture>_position   = nullptr;
    std::shared_ptr<ge::gl::Texture>_normal     = nullptr;
    std::shared_ptr<ge::gl::Texture>_shadowMask = nullptr;
    std::shared_ptr<ge::gl::Program>_program    = nullptr;
    std::shared_ptr<ge::gl::VertexArray>_vao    = nullptr;
};
