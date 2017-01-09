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
         AnimationKeyFrame() : t(){}
         AnimationKeyFrame(const core::time_point& time){ t = time; }

         template<class Rep, class Period = std::ratio<1>>
         AnimationKeyFrame(const std::chrono::duration<Rep, Period>& duration)
         {
            t = time_point(std::chrono::duration_cast<core::time_point::duration>(duration));
         }

         inline bool operator< (const AnimationKeyFrame& rhs) const
         {
            return this->t < rhs.t;
         }

         core::time_point getTime() const
         {
            return t;
         }

         core::time_point t;
      };

      /**
       * Keyframe with target value. Instantiate this class to create animation keys.
       */
      template<typename _ValueType>
      struct AnimationKeyFrameTemplate : public AnimationKeyFrame
      {
         typedef _ValueType value_type;

         AnimationKeyFrameTemplate() : AnimationKeyFrame(){}
         AnimationKeyFrameTemplate(const core::time_point& time) : AnimationKeyFrame(time){}
         AnimationKeyFrameTemplate(const core::time_point& time, const value_type& value)
            : AnimationKeyFrame(time)
         {
            val = value;
         }

         template<class Rep, class Period = std::ratio<1>>
         AnimationKeyFrameTemplate(const std::chrono::duration<Rep, Period>& duration, const value_type& value)
            : AnimationKeyFrame(duration)
         {
            val = value;
         }

         virtual value_type getValue() const
         {
            return val;
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