#pragma once

#include<iostream>
#include<vector>
#include<map>

#include<geUtil/Export.h>
#include<geUtil/ArgumentManager/ArgData.h>
#include<geUtil/ArgumentManager/BaseData.h>
#include<geUtil/ArgumentManager/ArrayData.h>
#include<geUtil/ArgumentManager/StructData.h>

namespace ge{
  namespace util{
    class GEUTIL_EXPORT ArgumentManager{
      public:
        using Name2Data = std::map<std::string,ArgData*>;
      protected:
        std::vector<std::string>_arguments;
        Name2Data _data;
        std::string _getFullName(std::string prefix,std::string name);
        void _tokenize(std::vector<std::string>&args,std::string src);
        void _loadArgs(std::vector<std::string>&args,std::string file);
        bool _toBOOL  (bool&              data,std::string input);
        bool _toI8    (char&              data,std::string input);
        bool _toI16   (short&             data,std::string input);
        bool _toI32   (int&               data,std::string input);
        bool _toI64   (long long int&     data,std::string input);
        bool _toU8    (unsigned char&     data,std::string input);
        bool _toU16   (unsigned short&    data,std::string input);
        bool _toU32   (unsigned int&      data,std::string input);
        bool _toU64   (unsigned long long&data,std::string input);
        bool _toF32   (float&data,std::string input);
        bool _toF64   (double&data,std::string input);
        void _parse   (std::vector<std::string>&args,std::string prefix);
        bool    _START      (std::vector<std::string>&args,unsigned&pos,std::string prefix);
        ArgData*_VALUE      (std::vector<std::string>&args,unsigned&pos);
        ArgData*_SAME_VALUES(std::vector<std::string>&args,unsigned&pos);
        ArgData*_VALUES     (std::vector<std::string>&args,unsigned&pos);
        ArgData*_BOOL       (std::vector<std::string>&args,unsigned&pos);
        ArgData*_I8         (std::vector<std::string>&args,unsigned&pos);
        ArgData*_I16        (std::vector<std::string>&args,unsigned&pos);
        ArgData*_I32        (std::vector<std::string>&args,unsigned&pos);
        ArgData*_I64        (std::vector<std::string>&args,unsigned&pos);
        ArgData*_U8         (std::vector<std::string>&args,unsigned&pos);
        ArgData*_U16        (std::vector<std::string>&args,unsigned&pos);
        ArgData*_U32        (std::vector<std::string>&args,unsigned&pos);
        ArgData*_U64        (std::vector<std::string>&args,unsigned&pos);
        ArgData*_F32        (std::vector<std::string>&args,unsigned&pos);
        ArgData*_F64        (std::vector<std::string>&args,unsigned&pos);
        ArgData*_STRING     (std::vector<std::string>&args,unsigned&pos);
        ArgData*_ARRAY      (std::vector<std::string>&args,unsigned&pos);
        ArgData*_STRUCT     (std::vector<std::string>&args,unsigned&pos);
      public:
        using Iterator = Name2Data::iterator;
        using ConstIterator = std::map<std::string,ArgData*>::const_iterator;
        ArgumentManager(int nofArguments,char*arguments[]);
        ~ArgumentManager();
        Iterator begin();
        Iterator end  ();
        ConstIterator begin()const;
        ConstIterator end()const;
        std::string toStr();
    };
  }
}

