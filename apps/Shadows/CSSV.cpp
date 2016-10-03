#include"CSSV.h"
#include"FastAdjacency.h"

#include<geCore/Dtemplates.h>

CSSV::CSSV(
    size_t maxMultiplicity,
    int computeSidesWGS,
    glm::uvec2 const&windowSize,
    std::shared_ptr<ge::gl::Texture>const&depth,
    std::shared_ptr<Model>const&model,
    std::shared_ptr<ge::gl::Texture>const&shadowMask):_windowSize(windowSize),_computeSidesWGS(computeSidesWGS){
  assert(this!=nullptr);
  this->_timeStamper = std::make_shared<TimeStamp>();

  this->_fbo = std::make_shared<ge::gl::Framebuffer>();
  this->_fbo->attachTexture(GL_DEPTH_ATTACHMENT,depth);
  this->_fbo->attachTexture(GL_STENCIL_ATTACHMENT,depth);
  assert(this->_fbo->check());

  this->_maskFbo = std::make_shared<ge::gl::Framebuffer>();
  this->_maskFbo->attachTexture(GL_STENCIL_ATTACHMENT,depth);
  this->_maskFbo->attachTexture(GL_COLOR_ATTACHMENT0,shadowMask);
  this->_maskFbo->drawBuffers(1,GL_COLOR_ATTACHMENT0);

  std::vector<float>vertices;
  model->getVertices(vertices);
  auto adj = std::make_shared<Adjacency>(vertices.data(),vertices.size()/9,maxMultiplicity);

  size_t numVer = 2+adj->getMaxMultiplicity();
  this->_adjacency = std::make_shared<ge::gl::Buffer>(sizeof(float)*4*numVer*adj->getNofEdges());

  float*Ptr=(float*)this->_adjacency->map();

  for(unsigned e=0;e<adj->getNofEdges();++e){
    //A
    for(int k=0;k<3;++k)
      Ptr[(e*numVer+0)*4+k]=adj->getVertices()[adj->getEdge(e,0)+k];
    Ptr[(e*numVer+0)*4+3]=adj->getNofOpposite(e);
    //B
    for(int k=0;k<3;++k)
      Ptr[(e*numVer+1)*4+k]=adj->getVertices()[adj->getEdge(e,1)+k];
    Ptr[(e*numVer+1)*4+3]=1;
    //O
    for(unsigned o=0;o<adj->getNofOpposite(e);++o){
      for(int k=0;k<3;++k)
        Ptr[(e*numVer+2+o)*4+k]=adj->getVertices()[adj->getOpposite(e,o)+k];
      Ptr[(e*numVer+2+o)*4+3]=1;
    }
    for(unsigned o=adj->getNofOpposite(e);o<adj->getMaxMultiplicity();++o){
      for(int k=0;k<4;++k)
        Ptr[(e*numVer+2+o)*4+k]=0;
    }
  }
  this->_adjacency->unmap();
  this->_nofEdges = adj->getNofEdges();

  this->_sillhouettes=std::make_shared<ge::gl::Buffer>(
      sizeof(float)*4*4*this->_nofEdges*adj->getMaxMultiplicity(),
      nullptr,GL_DYNAMIC_COPY);
  this->_sillhouettes->clear(GL_R32F,GL_RED,GL_FLOAT);

  this->_dibo=std::make_shared<ge::gl::Buffer>(sizeof(unsigned)*4);
  unsigned*CPtr=(unsigned*)this->_dibo->map();
  CPtr[0]=0;
  CPtr[1]=1;
  CPtr[2]=0;
  CPtr[3]=0;
  this->_dibo->unmap();

  this->_sidesVao=std::make_shared<ge::gl::VertexArray>();
  this->_sidesVao->addAttrib(this->_sillhouettes,0,4,GL_FLOAT);

  const std::string computeSrc = R".(
#ifndef MAX_MULTIPLICITY
#define MAX_MULTIPLICITY 4
#endif//MAX_MULTIPLICITY

#ifndef WORKGROUP_SIZE_X
#define WORKGROUP_SIZE_X 64
#endif//WORKGROUP_SIZE_X

//#define CULL_SIDE

layout(local_size_x=WORKGROUP_SIZE_X)in;

layout(std430,binding=0)buffer SInput  {vec4 IBuffer[];};
layout(std430,binding=1)buffer SOutput {vec4 OBuffer[];};
layout(std430,binding=2)buffer SCounter{uint Counter[];};

uniform uint NumEdge=0;
uniform vec4 LightPosition;
uniform mat4 mvp;

int greaterVec(vec3 a,vec3 b){
  return int(dot(ivec3(sign(a-b)),ivec3(4,2,1)));
}

int computeMult(vec3 A,vec3 B,vec3 C,vec4 L){
  vec3 n=cross(C-A,L.xyz-A*L.w);
  return int(sign(dot(n,B-A)));
}

bool isEdgeVisible(in vec4 A,in vec4 B){
  vec3 M=+A.xyz+A.www;
  vec3 N=+B.xyz+B.www;
  vec3 O=-A.xyz+A.www;
  vec3 P=-B.xyz+B.www;
  vec3 NM=N-M;
  vec3 PO=P-O;
  float Left=0;
  float Right=1;
  for(int i=0;i<3;++i){
    if(NM[i]==0){
      if(M[i]<0)return false;
    }else{
      if(NM[i]>0)Left=max(Left,-M[i]/NM[i]);
      else Right=min(Right,-M[i]/NM[i]);
    }

    if(PO[i]==0){
      if(O[i]<0)return false;
    }else{
      if(PO[i]>0)Left=max(Left,-O[i]/PO[i]);
      else Right=min(Right,-O[i]/PO[i]);
    }
  }
  return Left<=Right;
}

bool isFullVisible(in vec4 A,in vec4 B,in vec4 C,int Diag){
  vec3 a=A.xyz;
  vec3 b=B.xyz;
  vec3 c=C.xyz;
  if(Diag>=0){
    a[Diag]=-a[Diag];
    b[Diag]=-b[Diag];
    c[Diag]=-c[Diag];
  }
  float m=(a.x-a.y);
  float n=(b.x-b.y);
  float o=(c.x-c.y);
  float p=(a.x-a.z);
  float q=(b.x-b.z);
  float r=(c.x-c.z);
  float d=(q*o-n*r);
  float t=(m*r-p*o)/d;
  float l=-(m*q-p*n)/d;
  vec4 X=A+t*B+l*C;
  return (t>0)&&(t<1)&&(l>0)&&(l<1)&&
    all(greaterThan(X.xyz,-X.www))&&all(lessThan(X.xyz,X.www));
}

bool isVisible(in vec4 a,in vec4 b,in vec4 c,in vec4 d,vec4 l){
  vec4 A=mvp*a;
  vec4 B=mvp*b;
  vec4 C=mvp*c;
  vec4 D=mvp*d;
  vec3 n=(mvp*vec4(cross(b.xyz-a.xyz,l.xyz-a.xyz*l.w),0)).xyz;
  ivec3 Corner=ivec3(1+sign(n))>>1;
  if(Corner.z==1)Corner=ivec3(1)-Corner;
  int Diag=Corner.x+(Corner.y<<1)-1;
  if(isFullVisible(A,B-A,C-A,Diag))return true;
  if(isEdgeVisible(A,B))return true;
  if(isEdgeVisible(A,C))return true;
  if(isEdgeVisible(B,D))return true;
  if(isEdgeVisible(C,D))return true;
  return false;
}

bool isVisible(in vec4 P[4],in int Diag){
  if(isFullVisible(P[0],P[1]-P[0],P[2]-P[0],Diag))return true;
  if(isEdgeVisible(P[0],P[1]))return true;
  if(isEdgeVisible(P[0],P[2]))return true;
  if(isEdgeVisible(P[1],P[3]))return true;
  if(isEdgeVisible(P[2],P[3]))return true;
  return false;
}

void main(){
  uint gid=gl_GlobalInvocationID.x;
  if(gid<NumEdge){//compute silhouette
    vec4 P[4];
    gid*=2+MAX_MULTIPLICITY;

    P[0]=IBuffer[gid+0];
    P[1]=IBuffer[gid+1];
    P[2]=vec4(P[0].xyz*LightPosition.w-LightPosition.xyz,0);
    P[3]=vec4(P[1].xyz*LightPosition.w-LightPosition.xyz,0);

    int Num=int(P[0].w)+2;
    P[0].w=1;

#ifdef CULL_SIDE
    vec4 ClipP[4];
    for(int i=0;i<4;++i)
      ClipP[i]=mvp*P[i];

    vec3 Normal=(mvp*vec4(cross(
            P[1].xyz-P[0].xyz,
            LightPosition.xyz-P[0].xyz*LightPosition.w),0)).xyz;
    ivec3 Corner=ivec3(1+sign(Normal))>>1;
    if(Corner.z==1);Corner=ivec3(1)-Corner;
    int Diag=Corner.x+(Corner.y<<1)-1;

    if(!isVisible(ClipP,Diag))return;
#endif//CULL_SIDE

    precise int Multiplicity=0;
    if(Num>20)Num=0;
    if(Num<0)Num=0;

    for(int i=2;i<Num;++i){
#define T0 P[0].xyz
#define T1 P[1].xyz
#define T2 IBuffer[gid+i].xyz
      if(greaterVec(T0,T2)>0){//T[2] T[0] T[1]?
        Multiplicity+=computeMult(T2,T0,T1,LightPosition);
      }else{
        if(greaterVec(T1,T2)>0){//T[0] T[2] T[1]?
          Multiplicity-=computeMult(T0,T2,T1,LightPosition);
        }else{//T[0] T[1] T[2]?
          Multiplicity+=computeMult(T0,T1,T2,LightPosition);
        }
      }
    }
    if(Multiplicity>0){
      uint WH=atomicAdd(Counter[0],4*Multiplicity);
      for(int m=0;m<Multiplicity;++m){
        OBuffer[WH++]=P[1];
        OBuffer[WH++]=P[0];
        OBuffer[WH++]=P[3];
        OBuffer[WH++]=P[2];
      }
    }
    if(Multiplicity<0){
      Multiplicity=-Multiplicity;
      uint WH=atomicAdd(Counter[0],4*Multiplicity);
      for(int m=0;m<Multiplicity;++m){
        OBuffer[WH++]=P[0];
        OBuffer[WH++]=P[1];
        OBuffer[WH++]=P[2];
        OBuffer[WH++]=P[3];
      }
    }
  }
}).";
  this->_computeSides = std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(GL_COMPUTE_SHADER,
        "#version 450 core\n",
        ge::gl::Shader::define("WORKGROUP_SIZE_X",this->_computeSidesWGS),
        ge::gl::Shader::define("MAX_MULTIPLICITY",(int)adj->getMaxMultiplicity()),
        computeSrc));

  const std::string drawVPSrc = R".(
