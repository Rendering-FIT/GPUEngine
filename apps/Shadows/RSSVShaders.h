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

//layout(local_size_x=WORKGROUP_SIZE_X,local_size_y=WORKGROUP_SIZE_Y,local_size_z=WORKGROUP_SIZE_Z)in;
layout(local_size_x=8,local_size_y=8)in;
layout(rg32f,binding=HIERARCHICALDEPTHTEXTURE_BINDING_HDTINPUT )uniform image2D inputLevelOfHierarchicalDepthTexture;
layout(rg32f,binding=HIERARCHICALDEPTHTEXTURE_BINDING_HDTOUTPUT)uniform image2D outputLevelOfHierarchicalDepthTexture;

uniform uvec2 windowSize = uvec2(512,512);
shared float depth[WAVEFRONT_SIZE*2];
void main(){
  uvec2 pixelCoords = gl_GlobalInvocationID.xy;
  if(any(greaterThanEqual(pixelCoords,windowSize)))return;
  vec2 minmax=imageLoad(inputLevelOfHierarchicalDepthTexture,ivec2(pixelCoords)).xy;
	depth[gl_LocalInvocationID.x               ]=minmax.x;
	depth[gl_LocalInvocationID.x+WAVEFRONT_SIZE]=minmax.y;
	for(uint threadsPerLevel = WAVEFRONT_SIZE;threadsPerLevel>1;threadsPerLevel>>=1){
		if(gl_LocalInvocationID.x<threadsPerLevel){
      uint halfThreads = threadsPerLevel>>1;
      uint doMax = uint(gl_LocalInvocationID.x>=halfThreads);
			uint BaseIndex=(gl_LocalInvocationID.x&(halfThreads-1))+(doMax*(WAVEFRONT_SIZE));
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
	if(gl_LocalInvocationID.x<1)
    imageStore(outputLevelOfHierarchicalDepthTexture,ivec2(gl_WorkGroupID.xy),vec4(depth[0],depth[WAVEFRONT_SIZE],0,0));
}
).";


