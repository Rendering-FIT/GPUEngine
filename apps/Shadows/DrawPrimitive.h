#pragma once

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_access.hpp>

#include<geGL/geGL.h>

class DrawPrimitive: protected ge::gl::Context{
  public:
    enum LinMet{
      STANDARD=0,
      DP=1,
      NEITHY=2,
      LOG=3
    };
    DrawPrimitive(glm::uvec2 const&windowSize);
    void setWindowSize(glm::uvec2 const&size);
    void beginTriangles();
    void beginLine();
    void beginPoint();
    void beginPlanes();
    void end();
    void setView(glm::mat4 view);
    void setProjection(glm::mat4 projection);
    void setColor(float r,float g,float b,float a);
    void setColor(glm::vec4 color);
    void triangle(glm::vec3 a,glm::vec3 b,glm::vec3 c);
    void line(glm::vec3 a,glm::vec3 b);
    void point(glm::vec3 a,float size);
    void plane(glm::vec4 a,float size);
    void drawTexture(std::shared_ptr<ge::gl::Texture>const&texture,float x = 0,float y = 0,float sx = 1,float sy = 1,float tsx = 1,float tsy = 1);
    void drawDepth  (std::shared_ptr<ge::gl::Texture>const&texture,float x,float y,float sx,float sy,
        float near,float far,LinMet met=STANDARD);
    void drawCubeDepth  (GLuint id,float x,float y,float sx,float sy,
        float near,float far,int face,LinMet met=STANDARD);

    void drawHeatMap(GLuint id,float x,float y,float sx,float sy,
        unsigned min=0,unsigned max=255,int trans=0,unsigned channel=0);
    void drawHeatMap(GLuint id,float x,float y,float sx,float sy,
        float min=0.f,float max=1.f,int trans=0,unsigned channel=0);
    void draw1D(GLuint id,float x,float y,float sx,float sy,float min=0.f,float max=1.f,unsigned channel=0);
  private:
    glm::uvec2  _windowSize;
    glm::mat4 _view;
    glm::mat4 _projection;
    glm::vec4 _color;
    std::shared_ptr<ge::gl::Program>_drawTriangleProgram;
    std::shared_ptr<ge::gl::Program>_drawLineProgram;
    std::shared_ptr<ge::gl::Program>_drawPointProgram;
    std::shared_ptr<ge::gl::Program>_drawPlaneProgram;
    std::shared_ptr<ge::gl::Program>_drawTexture;
    std::shared_ptr<ge::gl::Program>_drawDepth;
    std::shared_ptr<ge::gl::Program>_drawCubeDepth;
    std::shared_ptr<ge::gl::Program>_drawHeatF;
    std::shared_ptr<ge::gl::Program>_drawHeatU;
    std::shared_ptr<ge::gl::Program>_draw1DF;
    std::shared_ptr<ge::gl::VertexArray>_emptyVAO;
    enum{
      TRIANGLES,
      LINES,
      POINTS,
      PLANE
    }_mode;
    std::shared_ptr<ge::gl::Program>_getActiveProgram();
    void _setStateSet();
    void _setViewPort(float x,float y,float sx,float sy);
    void _resetViewPort();
};


