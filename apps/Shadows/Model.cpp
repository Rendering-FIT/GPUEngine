#include"Model.h"

#include <FreeImage.h>
#include <experimental/filesystem>

Model::Model(std::string const&name){
  this->model = aiImportFile(name.c_str(),aiProcess_Triangulate|aiProcess_GenNormals|aiProcess_SortByPType|aiProcess_GenUVCoords|aiProcess_RemoveRedundantMaterials);
  if (this->model == nullptr)
	  ge::core::printError(GE_CORE_FCENAME, "Can't open file", name);
  else
  {
	  std::experimental::filesystem::path p = name;
	  modelFilename = p.filename().string();
	  modelDirectory = p.remove_filename().string();

#ifdef _WIN32
	  const std::string separator = "\\";
#else
	  const std::string separator = "/";
#endif

	  if (!modelDirectory.empty())
		  modelDirectory += separator;
  }
}

Model::~Model(){
  assert(this!=nullptr);
  if(this->model)aiReleaseImport(this->model);
}

void Model::getVertices(std::vector<float>&vertices) const 
{
  size_t nofVertices = 0;
  for(size_t i=0;i<model->mNumMeshes;++i)
    nofVertices+=model->mMeshes[i]->mNumFaces*3;
  vertices.reserve(nofVertices*3);
  for(size_t i=0;i<model->mNumMeshes;++i){
    auto mesh = model->mMeshes[i];
    for(size_t j=0;j<mesh->mNumFaces;++j)
      for(size_t k=0;k<3;++k)
        for(size_t l=0;l<3;++l)
          vertices.push_back(mesh->mVertices[mesh->mFaces[(uint32_t)j].mIndices[(uint32_t)k]][(uint32_t)l]);
  }
}

void Model::getNormals(std::vector<float>& normals) const
{
	for (size_t i = 0; i < model->mNumMeshes; ++i)
	{
		auto mesh = model->mMeshes[i];

		for (uint32_t j = 0; j < mesh->mNumFaces; ++j)
			for (uint32_t k = 0; k < 3; ++k)
			{
				for (uint32_t l = 0; l < 3; ++l)
					normals.push_back(mesh->mNormals[mesh->mFaces[j].mIndices[k]][l]);
#ifdef USE_FULL_SHADING
				float materialIndexEncoded = *((float*)(&mesh->mMaterialIndex));
				normals.push_back(materialIndexEncoded);
#endif
			}
	}
}

void Model::getTcoords(std::vector<float>& tcoords) const
{
	for (size_t i = 0; i < model->mNumMeshes; ++i)
	{
		auto mesh = model->mMeshes[i];

		const bool hasTcoords = mesh->HasTextureCoords(0);

		for (uint32_t j = 0; j < mesh->mNumFaces; ++j)
			for (uint32_t k = 0; k < 3; ++k)
				for (uint32_t l = 0; l < 2; ++l)
					if (hasTcoords)
						tcoords.push_back(mesh->mTextureCoords[0][mesh->mFaces[j].mIndices[k]][l]);
					else
						tcoords.push_back(0.0f);
	}
}

#ifdef USE_FULL_SHADING
void Model::getMaterialsTextures(std::vector<Material>& materials, std::vector<Texture>& textures)
{
	const uint32_t numMaterials = model->mNumMaterials;
	materials.resize(numMaterials);

	std::vector<std::string> texPaths;

	for(uint32_t i = 0; i<numMaterials; ++i)
	{
		aiColor3D color;
		float value;
		const aiMaterial* mat = model->mMaterials[i];

		mat->Get(AI_MATKEY_COLOR_AMBIENT, color);
		materials[i].ambientColor = glm::vec4(color.r, color.g, color.b, 1);

		mat->Get(AI_MATKEY_COLOR_DIFFUSE, color);
		mat->Get(AI_MATKEY_OPACITY, value);
		materials[i].diffuseColor = glm::vec4(color.r, color.g, color.b, value);

		mat->Get(AI_MATKEY_COLOR_SPECULAR, color);
		materials[i].specularColor = glm::vec4(color.r, color.g, color.b, 1);

		mat->Get(AI_MATKEY_SHININESS, value);
		materials[i].shininess = value;

		materials[i].textureIndex = -1;

		aiString tp;
		std::string texPath;
		mat->GetTexture(aiTextureType_DIFFUSE, 0, &tp);
		texPath = tp.C_Str();

		if(texPath !="")
		{
			//Find if texture is already in atlas
			const auto numTex = texPaths.size();

			for(auto j = 0; j<numTex; ++j)
			{
				if(texPaths[j]==texPath)
				{
					materials[i].textureIndex = j;
					break;
				}
			}

			if(materials[i].textureIndex < 0)
			{
				materials[i].textureIndex = int32_t(texPaths.size());
				texPaths.push_back(texPath);
			}
		}
		
	}

	_loadTextures(texPaths, textures);

}

