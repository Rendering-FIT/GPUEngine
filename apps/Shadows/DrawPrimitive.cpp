#include"DrawPrimitive.h"

DrawPrimitive::DrawPrimitive(glm::uvec2 const&windowSize):_windowSize(windowSize){
  const std::string emptyVPSrc = R".(
#version 450
void main(){}
).";
  const std::string colorFPSrc = R".(
#version 450
uniform vec4 color=vec4(1,1,1,1);
layout(location=0)out vec4 fColor;
void main(){fColor=color;}
).";
  const std::string pointGPSrc = R".(
#version 450 core
layout(points)in;
layout(triangle_strip,max_vertices=4)out;
uniform vec3 a=vec3(0,0,0);
uniform mat4 v   = mat4(1);
uniform mat4 p   = mat4(1);
uniform float size=.01f;
void main(){
  mat4 vp=p*v;
  vec4 center=vp*vec4(a,1);
  for(uint i=0;i<4;++i){
    gl_Position=center+p*vec4(-1.+2.*float(i%2),-1.+2.*float(i/2),0,0)*size;EmitVertex();
  }
  EndPrimitive();
}
).";
  const std::string lineGPSrc = R".(
#version 450 core
layout(points)in;
layout(line_strip,max_vertices=2)out;
uniform vec3 a=vec3(0,0,0);
uniform vec3 b=vec3(0,0,0);
uniform mat4 v   = mat4(1);
uniform mat4 p   = mat4(1);
uniform float size=.01f;
void main(){
  mat4 vp=p*v;
  gl_Position=vp*vec4(a,1);EmitVertex();
  gl_Position=vp*vec4(b,1);EmitVertex();
  EndPrimitive();
}
).";
  const std::string planeGPSrc = R".(
#version 450 core
layout(points)in;
layout(triangle_strip,max_vertices=12)out;
uniform vec4 a=vec4(1,0,0,0);
uniform float size=0;
uniform mat4 v   = mat4(1);
uniform mat4 p   = mat4(1);
void main(){
  vec3 center=(-a.w/dot(a.xyz,a.xyz))*a.xyz;
  vec3 v0;
  if(a.y==0&&a.z==0)v0=a.xyz+vec3(0,a.x,0);
  else v0=a.xyz+vec3(a.x,0,0);
  vec3 x=normalize(cross(a.xyz,v0));
  vec3 y=normalize(cross(a.xyz,x));
  mat4 vp=p*v;
  if(size==0){
    gl_Position=vp*vec4(center,1);EmitVertex();
    gl_Position=vp*vec4(x,size);EmitVertex();
    gl_Position=vp*vec4(y,size);EmitVertex();
    EndPrimitive();
    gl_Position=vp*vec4(center,1);EmitVertex();
    gl_Position=vp*vec4(y,size);EmitVertex();
    gl_Position=vp*vec4(-x,size);EmitVertex();
    EndPrimitive();
    gl_Position=vp*vec4(center,1);EmitVertex();
    gl_Position=vp*vec4(-x,size);EmitVertex();
    gl_Position=vp*vec4(-y,size);EmitVertex();
    EndPrimitive();
    gl_Position=vp*vec4(center,1);EmitVertex();
    gl_Position=vp*vec4(-y,size);EmitVertex();
    gl_Position=vp*vec4(x,size);EmitVertex();
    EndPrimitive();
  }else{
    x*=size;
    x+=center;
    y*=size;
    y+=center;
    gl_Position=vp*vec4(center,1);EmitVertex();
    gl_Position=vp*vec4(x,1);EmitVertex();
    gl_Position=vp*vec4(y,1);EmitVertex();
    EndPrimitive();
    gl_Position=vp*vec4(center,1);EmitVertex();
    gl_Position=vp*vec4(y,1);EmitVertex();
    gl_Position=vp*vec4(-x,1);EmitVertex();
    EndPrimitive();
    gl_Position=vp*vec4(center,1);EmitVertex();
    gl_Position=vp*vec4(-x,1);EmitVertex();
    gl_Position=vp*vec4(-y,1);EmitVertex();
    EndPrimitive();
    gl_Position=vp*vec4(center,1);EmitVertex();
    gl_Position=vp*vec4(-y,1);EmitVertex();
    gl_Position=vp*vec4(x,1);EmitVertex();
    EndPrimitive();
  }
}
).";
  const std::string planeFPSrc = R".(
