#include"CubeShadowMapping.h"

CubeShadowMapping::CubeShadowMapping(
        std::shared_ptr<ge::gl::Texture>const&shadowMask ,
        glm::uvec2                      const&windowSize ,
        std::shared_ptr<ge::gl::Texture>const&position   ,
        uint32_t                        const&nofVertices,
        std::shared_ptr<ge::gl::Buffer> const&vertices   ,
        CubeShadowMappingParams         const&params     ):
  _windowSize (windowSize ),
  _position   (position   ),
  _nofVertices(nofVertices),
  _params     (params     )
{
  assert(this!=nullptr);
  this->_shadowMap = std::make_shared<ge::gl::Texture>(GL_TEXTURE_CUBE_MAP,GL_DEPTH_COMPONENT24,1,this->_params.resolution,this->_params.resolution);
  this->_shadowMap->texParameteri(GL_TEXTURE_MIN_FILTER  ,GL_NEAREST             );
  this->_shadowMap->texParameteri(GL_TEXTURE_MAG_FILTER  ,GL_NEAREST             );
  this->_shadowMap->texParameteri(GL_TEXTURE_WRAP_S      ,GL_CLAMP_TO_EDGE       );
  this->_shadowMap->texParameteri(GL_TEXTURE_WRAP_T      ,GL_CLAMP_TO_EDGE       );
  this->_shadowMap->texParameteri(GL_TEXTURE_COMPARE_FUNC,GL_LEQUAL              );
  this->_shadowMap->texParameteri(GL_TEXTURE_COMPARE_MODE,GL_COMPARE_R_TO_TEXTURE);
  this->_fbo = std::make_shared<ge::gl::Framebuffer>();
  this->_fbo->attachTexture(GL_DEPTH_ATTACHMENT,this->_shadowMap);

  this->_vao = std::make_shared<ge::gl::VertexArray>();
  this->_vao->addAttrib(vertices,0,3,GL_FLOAT);

  this->_maskVao = std::make_shared<ge::gl::VertexArray>();
  this->_maskFbo = std::make_shared<ge::gl::Framebuffer>();
  this->_maskFbo->attachTexture(GL_COLOR_ATTACHMENT0,shadowMask);
  this->_maskFbo->drawBuffers(1,GL_COLOR_ATTACHMENT0);

#include"CubeShadowMappingShaders.h"

  this->_createShadowMap = std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER  ,
        "#version 450\n",
        createShadowMapVertexShaderSource  ),
      std::make_shared<ge::gl::Shader>(GL_GEOMETRY_SHADER,
        "#version 450\n",
        createShadowMapGeometryShaderSource));

  this->_createShadowMask = std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER  ,
        "#version 450\n",
        createShadowMaskVertexShaderSource),
      std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER,
        "#version 450\n",
        createShadowMaskFragmentShaderSource));
}

CubeShadowMapping::~CubeShadowMapping(){}

void CubeShadowMapping::create(glm::vec4 const&lightPosition,
    glm::mat4 const&,
    glm::mat4 const&){
  if(this->timeStamp)this->timeStamp->stamp("");
  glEnable(GL_POLYGON_OFFSET_FILL);
  glPolygonOffset(2.5,10);
  glViewport(0,0,this->_params.resolution,this->_params.resolution);
  glEnable(GL_DEPTH_TEST);
  this->_fbo->bind();
  glClear(GL_DEPTH_BUFFER_BIT);
  this->_vao->bind();
  this->_createShadowMap
    ->set4fv("lightPosition",glm::value_ptr(lightPosition))
    ->set1f ("near"         ,this->_params.near           )
    ->set1f ("far"          ,this->_params.far            )
    ->use();
  glDrawArraysInstanced(GL_TRIANGLES,0,this->_nofVertices,this->_params.faces);
  this->_vao->unbind();
  this->_fbo->unbind();
  if(this->timeStamp)this->timeStamp->stamp("createShadowMap");
  
  glViewport(0,0,this->_windowSize.x,this->_windowSize.y);
  this->_maskFbo->bind();
  this->_maskVao->bind();
  this->_createShadowMask
    ->set4fv("lightPosition",glm::value_ptr(lightPosition))
    ->set1f ("near"         ,this->_params.near           )
    ->set1f ("far"          ,this->_params.far            )
    ->use();
  this->_position->bind(0);
  this->_shadowMap->bind(1);
  glDrawArrays(GL_TRIANGLE_STRIP,0,4);
  this->_maskVao->unbind();
  this->_maskFbo->unbind();
  if(this->timeStamp)this->timeStamp->stamp("createShadowMask");
}

