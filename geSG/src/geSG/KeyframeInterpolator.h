#pragma once
#include <algorithm>
#include <geCore/Updatable.h>

namespace ge
{
   namespace sg
   {

      /**
       * Base class for keyframe interpolation. Interpolator is supplied to channels to
       * manipulate interpolation between key frames. Interpolation is based on parametr t
       * of type T and interpolates values of type Value.
       * \tparam KeyFrameContainer Collection of partially ordered, operator< comaparable elements. Elements must have T getT() method
       *         and V getValue() method. T must have implmentet TDiff operator- such that TDiff has defined basic arithmetical operations (+,-,*,/).
       *         This is important for any non-nearest interpolation (from linear interpolation onward).
       *         e.g. vector<AnimationKeyFrameTemplate<glm::vec3>>
       * \tparam T e.g. core::time_point.
       */
      template<typename KeyFrameContainer>
      class KeyframeInterpolator
      {
      public:
         using Value = typename KeyFrameContainer::value_type::value_type;
         using parameter_type = typename KeyFrameContainer::value_type::parameter_type;

         virtual Value interpolate(const KeyFrameContainer& keyframes, const parameter_type & t) const = 0;

      };


      /**
       * Interpolates between two key frames and returns the value of the closest one.
       * \tparam KeyFrameContainer e.g. vector<AnimationKeyFrameTemplate<glm::vec3>>
       * \tparam T e.g. core::time_point. The value returned is not extrapolated,
       *           its clamped into the key frame container range.
       */
      template<typename KeyFrameContainer>
      class NearestKeyframeInterpolator : public KeyframeInterpolator<KeyFrameContainer>
      {
      public:
         using Value = typename KeyframeInterpolator<KeyFrameContainer>::Value;
         using T = typename KeyFrameContainer::value_type::T;
         using Keyframe = typename KeyFrameContainer::value_type;
         using parameter_type = typename KeyframeInterpolator<KeyFrameContainer>::parameter_type;

         Value interpolate(const KeyFrameContainer& keyframes, const parameter_type& t) const override
         {
            if(keyframes.empty()) return Value();

            auto it = std::lower_bound(keyframes.begin(), keyframes.end() - 1, Keyframe::convertToT(t));
            if(it == keyframes.begin())
            {
               return it->getValue();
            }
            /* if the t is closer to previous frame, than we need to substract 1 if not
             * then 0. That is what casting bool to int does. 
             */

            parameter_type t1 = (it - 1)->getT();
            parameter_type t2 = it->getT();
            bool closerToPrevFrame = (t2 - t) >= (t - t1);
            return (it - int(closerToPrevFrame))->getValue();
         }

      };

      /**
       * Interpolates between two key frames and returns the linear interpolation of theirs values.
       * \tparam KeyFrameContainer e.g. vector<AnimationKeyFrameTemplate<glm::vec3>>
       * \tparam T e.g. core::time_point. The value returned is not extrapolated,
       *           its clamped into the key frame container range.
       */
      template<typename KeyFrameContainer>
      class LinearKeyframeInterpolator : public KeyframeInterpolator<KeyFrameContainer>
      {
      public:
         using Value = typename KeyframeInterpolator<KeyFrameContainer>::Value;
         using T = typename KeyFrameContainer::value_type::T;
         using Keyframe = typename KeyFrameContainer::value_type;
         using parameter_type = typename KeyframeInterpolator<KeyFrameContainer>::parameter_type;

         Value interpolate(const KeyFrameContainer& keyframes, const parameter_type& t) const override
         {
            if(keyframes.empty()) return Value();

            auto it = std::lower_bound(keyframes.begin(), keyframes.end() - 1, Keyframe::convertToT(t));
            if(it == keyframes.begin() || t > it->getT())
            {
               return it->getValue();
            }

            parameter_type t1 = (it - 1)->getT();
            parameter_type t2 = it->getT();
            Value v1 = (it - 1)->getValue();
            Value v2 = it->getValue();

            Value ret = ((t2 - t) * v1 + (t - t1) * v2) / (t2 - t1);

            return ret;
         }
      };

      /**
      * Interpolates between two key frames and returns the spherical linear interpolation of theirs values.
      * \tparam KeyFrameContainer e.g. vector<AnimationKeyFrameTemplate<glm::quat>>
      * \tparam T e.g. core::time_point. The value returned is not extrapolated,
      *           its clamped into the key frame container range.
      */
      template<typename KeyFrameContainer>
      class SlerpKeyframeInterpolator : public KeyframeInterpolator<KeyFrameContainer>
      {
      public:
         using Value = typename KeyframeInterpolator<KeyFrameContainer>::Value;
         using T = typename KeyFrameContainer::value_type::T;
         using Keyframe = typename KeyFrameContainer::value_type;
         using parameter_type = typename KeyframeInterpolator<KeyFrameContainer>::parameter_type;

         Value interpolate(const KeyFrameContainer& keyframes, const parameter_type& t) const override
         {
            if(keyframes.empty()) return Value();

            auto it = std::lower_bound(keyframes.begin(), keyframes.end() - 1, Keyframe::convertToT(t));
            if(it == keyframes.begin() || t > it->getT())
            {
               return it->getValue();
            }

            parameter_type t1 = (it - 1)->getT();
            parameter_type t2 = it->getT();
            Value v1 = (it - 1)->getValue();
            Value v2 = it->getValue();

            parameter_type dn_t = (t - t1) / (t2 - t1);
            if((t2 - t1) < std::numeric_limits<parameter_type>::epsilon()) return v1;

            Value ret = glm::slerp(v1,v2,dn_t);
            return ret;
         }
      };

   }
}
