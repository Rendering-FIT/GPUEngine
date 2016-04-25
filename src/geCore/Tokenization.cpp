#include<geCore/Tokenization.h>
#include<sstream>
#include<iterator>
#include<fstream>
#include<limits>

using namespace ge::core;

Tokenization::Tokenization(std::string start){
  this->_data.fsa = std::make_shared<FSA>(start);
}

Tokenization::Tokenization(){
  this->_data.fsa = nullptr;
}

Tokenization::~Tokenization(){
}

void Tokenization::load(std::string source){
  auto csv=std::make_shared<Tokenization>("START");
  csv->addTransition("START"    ,","     ,"START"    ,","                              );
  csv->addTransition("START"    ,"\r\n"  ,"LINE-END"                                   );
  csv->addTransition("START"    ,"\\\\"  ,"BACKSLASH",""        ,"b"                   );
  csv->addTransition("START"    ,FSA::els,"STRING"   ,""        ,"b"                   );
  csv->addTransition("START"    ,FSA::eof,"END"                                        );

  csv->addTransition("LINE-END" ,"\r\n"  ,"LINE-END"                                   );
  csv->addTransition("LINE-END" ,FSA::els,"START"    ,"line-end","g"                   );
  csv->addTransition("LINE-END" ,FSA::eof,"END"                                        );

  csv->addTransition("BACKSLASH",FSA::all,"STRING"                                     );
  csv->addTransition("BACKSLASH",FSA::eof,""         ,"unexpected end of file after \\");

  csv->addTransition("STRING"   ,"\r\n"  ,"LINE-END" ,"value"   ,"e"                   );
  csv->addTransition("STRING"   ,"\\\\"  ,"BACKSLASH"                                  );
  csv->addTransition("STRING"   ,","     ,"START"    ,"value"   ,"eg"                  );
  csv->addTransition("STRING"   ,FSA::els,"STRING"                                     );
  csv->addTransition("STRING"   ,FSA::eof,"END"      ,"value"   ,"e"                   );

  csv->begin();
  csv->parse(source);
  csv->end();
  bool lastWasComma=false;
  bool firstState = true;
  std::vector<std::string>params;
  while(!csv->empty()){
    auto t=csv->getToken();
    if(csv->tokenName(t.type)=="value"   ){
      std::string data="";
      bool escape=false;
      //std::cout<<"#######################################################: "<<t.rawData<<":"<<std::endl;
      for(std::string::size_type i=0;i<t.rawData.length();++i){
        if(!escape&&t.rawData[i]=='\\'){
          escape=true;
          continue;
        }
        if(escape){
          escape=false;
          switch(t.rawData[i]){
            case't':data+='\t'        ;break;
            case'n':data+='\n'        ;break;
            case'r':data+='\r'        ;break;
            default:data+=t.rawData[i];break;
          }
          continue;
        }
        data+=t.rawData[i];
      }
      params.push_back(data);
      lastWasComma=false;
      continue;
    }
    if(csv->tokenName(t.type)==","){
      if(lastWasComma)params.push_back("");
      lastWasComma = true;
      continue;
    }
    if(csv->tokenName(t.type)=="line-end"){
      if(lastWasComma)params.push_back("");
      lastWasComma=false;
      if(params.size()>=3&&params.size()<=5){
        while(params.size()!=5)params.push_back("");
        if(firstState){
          this->_data.fsa=std::make_shared<FSA>(params[0]);
          firstState=false;
        }
        //std::cout<<":"<<params[0]<<"-"<<params[1]<<"->"<<params[2]<<" "<<params[3]<<" "<<params[4]<<std::endl;
        this->addTransition(params[0],params[1],params[2],params[3],params[4]);
      }
      params.clear();
    }
  }
  if(params.size()>=3&&params.size()<=5){
    while(params.size()!=5)params.push_back("");
    if(firstState){
      this->_data.fsa=std::make_shared<FSA>(params[0]);
      firstState=false;
    }
    this->addTransition(params[0],params[1],params[2],params[3],params[4]);
    //std::cout<<":"<<params[0]<<"-"<<params[1]<<"->"<<params[2]<<" "<<params[3]<<" "<<params[4]<<std::endl;
  }
}

