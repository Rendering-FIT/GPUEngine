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
