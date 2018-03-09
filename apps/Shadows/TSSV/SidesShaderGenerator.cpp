#include "SidesShaderGenerator.hpp"

#include<sstream>

std::string GenTSSilLayoutLocation(bool Generate,unsigned Location){
	std::stringstream Result;
	Result<<"";//empty layout
	if(Generate)Result<<"layout(location="<<Location<<")";//generate layout
	return Result.str();//return layout
}

bool GenTSUseBuiltinMatrix(STSSilTemplate T){
	return T.MatrixUniformName==""||T.MatrixUniformName=="gl_ModelViewProjectionMatrix";
}

std::string GenTSMatrix(STSSilTemplate T){
	if(T.MatrixUniformName=="")return"gl_ModelViewProjectionMatrix";
	return T.MatrixUniformName;
}

std::string GenTSSilCompatibility(STSSilTemplate T){
	if(T.UseCompatibility||(T.Version>=130&&
				(T.MatrixUniformName==""||T.MatrixUniformName=="gl_ModelViewProjectionMatrix"))){
		return" compatibility";
	}
	return"";
}

std::string GenTSSilVertexAttribInputs(STSSilTemplate T){
	std::stringstream Result;
	//vertex attrib input layouts are available in verisions 330 and newer
	bool InputLayoutAvailable=(T.Version>=330)&&T.UseLayouts;
	std::string Input="in";//input qualifier
	if(T.Version<=120)Input="attribute";//input qualifier in older versions
	Result<<GenTSSilLayoutLocation(InputLayoutAvailable,0);//generate layouts
	Result<<Input<<" vec4 "<<T.VertexAttribName<<";\n";
	return Result.str();
}

std::string GenTSSilVertexHull(STSSilTemplate T){
	std::stringstream Result;
	Result<<"#version "<<T.Version<<GenTSSilCompatibility(T)<<"\n";//generate version
	Result<<"\n";
	Result<<GenTSSilVertexAttribInputs(T);//generate vertex attribs
	Result<<"\n";
	Result<<"void main(){\n";
	Result<<"  gl_Position="<<T.VertexAttribName<<";\n";
	Result<<"}\n";//main end
	return Result.str();
}

