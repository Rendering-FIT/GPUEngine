#pragma once

#include<iostream>

const std::string computeSrc = R".(
#ifndef MAX_MULTIPLICITY
#define MAX_MULTIPLICITY 2
#endif//MAX_MULTIPLICITY

#ifndef WORKGROUP_SIZE_X
#define WORKGROUP_SIZE_X 64
#endif//WORKGROUP_SIZE_X

//#define CULL_SIDES 1
//#define LOCAL_ATOMIC 1

layout(local_size_x=WORKGROUP_SIZE_X)in;

layout(std430,binding=0)buffer SInput  {vec4 IBuffer[];};
layout(std430,binding=1)buffer SOutput {vec4 OBuffer[];};

#if LOCAL_ATOMIC == 1
layout(std430,binding=2)volatile buffer SCounter{uint Counter[4];};
#else
layout(std430,binding=2)buffer SCounter{uint Counter[4];};
#endif

uniform uint numEdge=0;
uniform vec4 lightPosition;
uniform mat4 mvp;

int greaterVec(vec3 a,vec3 b){
  return int(dot(ivec3(sign(a-b)),ivec3(4,2,1)));
}

int computeMult(vec3 A,vec3 B,vec3 C,vec4 L){
  vec3 n=cross(C-A,L.xyz-A*L.w);
  return int(sign(dot(n,B-A)));
}

bool isEdgeVisible(in vec4 A,in vec4 B){
  vec3 M=+A.xyz+A.www;
  vec3 N=+B.xyz+B.www;
  vec3 O=-A.xyz+A.www;
  vec3 P=-B.xyz+B.www;
  vec3 NM=N-M;
  vec3 PO=P-O;
  float Left=0;
  float Right=1;
  for(int i=0;i<3;++i){
    if(NM[i]==0){
      if(M[i]<0)return false;
    }else{
      if(NM[i]>0)Left=max(Left,-M[i]/NM[i]);
      else Right=min(Right,-M[i]/NM[i]);
    }

    if(PO[i]==0){
      if(O[i]<0)return false;
    }else{
      if(PO[i]>0)Left=max(Left,-O[i]/PO[i]);
      else Right=min(Right,-O[i]/PO[i]);
    }
  }
  return Left<=Right;
}

bool isFullVisible(in vec4 A,in vec4 B,in vec4 C,int Diag){
  vec3 a=A.xyz;
  vec3 b=B.xyz;
  vec3 c=C.xyz;
  if(Diag>=0){
    a[Diag]=-a[Diag];
    b[Diag]=-b[Diag];
    c[Diag]=-c[Diag];
  }
  float m=(a.x-a.y);
  float n=(b.x-b.y);
  float o=(c.x-c.y);
  float p=(a.x-a.z);
  float q=(b.x-b.z);
  float r=(c.x-c.z);
  float d=(q*o-n*r);
  float t=(m*r-p*o)/d;
  float l=-(m*q-p*n)/d;
  vec4 X=A+t*B+l*C;
  return (t>0)&&(t<1)&&(l>0)&&(l<1)&&
    all(greaterThan(X.xyz,-X.www))&&all(lessThan(X.xyz,X.www));
}

bool isVisible(in vec4 a,in vec4 b,in vec4 c,in vec4 d,vec4 l){
  vec4 A=mvp*a;
  vec4 B=mvp*b;
  vec4 C=mvp*c;
  vec4 D=mvp*d;
  vec3 n=(mvp*vec4(cross(b.xyz-a.xyz,l.xyz-a.xyz*l.w),0)).xyz;
  ivec3 Corner=ivec3(1+sign(n))>>1;
  if(Corner.z==1)Corner=ivec3(1)-Corner;
  int Diag=Corner.x+(Corner.y<<1)-1;
  if(isFullVisible(A,B-A,C-A,Diag))return true;
  if(isEdgeVisible(A,B))return true;
  if(isEdgeVisible(A,C))return true;
  if(isEdgeVisible(B,D))return true;
  if(isEdgeVisible(C,D))return true;
  return false;
}

bool isVisible(in vec4 P[4],in int Diag){
  if(isFullVisible(P[0],P[1]-P[0],P[2]-P[0],Diag))return true;
  if(isEdgeVisible(P[0],P[1]))return true;
  if(isEdgeVisible(P[0],P[2]))return true;
  if(isEdgeVisible(P[1],P[3]))return true;
  if(isEdgeVisible(P[2],P[3]))return true;
  return false;
}


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

#define BE_HILLBERT 0

#if BE_HILLBERT == 1
  const uint map[64]={
    0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,
    1,3,5,7,9,11,13,15,17,19,21,23,25,27,29,31,33,35,37,39,41,43,45,47,49,51,53,55,57,59,61,63
  };
  uint gid = gl_WorkGroupID.x*gl_WorkGroupSize.x+map[gl_LocalInvocationID.x];
#else
  uint gid=gl_GlobalInvocationID.x;
