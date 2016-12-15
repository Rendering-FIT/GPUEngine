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
          if(contextCounter == 0){
            ge::core::printError(GE_CORE_FCENAME,
                "not matching: "+contextBegin+" and "+contextEnd,argument);
            return notFound;
          }
          --contextCounter;
        }
        ++argumentIndex;
      }
      return notFound;
    }
    bool getContext(std::vector<std::string>&subArguments,std::string const&argument)const{
      assert(this!=nullptr);
      size_t i = this->getArgumentPosition(argument);
      if(i>=this->arguments.size())return false;
      ++i;
      if(i>=this->arguments.size())return false;
      if(this->arguments.at(i)!=contextBegin)return false;
      ++i;
      size_t contextCounter=0;
      while(i<this->arguments.size()){
        if(this->arguments.at(i)==ArgumentViewerImpl::contextEnd){
          if(contextCounter==0){
            return true;
          }else contextCounter--;
        }
        if(this->arguments.at(i)==ArgumentViewerImpl::contextBegin)
          contextCounter++;
        subArguments.push_back(this->arguments.at(i));
        ++i;
      }
      subArguments.clear();
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
        if(i+1>=this->arguments.size()){
          ge::core::printError(GE_CORE_FCENAME,
              "expected "+this->typeName<TYPE>()+" value after parameter: "+argument+" not end of arguments",argument,def);
          return def;
        }
        auto value = this->arguments.at(i+1);
        if(!this->isValueConvertibleTo<TYPE>(value)){
          ge::core::printError(GE_CORE_FCENAME,
              "expected "+this->typeName<TYPE>()+" value after parameter: "+argument+" not: "+value,argument,def);
          return def;
        }
        return this->str2val<TYPE>(value);
      }
    template<typename TYPE>
      std::vector<TYPE>getArguments(std::string const&argument,std::vector<TYPE>const&def)const{
        assert(this!=nullptr);
        size_t i=this->getArgumentPosition(argument);
        if(i>=this->arguments.size())return def;
        if(i+1>=this->arguments.size()){
          ge::core::printError(GE_CORE_FCENAME,
              "expected vector of "+this->typeName<TYPE>()+" values after parameter: "+argument+" not end of arguments",argument,def);
          return def;
        }
        ++i;
        std::vector<TYPE>result;
        while(i<this->arguments.size()&&this->isValueConvertibleTo<TYPE>(this->arguments.at(i)))
          result.push_back(ge::core::str2Value<TYPE>(this->arguments.at(i++)));
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
  size_t contextCounter = 0;
  for(auto const&x:this->_impl->arguments){
    if(x==ArgumentViewerImpl::contextBegin)contextCounter++;
    if(x==ArgumentViewerImpl::contextEnd){
      if(contextCounter==0){
        ge::core::printError(GE_CORE_FCENAME,
            "not matching: "+ArgumentViewerImpl::contextBegin+" and "+ArgumentViewerImpl::contextEnd,argument);
        return false;
      }
      contextCounter--;
    }
    if(x==argument && contextCounter == 0)return true;
  }
  return false;
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
  size_t i=this->_impl->getArgumentPosition(name);
  auto createEmptyViewer = [&](){
    char const*argv[]={this->_impl->applicationName.c_str()};
    auto result = std::make_shared<ArgumentViewer>(1,(char**)argv);
    result->_impl->parent = this;
    return result;
  };
  if(i>=this->_impl->arguments.size())return createEmptyViewer();
  ++i;
  if(i>=this->_impl->arguments.size()){
    ge::core::printError(GE_CORE_FCENAME,
        "expected \""+ArgumentViewerImpl::contextBegin+"\" after context: "+name+" not end of arguments",name);
    return createEmptyViewer();
  }
  if(this->_impl->arguments.at(i)!=ArgumentViewerImpl::contextBegin){
    ge::core::printError(GE_CORE_FCENAME,
        "expected \""+ArgumentViewerImpl::contextBegin+"\" after context: "+name+" not: "+this->_impl->arguments.at(i),name);
    return createEmptyViewer();
  }
  ++i;
  size_t contextCounter=0;
  bool encounteredEnd = false;
  std::vector<std::string>subArguments;

  while(i<this->_impl->arguments.size()){
    if(this->_impl->arguments.at(i)==ArgumentViewerImpl::contextEnd){
      if(contextCounter==0){
        encounteredEnd = true;
        break;
      }else contextCounter--;
    }
    if(this->_impl->arguments.at(i)==ArgumentViewerImpl::contextBegin)
      contextCounter++;
    subArguments.push_back(this->_impl->arguments.at(i));
    ++i;
  }
  if(!encounteredEnd){
    ge::core::printError(GE_CORE_FCENAME,
        "expected \""+ArgumentViewerImpl::contextEnd+"\" at the end of context: "+name+" not end of arguments",name);
    return createEmptyViewer();
  }
  char const*appName[]={this->_impl->applicationName.c_str()};
  auto result = std::make_shared<ArgumentViewer>(1,(char**)appName);
  result->_impl->parent = this;
  result->_impl->arguments = subArguments;
  return result;
}

std::vector<std::string>ArgumentViewer::getsv(std::string const&contextName,std::vector<std::string>const&def)const{
  assert(this!=nullptr);
  std::vector<std::string>subArguments;
  if(!this->_impl->getContext(subArguments,contextName))return def;
  while(def.size()>subArguments.size())subArguments.push_back(def.at(subArguments.size()));
  return subArguments;
}
