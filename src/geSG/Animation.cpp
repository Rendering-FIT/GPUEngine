#include <geSG/Animation.h>
#include <geSG/AnimationChannel.h>
#include <chrono>
#include <algorithm>

using namespace ge::sg;
using namespace ge::core;

Animation::Animation()
   : mode(Mode::ONCE)
   , duration(time_unit(0))
{
}

/**
 * Computes duration, sets start time to t and calls update with t. If the animation has no channels nothing is done.
 * The duration is computed as maximum time value (t) of all keyframes of all channels.
 * \param t 
 */
void Animation::start(const time_point& t)
{
   startTime = t;
   if(channels.empty()) {
      duration = time_unit(0);
      return;
   }
   auto it = std::max_element(channels.begin(), channels.end(), [](const std::shared_ptr<AnimationChannel>& a, const std::shared_ptr<AnimationChannel>& b) { return a->getDuration() < b->getDuration(); });
   duration = (**it).getDuration();
   update(t);
}

/**
 * Use to update all animation channels. If the animation has no channels nothing is done.
 * @param t Is the simulation time resp. aplication gloab time. The start time is then substracted
 *          from this t and determines the current animation (relative) time. All channels are fed
 *          this relative time.
 * 
 */
void Animation::update(const time_point& t)
{
   time_unit anim_time(std::chrono::duration_cast<time_unit>(t - startTime)); //relative time -> 0.0 is when the animation starts
   switch (mode)
   {
      case Mode::LOOP:
         anim_time = duration > time_unit(0) ? anim_time % duration : time_unit(0);
         break;
      case Mode::ONCE:
      default:
         anim_time = std::min(anim_time,duration);
         break;
   }

   currentTime = time_point(anim_time);

   for (auto channel : channels)
   {
      channel->update(currentTime);
   }
}
