#pragma once

#include<iostream>

const std::string _generateHDT0Src = R".(
#ifndef WORKGROUP_SIZE_X
#define WORKGROUP_SIZE_X 8
#endif//WORKGROUP_SIZE_X

#ifndef WORKGROUP_SIZE_Y
#define WORKGROUP_SIZE_Y 8
#endif//WORKGROUP_SIZE_Y

#ifndef WORKGROUP_SIZE_Z
#define WORKGROUP_SIZE_Z 1
#endif//WORKGROUP_SIZE_Z

#ifndef WAVEFRONT_SIZE
#define WAVEFRONT_SIZE 64
#endif//WAVEFRONT_SIZE

#ifndef HIERARCHICALDEPTHTEXTURE_BINDING_DEPTH
#define HIERARCHICALDEPTHTEXTURE_BINDING_DEPTH 0
#endif//HIERARCHICALDEPTHTEXTURE_BINDING_DEPTH

#ifndef HIERARCHICALDEPTHTEXTURE_BINDING_HDT
#define HIERARCHICALDEPTHTEXTURE_BINDING_HDT 1
#endif//HIERARCHICALDEPTHTEXTURE_BINDING_HDT

layout(local_size_x=WORKGROUP_SIZE_X,local_size_y=WORKGROUP_SIZE_Y,local_size_z=WORKGROUP_SIZE_Z)in;
layout(      binding=HIERARCHICALDEPTHTEXTURE_BINDING_DEPTH)uniform sampler2DRect depthTexture                         ;
layout(rg32f,binding=HIERARCHICALDEPTHTEXTURE_BINDING_HDT  )uniform image2D       lowestLevelOfHierarchicalDepthTexture;

uniform uvec2 windowSize = uvec2(512,512);

void main(){
  uvec2 pixelCoords = gl_GlobalInvocationID.xy;
  if(any(greaterThanEqual(pixelCoords,windowSize)))return;
  float depth = texelFetch(depthTexture,ivec2(pixelCoords)).r;
  float clipSpaceDepth = depth*2.f-1.f;
  imageStore(lowestLevelOfHierarchicalDepthTexture,ivec2(pixelCoords),vec4(clipSpaceDepth));
}
).";

const std::string _generateHDTSrc = R".(
#ifndef WORKGROUP_SIZE_X
#define WORKGROUP_SIZE_X 8
#endif//WORKGROUP_SIZE_X

#ifndef WORKGROUP_SIZE_Y
#define WORKGROUP_SIZE_Y 8
#endif//WORKGROUP_SIZE_Y

#ifndef WORKGROUP_SIZE_Z
#define WORKGROUP_SIZE_Z 1
#endif//WORKGROUP_SIZE_Z

#ifndef WAVEFRONT_SIZE
#define WAVEFRONT_SIZE 64
#endif//WAVEFRONT_SIZE

#ifndef HIERARCHICALDEPTHTEXTURE_BINDING_HDTINPUT
  #define HIERARCHICALDEPTHTEXTURE_BINDING_HDTINPUT  0
#endif//HIERARCHICALDEPTHTEXTURE_BINDING_HDTINPUT

#ifndef HIERARCHICALDEPTHTEXTURE_BINDING_HDTOUTPUT
  #define HIERARCHICALDEPTHTEXTURE_BINDING_HDTOUTPUT 1
#endif//HIERARCHICALDEPTHTEXTURE_BINDING_HDTOUTPUT

#define DO_NOT_COUNT_WITH_INFINITY

layout(local_size_x=WORKGROUP_SIZE_X,local_size_y=WORKGROUP_SIZE_Y,local_size_z=WORKGROUP_SIZE_Z)in;
layout(rg32f,binding=HIERARCHICALDEPTHTEXTURE_BINDING_HDTINPUT )uniform image2D inputLevelOfHierarchicalDepthTexture;
layout(rg32f,binding=HIERARCHICALDEPTHTEXTURE_BINDING_HDTOUTPUT)uniform image2D outputLevelOfHierarchicalDepthTexture;

