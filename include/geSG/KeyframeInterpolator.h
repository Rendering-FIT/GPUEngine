#pragma once
#include <algorithm>

namespace ge
{
   namespace sg
   {

      /**
       * Base class for keyframe interpolation. Interpolator is supplied to channels to
       * manipulate interpolation between key frames. Interpolation is based on parametr t
       * of type T and interpolates values of type Value.
       * \tparam KeyFrameContainer e.g. vector<AnimationKeyFrameTemplate<glm::vec3>>
       * \tparam T e.g. core::time_point.
       */
      template<typename KeyFrameContainer, typename T>
      class KeyframeInterpolator
      {
      public:
         using Value = typename KeyFrameContainer::value_type::value_type;

         virtual Value interpolate(const KeyFrameContainer& keyframes, const T& t) const = 0;

      };


      /**
       * Interpolates between two key frames and returns the value of the closest one.
       * \tparam KeyFrameContainer e.g. vector<AnimationKeyFrameTemplate<glm::vec3>>
       * \tparam T e.g. core::time_point. The value returned is not extrapolated,
       *           its clamped into the key frame container range.
       */
      template<typename KeyFrameContainer, typename T>
      class NearestKeyframeInterpolator : public KeyframeInterpolator<KeyFrameContainer, T>
      {
      public:
         using Value = typename KeyframeInterpolator<KeyFrameContainer,T>::Value;
         Value interpolate(const KeyFrameContainer& keyframes, const T& t) const override
         {
            if(keyframes.empty()) return Value();

            auto it = std::lower_bound(keyframes.begin(), keyframes.end() - 1, t);
            if(it == keyframes.begin())
            {
               return it->getValue();
            }
            /* if the t is closer to previous frame, than we need to substract 1 if not
             * then 0. That is what casting bool to int does. 
             */
            bool closerToPrevFrame = (it->getTime() - t) >= (t - (it - 1)->getTime());
            return (it - int(closerToPrevFrame))->getValue();
         }

      };

      /**
       * Interpolates between two key frames and returns the linear interpolation of theirs values.
       * \tparam KeyFrameContainer e.g. vector<AnimationKeyFrameTemplate<glm::vec3>>
       * \tparam T e.g. core::time_point. The value returned is not extrapolated,
       *           its clamped into the key frame container range.
       */
      template<typename KeyFrameContainer, typename T>
      class LinearKeyframeInterpolator : public KeyframeInterpolator<KeyFrameContainer, T>
      {
      public:
         using Value = typename KeyframeInterpolator<KeyFrameContainer,T>::Value;
         Value interpolate(const KeyFrameContainer& keyframes, const T& t) const override
         {
            if(keyframes.empty()) return Value();

            auto it = std::lower_bound(keyframes.begin(), keyframes.end() - 1, t);
            if(it == keyframes.begin() || t > it->getTime())
            {
               return it->getValue();
            }

            float dn_t = (float)((t - (it-1)->getTime()).count()) / (it->getTime() - (it-1)->getTime()).count();
            if((it->getTime() - (it-1)->getTime()).count() == 0) return (it-1)->getValue();
            Value ret = ((it-1)->getValue())*(1.0f - dn_t) + (it->getValue())*dn_t;
            return ret;
         }
      };

      /**
      * Interpolates between two key frames and returns the spherical linear interpolation of theirs values.
      * \tparam KeyFrameContainer e.g. vector<AnimationKeyFrameTemplate<glm::quat>>
      * \tparam T e.g. core::time_point. The value returned is not extrapolated,
      *           its clamped into the key frame container range.
      */
      template<typename KeyFrameContainer, typename T>
      class SlerpKeyframeInterpolator : public KeyframeInterpolator<KeyFrameContainer, T>
      {
      public:
         using Value = typename KeyframeInterpolator<KeyFrameContainer,T>::Value;
         Value interpolate(const KeyFrameContainer& keyframes, const T& t) const override
         {
            if(keyframes.empty()) return Value();

            auto it = std::lower_bound(keyframes.begin(), keyframes.end() - 1, t);
            if(it == keyframes.begin() || t > it->getTime())
            {
               return it->getValue();
            }

            float dn_t = (float)((t - (it - 1)->getTime()).count()) / (it->getTime() - (it - 1)->getTime()).count();
            if((it->getTime() - (it - 1)->getTime()).count() == 0) return (it - 1)->getValue();
            Value ret = glm::slerp((it-1)->getValue(),it->getValue(),dn_t);
            return ret;
         }
      };

   }
}
