#include <geSG/Animation.h>
#include <geSG/AnimationChannel.h>

using namespace ge::sg;

Animation::Animation()
   : currentTime(0.0)
   , mode(Mode::ONCE)
{
}

/**
 * Use to update all animation channels.
 * @param t Is time related to Animation time frame i.e. not the simulation time,
 *          but time in seconds from the animation beggining.
 */
void Animation::update(double t)
{
   switch (mode)
   {
      case Mode::LOOP:
         t = fmod(t, duration);
         break;
      case Mode::ONCE:
      default:
         t = t > duration ? duration : t;
         break;
   }

   currentTime = t;

   for (auto channel : channels)
   {
      channel->update(t);
   }
}