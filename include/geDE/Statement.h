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
    class GEDE_EXPORT Statement: public ge::core::Command{
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
        bool hasSignaling(Statement*statement)const;
        size_t nofSignaling()const;
      protected:
        Type _type;
        bool _dirtyFlag = false;
        Ticks _updateTicks = 0;
        std::set<Statement*>_forSignaling;
        void _addSignaling(Statement*statement);
        void _removeSignaling(Statement*statement);
    };

    inline Statement::Statement(Type const&type){
      assert(this!=nullptr);
      this->_type = type;
    }

    inline Statement::~Statement(){
    }

    inline bool Statement::isDirty()const{
      assert(this!=nullptr);
      return this->_dirtyFlag;
    }
    inline void Statement::_addSignaling(Statement*statement){
      assert(this!=nullptr);
      this->_forSignaling.insert(statement);
    }

    inline void Statement::_removeSignaling(Statement*statement){
      assert(this!=nullptr);
      this->_forSignaling.erase(statement);
    }

    inline bool Statement::hasSignaling(Statement*statement)const{
      assert(this!=nullptr);
      return this->_forSignaling.count(statement)!=0;
    }

    inline size_t Statement::nofSignaling()const{
      assert(this!=nullptr);
      return this->_forSignaling.size();
    }

    inline void Statement::setDirty(){
      assert(this!=nullptr);
      this->_dirtyFlag = true;
      this->setSignalingDirty();
    }

    inline void Statement::setSignalingDirty(){
      assert(this!=nullptr);
      for(auto const&x:this->_forSignaling)
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