uniform uvec2 windowSize = uvec2(512,512);
shared float depth[WAVEFRONT_SIZE*2];
void main(){
  uvec2 pixelCoords = gl_GlobalInvocationID.xy;
  if(any(greaterThanEqual(pixelCoords,windowSize)))return;
  vec2 minmax=imageLoad(inputLevelOfHierarchicalDepthTexture,ivec2(pixelCoords)).xy;
  uint threadId = gl_LocalInvocationID.x+gl_LocalInvocationID.y*gl_WorkGroupSize.x;
	depth[threadId               ]=minmax.x;
	depth[threadId+WAVEFRONT_SIZE]=minmax.y;
	for(uint threadsPerLevel = WAVEFRONT_SIZE;threadsPerLevel>1;threadsPerLevel>>=1){
		if(threadId<threadsPerLevel){
      uint halfThreads = threadsPerLevel>>1;
      uint doMax = uint(threadId>=halfThreads);
			uint BaseIndex=(threadId&(halfThreads-1))+(doMax*(WAVEFRONT_SIZE));
			float a=depth[BaseIndex            ];
			float b=depth[BaseIndex+halfThreads];
#ifdef  DO_NOT_COUNT_WITH_INFINITY
			if(a>=+1)a=b;
			if(b>=+1)b=a;
			if(a<=-1)a=b;
			if(b<=-1)b=a;
#endif//DO_NOT_COUNT_WITH_INFINITY
			if((1-2*int(doMax))*(a-b)>=0)depth[BaseIndex]=b;
		}
	}
	if(threadId==0)
    imageStore(outputLevelOfHierarchicalDepthTexture,ivec2(gl_WorkGroupID.xy),vec4(depth[0],depth[WAVEFRONT_SIZE],0,0));
}
).";

const std::string _computeSilhouettesSrc = R".(
//DO NOT EDIT ANYTHING BELOW THIS COMMENT

#extension GL_AMD_gcn_shader       : enable
#extension GL_AMD_gpu_shader_int64 : enable

#ifndef MAX_MULTIPLICITY
#define MAX_MULTIPLICITY 2
#endif//MAX_MULTIPLICITY

#ifndef WORKGROUP_SIZE_X
#define WORKGROUP_SIZE_X 64
#endif//WORKGROUP_SIZE_X

//#define CULL_SIDES 1
//#define LOCAL_ATOMIC 1

layout(local_size_x=WORKGROUP_SIZE_X)in;

layout(std430,binding=0)buffer Edges                 {vec4  edges                 [ ];};
layout(std430,binding=1)buffer Silhouettes           {float silhouettes           [ ];};
layout(std430,binding=2)buffer DispatchIndirectBuffer{uint  dispatchIndirectBuffer[3];};

uniform uint numEdge       = 0;
uniform vec4 lightPosition = vec4(10,10,10,1);
uniform mat4 mvp           = mat4(1);

shared uint globalOffset;

void main(){
  uint gid=gl_GlobalInvocationID.x;
  precise int Multiplicity=0;
#if CULL_SIDES == 1
    vec4 P[4];
#else
    vec4 P[2];
#endif
  if(gid<numEdge){//compute silhouette
    gid*=2+MAX_MULTIPLICITY;

    P[0]=edges[gid+0];
    P[1]=edges[gid+1];
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

    if(Num>20)Num=0;
    if(Num<0)Num=0;

#if     USE_PLANES == 1
    for(int o=0;o<MAX_MULTIPLICITY;++o)
      Multiplicity += int(sign(dot(edges[gid+2+o],lightPosition)));
#else //USE_PLANES == 1
    for(int o=2;o<Num;++o)
      Multiplicity += currentMultiplicity(P[0].xyz,P[1].xyz,edges[gid+o].xyz,lightPosition);
#endif//USE_PLANES == 1

  }

  uint64_t isSilhouette = ballotAMD(Multiplicity!=0);
  if(gl_LocalInvocationID.x==0){
    uint nofSilhouettes = bitCount(uint(isSilhouette&0xffffffffu))+bitCount(uint(isSilhouette>>32));
    globalOffset = atomicAdd(dispatchIndirectBuffer[0],nofSilhouettes);
  }
  uint threadMaskLow  = uint(1u<<(gl_LocalInvocationID.x                               ))-1u;
  uint threadMaskHigh = uint(1u<<(gl_LocalInvocationID.x<32?0:gl_LocalInvocationID.x-32))-1u;
  uint localOffset    = bitCount(uint(isSilhouette&0xffffffffu)&threadMaskLow)+bitCount(uint(isSilhouette>>32)&threadMaskHigh);
  uint offset         = (globalOffset+localOffset)*7;

  if(Multiplicity==0)return;
  if(Multiplicity>0){
    silhouettes[offset+0]=P[0].x;
    silhouettes[offset+1]=P[0].y;
    silhouettes[offset+2]=P[0].z;
    silhouettes[offset+3]=P[1].x;
    silhouettes[offset+4]=P[1].y;
    silhouettes[offset+5]=P[1].z;
    silhouettes[offset+6]=float(Multiplicity);
  }else{
    silhouettes[offset+0]=P[1].x;
    silhouettes[offset+1]=P[1].y;
    silhouettes[offset+2]=P[1].z;
    silhouettes[offset+3]=P[0].x;
    silhouettes[offset+4]=P[0].y;
    silhouettes[offset+5]=P[0].z;
    silhouettes[offset+6]=float(-Multiplicity);
  }
}).";