std::string GenTSSilFunction(STSSilTemplate T){
	std::stringstream Result;//result
	Result<<"int GreaterVec(vec3 a,vec3 b){\n";
	Result<<"  return int(dot(sign(a-b),vec3(4,2,1)));\n";
	Result<<"}\n";
	Result<<"int ComputeMult(vec3 A,vec3 B,vec3 C,vec4 L){\n";
	Result<<"  vec3 n=cross(C-A,L.xyz-A*L.w);\n";
	Result<<"  return int(sign(dot(n,B-A)));\n";
	Result<<"}\n";
  Result<<"bool IsEdgeVisible(in vec4 A,in vec4 B){\n";
  Result<<"	vec3 M=+A.xyz+A.www;\n";
  Result<<"	vec3 N=+B.xyz+B.www;\n";
  Result<<"	vec3 O=-A.xyz+A.www;\n";
  Result<<"	vec3 P=-B.xyz+B.www;\n";
  Result<<"	vec3 NM=N-M;\n";
  Result<<"	vec3 PO=P-O;\n";
  Result<<"	float Left=0;\n";
  Result<<"	float Right=1;\n";
  Result<<"	for(int i=0;i<3;++i){\n";
  Result<<"		if(NM[i]==0){\n";
  Result<<"			if(M[i]<0)return false;\n";
  Result<<"		}else{\n";
  Result<<"			if(NM[i]>0)Left=max(Left,-M[i]/NM[i]);\n";
  Result<<"			else Right=min(Right,-M[i]/NM[i]);\n";
  Result<<"		}\n";
  Result<<" 	                                           \n";
  Result<<"		if(PO[i]==0){\n";
  Result<<"			if(O[i]<0)return false;\n";
  Result<<"		}else{\n";
  Result<<"			if(PO[i]>0)Left=max(Left,-O[i]/PO[i]);\n";
  Result<<"			else Right=min(Right,-O[i]/PO[i]);\n";
  Result<<"		}\n";
  Result<<"	}\n";
  Result<<"	return Left<=Right;\n";
  Result<<"}\n";
  Result<<"\n";
  Result<<"bool IsFullVisible(in vec4 A,in vec4 B,in vec4 C,int Diag){\n";
  Result<<"  vec3 a=A.xyz;\n";
  Result<<"  vec3 b=B.xyz;\n";
  Result<<"  vec3 c=C.xyz;\n";
  Result<<"  if(Diag>=0){\n";
  Result<<"    a[Diag]=-a[Diag];\n";
  Result<<"    b[Diag]=-b[Diag];\n";
  Result<<"    c[Diag]=-c[Diag];\n";
  Result<<"  }\n";
  Result<<"	float m=(a.x-a.y);\n";
  Result<<"	float n=(b.x-b.y);\n";
  Result<<"	float o=(c.x-c.y);\n";
  Result<<"	float p=(a.x-a.z);\n";
  Result<<"	float q=(b.x-b.z);\n";
  Result<<"	float r=(c.x-c.z);\n";
  Result<<"  float d=(q*o-n*r);\n";
  Result<<"  float t=(m*r-p*o)/d;\n";
  Result<<"  float l=-(m*q-p*n)/d;\n";
  Result<<"	vec4 X=A+t*B+l*C;\n";
  Result<<"  return (t>0)&&(t<1)&&(l>0)&&(l<1)&&\n";
  Result<<"      all(greaterThan(X.xyz,-X.www))&&all(lessThan(X.xyz,X.www));\n";
  Result<<"}\n";
  Result<<"\n";
	std::string Matrix="gl_ModelViewProjectionMatrix";
	if(T.MatrixUniformName!=""&&T.MatrixUniformName!="gl_ModelViewProjectionMatrix")
		Matrix=T.MatrixUniformName;
  Result<<"#define MATRIX "<<Matrix<<"\n";
  Result<<"bool IsVisible(in vec4 a,in vec4 b,in vec4 c,in vec4 d,vec4 l){\n";
  Result<<"	vec4 A=MATRIX*a;\n";
  Result<<"	vec4 B=MATRIX*b;\n";
  Result<<"	vec4 C=MATRIX*c;\n";
  Result<<"	vec4 D=MATRIX*d;\n";
  Result<<"	vec3 n=(MATRIX*vec4(cross(b.xyz-a.xyz,l.xyz-a.xyz*l.w),0)).xyz;\n";
  Result<<"	ivec3 Corner=ivec3(1+sign(n))>>1;\n";
  Result<<"  if(Corner.z==1);Corner=ivec3(1)-Corner;\n";
  Result<<"	int Diag=Corner.x+(Corner.y<<1)-1;\n";
  Result<<"	if(IsFullVisible(A,B-A,C-A,Diag))return true;\n";
  Result<<"	if(IsEdgeVisible(A,B))return true;\n";
  Result<<"	if(IsEdgeVisible(A,C))return true;\n";
  Result<<"	if(IsEdgeVisible(B,D))return true;\n";
  Result<<"	if(IsEdgeVisible(C,D))return true;\n";
  Result<<"	return false;\n";
  Result<<"}\n";

	return Result.str();//return result
}

