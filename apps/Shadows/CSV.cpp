#include"CSV.h"
#include<geCore/ErrorPrinter.h>
#include<sstream>

std::vector<std::vector<std::string>>loadCSV(std::string const&fileName){
  std::ifstream f(fileName.c_str());
  std::vector<std::vector<std::string>>ret;
  if(!f.is_open()){
    ge::core::printError(GE_CORE_FCENAME,"file cannot be opened",fileName);
    return ret;
  }
  std::string line;
  size_t largestLineLength = 0;
  while(std::getline(f,line)){
    std::istringstream linestream(line);
    std::string word;
    std::vector<std::string>words;
    while(std::getline(linestream,word,',')){
      words.push_back(word);
    }
    if(largestLineLength<words.size())largestLineLength=words.size();
    ret.push_back(words);
  }
  f.close();
  for(auto&line:ret)
    line.resize(largestLineLength,"");
  return ret;
}
