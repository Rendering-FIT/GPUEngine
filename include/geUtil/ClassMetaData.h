#pragma once

#include<iostream>
#include<vector>

namespace ge{
  namespace util{

    struct ArgMetaData{
      std::vector<unsigned>description;
      std::string name;
    };

    struct FceMetaData{
      std::vector<unsigned>returnType;
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
