#ifndef GE_EX_MATERIAL_H
#define GE_EX_MATERIAL_H

#include <glm/glm.hpp>
#include <string>
#include <map>


struct Material {
   std::string name;
   glm::vec3 ambientColor;  // Ka
   glm::vec3 diffuseColor;  // Kd
   glm::vec3 specularColor; // Ks
   float shininess;
   float transparency; // 0 for fully opague, 1 for completely transparent
   std::string ambientTexture;
   std::string diffuseTexture;
   std::string specularTexture;
   std::string shininessTexture;
   std::string alphaTexture;
   std::string bumpMap;
   std::string displacementMap;
   std::string decalMap;
};


void parseMtl(const std::string& fileName,std::map<std::string,Material>& materials);
const Material* defaultMaterial();


#endif /* GE_EX_MATERIAL_H */
