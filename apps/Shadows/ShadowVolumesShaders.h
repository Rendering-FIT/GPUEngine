#pragma once

#include<iostream>

const std::string blitVPSrc = R".(
#version 450 core
void main(){
  gl_Position = vec4(-1+2*(gl_VertexID/2),-1+2*(gl_VertexID%2),0,1);
}).";
const std::string blitFPSrc = R".(
#version 450 core
layout(location=0)out float fColor;
void main(){
  fColor = 1;
}).";

