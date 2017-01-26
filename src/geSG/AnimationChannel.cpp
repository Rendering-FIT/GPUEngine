#include <geSG/AnimationChannel.h>
#include <algorithm>
#include <chrono>
#include <array>
#include <glm/gtc/matrix_transform.hpp>

using namespace ge::sg;
using namespace ge::core;

AnimationChannel::AnimationChannel()
{}

AnimationChannel::~AnimationChannel()
{}

///////////////////////////////////////////////////////////////////////////

/**
 * Sets up LinearKeyframeInterpolator for orientation and scale and spherical linear interpolation for the orientation.
 */
MovementAnimationChannel::MovementAnimationChannel()
   : positionInterpolator(new ge::sg::LinearKeyframeInterpolator<std::vector<Vec3KeyFrame>>())
   , orientationInterpolator(new ge::sg::SlerpKeyframeInterpolator<std::vector<QuatKeyFrame>>())
   , scaleInterpolator(new ge::sg::LinearKeyframeInterpolator<std::vector<Vec3KeyFrame>>())
{
   
}


/**
 * Updates the target matrix. This function should not be called directly from the end user code.
 * It is better to use channels through Animation.
 * \param t Animation relative time.
 */
void MovementAnimationChannel::update(const time_point& t)
{
   glm::vec3 position;
   glm::vec3 scale(1, 1, 1);
   glm::quat oriantation;

   position = positionInterpolator->interpolate(positionKF, TPtoFP(t));
   if(!scaleKF.empty())
      scale = scaleInterpolator->interpolate(scaleKF, TPtoFP(t));
   oriantation = orientationInterpolator->interpolate(orientationKF, TPtoFP(t));


   glm::mat4 mat = glm::mat4_cast(oriantation);
   mat = glm::scale(mat, scale);
   mat[3] = glm::vec4(position, 1.f);

   if(_target)
      *_target = mat;
}


/**
 * Computes the duration of this channel. It takes the maximal t from the last key frame of
 * all containers.
 * \return Duration in core::time_unit.
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
