#include<geDE/Nullary.h>

using namespace ge::de;

Nullary::Nullary(
    std::shared_ptr<FunctionRegister>const&fr  ,
    FunctionId           id  ,
    std::shared_ptr<Resource>const&        data):AtomicFunction(fr,id){
  this->bindOutput(fr,data);
  this->_dirtyFlag = false;
  //this->_outputData = data;
}

//void Nullary::addSignaling(Statement*statement){
//  this->_addSignaling(statement);
//}

void Nullary::operator()(){
  if(!this->_dirtyFlag)return;
  this->_dirtyFlag = false;
  this->_updateTicks++;
  this->setSignalingDirty();
}


