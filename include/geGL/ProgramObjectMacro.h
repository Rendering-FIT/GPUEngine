#pragma once

#define DEF_GLUNIFORM(a,b) DEF_GLUNIFORM_##b(a)
#define DEF_GLUNIFORM_boolean(a) glUniform##a##i
#define DEF_GLUNIFORM_i(a) glUniform##a##i
#define DEF_GLUNIFORM_f(a) glUniform##a##f
#define DEF_GLUNIFORM_ui(a) glUniform##a##ui
#define DEF_GLUNIFORM_d(a) glUniform##a##d

#define DEF_GLUNIFORMV(a,b) DEF_GLUNIFORMV_##b(a)
#define DEF_GLUNIFORMV_boolean(a) glUniform##a##iv
#define DEF_GLUNIFORMV_i(a) glUniform##a##iv
#define DEF_GLUNIFORMV_f(a) glUniform##a##fv
#define DEF_GLUNIFORMV_ui(a) glUniform##a##uiv
#define DEF_GLUNIFORMV_d(a) glUniform##a##dv

#define DEF_GLPROGRAMUNIFORM(a,b) DEF_GLPROGRAMUNIFORM_##b(a)
#define DEF_GLPROGRAMUNIFORM_boolean(a) glProgramUniform##a##i
#define DEF_GLPROGRAMUNIFORM_i(a)       glProgramUniform##a##i
#define DEF_GLPROGRAMUNIFORM_f(a)       glProgramUniform##a##f
#define DEF_GLPROGRAMUNIFORM_ui(a)      glProgramUniform##a##ui
#define DEF_GLPROGRAMUNIFORM_d(a)       glProgramUniform##a##d

#define DEF_GLPROGRAMUNIFORMV(a,b) DEF_GLPROGRAMUNIFORMV_##b(a)
#define DEF_GLPROGRAMUNIFORMV_boolean(a) glProgramUniform##a##iv
#define DEF_GLPROGRAMUNIFORMV_i(a)       glProgramUniform##a##iv
#define DEF_GLPROGRAMUNIFORMV_f(a)       glProgramUniform##a##fv
#define DEF_GLPROGRAMUNIFORMV_ui(a)      glProgramUniform##a##uiv
#define DEF_GLPROGRAMUNIFORMV_d(a)       glProgramUniform##a##dv

#define DEF_GLTYPE(b_const) DEF_GLTYPE_##b_const
#define DEF_GLTYPE_b       GLbyte
#define DEF_GLTYPE_s       GLshort
#define DEF_GLTYPE_i       GLint
#define DEF_GLTYPE_i64     GLint64
#define DEF_GLTYPE_f       GLfloat
#define DEF_GLTYPE_ub      GLubyte
#define DEF_GLTYPE_us      GLushort
#define DEF_GLTYPE_ui      GLuint
#define DEF_GLTYPE_ui64    GLuint64
#define DEF_GLTYPE_d       GLdouble
#define DEF_GLTYPE_boolean GLboolean
#define DEF_GLTYPE_x

#define DEF_GLTYPETRANS(b_const) DEF_GLTYPETRANS_##b_const
#define DEF_GLTYPETRANS_b       GLbyte
#define DEF_GLTYPETRANS_s       GLshort
#define DEF_GLTYPETRANS_i       GLint
#define DEF_GLTYPETRANS_i64     GLint64
#define DEF_GLTYPETRANS_f       GLfloat
#define DEF_GLTYPETRANS_ub      GLubyte
#define DEF_GLTYPETRANS_us      GLushort
#define DEF_GLTYPETRANS_ui      GLuint
#define DEF_GLTYPETRANS_ui64    GLuint64
#define DEF_GLTYPETRANS_d       GLdouble
#define DEF_GLTYPETRANS_boolean GLint

#define DEF_GLTYPECONST(a,b) DEF_GLTYPECONST_##a##b
#define DEF_GLTYPECONST_1f       GL_FLOAT
#define DEF_GLTYPECONST_2f       GL_FLOAT_VEC2
#define DEF_GLTYPECONST_3f       GL_FLOAT_VEC3
#define DEF_GLTYPECONST_4f       GL_FLOAT_VEC4
#define DEF_GLTYPECONST_1d       GL_DOUBLE
#define DEF_GLTYPECONST_2d       GL_DOUBLE_VEC2
#define DEF_GLTYPECONST_3d       GL_DOUBLE_VEC3
#define DEF_GLTYPECONST_4d       GL_DOUBLE_VEC4
#define DEF_GLTYPECONST_1i       GL_INT
#define DEF_GLTYPECONST_2i       GL_INT_VEC2
#define DEF_GLTYPECONST_3i       GL_INT_VEC3
#define DEF_GLTYPECONST_4i       GL_INT_VEC4
#define DEF_GLTYPECONST_1ui      GL_UNSIGNED_INT
#define DEF_GLTYPECONST_2ui      GL_UNSIGNED_INT_VEC2
#define DEF_GLTYPECONST_3ui      GL_UNSIGNED_INT_VEC3
#define DEF_GLTYPECONST_4ui      GL_UNSIGNED_INT_VEC4
#define DEF_GLTYPECONST_1boolean GL_BOOL
#define DEF_GLTYPECONST_2boolean GL_BOOL_VEC2
#define DEF_GLTYPECONST_3boolean GL_BOOL_VEC3
#define DEF_GLTYPECONST_4boolean GL_BOOL_VEC4

