#pragma once

#include<geCore/Command.h>
#include<geDE/Export.h>
#include<cassert>
#include<set>

namespace ge{
  namespace de{
    class Body;
    class If;
    class While;
    class Function;
    class AtomicFunction;
    class /*GEDE_EXPORT*/ Statement: public ge::core::Command{
      friend class Body;
      friend class If;
      friend class While;
      friend class Function;
      friend class AtomicFunction;
      public:
        using Ticks = size_t;
        enum Type{
          FUNCTION,
          BODY    ,
          WHILE   ,
          IF      ,
        };
        Statement(Type const&type);
        virtual ~Statement();
        virtual void operator()()=0;
        void setDirty();
        void setSignalingDirty();
        bool isDirty()const;
        virtual Ticks getUpdateTicks()const;
        virtual void setUpdateTicks(Ticks ticks);
        bool hasSignalingSource(Statement*statement)const;
        bool hasSignalingTarget(Statement*statement)const;
        size_t nofSignalingSources()const;
        size_t nofSignalingTargets()const;
      protected:
        Type _type;
        bool _dirtyFlag = false;
        Ticks _updateTicks = 0;
        std::set<Statement*>_signalingSources;
        std::set<Statement*>_signalingTargets;
        void _addSignalingSource(Statement*statement);
        void _addSignalingTarget(Statement*statement);
        void _removeSignalingSource(Statement*statement);
        void _removeSignalingTarget(Statement*statement);
    };

    inline Statement::Statement(Type const&type){
      assert(this!=nullptr);
      this->_type = type;
    }

    inline Statement::~Statement(){
      for(auto const&x:this->_signalingSources)
        x->_removeSignalingTarget(this);
      for(auto const&x:this->_signalingTargets)
        x->_removeSignalingSource(this);
    }

    inline bool Statement::isDirty()const{
      assert(this!=nullptr);
      return this->_dirtyFlag;
    }

    inline void Statement::_addSignalingSource(Statement*statement){
      assert(this!=nullptr);
      this->_signalingSources.insert(statement);
    }

    inline void Statement::_removeSignalingSource(Statement*statement){
      assert(this!=nullptr);
      this->_signalingSources.erase(statement);
    }

    inline bool Statement::hasSignalingSource(Statement*statement)const{
      assert(this!=nullptr);
      return this->_signalingSources.count(statement)!=0;
    }

    inline void Statement::_addSignalingTarget(Statement*statement){
      assert(this!=nullptr);
      this->_signalingTargets.insert(statement);
    }

    inline void Statement::_removeSignalingTarget(Statement*statement){
      assert(this!=nullptr);
      this->_signalingTargets.erase(statement);
    }

    inline bool Statement::hasSignalingTarget(Statement*statement)const{
      assert(this!=nullptr);
      return this->_signalingTargets.count(statement)!=0;
    }


    inline size_t Statement::nofSignalingSources()const{
      assert(this!=nullptr);
      return this->_signalingSources.size();
    }

    inline size_t Statement::nofSignalingTargets()const{
      assert(this!=nullptr);
      return this->_signalingTargets.size();
    }

    inline void Statement::setDirty(){
      assert(this!=nullptr);
      this->_dirtyFlag = true;
      this->setSignalingDirty();
    }

    inline void Statement::setSignalingDirty(){
      assert(this!=nullptr);
      for(auto const&x:this->_signalingTargets)
        if(!x->isDirty())x->setDirty();
    }

    inline Statement::Ticks Statement::getUpdateTicks()const{
      assert(this!=nullptr);
      return this->_updateTicks;
    }

    inline void Statement::setUpdateTicks(Ticks ticks){
      assert(this!=nullptr);
      this->_updateTicks = ticks;
    }

  }
}