const std::string _rasterizeSrc = R".(

#extension GL_AMD_gcn_shader       : enable
#extension GL_AMD_gpu_shader_int64 : enable

#ifndef WORKGROUP_SIZE_X
#define WORKGROUP_SIZE_X 8
#endif//WORKGROUP_SIZE_X

#ifndef WORKGROUP_SIZE_Y
#define WORKGROUP_SIZE_Y 8
#endif//WORKGROUP_SIZE_Y

#ifndef WORKGROUP_SIZE_Z
#define WORKGROUP_SIZE_Z 1
#endif//WORKGROUP_SIZE_Z

#ifndef WAVEFRONT_SIZE
#define WAVEFRONT_SIZE 64
#endif//WAVEFRONT_SIZE

#ifndef SILHOUETTES_PER_WORKGROUP
#define SILHOUETTES_PER_WORKGROUP 1
#endif//SILHOUETTES_PER_WORKGROUP

#ifndef NUMBER_OF_LEVELS
#define NUMBER_OF_LEVELS 3
#endif//NUMBER_OF_LEVELS

#ifndef NUMBER_OF_LEVELS_MINUS_ONE
#define NUMBER_OF_LEVELS_MINUS_ONE 2
#endif//NUMBER_OF_LEVELS_MINUS_ONE

#ifndef RASTERIZE_BINDING_HDT
#define RASTERIZE_BINDING_HDT 0
#endif//RASTERIZE_BINDING_HDT

#ifndef RASTERIZE_BINDING_SSM
#define RASTERIZE_BINDING_SSM 1
#endif//RASTERIZE_BINDING_SSM

#ifndef RASTERIZE_BINDING_SILHOUETTES
#define RASTERIZE_BINDING_SILHOUETTES 0
#endif//RASTERIZE_BINDING_SILHOUETTES

#define  WORKGROUP_ID_IN_DISPATCH  (uint(gl_WorkGroupID.x + triangleOffset))
#define INVOCATION_ID_IN_WAVEFRONT (uint(gl_LocalInvocationID.x))
#define SILHOUETTE_ID_IN_WORKGROUP (uint(gl_LocalInvocationID.y))
#define SILHOUETTE_ID_IN_DISPATCH  (WORKGROUP_ID_IN_DISPATCH*SILHOUETTES_PER_WORKGROUP + SILHOUETTE_ID_IN_WORKGROUP)



#define NOF_COMPONENTS_OF_VEC4             4
#define NOF_COMPONENTS_OF_VEC3             3
#define UINT_BIT_SIZE                      32
#define POINTS_PER_SILHOUETTE              2
#define FLOATS_PER_POINT                   3
#define FLOATS_PER_SILHOUETTE_POINTS       (FLOATS_PER_POINT*POINTS_PER_SILHOUETTE)
#define FLOATS_PER_SILHOUETTE_MULTIPLICITY 1
#define FLOATS_PER_SILHOUETTE              (FLOATS_PER_SILHOUETTE_POINTS+FLOATS_PER_SILHOUETTE_MULTIPLICITY)
#define VEC4_PER_SIDE                      4
#define RESULT_LENGTH_IN_UINT              (WAVEFRONT_SIZE/UINT_BIT_SIZE)

