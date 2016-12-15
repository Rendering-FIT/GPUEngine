#include<geUtil/ArgumentViewer.h>
#include<geCore/ErrorPrinter.h>
#include<geCore/Text.h>

#include<algorithm>
#include<cassert>

using namespace ge::util;

class ge::util::ArgumentViewerImpl{
  public:
    std::string applicationName = "";
    std::vector<std::string>arguments;
    static std::string const contextBegin;
    static std::string const contextEnd  ;
    ArgumentViewer*parent = nullptr;
    size_t getArgumentPosition(std::string const&argument)const{
      assert(this != nullptr);
      size_t argumentIndex = 0;
      size_t contextCounter = 0;
      size_t const notFound = this->arguments.size();
      for(auto x:this->arguments){
        if(x == argument && contextCounter == 0)return argumentIndex;
        if(x == contextBegin)++contextCounter;
        if(x == contextEnd){
          if(contextCounter == 0)return notFound;
          --contextCounter;
        }
        ++argumentIndex;
      }
      return notFound;
    }
    bool getContext(std::vector<std::string>&contextArguments,std::string const&argument)const{
      assert(this!=nullptr);
      size_t ArgumentIndex = this->getArgumentPosition(argument);
      if(ArgumentIndex>=this->arguments.size())return false;
      ++ArgumentIndex;
      if(ArgumentIndex>=this->arguments.size())return false;
      if(this->arguments.at(ArgumentIndex)!=contextBegin)return false;
      ++ArgumentIndex;
      size_t contextCounter=0;
      while(ArgumentIndex<this->arguments.size()){
        if(this->arguments.at(ArgumentIndex)==ArgumentViewerImpl::contextEnd){
          if(contextCounter==0){
            return true;
          }else contextCounter--;
        }
        if(this->arguments.at(ArgumentIndex)==ArgumentViewerImpl::contextBegin)
          contextCounter++;
        contextArguments.push_back(this->arguments.at(ArgumentIndex));
        ++ArgumentIndex;
      }
      contextArguments.clear();
      return false;
    }
    template<typename TYPE>static std::string typeName();
    template<typename TYPE>static bool isValueConvertibleTo(std::string const&text);
    template<
      typename TYPE,
               typename std::enable_if<
                 std::is_same<TYPE,int32_t >::value ||
                 std::is_same<TYPE,int64_t >::value ||
                 std::is_same<TYPE,uint32_t>::value ||
                 std::is_same<TYPE,uint64_t>::value ||
                 std::is_same<TYPE,float   >::value ||
                 std::is_same<TYPE,double  >::value ,unsigned>::type = 0>
                 TYPE str2val(std::string const&value)const{
                   return ge::core::str2Value<TYPE>(value);
                 }
    template<typename TYPE,typename std::enable_if<std::is_same<TYPE,std::string>::value,unsigned>::type = 0>
      TYPE str2val(std::string const&value)const{
        return value;
      }
    template<typename TYPE>
      TYPE getArgument(std::string const&argument,TYPE const&def)const{
        assert(this!=nullptr);
        size_t i=this->getArgumentPosition(argument);
        if(i>=this->arguments.size())return def;
        if(i+1>=this->arguments.size())return def;
        auto value = this->arguments.at(i+1);
        if(!this->isValueConvertibleTo<TYPE>(value))return def;
        return this->str2val<TYPE>(value);
      }
    template<typename TYPE>
      std::vector<TYPE>getArguments(std::string const&argument,std::vector<TYPE>const&def)const{
        assert(this!=nullptr);
        size_t argumentIndex=this->getArgumentPosition(argument);
        if(argumentIndex>=this->arguments.size())return def;
        ++argumentIndex;
        if(argumentIndex>=this->arguments.size())return def;
        std::vector<TYPE>result;
        while(argumentIndex<this->arguments.size()&&this->isValueConvertibleTo<TYPE>(this->arguments.at(argumentIndex)))
          result.push_back(ge::core::str2Value<TYPE>(this->arguments.at(argumentIndex++)));
        while(result.size()<def.size())
          result.push_back(def.at(result.size()));
        return result;
      }
};