#version 450 core
layout(location=0)in vec4 Position;
uniform mat4 mvp;
void main(){
	gl_Position=mvp*Position;
}).";
  const std::string drawCPSrc = R".(
#version 450 core
layout(vertices=4)out;
void main(){
	gl_out[gl_InvocationID].gl_Position=gl_in[gl_InvocationID].gl_Position;
	if(gl_InvocationID==0){
		gl_TessLevelOuter[0]=1;
		gl_TessLevelOuter[1]=1;
		gl_TessLevelOuter[2]=1;
		gl_TessLevelOuter[3]=1;
		gl_TessLevelInner[0]=1;
		gl_TessLevelInner[1]=1;
	}
}).";
  const std::string drawEPSrc = R".(
#version 450 core
layout(quads)in;
void main(){
	gl_Position=mix(
		mix(
			gl_in[0].gl_Position,
			gl_in[1].gl_Position,
			gl_TessCoord.x),
		mix(
			gl_in[2].gl_Position,
			gl_in[3].gl_Position,
			gl_TessCoord.x),
		gl_TessCoord.y);
}).";
  const std::string drawFPSrc = R".(
#version 450 core
layout(location=0)out vec4 fragColor;
void main(){
	fragColor=vec4(1);
}).";
  this->_drawSides=std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER         ,drawVPSrc),
      std::make_shared<ge::gl::Shader>(GL_TESS_CONTROL_SHADER   ,drawCPSrc),
      std::make_shared<ge::gl::Shader>(GL_TESS_EVALUATION_SHADER,drawEPSrc),
      std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER       ,drawFPSrc));


  this->_emptyVao = std::make_shared<ge::gl::VertexArray>();
  const std::string blitVPSrc = R".(
