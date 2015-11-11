#include<geCore/fsa/fsa.h>
#include<sstream>
#include<set>
#include<algorithm>
#include<geCore/disjointSet.h>

using namespace ge::core;

State* FSA::_addState(std::string name){
  if(!this->_name2State.count(name)){
    State*newState=new State(name);
    this->_states.push_back(newState);
    this->_name2State[name]=newState;
  }
  return this->_name2State[name];
}

State*FSA::_getState(std::string name)const{
  return this->_name2State.find(name)->second;
}

std::string FSA::_expandLex(std::string lex)const{
  std::string elex="";
  unsigned len=lex.size();
  char lastChar='\0';
  enum State{
    START         ,
    BACKSLASH     ,
    RANGE         ,
    RANGEBACKSLASH,
  }state=START;
  for(unsigned i=0;i<len;++i){
    char c=lex[i];
    switch(state){
      case START:
        if(c=='\\'){
          if(lastChar!='\0')elex+=lastChar;
          state=BACKSLASH;
          break;
        }else{
          if(lastChar!='\0')elex+=lastChar;
          lastChar=c;
          break;
        }
      case BACKSLASH:
        if(c==FSA::digit[1]){//DIGIT
          for(char i='0';i<='9';++i)elex+=i;
          lastChar='\0';
          state=START;
          break;
        }else if(c==FSA::space[1]){//SPACE
          for(unsigned i=0;i<FSA::space.size();++i)elex+=FSA::space[i];
          lastChar='\0';
          state=START;
          break;
        }else if(c==FSA::range[1]){//DASH
          if(lastChar=='\0'){
            std::cerr<<"left side of range is empty"<<std::endl;
            return"";
          }
          state=RANGE;
          break;
        }else if(c=='\\'){//BACKSLASH
          lastChar=c;
          state=START;
          break;
        }else if(c==FSA::all[1]){//ALL
          for(int i=1;i<=255;++i)elex+=i;
          state=START;
          break;
        }else{
          lastChar=c;
          state=START;
          break;
        }
      case RANGE:
        if(c=='\\'){
          state=RANGEBACKSLASH;
          break;
        }else{
          for(int i=lastChar;i<=c;++i)elex+=i;
          lastChar='\0';
          state=START;
          break;
        }
      case RANGEBACKSLASH:
        if(c==FSA::digit[1]||c==FSA::space[1]||c==FSA::all[1]||c==FSA::range[1]){
          std::cerr<<"range right side cant be \\"<<c<<std::endl;
          return"";
        }else{
          for(int i=lastChar;i<=c;++i)elex+=i;
          lastChar='\0';
          state=START;
          break;
        }
    }

  }
  if(lastChar!='\0')elex+=lastChar;
  std::sort(elex.begin(),elex.end());
  elex.erase(std::unique(elex.begin(),elex.end()),elex.end());
  return elex;
}

void FSA::removeUnreachableStates(){
  std::set<State*>reachable;
  reachable.insert(this->_name2State[this->_start]);
  unsigned oldSize=reachable.size();
  unsigned newSize=0;
  do{
    std::vector<State*>newStates;
    for(auto x:reachable){
      for(auto y:*x)
        newStates.push_back(y.second.getNextState());
      if(x->getElseTransition().getNextState())
        newStates.push_back(x->getElseTransition().getNextState());
      if(x->getEOFTransition().getNextState())
        newStates.push_back(x->getEOFTransition().getNextState());
    }
    for(auto x:newStates)
      reachable.insert(x);
    newSize=reachable.size();
  }while(oldSize!=newSize);
  std::vector<State*>statesToRemove;
  for(auto x:this->_states)
    if(reachable.find(x)==reachable.end())
      statesToRemove.push_back(x);
  this->_states.clear();
  this->_name2State.clear();
  for(auto x:statesToRemove)
    delete x;
  for(auto x:reachable){
    this->_states.push_back(x);
    this->_name2State[x->getName()]=x;
  }
}

