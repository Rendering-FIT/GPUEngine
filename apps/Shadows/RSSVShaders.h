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

uniform uint numEdge=0;
uniform vec4 lightPosition;
uniform mat4 mvp;

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

int greaterVec(vec3 a,vec3 b){
  return int(dot(ivec3(sign(a-b)),ivec3(4,2,1)));
}

int computeMult(vec3 A,vec3 B,vec3 C,vec4 L){
  vec3 n=cross(C-A,L.xyz-A*L.w);
  return int(sign(dot(n,B-A)));
}

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

    for(int i=2;i<Num;++i){
#define T0 P[0].xyz
#define T1 P[1].xyz
#define T2 edges[gid+i].xyz
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
  }
  uint64_t isSilhouette = ballotAMD(Multiplicity!=0);
  if(gl_LocalInvocationID.x==0){
    uint nofSilhouettes = bitCount(uint(isSilhouette&0xffffffffu))+bitCount(uint(isSilhouette>>32));
    globalOffset = atomicAdd(dispatchIndirectBuffer[0],nofSilhouettes);
  }
  uint threadMaskLow  = uint(1u<<(gl_LocalInvocationID.x                               ))-1u;
  uint threadMaskHigh = uint(1u<<(gl_LocalInvocationID.x<32?0:gl_LocalInvocationID.x-32))-1u;
  uint localOffset = bitCount(uint(isSilhouette&0xffffffffu)&threadMaskLow)+bitCount(uint(isSilhouette>>32)&threadMaskHigh);
  uint offset=(globalOffset+localOffset)*7;
  if(Multiplicity!=0){
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

/*
#define TEST_SILHOUETTE_LAST(LEVEL)\
void TestSilhouetteHDB##LEVEL(uvec2 Coord,vec2 ClipCoord){\
  uvec2 LocalCoord             = uvec2(INVOCATION_ID_IN_WAVEFRONT&3,INVOCATION_ID_IN_WAVEFRONT>>3);\
  uvec2 GlobalCoord            = Coord*uvec2(8,8)+LocalCoord;\
  vec2  GlobalClipCoord        = ClipCoord+vec2(2.f/float(8<<(3*LEVEL)))*LocalCoord;\
  vec4  SampleCoordInClipSpace = vec4(\
    GlobalClipCoord+vec2(2.f/float(8<<(3*LEVEL)))*.5,\
    texelFetch(HDT[LEVEL],ivec2(GlobalCoord),0).x,1);\
    \
  if(SampleCoordInClipSpace.z>=1)return;\
  bool inside = true;\
  for(int p=0;p<NOF_PLANES_PER_SF;++p)\
    inside=inside && dot(SampleCoordInClipSpace,SharedShadowFrusta[SHADOWFRUSTUM_ID_IN_WORKGROUP][p])>=0;\
  if(inside)\
    imageStore(FinalStencilMask,ivec2(GlobalCoord),uvec4(SHADOW_VALUE));\
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
*/

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
