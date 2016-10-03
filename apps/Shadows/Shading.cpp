#include"Shading.h"
#include<geCore/Dtemplates.h>

Shading::Shading(
    std::shared_ptr<ge::gl::Texture>const&color     ,
    std::shared_ptr<ge::gl::Texture>const&position  ,
    std::shared_ptr<ge::gl::Texture>const&normal    ,
    std::shared_ptr<ge::gl::Texture>const&shadowMask):_color(color),_position(position),_normal(normal),_shadowMask(shadowMask){
  assert(this!=nullptr);
  const std::string vertSrc = R".(
#version 450
void main(){
  gl_Position = vec4(-1+2*(gl_VertexID/2),-1+2*(gl_VertexID%2),0,1);
}).";
  const std::string fragSrc = R".(
#version 450
layout(location=0)out vec4 fColor;

layout(binding=0)uniform usampler2D colorTexture;
layout(binding=1)uniform  sampler2D positionTexture;
layout(binding=2)uniform  sampler2D normalTexture;
layout(binding=3)uniform  sampler2D shadowMaskTexture;

ivec2 coord=ivec2(gl_FragCoord.xy);

uniform vec3 cameraPosition = vec3(0);

uniform vec4 lightPosition = vec4(100,100,100,1);
uniform vec3 La = vec3(0.1);//light ambient color
uniform vec3 Ld = vec3(1);//light diffuse color
uniform vec3 Ls = vec3(1);//light specular color
uniform bool useShadows = false;

void main(){
  vec3 sum=vec3(0);

  vec3  position    = texelFetch(positionTexture  ,coord,0).xyz;
  vec3  normal      = texelFetch(normalTexture    ,coord,0).xyz;
  float shadowCoef  = 1;
  if(useShadows)
    shadowCoef = texelFetch(shadowMaskTexture,coord,0).x;

  uvec4 color              = texelFetch(colorTexture,coord,0);
  vec3  Ka                 = vec3((color.xyz>>0)&0xff)/0xff;
  vec3  Kd                 = Ka;
  vec3  Ks                 = vec3((color.xyz>>8)&0xff)/0xff;
  float Shininess          = 50;//shininess factor
  float specularFactorCoef = float(color.w)/255.;

  vec3 V = normalize(cameraPosition-position);//view vector
  vec3 L = normalize(lightPosition.xyz-position*lightPosition.w);//light vector
  vec3 R = reflect(-L,normal);//reflected light vector

  float ambientFactor  = 1;
  float diffuseFactor  = max(dot(L,normal),0)*shadowCoef;
  float specularFactor = pow(max(dot(R,V),0),Shininess)*specularFactorCoef*shadowCoef;

  sum+=Ka*La*ambientFactor;
  sum+=Kd*Ld*diffuseFactor;
  sum+=Ks*Ls*specularFactor;

  fColor=vec4(sum,1);//output color
}).";
  this->_program = std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER,vertSrc),
      std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER,fragSrc));
  this->_vao = std::make_shared<ge::gl::VertexArray>();
}

Shading::~Shading(){

}

void Shading::draw(glm::vec4 const&lightPosition,glm::vec3 const&cameraPosition,bool useShadows){
  this->_color->bind(0);
  this->_position->bind(1);
  this->_normal->bind(2);
  this->_shadowMask->bind(3);
  this->_program->use();
  this->_program->set4fv("lightPosition",glm::value_ptr(lightPosition));
  this->_program->set3fv("cameraPosition",glm::value_ptr(cameraPosition));
  this->_program->set1i("useShadows",useShadows);
  this->_vao->bind();
  glDrawArrays(GL_TRIANGLE_STRIP,0,4);
  this->_vao->unbind();
}

