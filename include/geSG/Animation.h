#pragma once

#include <geSG/Export.h>
#include <memory>
#include <vector>
#include <geUtil/macros.h>

namespace ge
{
   namespace sg{
      class AnimationChannel;

      class GESG_EXPORT Animation
      {
      public:
         ENUM_CLASS_FRIEND_OPERATOR(Mode, ONCE, LOOP);

         Animation();

         void update(double t);

         inline double getCurrentTime(){ return currentTime; }

         std::vector<std::shared_ptr<AnimationChannel>> channels;

         Mode mode;
         double duration;

         double currentTime; //animation relative time
      protected:
      };
   }
}
