#pragma once

#include<vector>
#include<iostream>
#include<fstream>

std::vector<std::vector<std::string>>loadCSV(std::string const&fileName);

template<typename T>
void saveCSV(std::string const&fileName,std::vector<std::vector<T>>const&data){
  std::ofstream f(fileName.c_str());
  for(auto const&l:data){
    bool first = true;
    for(auto const&x:l){
      if(first)first = false;
      else f<<",";
      f<<x;
    }
    f<<std::endl;
  }
  f.close();
}
