#include <geGL/OpenGL.h>
#include<geCore/dtemplates.h>


using namespace ge::gl;

CommandContainer::CommandContainer(Command**command){
  this->_command = command;
}
CommandContainer::~CommandContainer(){
  this->_command = NULL;
}
void CommandContainer::apply(){
  if(this->_command)(*this->_command)->apply();
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

void CommandList::apply(){
  for(unsigned i=0;i<this->_commands.size();++i)
    this->_commands[i]->apply();
}

/**
 * @brief constructs command list
 *
 * @param outOfOrder if it is set to true, commands can be executed out of order
 */
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

void CommandIf::apply(){
  this->statement->apply();
  if(this->statement->isTrue){
    if(this->trueBranch)this->trueBranch->apply();
  }else{
    if(this->falseBranch)this->falseBranch->apply();
  }
}
//stepable while, semistepable while, deepstepable command
void CommandWhile::apply(){
  if(!this->body)return;
  for(;;){
    this->statement->apply();
    if(!this->statement->isTrue)break;
    this->body->apply();
  }
}

