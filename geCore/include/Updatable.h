#pragma once

#include <chrono>

namespace ge
{
   namespace core
   {
      /*This alias does not work when you need - time_point t = time_point::clock::now() - type conversion error!!!! (maybe a bug)*/
      //using time_point = std::chrono::time_point<std::chrono::steady_clock, std::chrono::steady_clock::duration>;
      using time_unit = std::chrono::duration<double>; ///< Basic duration used in GE. Time unit doubles of seconds.
      using time_point = std::chrono::time_point<std::chrono::steady_clock, time_unit>; ///< Time point on steady clock of time_unit

      /**
       * Simple convenient class to convert an arbitrary duration to our time_unit. Wrapper of duration_cast<>.
       */
      //template<typename Duration>
      //inline time_unit toTimeUnit(const Duration& tp){ return std::chrono::duration_cast<time_unit>(tp); }

      /**
       * Takes time in _Rep (e.g. doubles) of time_units (seconds by default) and returns time_unit representation of this value.
       */
      template<typename _Rep = double,typename ratio = time_unit::period>
      inline time_unit toTimeUnit(const _Rep& tp){ return std::chrono::duration_cast<time_unit>(std::chrono::duration<_Rep, ratio>(tp)); }

      /**
       * Convenience function to convert time_point to type FP that could be staticaly casted from time_point's duration::period
       * for Animation key frame interpolation purposes.
       */
      template<typename FP = float>
      inline FP TPtoFP(const time_point& tp) { return static_cast<FP>(tp.time_since_epoch().count()); }

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