#pragma once

#include<iostream>

const std::string computeSrc = R".(
#line 6

#extension GL_AMD_gcn_shader       : enable
#extension GL_AMD_gpu_shader_int64 : enable

#ifndef MAX_MULTIPLICITY
#define MAX_MULTIPLICITY 2
#endif//MAX_MULTIPLICITY

#ifndef WORKGROUP_SIZE_X
#define WORKGROUP_SIZE_X 64
#endif//WORKGROUP_SIZE_X

layout(local_size_x=WORKGROUP_SIZE_X)in;

layout(std430,binding=0)readonly buffer Edges              {vec4  edges             [];};
layout(std430,binding=1)         buffer Silhouettes        {float silhouettes       [];};
layout(std430,binding=2)         buffer DrawIndirectCommand{uint  drawIndirectBuffer[];};

uniform uint numEdge       = 0                  ;
uniform vec4 lightPosition = vec4(100,100,100,1);
uniform mat4 mvp           = mat4(1)            ;

shared uint globalOffset;

void main(){

  uint gid=gl_GlobalInvocationID.x;

  if(gid>=numEdge)return;
  gid*=2+MAX_MULTIPLICITY;

  vec4 P[2];
  P[0]=edges[gid+0];
  P[1]=edges[gid+1];

  int multiplicity=0;

  for(uint m=0;m<MAX_MULTIPLICITY;++m)
    multiplicity += int(sign(dot(edges[gid+2+m],lightPosition)));

  for(uint m=0;m<MAX_MULTIPLICITY;++m){
    uint64_t isSilhouetteLong = ballotAMD(abs(multiplicity) == m+1);
    uvec2 isSilhouette = unpackUint2x32(isSilhouetteLong);
    if(gl_LocalInvocationID.x==0){
      uint nofSilhouettes = bitCount(isSilhouette.x) + bitCount(isSilhouette.y);
      globalOffset = atomicAdd(drawIndirectBuffer[m*4],nofSilhouettes*2);
    }

    uint threadMaskLow  = gl_LocalInvocationID.x>=32 ? 0xffffffffu : uint(1u<<(gl_LocalInvocationID.x   ))-1u;
    uint threadMaskHigh = gl_LocalInvocationID.x< 32 ? 0x00000000u : uint(1u<<(gl_LocalInvocationID.x-32))-1u;
    uint localOffset    = bitCount(isSilhouette.x&threadMaskLow) + bitCount(isSilhouette.y&threadMaskHigh);
    uint offset         = (drawIndirectBuffer[m*4+2] + globalOffset + localOffset*2)*3;
    if(multiplicity == -m-1){
      silhouettes[offset+0]=P[0].x;
      silhouettes[offset+1]=P[0].y;
      silhouettes[offset+2]=P[0].z;
      silhouettes[offset+3]=P[1].x;
      silhouettes[offset+4]=P[1].y;
      silhouettes[offset+5]=P[1].z;
    }else if(multiplicity == m+1){
      silhouettes[offset+0]=P[1].x;
      silhouettes[offset+1]=P[1].y;
      silhouettes[offset+2]=P[1].z;
      silhouettes[offset+3]=P[0].x;
      silhouettes[offset+4]=P[0].y;
      silhouettes[offset+5]=P[0].z;
    }
  }
}).";





std::string const drawVPSrc = R".(
#version 450 core
layout(location=0)in vec3 Position;
void main(){
  gl_Position=vec4(Position,1);
}).";

std::string const drawCPSrc = R".(
#version 450 core
layout(vertices=4)out;
uniform mat4 mvp           = mat4(1)            ;
uniform vec4 lightPosition = vec4(100,100,100,1);
void main(){
  //gl_out[gl_InvocationID].gl_Position=mvp*gl_in[gl_InvocationID].gl_Position;
  gl_out[gl_InvocationID].gl_Position=mvp*(vec4(gl_in[gl_InvocationID&1].gl_Position.xyz-lightPosition.xyz*(gl_InvocationID/2),1-(gl_InvocationID/2)));
  if(gl_InvocationID==0){
    gl_TessLevelOuter[0]=1;
    gl_TessLevelOuter[1]=1;
    gl_TessLevelOuter[2]=1;
    gl_TessLevelOuter[3]=1;
    gl_TessLevelInner[0]=1;
    gl_TessLevelInner[1]=1;
  }
}).";

std::string const drawEPSrc = R".(
#version 450 core
layout(quads)in;
void main(){
  gl_Position = gl_in[uint(gl_TessCoord.x>.5)+(uint(gl_TessCoord.y>.5)<<1)].gl_Position;
}).";




std::string const capsVPSrc = R".(
#version 450 core
layout(location=0)in vec4 Position;
void main(){
  gl_Position=Position;
}).";

std::string const capsGPSrc = R".(

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

layout(triangles)in;
layout(triangle_strip,max_vertices=6)out;

uniform mat4 mvp           = mat4(1.f);
uniform vec4 lightPosition = vec4(100,100,100,1);

void main(){
  int Multiplicity = currentMultiplicity(gl_in[0].gl_Position.xyz,gl_in[1].gl_Position.xyz,gl_in[2].gl_Position.xyz,lightPosition);

  if(Multiplicity==0)return;

  if(Multiplicity>0){
    gl_Position=(mvp*gl_in[FCLF0].gl_Position).SWIZZLE;EmitVertex(); 
    gl_Position=(mvp*gl_in[FCLF1].gl_Position).SWIZZLE;EmitVertex(); 
    gl_Position=(mvp*gl_in[FCLF2].gl_Position).SWIZZLE;EmitVertex(); 
    EndPrimitive();
    //*
    if(lightPosition.w>0){
      gl_Position=(mvp*vec4(gl_in[BCLF0].gl_Position.xyz-lightPosition.xyz,0));EmitVertex();
      gl_Position=(mvp*vec4(gl_in[BCLF1].gl_Position.xyz-lightPosition.xyz,0));EmitVertex();
      gl_Position=(mvp*vec4(gl_in[BCLF2].gl_Position.xyz-lightPosition.xyz,0));EmitVertex();
      EndPrimitive();
    }// */
  }else{
    gl_Position=(mvp*gl_in[FCLB0].gl_Position).SWIZZLE;EmitVertex(); 
    gl_Position=(mvp*gl_in[FCLB1].gl_Position).SWIZZLE;EmitVertex(); 
    gl_Position=(mvp*gl_in[FCLB2].gl_Position).SWIZZLE;EmitVertex(); 
    EndPrimitive();
    //*
    if(lightPosition.w>0){
      gl_Position=(mvp*vec4(gl_in[BCLB0].gl_Position.xyz-lightPosition.xyz,0));EmitVertex();
      gl_Position=(mvp*vec4(gl_in[BCLB1].gl_Position.xyz-lightPosition.xyz,0));EmitVertex();
      gl_Position=(mvp*vec4(gl_in[BCLB2].gl_Position.xyz-lightPosition.xyz,0));EmitVertex();
      EndPrimitive();
    }// */
  }
}).";