layout(local_size_x=WORKGROUP_SIZE_X,local_size_y=WORKGROUP_SIZE_Y,local_size_z=WORKGROUP_SIZE_Z)in;
layout(       binding=RASTERIZE_BINDING_HDT        )uniform sampler2D HDT[NUMBER_OF_LEVELS];
layout(r32i  ,binding=RASTERIZE_BINDING_SSM        )uniform iimage2D screenSpaceMultiplicity;
layout(std430,binding=RASTERIZE_BINDING_SILHOUETTES)buffer Silhouettes{vec4 silhouettes[];};
uniform uint nofSilhouettes = 0;
uniform vec4 lightPosition = vec4(100,100,100,1);
uniform mat4 mvp = mat4(1);

shared vec4 sharedSilhouettes   [SILHOUETTES_PER_WORKGROUP][VEC4_PER_SHADOWFRUSTUM];
shared int  sharedMultiplicities[SILHOUETTES_PER_WORKGROUP];
shared vec4 sharedSidePlanes    [SILHOUETTES_PER_WORKGROUP];

shared vec4 sharedSampleCoordInClipSpace[SILHOUETTES_PER_WORKGROUP][WAVEFRONT_SIZE];

void testSilhouetteHDT(uvec2 coord,vec2 clipCoord,uint level){
  if(level==NUMBER_OF_LEVELS_MINUS_ONE){
    uvec2 localCoord             = uvec2(INVOCATION_ID_IN_WAVEFRONT&3,INVOCATION_ID_IN_WAVEFRONT>>3);
    uvec2 globalCoord            = (coord<<3)+localCoord;
    vec2  globalClipCoord        = clipCoord+vec2(2.f/float(8<<(3*LEVEL)))*localCoord;
    vec4  sampleCoordInClipSpace = vec4(
        globalClipCoord+vec2(2.f/float(8<<(3*LEVEL)))*.5,
        texelFetch(HDT[LEVEL],ivec2(GlobalCoord),0).x,1);
    sharedSampleCoordInClipSpace[SILHOUETTE_ID_IN_WORKGROUP][INVOCATION_ID_IN_WAVEFRONT] = sampleCoordInClipSpace;
    uint64_t sideTest = ballotAMD(dot(sharedSidePlanes[SILHOUETTE_ID_IN_WORKGROUP],sampleCoordInClipSpace)<0);
    if(INVOCATION_ID_IN_WAVEFRONT<WAVEFRONT_SIZE-1){
      int sideCollision = ((sideTest>>INVOCATION_ID_IN_WAVEFRONT+1)&1)-((sideTest>>INVOCATION_ID_IN_WAVEFRONT  )&1);

    }
  }else{

  }
}

#define NO_INTERSECTION 0x00000000u
#define INTERSECTS      0x00000001u

