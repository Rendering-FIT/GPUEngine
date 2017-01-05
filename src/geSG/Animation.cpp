#include <geSG/Animation.h>
#include <geSG/AnimationChannel.h>
#include <chrono>
#include <algorithm>

using namespace ge::sg;
using namespace ge::core;

Animation::Animation()
   : mode(Mode::ONCE)
   , currentTime(0)
   , startTime()
{
}

void Animation::start(const time_point& t)
{
   auto it = std::max_element(channels.begin(), channels.end(), [](const std::shared_ptr<AnimationChannel>& a, const std::shared_ptr<AnimationChannel>& b) { return a->getDuration() < b->getDuration(); });
   duration = (**it).getDuration();
   startTime = t;
   update(t);
}

/**
 * Use to update all animation channels.
 * @param t Is the simulation time,
 *          but time in seconds from the animation beggining.
 */
void Animation::update(const time_point& t)
{
   time_unit anim_time(std::chrono::duration_cast<time_unit>(t - startTime)); //relative time -> 0.0 is when the animation starts
   switch (mode)
   {
      case Mode::LOOP:
         anim_time = anim_time % duration;
         break;
      case Mode::ONCE:
      default:
         anim_time = std::min(anim_time,duration);
         break;
   }

   currentTime = anim_time;

   for (auto channel : channels)
   {
      channel->update(time_point(currentTime));
   }
}
