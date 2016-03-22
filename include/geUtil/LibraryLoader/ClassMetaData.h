#pragma once

#include<iostream>
#include<vector>
#include<geCore/TypeRegister.h>

namespace ge{
  namespace util{

    struct ArgMetaData{
      ge::core::TypeRegister::DescriptionList description;
      std::string name;
    };

    struct FceMetaData{
      ge::core::TypeRegister::DescriptionList returnType;
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
