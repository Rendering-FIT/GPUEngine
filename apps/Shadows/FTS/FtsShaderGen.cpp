#include "FtsShaderGen.h"

#include <string>
#include <sstream>

#include <geGl/Program.h>

std::unique_ptr<ge::gl::Program> FtsShaderGen::GetIzbFillProgram(glm::uvec3 const& bufferDims)
{   
    std::unique_ptr<ge::gl::Program> program = std::make_unique<ge::gl::Program>(
        std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, GetVSFill()),
        std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER, GetFSFill(bufferDims)));
    
    return std::move(program);
}

std::unique_ptr<ge::gl::Program> FtsShaderGen::GetIzbTraversalProgram(glm::uvec3 const& bufferDims)
{
    std::unique_ptr<ge::gl::Program> program = std::make_unique<ge::gl::Program>(
        std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, GetVSTraversal()),
        std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER, GetFSTraversal(bufferDims)));

    return std::move(program);
}

std::unique_ptr<ge::gl::Program> FtsShaderGen::GetIzbFillProgramOmnidir(glm::uvec3 const& bufferDims)
{
    std::unique_ptr<ge::gl::Program> program = std::make_unique<ge::gl::Program>(
        std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, GetVSFillOmnidir()),
        std::make_shared<ge::gl::Shader>(GL_GEOMETRY_SHADER, GetGSFillOmnidir()),
        std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER, GetFSFillOmnidir(bufferDims)));

    return std::move(program);
}

std::unique_ptr<ge::gl::Program> FtsShaderGen::GetIzbTraversalProgramOmnidirRaytrace(glm::uvec3 const& bufferDims)
{
    std::unique_ptr<ge::gl::Program> program = std::make_unique<ge::gl::Program>(
        std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, GetVSTraversal()),
        std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER, GetFSTraversalOmnidirRaytrace(bufferDims)));

    return std::move(program);
}


std::unique_ptr<ge::gl::Program> FtsShaderGen::GetIzbTraversalProgramOmnidirFrusta(glm::uvec3 const& bufferDims)
{
    std::unique_ptr<ge::gl::Program> program = std::make_unique<ge::gl::Program>(
        std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, GetVSTraversal()),
        std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER, GetFSTraversalOmnidirFrusta(bufferDims)));

    return std::move(program);
}

std::unique_ptr<ge::gl::Program> FtsShaderGen::GetTrianglePreprocessCS(uint32_t wgSize)
{
    std::unique_ptr<ge::gl::Program> program = std::make_unique<ge::gl::Program>(
        std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER, GetCSPreprocess(wgSize)));

    return std::move(program);
}


std::string FtsShaderGen::GetVSFill() const
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

std::string FtsShaderGen::GetFSFill(glm::uvec3 const& bufferDims) const
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

    fs << GetIzbAddressingFunction();

    fs << R".(
void main()
{
    uvec2 fragCoord = uvec2(gl_FragCoord.xy);
    const uint atomicIndex = IZB_WIDTH * uint(fragCoord.y) + uint(fragCoord.x);
    const uint depth = atomicAdd(atomicCounter[atomicIndex], 1);

    if(depth < IZB_DEPTH)
    {
        const uint izbIndex = GetIzbIndex(uvec4(uvec2(fragCoord.xy), depth, 0));//IZB_WIDTH * IZB_DEPTH * fragCoord.y + IZB_DEPTH * fragCoord.x + depth;
        izb[izbIndex] = primitiveId;
    }
}
).";

    return fs.str();
}

std::string FtsShaderGen::GetVSTraversal() const
{
    return R".(
#version 450 core

void main()
{
	gl_Position = vec4(-1 + 2*(gl_VertexID / 2), -1 + 2*(gl_VertexID % 2), 0, 1);
}
).";
}

