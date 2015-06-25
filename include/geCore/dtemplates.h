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


    template<unsigned SIZE,typename TYPE>
      void argsToArray(TYPE data[SIZE],TYPE v){
        data[SIZE-1]=v;
      }
    template<unsigned SIZE,typename TYPE,typename... Args>
      inline void argsToArray(TYPE data[SIZE],TYPE v, Args... args){
        data[SIZE-1-sizeof...(args)]=v;
        argsToArray<SIZE,TYPE>(data,args...);
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


    template<unsigned... Is>
      struct seq { };

    template<unsigned N, unsigned... Is>
      struct gen_seq : gen_seq<N - 1, N - 1, Is...> { };

    template<unsigned... Is>
      struct gen_seq<0, Is...> : seq<Is...> { };


    template<typename T>
      constexpr T notequal(const T ref,const T t){
        return ref!=t;
      }

    template<typename T,typename... Args>
      constexpr T notequal(const T ref,const T t,Args... args){
        return ref!=t&&notequal(ref,args...);
      }

    template<typename T,typename... Args>
      constexpr T nonof_rec(const T halt,const T t0,const T t1,Args... args){
        //static_assert(halt!=t0,"there is no space for nonof");
        return halt==t0?0:notequal(t0,t1,args...)?t0:nonof_rec(halt,t0+1,t1,args...);
      }

    template<typename T,typename... Args>
      constexpr T nonof(const T t0,const T t1,Args... args){
        return nonof_rec(t0,t0+1,t1,args...);
      }



    GECORE_EXPORT unsigned getDispatchSize(unsigned workSize,unsigned workGroupSize);
    GECORE_EXPORT unsigned bitCount(unsigned value);
  }
}
