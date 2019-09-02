#pragma once

#include<geGL/geGL.h>
#include <glm/gtc/type_ptr.hpp>


class GBuffer: public ge::gl::Context{
  public:
    GBuffer(uint32_t w,uint32_t h){
      assert(this!=nullptr);
      this->color    = std::make_shared<ge::gl::Texture>(GL_TEXTURE_2D,GL_RGBA16UI,1,w,h);
      color->texParameteri(GL_TEXTURE_MAG_FILTER,GL_NEAREST);
      color->texParameteri(GL_TEXTURE_MIN_FILTER,GL_NEAREST);
      this->position = std::make_shared<ge::gl::Texture>(GL_TEXTURE_2D,GL_RGBA32F,1,w,h);
      this->normal   = std::make_shared<ge::gl::Texture>(GL_TEXTURE_2D,GL_RGBA32F,1,w,h);
      this->depth    = std::make_shared<ge::gl::Texture>(GL_TEXTURE_RECTANGLE,GL_DEPTH24_STENCIL8,1,w,h);
      this->fbo = std::make_shared<ge::gl::Framebuffer>();
      this->fbo->attachTexture(GL_COLOR_ATTACHMENT0,this->color);
      this->fbo->attachTexture(GL_COLOR_ATTACHMENT1,this->position);
      this->fbo->attachTexture(GL_COLOR_ATTACHMENT2,this->normal);
      this->fbo->attachTexture(GL_DEPTH_ATTACHMENT,this->depth);
      this->fbo->attachTexture(GL_STENCIL_ATTACHMENT,this->depth);
      this->fbo->drawBuffers({GL_COLOR_ATTACHMENT0,GL_COLOR_ATTACHMENT1,GL_COLOR_ATTACHMENT2});
      assert(this->fbo->check());
    }

	void setClearColor(glm::vec4 const& color)
    {
		m_clearColor = glm::uvec4(255 * color.x, 255 * color.y, 255 * color.z, 255 * color.w);
    }

	void setClearColor(glm::uvec4 const& color)
	{
		m_clearColor = color;
	}

    void begin(){
      assert(this!=nullptr);
      this->fbo->bind();
		
      float const clearPosition[4] = { 0, 0, 0, 0 };
	  fbo->clearBuffer(GL_COLOR, 0, glm::value_ptr(m_clearColor));
	  fbo->clearBuffer(GL_COLOR, 1, clearPosition);
	  fbo->clearBuffer(GL_COLOR, 2, clearPosition);

	  ge::gl::glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }
    void end(){
      assert(this!=nullptr);
      this->fbo->unbind();
    }

    std::shared_ptr<ge::gl::Texture>position = nullptr;
    std::shared_ptr<ge::gl::Texture>color    = nullptr;
    std::shared_ptr<ge::gl::Texture>normal   = nullptr;
    std::shared_ptr<ge::gl::Texture>depth    = nullptr;
    std::shared_ptr<ge::gl::Framebuffer>fbo  = nullptr;

	glm::uvec4 m_clearColor = glm::uvec4(0, 0, 0, 0);
};
