#ifndef _CGENERATETESSELLATIONSHADERSILHOUETTE_HPP_
#define _CGENERATETESSELLATIONSHADERSILHOUETTE_HPP_

#include<iostream>

/**
 * @brief Struct configurates generation of vertex shader for silhouettes
 */
typedef struct{
	unsigned Version;///<version of shader
	bool UseLayouts;///<toggle usage of layouts in shader
	bool Universal;///<universal tessellation shader silhouette
	bool UseSillyPerPatchLevel;///<toggle usage of silly trasfer of TessLevel between shaders
	bool UseOptimizedDegeneration;///<toggle usage of optimized degeneration
	bool UseCompatibility;///<toggle usage of compatibility profile
	bool UseReferenceEdge;///<toggle usage of reference edge
  bool UseStencilValueExport;///<toggle usage of stencil value export
  bool CullSides;///<toggle usage of culling of sides
	std::string LightPositionUniformName;///<name of LightPosition uniform
	std::string MatrixUniformName;///<name of matrix uniform
	std::string VertexAttribName;///<name of input vertex attribs
}STSSilTemplate;

/**
 * @brief Function generates silhouette vertex shader for hulls
 *
 * @param Template template of shader
 *
 * @return Function returns string with shader
 */
std::string GenTSSilVertexHull(STSSilTemplate Template);

/**
 * @brief Function generates silhouette control shader for hulls
 *
 * @param Num numver of opposite vertices
 * @param Template template of shader
 *
 * @return Function returns string with shader
 */
std::string GenTSSilControlHull(unsigned Num,STSSilTemplate Template);

/**
 * @brief Function generates silhouette evaluation shader for hulls
 *
 * @param Template template of shader
 *
 * @return Function returns string with shader
 */
std::string GenTSSilEvaluationHull(STSSilTemplate Template);

/**
 * @brief Function generates silhouette fragment shader for hulls
 *
 * @param Template template of shader
 *
 * @return Function returns string with shader
 */
std::string GenTSSilFragmentHull(STSSilTemplate Template);

#endif//_CGENERATETESSELLATIONSHADERSILHOUETTE_HPP_
