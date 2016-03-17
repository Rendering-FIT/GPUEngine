#include<geCore/text.h>
#include<fstream>
#include<iostream>
#include<string>

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