#version 450 core
uniform vec4 color=vec4(1,1,1,1);
layout(location=0)out vec4 fColor;
void main(){
  if(gl_FrontFacing)fColor=vec4(0,1,0,color.w);
  else fColor=vec4(1,0,0,color.w);
}
).";
  const std::string triangleGPSrc = R".(
#version 450 core
layout(points)in;
layout(triangle_strip,max_vertices=3)out;
uniform vec3 a=vec3(0,0,0);
uniform vec3 b=vec3(0,1,0);
uniform vec3 c=vec3(1,1,0);
uniform mat4 v   = mat4(1);
uniform mat4 p   = mat4(1);
out vec4 normal;
void main(){
  mat4 vp=p*v;
  vec4 n=(vp*vec4(normalize(cross(b-a,c-a)),0));
  normal=n;gl_Position=vp*vec4(a,1);EmitVertex();
  normal=n;gl_Position=vp*vec4(b,1);EmitVertex();
  normal=n;gl_Position=vp*vec4(c,1);EmitVertex();
  EndPrimitive();
}
).";
  const std::string triangleFPSrc = R".(
#version 450 core
uniform vec4 color=vec4(1,1,1,1);
layout(location=0)out vec4 fColor;
in vec4 normal;
void main(){
  if(color.w>1)fColor=vec4(normal.xyz*.5+.5,normal.w);
  else fColor=color;
}
).";
  const std::string textureGPSrc = R".(
#version 450 core
layout(points)in;
layout(triangle_strip,max_vertices=4)out;
out vec2 gCoord;
uniform int transId=0;
vec2 transform(vec2 co){
  if(transId==0)return vec2(  co.x,  co.y);
  if(transId==1)return vec2(1-co.x,  co.y);
  if(transId==2)return vec2(  co.x,1-co.y);
  if(transId==3)return vec2(1-co.x,1-co.y);
  if(transId==4)return vec2(  co.y,  co.x);
  if(transId==5)return vec2(1-co.y,  co.x);
  if(transId==6)return vec2(  co.y,1-co.x);
  if(transId==7)return vec2(1-co.y,1-co.x);
  return co;
}
void main(){
	for(int i=0;i<4;++i){
		gl_Position=vec4(-1.f+2.f*float(i%2),-1.f+2.f*float(i/2),-1.f,1.f);
    gCoord=vec2(i%2,i/2);
		EmitVertex();
	}
	EndPrimitive();
}
).";
  const std::string textureFPSrc = R".(
#version 450 core
layout(location=0)out vec4 fColor;
layout(binding=0)uniform sampler2D tex;
in vec2 gCoord;
uniform vec2 texSize = vec2(1);
void main(){
  fColor=texture(tex,gCoord*texSize);
}
).";
  const std::string heatSrc = R".(
vec4 getHeatColor(float t){
  t=clamp(t,0,1);
  vec4 colors[]={
    vec4(0,0,0,1),
    vec4(0,0,1,1),
    vec4(0,1,0,1),
    vec4(1,0,0,1),
    vec4(1,1,0,1),
    vec4(1,1,1,1)
  };
  t*=colors.length();
  uint i=uint(floor(t));
  uint j=i+1;
  if(i>=colors.length()){
    i=colors.length()-1;
    j=i;
  }
  return mix(colors[i],colors[j],fract(t));
}
).";
  const std::string drawHeatSrc = R".(
layout(location=0)out vec4 fColor;
layout(binding=0)uniform sampler2D tex;

in vec2 gCoord;

uniform float minValue=0.f;
uniform float maxValue=1.f;
uniform uint channel=0;

void main(){
  float val=texture(tex,gCoord)[channel];
  val=(val-minValue)/(maxValue-minValue);
  fColor=getHeatColor(val);
}
).";
  const std::string drawHeatUSrc = R".(
layout(location=0)out vec4 fColor;
layout(binding=0)uniform usampler2D tex;

in vec2 gCoord;

uniform uint minValue = 0u;
uniform uint maxValue = 1u;
uniform uint channel  = 0u;

