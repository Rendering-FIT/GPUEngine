#include <geUtil/HighResolutionTimer.h>

ge::util::HighResolutionTimer::HighResolutionTimer()
{
	reset();
}

//Reset timer
void ge::util::HighResolutionTimer::reset()
{ 
	_start =  _last = std::chrono::high_resolution_clock::now();
}

double ge::util::HighResolutionTimer::getElapsedTimeSeconds()
{                    
	_stop = std::chrono::high_resolution_clock::now();
   _duration = _stop - _start;
   _last = _stop;

   return _duration.count() / TIMER_NS_PER_SECOND;
}

double ge::util::HighResolutionTimer::getElapsedTimeMilliseconds()
{
	_stop = std::chrono::high_resolution_clock::now();
   _duration = _stop - _start;
   _last = _stop;

   return _duration.count() / TIMER_NS_PER_MILLISECOND;
}

double ge::util::HighResolutionTimer::getElapsedTimeFromLastQuerySeconds()
{
   _stop = std::chrono::high_resolution_clock::now();
   _duration = _stop - _last;
   _last = _stop;

   return _duration.count() / TIMER_NS_PER_SECOND;
}

double ge::util::HighResolutionTimer::getElapsedTimeFromLastQueryMilliseconds()
{
   _stop = std::chrono::high_resolution_clock::now();
   _duration = _stop - _last;
   _last = _stop;

   return _duration.count() / TIMER_NS_PER_MILLISECOND;
}

double ge::util::HighResolutionTimer::getTimerPrecisionSeconds()
{
  return (double)std::chrono::high_resolution_clock::period::num / std::chrono::high_resolution_clock::period::den;
}
