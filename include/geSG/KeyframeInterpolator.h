#pragma once
#include <algorithm>

namespace ge
{
   namespace sg
   {

      /**
       * Base class for keyframe interpolation. 
       * \tparam KeyFrameContainer e.g. vector<AnimationKeyFrameTemplate<glm::vec3>>
       * \tparam T e.g. core::time_point
       */
      template<typename KeyFrameContainer, typename T>
      class KeyframeInterpolator
      {
      public:
         typedef typename KeyFrameContainer::value_type::value_type Value;

         virtual Value interpolate(const KeyFrameContainer& keyframes, const T& t) const = 0;

      };

      template<typename KeyFrameContainer, typename T>
      class NearestKeyframeInterpolator : public KeyframeInterpolator<KeyFrameContainer, T>
      {
      public:
         Value interpolate(const KeyFrameContainer& keyframes, const T& t) const override
         {
            if(keyframes.empty()) return Value();

            auto it = std::lower_bound(keyframes.begin(), keyframes.end(), t);
            if(it == keyframes.begin())
            {
               return it->getValue();
            }
            bool closerToPrevFrame = (it->getTime() - t) >= (t - (it - 1)->getTime());
            return (it - int(closerToPrevFrame))->getValue();
         }

      };

      /*template<typename KeyFrameContainer, typename T>
      class LinearKeyframeInterpolator : public KeyframeInterpolator<KeyFrameContainer, T>
      {
      public:
         Value interpolate(const KeyFrameContainer& keyframes, const T& t) const override
         {
            if(keyframes.empty()) return Value();


         }
      };*/
   }
}
