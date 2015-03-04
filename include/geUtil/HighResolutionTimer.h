#ifndef _HIGHRESOLUTIONTIMER_H
#define _HIGHRESOLUTIONTIMER_H


#include <geUtil/Export.h>
#include <chrono>

/*
 * High Resolution Timer
 */

#define TIMER_NS_PER_SECOND 1000000000.0
#define TIMER_NS_PER_MILLISECOND 1000000.0

namespace ge
{
	namespace util
	{
      class GEUTIL_EXPORT HighResolutionTimer
		{
		private:

			std::chrono::high_resolution_clock::time_point _start, _stop, _last;
         std::chrono::duration<double, std::nano> _duration;

		public:

			HighResolutionTimer();/*
			{
				reset();
			}*/

			//Reset timer
			void reset();/*
			{ 
				_start =  _last = std::chrono::high_resolution_clock::now();
			}*/

			//Return elapsed times
			/*inline*/ double getElapsedTimeSeconds();/*
			{                    
				_stop = std::chrono::high_resolution_clock::now();
            _duration = _stop - _start;
            _last = _stop;

            return _duration.count() / TIMER_NS_PER_SECOND;
			}*/
         
			/*inline*/ double getElapsedTimeMilliseconds();/*
			{
				_stop = std::chrono::high_resolution_clock::now();
            _duration = _stop - _start;
            _last = _stop;

            return _duration.count() / TIMER_NS_PER_MILLISECOND;
			}*/

         //Interval measurements
         /*inline*/ double getElapsedTimeFromLastQuerySeconds();/*
         {
            _stop = std::chrono::high_resolution_clock::now();
            _duration = _stop - _last;
            _last = _stop;

            return _duration.count() / TIMER_NS_PER_SECOND;
         }*/

         /*inline*/ double getElapsedTimeFromLastQueryMilliseconds();/*
         {
            _stop = std::chrono::high_resolution_clock::now();
            _duration = _stop - _last;
            _last = _stop;

            return _duration.count() / TIMER_NS_PER_MILLISECOND;
         }*/

         //Get timer precision, may be system-dependant
         /*inline*/ double getTimerPrecisionSeconds();/*
         {
           return (double)std::chrono::high_resolution_clock::period::num / std::chrono::high_resolution_clock::period::den;
         }*/
		};
	}
}	

#endif