#pragma once

#include <fstream>
#include <iostream>

namespace ge {
  namespace vu {
    std::vector<char> loadBinary(std::string const & fileName) {
      std::ifstream f(fileName.c_str(), std::ios::binary);
      if (!f.is_open()) {
        std::string er = "File not found:" + fileName;
        //throw std::runtime_error(er.c_str());
        std::cerr << er << "\n";
        return std::vector<char>();
      }
      std::vector<char> data((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
      f.close();
      return data;
    }
  }
}