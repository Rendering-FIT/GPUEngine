#include<geUtil/ArgumentManager/ArgumentManager.h>

#include<fstream>
#include<limits>
#include<sstream>
#include <cctype>

using namespace ge::util;

template<typename T>void pvec(std::vector<T>vec){
  bool start=true;
  for(auto x:vec){
    if(start)start=false;
    else std::cout<<", ";
    std::cout<<x;
  }
  std::cout<<std::endl;
}

ArgumentManager::ArgumentManager(int num,char*args[]){
  std::vector<std::string>arg;
  for(int i=0;i<num;++i)
    arg.push_back(std::string(args[i]));

  bool hasArgumentFile;
  do{
    hasArgumentFile=false;
    for(unsigned i=0;i<arg.size();++i)
      if(arg[i]=="<"){
        if(i+1>=arg.size()){
          std::cerr<<"expected filename after <"<<std::endl;
          break;
        }
        std::vector<std::string>newArgs;
        //std::cout<<"file: #"<<arg[i+1]<<"#"<<std::endl;
        this->_loadArgs(newArgs,arg[++i]);
        hasArgumentFile=true;
        std::vector<std::string>withLoadedFile;
        for(unsigned j=0;j<i-1;++j)withLoadedFile.push_back(arg[j]);
        for(auto x:newArgs)withLoadedFile.push_back(x);
        for(unsigned j=i+1;j<arg.size();++j)withLoadedFile.push_back(arg[j]);
        arg.clear();
        for(auto x:withLoadedFile)arg.push_back(x);
        break;
      }
  }while(hasArgumentFile);
  for(auto x:arg){
    this->_arguments.push_back(x);
    //std::cout<<x<<std::endl;
  }
  /*
  
  
  {
    std::string arg=std::string(args[i]);
    if(arg=="<"){
      if(i+1>=num){
        std::cerr<<"expected filename after <"<<std::endl;
        break;
      }
      std::vector<std::string>newArgs;
      this->_loadArgs(newArgs,args[++i]);
      for(auto x:newArgs)this->_arguments.push_back(x);

    }else{
      if(arg=="\\<")arg="<";
      this->_arguments.push_back(arg);
    }
  }
  */
  this->_parse(this->_arguments,"");
}

ArgumentManager::~ArgumentManager(){
  for(auto x:this->_data)
    delete x.second;
}

std::string ArgumentManager::toStr(){
  std::stringstream ss;
  for(auto x:this->_data)
    ss<<x.first<<" "<<x.second->toStr()<<std::endl;
  return ss.str();
}

ArgumentManager::Iterator ArgumentManager::begin(){
  return this->_data.begin();
}

ArgumentManager::Iterator ArgumentManager::end  (){
  return this->_data.end();
}

ArgumentManager::ConstIterator ArgumentManager::begin()const{
  return this->_data.begin();
}

ArgumentManager::ConstIterator ArgumentManager::end  ()const{
  return this->_data.end();
}


std::string ArgumentManager::_getFullName(std::string prefix,std::string name){
  if(prefix=="")return name;
  return prefix+"."+name;
}

void ArgumentManager::_tokenize(std::vector<std::string>&tokens,std::string file){
  enum{
    STATE_S,
    STATE_E,
    STATE_W,
    STATE_C,
    STATE_ESC
  }actState=STATE_S;
  std::string actWord="";
  unsigned pos=0;
  while(pos<file.size()){
    char ch=file[pos++];
    switch(actState){
      case STATE_S:
        if(std::isspace(ch)||ch=='\n'||ch=='\r')actState=STATE_E;
        else if(ch=='#')actState=STATE_C;
        else{actWord+=ch;actState=STATE_W;}
        break;
      case STATE_E:
        if(std::isspace(ch)||ch=='\n'||ch=='\r')actState=STATE_E;
        else if(ch=='#')actState=STATE_C;
        else{actWord+=ch;actState=STATE_W;}
        break;
      case STATE_W:
        if(ch=='\\')actState=STATE_ESC;
        else if(ch=='#')actState=STATE_C;
        else if(std::isspace(ch)||ch=='\n'||ch=='\r'){tokens.push_back(actWord);actWord="";actState=STATE_E;}
        else actWord+=ch;
        break;
      case STATE_C:
        if(ch=='\n'||ch=='\r')actState=STATE_E;
        break;
      case STATE_ESC:
        actWord+=ch;
        actState=STATE_W;
        break;
    }
  }
  if(actWord!="")tokens.push_back(actWord);
  /*
  std::cout<<"############"<<std::endl;
  for(auto x:tokens)
    std::cout<<x<<std::endl;
  std::cout<<"############"<<std::endl<<std::endl;
  // */
}

