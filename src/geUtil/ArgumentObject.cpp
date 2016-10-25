#include<geUtil/ArgumentObject.h>

#include<limits>
#include<cstdlib>

using namespace ge::util;

/**
 * @brief converts string to float with -+ inf ...
 *
 * @param s string
 *
 * @return floating point number
 */
float ge::util::atof(const char*s){
  if(s[0]=='-')return -(float)std::atof(s+1);
  std::string str(s);
  if(str=="inf")return std::numeric_limits<float>::infinity();
  else return (float)std::atof(s);
  //todo Inf INF -inf -Inf -INF NAN NaN nan ...
}

/**
 * @brief Constructor
 *
 * @param argc   number of arguments
 * @param argv[] arguments
 */
ArgumentObject::ArgumentObject(int argc,char*argv[]){
  for(int a=0;a<argc;++a)//loop over arguments
    this->_argList.push_back(std::string(argv[a]));//push arguemnt
}

/**
 * @brief Gets following argument
 *
 * @param argName argument name
 * @param def default returning value if the arg. is not found
 *
 * @return return next argument (1024 for -w; -w 1024)
 */
std::string ArgumentObject::getArg(
    std::string const&argName,
    std::string const&def    ){
  for(size_t i=0;i<this->_argList.size();++i)//loop over arguments
    if(this->_argList[i]==argName){//this is the argument
      if(i<this->_argList.size()-1)return this->_argList[i+1];//next
      else return def;//there is no next argument
    }
  return def;//we did not find the argument
}

/**
 * @brief Gets following argument and converts it to integer
 *
 * @param argName argument name
 * @param def default returning value if the arg. is not found
 *
 * @return return next argument (1024 for -w; -w 1024)
 */
int ArgumentObject::getArgi(
    std::string const&ArgName,
    std::string const&Default){
  return std::atoi(this->getArg(ArgName,Default).c_str());
}

/**
 * @brief Gets following argument and converts it to float
 *
 * @param argName argument name
 * @param def default returning value if the arg. is not found
 *
 * @return return next argument (1024 for -w; -w 1024)
 */
float ArgumentObject::getArgf(
    std::string const&argName,
    std::string const&def    ){
  return ge::util::atof(this->getArg(argName,def).c_str());
}

/**
 * @brief Is argument present
 *
 * @param argName argument name
 *
 * @return return true if the argument is used
 */
bool ArgumentObject::isPresent(std::string const&argName){
  for(size_t i=0;i<this->_argList.size();++i)//loop voer arguemnts
    if(this->_argList[i]==argName)return true;//this is the argument
  return false;//we did not find the argument
}




/**
 * @brief Gets following argument in context
 *
 * @param start starting argument of context
 * @param end ending argument of context
 * @param argName argument name
 * @param def default returning value if the arg. is not found
 *
 * @return 768 for -h in: -foo -tessstart -w 1024 -h 768 -tessend
 */
std::string ArgumentObject::getArg(
    std::string const&start  ,
    std::string const&end    ,
    std::string const&argName,
    std::string const&def    ){
  size_t i;//act argument index
  size_t ArgIndex;//index of wanted argument
  for(i=0;i<this->_argList.size();++i){//loop over arguments
    if(this->_argList[i]==start){//this is start
      i++;//increment index
      break;//break cycle
    }
  }
  if(i==this->_argList.size())return def;//there is no next argument
  for(;i<this->_argList.size();++i){//loop over arguments
    if(this->_argList[i]==argName){//this is the argument
      i++;//increment index
      break;//break cycle
    }
  }
  if(i==this->_argList.size())return def;//there is no next argument
  ArgIndex=i;//mark the arguement's index
  i++;//next argument
  for(;i<this->_argList.size();++i){//loop over arguments
    if(this->_argList[i]==end){//this is the argument
      break;//break cycle
    }
  }
  if(i==this->_argList.size())return def;//there is no end argument
  return this->_argList[ArgIndex];//return the argument value
}

/**
 * @brief Gets following argument in context and converts it to integer
 *
 * @param start starting argument of context
 * @param end ending argument of context
 * @param argName argument name
 * @param def default returning value if the arg. is not found
 *
 * @return 768 for -h in: -foo -tessstart -w 1024 -h 768 -tessend
 */
int ArgumentObject::getArgi(
    std::string const&start  ,
    std::string const&end    ,
    std::string const&argName,
    std::string const&def    ){
  return std::atoi(this->getArg(start,end,argName,def).c_str());
}

