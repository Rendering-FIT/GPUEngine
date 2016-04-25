#include<geCore/Text.h>
#include<fstream>
#include<iostream>
#include<string>
#include<geCore/fsa/Fsa.h>

using namespace ge::core;

std::string ge::core::loadTextFile(std::string fileName){
  std::ifstream f(fileName.c_str(), std::ios_base::in | std::ios_base::binary);
  if(!f.good()){
    std::cerr<<"ERROR: ge::core::loadTextFile("<<fileName;
    std::cerr<<") - cannot open file"<<std::endl;
    return "";
  }
  f.seekg(0,std::ios::end);
  std::size_t size=f.tellg();
  f.seekg(0,std::ios::beg);
  char*buffer=new char[size+1];
  f.read(buffer,size);
  buffer[size]='\0';
  std::string result(buffer);
  delete[]buffer;
  f.close();
  return result;
}

std::string ge::core::processEscapeSequences(std::string data){
  struct ParserData{
    unsigned    pos   ;
    std::string string;

    static void addChar(ge::core::FSA*fsa,void*data){
      auto d=(ParserData*)data;
      d->string+=fsa->getCurrentChar();
    };

    static void pushPos(ge::core::FSA*fsa,void*data){
      auto d=(ParserData*)data;
      d->pos = fsa->getCurrentPosition();
    };

    static void addEscChar(ge::core::FSA*fsa,void*data){
      auto d=(ParserData*)data;
      switch(fsa->getCurrentChar()){
        case '\'':d->string+='\'';break;
        case '\"':d->string+='\"';break;
        case '?' :d->string+='\?';break;
        case '\\':d->string+='\\';break;
        case 'a' :d->string+='\a';break;
        case 'b' :d->string+='\b';break;
        case 'f' :d->string+='\f';break;
        case 'n' :d->string+='\n';break;
        case 'r' :d->string+='\r';break;
        case 't' :d->string+='\t';break;
        case 'v' :d->string+='\v';break;
        default  :
                  d->string+=fsa->getCurrentChar();
                  std::cerr<<"WARNING: unknown escape sequence: \'\\";
                  std::cerr<<fsa->getCurrentChar()<<"\'"<<std::endl;
                  break;
      }
    };

    static void addHexa(ge::core::FSA*fsa,void*data){
      auto d=(ParserData*)data;
      auto toConvert = fsa->getAlreadyReadString().substr(d->pos+1);
      if(toConvert == ""){
        std::cerr<<"WARNING: \\x used with no following hex digits"<<std::endl;
        return;
      }
      unsigned val=0;
      bool overflow = false;
      for(unsigned i=0;i<toConvert.size();++i){
        val<<=4;
        char c=toConvert[i];
        if(c>='0'&&c<='9')val+=c-'0';
        else if(c>='a'&&c<='f')val+=c-'a'+10;
        else val+=c-'A'+10;
        if(val>=256)overflow = true;
      }
      if(overflow)std::cerr<<"WARNING: hex escape sequence out of range"<<std::endl;
      d->string+=(char)((unsigned char)val);
    };

    static void addHexaGoBack(ge::core::FSA*fsa,void*data){
      ((ParserData*)data)->addHexa(fsa,data);
      fsa->goBack();
    };

    static void addUnicode(ge::core::FSA*,void*){
      std::cerr<<"WARNING: unicode escape sequence not implemented"<<std::endl;
    };

    static void addUnicodeGoBack(ge::core::FSA*fsa,void*data){
      ((ParserData*)data)->addUnicode(fsa,data);
      fsa->goBack();
    };

    static void addOctal(ge::core::FSA*fsa,void*data){
      auto d=(ParserData*)data;
      auto toConvert = fsa->getAlreadyReadString().substr(d->pos+1);
      unsigned val=0;
      for(unsigned i=0;i<toConvert.size();++i){
        val<<=3;
        char c=toConvert[i];
        if(c>='0'&&c<='7')val+=c-'0';
      }
      if(val>=256)std::cerr<<"WARNING: octal escape sequence out of range"<<std::endl;
      d->string+=(char)((unsigned char)val);
    };

    static void addOctalGoBack(ge::core::FSA*fsa,void*data){
      ((ParserData*)data)->addOctal(fsa,data);
      fsa->goBack();
    };

    static void error(ge::core::FSA*,void*){
      std::cerr<<"ERROR: unexpected end of escape sequence"<<std::endl;
    };
  }pData;

  static auto fsa = ge::core::FSA(
      "START"    ,
      "START"    ,"\\\\"            ,"BACKSLASH",
      "START"    ,ge::core::FSA::els,"START"    ,pData.addChar         ,(void*)&pData,
      "START"    ,ge::core::FSA::eof,"END"      ,
      "BACKSLASH","x"               ,"HEXA"     ,pData.pushPos         ,(void*)&pData,
      "BACKSLASH","uU"              ,"UNICODE"  ,pData.pushPos         ,(void*)&pData,
      "BACKSLASH","0\\-7"           ,"OCTAL0"   ,pData.pushPos         ,(void*)&pData,
      "BACKSLASH",ge::core::FSA::els,"START"    ,pData.addEscChar      ,(void*)&pData,
      "BACKSLASH",ge::core::FSA::eof,""         ,pData.error           ,
      "HEXA"     ,"0\\-9a\\-fA\\-F" ,"HEXA"     ,
      "HEXA"     ,ge::core::FSA::els,"START"    ,pData.addHexaGoBack   ,(void*)&pData,
      "HEXA"     ,ge::core::FSA::eof,"END"      ,pData.addHexa         ,(void*)&pData,
      "UNICODE"  ,"0\\-9a\\-fA\\-F" ,"UNICODE"  ,
      "UNICODE"  ,ge::core::FSA::els,"START"    ,pData.addUnicodeGoBack,(void*)&pData,
      "UNICODE"  ,ge::core::FSA::eof,"END"      ,pData.addUnicode      ,(void*)&pData,
      "OCTAL0"   ,"0\\-7"           ,"OCTAL1"   ,
      "OCTAL0"   ,ge::core::FSA::els,"START"    ,pData.addOctalGoBack  ,(void*)&pData,
      "OCTAL0"   ,ge::core::FSA::eof,"END"      ,pData.addOctal        ,(void*)&pData,
      "OCTAL1"   ,"0\\-7"           ,"START"    ,pData.addOctal        ,(void*)&pData,
      "OCTAL1"   ,ge::core::FSA::els,"START"    ,pData.addOctalGoBack  ,(void*)&pData,
      "OCTAL1"   ,ge::core::FSA::eof,"END"      ,pData.addOctal        ,(void*)&pData);

  pData.pos    = 0 ;
  pData.string = "";
  fsa.run(data);
  return pData.string;
}