// P = [Px,Py,Pz,1]^T //point
//
// Ax = L //left   of frustum
// Ay = B //bottom of frustum
// Az = N //near   of frustum
// Bx = R //right  of frustum
// By = T //top    of frustum
// Bz = F //far    of frustum
//
// M = frustum(Ax,Bx,Ay,By,Az,Bz)
//
// Q' = M * P //point in clip space of frustum
//      [ 2Az/(Bx-Ax)            0   (Bx+Ax)/(Bx-Ax)               0 ]   [Px]
// Q' = [           0  2Az/(By-Ay)   (By+Ay)/(By-Ay)               0 ] * [Py]
//      [           0            0  -(Bz+Az)/(Bz-Az)  -2AzBz/(Bz-Az) ]   [Pz]
//      [           0            0                -1               0 ]   [ 1]
//
// Q'x =    2Az/(Bx-Ax)Px +  (Bx+Ax)/(Bx-Ax) Pz
// Q'y =    2Az/(By-Ay)Py +  (By+Ay)/(By-Ay) Pz
// Q'z = -2AzBz/(Bz-Az)   + -(Bz+Az)/(Bz-Az) Pz
// Q'w =                                    -Pz
//
//
// Ix //weight of Ax,Bx for left   side of sub-tile 
// Jx //weight of Ax,Bx for right  side of sub-tile
// Iy //weight of Ay,By for bottom side of sub-tile
// Jy //weight of Ay,By for top    side of sub-tile
//
// ax = Ax*(1-Ix) + Bx*(Ix)
// bx = Ax*(1-Jx) + Bx*(Jx)
//
// ay = Ay*(1-Iy) + By*(Iy)
// by = Ax*(1-Iy) + By*(Iy)
//
// az = zMinMax.x //minimum depth of tile
// bz = zMinMax.y //maximum depth of tile
//
// N = frustum(ax,bx,ay,by,az,bz)
//
// P' = N * P //point in clip space of sub-frustum
//      [ 2az/(bx-ax)            0   (bx+ax)/(bx-ax)               0 ]   [Px]
// P' = [           0  2az/(by-ay)   (by+ay)/(by-ay)               0 ] * [Py]
//      [           0            0  -(bz+az)/(bz-az)  -2azbz/(bz-az) ]   [Pz]
//      [           0            0                -1               0 ]   [ 1]
//
// P'x =    2az/(bx-ax)Px +  (bx+ax)/(bx-ax) Pz
// P'y =    2az/(by-ay)Py +  (by+ay)/(by-ay) Pz
// P'z = -2azbz/(bz-az)   + -(bz+az)/(bz-az) Pz
// P'w =                                    -Pz
//
// P'x = 2az/(Ax*(1-Jx)+Bx*(Jx)-Ax*(1-Ix)-Bx*(Ix))Px+(Ax*(1-Jx)+Bx*(Jx)+Ax*(1-Ix)+Bx*(Ix))/(Ax*(1-Jx)+Bx*(Jx)-Ax*(1-Ix)-Bx*(Ix))Pz
// P'x = 2az/(Ax*(1-Jx)+Bx*Jx-Ax*(1-Ix)-Bx*Ix)Px+(Ax*(1-Jx)+Bx*Jx+Ax*(1-Ix)+Bx*Ix)/(Ax*(1-Jx)+Bx*Jx-Ax*(1-Ix)-Bx*Ix)Pz
// P'x = 2az/(Ax*(1-Jx)+Bx*(Jx-Ix)-Ax*(1-Ix))Px+(Ax*(1-Jx)+Bx*(Jx+Ix)+Ax*(1-Ix))/(Ax*(1-Jx)+Bx*(Jx-Ix)-Ax*(1-Ix))Pz
// P'x = 2az/(Ax*(-Jx+Ix)+Bx*(Jx-Ix))Px+(Ax*(2-Jx-Ix)+Bx*(Jx+Ix))/(Ax*(-Jx+Ix)+Bx*(Jx-Ix))Pz
// P'x = 2az/(-Ax*(Jx-Ix)+Bx*(Jx-Ix))Px+(Ax*(2-Jx-Ix)+Bx*(Jx+Ix))/(-Ax*(Jx-Ix)+Bx*(Jx-Ix))Pz
// P'x = 2az/((Bx-Ax)*(Jx-Ix))Px+(Ax*(2-Jx-Ix)+Bx*(Jx+Ix))/((Bx-Ax)*(Jx-Ix))Pz
// P'x = (2az/(Bx-Ax)Px+(Ax*(2-Jx-Ix)+Bx*(Jx+Ix))/(Bx-Ax)Pz)/(Jx-Ix)
// P'x = (2az/(Bx-Ax)Px+(2Ax+Ax(-Jx-Ix)+Bx*(Jx+Ix))/(Bx-Ax)Pz)/(Jx-Ix)
// P'x = (2az/(Bx-Ax)Px+(2Ax-Ax(Jx+Ix)+Bx*(Jx+Ix))/(Bx-Ax)Pz)/(Jx-Ix)
// P'x = (2az/(Bx-Ax)Px+(2Ax+(Bx-Ax)(Jx+Ix))/(Bx-Ax)Pz)/(Jx-Ix)
// P'x = (2az/(Bx-Ax)Px+(2Ax/(Bx-Ax)+(Jx+Ix))Pz)/(Jx-Ix)
// P'x = (2az/(Bx-Ax)Px+(2Ax/(Bx-Ax)+1-1+(Jx+Ix))Pz)/(Jx-Ix)
// P'x = (2az/(Bx-Ax)Px+(2Ax/(Bx-Ax)+(Bx-Ax)/(Bx-Ax)-1+(Jx+Ix))Pz)/(Jx-Ix)
// P'x = (2az/(Bx-Ax)Px+((Bx+Ax)/(Bx-Ax)-1+(Jx+Ix))Pz)/(Jx-Ix)
// P'x = (2az/(Bx-Ax)Px+(Bx+Ax)/(Bx-Ax)Pz+(-1+(Jx+Ix))Pz)/(Jx-Ix)
// P'x = ( 2az/(Bx-Ax)Px + (Bx+Ax)/(Bx-Ax)Pz + (-1+(Jx+Ix))Pz )/(Jx-Ix)
// P'x = ( 2az/(Bx-Ax)Px + (Bx+Ax)/(Bx-Ax)Pz ) * (1/(Jx-Ix)) + (-1+Jx+Ix)Pz/(Jx-Ix)
// P'x = ( Q'x ) * (1/(Jx-Ix)) + ( -Q'w ) * (-1+Jx+Ix)/(Jx-Ix)
//
// P'x = ( Q'x ) * (1/(Jx-Ix)) + ( -Q'w ) * (-1+Jx+Ix)/(Jx-Ix)
// P'y = ( Q'y ) * (1/(Jy-Iy)) + ( -Q'w ) * (-1+Jy+Iy)/(Jy-Iy)
// P'z = ( Q'w ) * (zMinMax.y+zMinMax.x)/(zMinMax.y-zMinMax.x) - 2*zMinMax.x*zMinMax.y/(zMinMax.y-zMinMax.x)
// P'w = ( Q'w )
//
// clip-space point X = [Xx,Xy,Xz,Xw]^T lies inside frustum if and only if:
// foreach i in {x,y,z} : -Xw < Xi < +Xw
//
///////////////////////////////////////////////////
// light position: L=(Lx,Ly,Lz,Lw), Lw in {0,1}, Lw==0 -> light in infinity = direction light
// omnidirectional light source:
//
// edge: A->B, A=(Ax,Ay,Az,1), B=(Bx,By,Bz,1)
// shadow volume side: A->B, C = (Ax-Lx,Ay-Ly,Az-Lz,0), D = (Bx-Lx,By-Ly,Bz-Lz,0)
//
// shadow volume side lies inside frustum if:
// 1) adge A->B or A->C or B->D intersects frustum
// or
// 2) one of main diagonals of frustum intersects shadow volume side
//
// 1) edge A->B vs frustum intersection:
// X(t) = (1-t)A + tB, t in [0,1]
//
// foreach i in {x,y,z} : -X(t)w < W(t)i < +X(t)w
//
// -X(t)w < W(t)i
// -(1-t)Aw - tBw < (1-t)Ai + tBi
// -Aw + tAw - tBw < Ai - tAi + tBi
// tAw - tBw + tAi - tBi < Ai + Aw
// t(Aw - Bw + Ai - Bi) < Ai + Aw
//
// if(Aw-Bw+Ai-Bi > 0):
//   t < (Ai+Aw)/(Aw-Bw+Ai-Bi)
// 
// if(Aw-Bw+Ai-Bi > 0):
//   t > (Ai+Aw)/(Aw-Bw+Ai-Bi)
//
// if(Aw-Bw+Ai-Bi == 0) -> A == B
//
// W(t)i < W(t)w
// (1-t)Ai + tBi < (1-t)Aw + tBw
// Ai - tAi + tBi < Aw - tAw + tBw
// -tAi + tBi + tAw - tBw < Aw - Ai
//
// t(Aw - Bw - Ai + Bi) < -Ai + Aw
// 
// if(Aw-Bw-Ai+Bi > 0):
//   t < (-Ai+Aw)/(Aw-Bw-Ai+Bi)
//
// if(Aw-Bw-Ai+Bi > 0):
//   t > (-Ai+Aw)/(Aw-Bw-Ai+Bi)
//
// if(Aw-Bw-Ai+Bi == 0) -> A == B
//
// 
// tMin = 1
// tMax = 0
// foreach i in {x,y,z}:
//   if(Aw-Bw+Ai-Bi > 0):
//     tMax = min(tMax,(+Ai+Aw)/(Aw-Bw+Ai-Bi))
//   else:
//     tMin = max(tMin,(+Ai+Aw)/(Aw-Bw+Ai-Bi))
//   if(Aw-Bw-Ai+Bi > 0):
//     tMax = min(tMax,(-Ai+Aw)/(Aw-Bw-Ai+Bi))
//   else:
//     tMin = max(tMin,(-Ai+Aw)/(Aw-Bw-Ai+Bi))
//
//  return tMin <= tMax;

