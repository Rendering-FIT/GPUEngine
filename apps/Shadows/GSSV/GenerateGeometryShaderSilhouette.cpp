#include "GenerateGeometryShaderSilhouette.hpp"
#include "GSSV_Shaders.h"

#include <geGL/Shader.h>

std::string genGsSilVertexShader(SGSSilTemplate const& t)
{
	return 
		"#version 450 core\n" +
		(t.Universal ? ge::gl::Shader::define("UNIVERSAL") : "") +
		(t.UseVS2GSArray ? ge::gl::Shader::define("USE_ARRAY_TRANSFER") : "") +
		(t.UseVertexArray ? ge::gl::Shader::define("USE_VERTEX_ARRAY") : "") +
		(t.UseLayouts ? ge::gl::Shader::define("USE_LAYOUTS") : "") +
		ge::gl::Shader::define("VERTEX_ATTRIB_NAME", t.VertexAttribName) +
		ge::gl::Shader::define("MAX_MULTIPLICITY", t.MaxMultiplicity) +
		gsSilVs;
}

std::string genGsSilGeometryShader(SGSSilTemplate const& t)
{
	return
		"#version 450 core\n" + 
		(t.Deterministic ? ge::gl::Shader::define("DETERMINISTIC") : "") +
		(t.ReferenceEdge ? ge::gl::Shader::define("REFERENCE_EDGE") : "") +
		(t.Universal ? ge::gl::Shader::define("UNIVERSAL") : "") +
		(t.UseVS2GSArray ? ge::gl::Shader::define("USE_ARRAY_TRANSFER") : "") +
		(t.UseStencilValueExport ? ge::gl::Shader::define("USE_STENCIL_VALUE_EXPORT") : "") +
		(t.CCWIsFrontFace ? ge::gl::Shader::define("CCW_IS_FRONT_FACE") : "") +
		(t.FrontFaceInside ? ge::gl::Shader::define("FRONT_FACE_INSIDE") : "") +
		(t.CullSides ? ge::gl::Shader::define("CULL_SIDES") : "") +
		(t.FrontCapToInfinity ? ge::gl::Shader::define("FRONT_CAP_TO_INFINITY") : "") +
		(t.GenerateSides ? ge::gl::Shader::define("GENERATE_SIDES") : "") +
		(t.GenerateCaps ? ge::gl::Shader::define("GENERATE_CAPS") : "") +
		(t.Matrix != "" ? ge::gl::Shader::define("MATRIX", t.Matrix) : "") +
		ge::gl::Shader::define("MAX_MULTIPLICITY", t.MaxMultiplicity) +
		ge::gl::Shader::define("LIGHT", t.LightUniform) + 
		gsSilGs;
}

std::string genGsSilFragmentShader(SGSSilTemplate const& t)
{
	return
		"#version 450 core\n" +
		(t.UseStencilValueExport ? ge::gl::Shader::define("USE_STENCIL_VALUE_EXPORT") : "") +
		(t.UseLayouts ? ge::gl::Shader::define("USE_LAYOUTS") : "") +
		(t.Visualize ? ge::gl::Shader::define("VISUALIZE") : "") + 
		gsSilFs;
}
