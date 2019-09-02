#pragma once
#include<iostream>


std::string const smVsSource = R".(
#version 450 core

layout(location=0) in vec3 position;

uniform mat4 lightVP;

void main()
{
	gl_Position = lightVP * vec4(position, 1);
}
).";

std::string const smMaskVs = R".(
#version 450 core

void main()
{
	gl_Position = vec4(-1+2*(gl_VertexID/2),-1+2*(gl_VertexID%2),0,1);
}
).";

std::string const smMaskFs = R".(
#version 450 core

layout(location=0) out float fColor;

layout(binding=0) uniform sampler2D			position;
layout(binding=1) uniform sampler2DShadow	shadowMap;

uniform mat4  lightVP;
uniform int  pcfSize = 0;
uniform float texelSize;

void main()
{
	ivec2 Coord = ivec2(gl_FragCoord.xy);
	vec3 viewSamplePosition = texelFetch(position,Coord,0).xyz;
	vec4 lightFragPos = lightVP * vec4(viewSamplePosition, 1);
	
	lightFragPos /= lightFragPos.w;
	lightFragPos.xyz = 0.5 * lightFragPos.xyz + 0.5;	

	float shadow = 0;

	for(int i = -pcfSize; i<=pcfSize; ++i)
	{
		for(int j = -pcfSize; j<=pcfSize; ++j)
		{
			shadow += texture(shadowMap, lightFragPos.xyz + texelSize * vec3(i, j, 0));
		}
	}

	float squareSide = 2*pcfSize + 1;
	fColor=shadow/max(squareSide*squareSide, 1);	
}
).";