/**
 * @brief tests if edge intersect frustum
 * edge (A->B) is assumed to be in clip space and not degenerated: A!=B
 * requires at least 5 registers
 *
 * @param A edge starting point
 * @param B edge ending point
 *
 * @return return true if edge intersect frustum i.e. is visible
 */
bool doesEdgeIntersectFrustum(in vec4 A,in vec4 B){
  float tMin = 0.f;                         //register R0
  float tMax = 1.f;                         //register R1
  for(uint i=0u;i<3u;++i){                  //register R2
    float dividend = A[i]+A[3];             //register R3
    float divisor  = divident - B[i] - B[3];//register R4
    if(divisor > 0.f)
      tMax = min(tMax,dividend/divisor);
    else
      tMin = max(tMin,divident/divisor);
    divident = -A[i]+A[3];
    divisor = divident + B[i] - B[3];
    if(divisor > 0.f)
      tMax = min(tMax,dividend/divisor);
    else
      tMin = max(tMin,divident/divisor);
  }
  return tMin <= tMax;
}


uint doesSilhouetteIntersectsAABB(in vec3 aabbCorner,in vec3 aabbSize){
  return NO_INTERSECTION;
}

#define TILE_SIZE_IN_CLIP_SPACE0 vec2(2.f/float(8<<(3*0)))
#define TILE_SIZE_IN_CLIP_SPACE1 vec2(2.f/float(8<<(3*1)))
#define TILE_SIZE_IN_CLIP_SPACE1 vec2(2.f/float(8<<(3*2)))
#define TILE_SIZE_IN_CLIP_SPACE2 vec2(2.f/float(8<<(3*3)))
#define TILE_SIZE_IN_CLIP_SPACE3 vec2(2.f/float(8<<(3*4)))

