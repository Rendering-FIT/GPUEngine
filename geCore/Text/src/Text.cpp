#include<fstream>
#include<iostream>
#include<string>

#include<GPUEngine/geCore/FSA/FSA.h>
#include<GPUEngine/geCore/MealyMachine/MealyMachine.h>
#include<GPUEngine/geCore/ErrorPrinter/ErrorPrinter.h>


#include<GPUEngine/geCore/Text/Text.h>

using namespace ge::core;

std::string ge::core::loadTextFile(std::string const&fileName){
  std::ifstream f(fileName.c_str());
  if(!f.is_open()){
    ge::core::printError(GE_CORE_FCENAME,"cannot open file",fileName);
    return "";
  }
  std::string str((std::istreambuf_iterator<char>(f)),std::istreambuf_iterator<char>());
  f.close();
  return str;
}

std::string ge::core::processEscapeSequences(std::string const&data){
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

bool ge::core::isNan(std::string const&text){
  return std::set<std::string>({"NAN","Nan","nan"}).count(text)>0;
}

bool ge::core::isInfinity(std::string const&text){
  return std::set<std::string>({"inf","Inf","INF","+inf","+Inf","+INF","-inf","-Inf","-INF"}).count(text)>0;
}


bool ge::core::isFloat(std::string const&text){
  if(isNan(text))return true;
  if(isInfinity(text))return true;
  MealyMachine mm;

  auto start            = mm.addState();
  auto sign             = mm.addState();
  auto immediateDot     = mm.addState();
  auto fractionalNumber = mm.addState();
  auto wholeNumber      = mm.addState();
  auto exponent         = mm.addState();
  auto postfix          = mm.addState();
  auto exponentSign     = mm.addState();
  auto exponentNumber   = mm.addState();

  mm.addTransition   (start           ,"+-"   ,sign            );
  mm.addTransition   (start           ,"."    ,immediateDot    );
  mm.addTransition   (start           ,"0","9",wholeNumber     );
  mm.addTransition   (sign            ,"."    ,immediateDot    );
  mm.addTransition   (sign            ,"0","9",wholeNumber     );
  mm.addTransition   (immediateDot    ,"0","9",fractionalNumber);
  mm.addTransition   (wholeNumber     ,"0","9",wholeNumber     );
  mm.addTransition   (wholeNumber     ,"."    ,fractionalNumber);
  mm.addTransition   (wholeNumber     ,"fF"   ,postfix         );
  mm.addTransition   (wholeNumber     ,"eE"   ,exponent        );
  mm.addTransition   (fractionalNumber,"0","9",fractionalNumber);
  mm.addTransition   (fractionalNumber,"fF"   ,postfix         );
  mm.addTransition   (fractionalNumber,"eE"   ,exponent        );
  mm.addEOFTransition(postfix                                  );
  mm.addTransition   (exponent        ,"+-"   ,exponentSign    );
  mm.addTransition   (exponent        ,"0","9",exponentNumber  );
  mm.addTransition   (exponentSign    ,"0","9",exponentNumber  );
  mm.addTransition   (exponentNumber  ,"0","9",exponentNumber  );
  mm.addTransition   (exponentNumber  ,"fF"   ,postfix         );
  mm.setQuiet(true);

  return mm.match(text.c_str());
}

bool ge::core::isDouble(std::string const&text){
  if(isNan(text))return true;
  if(isInfinity(text))return true;
  MealyMachine mm;

  auto start            = mm.addState();
  auto sign             = mm.addState();
  auto immediateDot     = mm.addState();
  auto fractionalNumber = mm.addState();
  auto wholeNumber      = mm.addState();
  auto exponent         = mm.addState();
  auto exponentSign     = mm.addState();
  auto exponentNumber   = mm.addState();

  mm.addTransition   (start           ,"+-"   ,sign            );
  mm.addTransition   (start           ,"."    ,immediateDot    );
  mm.addTransition   (start           ,"0","9",wholeNumber     );
  mm.addTransition   (sign            ,"."    ,immediateDot    );
  mm.addTransition   (sign            ,"0","9",wholeNumber     );
  mm.addTransition   (immediateDot    ,"0","9",fractionalNumber);
  mm.addTransition   (wholeNumber     ,"0","9",wholeNumber     );
  mm.addTransition   (wholeNumber     ,"."    ,fractionalNumber);
  mm.addTransition   (wholeNumber     ,"eE"   ,exponent        );
  mm.addEOFTransition(wholeNumber                              );
  mm.addTransition   (fractionalNumber,"0","9",fractionalNumber);
  mm.addTransition   (fractionalNumber,"eE"   ,exponent        );
  mm.addEOFTransition(fractionalNumber                         );
  mm.addTransition   (exponent        ,"+-"   ,exponentSign    );
  mm.addTransition   (exponent        ,"0","9",exponentNumber  );
  mm.addTransition   (exponentSign    ,"0","9",exponentNumber  );
  mm.addTransition   (exponentNumber  ,"0","9",exponentNumber  );
  mm.addEOFTransition(exponentNumber                           );
  mm.setQuiet(true);

  return mm.match(text.c_str());

}

bool ge::core::isFloatingPoint(std::string const&text){
  return isFloat(text) || isDouble(text);
}

bool ge::core::isIntegral(std::string const&text){
  return isInt(text) || isUint(text);
}

bool ge::core::isInt(std::string const&text){
  MealyMachine mm;

  auto start = mm.addState();
  auto sign  = mm.addState();
  auto digs  = mm.addState();

  mm.addTransition(start,"+-"   ,sign);
  mm.addTransition(start,"0","9",digs);

  mm.addTransition(sign,"0","9",digs);

  mm.addTransition(digs,"0","9",digs);
  mm.addEOFTransition(digs);
  mm.setQuiet(true);

  return mm.match(text.c_str());
}

bool ge::core::isUint(std::string const&text){
  MealyMachine mm;

  auto start = mm.addState();
  auto sign  = mm.addState();
  auto digs  = mm.addState();

  mm.addTransition(start,"+"    ,sign);
  mm.addTransition(start,"0","9",digs);

  mm.addTransition(sign,"0","9",digs);

  mm.addTransition(digs,"0","9",digs);
  mm.addEOFTransition(digs);
  mm.setQuiet(true);

  return mm.match(text.c_str());
}

bool ge::core::isString(std::string const&){
  return true;
}
