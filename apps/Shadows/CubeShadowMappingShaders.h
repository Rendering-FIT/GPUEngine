#pragma once
#include<iostream>

std::string const createShadowMapVertexShaderSource = R".(
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
}
).";

std::string const createShadowMapGeometryShaderSource = R".(
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




std::string const createShadowMaskVertexShaderSource = R".(
void main(){
  gl_Position = vec4(-1+2*(gl_VertexID/2),-1+2*(gl_VertexID%2),0,1);
}
).";

std::string const createShadowMaskFragmentShaderSource = R".(
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
}
).";