void ArgumentManager::_loadArgs(std::vector<std::string>&args,std::string file){
  std::ifstream f(file.data());//otevreme soubor
  if(!f.good()){
    std::cerr<<"file "<<file<<" is corrupted or does not exist"<<std::endl;
    return;
  }
  f.seekg(0,std::ios::end);//jdeme na konec
  std::streamoff len=f.tellg();//tak tu mame delku (pozice hlavy)
  f.seekg(0,std::ios::beg);//navrat na zacatek
  unsigned char*data=new unsigned char[len+1];//alokace dat
  f.read((char*)data,len);//precteni souboru
  f.close();//zavreme soubor
  data[len]='\0';
  std::string strData((const char*)data);
  //if(data[len]=='\0')std::cerr<<"jo je konec"<<std::endl;
  //else std::cerr<<"neni konec"<<std::endl;
  delete[]data;
  this->_tokenize(args,strData);
}

bool ArgumentManager::_toBOOL  (bool&              data,std::string input){
  if     (input=="true" )data=true ;
  else if(input=="false")data=false;
  else return false;
  return true;
}

bool ArgumentManager::_toI8    (char&              data,std::string input){
  data=(char)std::atoi(input.c_str());
  return true;
}

bool ArgumentManager::_toI16   (short&             data,std::string input){
  data=(short)std::atoi(input.c_str());
  return true;
}
bool ArgumentManager::_toI32   (int&               data,std::string input){
  data=std::atoi(input.c_str());
  return true;
}
bool ArgumentManager::_toI64   (long long int&     data,std::string input){
  data=std::atoi(input.c_str());
  return true;
}
bool ArgumentManager::_toU8    (unsigned char&     data,std::string input){
  data=(unsigned char)std::atoi(input.c_str());
  return true;
}
bool ArgumentManager::_toU16   (unsigned short&    data,std::string input){
  data=(unsigned short)std::atoi(input.c_str());
  return true;
}
bool ArgumentManager::_toU32   (unsigned int&      data,std::string input){
  data=std::atoi(input.c_str());
  return true;
}
bool ArgumentManager::_toU64   (unsigned long long&data,std::string input){
  data=std::atoi(input.c_str());
  return true;
}
bool ArgumentManager::_toF32   (float&data,std::string input){
  if(input[0]=='-')data=-(float)std::atof(input.substr(1).c_str());
  if(
      input=="inf" ||
      input=="INF" ||
      input=="Inf" )
    data=std::numeric_limits<float>::infinity();
  else if( 
      input=="nan" ||
      input=="NAN" ||
      input=="NaN" )
    data=std::numeric_limits<float>::quiet_NaN();
  else data=(float)std::atof(input.c_str());
  return true;
}
bool ArgumentManager::_toF64   (double&data,std::string input){
  if(input[0]=='-')data=-std::atof(input.substr(1).c_str());
  if(
      input=="inf" ||
      input=="INF" ||
      input=="Inf" )
    data=std::numeric_limits<double>::infinity();
  else if( 
      input=="nan" ||
      input=="NAN" ||
      input=="NaN" )
    data=std::numeric_limits<double>::quiet_NaN();
  else data=std::atof(input.c_str());
  return true;
}

void ArgumentManager::_parse(std::vector<std::string>&args,std::string name){
  //std::cerr<<"_PARSE"<<std::endl;
  //<PARSE>         ::= <START>
  //<START>         ::= e
  //<START>         ::= <ARGUMENT> <VALUE>     <START>
  //<START>         ::= <ARGUMENT> { <START> } <START>
  //<VALUE>         ::= bool       <ARGUMENT>
  //<VALUE>         ::= i8         <ARGUMENT>
  //<VALUE>         ::= i16        <ARGUMENT>
  //<VALUE>         ::= i32        <ARGUMENT>
  //<VALUE>         ::= i64        <ARGUMENT>
  //<VALUE>         ::= u8         <ARGUMENT>
  //<VALUE>         ::= u16        <ARGUMENT>
  //<VALUE>         ::= u32        <ARGUMENT>
  //<VALUE>         ::= u64        <ARGUMENT>
  //<VALUE>         ::= f32        <ARGUMENT>
  //<VALUE>         ::= f64        <ARGUMENT>
  //<VALUE>         ::= string     <ARGUMENT>
  //<VALUE>         ::= [          <SAME_VALUES> ]
  //<VALUE>         ::= struct     { <VALUES> }
  //<SAME_VALUES>   ::= <VALUE>
  //<SAME_VALUES>   ::= <VALUE> <SAME_VALUES>
  //<VALUES>        ::= <VALUE>
  //<VALUES>        ::= <VALUE> <VALUES>
  //<ARGUMENT>      ::= .+
  unsigned pos=0;
  this->_START(args,pos,name);//<PARSE> ::= <START>
  if(pos!=args.size())
    std::cerr<<"expected end of arguments"<<std::endl;
}