void Model::_loadTextures(const std::vector<std::string>& texNames, std::vector<Texture>& textures)
{
	textures.resize(texNames.size());
	
	for(auto i = 0; i<texNames.size(); ++i)
	{
		const std::string fullPath = modelDirectory + texNames[i];

		FREE_IMAGE_FORMAT format = FreeImage_GetFileType(fullPath.c_str(), 0);

		if (format == -1)
		{
			ge::core::printError(GE_CORE_FCENAME, "Can't open or process texture: ", fullPath);
			exit(-1);
		}

		if (format == FIF_UNKNOWN)
		{
			format = FreeImage_GetFIFFromFilename(fullPath.c_str());

			if (!FreeImage_FIFSupportsReading(format))
			{
				ge::core::printError(GE_CORE_FCENAME, "Detected image format that cannot be read!");
				exit(-1);
			}
		}

		FIBITMAP* bitmap = FreeImage_Load(format, fullPath.c_str());
		const int bitsPerPixel = FreeImage_GetBPP(bitmap);

		FIBITMAP* bitmap32;
		if (bitsPerPixel == 32)
			bitmap32 = bitmap;
		else
			bitmap32 = FreeImage_ConvertTo32Bits(bitmap);

		Texture& t = textures[i];
		t.height = FreeImage_GetHeight(bitmap32);
		t.width = FreeImage_GetWidth(bitmap32);
		t.data = new unsigned char[4 * t.width * t.height];

		memcpy(t.data, FreeImage_GetBits(bitmap32), 4 * t.width * t.height);

		FreeImage_Unload(bitmap32);
		if (bitsPerPixel != 32)
			FreeImage_Unload(bitmap);
	}
}
#endif

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
  mdl->getNormals(normData);
 
  this->normals = std::make_shared<ge::gl::Buffer>(this->nofVertices*sizeof(float)*NUM_NORMAL_COMPONENTS,normData.data());

#ifdef USE_FULL_SHADING
  std::vector<float>tc;
  mdl->getTcoords(tc);
  tcoords = std::make_shared<ge::gl::Buffer>(this->nofVertices * sizeof(float) * 2, tc.data());

  std::vector<Material>mats;
  std::vector<Texture>textures;
  mdl->getMaterialsTextures(mats, textures);

  materials = std::make_shared<ge::gl::Buffer>(mats.size() * sizeof(Material), mats.data());

  //Loading textures
  const auto numTextures = textures.size();

  sampler = std::make_shared<ge::gl::Sampler>();
  sampler->setMinFilter(GL_LINEAR_MIPMAP_LINEAR);
  sampler->setMagFilter(GL_LINEAR);

  textureHandlesBuffer = std::make_shared<ge::gl::Buffer>(numTextures * sizeof(uint64_t), nullptr, GL_STATIC_READ);

  if (numTextures)
  {
  	  for (const auto& tex : textures)
	  {
		  err = glGetError();
  	  	  std::shared_ptr<ge::gl::Texture> t = std::make_shared<ge::gl::Texture>(GL_TEXTURE_2D, GL_RGBA8, 1, tex.width, tex.height);
		  err = glGetError();
		  t->setData2D(tex.data, GL_BGRA, GL_UNSIGNED_BYTE, 0, GL_TEXTURE_2D, 0, 0, tex.width, tex.height);
		  err = glGetError();
  	  	  t->generateMipmap();
		  err = glGetError();

		  texObjects.push_back(t);

		  const auto handle = t->getId();
		  const uint64_t handle64 = glGetTextureSamplerHandleARB(handle, sampler->getId());
		  err = glGetError();
  	  	  glMakeTextureHandleResidentARB(handle64);
		  err = glGetError();
		  textureHandles.push_back(handle64);
	  }

	  textureHandlesBuffer->setData(textureHandles.data(), numTextures * sizeof(uint64_t), 0);
  }
#endif

