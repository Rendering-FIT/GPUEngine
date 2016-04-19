#include<geCore/fsa/MealyMachine.h>

#include<limits>
#include<iostream>
#include<cassert>
#include<cstring>
#include<sstream>
#include<iomanip>
#include<algorithm>

#include<geCore/dtemplates.h>
#include<geCore/fsa/TransitionChooser.h>

using namespace ge::core;

std::string getHexRepresentation(
    MealyMachine::TransitionSymbol const&symbol,
    size_t size){
  std::stringstream ss;
  for(size_t i=0;i<size;++i)
    ss<<std::setfill('0')<<std::setw(2)<<std::hex<<
      static_cast<uint32_t>(symbol[i]);
  return ss.str();
}



MealyMachine::MealyMachine(size_t largestState){
  this->_symbolBuffer.resize(largestState);
}

MealyMachine::~MealyMachine(){
}

inline void MealyMachine::_call(Transition const&transition){
  CallbackWithData const&clb = std::get<CALLBACK_WITH_DATA>(transition);
  if(std::get<CALLBACK>(clb))
    std::get<CALLBACK>(clb)(this,std::get<DATA>(clb));
}

inline bool MealyMachine::_nextState(State const&state){
  auto const& transitionIndex = 
    std::get<CHOOSER>(state)->getTransition(this->_currentSymbol);
  Transition const* transition = nullptr;
  if(transitionIndex == MealyMachine::nonexistingTransition){
    auto trans = std::get<ELSE_TRANSITION>(state);
    if(!trans){
      std::stringstream ss;
      ss<<"there is no suitable transition from state ";
      ss<<this->_currentState<<" using symbol 0x"<<
        getHexRepresentation(this->_currentSymbol,this->_currentSymbolSize);
      ge::core::printError("MealyMachine::_nextState",ss.str());
      return false;
    }
    transition = &*trans;
  }else transition = &std::get<TRANSITIONS>(state)[transitionIndex];
  this->_call(*transition);
  this->_currentState = std::get<STATE_INDEX>(*transition);
  return true;
}

MealyMachine::StateIndex MealyMachine::addState(
    std::shared_ptr<TransitionChooser>const&chooser){
  auto id = this->_states.size();
  this->_states.push_back(State(TransitionVector(),chooser,nullptr,nullptr));
  return id;
}

void MealyMachine::addTransition(
    StateIndex       const&from    ,
    TransitionSymbol const&lex     ,
    StateIndex       const&to      ,
    Callback         const&callback,
    CallbackData     const&data    ){
  //std::cout<<"addTransition("<<from<<","<<*(char*)lex<<","<<to<<","<<(void*)callback<<","<<data<<")"<<std::endl;
  assert(this!=nullptr);
  assert(from<this->_states.size());
  assert(to<this->_states.size());
  assert(std::get<CHOOSER>(this->_states[from])!=nullptr);
  std::get<CHOOSER>(this->_states[from])->addTransition(lex);
  std::get<TRANSITIONS>(this->_states[from]).push_back(
      Transition(to,CallbackWithData(callback,data)));
}

void MealyMachine::addElseTransitions(
    StateIndex   const&from    ,
    StateIndex   const&to      ,
    Callback     const&callback,
    CallbackData const&data    ){
  assert(this!=nullptr);
  assert(from<this->_states.size());
  assert(to<this->_states.size());
  std::get<ELSE_TRANSITION>(this->_states[from]) = 
    std::make_shared<Transition>(to,CallbackWithData(callback,data));
}


void MealyMachine::addEOFTransition(
    StateIndex   const&from    ,
    Callback     const&callback,
    CallbackData const&data    ){
  //std::cout<<"addEOFTransition("<<from<<","<<(void*)callback<<","<<data<<")"<<std::endl;
  assert(this!=nullptr);
  assert(from<this->_states.size());
  std::get<EOF_TRANSITION>(this->_states[from]) = 
    std::make_shared<Transition>(0,CallbackWithData(callback,data));
}


void MealyMachine::begin(){
  this->_currentState = 0;
  this->_symbolBufferIndex = 0;
  this->_readingPosition = 0;
}