namespace ge{
  namespace util{
    template<>std::string ArgumentViewerImpl::typeName<float      >(){return "f32"   ;}
    template<>std::string ArgumentViewerImpl::typeName<double     >(){return "f64"   ;}
    template<>std::string ArgumentViewerImpl::typeName<int32_t    >(){return "i32"   ;}
    template<>std::string ArgumentViewerImpl::typeName<int64_t    >(){return "i64"   ;}
    template<>std::string ArgumentViewerImpl::typeName<uint32_t   >(){return "u32"   ;}
    template<>std::string ArgumentViewerImpl::typeName<uint64_t   >(){return "u64"   ;}
    template<>std::string ArgumentViewerImpl::typeName<std::string>(){return "string";}
    template<>bool ArgumentViewerImpl::isValueConvertibleTo<float>(std::string const&text){
      return ge::core::isFloatingPoint(text)||ge::core::isIntegral(text);
    }
    template<>bool ArgumentViewerImpl::isValueConvertibleTo<double>(std::string const&text){
      return ge::core::isFloatingPoint(text)||ge::core::isIntegral(text);
    }
    template<>bool ArgumentViewerImpl::isValueConvertibleTo<int32_t>(std::string const&text){
      return ge::core::isIntegral(text);
    }
    template<>bool ArgumentViewerImpl::isValueConvertibleTo<int64_t>(std::string const&text){
      return ge::core::isIntegral(text);
    }
    template<>bool ArgumentViewerImpl::isValueConvertibleTo<uint32_t>(std::string const&text){
      return ge::core::isUint(text);
    }
    template<>bool ArgumentViewerImpl::isValueConvertibleTo<uint64_t>(std::string const&text){
      return ge::core::isUint(text);
    }
    template<>bool ArgumentViewerImpl::isValueConvertibleTo<std::string>(std::string const&text){
      return ge::core::isString(text);
    }
    std::string const ArgumentViewerImpl::contextBegin = "{";
    std::string const ArgumentViewerImpl::contextEnd   = "}";
  }
}

/**
 * @brief Contructor of ArgumentViewer
 * This class can be used for simple argument manipulations
 * int main(int argc,char*argv[]){
 *   auto args = std::make_shared<ArgumentViewer>(argc,argv);
 * }
 *
 * @param argc number of arguments, it should always be one or greater (application name is always first argument)
 * @param argv list of arguments, it should always contain application name as the first argument
 */
ArgumentViewer::ArgumentViewer(int argc,char*argv[]){
  assert(this!=nullptr);
  if(argc <= 0){
    ge::core::printError(
        GE_CORE_FCENAME,
        "number of arguments has to be greater than 0",argc,argv);
    return;
  }
  this->_impl = std::unique_ptr<ArgumentViewerImpl>(new ArgumentViewerImpl);
  this->_impl->applicationName = std::string(argv[0]);
  for(int i=1;i<argc;++i)
    this->_impl->arguments.push_back(std::string(argv[i]));
  //this->_format = std::make_shared<ContextFormat>();
}

/**
 * @brief Destructor of ArgumentViewer instance
 */
ArgumentViewer::~ArgumentViewer(){}

/**
 * @brief Returns application name (zeroes argument)
 *
 * @return application name 
 */
std::string ArgumentViewer::getApplicationName()const{
  assert(this!=nullptr);
  return this->_impl->applicationName;
}

/**
 * @brief Returns number of arguments without application name - it can be zero
 *
 * @return number of arguments without inclusion of application name
 */
size_t ArgumentViewer::getNofArguments()const{
  assert(this!=nullptr);
  return this->_impl->arguments.size();
}

/**
 * @brief Gets argument on certain index
 *
 * @param index index of argument, should always be lesser than getNofArguments()
 *
 * @return argument
 */
std::string ArgumentViewer::getArgument(size_t const&index)const{
  assert(this!=nullptr);
  assert(index<this->_impl->arguments.size());
  return this->_impl->arguments.at(index);
}

bool ArgumentViewer::isPresent(std::string const&argument)const{
  assert(this!=nullptr);
  //TODO modify format
  return this->_impl->getArgumentPosition(argument)<this->_impl->arguments.size();
}