/*
  {
    std::vector<float>ver;
    for(size_t i=0;i<model->mNumMeshes;++i){
      auto mesh = model->mMeshes[i];
      for(size_t j=0;j<mesh->mNumVertices;++j){
        for(size_t k=0;k<3;++k)
          ver.push_back(mesh->mVertices[j][k]);
        for(size_t k=0;k<3;++k)
          ver.push_back(mesh->mNormals[j][k]);
      }
    }
    std::vector<uint32_t>ind;
    uint32_t offset=0;
    for(size_t i=0;i<model->mNumMeshes;++i){
      auto mesh = model->mMeshes[i];
      for(size_t j=0;j<mesh->mNumFaces;++j)
        for(size_t k=0;k<3;++k)
          ind.push_back(offset+mesh->mFaces[j].mIndices[k]);
      offset+=mesh->mNumFaces*3;
    }
    this->indexVertices = std::make_shared<ge::gl::Buffer>(ver.size()*sizeof(float),ver.data());
    this->indices = std::make_shared<ge::gl::Buffer>(ind.size()*sizeof(uint32_t),ind.data());
    this->vao = std::make_shared<ge::gl::VertexArray>();
    this->vao->addAttrib(this->indexVertices,0,3,GL_FLOAT,sizeof(float)*6,0);
    this->vao->addAttrib(this->indexVertices,1,3,GL_FLOAT,sizeof(float)*6,sizeof(float)*3);
    this->vao->addElementBuffer(this->indices);
    this->nofVertices = ind.size();
  }
*/
  //*
  this->vao = std::make_shared<ge::gl::VertexArray>();
  this->vao->addAttrib(this->vertices,0,3,GL_FLOAT);
  this->vao->addAttrib(this->normals,1,NUM_NORMAL_COMPONENTS,GL_FLOAT);
#ifdef USE_FULL_SHADING
  this->vao->addAttrib(this->tcoords, 2, 2, GL_FLOAT);
#endif
  // */
#ifdef USE_FULL_SHADING
  const std::string vertSrc = R".(
#version 450
uniform mat4 projectionView = mat4(1);

layout(location=0)in vec3 position;
layout(location=1)in vec4 normal;
layout(location=2)in vec2 tcoords;

out vec3 vPosition;
out vec3 vNormal;
out vec2 vTexCoords;
out flat uint materialIndex;

void main()
{
    gl_Position = projectionView*vec4(position,1);
    vPosition = position;
    vNormal   = normal.xyz;
	vTexCoords = tcoords;
    materialIndex = floatBitsToInt(normal.w);
}).";

  const std::string fragSrc = R".(
#version 450
#extension GL_ARB_bindless_texture : require
#extension GL_ARB_gpu_shader_int64 : enable
#extension GL_AMD_gpu_shader_int64 : enable

layout(location=0)out uvec4 fColor;
layout(location=1)out vec4  fPosition;
layout(location=2)out vec4  fNormal; 

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexCoords;
in flat uint materialIndex;

layout(std430,binding=0) readonly buffer textureSSBO
{
    uint64_t texHandles[];
};

struct Material
{
	vec4 ambientColor;
	vec4 diffuseColor;
	vec4 specularColor;
	int  textureIndex;
	float shininess;
	float dummy1;
	float dummy2;
};

layout(std430,binding=1) readonly buffer materialSSBO
{
    Material materials[];
};

void main()
{
	Material mat = materials[materialIndex];
	vec3 diffuse = mat.diffuseColor.xyz;
	if(mat.textureIndex>=0)
	{
#ifdef GL_ARB_gpu_shader_int64
		sampler2D s = sampler2D(texHandles[mat.textureIndex]);
#else
		sampler2D s = sampler2D(unpackUint2x32(texHandles[mat.textureIndex]));
#endif
		diffuse *= texture(s, vTexCoords).xyz;
	}
	uvec4 color  = uvec4(0);
    color.xyz   += uvec3(diffuse.xyz  *0xff);
	color.xyz   += uvec3(mat.specularColor.xyz *0xff)<<8;
	color.w      = uint (mat.shininess*0xff);
	
	fColor    = color;
	fPosition = vec4(vPosition,1);
    fNormal   = vec4(vNormal,-dot(vPosition,vNormal));
}).";
#else
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
#endif
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
#ifdef USE_FULL_SHADING
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, textureHandlesBuffer->getId());
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, materials->getId());
#endif
  //this->glDrawElements(GL_TRIANGLES,this->nofVertices,GL_UNSIGNED_INT,nullptr);
  this->glDrawArrays(GL_TRIANGLES,0,this->nofVertices);
  this->vao->unbind();

#ifdef USE_FULL_SHADING
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, 0);
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, 0);
#endif
}
