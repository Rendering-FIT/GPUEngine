#pragma once

#include<iostream>
#include<vector>
#include<map>

#include<geUtil/ArgData.h>
#include<geUtil/BaseData.h>
#include<geUtil/ArrayData.h>
#include<geUtil/StructData.h>

namespace ge{
  namespace util{
    class ArgumentManager{
      protected:
        std::vector<std::string>_arguments;
        std::map<std::string,ArgData*>_data;
        std::string _getFullName(std::string prefix,std::string name);
        void _tokenize(std::vector<std::string>&args,std::string src);
        void _loadArgs(std::vector<std::string>&args,std::string file);
        bool _toFloat (float&data,std::string input);
        bool _toInt   (int&  data,std::string input);
        void _parse   (std::vector<std::string>&args,std::string prefix);
        bool    _START      (std::vector<std::string>&args,unsigned&pos,std::string prefix);
        ArgData*_VALUE      (std::vector<std::string>&args,unsigned&pos);
        ArgData*_SAME_VALUES(std::vector<std::string>&args,unsigned&pos);
        ArgData*_VALUES     (std::vector<std::string>&args,unsigned&pos);
        ArgData*_FLOAT      (std::vector<std::string>&args,unsigned&pos);
        ArgData*_INT        (std::vector<std::string>&args,unsigned&pos);
        ArgData*_STRING     (std::vector<std::string>&args,unsigned&pos);
        ArgData*_ARRAY      (std::vector<std::string>&args,unsigned&pos);
        ArgData*_STRUCT     (std::vector<std::string>&args,unsigned&pos);
      public:
        typedef std::map<std::string,ArgData*>::iterator Iterator;
        ArgumentManager(int nofArguments,char*arguments[]);
        ~ArgumentManager();
        Iterator begin();
        Iterator end  ();
        std::string toStr();
    };
  }
}