void FSA::removeUndistinguishabeStates(){
  std::vector<ge::core::DisjointSet<State*>>eq;
  eq.push_back(ge::core::DisjointSet<State*>());
  for(auto p:this->_states)
    for(auto q:this->_states){
      if(
          p->getEOFTransition().getNextState()!=nullptr &&
          q->getEOFTransition().getNextState()!=nullptr &&
          p->getEOFTransition().getCallback() == q->getEOFTransition().getCallback() &&
          p->getEOFTransition().getCallbackData() == q->getEOFTransition().getCallbackData()
          )
        eq[0].add(p,q);
    }
  do{
    ge::core::DisjointSet<State*>newEq;
    for(auto p:this->_states)
      for(auto q:this->_states){
        auto lastRel=eq[eq.size()-1];
        if(!lastRel.eq(p,q))continue;
        if(p->getNofTransition()!=q->getNofTransition())continue;
        bool transitionsOk=true;
        for(unsigned i=0;i<p->getNofTransition();++i){
          char lex=p->getTransitionLex(i);
          if(!q->hasTransition(lex)){
            transitionsOk=false;
            break;
          }
          if(p->getTransition(lex).getCallbackData()!=q->getTransition(lex).getCallbackData()){
            transitionsOk=false;
            break;
          }
          if(p->getTransition(lex).getCallback()!=q->getTransition(lex).getCallback()){
            transitionsOk=false;
            break;
          }
          if(!lastRel.eq(p->getTransition(lex).getNextState(),q->getTransition(lex).getNextState())){
            transitionsOk=false;
            break;
          }
        }
        if(!transitionsOk)continue;
        if(q->hasElseTransition()!=p->hasElseTransition())continue;
        if(q->hasEOFTransition()!=p->hasEOFTransition())continue;
        if(q->getElseTransition().getNextState()   !=p->getElseTransition().getNextState())continue;
        if(q->getElseTransition().getCallback()    !=p->getElseTransition().getCallback())continue;
        if(q->getElseTransition().getCallbackData()!=p->getElseTransition().getCallbackData())continue;
        if(q->getEOFTransition().getNextState()   !=p->getEOFTransition().getNextState())continue;
        if(q->getEOFTransition().getCallback()    !=p->getEOFTransition().getCallback())continue;
        if(q->getEOFTransition().getCallbackData()!=p->getEOFTransition().getCallbackData())continue;
        newEq.add(p,q);
      }
    eq.push_back(newEq);
  }while(!(eq[eq.size()-1]==eq[eq.size()-2]));
  auto lastRel=eq[eq.size()-1];
  std::vector<State*>newStates;
  std::map<std::string,State*>newName2State;
  for(auto x:lastRel){
    std::string name="";
    for(auto y:x)
      name+=y->getName();
    auto newState=new State(name);
    newStates.push_back(newState);
    newName2State[name]=newState;



  }

}

FSA::FSA(std::string start){
  this->_start = start;
  if(this->_start!="")
    this->_addState(start);
}

FSA::~FSA(){
  for(auto x:this->_states)
    delete x;
}

void FSA::addTransition(
    std::string  stateA  ,
    char         lex     ,
    std::string  stateB  ,
    RuleCallback callback,
    void*        data    ){
  State*sa=this->_addState(stateA);
  State*sb=this->_addState(stateB);
  sa->addTransition(lex,sb,callback,data);
}

void FSA::addTransition(
    std::string  stateA  ,
    std::string  lex     ,
    std::string  stateB  ,
    RuleCallback callback,
    void*        data    ){
  std::string elex=this->_expandLex(lex);
  for(unsigned i=0;i<elex.size();++i){
    this->addTransition(stateA,elex[i],stateB,callback,data);
  }
}
void FSA::addAllTransition(
    std::string  stateA  ,
    std::string  stateB  ,
    RuleCallback callback,
    void*        data    ){
  State*sa=this->_addState(stateA);
  State*sb=this->_addState(stateB);
  sa->clearTransitions();
  sa->addElseTransition(sb,callback,data);
}

void FSA::addElseTransition(
    std::string  stateA  ,
    std::string  stateB  ,
    RuleCallback callback,
    void*        data    ){
  State*sa=this->_addState(stateA);
  State*sb=this->_addState(stateB);
  sa->addElseTransition(sb,callback,data);
}

void FSA::addEOFTransition(
    std::string  stateA  ,
    std::string  stateB  ,
    RuleCallback callback,
    void*        data    ){
  State*sa=this->_addState(stateA);
  State*sb=this->_addState(stateB);
  sa->addEOFTransition(sb,callback,data);
}

bool FSA::run(std::string text){
  this->_alreadyRead="";
  State*curState=this->_name2State[this->_start];
  unsigned pos=0;
  while(pos<text.size()){
    this->_currentChar      = text[pos];
    this->_currentStateName = curState->getName();
    this->_currentPosition  = pos;
    State*newState=curState->apply(text[pos],this);
    if(!newState)return false;
    this->_alreadyRead+=text[pos];
    pos++;
    curState=newState;
  }
  if(!curState->getEOFTransition().getNextState())return false;
  curState->getEOFTransition().callCallback(this);
  return true;
}

char FSA::getCurrentChar()const{
  return this->_currentChar;
}

std::string FSA::getAlreadyReadString()const{
  return this->_alreadyRead;
}

std::string FSA::getCurrentStateName()const{
  return this->_currentStateName;
}

unsigned FSA::getCurrentPosition()const{
  return this->_currentPosition;
}

std::string FSA::toStr()const{
  std::stringstream ss;
  for(auto x:this->_states)
    ss<<x->getName()<<": "<<x->toStr()<<std::endl;
  return ss.str();
}

/*
State*recPlus(FSA*result,State*a,State*b){
  auto newState=new State(a->getName()+b->getName());
  return newState;
}
*/
FSA*FSA::operator+(FSA const&other)const{
  FSA*result=new FSA(this->_start+other._start);
  //auto s=this->_name2State.find(this->_start)->second;
  return result;
}
/*
FSA const& FSA::operator*(FSA const&other)const{
}
*/

const std::string FSA::els   = ""       ;
const std::string FSA::eof   = "\\e"    ;
const std::string FSA::digit = "\\d"    ;
const std::string FSA::range = "\\-"    ;
const std::string FSA::all   = "\\."    ;
const std::string FSA::space = " \t\r\n";