std::string GenTSSilControlHull(unsigned Num,STSSilTemplate T){
	std::stringstream Result;
	Result<<"#version "<<T.Version<<GenTSSilCompatibility(T)<<"\n";//generate version
	Result<<"\n";
	Result<<"layout(vertices=1)out;\n";
	Result<<"\n";
	Result<<"uniform vec4 "<<T.LightPositionUniformName<<";\n";
	if(T.MatrixUniformName!=""&&T.MatrixUniformName!="gl_ModelViewProjectionMatrix"){
		Result<<"uniform mat4 "<<T.MatrixUniformName<<";\n";
		Result<<"\n";
	}
  if(T.UseStencilValueExport){
    Result<<"patch out int cMultiplicity;\n";
  }
	Result<<"\n";
	Result<<GenTSSilFunction(T);
	Result<<"\n";
	Result<<"patch out vec4 P[4];\n";
	if(T.UseSillyPerPatchLevel)Result<<"patch out float TessLevel;\n";
	Result<<"\n";
	Result<<"void main(){\n";
	if(T.Universal)Result<<"  int Num=int(gl_in[2].gl_Position.x);\n";
	Result<<"\n";
	Result<<"  int Multiplicity=0;\n";
  if(T.CullSides){
    Result<<"#define PLL "<<T.LightPositionUniformName<<"\n";
    Result<<"#define PA gl_in[0].gl_Position\n";
    Result<<"#define PB gl_in[1].gl_Position\n";
    Result<<"#define PC vec4(gl_in[0].gl_Position.xyz*PLL.w-PLL.xyz,0)\n";
    Result<<"#define PD vec4(gl_in[1].gl_Position.xyz*PLL.w-PLL.xyz,0)\n";
		Result<<"if(!IsVisible(PA,PB,PC,PD,PLL))\n";
    Result<<"{\n";
	  Result<<"  TessLevel=gl_TessLevelOuter[1]=0;\n";
    Result<<"  gl_TessLevelOuter[0]=0;\n";
	  Result<<"  gl_TessLevelOuter[3]=gl_TessLevelOuter[2]=0;\n";
	  Result<<"  gl_TessLevelInner[1]=gl_TessLevelInner[0]=0;\n";
    Result<<"return;\n";
    Result<<"}\n";
  }
	if(T.UseReferenceEdge){
		if(T.Universal)Result<<"  for(int i=0;i<Num;++i){\n";
		else Result<<"  for(int i=0;i<"<<Num<<";++i){\n";
		Result<<"#define T0 gl_in[0].gl_Position.xyz\n";
		Result<<"#define T1 gl_in[1].gl_Position.xyz\n";
		if(T.Universal)Result<<"#define T2 gl_in[i+3].gl_Position.xyz\n";
		else Result<<"#define T2 gl_in[i+2].gl_Position.xyz\n";
		Result<<"    if(GreaterVec(T0,T2)>0){//T[2] T[0] T[1]?\n";
		Result<<"      Multiplicity+=ComputeMult(T2,T0,T1,"<<T.LightPositionUniformName<<");\n";
		Result<<"    }else{\n";
		Result<<"      if(GreaterVec(T1,T2)>0){//T[0] T[2] T[1]?\n";
		Result<<"        Multiplicity-=ComputeMult(T0,T2,T1,"<<T.LightPositionUniformName<<");\n";
		Result<<"      }else{//T[0] T[1] T[2]?\n";
		Result<<"        Multiplicity+=ComputeMult(T0,T1,T2,"<<T.LightPositionUniformName<<");\n";
		Result<<"      }\n";
		Result<<"    }\n";
		Result<<"  }\n";//for end
	}else{//use GraphiCon determinism
		if(T.Universal)Result<<"  for(int i=0;i<Num;++i){\n";
		else Result<<"  for(int i=0;i<"<<Num<<";++i){\n";
		Result<<"    vec3 D[3];\n";
		Result<<"    vec3 NS[3];\n";
		Result<<"    vec4 PL[3];\n";
		Result<<"    float d[3];\n";
		Result<<"\n";
		Result<<"#define T0 gl_in[0].gl_Position.xyz\n";
		Result<<"#define T1 gl_in[1].gl_Position.xyz\n";
		if(T.Universal)Result<<"#define T2 gl_in[i+3].gl_Position.xyz\n";
		else Result<<"#define T2 gl_in[i+2].gl_Position.xyz\n";
		Result<<"\n";
		Result<<"    D[0]="<<T.LightPositionUniformName<<".xyz-T0*"<<T.LightPositionUniformName<<".w;\n";
		Result<<"    NS[0]=normalize(cross(T1-T0,D[0]));\n";
		Result<<"    PL[0]=vec4(NS[0],-dot(NS[0],T0));\n";
		Result<<"    d[0]=dot(PL[0],vec4(T2,1));\n";
		Result<<"\n";
		Result<<"    D[1]="<<T.LightPositionUniformName<<".xyz-T1*"<<T.LightPositionUniformName<<".w;\n";
		Result<<"    D[2]="<<T.LightPositionUniformName<<".xyz-T2*"<<T.LightPositionUniformName<<".w;\n";
		Result<<"\n";
		Result<<"    if(GreaterVec(T2,T0)>0){\n";
		Result<<"      NS[1]=normalize(cross(T2-T0,D[0]));\n";
		Result<<"      PL[1]=vec4(NS[1],-dot(NS[1],T0));\n";
		Result<<"      d[1]=dot(PL[1],vec4(T1,1));\n";
		Result<<"    }\n";
		Result<<"    else{\n";
		Result<<"      NS[1]=normalize(cross(T0-T2,D[2]));\n";
		Result<<"      PL[1]=vec4(NS[1],-dot(NS[1],T2));\n";
		Result<<"      d[1]=-dot(PL[1],vec4(T1,1));\n";
		Result<<"    }\n";
		Result<<"\n";
		Result<<"    if(GreaterVec(T2,T1)>0){\n";
		Result<<"      NS[2]=normalize(cross(T2-T1,D[1]));\n";
		Result<<"      PL[2]=vec4(NS[2],-dot(NS[2],T1));\n";
		Result<<"      d[2]=dot(PL[2],vec4(T0,1));\n";
		Result<<"    }else{\n";
		Result<<"      NS[2]=normalize(cross(T1-T2,D[2]));\n";
		Result<<"      PL[2]=vec4(NS[2],-dot(NS[2],T2));\n";
		Result<<"      d[2]=-dot(PL[2],vec4(T0,1));\n";
		Result<<"    }\n";
		Result<<"        \n";
		Result<<"\n";
		Result<<"    if(d[0]==0||d[1]==0||d[2]==0)continue;\n";
		Result<<"    if(!((d[0]<0&&d[1]>0&&d[2]<0)||(d[0]>0&&d[1]<0&&d[2]>0)))continue;\n";
		Result<<"    if(d[0]<0)Multiplicity++;\n";
		Result<<"    else if(d[0]>0)Multiplicity--;\n";
		Result<<"  }\n";
	}
  
  //if(T.CullSides){Result<<"}\n";}
	Result<<"\n";
	Result<<"  int AbsMultiplicity=abs(Multiplicity);\n";
	Result<<"  gl_TessLevelOuter[0]=int(AbsMultiplicity>0);\n";
	Result<<"  gl_TessLevelOuter[2]=1;\n";
	if(T.UseSillyPerPatchLevel)Result<<"  TessLevel=";
	else Result<<"  ";
	Result<<"gl_TessLevelOuter[1]=gl_TessLevelOuter[3]=gl_TessLevelInner[0]=";
	if(T.UseOptimizedDegeneration){
    if(T.UseStencilValueExport)Result<<"int(AbsMultiplicity>0);\n";
    else Result<<"2*AbsMultiplicity-1;\n";
  }
	else Result<<"AbsMultiplicity+(AbsMultiplicity-1)*2+int(1-(AbsMultiplicity&1));\n";
	Result<<"  gl_TessLevelInner[1]=1;\n";
	Result<<"\n";
	std::string Matrix="gl_ModelViewProjectionMatrix";
	if(T.MatrixUniformName!=""&&T.MatrixUniformName!="gl_ModelViewProjectionMatrix")
		Matrix=T.MatrixUniformName;

  Result<<"#define MATRIX "<<Matrix<<"\n";
	Result<<"  if(Multiplicity>0){\n";
  if(T.UseStencilValueExport)
    Result<<"cMultiplicity=Multiplicity;\n";
	Result<<"    P[0]=MATRIX*vec4(gl_in[1].gl_Position.xyz,1);\n";
	Result<<"    P[1]=MATRIX*vec4(gl_in[0].gl_Position.xyz,1);\n";
	Result<<"    P[2]=MATRIX*vec4(gl_in[1].gl_Position.xyz*LightPosition.w-LightPosition.xyz,0);\n";
	Result<<"    P[3]=MATRIX*vec4(gl_in[0].gl_Position.xyz*LightPosition.w-LightPosition.xyz,0);\n";
	Result<<"  }\n";
	Result<<"  if(Multiplicity<0)\n";
	Result<<"  {\n";
  if(T.UseStencilValueExport)
    Result<<"cMultiplicity=-Multiplicity;\n";
	Result<<"    P[0]=MATRIX*vec4(gl_in[0].gl_Position.xyz,1);\n";
	Result<<"    P[1]=MATRIX*vec4(gl_in[1].gl_Position.xyz,1);\n";
	Result<<"    P[2]=MATRIX*vec4(gl_in[0].gl_Position.xyz*LightPosition.w-LightPosition.xyz,0);\n";
	Result<<"    P[3]=MATRIX*vec4(gl_in[1].gl_Position.xyz*LightPosition.w-LightPosition.xyz,0);\n";
	Result<<"  }\n";
	Result<<"}\n";//main end
	return Result.str();
}