void main(){
  uint val=texture(tex,gCoord)[channel];
  float v=float(val-minValue)/float(maxValue-minValue);
  fColor=getHeatColor(v);
}
).";
  const std::string draw1DFSrc = R".(
layout(location=0)out vec4 fColor;
layout(binding=0)uniform sampler1D tex;

in vec2 gCoord;

uniform float size=0.01f;
uniform float minValue=0.f;
uniform float maxValue=1.f;
uniform uint  channel=0;

void main(){
  float val=texture(tex,gCoord.x)[channel];
  val=(val-minValue)/(maxValue-minValue);
  if(abs(gCoord.y-val)<size)fColor=vec4(1.f);
  else fColor=vec4(0.f);
}
).";
  const std::string drawDepthSrc = R".(
#version 450 core

layout(location=0)out vec4 fColor;
layout(binding=0)uniform sampler2D tex;

in vec2 gCoord;

uniform float near=0.1f;
uniform float far=100.f;

uniform int linMet=0;

float linearize(float d){
  return 2.f*far*near/(far+near-(2.f*d-1.f)*(far-near));
}

void main(){
  float val=texture(tex,gCoord).x;

  if(linMet==0)fColor=vec4((linearize(val)-near)/(far-near));
  if(linMet==1)fColor=vec4(val);
  if(linMet==2)fColor=vec4((1-val)*50);
  if(linMet==3)fColor=vec4(log(linearize(val))*10);

  //fColor=vec4((linearize(val)-near)/(far-near));
}
).";
  const std::string drawCubeDepthSrc = R".(
#version 450 core

layout(location=0)out vec4 fColor;
layout(binding=0)uniform samplerCube tex;

in vec2 gCoord;

uniform float near=0.1f;
uniform float far=100.f;

uniform int linMet=0;

uniform int face=0;

float linearize(float d){
  return 2.f*far*near/(far+near-(2.f*d-1.f)*(far-near));
}

void main(){
  vec3 co=vec3(1,0,0);
  vec2 gC=gCoord*2-1;
  if(face==0)co=vec3(-1,gC.y,gC.x);
  if(face==1)co=vec3(+1,gC.y,-gC.x);
  if(face==2)co=vec3(gC.y,-1,-gC.x);
  if(face==3)co=vec3(-gC.y,+1,-gC.x);
  if(face==4)co=vec3(-gC.x,gC.y,-1);
  if(face==5)co=vec3(gC.x,gC.y,+1);


  float val=texture(tex,co).x;
  //fColor=vec4(log(linearize(val))*10);
  //fColor=vec4((1-val)*50);

  if(linMet==0)fColor=vec4((linearize(val)-near)/(far-near));
  if(linMet==1)fColor=vec4(val);
  if(linMet==2)fColor=vec4((1-val)*50);
  if(linMet==3)fColor=vec4(log(linearize(val))*10);

}
).";
  this->_drawTriangleProgram = std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER  ,emptyVPSrc),
      std::make_shared<ge::gl::Shader>(GL_GEOMETRY_SHADER,triangleGPSrc),
      std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER,triangleFPSrc));

  this->_drawPointProgram = std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER  ,emptyVPSrc),
      std::make_shared<ge::gl::Shader>(GL_GEOMETRY_SHADER,pointGPSrc),
      std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER,colorFPSrc));

  this->_drawLineProgram = std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER  ,emptyVPSrc),
      std::make_shared<ge::gl::Shader>(GL_GEOMETRY_SHADER,lineGPSrc),
      std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER,colorFPSrc));

  this->_drawPlaneProgram = std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER  ,emptyVPSrc),
      std::make_shared<ge::gl::Shader>(GL_GEOMETRY_SHADER,planeGPSrc),
      std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER,planeFPSrc));

  this->_drawTexture = std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER  ,emptyVPSrc),
      std::make_shared<ge::gl::Shader>(GL_GEOMETRY_SHADER,textureGPSrc),
      std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER,textureFPSrc));

  this->_drawHeatF = std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER  ,emptyVPSrc),
      std::make_shared<ge::gl::Shader>(GL_GEOMETRY_SHADER,textureGPSrc),
      std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER,"#version 450 core\n",heatSrc,drawHeatSrc));
  this->_drawHeatU = std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER  ,emptyVPSrc),
      std::make_shared<ge::gl::Shader>(GL_GEOMETRY_SHADER,textureGPSrc),
      std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER,"#version 450 core\n",heatSrc,drawHeatUSrc));
  this->_draw1DF = std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER  ,emptyVPSrc),
      std::make_shared<ge::gl::Shader>(GL_GEOMETRY_SHADER,textureGPSrc),
      std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER,"#version 450 core\n",heatSrc,draw1DFSrc));

  this->_drawDepth = std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER  ,emptyVPSrc),
      std::make_shared<ge::gl::Shader>(GL_GEOMETRY_SHADER,textureGPSrc),
      std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER,drawDepthSrc));

  this->_drawCubeDepth = std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER  ,emptyVPSrc),
      std::make_shared<ge::gl::Shader>(GL_GEOMETRY_SHADER,textureGPSrc),
      std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER,drawCubeDepthSrc));

  this->_emptyVAO   = std::make_shared<ge::gl::VertexArray>();
  this->_mode       = TRIANGLES;
  this->_view       = glm::mat4(1.f);
  this->_projection = glm::mat4(1.f);
  this->_color      = glm::vec4(1.f);
}