void printStatus(std::string fceName,std::vector<std::string>&args,unsigned&pos){
  std::cout<<"ArgumentManager::"<<fceName<<std::endl;
  pvec(args);
  std::cout<<pos<<std::endl;
}

bool ArgumentManager::_START(std::vector<std::string>&args,unsigned&pos,std::string prefix){
  //printStatus("_START",args,pos);

  auto falseBranch=[](std::string error){std::cerr<<"ArgumentManager::_START: "<<error<<std::endl;return false;};

  if(args.size()<=pos)return true;

  std::string name=args[pos];
  pos++;
  if(args.size()<=pos)return falseBranch("expected value after name: \""+name+"\", or {");
  if(args[pos]=="{"){
    pos++;
    if(!this->_START(args,pos,this->_getFullName(prefix,name)))
      return false;
    if(args.size()<=pos || args[pos]!="}")return falseBranch("expected }");
    pos++;
  }else{
    ArgData*data=this->_VALUE(args,pos);
    if(!data)return false;
    this->_data[this->_getFullName(prefix,name)]=data;
  }
  if(args.size()<=pos)return true;
  if(args[pos]=="}")return true;
  return this->_START(args,pos,prefix);
}


#define DEF_NONTERM_TYPE(FCE,MFCE,TYPE)\
  ArgData*ArgumentManager::_##FCE (std::vector<std::string>&args,unsigned&pos){\
    if(args.size()<=pos+1||args[pos]!=MFCE)return NULL;\
    TYPE data;\
    if(!this->_to##FCE(data,args[pos+1])){std::cerr<<"can't convert "<<args[pos+1]<<" to "<<MFCE<<std::endl;return NULL;}\
    pos+=2;\
    ArgData*ptr=new BaseData<TYPE>(data);\
    return ptr;\
  }

DEF_NONTERM_TYPE(BOOL,"bool",bool              )
DEF_NONTERM_TYPE(I8  ,"i8"  ,char              )
DEF_NONTERM_TYPE(I16 ,"i16" ,short             )
DEF_NONTERM_TYPE(I32 ,"i32" ,int               )
DEF_NONTERM_TYPE(I64 ,"i64" ,long long int     )
DEF_NONTERM_TYPE(U8  ,"u8"  ,unsigned char     )
DEF_NONTERM_TYPE(U16 ,"u16" ,unsigned short    )
DEF_NONTERM_TYPE(U32 ,"u32" ,unsigned          )
DEF_NONTERM_TYPE(U64 ,"u64" ,unsigned long long)
DEF_NONTERM_TYPE(F32 ,"f32" ,float             )
DEF_NONTERM_TYPE(F64 ,"f64" ,double            )

/*
   ArgData*ArgumentManager::_F32 (std::vector<std::string>&args,unsigned&pos){
//printStatus("_FLOAT",args,pos);
if(args.size()<=pos+1||args[pos]!="f32")return NULL;
float data;
if(!this->_toF32(data,args[pos+1])){std::cerr<<"can't convert "<<args[pos+1]<<" to f32"<<std::endl;return NULL;}
pos+=2;
ArgData*ptr=new BaseData<float>(data);
return ptr;
}

ArgData*ArgumentManager::_I32   (std::vector<std::string>&args,unsigned&pos){
//printStatus("_INT",args,pos);
if(args.size()<=pos+1||args[pos]!="i8")return NULL;
int data;
if(!this->_toI32(data,args[pos+1])){std::cerr<<"can't convert "<<args[pos+1]<<" to i8"<<std::endl;return NULL;}
pos+=2;
return new BaseData<int>(data);
}
*/