bool MealyMachine::parse(BasicUnit const*data,size_t size){
  size_t read = 0;
  auto const& state = this->_states[this->_currentState];
  auto const& chooser = std::get<CHOOSER>(state);
  auto symbolSize = chooser->getSize();
  while(this->_symbolBufferIndex>0){
    read = std::min(symbolSize-this->_symbolBufferIndex,size);
    std::memcpy(this->_symbolBuffer.data()+this->_symbolBufferIndex,data,
        sizeof(BasicUnit)*read);
    this->_symbolBufferIndex+=read;
    if(this->_symbolBufferIndex<symbolSize)return true;

    this->_currentSymbol = this->_symbolBuffer.data();
    this->_currentSymbolSize = symbolSize;
    this->_dontMove = false;
    if(!this->_nextState(state))
      return false;
    if(!this->_dontMove){
      this->_readingPosition += symbolSize*sizeof(BasicUnit);
      this->_symbolBufferIndex = 0;
    }
  }

  do{
    auto const&state   = this->_states.at(this->_currentState);
    auto const&chooser = std::get<CHOOSER>(state);
    symbolSize = chooser->getSize();

    if(size-read<symbolSize){
      if(read == size)return true;
      std::memcpy(this->_symbolBuffer.data(),data+read,size-read);
      this->_symbolBufferIndex = size-read;
      return true;
    }

    this->_currentSymbol = data+read;
    this->_currentSymbolSize = symbolSize;
    this->_dontMove = false;
    if(!this->_nextState(state))
      return false;
    if(!this->_dontMove){
      this->_readingPosition += symbolSize*sizeof(BasicUnit);
      read += symbolSize*sizeof(BasicUnit);
    }
  }while(true);
}

bool MealyMachine::end(){
  if(this->_symbolBufferIndex>0){
    ge::core::printError("MealyMachine::end",
        "there are some unprocess bytes at the end of stream");
    return false;
  }
  auto const&state = this->_states[this->_currentState];
  auto const&transition = std::get<EOF_TRANSITION>(state);
  if(!transition)return false;
  this->_call(*transition);
  return false;
}

const MealyMachine::TransitionIndex MealyMachine::nonexistingTransition = 
  std::numeric_limits<MealyMachine::TransitionIndex>::max();


std::string MealyMachine::str()const{
  auto printTransition = [](Transition const&t){
    std::stringstream ss;
    ss<<std::get<STATE_INDEX>(t);
    auto &clb = std::get<CALLBACK_WITH_DATA>(t);
    ss<<" "<<std::get<CALLBACK>(clb)<<
      "("<<(void*)std::get<DATA>(clb)<<")"<<std::endl;
    return ss.str();
  };

  std::stringstream ss;
  size_t stateCounter = 0;
  for(auto s:this->_states){
    ss<<"state "<<stateCounter<<": "<<std::endl;
    auto const&transitions = std::get<TRANSITIONS>(s);
    size_t transitionCounter = 0;
    for(auto t:transitions){
      auto const&chooser = std::get<CHOOSER>(s);
      ss<<"  ";

      auto const&sym = chooser->getSymbol(transitionCounter);
      for(MealyMachine::TransitionIndex i = 0;i<chooser->getSize();++i)
        ss<<std::setfill('0')<<std::setw(2)<<std::hex<<
          static_cast<uint32_t>(sym[i]);
      if(chooser->getSize()<2)
        ss<<"  ";

      ss<<" -> "<<printTransition(t);
      transitionCounter++;
    }
    if(std::get<EOF_TRANSITION>(s)){
      auto const&t = *std::get<EOF_TRANSITION>(s);

      auto const&chooser = std::get<CHOOSER>(s);
      ss<<"  ";

      ss<<"eof ";
      if(chooser->getSize()>2)
        for(size_t i=0;i<chooser->getSize()-2;++i)
          ss<<"  ";

      ss<<" -> "<<std::get<EOF_TRANSITION>(s)<<" "<<printTransition(t);
    }
    if(std::get<ELSE_TRANSITION>(s)){
      auto const&t = *std::get<ELSE_TRANSITION>(s);

      auto const&chooser = std::get<CHOOSER>(s);
      ss<<"  ";

      ss<<"else";
      if(chooser->getSize()>2)
        for(size_t i=0;i<chooser->getSize()-2;++i)
          ss<<"  ";

      ss<<" -> "<<std::get<ELSE_TRANSITION>(s)<<" "<<printTransition(t);
    }
    stateCounter++;
  }
  return ss.str();
}
