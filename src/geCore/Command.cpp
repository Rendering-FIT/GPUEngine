#include<geCore/Command.h>
#include<geCore/dtemplates.h>

using namespace ge::core;

CommandContainer::CommandContainer(Command**command){
  this->_command = command;
}
CommandContainer::~CommandContainer(){
  this->_command = NULL;
}
void CommandContainer::operator()(){
  if(this->_command)(*(*this->_command))();
}
void CommandContainer::set(Command**command){
  this->_command = command;
}
Command**CommandContainer::get(){
  return this->_command;
}
Command*CommandContainer::getCommand(){
  if(this->_command)return *this->_command;
  return NULL;
}

/*
void CommandList::operator()(){
  for(unsigned i=0;i<this->_commands.size();++i)
    (*this->_commands[i])();
}

CommandList::CommandList(bool outOfOrder){
  this->_outOfOrder=outOfOrder;
}
CommandList::~CommandList(){
  for(unsigned i=0;i<this->_commands.size();++i)
    ge::core::deleteSetNull(this->_commands[i]);
}
unsigned CommandList::add(Command*commands){
  this->_commands.push_back(commands);
  return this->_commands.size()-1;
}
Command* CommandList::getCommand(unsigned i){
  if(i>=this->_commands.size())return NULL;
  return this->_commands[i];
}
unsigned CommandList::size(){return this->_commands.size();}
*/
CommandList::CommandList(){}
CommandList::~CommandList(){
  for(auto x:*this)delete x;
}
void CommandList::operator()(){
  for(auto x:*this)(*x)();
}

SharedCommandList::SharedCommandList(){}
SharedCommandList::~SharedCommandList(){}
void SharedCommandList::operator()(){
  for(auto x:*this)(*x)();
}

CommandListWithAccessor::CommandListWithAccessor():CommandList(){}

Command*CommandListWithAccessor::operator[](std::string name){
  auto it=this->_name2Command.find(name);
  if(it==this->_name2Command.end())return NULL;
  return this->_name2Command[name];
}

unsigned CommandListWithAccessor::add(Command*command,std::string name){
  if(name!="")this->_name2Command[name]=command;
  this->CommandList::push_back(command);
  return (unsigned)this->size()-1;
}

void CommandIf::operator()(){
  (*this->statement)();
  if(this->statement->isTrue){
    if(this->trueBranch)(*this->trueBranch)();
  }else{
    if(this->falseBranch)(*this->falseBranch)();
  }
}
//stepable while, semistepable while, deepstepable command
void CommandWhile::operator()(){
  if(!this->body)return;
  for(;;){
    (*this->statement)();
    if(!this->statement->isTrue)break;
    (*this->body)();
  }
}

