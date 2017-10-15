#include<limits>
#include<iostream>
#include<cassert>
#include<cstring>
#include<sstream>
#include<iomanip>
#include<algorithm>
#include<cctype>

#include<GPUEngine/geCore/ErrorPrinter/ErrorPrinter.h>

#include<GPUEngine/geCore/MealyMachine/MealyMachine.h>
#include<GPUEngine/geCore/MealyMachine/MapTransitionChooser.h>
#include<GPUEngine/geCore/MealyMachine/TransitionChooser.h>

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
      if(this->_quiet)return false;
      std::stringstream ss;
      ss<<"there is no suitable transition from state ";
      ss<<this->_currentState<<" using symbol: 0x"<<
        getHexRepresentation(this->_currentSymbol,this->_currentSymbolSize);
      ss<<" at position: "<<this->_currentSymbol;
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
    std::shared_ptr<TransitionChooser>const&chooser,std::string const&name){
  assert(this!=nullptr);
  assert(chooser!=nullptr);
  assert(chooser->getSize()<=this->_symbolBuffer.size());
  auto id = this->_states.size();
  this->_states.push_back(State(TransitionVector(),chooser,nullptr,nullptr,name));
  return id;
}

MealyMachine::StateIndex MealyMachine::addState(std::string const&name){
  assert(this);
  return this->addState(std::make_shared<MapTransitionChooser<1>>(),name);
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
  for(size_t i=1;i<=stateSize;++i)
    if(symbolFrom[stateSize-i]>symbolTo[stateSize-i])return;
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
    StateIndex  const&from    ,
    std::string const&lex     ,
    StateIndex  const&to      ,
    Callback    const&callback){
  assert(this!=nullptr);
  assert(from<this->_states.size());
  assert(std::get<CHOOSER>(this->_states.at(from))!=nullptr);
  size_t stateSize = std::get<CHOOSER>(this->_states.at(from))->getSize();
  if(lex.length()%stateSize!=0){
    ge::core::printError(
        GE_CORE_FCENAME,
        "transition symbol length is not multiplication of state size: "+ge::core::value2str(stateSize),from,lex,to);
    return;
  }
  for(size_t offset=0;offset<lex.length();offset+=stateSize)
    this->addTransition(from,(TransitionSymbol)lex.c_str()+offset,to,callback);
}

void MealyMachine::addTransition(
    StateIndex              const&from    ,
    std::vector<std::string>const&symbols ,
    StateIndex              const&to      ,
    Callback                const&callback){
  assert(this!=nullptr);
  for(auto const&x:symbols)
    this->addTransition(from,x,to,callback);
}

void MealyMachine::addTransition(
    StateIndex  const&from      ,
    std::string const&symbolFrom,
    std::string const&symbolTo  ,
    StateIndex  const&to        ,
    Callback    const&callback  ){
  this->addTransition(from,(TransitionSymbol)symbolFrom.c_str(),(TransitionSymbol)symbolTo.c_str(),to,callback);
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
    if(this->_quiet)return false;
    ge::core::printError("MealyMachine::end",
        "there are some unprocess bytes at the end of stream");
    return false;
  }
  assert(this->_currentState<this->_states.size());
  auto const&state = this->_states[this->_currentState];
  auto const&transition = std::get<EOF_TRANSITION>(state);
  if(!transition)return false;
  this->_call(*transition);
  return true;
}

bool MealyMachine::match(BasicUnit const*data,size_t size){
  assert(this);
  this->begin();
  return this->parse(data,size)&&this->end();
}

bool MealyMachine::match(char const*data){
  assert(this);
  return this->match((BasicUnit const*)data,std::strlen(data));
}

const MealyMachine::TransitionIndex MealyMachine::nonexistingTransition = 
std::numeric_limits<MealyMachine::TransitionIndex>::max();


std::string MealyMachine::str()const{
  assert(this!=nullptr);
  auto printTransition = [&](Transition const&t){
    std::stringstream ss;
    auto endStateIndex = std::get<STATE_INDEX>(t);
    assert(endStateIndex<this->_states.size());
    auto endState = this->_states.at(endStateIndex);
    if(std::get<NAME>(endState)!="")ss<<std::get<NAME>(endState);
    else ss<<endStateIndex;
    ss<<std::endl;
    return ss.str();
  };
  auto printSymbol = [](TransitionSymbol symbol,size_t size){
    std::stringstream ss;
    if(size==1&&std::isprint(symbol[0])){
      ss<<"\'"<<(char)symbol[0]<<"\' ";
      return ss.str();
    }
    for(MealyMachine::TransitionIndex i = 0;i<size;++i)
      ss<<std::setfill('0')<<std::setw(2)<<std::hex<<
        static_cast<uint32_t>(symbol[i]);
    return ss.str();
  };

  std::stringstream ss;
  size_t stateCounter = 0;
  for(auto const&s:this->_states){
    ss<<"state ";
    if(std::get<NAME>(s)!="")ss<<std::get<NAME>(s);
    else ss<<stateCounter;
    ss<<": "<<std::endl;
    auto const&transitions = std::get<TRANSITIONS>(s);
    size_t transitionCounter = 0;
    for(auto t:transitions){
      auto const&chooser = std::get<CHOOSER>(s);
      ss<<"  ";

      ss<<printSymbol(chooser->getSymbol(transitionCounter),chooser->getSize());
      if(chooser->getSize()<2)
        ss<<"  ";

      ss<<" -> "<<printTransition(t);
      transitionCounter++;
    }
    if(std::get<EOF_TRANSITION>(s)){
      auto const&t = *std::get<EOF_TRANSITION>(s);
      ss<<"  ";
      ss<<"eof "<<printTransition(t);
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

void MealyMachine::setQuiet(bool quiet){
  assert(this);
  this->_quiet = quiet;
}

bool MealyMachine::isQuiet()const{
  assert(this);
  return this->_quiet;
}

