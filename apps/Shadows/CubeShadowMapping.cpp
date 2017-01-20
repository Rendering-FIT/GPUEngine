#include"CubeShadowMapping.h"

CubeShadowMapping::CubeShadowMapping(
        glm::uvec2                      const&windowSize ,
        std::shared_ptr<ge::gl::Texture>const&position   ,
        uint32_t                        const&nofVertices,
        std::shared_ptr<ge::gl::Buffer> const&vertices   ,
        std::shared_ptr<ge::gl::Texture>const&shadowMask ,
        CubeShadowMappingParams         const&params     ):
  _windowSize (windowSize ),
  _position   (position   ),
  _nofVertices(nofVertices),
  _params     (params     )
{
  assert(this!=nullptr);
  this->_shadowMap = std::make_shared<ge::gl::Texture>(GL_TEXTURE_CUBE_MAP,GL_DEPTH_COMPONENT24,1,this->_params.resolution,this->_params.resolution);
  this->_shadowMap->texParameteri(GL_TEXTURE_MIN_FILTER,GL_NEAREST);
  this->_shadowMap->texParameteri(GL_TEXTURE_MAG_FILTER,GL_NEAREST);
  this->_shadowMap->texParameteri(GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
  this->_shadowMap->texParameteri(GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
  this->_shadowMap->texParameteri(GL_TEXTURE_COMPARE_FUNC,GL_LEQUAL);
  this->_shadowMap->texParameteri(GL_TEXTURE_COMPARE_MODE,GL_COMPARE_R_TO_TEXTURE);
  this->_fbo = std::make_shared<ge::gl::Framebuffer>();
  this->_fbo->attachTexture(GL_DEPTH_ATTACHMENT,this->_shadowMap);

  this->_vao = std::make_shared<ge::gl::VertexArray>();
  this->_vao->addAttrib(vertices,0,3,GL_FLOAT);

  this->_maskVao = std::make_shared<ge::gl::VertexArray>();
  this->_maskFbo = std::make_shared<ge::gl::Framebuffer>();
  this->_maskFbo->attachTexture(GL_COLOR_ATTACHMENT0,shadowMask);
  this->_maskFbo->drawBuffers(1,GL_COLOR_ATTACHMENT0);



  const std::string mapVertSrc = R".(
#version 450
layout(location=0)in vec3 position;
uniform float near = 0.1;
uniform float far  = 1000;
uniform vec4 lightPosition = vec4(0,0,0,1);
out int vInstanceID;
void main(){
  const mat4 views[6] = {
    mat4(vec4(+0,+0,-1,0), vec4(+0,-1,+0,0), vec4(-1,+0,+0,0), vec4(0,0,0,1)),
    mat4(vec4(+0,+0,+1,0), vec4(+0,-1,+0,0), vec4(+1,+0,+0,0), vec4(0,0,0,1)),
    mat4(vec4(+1,+0,+0,0), vec4(+0,+0,-1,0), vec4(+0,+1,+0,0), vec4(0,0,0,1)),
    mat4(vec4(+1,+0,+0,0), vec4(+0,+0,+1,0), vec4(+0,-1,+0,0), vec4(0,0,0,1)),
    mat4(vec4(+1,+0,+0,0), vec4(+0,-1,+0,0), vec4(+0,+0,-1,0), vec4(0,0,0,1)),
    mat4(vec4(-1,+0,+0,0), vec4(+0,-1,+0,0), vec4(+0,+0,+1,0), vec4(0,0,0,1))
  };

  mat4 projection = mat4(
    vec4(1,0,0,0),
    vec4(0,1,0,0),
    vec4(0,0,-(far+near)/(far-near),-1),
    vec4(0,0,-2*far*near/(far-near),0));
  gl_Position = projection*views[gl_InstanceID]*vec4(position-lightPosition.xyz,1);
  vInstanceID = gl_InstanceID;
}).";
  const std::string mapGeomSrc = R".(
#version 450
layout(triangles)in;
layout(triangle_strip,max_vertices=3)out;
in int vInstanceID[];
void main(){
  gl_Layer = vInstanceID[0];
  gl_Position = gl_in[0].gl_Position;EmitVertex();
  gl_Position = gl_in[1].gl_Position;EmitVertex();
  gl_Position = gl_in[2].gl_Position;EmitVertex();
  EndPrimitive();
}).";
  const std::string mapFragSrc = R".(
#version 450
void main(){
}).";
  this->_createShadowMap = std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER,mapVertSrc),
      std::make_shared<ge::gl::Shader>(GL_GEOMETRY_SHADER,mapGeomSrc),
      std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER,mapFragSrc));

  const std::string maskVertSrc = R".(
#version 450
void main(){
  gl_Position = vec4(-1+2*(gl_VertexID/2),-1+2*(gl_VertexID%2),0,1);
}).";

  const std::string maskFragSrc = R".(
#version 450
layout(location=0)out float fColor;

layout(binding=0)uniform sampler2D         position;
layout(binding=1)uniform samplerCubeShadow shadowMap;

uniform float near = 0.1;
uniform float far = 1000;
uniform vec4 lightPosition = vec4(0,0,0,1);

float computeDepth(vec3 dir){
  vec3 adir=abs(dir);
  float baseDis=-max(max(adir.x,adir.y),adir.z);
  float A=-(far+near)/(far-near);
  float B=-2*far*near/(far-near);
  return (-A-B/baseDis)*.5+.5;
}

void main(){
  ivec2 Coord=ivec2(gl_FragCoord.xy);
  vec3 viewSamplePosition = texelFetch(position,Coord,0).xyz;
  vec3 dir=viewSamplePosition-lightPosition.xyz;
  fColor=texture(shadowMap,vec4(dir,computeDepth(dir))).x;
}).";

  this->_createShadowMask = std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER,maskVertSrc),
      std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER,maskFragSrc));
}


CubeShadowMapping::~CubeShadowMapping(){

}

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
  this->_createShadowMap->use();
  this->_createShadowMap->set4fv("lightPosition" ,glm::value_ptr(lightPosition ));
  this->_createShadowMap->set1f("near",this->_params.near);
  this->_createShadowMap->set1f("far",this->_params.far);
  glDrawArraysInstanced(GL_TRIANGLES,0,this->_nofVertices,this->_params.faces);
  this->_vao->unbind();
  this->_fbo->unbind();
  if(this->timeStamp)this->timeStamp->stamp("createShadowMap");
  
  glViewport(0,0,this->_windowSize.x,this->_windowSize.y);
  this->_maskFbo->bind();
  this->_maskVao->bind();
  this->_createShadowMask->use();
  this->_createShadowMask->set4fv("lightPosition" ,glm::value_ptr(lightPosition ));
  this->_createShadowMask->set1f("near",this->_params.near);
  this->_createShadowMask->set1f("far",this->_params.far);
  this->_position->bind(0);
  this->_shadowMap->bind(1);
  glDrawArrays(GL_TRIANGLE_STRIP,0,4);
  this->_maskVao->unbind();
  this->_maskFbo->unbind();
  if(this->timeStamp)this->timeStamp->stamp("createShadowMask");
}