void DrawPrimitive::setWindowSize(glm::uvec2 const&size){
  this->_windowSize = size;
}


void DrawPrimitive::beginTriangles(){
  this->_mode=TRIANGLES;
  this->_setStateSet();
}

void DrawPrimitive::beginLine(){
  this->_mode=LINES;
  this->_setStateSet();
}

void DrawPrimitive::beginPoint(){
  this->_mode=POINTS;
  this->_setStateSet();
}

void DrawPrimitive::beginPlanes(){
  this->_mode=PLANE;
  this->_setStateSet();
}

void DrawPrimitive::end(){
  this->_emptyVAO->unbind();
}

std::shared_ptr<ge::gl::Program>DrawPrimitive::_getActiveProgram(){
  switch(this->_mode){
    case TRIANGLES:return this->_drawTriangleProgram;
    case LINES    :return this->_drawLineProgram    ;
    case POINTS   :return this->_drawPointProgram   ;
    case PLANE    :return this->_drawPlaneProgram   ;
    default       :return this->_drawTriangleProgram;
  }
}

void DrawPrimitive::_setStateSet(){
  this->_getActiveProgram()->use();
  this->setView      (this->_view      );
  this->setProjection(this->_projection);
  this->setColor     (this->_color     );
  this->_emptyVAO->bind();
}

void DrawPrimitive::setView(glm::mat4 view){
  this->_view=view;
  auto program=this->_getActiveProgram();
  program->setMatrix4fv("v",glm::value_ptr(this->_view));
}

void DrawPrimitive::setProjection(glm::mat4 projection){
  this->_projection=projection;
  auto program=this->_getActiveProgram();
  program->setMatrix4fv("p",glm::value_ptr(this->_projection));
}

void DrawPrimitive::setColor(float r,float g,float b,float a){
  this->setColor(glm::vec4(r,g,b,a));
}

void DrawPrimitive::setColor(glm::vec4 color){
  this->_color=color;
  auto program=this->_getActiveProgram();
  program->set4fv("color",glm::value_ptr(this->_color));
}

void DrawPrimitive::triangle(glm::vec3 a,glm::vec3 b,glm::vec3 c){
  this->_drawTriangleProgram->set3fv("a",glm::value_ptr(a));
  this->_drawTriangleProgram->set3fv("b",glm::value_ptr(b));
  this->_drawTriangleProgram->set3fv("c",glm::value_ptr(c));
  glDrawArrays(GL_POINTS,0,1);
}

void DrawPrimitive::line(glm::vec3 a,glm::vec3 b){
  this->_drawLineProgram->set3fv("a",glm::value_ptr(a));
  this->_drawLineProgram->set3fv("b",glm::value_ptr(b));
  glDrawArrays(GL_POINTS,0,1);
}

void DrawPrimitive::point(glm::vec3 a,float size){
  this->_drawPointProgram->set3fv("a",glm::value_ptr(a));
  this->_drawPointProgram->set1f("size",size);
  glDrawArrays(GL_POINTS,0,1);
}

