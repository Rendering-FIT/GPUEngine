#include<geCore/token.h>

#include<sstream>
#include<geCore/fsa/fsa.h>

using namespace ge::core;

std::string parseString(std::string data){
  static struct ParserData{
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

Token::Token(
    Type type,
    std::string rawData,
    unsigned linePosition,
    unsigned charPositionInLine,
    unsigned charPositionInFile){
  //std::cerr<<"Token::Token()"<<std::endl;
  this->_type               = type              ;
  this->_rawData            = rawData           ;
  this->_linePosition       = linePosition      ;
  this->_charPositionInLine = charPositionInLine;
  this->_charPositionInFile = charPositionInFile;

  switch(this->_type){
    case  INTEGER:
      this->_iData = std::atoll(this->_rawData.c_str());
      break;
    case FLOAT:
      this->_fData = (float)std::atof(this->_rawData.c_str());
      break;
    case STRING:
      this->_rawData = this->_rawData.substr(1,this->_rawData.size()-1);
      this->_sData=parseString(this->_rawData);
      break;
    case CHAR:
      //TODO
      break;
    case IDENTIFIER:
      if(this->_rawData == "for"    )this->_type = KEY_FOR    ;
      if(this->_rawData == "while"  )this->_type = KEY_WHILE  ;
      if(this->_rawData == "if"     )this->_type = KEY_IF     ;
      if(this->_rawData == "else"   )this->_type = KEY_ELSE   ;
      if(this->_rawData == "bool"   )this->_type = KEY_BOOL   ;
      if(this->_rawData == "i8"     )this->_type = KEY_I8     ;
      if(this->_rawData == "i16"    )this->_type = KEY_I16    ;
      if(this->_rawData == "i32"    )this->_type = KEY_I32    ;
      if(this->_rawData == "i64"    )this->_type = KEY_I64    ;
      if(this->_rawData == "u8"     )this->_type = KEY_U8     ;
      if(this->_rawData == "u16"    )this->_type = KEY_U16    ;
      if(this->_rawData == "u32"    )this->_type = KEY_U32    ;
      if(this->_rawData == "u64"    )this->_type = KEY_U64    ;
      if(this->_rawData == "f32"    )this->_type = KEY_F32    ;
      if(this->_rawData == "f64"    )this->_type = KEY_F64    ;
      if(this->_rawData == "void"   )this->_type = KEY_VOID   ;
      if(this->_rawData == "struct" )this->_type = KEY_STRUCT ;
      if(this->_rawData == "typedef")this->_type = KEY_TYPEDEF;
      break;
    default:
      break;
  }
}

std::string Token::str()const{
  std::stringstream ss;
  ss<<this->_type;
  switch(this->_type){
    case INTEGER:
    case FLOAT:
    case STRING:
    case CHAR:
    case IDENTIFIER:
      ss<<"("<<this->_rawData<<")";
    default:
      break;
  }
  return ss.str();
}
