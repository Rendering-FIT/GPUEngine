#pragma once

#include <geSG/Export.h>
#include <memory>
#include <vector>
#include <geUtil/macros.h>
#include <geCore/Updatable.h>
#include <chrono>

namespace ge
{
   namespace sg{
      class AnimationChannel;

      /**
       * Basic animation which groups particular channels. The init
       * should set the duration, mode and add some channels. Befor each 
       * replay you need to set start time to 0 (default constructed time_point).
       * The correct startTime is properly on the first (of current replay)
       * update invocation.
       */
      class GESG_EXPORT Animation : public ge::core::Updatable
      {
      public:
         ENUM_CLASS_FRIEND_OPERATOR(Mode, ONCE, LOOP);

         Animation();

         template<class Rep, class Period = std::ratio<1>>
         void start(const std::chrono::duration<Rep, Period>& duration)
         {
            start(core::time_point(std::chrono::duration_cast<core::time_point::duration>(duration)));
         }

         virtual void start(const core::time_point& t = core::time_point());

         template<class Rep, class Period = std::ratio<1>>
            void update(const std::chrono::duration<Rep, Period>& duration)
         {
            update(core::time_point(std::chrono::duration_cast<core::time_point::duration>(duration)));
         }

         void update(const core::time_point& t = core::time_point()) override;

         inline core::time_point getCurrentTime(){ return currentTime; }

         std::vector<std::shared_ptr<AnimationChannel>> channels;

         Mode mode;
         core::time_unit duration;

         core::time_point currentTime; //animation relative time
         core::time_point startTime; ///< simulation time of animation start
      protected:
      };
   }
}
