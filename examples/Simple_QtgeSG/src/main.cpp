
#include <SimplegeSGRenderer.h>

#include <QGuiApplication>
#include <AssimpModelLoader.h>
#include <QtImageLoader.h>

#include <geSG/DefaultImage.h>

#include <QFileInfo>

using namespace std;

/**
 * Simple function that loads images that are found at image components of materials
 * and populate its image property.
 * 
 * \warning Assumes relative texture file paths or empty imageDir. There should be an extended check
 *          in production code. 
 */
void loadImages(ge::sg::Scene* scene, std::string& imageDir)
{
   std::shared_ptr<ge::sg::DefaultImage> defaultImage(make_shared<ge::sg::DefaultImage>());

   for(auto model : scene->models)
   {
      for(std::shared_ptr<ge::sg::Material> material : model->materials)
      {
         for(std::vector<std::shared_ptr<ge::sg::MaterialComponent>>::iterator it = material->materialComponents.begin(); it != material->materialComponents.end(); ++it)
         {
            if((*it)->getType() == ge::sg::MaterialComponent::ComponentType::IMAGE)
            {
               ge::sg::MaterialImageComponent *img = dynamic_cast<ge::sg::MaterialImageComponent*>((*it).get());
               //cout << img->semantic << " " << img->filePath << endl;
               std::string textFile(imageDir + img->filePath);
               std::shared_ptr<QtImage> image(QtImageLoader::loadImage(textFile.c_str()));
               if(image == nullptr)
               {
                  cout << "  " << "FAILED TO LOAD!" << "substituting default image\n";
                  img->image = defaultImage;
               }
               else {
                  img->image = image;
               }
            }
         }
      }
   }
}

int main(int argc, char** argv)
{
   QGuiApplication app(argc, argv);

   QQuickWindow qw;
   qw.resize(800, 600);
   fsg::SimplegeSGRenderer basicRenderer(&qw);


   //model loading
   QString modelFileName(APP_RESOURCES"/models/texCube/texCube.obj");
   QFileInfo fi(modelFileName);
   string modelPath(qUtf8Printable(fi.canonicalPath() + "/"));

   std::shared_ptr<ge::sg::Scene> scene(AssimpModelLoader::loadScene(modelFileName.toUtf8().constData()));
   if(!scene)
   {
      cerr << "Failed to load scene!" << endl;      
   }
   basicRenderer.setScene(scene);

   //load Images
   loadImages(scene.get(), modelPath);


   qw.show();

   return app.exec();
}