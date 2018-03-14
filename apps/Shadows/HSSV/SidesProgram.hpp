#pragma once

const char* vsSource = R"(
#version 430 core

layout(location=0)in vec4 Position;

uniform mat4 mvp;

void main(){
  gl_Position=Position * mvp;
}
)";

const char* fsSource = R"(
#version 430 core

layout(location=0)out vec4 fColor;

void main(){
  if(gl_FrontFacing)
    fColor=vec4(0,1,0,1);
  else
    fColor=vec4(1,0,0,1);
}

)";