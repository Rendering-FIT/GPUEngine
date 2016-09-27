#pragma once

#include<iostream>
#include<vector>
#include<geDE/TypeRegister.h>

namespace ge{
  namespace ad{

    struct ArgMetaData{
      de::TypeDescriptionVector description;
      std::string name;
    };

    struct FceMetaData{
      de::TypeDescriptionVector returnType;
      std::string name;
      std::vector<ArgMetaData>args;
    };

    struct ConstructorMetaData{
      std::vector<ArgMetaData>args;
    };


    struct ClassMetaData{
      std::string name;
      std::vector<FceMetaData> fces;
      std::vector<ConstructorMetaData> constructors;
    };

  }
}