void Tokenization::addTransition(
    std::string start ,
    std::string lex   ,
    std::string end   ,
    std::string token ,
    std::string config){
  //std::cout<<start<<"-#"<<lex<<"#->"<<end<<"#"<<token<<"#"<<config<<"#"<<std::endl;
  Config conf=0;
  if(config.find(Tokenization::config_bit_begin )!=std::string::npos)conf|=BEGIN ;
  if(config.find(Tokenization::config_bit_end   )!=std::string::npos)conf|=END   ;
  if(config.find(Tokenization::config_bit_goback)!=std::string::npos)conf|=GOBACK;
  if(config.find(Tokenization::config_bit_create)!=std::string::npos)conf|=CREATE;
  if(end!=""&&token!="")conf|=CREATE;
  if(token==""){
    if(conf==EMPTY){
      this->_data.fsa->addTransition(start,lex,end);
    }else{
      this->_data.callbackData.push_back(std::make_shared<CallbackData>(conf,0,&this->_data));
      this->_data.fsa->addTransition(start,lex,end,
          this->_callback,&*this->_data.callbackData.back());
    }
    return;
  }

  if(end==""){
    this->_data.errorMessages.push_back(token);
    this->_data.fsa->addTransition(start,lex,end,
        this->_errorCallback,&this->_data.errorMessages.back());
    return;
  }

  Token::Type term = 0;
  if(token.find(" ")!=std::string::npos){
    std::stringstream ss(token);
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    std::vector<std::string> vstrings(begin, end);
    term = this->_registerToken(vstrings[0]);
    this->_data.hasKeywords.insert(term);
    for(auto x:vstrings)this->_registerToken(x);
  }else term = this->_registerToken(token);
  this->_data.callbackData.push_back(std::make_shared<CallbackData>(conf,term,&this->_data));
  this->_data.fsa->addTransition(start,lex,end,
      this->_callback,&*this->_data.callbackData.back());
}

std::string Tokenization::tokenName(Token::Type    term )const{
  auto ii=this->_data.term2name.find(term);
  if(ii!=this->_data.term2name.end())return ii->second;
  return "";
}

Token::Type    Tokenization::tokenType(std::string token)const{
  auto ii=this->_data.name2term.find(token);
  if(ii!=this->_data.name2term.end())return ii->second;
  return std::numeric_limits<Token::Type>::max();
}

Tokenization::TokenIndex Tokenization::nofTokens()const{
  return this->_data.name2term.size();
}

Token::Type Tokenization::_registerToken(std::string token){
  auto ii=this->_data.name2term.find(token);
  if(ii!=this->_data.name2term.end())return ii->second;
  Token::Type result = this->_data.name2term.size();
  this->_data.name2term[token]=result;
  this->_data.term2name[result]=token;
  return result;
}

void Tokenization::_callback(ge::core::FSA*fsa,void*data){
  auto cd=(CallbackData*)data;
  if(cd->conf&Tokenization::END){
    auto word = fsa->getAlreadyReadString().substr(cd->data->charPosition);
    Token::Type term = cd->term;
    if(cd->data->hasKeywords.count(term)){
      auto ii=cd->data->name2term.find(word);
      if(ii!=cd->data->name2term.end())
        term=ii->second;
    }
    cd->data->tokens.push_back(Token(term,word));
  }else if(cd->conf&Tokenization::CREATE){
    cd->data->tokens.push_back(Token(cd->term));
  }
  if(cd->conf&BEGIN){
    cd->data->charPosition = fsa->getCurrentPosition();
  }
  if(cd->conf&GOBACK)fsa->goBack();
}

void Tokenization::_errorCallback(ge::core::FSA*fsa,void*data){
  std::string*cd=(std::string*)data;
  std::cerr<<"ERROR: Tokenization at position: ";
  std::cerr<<fsa->getCurrentPosition()<<" and char: ";
  std::cerr<<fsa->getCurrentChar()<<" - "<<*cd<<std::endl;
}


Token Tokenization::getToken(){
  return this->_data.tokens[this->_data.currentToken++];
}

bool Tokenization::empty()const{
  return this->_data.currentToken>=this->_data.tokens.size();
}

void Tokenization::clear(){
  this->_data.tokens.clear();
  this->_data.currentToken = 0;
}

void Tokenization::parse(std::string data){
  this->_data.fsa->unpause(data);
}

void Tokenization::end(){
  this->_data.fsa->stop("");
}

void Tokenization::begin(){
  this->_data.fsa->runWithPause("");
}

Tokenization::Data::Data(){
  this->currentToken = 0;
  this->charPosition = 0;
}

const std::string Tokenization::config_bit_begin  = "b";
const std::string Tokenization::config_bit_end    = "e";
const std::string Tokenization::config_bit_goback = "g";
const std::string Tokenization::config_bit_create = "c";
const std::string Tokenization::config_bit_empty  = "" ;

