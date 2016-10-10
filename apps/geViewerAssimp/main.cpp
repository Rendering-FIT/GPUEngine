//#pragma warning(disable:4251) //class needs to have dll-interface to be used by clients of class  --glbinding
//#pragma warning(disable:4996) //This function or variable may be unsafe. Consider using strtok_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.

#include <iostream>
#include <numeric>
#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <assimp/postprocess.h>

#include <geSG/AnimationManager.h>
#include <geSG/AttributeDescriptor.h>
#include <geSG/Material.h>
#include <geSG/Model.h>
#include <geUtil/ArgumentObject.h>

#include "AssimpModelLoader.h"
#include "BVHGenerator.h"
#include "CameraManipulator.h"
#include "DefaultImage.h"
#include "ForrysVisualizationTechniques.h"
#include "FreeImageImageLoader.h"
#include "InputController.h"
#include "NFPlaneAdjustor.h"
#include "ste/DAG.h"
#include <geGL/geGL.h>

//#include "Renderer.h"

//#include <FreeImagePlus.h>

/*#include <ForrysAnimationTechnique.h>
#include <ForrysNormalMappingTechnique.h>
#include <ForryEnvironmentMappingTechnique.h>
#include <geUtil/macros.h>*/

/*#include <geSG/Animation.h>
#include <geSG/AnimationChannel.h>
#include <geSG/AnimationKeyFrame.h>

#include <geGL/OpenGLCommands.h>

#include <geGL/ProgramObject.h>

#include <geCore/EnumRegister.h>
#include <CubeMapTexture.h>
#include <EnumToGL.h>
#include <SkyBoxVT.h>*/

using namespace std;


#if defined(_WIN32)
static const char directoryNativeSeparator='\\';
static const char directoryNonNativeSeparator='/';
#else
static const char directoryNativeSeparator='/';
static const char directoryNonNativeSeparator='\\';
#endif


string getFilePath(const string& filename)
{
   return filename.substr(0,filename.find_last_of(directoryNativeSeparator));
}


string convertFileNameToNativeStyle(const string& filename)
{
   string s;
   s.reserve(filename.size());
   for(auto it : filename)
      s.push_back((it==directoryNonNativeSeparator)?directoryNativeSeparator:it);
   return s;
}


void loadImages(const ge::sg::Model* model, const char* imageDir)
{
   std::shared_ptr<fsg::DefaultImage> defaultImage(std::make_shared<fsg::DefaultImage>());
   std::string dir(imageDir);
   if (dir[dir.length()-1] != '\\' || dir[dir.length()-1] != '/')
   {
      dir += '/';
   }
   for(std::shared_ptr<ge::sg::Material> material : model->materials)
   {
      for(std::vector<std::shared_ptr<ge::sg::MaterialComponent>>::iterator it = material->materialComponents.begin(); it != material->materialComponents.end(); ++it)
      {
         if((*it)->getType() == ge::sg::MaterialComponent::ComponentType::IMAGE)
         {
            ge::sg::MaterialImageComponent *img = dynamic_cast<ge::sg::MaterialImageComponent*>((*it).get());
            std::string textureFileName(dir + convertFileNameToNativeStyle(img->filePath));
            std::shared_ptr<FreeImageImage> image(FreeImageImageLoader::loadImage(textureFileName.c_str()));
            if(image == nullptr)
            {
               cout << "  " << "Texture failed to load: " << textureFileName << endl;
               img->image = defaultImage;
            }
            else{
               cout << "  " << "Texture loaded: " << textureFileName << ", semantic: " << ge::sg::MaterialImageComponent::semanticRegister.getName(img->semantic) << endl;
               img->image = image;
            }
         }
      }
   }
}