float ArgumentViewer::getf32(std::string const&argument,float const&def)const{
  assert(this!=nullptr);
  //TODO modify format
  return this->_impl->getArgument<float>(argument,def);
}

double ArgumentViewer::getf64(std::string const&argument,double const&def)const{
  assert(this!=nullptr);
  //TODO modify format
  return this->_impl->getArgument<double>(argument,def);
}

int32_t ArgumentViewer::geti32(std::string const&argument,int32_t const&def)const{
  assert(this!=nullptr);
  //TODO modify format
  return this->_impl->getArgument<int32_t>(argument,def);
}

int64_t  ArgumentViewer::geti64(std::string const&argument,int64_t  const&def)const{
  assert(this!=nullptr);
  //TODO modify format
  return this->_impl->getArgument<int64_t>(argument,def);
}

uint32_t ArgumentViewer::getu32(std::string const&argument,uint32_t const&def)const{
  assert(this!=nullptr);
  //TODO modify format
  return this->_impl->getArgument<uint32_t>(argument,def);
}

uint64_t ArgumentViewer::getu64(std::string const&argument,uint64_t const&def)const{
  assert(this!=nullptr);
  //TODO modify format
  return this->_impl->getArgument<uint64_t>(argument,def);
}

std::string ArgumentViewer::gets(std::string const&argument,std::string const&def)const{
  assert(this!=nullptr);
  //TODO modify format
  return this->_impl->getArgument<std::string>(argument,def);
}

std::vector<float>ArgumentViewer::getf32v(std::string const&argument,std::vector<float>const&def)const{
  assert(this!=nullptr);
  //TODO modify format
  return this->_impl->getArguments<float>(argument,def);
}

std::vector<double  >ArgumentViewer::getf64v(std::string const&argument,std::vector<double  >const&def)const{
  assert(this!=nullptr);
  //TODO modify format
  return this->_impl->getArguments<double>(argument,def);
}

std::vector<int32_t >ArgumentViewer::geti32v(std::string const&argument,std::vector<int32_t >const&def)const{
  assert(this!=nullptr);
  //TODO modify format
  return this->_impl->getArguments<int32_t>(argument,def);
}

std::vector<int64_t >ArgumentViewer::geti64v(std::string const&argument,std::vector<int64_t >const&def)const{
  assert(this!=nullptr);
  //TODO modify format
  return this->_impl->getArguments<int64_t>(argument,def);
}

std::vector<uint32_t>ArgumentViewer::getu32v(std::string const&argument,std::vector<uint32_t>const&def)const{
  assert(this!=nullptr);
  //TODO modify format
  return this->_impl->getArguments<uint32_t>(argument,def);
}

std::vector<uint64_t>ArgumentViewer::getu64v(std::string const&argument,std::vector<uint64_t>const&def)const{
  assert(this!=nullptr);
  //TODO modify format
  return this->_impl->getArguments<uint64_t>(argument,def);
}

std::shared_ptr<ArgumentViewer>ArgumentViewer::getContext(std::string const&name){
  assert(this!=nullptr);
  //TODO modify format
  std::vector<std::string>subArguments;
  if(!this->_impl->getContext(subArguments,name)){
    char const*argv[]={this->_impl->applicationName.c_str()};
    auto result = std::make_shared<ArgumentViewer>(1,(char**)argv);
    result->_impl->parent = this;
    return result;
  }
  char const*appName[]={this->_impl->applicationName.c_str()};
  auto result = std::make_shared<ArgumentViewer>(1,(char**)appName);
  result->_impl->parent = this;
  result->_impl->arguments = subArguments;
  return result;
}

std::vector<std::string>ArgumentViewer::getsv(std::string const&contextName,std::vector<std::string>const&def)const{
  assert(this!=nullptr);
  //TODO modify format
  std::vector<std::string>subArguments;
  if(!this->_impl->getContext(subArguments,contextName))return def;
  while(def.size()>subArguments.size())subArguments.push_back(def.at(subArguments.size()));
  return subArguments;
}
