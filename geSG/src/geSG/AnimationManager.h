#pragma once

#include <geSG/Export.h>
#include <geSG/Animation.h>

#include <vector>
#include <list>
#include <memory>
#include <chrono>

namespace ge
{
   namespace sg{

      /**
       * Simple class responsible for playing (updating) animations. Only currently played
       * animations are held in the manager. When animation is done it is automaticaly removed.
       * 
       */
      class GESG_EXPORT AnimationManager: public core::Updatable
      {
      public:

         template<class Rep, class Period = std::ratio<1>>
         void playAnimation(std::shared_ptr<Animation>& animation, const std::chrono::duration<Rep, Period>& duration)
         {
            playAnimation(animation, core::time_point(std::chrono::duration_cast<core::time_point::duration>(duration)));
         }

         template<class Rep, class Period = std::ratio<1>>
         void update(const std::chrono::duration<Rep, Period>& duration)
         {
            update(core::time_point(std::chrono::duration_cast<core::time_point::duration>(duration)));
         }

         virtual void update(const core::time_point& t) override;
         void pauseAnimation(std::shared_ptr<Animation>& animation);
         void playAnimation(std::shared_ptr<Animation>& animation, const core::time_point& startTime);

         virtual ~AnimationManager(){}

      protected:

         std::list<std::shared_ptr<Animation>> playlist; ///< list of all playing animation, needs to be list for convenient cleanup

      private:
         void removeFinishedAnimation();

      };
   }
}