#endif

  if(gid<numEdge){//compute silhouette
#if CULL_SIDES == 1
    vec4 P[4];
#else
    vec4 P[2];
#endif
    gid*=2+MAX_MULTIPLICITY;

    P[0]=IBuffer[gid+0];
    P[1]=IBuffer[gid+1];
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

    for(int i=2;i<Num;++i){
#define T0 P[0].xyz
#define T1 P[1].xyz
#define T2 IBuffer[gid+i].xyz
      if(greaterVec(T0,T2)>0){//T[2] T[0] T[1]?
        Multiplicity+=computeMult(T2,T0,T1,lightPosition);
      }else{
        if(greaterVec(T1,T2)>0){//T[0] T[2] T[1]?
          Multiplicity-=computeMult(T0,T2,T1,lightPosition);
        }else{//T[0] T[1] T[2]?
          Multiplicity+=computeMult(T0,T1,T2,lightPosition);
        }
      }
    }
#if LOCAL_ATOMIC == 1
    uint localOffset = atomicAdd(localCounter,uint(2*abs(Multiplicity)));
    barrier();
    if(gl_LocalInvocationID.x==0){
      globalOffset = atomicAdd(Counter[0],localCounter);
    }
    barrier();
    uint WH = globalOffset + localOffset;
    if(Multiplicity>0){
      for(int m=0;m<Multiplicity;++m){
        OBuffer[WH++]=P[1];
        OBuffer[WH++]=P[0];
      }
    }
    if(Multiplicity<0){
      Multiplicity=-Multiplicity;
      for(int m=0;m<Multiplicity;++m){
        OBuffer[WH++]=P[0];
        OBuffer[WH++]=P[1];
      }
    }
#else
    if(Multiplicity>0){
      uint WH=atomicAdd(Counter[0],2*Multiplicity);
      for(int m=0;m<Multiplicity;++m){
        OBuffer[WH++]=P[1];
        OBuffer[WH++]=P[0];
      }
    }
    if(Multiplicity<0){
      Multiplicity=-Multiplicity;
      uint WH=atomicAdd(Counter[0],2*Multiplicity);
      for(int m=0;m<Multiplicity;++m){
        OBuffer[WH++]=P[0];
        OBuffer[WH++]=P[1];
      }
    }
#endif
  }
}).";





const std::string drawVPSrc = R".(
#version 450 core
layout(location=0)in vec4 Position;
void main(){
  gl_Position=Position;
}).";
const std::string drawCPSrc = R".(
#version 450 core
layout(vertices=4)out;
uniform mat4 mvp;
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
const std::string drawEPSrc = R".(
#version 450 core
layout(quads)in;
void main(){
  gl_Position = gl_in[uint(gl_TessCoord.x>.5)+(uint(gl_TessCoord.y>.5)<<1)].gl_Position;
}).";
const std::string drawFPSrc = R".(
#version 450 core
layout(location=0)out vec4 fragColor;
void main(){
  fragColor=vec4(1);
}).";


const std::string capsVPSrc = R".(
#version 450 core
layout(location=0)in vec4 Position;
void main(){
  gl_Position=Position;
}).";
const std::string capsGPSrc = R".(
#version 450 core

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

uniform mat4 mvp;
uniform vec4 lightPosition;

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
    Multiplicity=-ComputeMult(A.xyz,B.xyz,C.xyz,lightPosition);
  else
    Multiplicity=+ComputeMult(A.xyz,B.xyz,C.xyz,lightPosition);

  if(Multiplicity==0)return;

  if(Multiplicity>0){
    gl_Position=(mvp*gl_in[FCLF0].gl_Position).SWIZZLE;EmitVertex(); 
    gl_Position=(mvp*gl_in[FCLF1].gl_Position).SWIZZLE;EmitVertex(); 
    gl_Position=(mvp*gl_in[FCLF2].gl_Position).SWIZZLE;EmitVertex(); 
    EndPrimitive();
    //*
    if(lightPosition.w>0){
      gl_Position=(mvp*vec4(gl_in[BCLF0].gl_Position.xyz-lightPosition.xyz,0));
      EmitVertex();
      gl_Position=(mvp*vec4(gl_in[BCLF1].gl_Position.xyz-lightPosition.xyz,0));
      EmitVertex();
      gl_Position=(mvp*vec4(gl_in[BCLF2].gl_Position.xyz-lightPosition.xyz,0));
      EmitVertex();
      EndPrimitive();
    }// */
  }else{
    gl_Position=(mvp*gl_in[FCLB0].gl_Position).SWIZZLE;EmitVertex(); 
    gl_Position=(mvp*gl_in[FCLB1].gl_Position).SWIZZLE;EmitVertex(); 
    gl_Position=(mvp*gl_in[FCLB2].gl_Position).SWIZZLE;EmitVertex(); 
    EndPrimitive();
    //*
    if(lightPosition.w>0){
      gl_Position=(mvp*vec4(gl_in[BCLB0].gl_Position.xyz-lightPosition.xyz,0));
      EmitVertex();
      gl_Position=(mvp*vec4(gl_in[BCLB1].gl_Position.xyz-lightPosition.xyz,0));
      EmitVertex();
      gl_Position=(mvp*vec4(gl_in[BCLB2].gl_Position.xyz-lightPosition.xyz,0));
      EmitVertex();
      EndPrimitive();
    }// */
  }
}).";
const std::string capsFPSrc = R".(
#version 450 core

layout(location=0)out vec4 fColor;

void main(){
  if(gl_FrontFacing)
    fColor=vec4(0,1,0,1);
  else
    fColor=vec4(1,0,0,1);
}).";


