#pragma once

const char* hssvVsSource = R"(
#version 430 core

layout(location=0)in vec4 Position;

uniform mat4 mvp = mat4(1);

void main(){
  gl_Position=mvp*Position;
}
)";

const char* hssvFsSource = R"(
#version 430 core

layout(location=0)out vec4 fColor;

void main(){
  if(gl_FrontFacing)
    fColor=vec4(0,1,0,1);
  else
    fColor=vec4(1,0,0,1);
}
)";