void DrawPrimitive::plane(glm::vec4 a,float size){
  this->_drawPlaneProgram->set4fv("a",glm::value_ptr(a));
  this->_drawPlaneProgram->set1f("size",size);
  glDrawArrays(GL_POINTS,0,1);
}

void DrawPrimitive::_setViewPort(float x,float y,float sx,float sy){
  glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
  glViewport(
      x *this->_windowSize[0],
      y *this->_windowSize[1],
      sx*this->_windowSize[0],
      sy*this->_windowSize[1]);
  this->_emptyVAO->bind();
}

void DrawPrimitive::_resetViewPort(){
  glDrawArrays(GL_POINTS,0,1);
  this->_emptyVAO->unbind();
  glViewport(0,0,this->_windowSize[0],this->_windowSize[1]);
}

void DrawPrimitive::drawTexture(std::shared_ptr<ge::gl::Texture>const&texture,float x,float y,float sx,float sy,float tsx,float tsy){
  this->_setViewPort(x,y,sx,sy);

  this->_drawTexture->use();
  this->_drawTexture->set2f("texSize",tsx,tsy);
  texture->bind(0);

  this->_resetViewPort();
}

void DrawPrimitive::drawHeatMap(GLuint id,float x,float y,float sx,float sy,
    float min,float max,int trans,unsigned channel){
  this->_setViewPort(x,y,sx,sy);

  this->_drawHeatF->use();
  this->_drawHeatF->set("minValue",min);
  this->_drawHeatF->set("maxValue",max);
  this->_drawHeatF->set("channel",channel);
  this->_drawHeatF->set("transId",trans);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D,id);

  this->_resetViewPort();
}

void DrawPrimitive::drawHeatMap(GLuint id,float x,float y,float sx,float sy,
    unsigned min,unsigned max,int trans,unsigned channel){
  this->_setViewPort(x,y,sx,sy);

  this->_drawHeatU->use();
  this->_drawHeatU->set("minValue",min);
  this->_drawHeatU->set("maxValue",max);
  this->_drawHeatU->set("channel",channel);
  this->_drawHeatU->set("transId",trans);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D,id);

  this->_resetViewPort();
}

void DrawPrimitive::draw1D(GLuint id,float x,float y,float sx,float sy,
    float min,float max,unsigned channel){
  this->_setViewPort(x,y,sx,sy);

  this->_draw1DF->use();
  this->_draw1DF->set1f("size",.8/(sy*this->_windowSize[1]));
  this->_draw1DF->set1f("minValue",min);
  this->_draw1DF->set1f("maxValue",max);
  this->_draw1DF->set1f("channel",channel);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_1D,id);

  this->_resetViewPort();
}

void DrawPrimitive::drawDepth  (std::shared_ptr<ge::gl::Texture>const&texture,float x,float y,float sx,float sy,
        float near,float far,LinMet met){
  this->_setViewPort(x,y,sx,sy);
  this->_drawDepth->use();
  this->_drawDepth->set1f("near",near);
  this->_drawDepth->set1f("far",far);
  this->_drawDepth->set1i("linMet",(int)met);
  texture->bind(0);
  GLint last;
  glGetTextureParameteriv(texture->getId(),GL_TEXTURE_COMPARE_MODE,&last);
  glTextureParameteri(texture->getId(),GL_TEXTURE_COMPARE_MODE,GL_NONE);
  this->_resetViewPort();
  glTextureParameteri(texture->getId(),GL_TEXTURE_COMPARE_MODE,last);

}
void DrawPrimitive::drawCubeDepth  (GLuint id,float x,float y,float sx,float sy,
    float near,float far,int face,LinMet met){
  this->_setViewPort(x,y,sx,sy);

  this->_drawCubeDepth->use();
  this->_drawCubeDepth->set1f("near",near);
  this->_drawCubeDepth->set1f("far",far);
  this->_drawCubeDepth->set1i("face",face);
  this->_drawCubeDepth->set1i("linMet",(int)met);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP,id);
  GLint last;
  glGetTexParameteriv(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_COMPARE_MODE,&last);
  glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_COMPARE_MODE,GL_NONE);
  this->_resetViewPort();
  glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_COMPARE_MODE,last);
}