std::string FtsShaderGen::GetFSTraversal(glm::uvec3 const& bufferDims) const
{
    std::stringstream fs;

    fs << R".(
#version 450 core

layout(location=0) out float fColor;

layout(binding=0) uniform sampler2D			positionTex;

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

    fs << "const vec2 izbSize = uvec2(IZB_WIDTH, IZB_HEIGHT);" << std::endl;
    
    fs << GetRayInersectFunction();

    fs << GetIzbAddressingFunction();

    fs << R".(

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
        
        const uvec2 izbIndex = uvec2(floor(izbSize * lightFragPos.xy));
    
        const uint counterIndex = IZB_WIDTH * izbIndex.y + izbIndex.x;
        const uint nofTriangles = counter[counterIndex];

        //const uint izbCoordBase = IZB_WIDTH * IZB_DEPTH * izbIndex.y + IZB_DEPTH * izbIndex.x;
        const vec3 rayDir = lightPos.xyz - lightPos.w * viewSamplePosition;
        
        shadowValue = 1.f;

        for(uint i = 0; i<nofTriangles; ++i)
        {
            const uint izbCoords = GetIzbIndex(uvec4(izbIndex, i, 0));//izbCoordBase + i;
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

//----------------------------------------------------------------------

std::string FtsShaderGen::GetVSFillOmnidir() const
{
    return R".(
#version 450 core

layout(location=0)in vec3 position;

uniform float near;
uniform float far;
uniform vec4 lightPos;

flat out int vInstanceID;
flat out uint vPrimitiveId;

void main()
{
    const mat4 views[6] = 
    {
        mat4(vec4(+0,+0,-1,0), vec4(+0,-1,+0,0), vec4(-1,+0,+0,0), vec4(0,0,0,1)),
        mat4(vec4(+0,+0,+1,0), vec4(+0,-1,+0,0), vec4(+1,+0,+0,0), vec4(0,0,0,1)),
        mat4(vec4(+1,+0,+0,0), vec4(+0,+0,-1,0), vec4(+0,+1,+0,0), vec4(0,0,0,1)),
        mat4(vec4(+1,+0,+0,0), vec4(+0,+0,+1,0), vec4(+0,-1,+0,0), vec4(0,0,0,1)),
        mat4(vec4(+1,+0,+0,0), vec4(+0,-1,+0,0), vec4(+0,+0,-1,0), vec4(0,0,0,1)),
        mat4(vec4(-1,+0,+0,0), vec4(+0,-1,+0,0), vec4(+0,+0,+1,0), vec4(0,0,0,1))
    };

    mat4 projection = mat4(
        vec4(1,0,0,0),
        vec4(0,1,0,0),
        vec4(0,0,-(far+near)/(far-near),-1),
        vec4(0,0,-2*far*near/(far-near),0));

    gl_Position = projection*views[gl_InstanceID]*vec4(position-lightPos.xyz,1);
    vInstanceID = gl_InstanceID;
    vPrimitiveId = gl_VertexID / 3;
}
).";
}

std::string FtsShaderGen::GetGSFillOmnidir() const
{
    return R".(
#version 450 core

layout(triangles)in;
layout(triangle_strip,max_vertices=3) out;

flat in int vInstanceID[];
flat in uint vPrimitiveId[];

flat out uint gPrimitiveId;

void main()
{
    gl_Layer = vInstanceID[0];
    
    gl_Position = gl_in[0].gl_Position; gPrimitiveId = vPrimitiveId[0]; EmitVertex();
    gl_Position = gl_in[1].gl_Position; gPrimitiveId = vPrimitiveId[0]; EmitVertex();
    gl_Position = gl_in[2].gl_Position; gPrimitiveId = vPrimitiveId[0]; EmitVertex();
    EndPrimitive();
}).";
}

std::string FtsShaderGen::GetFSFillOmnidir(glm::uvec3 const& bufferDims) const
{
    std::stringstream fs;

    fs << R".(
#version 450 core

layout(std430, binding=0) buffer _izb     {uint izb[];};
layout(std430, binding=1) buffer _counter {uint atomicCounter[];};

layout(pixel_center_integer) in vec4 gl_FragCoord;

flat in uint gPrimitiveId;
).";

    fs << "#define IZB_WIDTH " << bufferDims.x << std::endl;
    fs << "#define IZB_HEIGHT " << bufferDims.y << std::endl;
    fs << "#define IZB_DEPTH " << bufferDims.z << std::endl << std::endl;

    fs << GetIzbAddressingFunction();

    fs << R".(
