#include <geSG/Animation.h>
#include <geSG/AnimationChannel.h>
#include <geSG/AnimationManager.h>
#include <memory>

#include <glm/gtc/matrix_transform.hpp>

using namespace std;
using namespace ge::sg;
using namespace ge::core;


#define CATCH_CONFIG_MAIN
#include "catch.hpp"

SCENARIO("Aniamtion Movement channel interpolation test","[Animation]")
{
   GIVEN("Simple position and movement animation")
   {
      glm::vec3 tr1(1, 2, 4), tr0(0,0,0); //translations for two key frames
      glm::vec3 sc0(1, 1, 1), sc1(2, 2, 2); //scales for two key frames
      glm::vec3 curr_tr;
      glm::quat r0 = glm::angleAxis(0.f, glm::vec3(0, 1, 0)), // rotation quats
                r1 = glm::angleAxis(glm::quarter_pi<float>(), glm::vec3(0, 1, 0)), 
                r2 = glm::angleAxis(glm::half_pi<float>(), glm::vec3(0, 1, 0));
      glm::quat curr_q;

      shared_ptr<glm::mat4> matrix = make_shared<glm::mat4>(); //animation target
      shared_ptr<Animation> animation = make_shared<Animation>(); //animation
      shared_ptr<MovementAnimationChannel> mvch = make_shared<MovementAnimationChannel>(); //movement channel
      mvch->setTarget(matrix); //set target the channel is manipulating
      animation->channels.push_back(mvch); // connects movement channel to this animation - one channel can be shared with multiple animations
      mvch->positionKF.emplace_back(time_point(0s), tr0); // translation goes from tr0 to tr1 in one sec
      mvch->positionKF.emplace_back(1.0s, tr1);

      mvch->orientationKF.emplace_back(0s, glm::angleAxis(0.f, glm::vec3(0, 1, 0))); //rotation goes from 0 to pi/2 (90 deg) in one sec around the Y axis
      mvch->orientationKF.emplace_back(0.5s, glm::angleAxis(glm::quarter_pi<float>(), glm::vec3(0, 1, 0)));
      mvch->orientationKF.emplace_back(1s, glm::angleAxis(glm::half_pi<float>(), glm::vec3(0, 1, 0)));

      mvch->scaleKF.emplace_back(0ms,sc0); //scale goes from 1 to 2 uniform scale but since the interpolator is set to nearest neighbor the value jumps discretely at 0.5s
      mvch->scaleKF.emplace_back(1000.0ms, sc1);

      mvch->scaleInterpolator.reset(new NearestKeyframeInterpolator<vector<MovementAnimationChannel::Vec3KeyFrame>>()); //changes the default linear interpolator to a nearest one

      unique_ptr<AnimationManager> manager(new AnimationManager); // creates animation manager to manage our test animation

      //begin animation
      manager->playAnimation(animation, 0s); // gives manager the animatio we want to play, in the real example the time (secong argument) would probably be something like std::chrono::system_clock::now or Application::getCurrentTime() or even better ge::core::time_point::clock::now()
      WHEN("animation starts through manager at time 0s")
      {
         //tests
         curr_tr = glm::vec3((*matrix.get())[3]);
         glm::mat4 rot = glm::mat4_cast(r0);
         THEN("translation should be tr0")
         {
            REQUIRE(tr0 == curr_tr);
         }
      }
      WHEN("In time 0.45s")
      {
         manager->update(std::chrono::duration<double>(0.45)); //same as before - in real app there would be the simulation or real time as a parameter to the manager update function

         //tests
         curr_tr = glm::vec3((*matrix.get())[3]);
         curr_q = glm::slerp(r0, r1, 0.45f / 0.5f);
         glm::mat4 rot = glm::mat4_cast(curr_q);
         bool rotation_mat_equiv = rot[0] == (*matrix)[0] && rot[1] == (*matrix)[1] && rot[2] == (*matrix)[2];
         REQUIRE(curr_tr == tr1*0.45f);
         REQUIRE(rotation_mat_equiv);
      }
      WHEN("Time is after the animation end 1.7s")
      {
         /* since the last key frame of the animation is scheduled at 1.0s and the animation is set to run only once by default
          * the last keyframes from all containers are selected. This behavior could be changed through making an interpolator class
          * in such way that it for example extrapolates.
          */
         manager->update(1.7s);

         //tests
         curr_tr = glm::vec3((*matrix.get())[3]);
         curr_q = r2;
         glm::mat4 rot = glm::mat4_cast(curr_q);
         rot = glm::scale(rot,sc1);
         bool rotation_mat_equiv = rot[0] == (*matrix)[0] && rot[1] == (*matrix)[1] && rot[2] == (*matrix)[2];
         THEN("Animation target should be updated to last key frame and animation is release from the manager")
         {
            REQUIRE(curr_tr == tr1);
            REQUIRE(rotation_mat_equiv);
         }
      }
   }
}