#version 450 core
void main(){
  gl_Position = vec4(-1+2*(gl_VertexID/2),-1+2*(gl_VertexID%2),0,1);
}).";
  const std::string blitFPSrc = R".(
#version 450 core
layout(location=0)out float fColor;
void main(){
  fColor = 1;
}).";
  this->_blit = std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER,blitVPSrc),
      std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER,blitFPSrc));


  this->_nofTriangles=adj->getNofTriangles();
  this->_caps = std::make_shared<ge::gl::Buffer>(sizeof(float)*4*3*this->_nofTriangles);
  Ptr=(float*)this->_caps->map();
  for(unsigned t=0;t<this->_nofTriangles;++t){
    for(unsigned p=0;p<3;++p){
      for(unsigned i=0;i<3;++i)
        Ptr[(t*3+p)*4+i]=adj->getVertices()[(t*3+p)*3+i];
      Ptr[(t*3+p)*4+3]=1;
    }
  }
  this->_caps->unmap();
  this->_capsVao = std::make_shared<ge::gl::VertexArray>();
  this->_capsVao->addAttrib(this->_caps,0,4,GL_FLOAT);

  const std::string capsVPSrc = R".(
#version 450 core
layout(location=0)in vec4 Position;
void main(){
  gl_Position=Position;
}).";
  const std::string capsGPSrc = R".(
