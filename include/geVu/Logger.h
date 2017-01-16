#pragma once

#include <geVu/geVuClasses.h>

//#include <functional>
#include <iostream>

namespace ge {
  namespace vu {
    template<class Head, class...Tail>
    void log(std::ostream& stream, Head head, Tail...tail) {
      stream << head << " ";
      log(stream, tail...);
    }

    template<class Head>
    void log(std::ostream& stream, Head head) {
      stream << head << "\n";
    }
  }
}

/*
class ge::vu::Logger {
protected:
  std::function<bool()> condition;
  std::ostream& stream;
public:
  Logger(std::function<bool()> condition = []() {return true;},
    std::ostream& stream = std::cout)
    :condition(condition),stream(stream){
  }

  template<class Head, class...Tail>
  void log(Head head, Tail...tail) {
    if (!condition())return;
    stream << head << " ";
    log(tail...);
  }

  template<class Head>
  void log(Head head) {
    if (!condition())return;
    stream << head << "\n";
  }
};*/