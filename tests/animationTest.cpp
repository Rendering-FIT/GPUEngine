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

      //! [target]
      shared_ptr<glm::mat4> matrix = make_shared<glm::mat4>(); //animation target
      //! [target]
      //! [animation]
      shared_ptr<Animation> animation = make_shared<Animation>(); //animation
      //! [animation]
      //! [channel]
      shared_ptr<MovementAnimationChannel> mvch = make_shared<MovementAnimationChannel>(); //movement channel
      mvch->setTarget(matrix); //set target the channel is manipulating
      animation->channels.push_back(mvch); // connects movement channel to this animation - one channel can be shared with multiple animations
      //! [channel]
      //! [KF]
      mvch->positionKF.emplace_back(time_point(0s), tr0); // translation goes from tr0 to tr1 in one sec
      mvch->positionKF.emplace_back(1.0s, tr1);

      mvch->orientationKF.emplace_back(0s, glm::angleAxis(0.f, glm::vec3(0, 1, 0))); //rotation goes from 0 to pi/2 (90 deg) in one sec around the Y axis
      mvch->orientationKF.emplace_back(0.5s, glm::angleAxis(glm::quarter_pi<float>(), glm::vec3(0, 1, 0)));
      mvch->orientationKF.emplace_back(1s, glm::angleAxis(glm::half_pi<float>(), glm::vec3(0, 1, 0)));

      mvch->scaleKF.emplace_back(0ms,sc0); //scale goes from 1 to 2 uniform scale but since the interpolator is set to nearest neighbor the value jumps discretely at 0.5s
      mvch->scaleKF.emplace_back(1000.0ms, sc1);
      //! [KF]

      //! [interpolator]
      mvch->scaleInterpolator.reset(new NearestKeyframeInterpolator<vector<MovementAnimationChannel::Vec3KeyFrame>>()); //changes the default linear interpolator to a nearest one
      //! [interpolator]

      //! [manager]
      unique_ptr<AnimationManager> manager(new AnimationManager); // creates animation manager to manage our test animation
      //! [manager]

      //begin animation
      //! [start]
      manager->playAnimation(animation, 0s); // gives manager the animatio we want to play, in the real example the time (secong argument) would probably be something like std::chrono::system_clock::now or Application::getCurrentTime() or even better ge::core::time_point::clock::now()
      //! [start]
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
         //! [update1]
         manager->update(std::chrono::duration<double>(0.45)); //same as before - in real app there would be the simulation or real time as a parameter to the manager update function
         //! [update1]

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
         //! [update2]
         /* since the last key frame of the animation is scheduled at 1.0s and the animation is set to run only once by default
          * the last keyframes from all containers are selected. This behavior could be changed through making an interpolator class
          * in such way that it for example extrapolates.
          * The animation manager also removes the animation from it's playlist, since the animation has finished. If you want to play
          * it again, then you need to call AnimationManaget::play() again.
          */
         manager->update(1.7s);
         //! [update2]

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

/**
 * \example Animation
 * This example is also a unit test for animation. <br/>
 * First, we need to have something to animate, this is called a target. It could be anything. Mostly, animations
 * are used to move objects so we will use a transform matrix as our target.
 * \snippet tests/animationTest.cpp target
 * Then, we create our animation object. Animation objects are normaly part of the ge::sg::Scene, loaded from a file.
 * \snippet tests/animationTest.cpp animation
 * Animation is a compilation of channels which actualy do the work. The animation only does transformation of application/simulation
 * time to <em>animation relative</em> time, the time that goes from start of the animation to its end. The end of the animation is
 * considered the last point in time that will try to change the target - the chronologicaly last key frame. In animation relative
 * time this is also the animation duration. The animation also manages the mode of the animation ge::sg::Animation::Mode <br/>
 * We create a single movement channel ge::sg::MovementAnimationChannel, set its target and give it to animation. You can share the channels.
 * The channel also implements the ge::core::Updatable interface but its update() methos takes the relative time as argument. The main
 * task of the channel is to update the target with the newly computed value. 
 * \snippet tests/animationTest.cpp channel
 * The channel is driven by one or more collections of key frames. Management of the key frames is handled by the channel.
 * Mostly, it will be a std::vector of ge::sg::AnimationKeyFrameTemplate. In our example we fill all three of those. But the 
 * MovementAnimationChannel can work with any combination of empty/filled containers. Simply, the frame containers that you don't fill will
 * not influence the target matrix.
 * \snippet tests/animationTest.cpp KF
 * The key frame is a structure that contains a \p value_type value assigned to the specific time. The generalization of the key frame is 
 * ge::core::KeyPointInterface. The value is interpolated from the key frames during the update. The interpolation is driven by
 * ge::sg::KeyframeInterpolator class. By default, the interpolation is linear or spherical linear for rotation. You can change it any time.
 * \snippet tests/animationTest.cpp interpolator
 * To run the animation we can use the animation or even the channel directly, but ge::sg::AnimationManager can handle
 * this task.
 * \snippet tests/animationTest.cpp manager
 * Every time you want to start the animation over you need to call start() method on it with the application time as argument. Then
 * you can call update(), also with application/simulation time. The animation framework runs on std::chrono. Basic interface for this
 * framework is ge::core::Updatable. This application/simulation time is your application relative time, which could be
 * time measured from app start or simply real time. The animation simply marks down the start time as the animation relative 0 and each update
 * is then related to this start, so the channels gets their relative time. The manager calls the start() for us when we call playAnimation().
 * The manager also temporarily puts the animation pointer to it's play list. When you call update() on manager it updates all animations it has.
 * Once the animation is finished, the manager simply removes it. You need to keep the animation elsewhere, usualy in the ge::sg::Scene, but
 * you can have your own framework.
 * \snippet tests/animationTest.cpp start
 * Start and update functions in manager and animation are overloaded for convenience so you can feed them with not only the time_point
 * but also a time_unit. The conversion is automatic.
 * \snippet tests/animationTest.cpp update1
 * You can also use literals.
 * \snippet tests/animationTest.cpp update2
 * But in application you will use something like this:
 * \code{.cpp}
 *    // -STL standard-
 *    manager->update(time_point::clock::now);
 *    // -or-
 *    manager->update(time_unit(SDL_GetTicks()));
 *    //...
 * \endcode
 * 
 * \see include/geCore/Updatable.h ge::sg::AnimationManager
 */