int main(int argc, char** argv)
{
   AssimpModelLoader::registerSemantics();

   ge::util::ArgumentObject args(argc,argv);

   // file name
   string filename;
   if(argc>1)
   {
      int i=argc-1;
      if(argv[i][0]!='-')
         if(argc==2 || argv[i-1][0]!='-')  filename=argv[1];
   }

   shared_ptr<ge::sg::Scene> scene;
   ge::sg::AnimationManager animationManager;
   if(!filename.empty()) {

      // load scene
      scene=shared_ptr<ge::sg::Scene>(AssimpModelLoader::loadScene(filename.c_str(),
            aiProcess_Triangulate|aiProcess_SortByPType|aiProcess_CalcTangentSpace));
      if(!scene)
         cout<<"Scene loading failed on file: "<<filename<<endl;

      // load images
      if(scene && scene->models.size()>0) {
         ge::sg::Model* model=scene->models[0].get();
         if(model)
            loadImages(model,getFilePath(filename).c_str());
      }

      // load animations
      if(scene && scene->animations.size()>0) {
         if(scene->animations[0]) {
            animationManager.playAnimation(scene->animations[0]);
         }
      }
   }


   std::shared_ptr<ge::sg::MatrixTransformNode> rootNode(std::make_shared<ge::sg::MatrixTransformNode>(std::make_shared<ge::sg::MatrixTransform>()));
   if(scene && scene->models.size()>0 && scene->models[0]->rootNode)
      rootNode->children.push_back(scene->models[0]->rootNode);

   /*std::shared_ptr<ge::sg::MatrixTransformNode> box2Node(std::make_shared<ge::sg::MatrixTransformNode>(std::make_shared<ge::sg::MatrixTransform>()));
   *(box2Node->data->getMatrix()) = glm::translate(*(box2Node->data->getMatrix()),glm::vec3(5,0,0));
   box2Node->children.push_back(model->rootNode);

   rootNode->children.push_back(box2Node);*/

   ///////////////////////////////////////////////////////////////////////////
   // BVH generator test

   std::shared_ptr<ge::util::BVHGenerator::BSMTNode> BVH = ge::util::BVHGenerator::generateBoundingSpheresHierarchy(rootNode);

   //////////////////////////////////////////////////////////////////////////
   // Prepare geGL scene



   if (!glfwInit())
   {
      cerr << "GLFW init failed" << endl;
      return -1;
   }

   int screenWidth = 640;
   int screenHeight = 480;

   GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "geViewerAssimp", nullptr, nullptr);

   glfwMakeContextCurrent(window);
   //glewExperimental = GL_TRUE;
   glewInit();
   glGetError();


   //cubeMap1->initTextureObject();
   //////////////////////////////////////////////////////////////////////////
   // Matrices
   float fovy = glm::pi<float>() / 4.0f; // 45 degrees
   shared_ptr<glm::mat4> perspectiveMat(make_shared<glm::mat4>());
   *perspectiveMat = glm::perspective(fovy, (float)(screenWidth)/screenHeight,1.0f,1000.0f);

   shared_ptr<glm::mat4> viewMatrix(make_shared<glm::mat4>());


   //////////////////////////////////////////////////////////////////////////
   // Program assembly
   ge::gl::init();
   ge::gl::initShadersAndPrograms();
   std::shared_ptr<ge::gl::ProgramObject> simplifiedPhongProgram=std::make_shared<ge::gl::ProgramObject>(
      GL_VERTEX_SHADER,
      "#version 430 compatibility\n"
      "\n"
      "layout(location=0) in vec3 pos;\n"
      "layout(location=1) in vec3 norm;\n"
      "layout(location=2) in vec2 tex;\n"
      "\n"
      "uniform mat4 projection;\n"
      "uniform mat4 model;\n"
      "uniform mat4 normalMatrix;\n"
      "uniform mat4 viewMatrix;\n"
      "\n"
      "out perVertex\n"
      "{\n"
      "   vec3 normal;\n"
      "   vec3 viewvec;\n"
      "   vec2 texcoord;\n"
      "} perVertex_out;\n"
      "\n"
      "void main(){\n"
      "   perVertex_out.normal = normalize((normalMatrix * vec4(norm, 0)).xyz);\n"
      "   perVertex_out.texcoord = tex;\n"
      "   gl_Position = projection * viewMatrix * model * gl_Vertex;\n"
      "   perVertex_out.viewvec = vec3(model * gl_Vertex);\n"
      "}",
      GL_FRAGMENT_SHADER,
      "#version 430 compatibility\n"
      "\n"
      "layout(location=0)out vec4 fragColor;\n"
      "\n"
      "layout(binding=0) uniform sampler2D dif_tex;\n"
      "\n"
      "uniform vec4 ambientMat;\n"
      "uniform vec4 diffuseMat;\n"
      "uniform vec4 specularMat;\n"
      "uniform float shininessMat;\n"
      "\n"
      "uniform vec4 lightPos;\n"
      "uniform vec4 lightCol;\n"
      "\n"
      "in perVertex\n"
      "{\n"
      "   vec3 normal;\n"
      "   vec3 viewvec;\n"
      "   vec2 texcoord;\n"
      "} perVertex_in;\n"
      "\n"
      "void main()\n"
      "{\n"
      "   //phong\n"
      "   vec4 ambient = ambientMat;\n"
      "   vec3 normal = normalize(perVertex_in.normal);\n"
      "   vec3 viewvec = normalize(perVertex_in.viewvec);\n"
      "   vec3 lightvec = normalize(lightPos.xyz - perVertex_in.viewvec);\n"
      "   vec4 diffuse = texture(dif_tex,perVertex_in.texcoord) * diffuseMat * lightCol * max(0,dot(normal, lightPos.xyz));\n"
      "   vec4 specular;\n"
      "   specular = lightCol * pow(max(dot(reflect(-lightvec, normal), -viewvec), 0.0), shininessMat);\n"
      "\n"
      "   fragColor = ambient + diffuse + specular;\n"
      "}");

