#include "GenerateGeometryShaderSilhouette.hpp"
#include "GSSV_Shaders.h"
#include <geGL/Shader.h>

#if 0

#include<sstream>

//#define USE_AMD

std::string GenGSSilVertex(
	unsigned Num,
	SGSSilTemplate T) {
	if (T.Universal)Num++;
	std::stringstream Result;//resulting framebuffer
	Result << GenVersion(T);//generate version
	Result << "#extension GL_ARB_separate_shader_objects : enable\n";
	Result << "#extension GL_ARB_shading_language_420pack : enable\n";
	Result << "\n";
	for (unsigned i = 0; i < Num + 2; ++i)
		Result << "layout(location=" << i << ")in vec4 Position" << i << ";\n";
	Result << "\n";
	for (unsigned i = 0; i < Num + 1; ++i)
		Result << "out vec4 vPosition" << i << ";\n";
	Result << "\n";
	Result << "void main(){\n";
	Result << "\tgl_Position=Position0;\n";
	for (unsigned i = 0; i < Num + 1; ++i)
		Result << "\tvPosition" << i << "=Position" << i + 1 << ";\n";
	Result << "}";
	return Result.str();
}

std::string GenCmpVec() {
	std::stringstream Result;
	Result << "int GreaterVec(vec3 a,vec3 b){\n";
	Result << "\treturn int(dot(ivec3(greaterThanEqual(a,b))*2-1,ivec3(4,2,1)));\n";
	Result << "}\n";
	//return Result.str();

	Result << "int CmpVec(vec3 a,vec3 b){\n";
	Result << "\tif(a.x<b.x)return-1;\n";
	Result << "\telse if(a.x>b.x)return 1;\n";
	Result << "\telse{\n";
	Result << "\t\tif(a.y<b.y)return-1;\n";
	Result << "\t\telse if(a.y>b.y)return 1;\n";
	Result << "\t\telse{\n";
	Result << "\t\t\tif(a.z<b.z)return-1;\n";
	Result << "\t\t\telse if(a.z>b.z)return 1;\n";
	Result << "\t\t\telse return 0;\n";
	Result << "\t\t}\n";
	Result << "\t}\n";
	Result << "}\n";
	return Result.str();
}

std::string GenGSSilGeometryInOut(unsigned Num, bool Caps, SGSSilTemplate T) {
	unsigned NumTriangles;
	if (T.Universal)
		if (Caps)NumTriangles = Num * 6;
		else NumTriangles = Num * 4;
	else
		if (Caps)NumTriangles = Num * 6;
		else NumTriangles = Num * 4;
#ifdef USE_AMD
	if (!Caps)
		NumTriangles = 4;
#endif
	if (T.UseGSInvocation && !Caps)
		NumTriangles = (NumTriangles / 4) * 3;
	std::string Invocation = "";
	if (T.UseGSInvocation && !Caps)
		Invocation = ",invocations=2";
	std::stringstream Result;
	Result << "layout(points" << Invocation << ")in;\n";
	Result << "layout(triangle_strip,max_vertices=" << NumTriangles << ")out;\n";
	return Result.str();
}

std::string GenInPosition(unsigned Num, SGSSilTemplate T) {
	Num += 2;//2 for edge points
	Num -= 1;//-1 for gl_Position
	if (T.Universal)Num += 1;//1 for number
	std::stringstream Result;
	for (unsigned i = 0; i < Num; ++i)
		Result << "in vec4 vPosition" << i << "[];\n";
	return Result.str();
}

std::string GenUniforms(SGSSilTemplate T) {
	std::stringstream Result;
	if (!T.Compatible)Result << "uniform mat4 mvp;\n";
	Result << "uniform vec4 LightPosition;\n";
	return Result.str();
}

std::string GenPoint(std::string LightPos, SGSSilTemplate T) {
	std::stringstream Result;
	std::string Matrix;
	if (T.Compatible)Matrix = "gl_ModelViewProjectionMatrix";
	else Matrix = "mvp";
	Result << "\tvec4 P[4];\n";
	Result << "\tP[0]=gl_PositionIn[0];\n";
	Result << "\tP[1]=vPosition0[0];\n";
	Result << "\tP[2]=vec4(P[0].xyz*" << LightPos << ".w-" << LightPos << ".xyz,0);\n";
	Result << "\tP[3]=vec4(P[1].xyz*" << LightPos << ".w-" << LightPos << ".xyz,0);\n";
	Result << "\tvec4 mvpP[4];\n";
	Result << "\tmvpP[0]=" << Matrix << "*P[0];\n";
	Result << "\tmvpP[1]=" << Matrix << "*P[1];\n";
	Result << "\tmvpP[2]=" << Matrix << "*P[2];\n";
	Result << "\tmvpP[3]=" << Matrix << "*P[3];\n";
	return Result.str();
}