#define TEST_SILHOUETTE_LAST(LEVEL)                                                         \
void TestSilhouette ## LEVEL(                                                               \
    uvec2 coord    ,                                                                        \
    vec2  clipCoord){                                                                       \
  uvec2 localCoord      = uvec2(INVOCATION_ID_IN_WAVEFRONT&3,INVOCATION_ID_IN_WAVEFRONT>>3);\
  uvec2 globalCoord     = (coord<<3)+ localCoord;                                           \
  vec2  globalClipCoord = clipCoord + JOIN(TILE_SIZE_IN_CLIP_SPACE,LEVEL)*localCoord;       \
  vec4  sampleCoordInClipSpace = vec4(                                                      \
    globalClipCoord+JOIN(TILE_SIZE_IN_CLIP_SPACE,LEVEL)*.5,                                 \
    texelFetch(HDT[LEVEL],ivec2(globalCoord),0).x,1);                                       \
  bool inside       = false;                                                                \
  int  multiplicity = 0    ;                                                                \
  /*TODO*/                                                                                  \
  if(inside)                                                                                \
    imageAtomicAdd(multiplicityTexture,ivec2(globalCoord),ivec4(multiplicity));             \
}



#define TEST_SILHOUETTE(LEVEL,NEXT_LEVEL)                                                          \
void testSilhouette ## LEVEL(                                                                      \
    uvec2 coord    ,                                                                               \
    vec2  clipCoord){                                                                              \
  uvec2 localCoord      = uvec2(INVOCATION_ID_IN_WAVEFRONT&3,INVOCATION_ID_IN_WAVEFRONT>>3);       \
  uvec2 globalCoord     = (coord<<3)+localCoord;                                                   \
  vec2  globalClipCoord = clipCoord + JOIN(TILE_SIZE_IN_CLIP_SPACE,LEVEL)*localCoord;              \
  vec2  zMinMax         = texelFetch(HDT[LEVEL],ivec2(globalCoord),0).xy;                          \
  vec3  aabbCorner      = vec3(globalClipCoord,zMinMax.x);                                         \
  vec3  aabbSize        = vec3(JOIN(TILE_SIZE_IN_CLIP_SPACE,LEVEL),zMinMax.y-zMinMax.x);           \
  uint  result          = doesSilhouetteIntersectsAABB(aabbCorner,aabbSize);                       \
  uint64_t intersectsBallot = ballotAMD(result==INTERSECTS);                                       \
  for(int i=0;i<RESULT_LENGTH_IN_UINT;++i){                                                        \
    uint unresolvedIntersections = uint((IntersectsBallot>>(UINT_BIT_SIZE*i))&0xffffffffu);        \
    while(unresolvedIntersections != 0u){                                                          \
      int   currentBit         = findMSB(unresolvedIntersections);                                 \
      int   currentTile        = currentBit + i*UINT_BIT_SIZE;                                     \
      uvec2 currentLocalCoord  = uvec2(currentTile&3,currentTile>>3);                              \
      uvec2 currentGlobalCoord = (coord<<3) + currentLocalCoord;                                   \
      vec2  currentClipCoord   = clipCoord + JOIN(TILE_SIZE_IN_CLIP_SPACE,LEVEL)*CurrentLocalCoord;\
      testSilhouette ## NEXT_LEVEL (currentGlobalCoord,currentClipCoord);                          \
      unresolvedIntersections &= ~(1u<<currentBit);                                                \
    }                                                                                              \
  }                                                                                                \
}