/*   const std::string shaderDir = "F:/grafika/AssetLoader/src/shaders";
   std::shared_ptr<ge::gl::ShaderObject>simple_vs(new ge::gl::ShaderObject(shaderDir + "/texture_material_vs.glsl", GL_VERTEX_SHADER));
   std::shared_ptr<ge::gl::ShaderObject>simple_fs(new ge::gl::ShaderObject(shaderDir + "/texture_material_fs.glsl", GL_FRAGMENT_SHADER));

   std::shared_ptr<ge::gl::ShaderObject>normal_vs(new ge::gl::ShaderObject(shaderDir + "/texture_normal_vs.glsl", GL_VERTEX_SHADER));
   std::shared_ptr<ge::gl::ShaderObject>normal_fs(new ge::gl::ShaderObject(shaderDir + "/texture_normal_fs.glsl", GL_FRAGMENT_SHADER));

   std::shared_ptr<ge::gl::ShaderObject>sky_vs(new ge::gl::ShaderObject(shaderDir + "/sky_box_vs.glsl", GL_VERTEX_SHADER));
   std::shared_ptr<ge::gl::ShaderObject>sky_gs(new ge::gl::ShaderObject(shaderDir + "/full_screen_quad_gs.glsl", GL_GEOMETRY_SHADER));
   std::shared_ptr<ge::gl::ShaderObject>sky_fs(new ge::gl::ShaderObject(shaderDir + "/skybox_dorm_fs.glsl", GL_FRAGMENT_SHADER));

   std::shared_ptr<ge::gl::ShaderObject>env_fs(new ge::gl::ShaderObject(shaderDir + "/environment_fs.glsl", GL_FRAGMENT_SHADER));
*/

//   std::shared_ptr<ge::gl::ProgramObject> simpleProgram(std::make_shared<ge::gl::ProgramObject>(simple_vs,simple_fs));
//   std::shared_ptr<ge::gl::ProgramObject> normalProgram(std::make_shared<ge::gl::ProgramObject>(normal_vs, normal_fs));
//   std::shared_ptr<ge::gl::ProgramObject> skyProgram(std::make_shared<ge::gl::ProgramObject>( sky_vs, sky_gs, sky_fs));
//   std::shared_ptr<ge::gl::ProgramObject> envProgram(std::make_shared<ge::gl::ProgramObject>( simple_vs, env_fs));

   std::shared_ptr<fsg::UniformMatrixGLMShared> perspMatU(std::make_shared<fsg::UniformMatrixGLMShared>(simplifiedPhongProgram->getUniform("projection").getLocation(), 1, GL_FALSE, perspectiveMat));


   fsg::ForryPhongTechnique fpt(rootNode,simplifiedPhongProgram);
   fpt.process();
   fpt.getViewMatrixRef() = viewMatrix;

   /*fsg::SkyBoxVT skyboxVT;
   skyboxVT.cubeMap = cubeMap1;
   skyboxVT.program = skyProgram;
   skyboxVT.viewMatrix = viewMatrix;
   skyboxVT.projectionMatrix = perspectiveMat;
   skyboxVT.winSize = glm::vec2(screenWidth, screenHeight);*/