#define DEF_GLTYPEPAR(b_num,type) DEF_GLTYPEPAR_##b_num(type)
#define DEF_GLTYPEPAR_1(type) DEF_GLTYPE(type) v0
#define DEF_GLTYPEPAR_2(type) DEF_GLTYPE(type) v0,DEF_GLTYPE(type) v1
#define DEF_GLTYPEPAR_3(type) DEF_GLTYPE(type) v0,DEF_GLTYPE(type) v1,DEF_GLTYPE(type) v2
#define DEF_GLTYPEPAR_4(type) DEF_GLTYPE(type) v0,DEF_GLTYPE(type) v1,DEF_GLTYPE(type) v2,DEF_GLTYPE(type) v3

#define DEF_GLTYPEPARCONV(b_num,type) DEF_GLTYPEPARCONV_##b_num(type)
#define DEF_GLTYPEPARCONV_1(type) (DEF_GLTYPETRANS(type)) v0
#define DEF_GLTYPEPARCONV_2(type) (DEF_GLTYPETRANS(type)) v0,(DEF_GLTYPETRANS(type)) v1
#define DEF_GLTYPEPARCONV_3(type) (DEF_GLTYPETRANS(type)) v0,(DEF_GLTYPETRANS(type)) v1,(DEF_GLTYPETRANS(type)) v2
#define DEF_GLTYPEPARCONV_4(type) (DEF_GLTYPETRANS(type)) v0,(DEF_GLTYPETRANS(type)) v1,(DEF_GLTYPETRANS(type)) v2,(DEF_GLTYPETRANS(type)) v3

#define DEFDEFFCE(a,b)\
	void set(std::string uniformName,DEF_GLTYPEPAR(a,b))

#define DEF_PROGRAMOBJECT_SET(a,b)\
	void ProgramObject::set(std::string uniformName,DEF_GLTYPEPAR(a,b)){\
    if(!this->_uniformList.count(uniformName))return;\
		DEF_GLUNIFORM(a,b)(this->_uniformList[uniformName].getLocation(),DEF_GLTYPEPARCONV(a,b));\
	}

#define DEFDEFFCEV(type)\
	void set(std::string uniformName,GLsizei count,\
			DEF_GLTYPE(type) *value)

#define DEF_PROGRAMOBJECT_SETV(type_name)\
	void ProgramObject::set(\
			std::string uniformName,\
			GLsizei count,\
			const DEF_GLTYPE(type_name) *value){\
    if(!this->_uniformList.count(uniformName))return;\
		ProgramObjectParameter param=this->_uniformList[uniformName];\
		switch(param.getType()){\
			case DEF_GLTYPECONST(1,type_name):\
				DEF_GLUNIFORMV(1,type_name)(param.getLocation(),count,(const DEF_GLTYPETRANS(type_name)*)value);\
				break;\
			case DEF_GLTYPECONST(2,type_name):\
				DEF_GLUNIFORMV(2,type_name)(param.getLocation(),count,(const DEF_GLTYPETRANS(type_name)*)value);\
				break;\
			case DEF_GLTYPECONST(3,type_name):\
				DEF_GLUNIFORMV(3,type_name)(param.getLocation(),count,(const DEF_GLTYPETRANS(type_name)*)value);\
				break;\
			case DEF_GLTYPECONST(4,type_name):\
				DEF_GLUNIFORMV(4,type_name)(param.getLocation(),count,(const DEF_GLTYPETRANS(type_name)*)value);\
				break;\
			default:\
				break;\
		}\
	}

#define DEFDEFDSAFCE(a,b)\
	void setdsa(std::string uniformName,DEF_GLTYPEPAR(a,b))

#define DEF_PROGRAMOBJECT_SETDSA(a,b)\
	void ProgramObject::setdsa(std::string uniformName,DEF_GLTYPEPAR(a,b)){\
    if(!this->_uniformList.count(uniformName))return;\
		DEF_GLPROGRAMUNIFORM(a,b)(this->_id,this->_uniformList[uniformName].getLocation(),DEF_GLTYPEPARCONV(a,b));\
	}

#define DEFDEFDSAFCEV(type)\
	void setdsa(std::string uniformName,GLsizei count,\
			DEF_GLTYPE(type) *value)

#define DEF_PROGRAMOBJECT_SETDSAV(type_name)\
	void ProgramObject::setdsa(\
			std::string uniformName,\
			GLsizei count,\
			const DEF_GLTYPE(type_name) *value){\
    if(!this->_uniformList.count(uniformName))return;\
		ProgramObjectParameter param=this->_uniformList[uniformName];\
		switch(param.getType()){\
			case DEF_GLTYPECONST(1,type_name):\
				DEF_GLPROGRAMUNIFORMV(1,type_name)(this->_id,param.getLocation(),count,(const DEF_GLTYPETRANS(type_name)*)value);\
				break;\
			case DEF_GLTYPECONST(2,type_name):\
				DEF_GLPROGRAMUNIFORMV(2,type_name)(this->_id,param.getLocation(),count,(const DEF_GLTYPETRANS(type_name)*)value);\
				break;\
			case DEF_GLTYPECONST(3,type_name):\
				DEF_GLPROGRAMUNIFORMV(3,type_name)(this->_id,param.getLocation(),count,(const DEF_GLTYPETRANS(type_name)*)value);\
				break;\
			case DEF_GLTYPECONST(4,type_name):\
				DEF_GLPROGRAMUNIFORMV(4,type_name)(this->_id,param.getLocation(),count,(const DEF_GLTYPETRANS(type_name)*)value);\
				break;\
			default:\
				break;\
		}\
	}

