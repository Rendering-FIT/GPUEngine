#pragma once

const char* vsSource = R"(
#version 430 core

layout(location=0)in vec4 Position;

void main(){
  gl_Position=Position;
}
)";

const char* gsSource = R"(
#define SHIFT_TRIANGLE_TO_INFINITY

#ifdef SHIFT_TRIANGLE_TO_INFINITY
  #define SWIZZLE xyww
#else
  #define SWIZZLE xyzw
#endif

//front cap, light facing
#define FCLF0 0
#define FCLF1 1
#define FCLF2 2
//back cap, light facing
#define BCLF0 2
#define BCLF1 1
#define BCLF2 0
//front cap, light back-facing
#define FCLB0 2
#define FCLB1 1
#define FCLB2 0
//back cap, light back-facing
#define BCLB0 0
#define BCLB1 1
#define BCLB2 2

#version 430 core

layout(triangles)in;
layout(triangle_strip,max_vertices=6)out;

uniform mat4 mvp;
uniform vec4 LightPosition;

/**
* @brief Computes greater vector
*
* @param a vertex a
* @param b vertex b
*
* @return 1 if a>b, 0 if a==b, -1 if b<a
*/
int GreaterVec(in vec3 a,in vec3 b){
  return int(dot(sign(a-b),vec3(4,2,1)));
}

/**
* @brief Function computes multiplicity for one opposite vertex
*
* @param A smallest vertex of a triangle
* @param B middle vertex of a triangle
* @param C largest vertex of a triangle
* @param L light position
*
* @return 1 ABC (CCW) facing L, -1 ABC (CCW) not-facing L
*/
int ComputeMult(in vec3 A,in vec3 B,in vec3 C,in vec4 L){
  vec3 n=cross(C-A,L.xyz-A*L.w);//normal vector of light plane
  return int(sign(dot(n,B-A)));//multiplicity
}

void Swap(inout vec4 A,inout vec4 B){
  vec4 C=A;A=B;B=C;
}

void main(){
  vec4 A=gl_in[0].gl_Position;
  vec4 B=gl_in[1].gl_Position;
  vec4 C=gl_in[2].gl_Position;
  bool Swapped=false;
  if(GreaterVec(A.xyz,B.xyz)>0){Swap(A,B);Swapped=!Swapped;}
  if(GreaterVec(B.xyz,C.xyz)>0){Swap(B,C);Swapped=!Swapped;}
  if(GreaterVec(A.xyz,B.xyz)>0){Swap(A,B);Swapped=!Swapped;}
  /*
    000: ABC CCW 
    100: BAC CW                                                                 
    010: ACB CW                                                                 
    110: BCA CCW                                                                
    001: X                                                                      
    101: X                                                                      
    011: CAB CCW                                                                
    111: CBA CW
   */

  int Multiplicity;

  if(Swapped)
    Multiplicity=-ComputeMult(A.xyz,B.xyz,C.xyz,LightPosition);
  else
    Multiplicity=+ComputeMult(A.xyz,B.xyz,C.xyz,LightPosition);

  if(Multiplicity==0)return;

  if(Multiplicity>0){
    gl_Position=(mvp*gl_in[FCLF0].gl_Position).SWIZZLE;EmitVertex(); 
    gl_Position=(mvp*gl_in[FCLF1].gl_Position).SWIZZLE;EmitVertex(); 
    gl_Position=(mvp*gl_in[FCLF2].gl_Position).SWIZZLE;EmitVertex(); 
    EndPrimitive();
//*
    if(LightPosition.w>0){
      gl_Position=mvp*vec4(gl_in[BCLF0].gl_Position.xyz-LightPosition.xyz,0);
      EmitVertex();
      gl_Position=mvp*vec4(gl_in[BCLF1].gl_Position.xyz-LightPosition.xyz,0);
      EmitVertex();
      gl_Position=mvp*vec4(gl_in[BCLF2].gl_Position.xyz-LightPosition.xyz,0);
      EmitVertex();
      EndPrimitive();
    }// */
  }else{
    gl_Position=(mvp*gl_in[FCLB0].gl_Position).SWIZZLE;EmitVertex(); 
    gl_Position=(mvp*gl_in[FCLB1].gl_Position).SWIZZLE;EmitVertex(); 
    gl_Position=(mvp*gl_in[FCLB2].gl_Position).SWIZZLE;EmitVertex(); 
    EndPrimitive();
//*
    if(LightPosition.w>0){
      gl_Position=mvp*vec4(gl_in[BCLB0].gl_Position.xyz-LightPosition.xyz,0);
      EmitVertex();
      gl_Position=mvp*vec4(gl_in[BCLB1].gl_Position.xyz-LightPosition.xyz,0);
      EmitVertex();
      gl_Position=mvp*vec4(gl_in[BCLB2].gl_Position.xyz-LightPosition.xyz,0);
      EmitVertex();
      EndPrimitive();
    }// */
  }
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
