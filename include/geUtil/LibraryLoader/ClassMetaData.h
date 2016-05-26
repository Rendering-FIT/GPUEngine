#pragma once

#include<iostream>
#include<vector>
#include<geDE/TypeRegister.h>

namespace ge{
  namespace util{

    struct ArgMetaData{
      de::TypeRegister::DescriptionVector description;
      std::string name;
    };

    struct FceMetaData{
      de::TypeRegister::DescriptionVector returnType;
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
