#include <geSG/Animation.h>
#include <geSG/AnimationChannel.h>

using namespace ge::sg;
using namespace ge::core;

Animation::Animation()
   : mode(Mode::ONCE)
   , currentTime(0)
   , startTime()
{
}

/**
 * Use to update all animation channels.
 * @param t Is the simulation time,
 *          but time in seconds from the animation beggining.
 */
void Animation::update(time_point t)
{
   if(startTime <= time_point()) startTime = t; //this is the first update so we set the start time to current t
   time_unit anim_time(std::chrono::duration_cast<time_unit>(t - startTime)); //relative time -> 0.0 is when the animation starts
   switch (mode)
   {
      case Mode::LOOP:
         anim_time = time_unit(anim_time.count() % duration.count());
         break;
      case Mode::ONCE:
      default:
         anim_time = anim_time > duration ? duration : anim_time;
         break;
   }

   currentTime = anim_time;

   for (auto channel : channels)
   {
      channel->update(anim_time);
   }
}
