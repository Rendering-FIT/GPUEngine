#include <geSG/AnimationChannel.h>
#include <algorithm>
#include <iostream>

using namespace ge::sg;
using namespace ge::core;

AnimationChannel::AnimationChannel()
{}

AnimationChannel::~AnimationChannel()
{}

///////////////////////////////////////////////////////////////////////////

MovementAnimationChannel::MovementAnimationChannel()
   : _interpolator(new ge::util::LinearInterpolator())
{
   
}

void MovementAnimationChannel::update(time_unit t)
{
   glm::vec3 position;
   glm::vec3 scale(1,1,1);
   glm::quat oriantation;

   if(!positionKF.empty()){
      if(positionKF.size() > 1)
      {
         auto it = std::lower_bound(positionKF.begin(), positionKF.end(), t, positionKF[0]);
         if(it == positionKF.end()){
            //return positionKF.back().val;
            position = positionKF.back().val;
         }
         else if(it == positionKF.begin()){
            //return positionKF[0].val
            position = positionKF.front().val;
         }
         else if(positionKF.size() > 1){
            //position = interpolateLinear<Vec3KeyFrame, float>(*(it-1), *it, t);
            position = it->val;
         }
      }
      else
      {
         position = positionKF.back().val;
      }
   }

   if(!scaleKF.empty()){
      if(scaleKF.size() > 1)
      {
         auto it = std::lower_bound(scaleKF.begin(), scaleKF.end(), t, scaleKF[0]);
         if(it == scaleKF.end()){
            //return scaleKF.back().val;
            scale = scaleKF.back().val;
         }
         else if(it == scaleKF.begin()){
            //return scaleKF[0].val
            scale = scaleKF.front().val;
         }
         else{
            //scale = interpolateLinear<Vec3KeyFrame, float>(*(it - 1), *it, t);
            scale = it->val;
         }
      }
      else
      {
         scale = scaleKF.back().val;
      }
   }

   if(!orientationKF.empty()){
      if(orientationKF.size() > 1)
      {
         auto it = std::lower_bound(orientationKF.begin(), orientationKF.end(), t, orientationKF[0]);
         if(it == orientationKF.end()){
            //return orientationKF.back().val;
            oriantation = orientationKF.back().val;
         }
         else if(it == orientationKF.begin()){
            //return orientationKF[0].val
            oriantation = orientationKF.front().val;
         }
         else{
            /*QuatKeyFrame& a = *(it - 1);
            QuatKeyFrame& b = *it;
            double dn_t = (double)(t - a.t) / (b.t - a.t); //TODO unused?
            oriantation = interpolateSLerp(a.val, b.val, dn_t);*/
            oriantation = it->val;
         }
      }
      else
      {
         oriantation = orientationKF.back().val;
      }
   }

   glm::mat4 mat = glm::mat4_cast(oriantation);
   mat[0][0] *= scale.x; mat[0][1] *= scale.y; mat[0][2] *= scale.z;
   mat[1][0] *= scale.x; mat[1][1] *= scale.y; mat[1][2] *= scale.z;
   mat[2][0] *= scale.x; mat[2][1] *= scale.y; mat[2][2] *= scale.z;
   mat[3][0] = position.x; mat[3][1] = position.y; mat[3][2] = position.z;

   //TBD write mat to target
   if(_target)
      *_target = mat;//glm::transpose(mat);
}

MovementAnimationChannel::~MovementAnimationChannel()
{
}
