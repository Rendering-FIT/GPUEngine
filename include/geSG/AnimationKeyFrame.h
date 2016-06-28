#pragma once

#include <geCore/Updatable.h>

namespace ge
{
   namespace sg{

      /**
       * Keyframe base class containing time stamp and ability to be compared on the 
       * time basis.
       */
      struct AnimationKeyFrame
      {
         AnimationKeyFrame() : t(0){}
         AnimationKeyFrame(core::time_unit time){ t = time; }

         inline bool operator()(const AnimationKeyFrame& a, const AnimationKeyFrame& b)
         {
            return a.t < b.t;
         }

         core::time_unit t;
      };

      /**
       * Keyframe with target value.
       */
      template<typename _ValueType>
      struct AnimationKeyFrameTemplate : public AnimationKeyFrame
      {
         typedef _ValueType value_type;

         AnimationKeyFrameTemplate() : AnimationKeyFrame(){}
         AnimationKeyFrameTemplate(core::time_unit time) : AnimationKeyFrame(time){}
         AnimationKeyFrameTemplate(core::time_unit time, const value_type& value)
            : AnimationKeyFrame(time)
         {
            val = value;
         }

         value_type val;
      };

      template < typename KeyFrameType >
      typename KeyFrameType::value_type interpolate()
      {
         return KeyFrameType::value_type();
      }

      /**
       * Linear interpolation base on t going from a.t to b.t.
       */
      template < typename KeyFrameType, typename T = double >
      typename KeyFrameType::value_type interpolateLinear(const KeyFrameType& a, const KeyFrameType& b, T t)
      {
         T dn_t = (t - a.t) / (b.t - a.t);
         if((b.t - a.t) == 0.0) return a.val;
         typename KeyFrameType::value_type ret = (1 - dn_t)*a.val + dn_t*b.val;
         return ret;
      }

      /**
       * Linear interpolation for std::chrono time, base on t going from a.t to b.t.
       */
      template < typename KeyFrameType, typename T = double >
      typename KeyFrameType::value_type interpolateLinear(const KeyFrameType& a, const KeyFrameType& b, core::time_unit t)
      {
         T dn_t = (T)((t - a.t).count()) / (b.t - a.t).count();
         if((b.t - a.t).count() == 0) return a.val;
         typename KeyFrameType::value_type ret = (1 - dn_t)*a.val + dn_t*b.val;
         return ret;
      }
   }
}