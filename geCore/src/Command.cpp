#include<GPUEngine/geCore/Command.h>
#include<GPUEngine/geCore/Dtemplates.h>

using namespace ge::core;

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

