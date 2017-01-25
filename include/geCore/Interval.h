#pragma once

#include<type_traits>
#include<iostream>
#include<sstream>

template<typename TYPE>
class Interval{
  public:
    enum IntervalType{CLOSED,LEFT_OPEN,RIGHT_OPEN,OPEN,};
    Interval(){}
    Interval(
        TYPE         const&leftEndPoint          ,
        TYPE         const&rightEndPoint         ,
        IntervalType const&type          = CLOSED):_leftEndPoint(leftEndPoint),_rightEndPoint(rightEndPoint),_type(type){
      assert((leftEndPoint<rightEndPoint)||(leftEndPoint==rightEndPoint&&type==CLOSED));
    }
    Interval(
        TYPE const&leftEndPoint ,
        TYPE const&rightEndPoint,
        bool const&leftOpen     ,
        bool const&rightOpen    ):Interval(leftEndPoint,rightEndPoint,createType(leftOpen,rightOpen)){}
    Interval(
        TYPE const&value):Interval(value,value){}
    bool contain(TYPE const&value)const{
      assert(this!=nullptr);
      return
        (value>this->_leftEndPoint    &&value< this->_rightEndPoint)|| 
        (!this->isLeftOpen ()&&value==this->_leftEndPoint)|| 
        (!this->isRightOpen()&&value==this->_rightEndPoint);
    }
    bool contain(Interval<TYPE>const&other)const{
      assert(this!=nullptr);
      return this->contain(other.getLeft()) && this->contain(other.getRight());
    };
    static bool isSuccessor(TYPE const&value,TYPE const&nextValue){
      if(!std::is_integral<TYPE>::value)return false;
      return value+1==nextValue;
    }
    static IntervalType createType(bool leftOpen,bool rightOpen){
      if( leftOpen &&  rightOpen)return OPEN;
      if( leftOpen && !rightOpen)return LEFT_OPEN;
      if(!leftOpen &&  rightOpen)return RIGHT_OPEN;
      return CLOSED;
    }
    bool isLeftOpen   ()const{assert(this!=nullptr);return this->_type == OPEN || this->_type == LEFT_OPEN;}
    bool isRightOpen  ()const{assert(this!=nullptr);return this->_type == OPEN || this->_type == RIGHT_OPEN;}
    bool isLeftClosed ()const{assert(this!=nullptr);return !this->isLeftOpen()  ;}
    bool isRightClosed()const{assert(this!=nullptr);return !this->isRightOpen() ;}
    bool isClosed     ()const{assert(this!=nullptr);return this->_type == CLOSED;}
    bool isOpen       ()const{assert(this!=nullptr);return this->_type == OPEN  ;}
    IntervalType getType()const{assert(this!=nullptr);return this->_type;}
    void setType(IntervalType const&type){assert(this!=nullptr);this->_type = type;}
    TYPE getLeft()const{assert(this!=nullptr);return this->_leftEndPoint;}
    TYPE getRight()const{assert(this!=nullptr);return this->_rightEndPoint;}
    void setLeft(TYPE const&value){assert(this!=nullptr);this->_leftEndPoint = value;}
    void setRight(TYPE const&value){assert(this!=nullptr);this->_rightEndPoint = value;}
    bool isJoinable(Interval<TYPE>const&other)const{
      assert(this!=nullptr);
      if(this->getLeft()> other.getRight())
        return isSuccessor(other.getRight(),this->getLeft());
      if(this->getLeft()==other.getRight())
        return !other.isRightOpen() || !this->isLeftOpen();
      if(this->getRight()< other.getLeft())
        return isSuccessor(this->getRight(),other.getLeft());
      if(this->getRight()==other.getLeft())
        return !this->isRightOpen() || !other.isLeftOpen();
      return this->contain(other.getLeft()) || other.contain(this->getLeft());
    }
    Interval<TYPE>join(Interval<TYPE>const&other)const{
      assert(this!=nullptr);
      assert(this->isJoinable(other));
      if(this->contain(other.getLeft()) && this->contain(other.getRight()))
        return *this;
      if(other.contain(this->_leftEndPoint) && other.contain(this->_rightEndPoint))
        return other;
      if(this->contain(other.getLeft()))
        return Interval<TYPE>(this->getLeft(),other.getRight(),this->isLeftOpen(),other.isRightOpen());
      if(other.contain(this->getLeft()))
        return Interval<TYPE>(other.getLeft(),this->getRight(),other.isLeftOpen(),this->isRightOpen());
      if(this->getLeft()<other.getLeft())
        return Interval<TYPE>(this->getLeft(),other.getRight(),this->isLeftOpen(),other.isRightOpen());
      return Interval<TYPE>(other.getLeft(),this->getRight(),other.isLeftOpen(),this->isRightOpen());
    }
    std::string toStr()const{
      assert(this!=nullptr);
      std::stringstream ss;
      if(this->getLeft() == this->getRight()){
        ss<<this->getLeft();
        return ss.str();
      }
      if(this->isLeftOpen())ss<<"(";
      else ss<<"[";
      ss<<this->getLeft()<<","<<this->getRight();
      if(this->isRightOpen())ss<<")";
      else ss<<"]";
      return ss.str();
    }
  protected:
    TYPE         _leftEndPoint;
    TYPE         _rightEndPoint;
    IntervalType _type;
};


