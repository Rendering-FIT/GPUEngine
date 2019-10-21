#include "FtsShaderGen.h"

#include <string>
#include <sstream>

#include <geGl/Program.h>

std::unique_ptr<ge::gl::Program> FtsShaderGen::GetZbufferFillProgram(glm::uvec3 const& bufferDims)
{   
    std::unique_ptr<ge::gl::Program> program = std::make_unique<ge::gl::Program>(
        std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, GetVS_Fill()),
        std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER, GetFS_Fill(bufferDims)));
    
    return std::move(program);
}

std::unique_ptr<ge::gl::Program> FtsShaderGen::GetZbufferTraversalProgram(glm::uvec3 const& bufferDims)
{
    std::unique_ptr<ge::gl::Program> program = std::make_unique<ge::gl::Program>(
        std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, GetVS_Traversal()),
        std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER, GetFS_Traversal(bufferDims)));

    return std::move(program);
}

std::string FtsShaderGen::GetVS_Fill() const
{
    return R".(
#version 450 core

in vec3 position;

flat out uint primitiveId;

uniform mat4 lightVP;

void main()
{
    gl_Position = lightVP * vec4(position, 1);
    primitiveId = gl_VertexID / 3;
}
).";
}

std::string FtsShaderGen::GetFS_Fill(glm::uvec3 const& bufferDims) const
{
    std::stringstream fs;

    fs << R".(
#version 450 core

layout(std430, binding=0) buffer _izb     {uint izb[];};
layout(std430, binding=1) buffer _counter {uint atomicCounter[];};

layout(pixel_center_integer) in vec4 gl_FragCoord;

flat in uint primitiveId;
).";

    fs << "#define IZB_WIDTH "  << bufferDims.x << std::endl;
    fs << "#define IZB_HEIGHT " << bufferDims.y << std::endl;
    fs << "#define IZB_DEPTH "  << bufferDims.z << std::endl << std::endl;

    fs << R".(
void main()
{
    uvec2 fragCoord = uvec2(gl_FragCoord.xy);
    const uint atomicIndex = IZB_WIDTH * uint(fragCoord.y) + uint(fragCoord.x);
    const uint depth = atomicAdd(atomicCounter[atomicIndex], 1);

    if(depth < IZB_DEPTH)
    {
        const uint izbIndex = IZB_WIDTH * IZB_DEPTH * fragCoord.y + IZB_DEPTH * fragCoord.x + depth;
        izb[izbIndex] = primitiveId;
    }
}
).";

    return fs.str();
}

std::string FtsShaderGen::GetVS_Traversal() const
{
    return R".(
#version 450 core

void main()
{
	gl_Position = vec4(-1 + 2*(gl_VertexID / 2), -1 + 2*(gl_VertexID % 2), 0, 1);
}
).";
}

std::string FtsShaderGen::GetFS_Traversal(glm::uvec3 const& bufferDims) const
{
    std::stringstream fs;

    fs << R".(
#version 450 core

layout(location=0) out float fColor;

layout(binding=0) uniform sampler2D			positionTex;
layout(binding=1) uniform sampler2DShadow	shadowMap;

layout(std430, binding=0) buffer _izb      {uint izb[];};
layout(std430, binding=1) buffer _counter  {uint counter[];};
layout(std430, binding=2) buffer _vertices {float vertices[];};

uniform mat4 lightVP;
uniform vec4 lightPos;

#define NOF_FLOATS_TRIANGLE 9u
).";

    fs << "#define IZB_WIDTH "  << bufferDims.x << std::endl;
    fs << "#define IZB_HEIGHT " << bufferDims.y << std::endl;
    fs << "#define IZB_DEPTH "  << bufferDims.z << std::endl << std::endl;

    fs << "const vec2 screenDim = uvec2(IZB_WIDTH, IZB_HEIGHT);" << std::endl;

    fs << R".(

//https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
bool rayTriangleIntersect(vec3 v0, vec3 v1, vec3 v2, vec3 rayDir, vec3 rayOrigin)
{
    const float EPSILON = 0.0000008;

    const vec3 edge1 = v1 - v0;
    const vec3 edge2 = v2 - v0;

    const vec3 h = cross(rayDir, edge2);
    const float a = dot(edge1, h);

    if (a > -EPSILON && a < EPSILON)
    {
        return false;
    }

    const float f = 1.0/a;
    const vec3 s = rayOrigin - v0;
    const float u = f * dot(s, h);

    if (u < 0.0 || u > 1.0)
    {
        return false;
    }

    const vec3 q = cross(s, edge1);
    const float v = f * dot(rayDir, q);

    if (v < 0.0 || u + v > 1.0)
    {
        return false;
    }

    const float t = f * dot(edge2, q);
    if (t > EPSILON && t < 1/EPSILON)
    {
        return true;
    }
    
    return false;
}

void main()
{
	ivec2 tcoord = ivec2(gl_FragCoord.xy);
    vec3 viewSamplePosition = texelFetch(positionTex,tcoord,0).xyz;
    
    vec4 lightFragPos = lightVP * vec4(viewSamplePosition, 1);
    
    float shadowValue = 0.f;

    const float w = lightFragPos.w;
    if(lightFragPos.x <= w && lightFragPos.x >= -w && lightFragPos.y <= w && lightFragPos.y >=-w)
    {
        lightFragPos /= lightFragPos.w;
	    lightFragPos.xyz = 0.5 * lightFragPos.xyz + 0.5;
        
        const uvec2 izbIndex = uvec2(floor(screenDim * lightFragPos.xy));
    
        const uint counterIndex = IZB_WIDTH * izbIndex.y + izbIndex.x;
        const uint nofTriangles = counter[counterIndex];

        const uint izbCoordBase = IZB_WIDTH * IZB_DEPTH * izbIndex.y + IZB_DEPTH * izbIndex.x;
        const vec3 rayDir = lightPos.xyz - lightPos.w * viewSamplePosition;
        
        shadowValue = 1.f;

        for(uint i = 0; i<nofTriangles; ++i)
        {
            const uint izbCoords = izbCoordBase + i;
            const uint triangleId = izb[izbCoords];
            const uint vertexIndexBase = triangleId * NOF_FLOATS_TRIANGLE;
        
            //Construct a triangle
            vec3 verts[3];
            verts[0] = vec3(vertices[vertexIndexBase + 0], vertices[vertexIndexBase + 1], vertices[vertexIndexBase + 2]);
            verts[1] = vec3(vertices[vertexIndexBase + 3], vertices[vertexIndexBase + 4], vertices[vertexIndexBase + 5]);
            verts[2] = vec3(vertices[vertexIndexBase + 6], vertices[vertexIndexBase + 7], vertices[vertexIndexBase + 8]);
        
            //Test for intersection
            const bool isIntersecting = rayTriangleIntersect(verts[0], verts[1], verts[2], rayDir, viewSamplePosition);

            if(isIntersecting)
            {
                shadowValue = 0.f;
                break;
            }
        }
    }

    fColor = shadowValue;
}
).";

    return fs.str();
}

