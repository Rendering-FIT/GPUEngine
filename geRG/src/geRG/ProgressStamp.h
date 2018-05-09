#ifndef GE_RG_PROGRESS_STAMP_H
#define GE_RG_PROGRESS_STAMP_H

namespace ge
{
   namespace rg
   {

      class ProgressStamp {
      protected:

         long long _value;

         explicit constexpr inline ProgressStamp(long long value);

      public:

         explicit constexpr inline operator long long() const;
         inline ProgressStamp operator++();
         inline ProgressStamp operator++(int);
         constexpr inline bool operator==(ProgressStamp rhs) const;
         constexpr inline bool operator!=(ProgressStamp rhs) const;

         constexpr inline ProgressStamp();
         static constexpr inline ProgressStamp invalid();

      };



      constexpr inline ProgressStamp::ProgressStamp(long long value) : _value(value)  {}
      constexpr inline ProgressStamp::operator long long() const  { return _value; }
      inline ProgressStamp ProgressStamp::operator++()  { _value=(_value+1)&0x7fffffffffffffff; return ProgressStamp(_value); }
      inline ProgressStamp ProgressStamp::operator++(int)  { long long r=_value; _value=(_value+1)&0x7fffffffffffffff; return ProgressStamp(r); }
      constexpr inline bool ProgressStamp::operator==(ProgressStamp rhs) const  { return _value==rhs._value; }
      constexpr inline bool ProgressStamp::operator!=(ProgressStamp rhs) const  { return _value!=rhs._value; }
      constexpr inline ProgressStamp::ProgressStamp() : _value(ProgressStamp::invalid())  {}
      constexpr inline ProgressStamp ProgressStamp::invalid()  { return ProgressStamp(-1); }

   }
}

#endif /* GE_RG_PROGRESS_STAMP_H */