#version 450 core

#define SHIFT_TRIANGLE_TO_INFINITY

#ifdef SHIFT_TRIANGLE_TO_INFINITY
  #define SWIZZLE xyww
#else
  #define SWIZZLE xyzw
#endif

//front cap, light facing
#define FCLF0 0
#define FCLF1 1
#define FCLF2 2
//back cap, light facing
#define BCLF0 2
#define BCLF1 1
#define BCLF2 0
//front cap, light back-facing
#define FCLB0 2
#define FCLB1 1
#define FCLB2 0
//back cap, light back-facing
#define BCLB0 0
#define BCLB1 1
#define BCLB2 2

layout(triangles)in;
layout(triangle_strip,max_vertices=6)out;

uniform mat4 mvp;
uniform vec4 LightPosition;

/**
* @brief Computes greater vector
*
* @param a vertex a
* @param b vertex b
*
* @return 1 if a>b, 0 if a==b, -1 if b<a
*/
int GreaterVec(in vec3 a,in vec3 b){
  return int(dot(sign(a-b),vec3(4,2,1)));
}

/**
* @brief Function computes multiplicity for one opposite vertex
*
* @param A smallest vertex of a triangle
* @param B middle vertex of a triangle
* @param C largest vertex of a triangle
* @param L light position
*
* @return 1 ABC (CCW) facing L, -1 ABC (CCW) not-facing L
*/
int ComputeMult(in vec3 A,in vec3 B,in vec3 C,in vec4 L){
  vec3 n=cross(C-A,L.xyz-A*L.w);//normal vector of light plane
  return int(sign(dot(n,B-A)));//multiplicity
}

void Swap(inout vec4 A,inout vec4 B){
  vec4 C=A;A=B;B=C;
}

void main(){
  vec4 A=gl_in[0].gl_Position;
  vec4 B=gl_in[1].gl_Position;
  vec4 C=gl_in[2].gl_Position;
  bool Swapped=false;
  if(GreaterVec(A.xyz,B.xyz)>0){Swap(A,B);Swapped=!Swapped;}
  if(GreaterVec(B.xyz,C.xyz)>0){Swap(B,C);Swapped=!Swapped;}
  if(GreaterVec(A.xyz,B.xyz)>0){Swap(A,B);Swapped=!Swapped;}
  /*
    000: ABC CCW 
    100: BAC CW                                                                 
    010: ACB CW                                                                 
    110: BCA CCW                                                                
    001: X                                                                      
    101: X                                                                      
    011: CAB CCW                                                                
    111: CBA CW
   */

  int Multiplicity;

  if(Swapped)
    Multiplicity=-ComputeMult(A.xyz,B.xyz,C.xyz,LightPosition);
  else
    Multiplicity=+ComputeMult(A.xyz,B.xyz,C.xyz,LightPosition);

  if(Multiplicity==0)return;

  if(Multiplicity>0){
    gl_Position=(mvp*gl_in[FCLF0].gl_Position).SWIZZLE;EmitVertex(); 
    gl_Position=(mvp*gl_in[FCLF1].gl_Position).SWIZZLE;EmitVertex(); 
    gl_Position=(mvp*gl_in[FCLF2].gl_Position).SWIZZLE;EmitVertex(); 
    EndPrimitive();
//*
    if(LightPosition.w>0){
      gl_Position=(mvp*vec4(gl_in[BCLF0].gl_Position.xyz-LightPosition.xyz,0));
      EmitVertex();
      gl_Position=(mvp*vec4(gl_in[BCLF1].gl_Position.xyz-LightPosition.xyz,0));
      EmitVertex();
      gl_Position=(mvp*vec4(gl_in[BCLF2].gl_Position.xyz-LightPosition.xyz,0));
      EmitVertex();
      EndPrimitive();
    }// */
  }else{
    gl_Position=(mvp*gl_in[FCLB0].gl_Position).SWIZZLE;EmitVertex(); 
    gl_Position=(mvp*gl_in[FCLB1].gl_Position).SWIZZLE;EmitVertex(); 
    gl_Position=(mvp*gl_in[FCLB2].gl_Position).SWIZZLE;EmitVertex(); 
    EndPrimitive();
//*
    if(LightPosition.w>0){
      gl_Position=(mvp*vec4(gl_in[BCLB0].gl_Position.xyz-LightPosition.xyz,0));
      EmitVertex();
      gl_Position=(mvp*vec4(gl_in[BCLB1].gl_Position.xyz-LightPosition.xyz,0));
      EmitVertex();
      gl_Position=(mvp*vec4(gl_in[BCLB2].gl_Position.xyz-LightPosition.xyz,0));
      EmitVertex();
      EndPrimitive();
    }// */
  }
}).";
  const std::string capsFPSrc = R".(
