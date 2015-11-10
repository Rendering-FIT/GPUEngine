#pragma once

namespace ge
{
   namespace util{
      /**
       * Class that resamples the parametr t <0,1>.
       * For use in animation for ease motion.
       */
      class Interpolator
      {
      public:
         virtual double operator()(double t) = 0;
      };

      class LinearInterpolator : public Interpolator
      {
         virtual double operator()(double t) override
         {
            return t;
         }
      };
   }
}