void main()
{
    uvec2 fragCoord = uvec2(gl_FragCoord.xy);
    const uint outLayer = gl_Layer;
    const uint atomicIndex = IZB_WIDTH * IZB_HEIGHT * outLayer + IZB_WIDTH * uint(fragCoord.y) + uint(fragCoord.x);
    const uint depth = atomicAdd(atomicCounter[atomicIndex], 1);

    if(depth < IZB_DEPTH)
    {
        const uint izbIndex = GetIzbIndex(uvec4(uvec2(fragCoord.xy), depth, outLayer));
        izb[izbIndex] = gPrimitiveId;
    }
}
).";

    return fs.str();
}

std::string FtsShaderGen::GetFSTraversalOmnidirRaytrace(glm::uvec3 const& bufferDims) const
{
    std::stringstream fs;

    fs << R".(
#version 450 core

layout(location=0) out float fColor;

layout(binding=0) uniform sampler2D			positionTex;

layout(std430, binding=0) buffer _izb      {uint izb[];};
layout(std430, binding=1) buffer _counter  {uint counter[];};
layout(std430, binding=2) buffer _vertices {float vertices[];};

uniform vec4 lightPos;

#define NOF_FLOATS_TRIANGLE 9u
).";

    fs << "#define IZB_WIDTH " << bufferDims.x << std::endl;
    fs << "#define IZB_HEIGHT " << bufferDims.y << std::endl;
    fs << "#define IZB_DEPTH " << bufferDims.z << std::endl << std::endl;

    fs << "const vec2 izbDim = uvec2(IZB_WIDTH, IZB_HEIGHT);" << std::endl;

    fs << GetIzbAddressingFunction();

    fs << GetRayInersectFunction();

    fs << GetCubeAddressingFunction();

    fs << R".(

void main()
{
	ivec2 tcoord = ivec2(gl_FragCoord.xy);
    vec3 viewSamplePosition = texelFetch(positionTex,tcoord,0).xyz;
    
    const vec3 rayDir = viewSamplePosition - lightPos.xyz;

    uint cubeFaceIndex;   
    vec2 izbCoords = getCubeTcoords(rayDir, cubeFaceIndex);
    
    float shadowValue = 1.f;

    const uvec2 izbIndex = uvec2(floor(izbDim * izbCoords));
    
    const uint counterIndex = IZB_WIDTH * IZB_HEIGHT * cubeFaceIndex + IZB_WIDTH * izbIndex.y + izbIndex.x;
    const uint nofTriangles = counter[counterIndex];
    
    for(uint i = 0; i<nofTriangles; ++i)
    {
        const uint izbTriangleCoords = GetIzbIndex(uvec4(izbIndex, i, cubeFaceIndex));
        const uint triangleId = izb[izbTriangleCoords];
        const uint vertexIndexBase = triangleId * NOF_FLOATS_TRIANGLE;
    
        //Construct a triangle
        vec3 verts[3];
        verts[0] = vec3(vertices[vertexIndexBase + 0], vertices[vertexIndexBase + 1], vertices[vertexIndexBase + 2]);
        verts[1] = vec3(vertices[vertexIndexBase + 3], vertices[vertexIndexBase + 4], vertices[vertexIndexBase + 5]);
        verts[2] = vec3(vertices[vertexIndexBase + 6], vertices[vertexIndexBase + 7], vertices[vertexIndexBase + 8]);
    
        //Test for intersection
        const bool isIntersecting = rayTriangleIntersect(verts[0], verts[1], verts[2], -rayDir, viewSamplePosition);

        if(isIntersecting)
        {
            shadowValue = 0.f;
            break;
        }
    }

    fColor = shadowValue;
}
).";

    return fs.str();
}