#version 450 core

layout(location=0)out vec4 fColor;

void main(){
  if(gl_FrontFacing)
    fColor=vec4(0,1,0,1);
  else
    fColor=vec4(1,0,0,1);
}).";

  this->_drawCaps = std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER,capsVPSrc),
      std::make_shared<ge::gl::Shader>(GL_GEOMETRY_SHADER,capsGPSrc),
      std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER,capsFPSrc));


}

CSSV::~CSSV(){
}

void CSSV::create(glm::vec4 const&lightPosition,
    glm::mat4 const&view,
    glm::mat4 const&projection){
  (void)lightPosition;
  (void)view;
  (void)projection;
  auto mvp = projection*view;

  this->_timeStamper->begin();
  this->_dibo->clear(GL_R32UI,0,sizeof(unsigned),GL_RED_INTEGER,GL_UNSIGNED_INT);

  glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
  this->_computeSides->use();
  this->_computeSides->set1ui("NumEdge",this->_nofEdges);
  this->_computeSides->set4fv("LightPosition",glm::value_ptr(lightPosition));
  //this->_computeSides->setMatrix4fv("mvp",glm::value_ptr(mvp));
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER,0,this->_adjacency->getId());
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER,1,this->_sillhouettes->getId());
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER,2,this->_dibo->getId());

  glDispatchCompute(ge::core::getDispatchSize(this->_nofEdges,this->_computeSidesWGS),1,1);

  glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
  this->_timeStamper->stamp("computeSillhouettes");

  this->_fbo->bind();
  glEnable(GL_STENCIL_TEST);
  glStencilFunc(GL_ALWAYS,0,0);
  if(true){
    glStencilOpSeparate(GL_FRONT,GL_KEEP,GL_INCR_WRAP,GL_KEEP);
    glStencilOpSeparate(GL_BACK,GL_KEEP,GL_DECR_WRAP,GL_KEEP);
  }else{
    glStencilOpSeparate(GL_FRONT,GL_KEEP,GL_KEEP,GL_INCR_WRAP);
    glStencilOpSeparate(GL_BACK,GL_KEEP,GL_KEEP,GL_DECR_WRAP);
  }
  glDepthFunc(GL_LESS);
  glDepthMask(GL_FALSE);
  glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
  this->_drawSides->use();
  this->_drawSides->setMatrix4fv("mvp",glm::value_ptr(mvp));
  this->_sidesVao->bind();
  this->_dibo->bind(GL_DRAW_INDIRECT_BUFFER);
  glPatchParameteri(GL_PATCH_VERTICES,4);
  glDrawArraysIndirect(GL_PATCHES,NULL);
  this->_sidesVao->unbind();
  this->_timeStamper->stamp("drawSides");

  this->_drawCaps->use();
  this->_drawCaps->setMatrix4fv("mvp",glm::value_ptr(mvp));
  this->_drawCaps->set4fv("LightPosition",glm::value_ptr(lightPosition));
  this->_capsVao->bind();
  glDrawArrays(GL_TRIANGLES,0,this->_nofTriangles*3);
  this->_capsVao->unbind();

  this->_fbo->unbind();
  this->_timeStamper->stamp("drawCaps");

  glDisable(GL_DEPTH_TEST);
  this->_maskFbo->bind();
  glClear(GL_COLOR_BUFFER_BIT);
  glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);
  glStencilFunc(GL_EQUAL,0,0xff);
  glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
  glDepthFunc(GL_ALWAYS);
  glDepthMask(GL_FALSE);
  this->_blit->use();
  this->_emptyVao->bind();
  glDrawArrays(GL_TRIANGLE_STRIP,0,4);
  this->_emptyVao->unbind();
  this->_maskFbo->unbind();
  glDepthFunc(GL_LESS);
  glDisable(GL_STENCIL_TEST);
  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);

  this->_timeStamper->end("blit");
}