/*   fsg::ForryEnvironmentMappingTechnique fet;
   fet.setInput(scene);
   fet.phongProgram = envProgram;
   fet.initMatrixUniforms();
   fet.environmentMap = cubeMap1->textureObject;
   fet.prespectiveMatrixUniform->value = perspectiveMat;
   fet.viewMatrixUniform->value = viewMatrix;
   fet.process();*/

   std::shared_ptr<ge::gl::Uniform4f<>> lightPosU(ge::gl::newUniform4f(simplifiedPhongProgram->getUniform("lightPos").getLocation(), -3.f, 3.f, 3.f, 1.f));
   std::shared_ptr<ge::gl::Uniform4f<>> lightColU(ge::gl::newUniform4f(simplifiedPhongProgram->getUniform("lightCol").getLocation(), 1.f, 1.f, 1.f, 1.f));

   //Renderer renderer;
   //GLuint tex;

   ///////////////////////////////////////////////////////////////////////////
   /*std::shared_ptr<FreeImageImage> image(FreeImageImageLoader::loadImage("F:/3D models/darkskies/darkskies_bk.tga"));
   if(image == nullptr)
   {
      cout << "  " << "FAILED TO LOAD!" << "substituting default image\n";
      //img->image = defaultImage;
   }
   std::shared_ptr<ge::gl::TextureObject> texture(std::make_shared<ge::gl::TextureObject>(GL_TEXTURE_CUBE_MAP, GL_RGBA8, 1, image->getWidth(), image->getHeight()));
   glTextureSubImage2DEXT(texture->getId(), GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, 0, 0, image->getWidth(), image->getHeight(), fsg::translateEnum(image->getFormat()), fsg::translateEnum(image->getDataType()), image->getBits());
   //glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA8, image->getWidth(), image->getHeight(), 0, fsg::translateEnum(image->getFormat()), fsg::translateEnum(image->getDataType()), image->getBits());

   */

   //////////////////////////////////////////////////////////////////////////

   shared_ptr<fsg::OrbitObjectManipulator> cam = make_shared<fsg::OrbitObjectManipulator>();

   //link (share) this matrix with viewmatrix in visualization technique
   cam->setRefMatrix(viewMatrix);
   cam->setCenter(BVH->data->MTNode->center);
   cam->setDistance(BVH->data->MTNode->radius*3);
   cam->sensitivityZ = BVH->data->MTNode->radius / 10.0f;
   cam->updateViewMatrix();

   InputController::_cameraManipulator = cam;

   fsg::NFPlaneAdjustor nfAdjustor;
   nfAdjustor.minimumNear = 1.0f;
   nfAdjustor.viewMatrix = cam->getRefMatrix();
   nfAdjustor.bs = (***BVH).MTNode;


   glfwSetMouseButtonCallback(window, InputController::GLFW_MB_callback);
   glfwSetCursorPosCallback(window, InputController::GLFW_MM_callback);
   glfwSetScrollCallback(window, InputController::GLFW_MW_callback);

   std::pair<float, float> near_far{0.1f,1000.0f};

   glEnable(GL_DEPTH_TEST);
   glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
   //cam->updateViewMatrix();

   while(!glfwWindowShouldClose(window))
   {
      glfwMakeContextCurrent(window);

      animationManager.update(ge::core::time_point::clock::now());

      near_far = nfAdjustor.computeNearFar();

      *perspectiveMat = glm::perspective(fovy, (float)(screenWidth) / screenHeight, near_far.first, near_far.second);

      //renderer.frame(0.0);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      /*glDisable(GL_DEPTH_TEST);
      skyboxVT.draw();
      glEnable(GL_DEPTH_TEST);*/

      //normalProgram->use();
      simplifiedPhongProgram->use();
      (*lightPosU)();
      (*lightColU)();
      (*perspMatU)();
      fpt.draw();
      /*fat.draw();*/
      //fet.draw();


      //meshCmdList->apply();
      GLenum err = glGetError();
      if(err != 0)
      {
         cout << "glerr " << err << endl;
      }

      glfwSwapBuffers(window);
      glfwPollEvents();
      if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
         glfwSetWindowShouldClose(window, (int)GL_TRUE);  
      if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
      {
         cam->rotate(-0.1, 0.0);
         cam->updateViewMatrix();
      }
      glfwMakeContextCurrent(NULL);

   }

   glfwMakeContextCurrent(window);
//   delete simpleProgram;
//   delete meshCmdList;

   glfwTerminate();
   return 0;
}
