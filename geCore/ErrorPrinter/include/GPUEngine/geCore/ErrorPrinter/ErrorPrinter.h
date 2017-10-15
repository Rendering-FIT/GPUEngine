#pragma once

#include<GPUEngine/geCore/PrettyFunctionName/PrettyFunctionName.h>
#include<GPUEngine/geCore/ValuePrinter/ValuePrinter.h>

namespace ge{
  namespace core{
    template<typename...ARGS,typename = std::enable_if<sizeof...(ARGS)!=0>>
      void printError(std::string fceName,std::string message,ARGS...args){
        std::cerr<<"ERROR: "<<fceName<<"(";
        std::vector<std::string>argStrings = {value2str(args)...};
        bool first=true;
        for(auto const&x:argStrings){
          if(first)first=false;
          else std::cerr<<",";
          std::cerr<<x;
        }
        std::cerr<<") - "<<message<<std::endl;
      }
  }
}
