#pragma once

namespace ge
{
   namespace sg{
      struct AnimationKeyFrame
      {
         AnimationKeyFrame() : t(0.0){}
         AnimationKeyFrame(double time){ t = time; }

         inline bool operator()(const AnimationKeyFrame& a, const AnimationKeyFrame& b)
         {
            return a.t < b.t;
         }

         double t;
      };

      template<typename _ValueType>
      struct AnimationKeyFrameTemplate : public AnimationKeyFrame
      {
         typedef _ValueType value_type;

         AnimationKeyFrameTemplate() : AnimationKeyFrame(){}
         AnimationKeyFrameTemplate(double time) : AnimationKeyFrame(time){}
         AnimationKeyFrameTemplate(double time, const value_type& value)
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

      template < typename KeyFrameType, typename T = double >
      typename KeyFrameType::value_type interpolateLinear(const KeyFrameType& a, const KeyFrameType& b, T t)
      {
         T dn_t = (t - a.t) / (b.t - a.t);
         if((b.t - a.t) == 0.0) return a.val;
         typename KeyFrameType::value_type ret = (1 - dn_t)*a.val + dn_t*b.val;
         return ret;
      }
   }
}