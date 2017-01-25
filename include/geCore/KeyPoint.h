#pragma once

namespace ge
{
   namespace core
   {
      /**
       * KeyPoint is interface used as a basis for interpolation framework. Used it with conjuction with
       * interpolators to produce meaningful result. But it might be useful in different ways.
       * \tparam _FP Type of parameter space used for interpolation.
       */
      template<typename _FP = float>
      class KeyPointInterface
      {
      public:

         using parameter_type = _FP; ///< Type used for numerical interpolation. The real used parameter is converted to this for arithmetic operation.


         /**
          * Since the implementation of this interface can use any type of parameter it sees fit it allows to supply another type for
          * arithmetic computation purposes. This function allows others to get the internal type (e.g. time_point) transformed to type
          * that is more suitable for arithmetic purposes (e.g. float). It is used in animation key frame interpolators.
          * \return The parameter of the key point transformed to parameter_type.
          */
         virtual parameter_type getT() const = 0;

         virtual ~KeyPointInterface() = default;
      };

   }
}