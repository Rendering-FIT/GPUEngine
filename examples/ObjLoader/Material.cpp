#include <fstream>
#include <sstream>
#include "Material.h"

#include <iostream>
using namespace std;


void parseMtl(const string& fileName,map<string,Material>& materials)
{
   if(fileName.empty())
      return;

   // open file
   ifstream f(fileName);
   if(!f) {
      cout<<"Failed to open file \""<<fileName<<"\"."<<endl;
      return;
   }

   // initialize variables
   stringstream line;
   string lineBuf;
   string token;
   f.imbue(locale("en_US.UTF-8"));
   line.imbue(locale("en_US.UTF-8"));
   Material dummy;
   Material *m=&dummy;
   float r,g,b;
   bool usingDissolve;

   // parsing loop
   while(true)
   {
      // read line
      getline(f,lineBuf);
      if(!f) break;
      line.clear();
      line.str(lineBuf);

      line>>token;
      if(!line) continue;
      const char *s=token.c_str();

      switch(s[0]) {

         case '\0':
         case '#':
            // ignore empty lines and comment lines
            continue;

         case 'n':
            if(token=="newmtl") {
               string name;
               line>>name;
               m=&materials[name];
               m->name=name;
               usingDissolve=false;
            }
            else
               cout<<"Unknown line content \""<<lineBuf<<"\"\n"<<endl;
            continue;

         case 'K':
            if(token.length()==1)
               break;
            line>>r>>g>>b;
            switch(s[1]) {
               case 'a': m->ambientColor=glm::vec3(r,g,b); continue;
               case 'd': m->diffuseColor=glm::vec3(r,g,b); continue;
               case 's': m->specularColor=glm::vec3(r,g,b); continue;
            }
            cout<<"Unknown line content \""<<lineBuf<<"\"\n"<<endl;
            continue;

         case 'T':
            //
            // Tr - transparency
            //
            // Seems that the world did not agreed about the specification of the item.
            //
            // Some thinks that value of 1 means opaque material and 0 transparent material,
            // such as http://people.sc.fsu.edu/~jburkardt/data/mtl/mtl.html .
            //
            // However, 3ds Max export uses the opposite: 0 means opaque material and
            // 1 completely transparent material. These 3ds Max exported files
            // carry the following signature as the first line in the file (*.obj, *.mtl):
            // # 3ds Max Wavefront OBJ Exporter v0.97b - (c)2007 guruware
            //
            // Moreover, at least one model uses Tr followed by two numbers.
            // Such model can be downloaded from http://graphics.cs.williams.edu/data/meshes/cube.zip
            // (part of the following collection: http://graphics.cs.williams.edu/data/meshes.xml).
            //
            // Current solution: As we do not know what is the correct interpretation of
            // the value 0 and value 1 for Tr, we will rely on d (dissolve) parameter instead
            // whenever it is present. This seems to fix the problem on large number of models.
            //
            if(token=="Tr") {
               if(!usingDissolve) {
                  float t;
                  line>>t;
                  m->transparency=1.f-t;
               }
               continue;
            }
            cout<<"Unknown line content \""<<lineBuf<<"\"\n"<<endl;
            continue;

         case 'd':
            //
            // d - dissolve (pseudo-transparency)
            //
            // Dissolve of value 1 means completely opaque material
            // and value of 0 results in completely transparent material.
            //
            // To be compatible with 3D Max obj exporter,
            // d takes precedence over Tr (handled through usingDissolve variable).
            //
            if(s[1]=='\0') {
               usingDissolve=true;
               float d;
               line>>d;
               m->transparency=1.f-d;
               continue;
            }

            if(token=="disp") {
               string name;
               line>>name;
               m->displacementMap=name;
               continue;
            }
            if(token=="decal") {
               string name;
               line>>name;
               m->decalMap=name;
               continue;
            }
            cout<<"Unknown line content \""<<lineBuf<<"\"\n"<<endl;
            break;

         case 'm': {
            string name;
            line>>name;
            if(token=="map_Ka")  m->ambientTexture=name; continue;
            if(token=="map_Kd")  m->diffuseTexture=name; continue;
            if(token=="map_Ks")  m->specularTexture=name; continue;
            if(token=="map_Ns")  m->shininessTexture=name; continue;
            if(token=="map_d")   m->alphaTexture=name; continue;
            if(token=="map_bump")  m->bumpMap=name; continue;
            cout<<"Unknown line content \""<<lineBuf<<"\"\n"<<endl;
            continue;
         }

         case 'b':
            if(token=="bump") {
               string name;
               line>>name;
               m->bumpMap=name;
               continue;
            }
            cout<<"Unknown line content \""<<lineBuf<<"\"\n"<<endl;
            continue;

         default:
            cout<<"Unknown line content \""<<lineBuf<<"\"\n"<<endl;
            continue;
      }
   }

}
