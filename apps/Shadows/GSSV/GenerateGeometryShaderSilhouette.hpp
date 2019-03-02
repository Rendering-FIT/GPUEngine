#pragma once

#include<string>


#if 0

typedef struct {
	unsigned Version;//version of shader
	bool Compatible;//compatible profile
	bool Universal;//is shader universal
	bool Framebuffer;//framebuffer instead of stencil buffer
	bool ImageAtomicAdd;//ImageAtomicAdd
	bool AMDExtension;//
	bool Deterministic;//deterministic shader
	//bool OneRepresenatative;//one edge determinism
	bool UseGSInvocation;//toggle usage of geometry shader invocation
	bool ZFail;//zfail algorithm
	bool CullFace;
}SGSSilTemplate;

/**
 * @brief Generate input and output layouts
 *
 * @param Num Number of opposite vertices or max number of opposite vertices
 * @param Caps generate layout for caps shader
 * @param Template template
 *
 * @return returns string representation
 */
//Main functions
std::string GenGSSilVertex(unsigned Num, SGSSilTemplate Template);
std::string GenGSSilGeometryHull(unsigned Num, SGSSilTemplate Template);
std::string GenGSSilFragment(SGSSilTemplate Template);

//Support functions
std::string GenVersion(SGSSilTemplate T);
std::string GenGSSilGeometryInOut(unsigned Num, bool Caps, SGSSilTemplate Template);
std::string GenGSSilGeometryCap(unsigned Num, SGSSilTemplate Template);


//std::string GenGSSilGeometryHullGI(unsigned Num, SGSSilTemplate Template);

#endif

typedef struct {
	bool Deterministic;          ///< deterministic version
	bool ReferenceEdge;          ///< Reference edge version
	bool Universal;              ///< universal shader
	bool UseVS2GSArray;          ///< toggle usage of array as way of transfer
	bool UseVertexArray;         ///< inputs into vertex shader are in array
	bool UseLayouts;             ///< inputs have layout interface
	bool UseStencilValueExport;  ///< toggle usage of AMD extension
	bool CCWIsFrontFace;         ///< Front Face is CCW
	bool FrontFaceInside;        ///< Front Face are oriented inside Shadow Volume
	bool CullSides;              ///< toggle culling of sides
	bool Visualize;              ///< visualize SV with colors
	bool FrontCapToInfinity;     ///< shift front cap to infinity
	bool GenerateSides;          ///< toggle generation of sides
	bool GenerateCaps;           ///< toggle generation of caps
	std::string Matrix;          ///< mvp matrix uniform name
	unsigned    MaxMultiplicity; ///< maximal number of opposite vertices
	std::string LightUniform;    ///< light position uniform name
	std::string VertexAttribName;///< name of vertex attribs
} SGSSilTemplate;

std::string genGsSilVertexShader(SGSSilTemplate const& templ);
std::string genGsSilGeometryShader(SGSSilTemplate const& templ);
std::string genGsSilFragmentShader(SGSSilTemplate const& templ);
