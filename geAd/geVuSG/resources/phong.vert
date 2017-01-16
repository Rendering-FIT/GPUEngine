#version 450

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

layout(push_constant) uniform PushConstants {
  mat4 p;
  mat4 v;
  mat4 m;
} u;

layout(location = 0) out vec3 position;
layout(location = 1) out vec3 normal;
layout(location = 2) out vec2 texCoord;

void main() {
  vec4 pos = u.m*vec4(aPosition,1);
  position = pos.xyz;
  normal = aNormal;
  texCoord = aTexCoord;

  mat4 vp = u.p*u.v;
  gl_Position = vp*pos;
  gl_Position.y = -gl_Position.y;
}