ArgData*ArgumentManager::_STRING(std::vector<std::string>&args,unsigned&pos){
  //printStatus("_STRING",args,pos);
  if(args.size()<=pos+1||args[pos]!="string")return NULL;
  pos+=2;
  return new BaseData<std::string>(args[pos-1]);
}

ArgData*ArgumentManager::_ARRAY (std::vector<std::string>&args,unsigned&pos){
  //printStatus("_ARRAY",args,pos);
  if(args.size()<pos||args[pos]!="[")return NULL;
  unsigned lastPos=pos;
  pos++;
  ArgData*result=this->_SAME_VALUES(args,pos);
  if(!result||args.size()<=pos||args[pos]!="]"){
    delete result;
    std::cerr<<"expected ]"<<std::endl;
    pos=lastPos;
    return NULL;
  }
  pos++;
  return result;
}

ArgData*ArgumentManager::_STRUCT(std::vector<std::string>&args,unsigned&pos){
  //printStatus("_STRUCT",args,pos);
  if(args.size()<pos+1||args[pos]!="struct"||args[pos+1]!="{")return NULL;
  unsigned lastPos=pos;
  pos+=2;
  ArgData*result=this->_VALUES(args,pos);
  if(!result||args.size()<=pos||args[pos]!="}"){
    delete result;
    std::cerr<<"expected }"<<std::endl;
    pos=lastPos;
    return NULL;
  }
  pos++;
  return result;
}

ArgData*ArgumentManager::_VALUE(std::vector<std::string>&args,unsigned&pos){
  //printStatus("_VALUE",args,pos);
  ArgData*result;
  if((result=this->_BOOL  (args,pos)))return result;
  if((result=this->_I8    (args,pos)))return result;
  if((result=this->_I16   (args,pos)))return result;
  if((result=this->_I32   (args,pos)))return result;
  if((result=this->_I64   (args,pos)))return result;
  if((result=this->_U8    (args,pos)))return result;
  if((result=this->_U16   (args,pos)))return result;
  if((result=this->_U32   (args,pos)))return result;
  if((result=this->_U64   (args,pos)))return result;
  if((result=this->_F32   (args,pos)))return result;
  if((result=this->_F64   (args,pos)))return result;
  if((result=this->_STRING(args,pos)))return result;
  if((result=this->_ARRAY (args,pos)))return result;
  if((result=this->_STRUCT(args,pos)))return result;
  //std::cerr<<"expected float, int, string, [ or struct"<<std::endl;
  return NULL;
}


ArgData*ArgumentManager::_SAME_VALUES(std::vector<std::string>&args,unsigned&pos){
  //printStatus("_SAME_VALUES",args,pos);
  if(args.size()<=pos){
    std::cerr<<"ArgumentManager::_SAME_VALUES: expected some values"<<std::endl;
    return NULL;
  }
  ArgData*firstItem=this->_VALUE(args,pos);
  if(!firstItem){
    std::cerr<<"ArgumentManager::_SAME_VALUES: expected at least one item"<<std::endl;
    return NULL;
  }
  ArrayData*result=new ArrayData(firstItem->getType());
  result->add(firstItem);
  ArgData*newItem=NULL;
  while(pos<args.size()&&args[pos]!="]"){
    newItem=this->_VALUE(args,pos);
    if(!newItem)break;
    if(!newItem->sameType(firstItem)){
      std::cerr<<"ArgumentManager::_SAME_VALUES: array has to contains one type of values"<<std::endl;
      return NULL;
    }
    result->add(newItem);
  }
  return result;
}

ArgData*ArgumentManager::_VALUES(std::vector<std::string>&args,unsigned&pos){
  //printStatus("_VALUES",args,pos);
  if(args.size()<=pos){
    std::cerr<<"ArgumentManager::_VALUES: expected some values"<<std::endl;
    return NULL;
  }
  ArgData*firstItem=this->_VALUE(args,pos);
  if(!firstItem){
    std::cerr<<"ArgumentManager::_VALUES: expected at least one item"<<std::endl;
    return NULL;
  }
  StructData*result=new StructData();
  result->add(firstItem);
  ArgData*newItem=NULL;
  while(pos<args.size()&&args[pos]!="]"){
    newItem=this->_VALUE(args,pos);
    if(!newItem)break;
    result->add(newItem);
  }
  return result;
}

