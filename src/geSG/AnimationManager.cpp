#include <geSG/AnimationManager.h>
#include <algorithm>
#include <chrono>

using namespace ge::sg;
using namespace ge::core;


/**
 * Updates each animation to time point t. 
 */
void AnimationManager::update(const time_point& t)
{
   std::for_each(playlist.begin(), playlist.end(), [t](std::shared_ptr<Animation> animation){animation->update(t); });
   removeFinishedAnimation();
}

/**
 * Not implemented. 
 */
void AnimationManager::pauseAnimation(std::shared_ptr<Animation>
   /*animation*/& )
{
}

/**
 * Adds the animation to the play list and starts the animation.
 */
void AnimationManager::playAnimation(std::shared_ptr<Animation>& animation, const time_point& startTime)
{
   auto it = std::find(playlist.begin(), playlist.end(), animation);
   if(it == playlist.end())
   {
      playlist.push_back(animation);
   }
   animation->start(startTime);
}

/**
 * Removes finished animations from manager. This method is called at the end
 * of the update method.
 */
void AnimationManager::removeFinishedAnimation()
{
   auto it = playlist.begin();
   for(; it != playlist.end(); )
   {
      if((*it)->getCurrentTime() >= (*it)->duration && (*it)->mode == Animation::Mode::ONCE)
      {
         auto rm = it;
         ++it;
         playlist.erase(rm);
      }
      else
      {
         ++it;
      }
   }
}
