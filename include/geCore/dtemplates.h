#pragma once

#include<geCore/Export.h>

#include<iostream>
#include<cstring>
#include<sstream>
#include<vector>
#include<map>

#define DEF_ENUM(name,...)\
  enum name{\
    __VA_ARGS__\
  };\
friend std::ostream& operator<<(std::ostream& os,const name&val){\
  char data[]=#__VA_ARGS__;\
  char*token=std::strtok(data,",");\
  unsigned counter=0;\
  while(counter<unsigned(val)){\
    token=std::strtok(NULL,",");\
    counter++;\
  }\
  os << token;\
  return os;\
}

namespace ge{
  namespace core{
    template<typename T>
      void argsToVector(std::vector<T>&vec,T v){
        vec.push_back(v);
      }

    template<typename T,typename... Args>
      void argsToVector(std::vector<T>&vec,T v,Args... args){
        argsToVector(vec,v);
        argsToVector(vec,args...);
      }


    template<typename TPtr>
      void deleteSetNull(TPtr&b){
        if(b)delete b;b=NULL;
      }

    template<typename TPtr,typename...Args>
      void deleteSetNull(TPtr&b,Args... args){
        deleteSetNull(b);
        deleteSetNull(args...);
      }


    template<typename T>
      void filterArgsToVector(std::vector<T>&data,T t){
        data.push_back(t);
      }

    template<typename T,typename T2>
      void filterArgsToVector(std::vector<T>&,T2){}

    template<typename T,typename T2,typename... Args>
      void filterArgsToVector(std::vector<T>&data,T2,Args... args);

    template<typename T,typename... Args>
      void filterArgsToVector(std::vector<T>&data,T t,Args... args){
        filterArgsToVector(data,t);
        filterArgsToVector(data,args...);
      }

    template<typename T,typename T2,typename... Args>
      void filterArgsToVector(std::vector<T>&data,T2,Args... args){
        filterArgsToVector(data,args...);
      }
    GECORE_EXPORT unsigned getDispatchSize(unsigned workSize,unsigned workGroupSize);  
  }
}
