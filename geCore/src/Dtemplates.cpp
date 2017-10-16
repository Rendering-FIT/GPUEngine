#include<GPUEngine/geCore/Dtemplates.h>
#include<GPUEngine/geCore/FSA/FSA.h>

using namespace ge::core;

void ParseEnumArgs::_begin(ge::core::FSA*fsa,void*data){
  ParserData*p=(ParserData*)data;
  p->start = fsa->getCurrentPosition();
}

void ParseEnumArgs::_writeKey(ge::core::FSA*fsa,void*data){
  ParserData*p=(ParserData*)data;
  p->_this->_id2Name[p->id++]=fsa->getAlreadyReadString().substr(p->start);
}

void ParseEnumArgs::_storeKey(ge::core::FSA*fsa,void*data){
  ParserData*p=(ParserData*)data;
  p->key = fsa->getAlreadyReadString().substr(p->start);
}

void ParseEnumArgs::_writeStoredKey(ge::core::FSA*,void*data){
  ParserData*p=(ParserData*)data;
  p->_this->_id2Name[p->id++]=p->key;
}

void ParseEnumArgs::_writeValue(ge::core::FSA*fsa,void*data){
  ParserData*p=(ParserData*)data;
  std::string sValue=fsa->getAlreadyReadString().substr(p->start);
  p->id = std::atoi(sValue.c_str());
  p->_this->_id2Name[p->id++] = p->key;
}


ParseEnumArgs::ParseEnumArgs(){
  this->_f = std::make_shared<ge::core::FSA>(
      "S",
      "S",ge::core::FSA::space,"S",
      "S","a\\-zA\\-Z_"       ,"A",(ge::core::FSACallback::Fce)this->_begin         ,(void*)&this->_pData,
      "S",ge::core::FSA::eof  ,"H",(ge::core::FSACallback::Fce)this->_writeKey      ,(void*)&this->_pData,
      "A","a\\-zA\\-Z0\\-9_"  ,"A",
      "A",","                 ,"B",(ge::core::FSACallback::Fce)this->_writeKey      ,(void*)&this->_pData,
      "A",ge::core::FSA::space,"C",(ge::core::FSACallback::Fce)this->_storeKey      ,(void*)&this->_pData,
      "A","="                 ,"D",(ge::core::FSACallback::Fce)this->_storeKey      ,(void*)&this->_pData,
      "A",ge::core::FSA::eof  ,"H",(ge::core::FSACallback::Fce)this->_writeKey      ,(void*)&this->_pData,
      "B",ge::core::FSA::space,"S",
      "B","a\\-zA\\-Z_"       ,"A",(ge::core::FSACallback::Fce)this->_begin         ,(void*)&this->_pData,
      "B",ge::core::FSA::eof  ,"H",
      "C",ge::core::FSA::space,"C",
      "C",","                 ,"B",(ge::core::FSACallback::Fce)this->_writeStoredKey,(void*)&this->_pData,
      "C","="                 ,"D",
      "C",ge::core::FSA::eof  ,"H",(ge::core::FSACallback::Fce)this->_writeStoredKey,(void*)&this->_pData,
      "D",ge::core::FSA::space,"E",
      "D",","                 ,"B",(ge::core::FSACallback::Fce)this->_writeStoredKey,(void*)&this->_pData,
      "D",ge::core::FSA::digit,"F",(ge::core::FSACallback::Fce)this->_begin         ,(void*)&this->_pData,
      "D",ge::core::FSA::eof  ,"H",(ge::core::FSACallback::Fce)this->_writeStoredKey,(void*)&this->_pData,
      "E",ge::core::FSA::space,"E",
      "E",","                 ,"B",(ge::core::FSACallback::Fce)this->_writeStoredKey,(void*)&this->_pData,
      "E",ge::core::FSA::digit,"F",(ge::core::FSACallback::Fce)this->_begin         ,(void*)&this->_pData,
      "E",ge::core::FSA::eof  ,"H",(ge::core::FSACallback::Fce)this->_writeStoredKey,(void*)&this->_pData,
      "F",ge::core::FSA::digit,"F",
      "F",ge::core::FSA::space,"G",(ge::core::FSACallback::Fce)this->_writeValue    ,(void*)&this->_pData,
      "F",","                 ,"B",(ge::core::FSACallback::Fce)this->_writeValue    ,(void*)&this->_pData,
      "F",ge::core::FSA::eof  ,"H",(ge::core::FSACallback::Fce)this->_writeValue    ,(void*)&this->_pData,
      "G",ge::core::FSA::space,"G",
      "G",","                 ,"B",
      "G",ge::core::FSA::eof  ,"H"
        );
  this->_pData._this = this;
}

std::map<unsigned,std::string>ParseEnumArgs::operator()(const char*args){
  this->_pData.key="";
  this->_pData._this = this;
  this->_pData.start = 0;
  this->_pData.id = 0;
  this->_f->run(std::string(args));
  return this->_id2Name;
}

size_t ge::core::divRoundUp(size_t x,size_t y){
  return(x/y)+(x%y==0?0:1);
}

size_t ge::core::divRoundDown(size_t x,size_t y){
  return x/y;
}

size_t ge::core::getDispatchSize(size_t workSize,size_t workGroupSize){
  return workSize%workGroupSize?workSize/workGroupSize+1:workSize/workGroupSize;
}

unsigned ge::core::bitCount(unsigned value){
  unsigned result=0;
  while(value){
    result+=value&1u;
    value>>=1;
  }
  return result;
}
