#pragma once

#include<iostream>

const std::string computeSrc = R".(
#line 6
#ifndef MAX_MULTIPLICITY
#define MAX_MULTIPLICITY 2
#endif//MAX_MULTIPLICITY

#ifndef WORKGROUP_SIZE_X
#define WORKGROUP_SIZE_X 64
#endif//WORKGROUP_SIZE_X

//#define CULL_SIDES 1
//#define LOCAL_ATOMIC 1

layout(local_size_x=WORKGROUP_SIZE_X)in;

#if     USE_PLANES == 1
layout(std430,binding=0)readonly buffer Edges              {float edges      [];};
#else //USE_PLANES == 1
layout(std430,binding=0)readonly buffer Edges              {vec4  edges      [];};
#endif//USE_PLANES == 1

layout(std430,binding=1)         buffer Silhouettes        {vec4  silhouettes[];};

#if LOCAL_ATOMIC == 1
layout(std430,binding=2)volatile buffer DrawIndirectCommand{uint drawIndirectBuffer[4];};
#else
layout(std430,binding=2)         buffer DrawIndirectCommand{uint drawIndirectBuffer[4];};
#endif

uniform uint numEdge       = 0                  ;
uniform vec4 lightPosition = vec4(100,100,100,1);
uniform mat4 mvp           = mat4(1)            ;

#if LOCAL_ATOMIC == 1
shared uint localCounter;
shared uint globalOffset;
#endif

void main(){

#if LOCAL_ATOMIC == 1
  if(gl_LocalInvocationID.x==0){
    localCounter = 0;
    globalOffset = 0;
  }
  barrier();
#endif

  uint gid=gl_GlobalInvocationID.x;

  if(gid>=numEdge)return;
#if CULL_SIDES == 1
  vec4 P[4];
#else
  vec4 P[2];
#endif
#if     USE_PLANES == 1
  gid*=3+3+4*MAX_MULTIPLICITY;
#else //USE_PLANES == 1
  gid*=2+MAX_MULTIPLICITY;
#endif//USE_PLANES == 1

#if     USE_PLANES == 1

#if     USE_INTERLEAVING == 1
  P[0].x = edges[gl_GlobalInvocationID.x+numEdge*0];
  P[0].y = edges[gl_GlobalInvocationID.x+numEdge*1];
  P[0].z = edges[gl_GlobalInvocationID.x+numEdge*2];
  P[0].w = 1;
  P[1].x = edges[gl_GlobalInvocationID.x+numEdge*3];
  P[1].y = edges[gl_GlobalInvocationID.x+numEdge*4];
  P[1].z = edges[gl_GlobalInvocationID.x+numEdge*5];
  P[1].w = 1;
#else //USE_INTERLEAVING == 1
  P[0] = vec4(edges[gid+0],edges[gid+1],edges[gid+2],1);
  P[1] = vec4(edges[gid+3],edges[gid+4],edges[gid+5],1);
#endif//USE_INTERLEAVING == 1

#else //USE_PLANES == 1
  P[0]=edges[gid+0];
  P[1]=edges[gid+1];
#endif//USE_PLANES == 1

#if CULL_SIDES == 1
  P[2]=vec4(P[0].xyz*lightPosition.w-lightPosition.xyz,0);
  P[3]=vec4(P[1].xyz*lightPosition.w-lightPosition.xyz,0);
#endif

  int Num=int(P[0].w)+2;
  P[0].w=1;

#if CULL_SIDES == 1
  vec4 ClipP[4];
  for(int i=0;i<4;++i)
    ClipP[i]=mvp*P[i];

  vec3 Normal=(mvp*vec4(cross(
          P[1].xyz-P[0].xyz,
          lightPosition.xyz-P[0].xyz*lightPosition.w),0)).xyz;
  ivec3 Corner=ivec3(1+sign(Normal))>>1;
  if(Corner.z==1);Corner=ivec3(1)-Corner;
  int Diag=Corner.x+(Corner.y<<1)-1;

  if(!isVisible(ClipP,Diag))return;
#endif//CULL_SIDES

  precise int Multiplicity=0;
  if(Num>20)Num=0;
  if(Num<0)Num=0;

#if     USE_PLANES == 1

#if     USE_INTERLEAVING == 1
  for(uint m=0;m<MAX_MULTIPLICITY;++m){
    vec4 plane;
    plane.x = edges[gl_GlobalInvocationID.x+numEdge*(6+m*4+0)];
    plane.y = edges[gl_GlobalInvocationID.x+numEdge*(6+m*4+1)];
    plane.z = edges[gl_GlobalInvocationID.x+numEdge*(6+m*4+2)];
    plane.w = edges[gl_GlobalInvocationID.x+numEdge*(6+m*4+3)];
    Multiplicity += int(sign(dot(plane,lightPosition)));
  }
#else //USE_INTERLEAVING == 1
  for(uint m=0;m<MAX_MULTIPLICITY;++m)
    Multiplicity += int(sign(dot(vec4(edges[gid+6+m*4+0],edges[gid+6+m*4+1],edges[gid+6+m*4+2],edges[gid+6+m*4+3]),lightPosition)));
#endif//USE_INTERLEAVING == 1

#else //USE_PLANES == 1
  for(int i=2;i<Num;++i)
    Multiplicity += currentMultiplicity(P[0].xyz,P[1].xyz,edges[gid+i].xyz,lightPosition);
#endif//USE_PLANES == 1

#if LOCAL_ATOMIC == 1
  uint localOffset = atomicAdd(localCounter,uint(2*abs(Multiplicity)));
  barrier();
  if(gl_LocalInvocationID.x==0){
    globalOffset = atomicAdd(drawIndirectBuffer[0],localCounter);
  }
  barrier();
  uint WH = globalOffset + localOffset;
  if(Multiplicity>0){
    for(int m=0;m<Multiplicity;++m){
      silhouettes[WH++]=P[1];
      silhouettes[WH++]=P[0];
    }
  }
  if(Multiplicity<0){
    Multiplicity=-Multiplicity;
    for(int m=0;m<Multiplicity;++m){
      silhouettes[WH++]=P[0];
      silhouettes[WH++]=P[1];
    }
  }
#else
  if(Multiplicity>0){
    uint WH=atomicAdd(drawIndirectBuffer[0],2*Multiplicity);
    for(int m=0;m<Multiplicity;++m){
      silhouettes[WH++]=P[1];
      silhouettes[WH++]=P[0];
    }
  }
  if(Multiplicity<0){
    Multiplicity=-Multiplicity;
    uint WH=atomicAdd(drawIndirectBuffer[0],2*Multiplicity);
    for(int m=0;m<Multiplicity;++m){
      silhouettes[WH++]=P[0];
      silhouettes[WH++]=P[1];
    }
  }
#endif
}).";





std::string const drawVPSrc = R".(
#version 450 core
layout(location=0)in vec4 Position;
void main(){
  gl_Position=Position;
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

