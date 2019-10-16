#pragma once

#include<chrono>
#include<ctime>
#include<cassert>

namespace ge{
  namespace util{
    template<typename TYPE>
      class Timer{
        public:
          Timer(){
            assert(this!=nullptr);
            this->reset();
          }
          void reset(){
            assert(this!=nullptr);
            this->_start = std::chrono::high_resolution_clock::now();
            this->_last  = this->_start;
          }
          TYPE elapsedFromStart(){
            assert(this!=nullptr);
            auto newTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<TYPE> elapsed = newTime - this->_start;
            this->_last = newTime;
            return elapsed.count();
          }
          TYPE elapsedFromLast(){
            assert(this!=nullptr);
            auto newTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<TYPE> elapsed = newTime - this->_last;
            this->_last = newTime;
            return elapsed.count();
          }
        protected:
          std::chrono::time_point<std::chrono::high_resolution_clock>_start;
          std::chrono::time_point<std::chrono::high_resolution_clock>_last ;
      };
  }
}	