TEST_SILHOUETTE_LAST(NUMBER_OF_LEVELS_MINUS_ONE)

#if NUMBER_OF_LEVELS > 7
TEST_SILHOUETTE(6,7)
#endif

#if NUMBER_OF_LEVELS > 6
TEST_SILHOUETTE(5,6)
#endif

#if NUMBER_OF_LEVELS > 5
TEST_SILHOUETTE(4,5)
#endif

#if NUMBER_OF_LEVELS > 4
TEST_SILHOUETTE(3,4)
#endif

#if NUMBER_OF_LEVELS > 3
TEST_SILHOUETTE(2,3)
#endif

#if NUMBER_OF_LEVELS > 2
TEST_SILHOUETTE(1,2)
#endif

#if NUMBER_OF_LEVELS > 1
TEST_SILHOUETTE(0,1)
#endif

void main(){
  if(SILHOUETTE_ID_IN_DISPATCH>=nofSilhouettes)return;
  if(INVOCATION_ID_IN_WAVEFRONT<FLOATS_PER_SILHOUETTE_POINTS){
    sharedSilhouettes
      [SILHOUETTE_ID_IN_WORKGROUP]
      [INVOCATION_ID_IN_WAVEFRONT/FLOATS_PER_POINT]
      [INVOCATION_ID_IN_WAVEFRONT%FLOATS_PER_POINT]=
      silhouettes
      [SILHOUETTE_ID_IN_DISPATCH*FLOATS_PER_SILHOUETTE
      +INVOCATION_ID_IN_WAVEFRONT];
  }
  if(INVOCATION_ID_IN_WAVEFRONT==0)
    sharedMultiplicities[SILHOUETTE_ID_IN_WORKGROUP] = int(silhouettes[SILHOUETTE_ID_IN_DISPATCH*FLOATS_PER_SILHOUETTE+FLOATS_PER_SILHOUETTE_POINTS]);
  if(INVOCATION_ID_IN_WAVEFRONT<POINTS_PER_SILHOUETTE){
    sharedSilhouettes[SILHOUETTE_ID_IN_WORKGROUP][2+INVOCATION_ID_IN_WAVEFRONT] = mvp*vec4(sharedSilhouettes[SILHOUETTE_ID_IN_WORKGROUP][INVOCATION_ID_IN_WAVEFRONT].xyz*lightPosition.w-lightPosition.xyz,0);
    sharedSilhouettes[SILHOUETTE_ID_IN_WORKGROUP][0+INVOCATION_ID_IN_WAVEFRONT] = mvp*vec4(sharedSilhouettes[SILHOUETTE_ID_IN_WORKGROUP][INVOCATION_ID_IN_WAVEFRONT].xyz,1);
  }



  TestShadowFrustumHDB0(
      LEFT_DOWN_CORNER_COORD,
      LEFT_DOWN_CORNER_CLIP_COORD);
}

).";
