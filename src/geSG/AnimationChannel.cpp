#include <geSG/AnimationChannel.h>
#include <algorithm>
#include <chrono>
#include <array>
#include <glm/gtc/matrix_transform.inl>

using namespace ge::sg;
using namespace ge::core;

AnimationChannel::AnimationChannel()
{}

AnimationChannel::~AnimationChannel()
{}

///////////////////////////////////////////////////////////////////////////

/**
 * Sets up NearestKeyframeInterpolator for all key frames.
 */
MovementAnimationChannel::MovementAnimationChannel()
   : positionInterpolator(new ge::sg::NearestKeyframeInterpolator<std::vector<Vec3KeyFrame>, core::time_point >())
   , orientationInterpolator(new ge::sg::NearestKeyframeInterpolator<std::vector<QuatKeyFrame>, core::time_point >())
   , scaleInterpolator(new ge::sg::NearestKeyframeInterpolator<std::vector<Vec3KeyFrame>, core::time_point >())
{
   
}


/**
 * Updates the target matrix.
 * \param t Animation relative time.
 */
void MovementAnimationChannel::update(const time_point& t)
{
   glm::vec3 position;
   glm::vec3 scale(1, 1, 1);
   glm::quat oriantation;

   position = positionInterpolator->interpolate(positionKF, t);
   if(!scaleKF.empty())
      scale = scaleInterpolator->interpolate(scaleKF, t);   
   oriantation = orientationInterpolator->interpolate(orientationKF, t);


   glm::mat4 mat = glm::mat4_cast(oriantation);
   mat = glm::scale(mat, scale);
   mat[3] = glm::vec4(position, 1.f);

   if(_target)
      *_target = mat;
}


/**
 * Computes the duration of this channel. It takes the maximal t from the last key frame of
 * all containers.
 * \return Duration in core::time_unit
 */
time_unit MovementAnimationChannel::getDuration() const
{
   std::array<core::time_point, 3> endFrameTimes;
   endFrameTimes[0] = positionKF.empty() ? time_point() : positionKF.back().getTime();
   endFrameTimes[1] = orientationKF.empty() ? time_point() : orientationKF.back().getTime();
   endFrameTimes[2] = scaleKF.empty() ? time_point() : scaleKF.back().getTime();
   return std::chrono::duration_cast<time_unit>(std::max_element(endFrameTimes.begin(),endFrameTimes.end())->time_since_epoch());
}

MovementAnimationChannel::~MovementAnimationChannel()
{
}