std::string GenTSSilEvaluationHull(STSSilTemplate T){
	std::stringstream Result;
	Result<<"#version "<<T.Version<<GenTSSilCompatibility(T)<<"\n";//generate version
	Result<<"\n";
	Result<<"layout(quads,fractional_odd_spacing,cw)in;\n";
	Result<<"\n";
	Result<<"patch in vec4 P[4];\n";
  if(T.UseStencilValueExport){
    Result<<"patch in int cMultiplicity;\n";
    Result<<"flat out int eMultiplicity;\n";
  }
	if(T.UseSillyPerPatchLevel)Result<<"patch in float TessLevel;\n";
	Result<<"\n";
	if(T.MatrixUniformName!=""&&T.MatrixUniformName!="gl_ModelViewProjectionMatrix"){
		Result<<"uniform mat4 "<<T.MatrixUniformName<<";\n";
		Result<<"\n";
	}
	Result<<"int GetIndex(){\n";
	if(T.UseSillyPerPatchLevel)Result<<"  int x=int(round(gl_TessCoord.x*TessLevel))*2;\n";
	else Result<<"  int x=int(round(gl_TessCoord.x*gl_TessLevelInner[0]))*2;\n";
	Result<<"  int y=int(round(gl_TessCoord.y));\n";
	Result<<"  int id=x+y;\n";
	if(T.UseOptimizedDegeneration){
		Result<<"  int l=((id+2)/4)%2;\n";
		Result<<"  int t=(id%2)^((id/4)%2);\n";
	}else{
		Result<<"  int l=((id+1)/3)%2;\n";
		Result<<"  int t=int(((id+1)%3)/2)+int(((id+1)%6)==4);\n";
	}
	Result<<"  return t+l*2;\n";
	Result<<"}\n";

	Result<<"\n";
	Result<<"void main(){\n";
	std::string Matrix="gl_ModelViewProjectionMatrix";
	if(T.MatrixUniformName!=""&&T.MatrixUniformName!="gl_ModelViewProjectionMatrix")
		Matrix=T.MatrixUniformName;
	//Result<<"  gl_Position="<<Matrix<<"*P[GetIndex()];\n";
  Result<<"if(TessLevel!=0)";
	Result<<"  gl_Position=P[GetIndex()];\n";
  if(T.UseStencilValueExport)
    Result<<"eMultiplicity=cMultiplicity;\n";
	Result<<"}\n";//main end
	return Result.str();
}

std::string GenTSSilFragmentHull(STSSilTemplate T){
	std::stringstream Result;
	Result<<"#version "<<T.Version<<GenTSSilCompatibility(T)<<"\n";//generate version
	Result<<"\n";
  if(T.UseStencilValueExport){
    Result<<"  #extension GL_ARB_shader_stencil_export:enable\n";
    Result<<"flat in int eMultiplicity;\n";
  }
	bool FragmentOutputLayoutAvailable=false;
	if(T.Version>=330)FragmentOutputLayoutAvailable=true;
	std::string OutputVariable="gl_FragColor";
	if(T.Version>120){
		OutputVariable="fColor";
		Result<<GenTSSilLayoutLocation(FragmentOutputLayoutAvailable,0);
		Result<<"out vec4 "<<OutputVariable<<";\n";
	}
	Result<<"void main(){\n";
	Result<<"  "<<OutputVariable<<"=vec4(1,0,1,1);\n";
  if(T.UseStencilValueExport)
    Result<<"gl_FragStencilValueAMD=eMultiplicity;\n";
	Result<<"}\n";//main end
	return Result.str();
}
