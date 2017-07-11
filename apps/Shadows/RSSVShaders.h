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
  if(gid >= numEdge)return;
  precise int multiplicity=0;

#if CULL_SIDES == 1
  vec4 P[4];
#else
  vec4 P[2];
#endif

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
  for(int o = 0; o < MAX_MULTIPLICITY; ++o)
    multiplicity += int(sign(dot(edges[gid+2+o],lightPosition)));
#else //USE_PLANES == 1
  for(int o = 2; o < Num; ++o)
    multiplicity += currentMultiplicity(P[0].xyz,P[1].xyz,edges[gid+o].xyz,lightPosition);
#endif//USE_PLANES == 1

  uint64_t isSilhouetteLong = ballotAMD(abs(multiplicity) != 0);
  uvec2 isSilhouette = unpackUint2x32(isSilhouetteLong);
  if(gl_LocalInvocationID.x == 0){
    uint nofSilhouettes = bitCount(isSilhouette.x) + bitCount(isSilhouette.y);
    globalOffset = atomicAdd(dispatchIndirectBuffer[0],nofSilhouettes);
  }

  uint threadMaskLow  = gl_LocalInvocationID.x>=32 ? 0xffffffffu : uint(1u<<(gl_LocalInvocationID.x   ))-1u;
  uint threadMaskHigh = gl_LocalInvocationID.x< 32 ? 0x00000000u : uint(1u<<(gl_LocalInvocationID.x-32))-1u;
  uint localOffset    = bitCount(isSilhouette.x & threadMaskLow) + bitCount(isSilhouette.y & threadMaskHigh);
  uint offset         = (globalOffset + localOffset) * 7;

  if(multiplicity == 0)return;
  if(multiplicity > 0){
    silhouettes[offset + 0] = P[0].x;
    silhouettes[offset + 1] = P[0].y;
    silhouettes[offset + 2] = P[0].z;
    silhouettes[offset + 3] = P[1].x;
    silhouettes[offset + 4] = P[1].y;
    silhouettes[offset + 5] = P[1].z;
    silhouettes[offset + 6] = float(+multiplicity);
  }else{
    silhouettes[offset + 0] = P[1].x;
    silhouettes[offset + 1] = P[1].y;
    silhouettes[offset + 2] = P[1].z;
    silhouettes[offset + 3] = P[0].x;
    silhouettes[offset + 4] = P[0].y;
    silhouettes[offset + 5] = P[0].z;
    silhouettes[offset + 6] = float(-multiplicity);
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
#define FLOATS_PER_SILHOUETTE_POINTS       (FLOATS_PER_POINT * POINTS_PER_SILHOUETTE)
#define FLOATS_PER_SILHOUETTE_MULTIPLICITY 1
#define FLOATS_PER_SILHOUETTE              (FLOATS_PER_SILHOUETTE_POINTS + FLOATS_PER_SILHOUETTE_MULTIPLICITY)
#define VEC4_PER_SIDE                      4
#define RESULT_LENGTH_IN_UINT              (WAVEFRONT_SIZE/UINT_BIT_SIZE)

layout(local_size_x=WORKGROUP_SIZE_X,local_size_y=WORKGROUP_SIZE_Y,local_size_z=WORKGROUP_SIZE_Z)in;

layout(       binding=RASTERIZE_BINDING_HDT        )uniform sampler2D HDT[NUMBER_OF_LEVELS];
layout(r32i  ,binding=RASTERIZE_BINDING_SSM        )uniform iimage2D screenSpaceMultiplicity;
layout(std430,binding=RASTERIZE_BINDING_SILHOUETTES)buffer Silhouettes{float silhouettes[];};

uniform uint nofSilhouettes = 0;
uniform vec4 lightPosition = vec4(100,100,100,1);
uniform mat4 mvp = mat4(1);

shared vec4 sharedSilhouettePoints        [SILHOUETTES_PER_WORKGROUP][POINTS_PER_SILHOUETTE];
shared int  sharedSilhouetteMultiplicities[SILHOUETTES_PER_WORKGROUP]                       ;

shared vec4 sharedSilhouettes   [SILHOUETTES_PER_WORKGROUP][VEC4_PER_SHADOWFRUSTUM];
shared int  sharedMultiplicities[SILHOUETTES_PER_WORKGROUP];
shared vec4 sharedSidePlanes    [SILHOUETTES_PER_WORKGROUP];

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
// P'x = 2az/(Ax*(1-Jx)+Bx* Jx -Ax*(1-Ix)-Bx* Ix )Px+(Ax*(1-Jx)+Bx* Jx +Ax*(1-Ix)+Bx* Ix )/(Ax*(1-Jx)+Bx* Jx -Ax*(1-Ix)-Bx* Ix )Pz
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

/**
 * @brief This function moves point in clip-space into clip-space of subfrustum
 *
 * @param point input point in clip-space
 * @param leftRightInterpolation interpolation parameters [0,1] for left and right side of sub frustum
 * @param bottomTopInterpolation interpolation parameters [0,1] for bottom and top side of sub frustum
 * @param nearFar near and far planes of sub frustum computed using minima and maxima of z
 *
 * @return point in clip-space of sub frustum
 */
vec4 movePointToSubfrustum(
    in vec4 point    ,
    in vec2 leftRight,
    in vec2 bottomTop,
    in vec2 nearFar  ){
  vec4 result;
  result.x = (point.x + -point.w * ( -1 + leftRight.y + leftRight.x)) / (leftRight.y - leftRight.x);
  result.y = (point.y + -point.w * ( -1 + bottomTop.y + bottomTop.x)) / (bottomTop.y - bottomTop.x);
  result.z = (point.w * (nearFar.y + nearFar.x) - 2 * nearFar.x * nearFar.y ) / (nearFar.y - nearFar.x);
  result.w = point.w;
  return result;
}

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//
// light position: L=(Lx,Ly,Lz,Lw), Lw in {0,1}, Lw==0 -> light in infinity = direction light
// omnidirectional light source:
//
// edge: A->B, A=(Ax,Ay,Az,1), B=(Bx,By,Bz,1)
// shadow volume side: A->B, C = (Ax-Lx,Ay-Ly,Az-Lz,0), D = (Bx-Lx,By-Ly,Bz-Lz,0)
//
// Shadow volume side intersects inside frustum if:
// 1) edge A->B or A->C or B->D intersects frustum
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
// Algorithm0(A,B):
//   tMin = 0
//   tMax = 1
//   foreach i in {x,y,z}:
//     if(Aw-Bw+Ai-Bi > 0):
//       tMax = min(tMax,(+Ai+Aw)/(Aw-Bw+Ai-Bi))
//
//     if(Aw-Bw+Ai-Bi < 0):
//       tMin = max(tMin,(+Ai+Aw)/(Aw-Bw+Ai-Bi))
//
//     if(Aw-Bw+Ai-Bi == 0):
//       if(+Ai+Aw < 0):return false
//
//     if(Aw-Bw-Ai+Bi > 0):
//       tMax = min(tMax,(-Ai+Aw)/(Aw-Bw-Ai+Bi))
//
//     if(Aw-Bw-Ai+Bi < 0):
//       tMin = max(tMin,(-Ai+Aw)/(Aw-Bw-Ai+Bi))
//
//     if(Aw-Bw-Ai+Bi == 0):
//       if(-Ai+Aw < 0):return false
//   return tMin <= tMax;
//
// Algorithm0(A,A):
//   tMin = 0
//   tMax = 1
//   foreach i in {x,y,z}:
//     if(+Ai+Aw < 0):return false
//     if(-Ai+Aw < 0):return false
//   return tMin <= tMax;
//
// Algorithm0(A,0):
//   return true
//

/**
 * @brief This function tests if edge intersects frustum
 * edge (A->B) is assumed to be in clip space
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
    if(divisor < 0.f)
      tMin = max(tMin,divident/divisor);
    if(divisor == 0.f && dividend < 0.f)
      return false;
    dividend = -A[i]+A[3];
    divisor = divident + B[i] - B[3];
    if(divisor > 0.f)
      tMax = min(tMax,dividend/divisor);
    if(divisor < 0.f)
      tMin = max(tMin,divident/divisor);
    if(divisor == 0.f && dividend < 0.f)
      return false;
  }
  return tMin <= tMax;
}

//
// 2) one of main diagonals of frustum intersects shadow volume side
// corners of frustum in clip-space:
// C0 = (-1,-1,-1,1)
// C1 = (+1,-1,-1,1)
// C2 = (-1,+1,-1,1)
// C3 = (+1,+1,-1,1)
// C4 = (-1,-1,-1,1)
// C5 = (+1,-1,-1,1)
// C6 = (-1,+1,-1,1)
// C7 = (+1,+1,-1,1)
//
// C(i) = (-1+2*((i>>0)&1),-1+2*((i>>1)&1),-1+2*((i>>2)&1),1)
//
// If main diagonal intersect shadow volume side in point X then:
// X.x ==  X.y ==  X.z   C0->C7
// X.x == -X.y == -X.z   C1->C6
// X.x == -X.y ==  X.z   C2->C5
// X.x ==  X.y == -X.z   C3->C4
//
// edge: A->B, A=(Ax,Ay,Az,1), B=(Bx,By,Bz,1)
// shadow volume side: A->B, C = (Ax-Lx,Ay-Ly,Az-Lz,0), D = (Bx-Lx,By-Ly,Bz-Lz,0)
//
// M(t) = (1-t)*A+t*B
// O(t) = (1-t)*C+t*D
// X(t,l) = (1-l)*M(t) + l*O(t)
// X(t,l) = (1-l)*(1-t)*A + (1-l)*t*B + l*(1-t)*C + l*t*D
// X(t,l) = A -l*A -t*A + t*l*A + t*B - t*l*B + l*C - t*l*C + t*l*D
// X(t,l) = A + l*(C-A) + t*(B-A) + t*l*(A-B-C+D)
// X(t,l) = A + l*((Ax-Lx,Ay-Ly,Az-Lz,0)-(Ax,Ay,Az,1)) + t*(B-A) + t*l*(A-B-C+D)
// X(t,l) = A + l*((-Lx,-Ly,-Lz,-1)) + t*(B-A) + t*l*(A-B-C+D)
// X(t,l) = A - l*L + t*(B-A) + t*l*(A-B-C+D)
// X(t,l) = A - l*L + t*(B-A) + t*l*((Ax,Ay,Az,1)-(Bx,By,Bz,1)-(Ax-Lx,Ay-Ly,Az-Lz,0)+(Bx-Lx,By-Ly,Bz-Lz,0))
// X(t,l) = A - l*L + t*(B-A) + t*l*((Ax-Bx,Ay-By,Az-Bz,0)-(Ax-Lx,Ay-Ly,Az-Lz,0)+(Bx-Lx,By-Ly,Bz-Lz,0))
// X(t,l) = A - l*L + t*(B-A) + t*l*((Lx-Bx,Ly-By,Lz-Bz,0)+(Bx-Lx,By-Ly,Bz-Lz,0))
// X(t,l) = A - l*L + t*(B-A) + t*l*0
// X(t,l) = A - l*L + t*(B-A)
//
// X(t,l)x == X(t,l)y
//
// X(t,l)x ==  X(t,l)y && X(t,l)x ==  X(t,l)z    C0->C7
// X(t,l)x == -X(t,l)y && X(t,l)x == -X(t,l)z    C1->C6
// X(t,l)x == -X(t,l)y && X(t,l)x ==  X(t,l)z    C2->C5
// X(t,l)x ==  X(t,l)y && X(t,l)x == -X(t,l)z    C3->C4
//
// X(t,l)x == aX(t,l)y && X(t,l)x == bX(t,l)z, a,b in {-1,1}
//
// Ax - l*Lx + t*(Bx-Ax) == aAy - al*Ly + at*(By-Ay)
// (Ax-aAy) + l*(aLy-Lx) + t*(Bx-Ay-aBy+aAy) = 0
// t*(Bx-Ay-aBy+aAy) + l*(aLy-Lx) = (aAy-Ax)
//
// Ax - l*Lx + t*(Bx-Ax) == bAz - bl*Lz + bt*(Bz-Az)
// t*(Bx-Ay-bBz+bAz) + l*(bLz-Lx) = (bAz-Ax)
//
// t*(Bx-Ay-aBy+aAy) + l*(aLy-Lx) = (aAy-Ax)
// t*(Bx-Ay-bBz+bAz) + l*(bLz-Lx) = (bAz-Ax)
//
// t*u + l*v = w
// t*x + l*y = z
//
//     |w v|  / |u v|
// t = |z y| /  |x y|
//
// l = (w-t*u)/v
//  
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//
//

/**
 * @brief This function tests if diagonal of frustum intersects shadow volume side
 *
 * @param A edge point in clip-space
 * @param B edge point in clip-space
 * @param L light position in clip-space
 * @param D diagonal index
 *
 * @return This function returns true if diagonal intersects shadow volume side.
 */
bool doesDiagonalIntersectShadowVolumeSide(in vec4 A,in vec4 B,in vec4 L,in uint D){
  float a = -1.f + 2.f*float(d/2);
  float b = -1.f + 2.f*float(d&1);
  float u = B.x - A.y - a*B.y + a*A.y;
  float v = a*L.y - L.x;
  float w = a*A.y - A.x;
  float x = B.x - A.y - b*B.z + b*A.z;
  float y = b*L.z - L.x;
  float z = b*A.z - A.x;
  float divisor  = u*y - x*v;
  float dividend = w*y - z*v;
  if(divisor == 0.f)return false;
  float t = (w*y - z*v) / (u*y - x*v);
  if(t < 0.f || t > 1.f)return false;
  if(v == 0.f)return false;
  float l = (w-t*u)/v;
  if(l < 0.f || l > 1.f)return false;
  return true;
}

/**
 * @brief This function tests if shadow volume side intersects frustum.
 *
 * @param A edge point in clip-space
 * @param B edge point in clip-space
 * @param L light position in clip-space
 *
 * @return This function returns true if shadow volume side intersects frustum 
 */
bool doesShadowVolumeSideIntersectsFrustum(in vec4 A,in vec4 B,in vec4 L){
  for(uint d=0;d<4;++d)
    if(doesDiagonalIntersectShadowVolumeSide(A,B,L,d))return true;
  if(doesEdgeIntersectFrustum(A,B))return true;
  if(doesEdgeIntersectFrustum(A,A-L))return true;
  return doesEdgeIntersectFrustum(B,B-L);
}

// PxAx + PyAy + PzAz = 0
// PxBx + PyBy + PzBz = 0
// Pz = 1
//
//
// Px = |Ay -AzPz|  / |Ax Ay|
//      |By -BzPz| /  |Bx By|
//
// Py = |Ax -AzPz|  / |Ax Ay|
//      |Bx -BzPz| /  |Bx By|
//
// Px = (ByAz-AyBz)/(AxBy-BxAy)*Pz
// Py = (BxAz-AxBz)/(AxBy-BxAy)*Pz
//
// Px = (ByAz-AyBz)/(AxBy-BxAy)
// Py = (BxAz-AxBz)/(AxBy-BxAy)
//
// 

/**
 * @brief This function tests if edge formed by two pixels intersects shadow volume side.
 *
 * @param A point of edge of shadow volume side in clip-space
 * @param B point of edge of shadow volume side in clip-space
 * @param L light position in clip-space
 * @param PA pixel position in clip-space
 * @param PB pixel position in clip-space
 *
 * @return This function returns -1,0,1: 0 - no intersection, 1 - intersection and PA is in front of shadow volume side.
 */
int doesScreenEdgeIntersectsShadowVolumeSide(
    in vec4 A           ,
    in vec4 B           ,
    in vec4 L           ,
    in vec4 PA          ,
    in vec4 PB          ,
    in int  multiplicity){
  vec3 LL  = L .xyz/L .w;
  vec3 PPA = PA.xyz/PA.w;
  vec3 PPB = PB.xyz/PB.w;
  vec3 BB  = B .xyz/B .w;
  vec3 AA  = A .xyz/A .w;
  vec3 pixelPlaneNormal     = cross(PPB - PPA,LL  - PPA);
  vec3 sidePlaneNormal      = cross(BB  - AA ,LL  - AA );
  vec3 sidePixelPlaneNormal = cross(BB  - AA ,PPB - PPA);
  vec4 pixelPlane           = vec4(pixelPlaneNormal    ,-dot(PA.xyz,pixelPlaneNormal    )/PA.w);
  vec4 sidePlane            = vec4(sidePlaneNormal     ,-dot(A .xyz,sidePlaneNormal     )/A .w);
  vec4 sidePixelPlane       = vec4(sidePixelPlaneNormal,-dot(A .xyz,sidePixelPlaneNormal)/A .w);

  float spa = dot(sidePlane,PA);
  float spb = dot(sidePlane,PB);

  float ppa = dot(pixelPlane,A);
  float ppb = dot(pixelPlane,B);

  if(ppa >  0 && ppb >  0)return 0;
  if(ppa <= 0 && ppb <= 0)return 0;

  if(multiplicity < 0){
    if(spa >= 0 && spb >= 0)return 0;
    if(spa <  0 && spb <  0)return 0;

    if(dot(sidePixelPlane,PA) > 0)return 0;
  }

  if(multiplicity > 0{
    if(spa <= 0 && spb <= 0)return 0;
    if(spa >  0 && spb >  0)return 0;

    if(dot(sidePixelPlane,PA) >= 0)return 0;
  }


  if(multiplicity < 0){
    if(spa >= 0 && spb < 0)return multiplicity;
    return -multiplicity;
  }

  if(spa > 0 && spb <= 0)return multiplicity;
  return -multiplicity;

}

#define TILE_SIZE_IN_CLIP_SPACE0 vec2(2.f/float(8<<(3*0)))
#define TILE_SIZE_IN_CLIP_SPACE1 vec2(2.f/float(8<<(3*1)))
#define TILE_SIZE_IN_CLIP_SPACE1 vec2(2.f/float(8<<(3*2)))
#define TILE_SIZE_IN_CLIP_SPACE2 vec2(2.f/float(8<<(3*3)))
#define TILE_SIZE_IN_CLIP_SPACE3 vec2(2.f/float(8<<(3*4)))

#define TILE_BOTTOM_LEFT_TO_RIGHT 0u
#define TILE_BOTTOM_LEFT_TO_TOP   1u
#define TILE_TOP_RIGHT_TO_LEFT    2u
#define TILE_TOP_RIGHT_TO_BOTTOM  3u

#define TILE_TRANSPOSE(tile) (tile^0xfffffffeu) // inverse lsb
#define TILE_INVERSE(tile)   (tile^0xfffffffdu) // inverse second lsb

#define TILE_TRANSPOSE_CONDITION(tile,condition)         (tile ^ (~(uint(condition)<<0)) )
#define TILE_INVERSE_CONDITION(tile,condition)           (tile ^ (~(uint(condition)<<1)) )
#define TILE_TRANSPOSE_INVERSE_CONDITION(tile,condition) (tile ^ (~(uint(condition)* 3)) )

#define IS_ODD(x)  bool(x&1)
#define IS_EVEN(x) (!IS_ODD(x))

#define IS_LESS_THAN_SIZE_MINUS_ONE(x,size) (x<(size-1))

#define IS_ON_OPPOSITE_LINE(id,size,orientation)\
  (id[orientation&1] == ((size[orientation&1]-1)*(1-(orientation>>1)&1))

#define IS_ON_EVEN_LINE(id,size,orientation)\
  IS_EVEN((id[tileOrientation&1] + ((tileOrientation>>1)&1) + tileOrientation>>1))

/*
#define GET_SUBTILE_ORIENTATION(tileOrientation,id,size)(\
  tileOrientation == TILE_BOTTOM_LEFT_TO_RIGHT ? ( IS_LESS_THAN_SIZE_MINUS_ONE(        id[1]  ,size[1]) ? TILE_INVERSE(TILE_BOTTOM_LEFT_TO_TOP  ,IS_EVEN(        id[0]  )) : TILE_BOTTOM_LEFT_TO_RIGHT ) : (\
  tileOrientation == TILE_BOTTOM_LEFT_TO_TOP   ? ( IS_LESS_THAN_SIZE_MINUS_ONE(        id[0]  ,size[0]) ? TILE_INVERSE(TILE_BOTTOM_LEFT_TO_RIGHT,IS_EVEN(        id[1]  )) : TILE_BOTTOM_LEFT_TO_TOP   ) : (\
  tileOrientation == TILE_TOP_RIGHT_TO_LEFT    ? ( IS_LESS_THAN_SIZE_MINUS_ONE(size[1]-id[1]-1,size[1]) ? TILE_INVERSE(TILE_TOP_RIGHT_TO_BOTTOM ,IS_EVEN(size[0]-id[0]-1)) : TILE_TOP_RIGHT_TO_LEFT    ) : (\
                                                 ( IS_LESS_THAN_SIZE_MINUS_ONE(size[0]-id[0]-1,size[0]) ? TILE_INVERSE(TILE_TOP_RIGHT_TO_LEFT   ,IS_EVEN(size[1]-id[1]-1)) : TILE_TOP_RIGHT_TO_BOTTOM  )    \
  ))))
*/

/*
#define GET_SUBTILE_ORIENTATION(tileOrientation,id,size)(\
  tileOrientation == 0 ? (         id[1]  <size[1]-1 ? TILE_INVERSE(TILE_TRASPOSE(tileOrientation),IS_EVEN(        id[0]  )) : tileOrientation ) : (\
  tileOrientation == 1 ? (         id[0]  <size[0]-1 ? TILE_INVERSE(TILE_TRASPOSE(tileOrientation),IS_EVEN(        id[1]  )) : tileOrientation ) : (\
  tileOrientation == 2 ? ( size[1]-id[1]-1<size[1]-1 ? TILE_INVERSE(TILE_TRASPOSE(tileOrientation),IS_EVEN(size[0]-id[0]-1)) : tileOrientation ) : (\
                         ( size[0]-id[0]-1<size[0]-1 ? TILE_INVERSE(TILE_TRASPOSE(tileOrientation),IS_EVEN(size[1]-id[1]-1)) : tileOrientation )    \
  ))))
*/

/*
#define GET_SUBTILE_ORIENTATION(tileOrientation,id,size)(\
  tileOrientation==0?(                             id[1-(tileOrientation&1)]  <size[1-(tileOrientation&1)]-1?TILE_INVERSE(TILE_TRASPOSE(tileOrientation),IS_EVEN(                        id[tileOrientation&1]  )):tileOrientation ):(\
  tileOrientation==1?(                             id[1-(tileOrientation&1)]  <size[1-(tileOrientation&1)]-1?TILE_INVERSE(TILE_TRASPOSE(tileOrientation),IS_EVEN(                        id[tileOrientation&1]  )):tileOrientation ):(\
  tileOrientation==2?( size[1-(tileOrientation&1)]-id[1-(tileOrientation&1)]-1<size[1-(tileOrientation&1)]-1?TILE_INVERSE(TILE_TRASPOSE(tileOrientation),IS_EVEN(size[tileOrientation&1]-id[tileOrientation&1]-1)):tileOrientation ):(\
                     ( size[1-(tileOrientation&1)]-id[1-(tileOrientation&1)]-1<size[1-(tileOrientation&1)]-1?TILE_INVERSE(TILE_TRASPOSE(tileOrientation),IS_EVEN(size[tileOrientation&1]-id[tileOrientation&1]-1)):tileOrientation )  \
  ))))
*/

#define GET_SUBTILE_ORIENTATION(tileOrientation,id,size)(\
  tileOrientation==0?(IS_ON_OPPOSITE_LINE(id,size,tileOrientation)?TILE_INVERSE(TILE_TRASPOSE(tileOrientation),IS_EVEN(                        id[tileOrientation&1]  )):tileOrientation ):(\
  tileOrientation==1?(IS_ON_OPPOSITE_LINE(id,size,tileOrientation)?TILE_INVERSE(TILE_TRASPOSE(tileOrientation),IS_EVEN(                        id[tileOrientation&1]  )):tileOrientation ):(\
  tileOrientation==2?(IS_ON_OPPOSITE_LINE(id,size,tileOrientation)?TILE_INVERSE(TILE_TRASPOSE(tileOrientation),IS_EVEN(size[tileOrientation&1]-id[tileOrientation&1]-1)):tileOrientation ):(\
                     (IS_ON_OPPOSITE_LINE(id,size,tileOrientation)?TILE_INVERSE(TILE_TRASPOSE(tileOrientation),IS_EVEN(size[tileOrientation&1]-id[tileOrientation&1]-1)):tileOrientation )  \
  ))))

#define TRANSFORM_BALLOT_RESULT_TO_UINTS(result)\
  unpackUint2x32(result)

#define UINT_RESULT_ARRAY uvec2

#define GET_UINT_FROM_UINT_ARRAY(array,i)\
  array[i]

#define BALLOT(x) ballotAMD(x)

#define UPPER_TILE_DIVISIBILITY_MASK(level)\
  uvec2(7u,7u)

#define UPPER_TILE_DIVISIBILITY_EXPONENT(level)\
  uvec2(3u,3u);

#define TILE_INDEX_TO_TILE_COORD(invocation,level)\
  uvec2(invocation&UPPER_TILE_DIVISIBILITY_MASK(level).x,invocation>>UPPER_TILE_DIVISIBILITY_EXPONENT(level).x)

#define GET_GLOBAL_COORD(coord,localCoord,level)\
  ((coord<<UPPER_TILE_DIVISIBILITY_EXPONENT(level)) + localCoord)

#define MARK_BIT_AS_SOLVED(mask,bit)\
  mask &= ~(1u<<bit)

#define GET_TILE_MINMAX_DEPTH(level,coord)\
  vec2(texelFetch(HDT[level],ivec2(coord),0).xy)

#define GET_TILE_MIN_DEPTH(level,coord)\
  GET_TILE_MINMAX_DEPTH(level,coord).x

#define GET_TILE_SIZE_IN_CLIP_SPACE(level)\
  JOIN(TILE_SIZE_IN_CLIP_SPACE,LEVEL)


#define TEST_SILHOUETTE_LAST(LEVEL)                                                                                  \
  shared vec4 viewSamples[WAVEFRONT_SIZE];                                                                           \
  void JOIN(testSilhouette,LEVEL)(                                                                                   \
      uvec2 leftBottomCoord    ,                                                                                     \
      vec2  leftBottomClipCoord){                                                                                    \
    uvec2 localCoord      = TILE_INDEX_TO_TILE_COORD(INVOCATION_ID_IN_WAVEFRONT,LEVEL);                              \
    uvec2 globalCoord     = GET_GLOBAL_COORD(leftBottomCoord,localCoord,LEVEL);                                      \
    vec2  globalClipCoord = leftBottomClipCoord + GET_TILE_SIZE_IN_CLIP_SPACE(LEVEL)*localCoord;                     \
    vec2  minmax          = GET_TILE_MINMAX_DEPTH(level,coord);                                                      \
    vec4  viewSample = vec4(                                                                                         \
        globalClipCoord+GET_TILE_SIZE_IN_CLIP_SPACE(LEVEL)*.5,                                                       \
        minmax.x,1);                                                                                                 \
    viewSamples[INVOCATION_ID_IN_WAVEFRONT] = viewSample;                                                            \
    if(INVOCATION_ID_IN_WAVEFRONT == WAVEFRONT_SIZE-1)return;                                                        \
    vec4 nextViewSample = viewSamples[INVOCATION_ID_IN_WAVEFRONT+1];                                                 \
    int  multiplicity = sharedMultiplicities[SILHOUETTE_ID_IN_WORKGROUP];                                            \
    vec2 leftRight = (globalClipCoord.xx + vec2(0,GET_TILE_SIZE_IN_CLIP_SPACE(LEVEL).x))*.5+.5;                      \
    vec2 bottomTop = (globalClipCoord.yy + vec2(0,GET_TILE_SIZE_IN_CLIP_SPACE(LEVEL).y))*.5+.5;                      \
    vec4 A = movePointToSubfrustum(sharedSilhouettePoints[SILHOUETTE_ID_IN_WORKGROUP][0],leftRight,bottomTop,minmax);\
    vec4 B = movePointToSubfrustum(sharedSilhouettePoints[SILHOUETTE_ID_IN_WORKGROUP][1],leftRight,bottomTop,minmax);\
    vec4 L = movePointToSubfrustum(lightPosition                                        ,leftRight,bottomTop,minmax);\
    int resultMultiplicity = doesScreenEdgeIntersectsShadowVolumeSide(A,B,L,viewSample,nextViewSample,multiplicity); \
    if(resultMultiplicity != 0)                                                                                      \
      imageAtomicAdd(multiplicityTexture,ivec2(globalCoord),ivec4(resultMultiplicity));                              \
  }

#define TEST_SILHOUETTE(LEVEL,NEXT_LEVEL)                                                                      \
  void JOIN(testSilhouette,LEVEL)(                                                                             \
      uvec2 leftBottomCoord    ,                                                                               \
      vec2  leftBottomClipCoord){                                                                              \
    uvec2             localCoord       = TILE_INDEX_TO_TILE_COORD(INVOCATION_ID_IN_WAVEFRONT,LEVEL);           \
    uvec2             globalCoord      = GET_GLOBAL_COORD(leftBottomCoord,localCoord,LEVEL);                   \
    vec2              globalClipCoord  = leftBottomClipCoord + GET_TILE_SIZE_IN_CLIP_SPACE(LEVEL)*localCoord;  \
    vec2              zMinMax          = GET_TILE_MINMAX_DEPTH(LEVEL,globalCoord);                             \
    vec3              aabbCorner       = vec3(globalClipCoord,zMinMax.x);                                      \
    vec3              aabbSize         = vec3(JOIN(TILE_SIZE_IN_CLIP_SPACE,LEVEL),zMinMax.y-zMinMax.x);        \
    uint              result           = doesSilhouetteIntersectsAABB(aabbCorner,aabbSize);                    \
    UINT_RESULT_ARRAY intersectsBallot = TRANSFORM_BALLOT_RESULT_TO_UINTS(BALLOT(result==INTERSECTS));         \
    for(int i = 0; i < RESULT_LENGTH_IN_UINT; ++i){                                                            \
      uint unresolvedIntersections = GET_UINT_FROM_UNIT_ARRAY(intersectsBallot,i);                             \
      while(unresolvedIntersections != 0u){                                                                    \
        int   currentBit         = findMSB(unresolvedIntersections);                                           \
        int   currentTile        = currentBit + i*UINT_BIT_SIZE;                                               \
        uvec2 currentLocalCoord  = TILE_INDEX_TO_TILE_COORD(currentTile,level);                                \
        uvec2 currentGlobalCoord = GET_GLOBAL_COORD(leftBottomCoord,currentLocalCoord,LEVEL);                  \
        vec2  currentClipCoord   = leftBottomClipCoord + JOIN(TILE_SIZE_IN_CLIP_SPACE,LEVEL)*CurrentLocalCoord;\
        JOIN(testSilhouette,NEXT_LEVEL)(currentGlobalCoord,currentClipCoord);                                  \
        MARK_BIT_AS_SOLVED(unresolvedIntersections,currentBit);                                                \
      }                                                                                                        \
    }                                                                                                          \
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
  if(SILHOUETTE_ID_IN_DISPATCH >= nofSilhouettes)return;

  if(INVOCATION_ID_IN_WAVEFRONT < SILHOUETTE_ID_IN_WORKGROUP){
    sharedSilhouettePoints[INVOCATION_ID_IN_WAVEFRONT][0] = mvp * vec4(
      silhouettes[SILHOUETTE_ID_IN_DISPATCH*FLOATS_PER_SILHOUETTE + 0],
      silhouettes[SILHOUETTE_ID_IN_DISPATCH*FLOATS_PER_SILHOUETTE + 1],
      silhouettes[SILHOUETTE_ID_IN_DISPATCH*FLOATS_PER_SILHOUETTE + 2],
      1);
    sharedSilhouettePoints[INVOCATION_ID_IN_WAVEFRONT][1] = mvp * vec4(
      silhouettes[SILHOUETTE_ID_IN_DISPATCH*FLOATS_PER_SILHOUETTE + 3],
      silhouettes[SILHOUETTE_ID_IN_DISPATCH*FLOATS_PER_SILHOUETTE + 4],
      silhouettes[SILHOUETTE_ID_IN_DISPATCH*FLOATS_PER_SILHOUETTE + 5],
      1);
    sharedSilhouetteMultiplicities[INVOCATION_ID_IN_WAVEFRONT] = int(
      silhouettes[SILHOUETTE_ID_IN_DISPATCH*FLOATS_PER_SILHOUETTE + 6]);
  }

  testSilhouette0(uvec2(0),vec2(-1));
}

).";