std::string FtsShaderGen::GetFSTraversalOmnidirFrusta(glm::uvec3 const& bufferDims) const
{
    std::stringstream fs;

    fs << R".(
#version 450 core

layout(location = 0) out float fColor;

layout(binding = 0) uniform sampler2D			positionTex;

layout(std430, binding = 0) buffer _izb { uint izb[]; };
layout(std430, binding = 1) buffer _counter { uint counter[]; };
layout(std430, binding = 2) buffer _frusta { vec4 planes[]; };

uniform vec4 lightPos;

#define NOF_PLANES_TRIANGLE 4u
    ).";

    fs << "#define IZB_WIDTH " << bufferDims.x << std::endl;
    fs << "#define IZB_HEIGHT " << bufferDims.y << std::endl;
    fs << "#define IZB_DEPTH " << bufferDims.z << std::endl << std::endl;

    fs << "const vec2 izbDim = uvec2(IZB_WIDTH, IZB_HEIGHT);" << std::endl;

    fs << GetIzbAddressingFunction();

    fs << GetCubeAddressingFunction();

    fs << R".(

bool isPointInside(vec4 v, vec4 p1, vec4 p2, vec4 p3, vec4 p4)
{
    return dot(v, p1)<=0 && dot(v, p2)<=0 && dot(v, p3)<=0 && dot(v, p4)<=0;
}

void main()
{
	ivec2 tcoord = ivec2(gl_FragCoord.xy);
    vec3 viewSamplePosition = texelFetch(positionTex,tcoord,0).xyz;
    
    const vec3 rayDir = viewSamplePosition - lightPos.xyz;

    uint cubeFaceIndex;   
    vec2 izbCoords = getCubeTcoords(rayDir, cubeFaceIndex);
    
    float shadowValue = 1.f;

    const uvec2 izbIndex = uvec2(floor(izbDim * izbCoords));
    
    const uint counterIndex = IZB_WIDTH * IZB_HEIGHT * cubeFaceIndex + IZB_WIDTH * izbIndex.y + izbIndex.x;
    const uint nofTriangles = counter[counterIndex];
    
    for(uint i = 0; i<nofTriangles; ++i)
    {
        const uint izbTriangleCoords = GetIzbIndex(uvec4(izbIndex, i, cubeFaceIndex));
        const uint triangleId = izb[izbTriangleCoords];
        const uint planeIndexBase = triangleId * NOF_PLANES_TRIANGLE;
    
        //Test for intersection
        const bool isInside = isPointInside(vec4(viewSamplePosition, 1), planes[planeIndexBase+0], planes[planeIndexBase+1], planes[planeIndexBase+2], planes[planeIndexBase+3]);

        if(isInside)
        {
            shadowValue = 0.f;
            break;
        }
    }

    fColor = shadowValue;
}
).";

    return fs.str();
}

std::string FtsShaderGen::GetCSPreprocess(uint32_t wgSize) const
{
    std::stringstream cs;
    cs << R".(
#version 450 core

#define VEC4_PER_TRIANGLE 4
#define FLOATS_PER_TRIANGLE 9
#define BIAS 0.001f

).";

    cs << "layout(local_size_x=" << wgSize << ") in;\n";

    cs << R".(
layout(std430,binding=0) readonly buffer Triangles   {float triangles [];};
layout(std430,binding=1) writeonly buffer ShadowFrusta{vec4 triangleFrusta[];};

uniform uint nofTriangles;
uniform vec4 lightPos;

int greaterVec(vec3 a,vec3 b)
{
	return int(dot(ivec3(sign(a-b)),ivec3(4,2,1)));
}

vec4 getPlane(vec3 A,vec3 B,vec4 L)
{
	if(greaterVec(A,B)>0)
    {
		vec3 n=normalize(cross(A-B,L.xyz-B));
		return vec4(-n,dot(n,B));
	}
    else
    {
		vec3 n=normalize(cross(B-A,L.xyz-A));
		return vec4(n,-dot(n,A));
	}
}

