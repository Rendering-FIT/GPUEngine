#pragma once

#include <geSG/Export.h>
#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <geUtil/Interpolator.h>
#include <geSG/AnimationKeyFrame.h>


namespace ge
{ 
   namespace sg{

      class GESG_EXPORT AnimationChannel
      {
      public:
         AnimationChannel();


         virtual void update(double t) = 0;

         virtual ~AnimationChannel();
      protected:

      };



      inline glm::quat interpolateSLerp(const glm::quat& a, const glm::quat& b, double t)
      {
         return glm::slerp(a, b, static_cast<float>(t));
      }

      class GESG_EXPORT MovementAnimationChannel : public AnimationChannel
      {
      public:

         typedef AnimationKeyFrameTemplate<glm::vec3> Vec3KeyFrame;
         typedef AnimationKeyFrameTemplate<glm::quat> QuatKeyFrame;

         MovementAnimationChannel();

         virtual void update(double t);

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
         std::unique_ptr<ge::util::Interpolator> _interpolator;

      };
   }
}