#pragma once

#include <geSG/Export.h>
#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <geUtil/Interpolator.h>
#include <geSG/AnimationKeyFrame.h>
#include <geCore/Updatable.h>


namespace ge
{ 
   namespace sg{

      /**
       * The part of an animation. Channel is responsible for updating one value
       * or group of values that makes sense together e.g. movement (position, orientation),
       * color.
       */
      class GESG_EXPORT AnimationChannel //: public ge::core::Updatable
      {
      public:
         AnimationChannel();


         virtual void update(core::time_unit t) = 0;

         virtual ~AnimationChannel();
      protected:

      };



      inline glm::quat interpolateSLerp(const glm::quat& a, const glm::quat& b, double t)
      {
         return glm::slerp(a, b, static_cast<float>(t));
      }

      /**
       * Channel for animating model matrix via translation, oriantation and scale keyframes.
       * There is currently no interpolation between keyframes (due to assimp animation not working
       * properly).
       */
      class GESG_EXPORT MovementAnimationChannel : public AnimationChannel
      {
      public:

         typedef AnimationKeyFrameTemplate<glm::vec3> Vec3KeyFrame;
         typedef AnimationKeyFrameTemplate<glm::quat> QuatKeyFrame;

         MovementAnimationChannel();

         virtual void update(core::time_unit t);

         inline void setTarget(std::shared_ptr<glm::mat4>& target){ _target = target; }
         inline std::shared_ptr<glm::mat4>& getTarget(){ return _target; }
         inline glm::mat4 getMatrixTarget(){ return *_target; }


         virtual ~MovementAnimationChannel();



      public:
         std::vector<Vec3KeyFrame> positionKF;
         std::vector<QuatKeyFrame> orientationKF;
         std::vector<Vec3KeyFrame> scaleKF;

      protected:
         std::shared_ptr<glm::mat4> _target;
         std::unique_ptr<ge::util::Interpolator> _interpolator; ///<not used;

      };
   }
}