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
    size_t getArgumentPosition(std::string const&argument)const{
      assert(this != nullptr);
      size_t argumentIndex = 0;
      size_t namespaceCounter = 0;
      std::string const namespaceBegin = "{";
      std::string const namespaceEnd   = "}";
      size_t const notFound = this->arguments.size();
      for(auto x:this->arguments){
        if(x == argument && namespaceCounter == 0)return argumentIndex;
        if(x == namespaceBegin)++namespaceCounter;
        if(x == namespaceEnd){
          if(namespaceCounter == 0){
            ge::core::printError(GE_CORE_FCENAME,
                "not matching: "+namespaceBegin+" and "+namespaceEnd,argument);
            return notFound;
          }
          --namespaceCounter;
        }
        ++argumentIndex;
      }
      return notFound;
    }
    template<typename TYPE>static std::string typeName();
    template<typename TYPE>
      TYPE getArgument(std::string const&argument,TYPE const&def)const{
        assert(this!=nullptr);
        //TODO modify format
        size_t i=this->getArgumentPosition(argument);
        if(i>=this->arguments.size())return def;
        if(i+1>=this->arguments.size()){
          ge::core::printError(GE_CORE_FCENAME,
              "expected "+this->typeName<TYPE>()+" value after parameter: "+argument+" not end of arguments",argument,def);
          return def;
        }
        auto value = this->arguments.at(i+1);
        if(!ge::core::isValue<TYPE>(value)){
          ge::core::printError(GE_CORE_FCENAME,
              "expected "+this->typeName<TYPE>()+" value after parameter: "+argument+" not: "+value,argument,def);
          return def;
        }
        return ge::core::str2Value<TYPE>(value);
      }

};

namespace ge{
  namespace util{
    template<>std::string ArgumentViewerImpl::typeName<float >(){return "f32";}
    template<>std::string ArgumentViewerImpl::typeName<double>(){return "f64";}
  }
}

ArgumentViewer::ArgumentViewer(int argc,char*argv[]){
  assert(this!=nullptr);
  if(argc <= 0){
    ge::core::printError(
        GE_CORE_FCENAME,
        "number of arguments has to be greater than 0",argc,argv);
    return;
  }
  this->_impl = std::make_unique<ArgumentViewerImpl>();
  this->_impl->applicationName = std::string(argv[0]);
  for(int i=1;i<argc;++i)
    this->_impl->arguments.push_back(std::string(argv[i]));
  //this->_format = std::make_shared<ContextFormat>();
}

ArgumentViewer::~ArgumentViewer(){}

std::string ArgumentViewer::getApplicationName()const{
  assert(this!=nullptr);
  return this->_impl->applicationName;
}

size_t ArgumentViewer::getNofArguments()const{
  assert(this!=nullptr);
  return this->_impl->arguments.size();
}

std::string ArgumentViewer::getArgument(size_t const&index)const{
  assert(this!=nullptr);
  assert(index<this->_impl->arguments.size());
  return this->_impl->arguments.at(index);
}

bool ArgumentViewer::isPresent(std::string const&argument)const{
  assert(this!=nullptr);
  //TODO modify format
  return std::find(
      this->_impl->arguments.begin(),
      this->_impl->arguments.end(),argument) != this->_impl->arguments.end();
}

float ArgumentViewer::getf32(std::string const&argument,float const&def)const{
  assert(this!=nullptr);
  //TODO modify format
  size_t i=this->_impl->getArgumentPosition(argument);
  if(i>=this->_impl->arguments.size())return def;
  if(i+1>=this->_impl->arguments.size()){
    ge::core::printError(GE_CORE_FCENAME,
        "expected f32 value after parameter: "+argument+" not end of arguments",argument,def);
    return def;
  }
  auto value = this->_impl->arguments.at(i+1);
  if(!ge::core::isValue<float>(value)){
    ge::core::printError(GE_CORE_FCENAME,
        "expected f32 value after parameter: "+argument+" not: "+value,argument,def);
    return def;
  }
  return ge::core::str2Value<float>(value);
}

double ArgumentViewer::getf64(std::string const&argument,double const&def)const{
  assert(this!=nullptr);
  //TODO modify format
  size_t i=this->_impl->getArgumentPosition(argument);
  if(i>=this->_impl->arguments.size())return def;
  if(i+1>=this->_impl->arguments.size()){
    ge::core::printError(GE_CORE_FCENAME,
        "expected f64 value after parameter: "+argument+" not end of arguments",argument,def);
    return def;
  }
  auto value = this->_impl->arguments.at(i+1);
  if(!ge::core::isValue<double>(value)){
    ge::core::printError(GE_CORE_FCENAME,
        "expected f64 value after parameter: "+argument+" not: "+value,argument,def);
    return def;
  }
  return ge::core::str2Value<double>(value);
}
