#include<geCore/fsa/MealyMachine.h>
#include<geCore/fsa/MapTransitionChooser.h>

#include<limits>
#include<iostream>
#include<cassert>
#include<cstring>
#include<sstream>
#include<iomanip>
#include<algorithm>

#include<geCore/ErrorPrinter.h>
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
  auto clb = std::get<CALLBACK>(transition);
  if(clb)clb(this);
}

inline bool MealyMachine::_nextState(State const&state){
  assert(this!=nullptr);
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
  assert(this!=nullptr);
  assert(chooser!=nullptr);
  assert(chooser->getSize()<=this->_symbolBuffer.size());
  auto id = this->_states.size();
  this->_states.push_back(State(TransitionVector(),chooser,nullptr,nullptr));
  return id;
}

MealyMachine::StateIndex MealyMachine::addState(){
  assert(this);
  return this->addState(std::make_shared<MapTransitionChooser<1>>());
}

void MealyMachine::addTransition(
    StateIndex       const&from    ,
    TransitionSymbol const&lex     ,
    StateIndex       const&to      ,
    Callback         const&callback){
  assert(this!=nullptr);
  assert(from<this->_states.size());
  assert(to<this->_states.size());
  assert(std::get<CHOOSER>(this->_states[from])!=nullptr);
  std::get<CHOOSER>(this->_states[from])->addTransition(lex);
  std::get<TRANSITIONS>(this->_states[from]).push_back(
      Transition(to,callback));
}

void MealyMachine::addTransition(
    StateIndex                   const&from    ,
    std::vector<TransitionSymbol>const&symbols ,
    StateIndex                   const&to      ,
    Callback                     const&callback){
  assert(this!=nullptr);
  for(auto const&x:symbols)
    this->addTransition(from,x,to,callback);
}

void MealyMachine::addTransition(
    StateIndex                   const&from      ,
    TransitionSymbol             const&symbolFrom,
    TransitionSymbol             const&symbolTo  ,
    StateIndex                   const&to        ,
    Callback                     const&callback  ){
  assert(this!=nullptr);
  assert(from<this->_states.size());
  assert(std::get<CHOOSER>(this->_states.at(from))!=nullptr);
  size_t stateSize = std::get<CHOOSER>(this->_states.at(from))->getSize();
  bool same = true;
  for(size_t i=1;i<=stateSize;++i){
    if(symbolFrom[stateSize-i]<symbolTo[stateSize-i])same = false;
    if(symbolFrom[stateSize-i]>symbolTo[stateSize-i])return;
  }
  this->addTransition(from,symbolTo,to,callback);
  if(same)return;
  bool running=true;
  std::vector<BasicUnit>currentSymbol;
  currentSymbol.resize(stateSize);
  std::memcpy(currentSymbol.data(),symbolFrom,stateSize);
  do{
    this->addTransition(from,currentSymbol.data(),to,callback);
    size_t ii=0;
    while(ii<currentSymbol.size()&&currentSymbol.at(ii)==std::numeric_limits<BasicUnit>::max())
      currentSymbol.at(ii++)=0;
    if(ii<currentSymbol.size())currentSymbol.at(ii)++;
    else break;
    for(size_t i=1;i<=stateSize;++i)
      if(currentSymbol[stateSize-i]>symbolTo[stateSize-i]){
        running=false;
        break;
      }
  }while(running);
}

void MealyMachine::addTransition(
    StateIndex const&from    ,
    char const*const&lex     ,
    StateIndex const&to      ,
    Callback   const&callback){
  assert(this!=nullptr);
  this->addTransition(from,(TransitionSymbol)lex,to,callback);
}

void MealyMachine::addTransition(
    StateIndex              const&from    ,
    std::vector<char const*>const&symbols ,
    StateIndex              const&to      ,
    Callback                const&callback){
  assert(this!=nullptr);
  for(auto const&x:symbols)
    this->addTransition(from,x,to,callback);
}

void MealyMachine::addTransition(
    StateIndex const&from      ,
    char const*const&symbolFrom,
    char const*const&symbolTo  ,
    StateIndex const&to        ,
    Callback   const&callback  ){
  this->addTransition(from,(TransitionSymbol)symbolFrom,(TransitionSymbol)symbolTo,to,callback);
}

void MealyMachine::addElseTransition(
    StateIndex   const&from    ,
    StateIndex   const&to      ,
    Callback     const&callback){
  assert(this!=nullptr);
  assert(from<this->_states.size());
  assert(to<this->_states.size());
  std::get<ELSE_TRANSITION>(this->_states[from]) = 
    std::make_shared<Transition>(to,callback);
}


void MealyMachine::addEOFTransition(
    StateIndex   const&from    ,
    Callback     const&callback){
  assert(this!=nullptr);
  assert(from<this->_states.size());
  std::get<EOF_TRANSITION>(this->_states[from]) = 
    std::make_shared<Transition>(0,callback);
}

void MealyMachine::addTransition(
    StateIndex       const&from    ,
    TransitionSymbol const&symbol  ,
    StateIndex       const&to      ,
    SimpleCallback   const&callback){
  assert(this!=nullptr);
  if(callback)
    this->addTransition(from,symbol,to,[callback](MealyMachine*){callback();});
  else
    this->addTransition(from,symbol,to);
}

void MealyMachine::addElseTransition(
    StateIndex     const&from    ,
    StateIndex     const&to      ,
    SimpleCallback const&callback){
  assert(this!=nullptr);
  if(callback)
    this->addElseTransition(from,to,[callback](MealyMachine*){callback();});
  else
    this->addElseTransition(from,to);
}

void MealyMachine::addEOFTransition(
    StateIndex     const&from    ,
    SimpleCallback const&callback){
  assert(this!=nullptr);
  if(callback)
    this->addEOFTransition(from,[callback](MealyMachine*){callback();});
  else
    this->addEOFTransition(from);
}

void MealyMachine::addTransition(
    StateIndex       const&from    ,
    char const*      const&symbol  ,
    StateIndex       const&to      ,
    SimpleCallback   const&callback){
  assert(this!=nullptr);
  this->addTransition(from,(TransitionSymbol)symbol,to,callback);
}

void MealyMachine::begin(){
  assert(this!=nullptr);
  this->_currentState      = 0;
  this->_symbolBufferIndex = 0;
  this->_readingPosition   = 0;
}

bool MealyMachine::parse(BasicUnit const*data,size_t size){
  assert(this!=nullptr);
  assert(this->_currentState<this->_states.size());
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

bool MealyMachine::parse(char const*data){
  assert(this);
  return this->parse((MealyMachine::BasicUnit const*)data,std::strlen(data));
}

bool MealyMachine::end(){
  assert(this!=nullptr);
  if(this->_symbolBufferIndex>0){
    ge::core::printError("MealyMachine::end",
        "there are some unprocess bytes at the end of stream");
    return false;
  }
  assert(this->_currentState<this->_states.size());
  auto const&state = this->_states[this->_currentState];
  auto const&transition = std::get<EOF_TRANSITION>(state);
  if(!transition)return false;
  this->_call(*transition);
  return false;
}

const MealyMachine::TransitionIndex MealyMachine::nonexistingTransition = 
std::numeric_limits<MealyMachine::TransitionIndex>::max();


std::string MealyMachine::str()const{
  assert(this!=nullptr);
  auto printTransition = [](Transition const&t){
    std::stringstream ss;
    ss<<std::get<STATE_INDEX>(t);
    ss<<std::endl;
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
