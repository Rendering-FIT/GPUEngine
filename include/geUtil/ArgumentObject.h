#pragma once

#include<iostream>
#include<vector>
#include<map>

#include <geUtil/Export.h>

namespace ge{
  namespace util{
    GEUTIL_EXPORT float atof(const char*s);
    /**
     * @brief Represents manager of program arguments
     */
    class GEUTIL_EXPORT ArgumentObject{
      public:
        ArgumentObject(
            int  argc  ,
            char*argv[]);
        std::string getArg(
            std::string const&argName     ,
            std::string const&def     = "");
        int getArgi(
            std::string const&argName     ,
            std::string const&def     = "");
        float getArgf(
            std::string const&argName     ,
            std::string const&def     = "");
        bool isPresent(
            std::string const&argName);
        std::string getArg(
            std::string const&start       ,
            std::string const&end         ,
            std::string const&argName     ,
            std::string const&def     = "");
        int getArgi(
            std::string const&start       ,
            std::string const&end         ,
            std::string const&argName     ,
            std::string const&def     = "");
        float getArgf(
            std::string const&start       ,
            std::string const&end         ,
            std::string const&argName     ,
            std::string const&def     = "");
        bool isPresent(
            std::string const&start  ,
            std::string const&end    ,
            std::string const&argName);
        size_t getContextLength(
            std::string const&start,
            std::string const&end  );
        std::string getArg(
            std::string const&start     ,
            std::string const&end       ,
            size_t            index     ,
            std::string const&def   = "");
        int getArgi(
            std::string const&start     ,
            std::string const&end       ,
            size_t            index     ,
            std::string const&def   = "");
        float getArgf(
            std::string const&start     ,
            std::string const&end       ,
            size_t            index     ,
            std::string const&def   = "");
      private:
        std::vector<std::string>_argList;///<list of program arguments
    };
  }//util
}//ge