std::string GenOppositeArray(unsigned Num) {
	std::stringstream Result;
	Result << "\tvec4 O[" << Num << "];\n";
	for (unsigned i = 0; i < Num; ++i)
		Result << "\tO[" << i << "]=vPosition" << i + 1 << "[0];\n";
	return Result.str();
}

std::string GenHull(SGSSilTemplate T) {
	std::stringstream Result;
	std::string Matrix;
	if (T.Compatible)Matrix = "gl_ModelViewProjectionMatrix";
	else Matrix = "mvp";
#ifdef USE_AMD
	if (true) {
#else
	if (T.Framebuffer) {
#endif
		/*
		Result<<"\tif(Multiplicity!=0){\n";
		Result<<"\t\tgMultiplicity=Multiplicity;gl_Position="<<Matrix<<"*P[0];EmitVertex();\n";
		Result<<"\t\tgMultiplicity=Multiplicity;gl_Position="<<Matrix<<"*P[1];EmitVertex();\n";
		Result<<"\t\tgMultiplicity=Multiplicity;gl_Position="<<Matrix<<"*P[2];EmitVertex();\n";
		Result<<"\t\tgMultiplicity=Multiplicity;gl_Position="<<Matrix<<"*P[3];EmitVertex();\n";
		Result<<"\t\tEndPrimitive();\n";
		Result<<"\t}\n";
		*/
#ifdef USE_AMD
		Result << "\tif(Multiplicity!=0){\n";
		Result << "\t\tgMultiplicity=Multiplicity;gl_Position=mvpP[0];EmitVertex();\n";
		Result << "\t\tgMultiplicity=Multiplicity;gl_Position=mvpP[1];EmitVertex();\n";
		Result << "\t\tgMultiplicity=Multiplicity;gl_Position=mvpP[2];EmitVertex();\n";
		Result << "\t\tgMultiplicity=Multiplicity;gl_Position=mvpP[3];EmitVertex();\n";
		Result << "\t\tEndPrimitive();\n";
		Result << "\t}\n";

		/*
		//FUNKCNI
		Result<<"\tif(Multiplicity>0){\n";
		Result<<"\t\tgMultiplicity=Multiplicity;gl_Position=mvpP[0];EmitVertex();\n";
		Result<<"\t\tgMultiplicity=Multiplicity;gl_Position=mvpP[1];EmitVertex();\n";
		Result<<"\t\tgMultiplicity=Multiplicity;gl_Position=mvpP[2];EmitVertex();\n";
		Result<<"\t\tgMultiplicity=Multiplicity;gl_Position=mvpP[3];EmitVertex();\n";
		Result<<"\t\tEndPrimitive();\n";
		Result<<"\t}\n";

		Result<<"\tif(Multiplicity<0){\n";
		Result<<"\t\tgMultiplicity=-Multiplicity;gl_Position=mvpP[1];EmitVertex();\n";
		Result<<"\t\tgMultiplicity=-Multiplicity;gl_Position=mvpP[0];EmitVertex();\n";
		Result<<"\t\tgMultiplicity=-Multiplicity;gl_Position=mvpP[3];EmitVertex();\n";
		Result<<"\t\tgMultiplicity=-Multiplicity;gl_Position=mvpP[2];EmitVertex();\n";
		Result<<"\t\tEndPrimitive();\n";
		Result<<"\t}\n";
		*/
#else
		Result << "\tif(Multiplicity!=0){\n";
		Result << "\t\tgMultiplicity=Multiplicity;gl_Position=mvpP[0];EmitVertex();\n";
		Result << "\t\tgMultiplicity=Multiplicity;gl_Position=mvpP[1];EmitVertex();\n";
		Result << "\t\tgMultiplicity=Multiplicity;gl_Position=mvpP[2];EmitVertex();\n";
		Result << "\t\tgMultiplicity=Multiplicity;gl_Position=mvpP[3];EmitVertex();\n";
		Result << "\t\tEndPrimitive();\n";
		Result << "\t}\n";
#endif

	}
	else {
		/*
		Result<<"\tif(Multiplicity>0){\n";
		Result<<"\t\tfor(int i=0;i<Multiplicity;++i){\n";
		Result<<"\t\t\tgl_Position="<<Matrix<<"*P[0];EmitVertex();\n";
		Result<<"\t\t\tgl_Position="<<Matrix<<"*P[1];EmitVertex();\n";
		Result<<"\t\t\tgl_Position="<<Matrix<<"*P[2];EmitVertex();\n";
		Result<<"\t\t\tgl_Position="<<Matrix<<"*P[3];EmitVertex();\n";
		Result<<"\t\t\tEndPrimitive();\n";
		Result<<"\t\t}\n";
		Result<<"\t}\n";
		Result<<"\tif(Multiplicity<0){\n";
		Result<<"\t\tMultiplicity=-Multiplicity;\n";
		Result<<"\t\tfor(int i=0;i<Multiplicity;++i){\n";
		Result<<"\t\t\tgl_Position="<<Matrix<<"*P[1];EmitVertex();\n";
		Result<<"\t\t\tgl_Position="<<Matrix<<"*P[0];EmitVertex();\n";
		Result<<"\t\t\tgl_Position="<<Matrix<<"*P[3];EmitVertex();\n";
		Result<<"\t\t\tgl_Position="<<Matrix<<"*P[2];EmitVertex();\n";
		Result<<"\t\t\tEndPrimitive();\n";
		Result<<"\t\t}\n";
		Result<<"\t}\n";
		*/
		if (T.UseGSInvocation) {
			Result << "\tif(Multiplicity>0){\n";
			Result << "\t\tfor(int i=0;i<Multiplicity;++i){\n";
			Result << "\t\t\tgl_Position=mvpP[0+gl_InvocationID];EmitVertex();\n";
			Result << "\t\t\tgl_Position=mvpP[1+(gl_InvocationID<<1)];EmitVertex();\n";
			Result << "\t\t\tgl_Position=mvpP[2];EmitVertex();\n";
			Result << "\t\t\tEndPrimitive();\n";
			Result << "\t\t}\n";
			Result << "\t}\n";
			Result << "\tif(Multiplicity<0){\n";
			Result << "\t\tMultiplicity=-Multiplicity;\n";
			Result << "\t\tfor(int i=0;i<Multiplicity;++i){\n";
			Result << "\t\t\tgl_Position=mvpP[1-gl_InvocationID];EmitVertex();\n";
			Result << "\t\t\tgl_Position=mvpP[0+(gl_InvocationID<<1)];EmitVertex();\n";
			Result << "\t\t\tgl_Position=mvpP[3];EmitVertex();\n";
			Result << "\t\t\tEndPrimitive();\n";
			Result << "\t\t}\n";
			Result << "\t}\n";
		}
		else {
			Result << "\tif(Multiplicity>0){\n";
			Result << "\t\tfor(int i=0;i<Multiplicity;++i){\n";
			Result << "\t\t\tgl_Position=mvpP[0];EmitVertex();\n";
			Result << "\t\t\tgl_Position=mvpP[1];EmitVertex();\n";
			Result << "\t\t\tgl_Position=mvpP[2];EmitVertex();\n";
			Result << "\t\t\tgl_Position=mvpP[3];EmitVertex();\n";
			Result << "\t\t\tEndPrimitive();\n";
			Result << "\t\t}\n";
			Result << "\t}\n";
			Result << "\tif(Multiplicity<0){\n";
			Result << "\t\tMultiplicity=-Multiplicity;\n";
			Result << "\t\tfor(int i=0;i<Multiplicity;++i){\n";
			Result << "\t\t\tgl_Position=mvpP[1];EmitVertex();\n";
			Result << "\t\t\tgl_Position=mvpP[0];EmitVertex();\n";
			Result << "\t\t\tgl_Position=mvpP[3];EmitVertex();\n";
			Result << "\t\t\tgl_Position=mvpP[2];EmitVertex();\n";
			Result << "\t\t\tEndPrimitive();\n";
			Result << "\t\t}\n";
			Result << "\t}\n";
		}
	}
	return Result.str();
	}

std::string GenFirstEdge(std::string LightPos) {
	std::stringstream Result;
	Result << "\t\tvec3 T[3];\n";
	Result << "\t\tvec3 D[3];\n";
	Result << "\t\tvec3 NS[3];\n";
	Result << "\t\tvec4 PL[3];\n";
	Result << "\t\tfloat d[3];\n";
	Result << "\n";
	Result << "\t\tT[0]=P[0].xyz;\n";
	Result << "\t\tT[1]=P[1].xyz;\n";
	Result << "\t\tT[2]=O[i].xyz;\n";
	Result << "\n";
	Result << "\t\tD[0]=" << LightPos << ".xyz-T[0]*" << LightPos << ".w;\n";
	Result << "\t\tNS[0]=normalize(cross(T[1]-T[0],D[0]));\n";
	Result << "\t\tPL[0]=vec4(NS[0],-dot(NS[0],T[0]));\n";
	Result << "\t\td[0]=dot(PL[0],vec4(T[2],1));\n";
	Result << "\n";
	return Result.str();
}

std::string GenSecondThirdEdge(std::string LightPos) {
	std::stringstream Result;
	Result << "\n";
	Result << "\t\tD[1]=" << LightPos << ".xyz-T[1]*" << LightPos << ".w;\n";
	Result << "\t\tD[2]=" << LightPos << ".xyz-T[2]*" << LightPos << ".w;\n";
	Result << "\n";
	Result << "\t\tif(GreaterVec(T[2],T[0])>0){\n";
	Result << "\t\t\tNS[1]=normalize(cross(T[2]-T[0],D[0]));\n";
	Result << "\t\t\tPL[1]=vec4(NS[1],-dot(NS[1],T[0]));\n";
	Result << "\t\t\td[1]=dot(PL[1],vec4(T[1],1));\n";
	Result << "\t\t}\n";
	Result << "\t\telse{\n";
	Result << "\t\t\tNS[1]=normalize(cross(T[0]-T[2],D[2]));\n";
	Result << "\t\t\tPL[1]=vec4(NS[1],-dot(NS[1],T[2]));\n";
	Result << "\t\t\td[1]=-dot(PL[1],vec4(T[1],1));\n";
	Result << "\t\t}\n";
	Result << "\n";
	Result << "\t\tif(GreaterVec(T[2],T[1])>0){\n";
	Result << "\t\t\tNS[2]=normalize(cross(T[2]-T[1],D[1]));\n";
	Result << "\t\t\tPL[2]=vec4(NS[2],-dot(NS[2],T[1]));\n";
	Result << "\t\t\td[2]=dot(PL[2],vec4(T[0],1));\n";
	Result << "\t\t}else{\n";
	Result << "\t\t\tNS[2]=normalize(cross(T[1]-T[2],D[2]));\n";
	Result << "\t\t\tPL[2]=vec4(NS[2],-dot(NS[2],T[2]));\n";
	Result << "\t\t\td[2]=-dot(PL[2],vec4(T[0],1));\n";
	Result << "\t\t}\n";
	Result << "\n";
	Result << "\t\tif(d[0]==0||d[1]==0||d[2]==0)continue;\n";
	Result << "\t\tif(!((d[0]<0&&d[1]>0&&d[2]<0)||(d[0]>0&&d[1]<0&&d[2]>0)))continue;\n";
	return Result.str();
}

std::string GenComputeMultiplicityHull(SGSSilTemplate T, std::string LightPos) {
	std::stringstream Result;
	Result << GenFirstEdge(LightPos);
	if (T.Deterministic) {
		Result << GenSecondThirdEdge(LightPos);
	}
	Result << "\t\tif(d[0]<0)Multiplicity++;\n";
	Result << "\t\telse if(d[0]>0)Multiplicity--;\n";
	return Result.str();
}

std::string GenComputeMultiplicityCap(SGSSilTemplate T, std::string LightPos) {
	std::stringstream Result;
	std::string Matrix;
	if (T.Compatible)Matrix = "gl_ModelViewProjectionMatrix";
	else Matrix = "mvp";
	Result << GenFirstEdge(LightPos);
	if (T.Deterministic)
		Result << GenSecondThirdEdge(LightPos);
#ifdef USE_AMD
	if (true) {
#else
	if (T.Framebuffer) {
#endif
		Result << "\t\tif(O[i].w==1){\n";
		Result << "\t\t\tfloat a=1;\n";
		Result << "\t\t\tvec3 NN=normalize(cross(P[1].xyz-P[0].xyz,O[i].xyz-P[0].xyz));\n";
		Result << "\t\t\tif(dot(NN," << LightPos << ".xyz)-dot(NN,P[0].xyz)>0)a=1;\n";
		Result << "\t\t\telse a=-1;\n";
		Result << "\t\t\tgMultiplicity=a;gl_Position=" << Matrix << "*vec4(P[2].xyz,0);EmitVertex();\n";
		Result << "\t\t\tgMultiplicity=a;gl_Position=" << Matrix << "*vec4(P[3].xyz,0);EmitVertex();\n";
		Result << "\t\t\tgMultiplicity=a;gl_Position=" << Matrix << "*vec4(O[i].xyz*" <<
			LightPos << ".w-" << LightPos << ".xyz,0);EmitVertex();\n";
		Result << "\t\t\tEndPrimitive();\n";
		Result << "\t\t\tgMultiplicity=-a;gl_Position=" << Matrix << "*P[0];EmitVertex();\n";
		Result << "\t\t\tgMultiplicity=-a;gl_Position=" << Matrix << "*P[1];EmitVertex();\n";
		Result << "\t\t\tgMultiplicity=-a;gl_Position=" << Matrix << "*O[i];EmitVertex();\n";
		Result << "\t\t\tEndPrimitive();\n";
		Result << "\t\t}\n";
	}
	else {
		Result << "\t\tif(O[i].w==1){\n";
		Result << "\n";
		Result << "\t\t\tvec3 NN=cross(P[1].xyz-P[0].xyz,O[i].xyz-P[0].xyz);\n";
		Result << "\t\t\tvec3 LL=" << LightPos << ".xyz-P[0].xyz*" << LightPos << ".w;\n";
		Result << "\t\t\tif(dot(NN,LL)>0){\n";
		Result << "\t\t\t\tgl_Position=" << Matrix << "*P[2];EmitVertex();\n";
		Result << "\t\t\t\tgl_Position=" << Matrix << "*P[3];EmitVertex();\n";
		Result << "\t\t\t\tgl_Position=" << Matrix << "*vec4(O[i].xyz*" <<
			LightPos << ".w-" << LightPos << ".xyz,0);EmitVertex();\n";
		Result << "\t\t\t\tEndPrimitive();\n";
		Result << "\t\t\t\t\n";
		Result << "\t\t\t\tgl_Position=" << Matrix << "*P[1];EmitVertex();\n";
		Result << "\t\t\t\tgl_Position=" << Matrix << "*P[0];EmitVertex();\n";
		Result << "\t\t\t\tgl_Position=" << Matrix << "*O[i];EmitVertex();\n";
		Result << "\t\t\t\tEndPrimitive();\n";
		Result << "\n";
		Result << "\t\t\t}else{\n";
		Result << "\t\t\t\tgl_Position=" << Matrix << "*P[3];EmitVertex();\n";
		Result << "\t\t\t\tgl_Position=" << Matrix << "*P[2];EmitVertex();\n";
		Result << "\t\t\t\tgl_Position=" << Matrix << "*vec4(O[i].xyz*" <<
			LightPos << ".w-" << LightPos << ".xyz,0);EmitVertex();\n";
		Result << "\t\t\t\tEndPrimitive();\n";
		Result << "\t\t\t\tgl_Position=" << Matrix << "*P[0];EmitVertex();\n";
		Result << "\t\t\t\tgl_Position=" << Matrix << "*P[1];EmitVertex();\n";
		Result << "\t\t\t\tgl_Position=" << Matrix << "*O[i];EmitVertex();\n";
		Result << "\t\t\t\tEndPrimitive();\n";
		Result << "\n";
		Result << "\t\t\t}\n";
		Result << "\t\t}\n";
	}
	return Result.str();
	}

std::string GenGSSilFCFunc() {
	std::stringstream Result;
	/*Result<<"bool IsEdgeVisible(vec4 A,vec4 B){\n";
	Result<<"	//X=A+x*(B-A)\n";
	Result<<"	//i={x,y,z}\n";
	Result<<"\n";
	Result<<"	//X.i>=-X.w\n";
	Result<<"	//X.i<=X.w\n";
	Result<<"\n";
	Result<<"	//+X.i+X.w>=0\n";
	Result<<"	//-X.i+X.w>=0\n";
	Result<<"\n";
	Result<<"	//+A.i+x*(B.i-A.i)+A.w+x*(B.w-A.w)>=0\n";
	Result<<"	//-A.i-x*(B.i-A.i)+A.w+x*(B.w-A.w)>=0\n";
	Result<<"\n";
	Result<<"	//(+A.i+A.w)+x*((+B.i+B.w)-(+A.i+A.w))>=0\n";
	Result<<"	//(-A.i+A.w)+x*((-B.i+B.w)-(-A.i+A.w))>=0\n";
	Result<<"\n";
	Result<<"	//M.i+x*(N.i-M.i)>=0\n";
	Result<<"	//O.i+x*(P.i-O.i)>=0\n";
	Result<<"\n";
	Result<<"	//M.i+x*NM.i>=0\n";
	Result<<"	//O.i+x*PO.i>=0\n";
	Result<<"\n";
	Result<<"	//NM.i>0 shift min x to greater value -M.i/NM.i\n";
	Result<<"	//NM.i<0 shift max x to lesser value -M.i/NM.i\n";
	Result<<"	//MN.i=0 fail if M.i < 0\n";
	Result<<"\n";
	Result<<"	vec3 M=+A.xyz+A.www;\n";
	Result<<"	vec3 N=+B.xyz+B.www;\n";
	Result<<"	vec3 O=-A.xyz+A.www;\n";
	Result<<"	vec3 P=-B.xyz+B.www;\n";
	Result<<"	vec3 NM=N-M;\n";
	Result<<"	vec3 PO=P-O;\n";
	Result<<"\n";
	Result<<"	float xmin=0;\n";
	Result<<"	float xmax=1;\n";
	Result<<"	for(int i=0;i<3;++i){\n";
	//Result<<"		if(NM[i]==0&&M[i]<0)return false;\n";
	Result<<"		if(NM[i]>0)xmin=max(xmin,-M[i]/NM[i]);\n";
	Result<<"		if(NM[i]<0)xmax=min(xmax,-M[i]/NM[i]);\n";

	//Result<<"		if(PO[i]==0&&O[i]<0)return false;\n";
	Result<<"		if(PO[i]>0)xmin=max(xmin,-O[i]/PO[i]);\n";
	Result<<"		if(PO[i]<0)xmax=min(xmax,-O[i]/PO[i]);\n";
	Result<<"	}\n";
	Result<<"	return xmin<=xmax;\n";
	Result<<"}\n";

	Result<<"bool Visible(vec4 A,vec4 B,vec4 C,vec4 D){\n";
	Result<<"	if(IsEdgeVisible(A,B))return true;\n";
	Result<<"	if(IsEdgeVisible(A,C))return true;\n";
	Result<<"	if(IsEdgeVisible(B,D))return true;\n";
	Result<<"	if(IsEdgeVisible(C,D))return true;\n";
	Result<<"	//TODO edges are not visible but we see extruded edge\n";
	Result<<"	return false;\n";
	Result<<"}\n";*/
	Result << "bool IsEdgeVisible(in vec4 A,in vec4 B){\n";
	Result << "	vec3 M=+A.xyz+A.www;\n";
	Result << "	vec3 N=+B.xyz+B.www;\n";
	Result << "	vec3 O=-A.xyz+A.www;\n";
	Result << "	vec3 P=-B.xyz+B.www;\n";
	Result << "	vec3 NM=N-M;\n";
	Result << "	vec3 PO=P-O;\n";
	Result << "	float Left=0;\n";
	Result << "	float Right=1;\n";
	Result << "	for(int i=0;i<3;++i){\n";
	Result << "		if(NM[i]==0){\n";
	Result << "			if(M[i]<0)return false;\n";
	Result << "		}else{\n";
	Result << "			if(NM[i]>0)Left=max(Left,-M[i]/NM[i]);\n";
	Result << "			else Right=min(Right,-M[i]/NM[i]);\n";
	Result << "		}\n";
	Result << " 	                                           \n";
	Result << "		if(PO[i]==0){\n";
	Result << "			if(O[i]<0)return false;\n";
	Result << "		}else{\n";
	Result << "			if(PO[i]>0)Left=max(Left,-O[i]/PO[i]);\n";
	Result << "			else Right=min(Right,-O[i]/PO[i]);\n";
	Result << "		}\n";
	Result << "	}\n";
	Result << "	return Left<=Right;\n";
	Result << "}\n";
	Result << "\n";
	Result << "bool IsFullVisible(in vec4 A,in vec4 B,in vec4 C,int Diag){\n";
	Result << "  vec3 a=A.xyz;\n";
	Result << "  vec3 b=B.xyz;\n";
	Result << "  vec3 c=C.xyz;\n";
	Result << "  if(Diag>=0){\n";
	Result << "    a[Diag]=-a[Diag];\n";
	Result << "    b[Diag]=-b[Diag];\n";
	Result << "    c[Diag]=-c[Diag];\n";
	Result << "  }\n";
	Result << "	float m=(a.x-a.y);\n";
	Result << "	float n=(b.x-b.y);\n";
	Result << "	float o=(c.x-c.y);\n";
	Result << "	float p=(a.x-a.z);\n";
	Result << "	float q=(b.x-b.z);\n";
	Result << "	float r=(c.x-c.z);\n";
	Result << "  float d=(q*o-n*r);\n";
	Result << "  float t=(m*r-p*o)/d;\n";
	Result << "  float l=-(m*q-p*n)/d;\n";
	Result << "	vec4 X=A+t*B+l*C;\n";
	Result << "  return (t>0)&&(t<1)&&(l>0)&&(l<1)&&\n";
	Result << "      all(greaterThan(X.xyz,-X.www))&&all(lessThan(X.xyz,X.www));\n";
	Result << "}\n";
	Result << "\n";
	Result << "#define MATRIX mvp\n";
	Result << "bool IsVisible(in vec4 a,in vec4 b,in vec4 c,in vec4 d,vec4 l){\n";
	Result << "	vec4 A=MATRIX*a;\n";
	Result << "	vec4 B=MATRIX*b;\n";
	Result << "	vec4 C=MATRIX*c;\n";
	Result << "	vec4 D=MATRIX*d;\n";
	Result << "	vec3 n=(MATRIX*vec4(cross(b.xyz-a.xyz,l.xyz-a.xyz*l.w),0)).xyz;\n";
	Result << "	ivec3 Corner=ivec3(1+sign(n))>>1;\n";
	Result << "  if(Corner.z==1);Corner=ivec3(1)-Corner;\n";
	Result << "	int Diag=Corner.x+(Corner.y<<1)-1;\n";
	Result << "	if(IsFullVisible(A,B-A,C-A,Diag))return true;\n";
	Result << "	if(IsEdgeVisible(A,B))return true;\n";
	Result << "	if(IsEdgeVisible(A,C))return true;\n";
	Result << "	if(IsEdgeVisible(B,D))return true;\n";
	Result << "	if(IsEdgeVisible(C,D))return true;\n";
	Result << "	return false;\n";
	Result << "}\n";

	return Result.str();
}

std::string GenGSSilFC() {
	std::stringstream Result;
	Result << "	if(!IsVisible(P[0],P[1],P[2],P[3],LightPosition))return;\n";
	return Result.str();
}

std::string GenGSSilGeometryPrologue(unsigned Num, SGSSilTemplate T, bool Cap) {
	std::stringstream Result;
	Result << GenVersion(T);
	Result << "#extension GL_EXT_geometry_shader4:enable\n";
	Result << GenGSSilGeometryInOut(Num, Cap, T);
	Result << GenUniforms(T);
	Result << GenInPosition(Num, T);
#ifdef USE_AMD
	if (true) {
#else
	if (T.Framebuffer) {
#endif
		/*if(T.ImageAtomicAdd)
			Result<<"flat out int gMultiplicity;\n";
		else*/
		Result << "flat out float gMultiplicity;\n";
		//FC
	}
	Result << GenGSSilFCFunc();


	if (T.Deterministic)Result << GenCmpVec();
	Result << "void main(){\n";
	Result << GenPoint("LightPosition", T);

	//FC
	//if(!T.Framebuffer&&!Cap&&T.Deterministic)Result<<GenGSSilFC();

	if (T.CullFace && !Cap)Result << GenGSSilFC();

	Result << GenOppositeArray(Num);
	if (!Cap)Result << "\tint Multiplicity=0;\n";
	if (T.Universal)Result << "\tint Num=int(vPosition" << Num + 1 << "[0].x);\n";
	else Result << "\tint Num=" << Num << ";\n";
	return Result.str();
	}

std::string GenGSSilGeometryHull(unsigned Num, SGSSilTemplate T) {
	std::stringstream Result;
	Result << GenGSSilGeometryPrologue(Num, T, false);//generate prologue
	Result << "\tfor(int i=0;i<Num;++i){\n";//loop over opposite vertices
	Result << GenComputeMultiplicityHull(T, "LightPosition");//compute multiplicity
	Result << "\t}\n";
	Result << GenHull(T);//generate geometry
	Result << "}\n";
	return Result.str();
}

std::string GenGSSilGeometryCap(unsigned Num, SGSSilTemplate T) {
	std::stringstream Result;
	Result << GenGSSilGeometryPrologue(Num, T, true);//generate prologue
	Result << "\tfor(int i=0;i<Num;++i){\n";//loop over opposite vertices
	Result << GenComputeMultiplicityCap(T, "LightPosition");//compute caps
	Result << "\t}\n";
	Result << "}\n";
	return Result.str();
}

std::string GenVersion(SGSSilTemplate T) {
	std::stringstream Result;//resulting framebuffer
	Result << "#version " << T.Version;//version of shader
	if (T.Compatible)Result << " compatible\n";//compatible mode
	else Result << "\n";//core mode
	return Result.str();
}

std::string GenGSSilFragment(SGSSilTemplate T) {
	std::stringstream Result;//resulting framebuffer
	Result << GenVersion(T);//generate version
	Result << "#extension GL_ARB_shading_language_420pack:enable\n";
	//Result<<"#extension GL_ARB_shader_stencil_export:enable\n";
	Result << "\n";
	Result << "layout(location=0)out vec4 fColor;\n";

#ifndef USE_AMD
	Result << "layout(early_fragment_tests)in;\n";
#endif

#ifdef USE_AMD
	if (true) {
#else
	if (T.Framebuffer) {
#endif
		if (T.ImageAtomicAdd) {
			Result << "flat in float gMultiplicity;\n";
			Result << "layout(r32i,location=0)coherent uniform iimage2D MyStencil;\n";
			Result << "ivec2 Coord=ivec2(gl_FragCoord.xy);\n";
		}
		else {
			Result << "flat in float gMultiplicity;\n";
		}
	}
	Result << "\n";
	Result << "void main(){\n";
	if (T.Framebuffer) {
		if (T.ImageAtomicAdd) {
			Result << "\tif(gl_FrontFacing)imageAtomicAdd(MyStencil,Coord,int(-gMultiplicity));\n";
			Result << "\telse imageAtomicAdd(MyStencil,Coord,int(gMultiplicity));\n";
		}
		else {
			Result << "\tif(gl_FrontFacing)fColor=vec4(-gMultiplicity);\n";
			Result << "\telse fColor=vec4(gMultiplicity);\n";
		}
	}
	else {
#ifdef USE_AMD
		//Result<<"\tif(gl_FrontFacing)gl_FragStencilValueAMD=int(gMultiplicity);\n";
		//Result<<"\telse gl_FragStencilValueAMD=int(-gMultiplicity);\n";
		/*
		//FUNKCNI
		Result<<"\tgl_FragStencilValueAMD=int(1+0*gMultiplicity);\n";
		*/
		//Result<<"\tgl_FragStencilValueAMD=int(gMultiplicity);\n";
#endif
		Result << "\tfColor=vec4(1);\n";
	}
	Result << "}";
	return Result.str();
	}

/*
std::string GenGSSilGeometryHullGI(unsigned Num,SGSSilTemplate T){
	std::stringstream Result;
	Result<<GenGSSilGeometryPrologue(Num,T,false);//generate prologue
	Result<<"\tfor(int i=0;i<Num;++i){\n";//loop over opposite vertices
	Result<<GenComputeMultiplicityHull(T,"LightPosition");//compute multiplicity
	Result<<"\t}\n";
	Result<<GenHull(T);//generate geometry
	Result<<"}\n";
	return Result.str();

}
*/

unsigned GetMinPowerOf2(unsigned MaxMultiplicity) {
	if (MaxMultiplicity == 0)return 0;
	MaxMultiplicity--;
	MaxMultiplicity |= MaxMultiplicity >> 1;
	MaxMultiplicity |= MaxMultiplicity >> 2;
	MaxMultiplicity |= MaxMultiplicity >> 4;
	MaxMultiplicity |= MaxMultiplicity >> 8;
	MaxMultiplicity |= MaxMultiplicity >> 16;
	return MaxMultiplicity + 1;
}

#endif

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
