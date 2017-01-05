#pragma once

#include <chrono>

namespace ge
{
   namespace core
   {
      /*This alias does not work when you need - time_point t = time_point::clock::now() - type conversion error!!!! (maybe a bug)*/
      //using time_point = std::chrono::time_point<std::chrono::steady_clock, std::chrono::steady_clock::duration>;
      using time_point = std::chrono::steady_clock::time_point;
      using time_unit = std::chrono::milliseconds; ///< time unit is ms

      template<typename Duration>
      inline time_unit toTimeUnit(Duration tp){ return std::chrono::duration_cast<time_unit>(tp); }

      /**
       * Takes time in milliseconds and returns time_unit representation of this value.
       */
      template<typename ratio = std::milli>
      inline time_unit toTimeUnit(double tp){ return std::chrono::duration_cast<time_unit>(std::chrono::duration<double, ratio>(tp)); }

      /**
       * Pure virtual interface for "updatable" classes such as animations.
       * The implementation relies on std::chrono. Subclasses are forced to implement
       * only the update method.
       */
      class Updatable
      {
      public:
         virtual void update(const time_point& t = time_point()) = 0;
      };
   }
}