/**
 * @brief Gets following argument in context and converts it to float
 *
 * @param start starting argument of context
 * @param end ending argument of context
 * @param argName argument name
 * @param def default returning value if the arg. is not found
 *
 * @return 768 for -h in: -foo -tessstart -w 1024 -h 768 -tessend
 */
float ArgumentObject::getArgf(
    std::string const&start  ,
    std::string const&end    ,
    std::string const&argName,
    std::string const&def    ){
  return ge::util::atof(this->getArg(start,end,argName,def).c_str());
}

/**
 * @brief Is arguemnt present in context
 *
 * @param start starting argument of context
 * @param end ending argument of context
 * @param argName argment name
 *
 * @return true for -h in: -foo -gostart -bla -h -jojo -goend
 */
bool ArgumentObject::isPresent(
    std::string const&start  ,
    std::string const&end    ,
    std::string const&argName){
  size_t i;//act argument index
  for(i=0;i<this->_argList.size();++i){//loop over arguments
    if(this->_argList[i]==start){//this is start
      i++;//increment index
      break;//break cycle
    }
  }
  if(i==this->_argList.size())return false;//there is no next argument
  for(;i<this->_argList.size();++i){//loop over arguments
    if(this->_argList[i]==argName){//this is the argument
      i++;//increment index
      break;//break cycle
    }
  }

  if(i==this->_argList.size())return false;//there is no next argument
  for(;i<this->_argList.size();++i){//loop over arguments
    if(this->_argList[i]==end){//this is the argument
      break;//break cycle
    }
  }
  if(i==this->_argList.size())return false;//there is no end argument
  return true;//return the argument value
}

/**
 * @brief Gets number of arguments in context
 *
 * @param start starting argument of context
 * @param end ending arguement of context
 *
 * @return 3 in: -foo -blastart -a -b -c -blaend
 */
size_t ArgumentObject::getContextLength(
    std::string const&start,
    std::string const&end  ){
  size_t i;//act argument index
  size_t Counter=0;
  for(i=0;i<this->_argList.size();++i){//loop over arguments
    if(this->_argList[i]==start){//this is start
      i++;//increment index
      break;//break cycle
    }
  }
  if(i==this->_argList.size())return 0;//there is no next argument
  for(;i<this->_argList.size();++i){//loop over arguments
    if(this->_argList[i]==end){//this is the argument
      break;//break cycle
    }
    ++Counter;//increment counter
  }
  if(i==this->_argList.size())return 0;//there is no end argument
  return Counter;//return number of arguments in context
}

/**
 * @brief Gets argument in context by index
 *
 * @param start starting argument of context
 * @param end endif argument of context
 * @param index index of argument in context
 * @param def default value of argument
 *
 * @return g for 2 in: -foo -hahastart a b g d -hahaend
 */
std::string ArgumentObject::getArg(
    std::string const&start,
    std::string const&end  ,
    size_t            index,
    std::string const&def  ){
  size_t i;//act argument index
  size_t StartIndex=0;
  for(i=0;i<this->_argList.size();++i){//loop over arguments
    if(this->_argList[i]==start){//this is start
      StartIndex=i;
      i++;//increment index
      break;//break cycle
    }
  }
  if(i==this->_argList.size())return def;//there is no next argument
  i++;//next argument
  for(;i<this->_argList.size();++i){//loop over arguments
    if(this->_argList[i]==end){//this is the argument
      break;//break cycle
    }
  }
  if(i==this->_argList.size())return def;//there is no end argument
  return this->_argList[StartIndex+1+index];//return argument by index
}

int ArgumentObject::getArgi(
    std::string const&start,
    std::string const&end  ,
    size_t            index,
    std::string const&def  ){
  return std::atoi(this->getArg(start,end,index,def).c_str());
}

/**
 * @brief Gets following argument in context and converts it to float
 *
 * @param start starting argument of context
 * @param end ending argument of context
 * @param index argument index
 * @param def default returning value if the arg. is not found
 *
 * @return 768 for -h in: -foo -tessstart -w 1024 -h 768 -tessend
 */
float ArgumentObject::getArgf(
    std::string const&start,
    std::string const&end  ,
    size_t            index,
    std::string const&def  ){
  return ge::util::atof(this->getArg(start,end,index,def).c_str());
}



