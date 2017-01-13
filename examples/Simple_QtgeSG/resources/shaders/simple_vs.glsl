#version 430

layout(location=0) in vec3 pos;
layout(location = 2) in vec2 texcoords;

uniform mat4 projection;
uniform mat4 model;

out vec2 uv;

void main(){
   uv = texcoords;
   gl_Position = projection * model * vec4(pos,1.0);
}