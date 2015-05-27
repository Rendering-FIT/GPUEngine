#include <geGL/OpenGL.h>


using namespace ge::gl;

void CommandContainer::reset(){
  this->command = NULL;
  this->ref     = false;
}

void CommandContainer::free(){
  if(this->command&&!this->ref)delete this->command;
  this->reset();
}

void CommandContainer::apply(){
  if(this->command)this->command->apply();
}

void CommandList::apply(){
  for(unsigned i=0;i<this->commands.size();++i)
    this->commands[i]->apply();
}

/**
 * @brief constructs command list
 *
 * @param outOfOrder if it is set to true, commands can be executed out of order
 */
CommandList::CommandList(bool outOfOrder){
  this->outOfOrder=outOfOrder;
}
CommandList::Iterator CommandList::add(Command*commands){
  this->commands.push_back(std::shared_ptr<Command>(commands));
  return this->commands.end();
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

