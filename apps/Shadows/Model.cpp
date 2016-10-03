#include"Model.h"

Model::Model(std::string const&name){
  this->model = aiImportFile(name.c_str(),aiProcess_Triangulate|aiProcess_GenNormals|aiProcess_SortByPType);
  if(this->model==nullptr)
    ge::core::printError(GE_CORE_FCENAME,"Can't open file",name);
}

Model::~Model(){
  assert(this!=nullptr);
  if(this->model)aiReleaseImport(this->model);
}

void Model::getVertices(std::vector<float>&vertices){
  size_t nofVertices = 0;
  for(size_t i=0;i<model->mNumMeshes;++i)
    nofVertices+=model->mMeshes[i]->mNumFaces*3;
  vertices.reserve(nofVertices*3);
  for(size_t i=0;i<model->mNumMeshes;++i){
    auto mesh = model->mMeshes[i];
    for(size_t j=0;j<mesh->mNumFaces;++j)
      for(size_t k=0;k<3;++k)
        for(size_t l=0;l<3;++l)
          vertices.push_back(mesh->mVertices[mesh->mFaces[j].mIndices[k]][l]);
  }
}

RenderModel::RenderModel(std::shared_ptr<Model>const&mdl){
  assert(this!=nullptr);
  if(mdl==nullptr)
    ge::core::printError(GE_CORE_FCENAME,"mdl is nullptr!");

  this->nofVertices = 0;
  auto model = mdl->model;
  for(size_t i=0;i<model->mNumMeshes;++i)
    this->nofVertices+=model->mMeshes[i]->mNumFaces*3;

  std::vector<float>vertData;
  mdl->getVertices(vertData);
  this->vertices = std::make_shared<ge::gl::Buffer>(this->nofVertices*sizeof(float)*3,vertData.data());

  std::vector<float>normData;
  normData.reserve(this->nofVertices*3);
  for(size_t i=0;i<model->mNumMeshes;++i){
    auto mesh = model->mMeshes[i];
    for(size_t j=0;j<mesh->mNumFaces;++j)
      for(size_t k=0;k<3;++k)
        for(size_t l=0;l<3;++l)
          normData.push_back(mesh->mNormals[mesh->mFaces[j].mIndices[k]][l]);
  }
  this->normals = std::make_shared<ge::gl::Buffer>(this->nofVertices*sizeof(float)*3,normData.data());

  this->vao = std::make_shared<ge::gl::VertexArray>();
  this->vao->addAttrib(this->vertices,0,3,GL_FLOAT);
  this->vao->addAttrib(this->normals,1,3,GL_FLOAT);

  const std::string vertSrc = R".(
#version 450
uniform mat4 projectionView = mat4(1);

layout(location=0)in vec3 position;
layout(location=1)in vec3 normal;

out vec3 vPosition;
out vec3 vNormal;

void main(){
  gl_Position = projectionView*vec4(position,1);
  vPosition = position;
  vNormal   = normal;
}).";
  const std::string fragSrc = R".(
#version 450
layout(location=0)out uvec4 fColor;
layout(location=1)out vec4  fPosition;
layout(location=2)out vec4  fNormal; 

in vec3 vPosition;
in vec3 vNormal;

void main(){
  vec3  diffuseColor   = vec3(0.5,0.5,0.5);
  vec3  specularColor  = vec3(1);
  vec3  normal         = vNormal;
  float specularFactor = 1;

  uvec4 color  = uvec4(0);
  color.xyz   += uvec3(diffuseColor  *0xff);
  color.xyz   += uvec3(specularColor *0xff)<<8;
  color.w      = uint (specularFactor*0xff);

  fColor    = color;
  fPosition = vec4(vPosition,1);
  fNormal   = vec4(normal,-dot(vPosition,normal));
}).";
  this->program = std::make_shared<ge::gl::Program>(
      std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER,vertSrc),
      std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER,fragSrc));
}

RenderModel::~RenderModel(){
  assert(this!=nullptr);
}


void RenderModel::draw(glm::mat4 const&projectionView){
  assert(this!=nullptr);
  this->vao->bind();
  this->program->use();
  this->program->setMatrix4fv("projectionView",glm::value_ptr(projectionView));
  this->glDrawArrays(GL_TRIANGLES,0,this->nofVertices);
  this->vao->unbind();
}
