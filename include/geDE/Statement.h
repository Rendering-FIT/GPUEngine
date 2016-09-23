#pragma once

#include<geCore/Command.h>
#include<geDE/Export.h>
#include<geCore/CallStackPrinter.h>
#include<cassert>
#include<set>

namespace ge{
  namespace de{
    class Body;
    class If;
    class While;
    class Function;
    class AtomicFunction;
    class CompositeFunction;
    class /*GEDE_EXPORT*/ Statement: public ge::core::Command, public std::enable_shared_from_this<Statement>{
      friend class Body;
      friend class If;
      friend class While;
      friend class Function;
      friend class AtomicFunction;
      friend class CompositeFunction;
      public:
        using Ticks = size_t;
        enum Type{
          STATEMENT,
          FUNCTION ,
          BODY     ,
          WHILE    ,
          IF       ,
        };
        Statement(Type const&type = STATEMENT,bool ignoreDirty = false);
        virtual ~Statement();
        virtual void operator()();
        void setDirty();
        virtual void setSignalingDirty();
        bool isDirty()const;
        virtual Ticks getUpdateTicks()const;
        virtual void setUpdateTicks(Ticks ticks);
        bool hasSignalingSource(Statement*statement)const;
        bool hasSignalingTarget(Statement*statement)const;
        size_t nofSignalingSources()const;
        size_t nofSignalingTargets()const;
        virtual std::shared_ptr<Body>toBody()const;
        virtual std::shared_ptr<If>toIf()const;
        virtual std::shared_ptr<While>toWhile()const;
        virtual std::shared_ptr<Function>toFunction()const;
        virtual bool isIgnoringDirty()const;
        virtual void setIgnoreDirty(bool ignore = false);
      protected:
        Type _type;
        bool _dirtyFlag = false;
        Ticks _updateTicks = 0;
        bool _ignoreDirty = false;
        std::set<Statement*>_signalingSources;
        std::set<Statement*>_signalingTargets;
        virtual void _addSignalingSource(Statement*statement);
        virtual void _addSignalingTarget(Statement*statement);
        virtual void _removeSignalingSource(Statement*statement);
        virtual void _removeSignalingTarget(Statement*statement);
    };

    inline Statement::Statement(Type const&type,bool ignore){
      PRINT_CALL_STACK(type);
      assert(this!=nullptr);
      this->_type = type;
      this->_ignoreDirty = ignore;
    }

    inline Statement::~Statement(){
      PRINT_CALL_STACK();
      assert(this!=nullptr);
      for(auto const&x:this->_signalingSources)
        x->_removeSignalingTarget(this);
      for(auto const&x:this->_signalingTargets)
        x->_removeSignalingSource(this);
    }

    inline void Statement::operator()(){}

    inline bool Statement::isDirty()const{
      PRINT_CALL_STACK();
      assert(this!=nullptr);
      return this->_dirtyFlag;
    }

    inline void Statement::_addSignalingSource(Statement*statement){
      PRINT_CALL_STACK(statement);
      assert(this!=nullptr);
      this->_signalingSources.insert(statement);
    }

    inline void Statement::_removeSignalingSource(Statement*statement){
      PRINT_CALL_STACK(statement);
      assert(this!=nullptr);
      this->_signalingSources.erase(statement);
    }

    inline bool Statement::hasSignalingSource(Statement*statement)const{
      PRINT_CALL_STACK(statement);
      assert(this!=nullptr);
      return this->_signalingSources.count(statement)!=0;
    }

    inline void Statement::_addSignalingTarget(Statement*statement){
      PRINT_CALL_STACK(statement);
      assert(this!=nullptr);
      this->_signalingTargets.insert(statement);
    }

    inline void Statement::_removeSignalingTarget(Statement*statement){
      PRINT_CALL_STACK(statement);
      assert(this!=nullptr);
      this->_signalingTargets.erase(statement);
    }

    inline bool Statement::hasSignalingTarget(Statement*statement)const{
      PRINT_CALL_STACK(statement);
      assert(this!=nullptr);
      return this->_signalingTargets.count(statement)!=0;
    }


    inline size_t Statement::nofSignalingSources()const{
      PRINT_CALL_STACK();
      assert(this!=nullptr);
      return this->_signalingSources.size();
    }

    inline size_t Statement::nofSignalingTargets()const{
      PRINT_CALL_STACK();
      assert(this!=nullptr);
      return this->_signalingTargets.size();
    }

    inline void Statement::setDirty(){
      PRINT_CALL_STACK();
      assert(this!=nullptr);
      this->_dirtyFlag = true;
      this->setSignalingDirty();
    }

    inline void Statement::setSignalingDirty(){
      PRINT_CALL_STACK();
      assert(this!=nullptr);
      for(auto const&x:this->_signalingTargets)
        if(!x->isDirty())x->setDirty();
    }

    inline Statement::Ticks Statement::getUpdateTicks()const{
      PRINT_CALL_STACK();
      assert(this!=nullptr);
      return this->_updateTicks;
    }

    inline void Statement::setUpdateTicks(Ticks ticks){
      PRINT_CALL_STACK(ticks);
      assert(this!=nullptr);
      this->_updateTicks = ticks;
    }

    inline std::shared_ptr<Body>Statement::toBody()const{
      PRINT_CALL_STACK();
      return nullptr;
    }

    inline std::shared_ptr<If>Statement::toIf()const{
      PRINT_CALL_STACK();
      return nullptr;
    }

    inline std::shared_ptr<While>Statement::toWhile()const{
      PRINT_CALL_STACK();
      return nullptr;
    }

    inline std::shared_ptr<Function>Statement::toFunction()const{
      PRINT_CALL_STACK();
      return nullptr;
    }

    inline bool Statement::isIgnoringDirty()const{
      PRINT_CALL_STACK();
      assert(this!=nullptr);
      return this->_ignoreDirty;
    }

    inline void Statement::setIgnoreDirty(bool ignore){
      PRINT_CALL_STACK();
      assert(this!=nullptr);
      this->_ignoreDirty = ignore;
    }
  }
}