vec4 getPlane(vec3 A,vec3 B,vec3 C)
{
	vec3 n=normalize(cross(B-A,C-A));
	return vec4(n,-dot(n,A));
}

void main()
{
	const uint gid=gl_GlobalInvocationID.x;

    if(gid >= nofTriangles)
    {
        return;
    }

	vec3 v0=vec3(triangles[gid*FLOATS_PER_TRIANGLE+0], triangles[gid*FLOATS_PER_TRIANGLE+1], triangles[gid*FLOATS_PER_TRIANGLE+2]);
	vec3 v1=vec3(triangles[gid*FLOATS_PER_TRIANGLE+3], triangles[gid*FLOATS_PER_TRIANGLE+4], triangles[gid*FLOATS_PER_TRIANGLE+5]);
	vec3 v2=vec3(triangles[gid*FLOATS_PER_TRIANGLE+6], triangles[gid*FLOATS_PER_TRIANGLE+7], triangles[gid*FLOATS_PER_TRIANGLE+8]);

	vec4 e0 = getPlane(v0,v1,lightPos);
	vec4 e1 = getPlane(v1,v2,lightPos);
	vec4 e2 = getPlane(v2,v0,lightPos);
	vec4 e3 = getPlane(
        v0 + BIAS*normalize(v0-lightPos.xyz),
        v1 + BIAS*normalize(v1-lightPos.xyz),
        v2 + BIAS*normalize(v2-lightPos.xyz));

	if(dot(e3, lightPos)<0)
    {
		e0=-e0;
		e1=-e1;
		e2=-e2;
		e3=-e3;
	}

	triangleFrusta[gid*VEC4_PER_TRIANGLE+0]=e0;
	triangleFrusta[gid*VEC4_PER_TRIANGLE+1]=e1;
	triangleFrusta[gid*VEC4_PER_TRIANGLE+2]=e2;
	triangleFrusta[gid*VEC4_PER_TRIANGLE+3]=e3;
}
).";

    return cs.str();
}


std::string FtsShaderGen::GetIzbAddressingFunction() const
{
    return R".(

//XYZ - coords in a cube, w - cube index
uint GetIzbIndex(uvec4 coords)
{
    return (IZB_WIDTH * IZB_HEIGHT * IZB_DEPTH * coords.w) + (IZB_WIDTH * IZB_HEIGHT * coords.z) + (IZB_WIDTH * coords.y) + coords.x;
    //return (IZB_WIDTH * IZB_HEIGHT * 6 * coords.z) + (IZB_WIDTH * IZB_HEIGHT * coords.w) + (IZB_WIDTH * coords.y) + coords.x;
}

).";
}

std::string FtsShaderGen::GetCubeAddressingFunction() const
{
    return R".(
//https://www.gamedev.net/forums/topic/687535-implementing-a-cube-map-lookup-function/?do=findComment&comment=5337472
vec2 getCubeTcoords(const vec3 v, out uint faceIndex)
{
	vec3 vAbs = abs(v);
	float ma;
	vec2 uv;
	if(vAbs.z >= vAbs.x && vAbs.z >= vAbs.y)
	{
		faceIndex = v.z < 0.0 ? 5 : 4;
		ma = 0.5 / vAbs.z;
		uv = vec2(v.z < 0.0 ? -v.x : v.x, -v.y);
	}
	else if(vAbs.y >= vAbs.x)
	{
		faceIndex = v.y < 0.0 ? 3 : 2;
		ma = 0.5 / vAbs.y;
		uv = vec2(v.x, v.y < 0.0 ? -v.z : v.z);
	}
	else
	{
		faceIndex = v.x < 0.0 ? 1 : 0;
		ma = 0.5 / vAbs.x;
		uv = vec2(v.x < 0.0 ? v.z : -v.z, -v.y);
	}

	return uv * ma + 0.5f;
}

).";
}

std::string FtsShaderGen::GetRayInersectFunction() const
{
    return R".(
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

).";
}

