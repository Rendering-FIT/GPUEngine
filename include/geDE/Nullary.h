#pragma once

#include<geDE/AtomicFunction.h>
#include<geDE/FunctionRegister.h>

namespace ge{
  namespace de{
    class GEDE_EXPORT Nullary: public AtomicFunction{
      public:
        Nullary(
            std::shared_ptr<FunctionRegister>const&fr            ,
            FunctionId                             id            ,
            std::shared_ptr<Resource>const&        data = nullptr);
        template<typename TYPE>
          Nullary(
              std::shared_ptr<FunctionRegister>const&fr  ,
              FunctionId           id  ,
              TYPE const&                            data):AtomicFunction(
                fr,id){
                auto ss=fr->getTypeRegister()->sharedResource(keyword<TYPE>());
                (TYPE&)(*ss) = data;
                this->bindOutput(fr,ss);//fr->getTypeRegister()->sharedResource<TYPE>(data));
                this->_dirtyFlag = false;
              }
        template<typename TYPE>
          Nullary(
              std::shared_ptr<FunctionRegister>const&fr  ,
              TYPE const&                            data):Nullary(
                fr,fr->getFunctionId(keyword<Nullary>()),data){}
        template<typename TYPE>
          void update(TYPE const&data){
            (TYPE&)*this->_outputData=data;
            //this->_updateTicks++;
            this->setDirty();
          }
        //void addSignaling(Statement*statement);
        virtual void operator()()override;
    };

  }
}
