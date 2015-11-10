#pragma once

#include <geSG/Export.h>
#include <geSG/Animation.h>

#include <vector>
#include <list>
#include <memory>

namespace ge
{
   namespace sg{

      class GESG_EXPORT AnimationManager
      {
      public:

         void addAnimation(std::shared_ptr<Animation>& animation);
         void removeAnimation(std::shared_ptr<Animation>animation);


         virtual void update(double t);
         void pauseAnimation(std::shared_ptr<Animation>animation);
         void playAnimation(std::shared_ptr<Animation>animation);

         virtual ~AnimationManager(){}

      protected:

         std::vector<std::shared_ptr<Animation>> animations;
         std::list<std::shared_ptr<Animation>> playlist;

      private:
         void removeFinishedAnimation();

         std::vector<std::list<std::shared_ptr<Animation>>::const_iterator> _toRemove;
      };
   }
}