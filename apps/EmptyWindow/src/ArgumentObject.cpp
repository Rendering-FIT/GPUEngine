#include"ArgumentObject.h"

ArgumentObject::ArgumentObject(int Argc,char*Argv[]){
  for(int a=0;a<Argc;++a)//loop over arguments
    this->_argList.push_back(std::string(Argv[a]));//push arguemnt
}
std::string ArgumentObject::getArg(
    std::string ArgName,
    std::string Default){
  for(unsigned i=0;i<this->_argList.size();++i)//loop over arguments
    if(this->_argList[i]==ArgName){//this is the argument
      if(i<this->_argList.size()-1)return this->_argList[i+1];//next
      else return Default;//there is no next argument
    }
  return Default;//we did not find the argument
}

std::string ArgumentObject::getArg(
    std::string Start,
    std::string End,
    std::string ArgName,
    std::string Default){
  unsigned i;//act argument index
  unsigned ArgIndex;//index of wanted argument
  for(i=0;i<this->_argList.size();++i){//loop over arguments
    if(this->_argList[i]==Start){//this is start
      i++;//increment index
      break;//break cycle
    }
  }
  if(i==this->_argList.size())return Default;//there is no next argument
  for(;i<this->_argList.size();++i){//loop over arguments
    if(this->_argList[i]==ArgName){//this is the argument
      i++;//increment index
      break;//break cycle
    }
  }
  if(i==this->_argList.size())return Default;//there is no next argument
  ArgIndex=i;//mark the arguement's index
  i++;//next argument
  for(;i<this->_argList.size();++i){//loop over arguments
    if(this->_argList[i]==End){//this is the argument
      break;//break cycle
    }
  }
  if(i==this->_argList.size())return Default;//there is no end argument
  return this->_argList[ArgIndex];//return the argument value
}

bool ArgumentObject::isPresent(std::string ArgName){
  for(unsigned i=0;i<this->_argList.size();++i)//loop voer arguemnts
    if(this->_argList[i]==ArgName)return true;//this is the argument
  return false;//we did not find the argument
}

bool ArgumentObject::isPresent(
    std::string Start,
    std::string End,
    std::string ArgName){
  unsigned i;//act argument index
  for(i=0;i<this->_argList.size();++i){//loop over arguments
    if(this->_argList[i]==Start){//this is start
      i++;//increment index
      break;//break cycle
    }
  }
  if(i==this->_argList.size())return false;//there is no next argument
  for(;i<this->_argList.size();++i){//loop over arguments
    if(this->_argList[i]==ArgName){//this is the argument
      i++;//increment index
      break;//break cycle
    }
  }

  if(i==this->_argList.size())return false;//there is no next argument
  for(;i<this->_argList.size();++i){//loop over arguments
    if(this->_argList[i]==End){//this is the argument
      break;//break cycle
    }
  }
  if(i==this->_argList.size())return false;//there is no end argument
  return true;//return the argument value
}

unsigned ArgumentObject::getContextLength(
    std::string Start,
    std::string End){
  unsigned i;//act argument index
  unsigned Counter=0;
  for(i=0;i<this->_argList.size();++i){//loop over arguments
    if(this->_argList[i]==Start){//this is start
      i++;//increment index
      break;//break cycle
    }
  }
  if(i==this->_argList.size())return 0;//there is no next argument
  for(;i<this->_argList.size();++i){//loop over arguments
    if(this->_argList[i]==End){//this is the argument
      break;//break cycle
    }
    ++Counter;//increment counter
  }
  if(i==this->_argList.size())return 0;//there is no end argument
  return Counter;//return number of arguments in context
}

std::string ArgumentObject::getArg(
    std::string Start,
    std::string End,
    unsigned Index,
    std::string Default){
  unsigned i;//act argument index
  unsigned StartIndex=0;
  for(i=0;i<this->_argList.size();++i){//loop over arguments
    if(this->_argList[i]==Start){//this is start
      StartIndex=i;
      i++;//increment index
      break;//break cycle
    }
  }
  if(i==this->_argList.size())return Default;//there is no next argument
  i++;//next argument
  for(;i<this->_argList.size();++i){//loop over arguments
    if(this->_argList[i]==End){//this is the argument
      break;//break cycle
    }
  }
  if(i==this->_argList.size())return Default;//there is no end argument
  return this->_argList[StartIndex+1+Index];//return argument by index

}


