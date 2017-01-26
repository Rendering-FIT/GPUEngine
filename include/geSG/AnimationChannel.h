#pragma once

#include <geSG/Export.h>
#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <geSG/KeyframeInterpolator.h>
#include <geSG/AnimationKeyFrame.h>
#include <geCore/Updatable.h>
#include <chrono>


namespace ge
{ 
   namespace sg{

      /**
       * The main part of an animation. Channel is responsible for updating one value
       * or group of values that makes sense together e.g. movement (position, orientation),
       * color. etc. Implements Updatable interface.
       */
      class GESG_EXPORT AnimationChannel : public ge::core::Updatable
      {
      public:
         AnimationChannel();


         /**
          * Updates the channe. This function should not be called directly from the end user code.
          * It is better to use channels through Animation.
          * \param t Animation relative time. This means that the time is related to animation start time or to 0, not to the real time clock. 
          */
         virtual void update(const core::time_point& t) = 0;


         /**
          * This function should compute and return the duration of this channel, this usualy equals the time of the last key frame.
          * Even if the first key frame doesn't beggins at 0s the animation always does.
          * \return Last time the channel can change its target. In another wors there should be no change to target after time_point(getDuration).
          */
         virtual core::time_unit getDuration() const = 0;

         virtual ~AnimationChannel();
      protected:

      };



      inline glm::quat interpolateSLerp(const glm::quat& a, const glm::quat& b, double t)
      {
         return glm::slerp(a, b, static_cast<float>(t));
      }

      /**
       * Channel for animating model matrix via translation, oriantation and scale keyframes.
       * The default interpolation is linear \see MovementAnimationChannel::MovementAnimationChannel
       */
      class GESG_EXPORT MovementAnimationChannel : public AnimationChannel
      {
      public:

         typedef AnimationKeyFrameTemplate<glm::vec3> Vec3KeyFrame;
         typedef AnimationKeyFrameTemplate<glm::quat> QuatKeyFrame;

         MovementAnimationChannel();

         virtual void update(const core::time_point& t);

         inline void setTarget(std::shared_ptr<glm::mat4>& target){ _target = target; }
         inline std::shared_ptr<glm::mat4>& getTarget(){ return _target; }
         inline glm::mat4 getTargetMatrix(){ return *_target; }
         core::time_unit getDuration() const override;

         virtual ~MovementAnimationChannel();



      public:
         std::vector<Vec3KeyFrame> positionKF;
         std::vector<QuatKeyFrame> orientationKF;
         std::vector<Vec3KeyFrame> scaleKF;
         std::unique_ptr<KeyframeInterpolator<std::vector<Vec3KeyFrame>>> positionInterpolator;
         std::unique_ptr<KeyframeInterpolator<std::vector<QuatKeyFrame>>> orientationInterpolator;
         std::unique_ptr<KeyframeInterpolator<std::vector<Vec3KeyFrame>>> scaleInterpolator;

      protected:
         std::shared_ptr<glm::mat4> _target;

      };
   }
}
