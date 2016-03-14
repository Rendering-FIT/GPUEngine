#include<geCore/termNode.h>

using namespace ge::core;

void TermNode::match(NodeContext&ctx){
  auto printStatus=[](NodeContext::Status status,unsigned currentLevel){
#ifndef DEBUG
    return;
#endif
    std::string statusName[3]={"TRUE","WAITING","FALSE"};
    for(unsigned i=0;i<currentLevel;++i)
      std::cout<<"  ";
    std::cout<<statusName[status]<<std::endl;
  };

#ifdef DEBUG
  for(unsigned i=0;i<ctx.currentLevel;++i)
    std::cout<<"  ";
  std::cout<<"\""<<this->getTerm()->name<<"\" ";
  std::cout<<" ["<<this->range.min()<<"-"<<this->range.max()<<"]";
  if(ctx.calledFromChildOrRecheck)std::cout<<" recheck";
  std::cout<<std::endl;
#endif

  if(this->range.empty()){
    if(this->canWait){
      ctx.setNode(this->shared_from_this());
      ctx.setStatus(NodeContext::WAITING);
    }else ctx.setStatus(NodeContext::FALSE);
    printStatus(ctx.getStatus(),ctx.currentLevel);
    return;
  }

  if(this->range.length()>this->getTerm()->range.max()){
    ctx.setStatus(NodeContext::FALSE);
    ctx.termIndex = this->range.min();
    if(this->areWeCurrent(ctx))this->parentMatch(ctx);
    printStatus(ctx.getStatus(),ctx.currentLevel);
    return;
  }

  if(ctx.calledFromChildOrRecheck){
    ctx.setStatus(NodeContext::FALSE);
    ctx.termIndex = this->range.min();
    this->parentMatch(ctx);
    printStatus(ctx.getStatus(),ctx.currentLevel);
    return;
  }

  ctx.termIndex = this->range.min();
  if(ctx.getTerm()!=this->getTerm()->type){
    ctx.setStatus(NodeContext::FALSE);
  }else{
    ctx.next();
    ctx.setStatus(NodeContext::TRUE);
  }

  if(this->areWeCurrent(ctx))
    this->parentMatch(ctx);

  printStatus(ctx.getStatus(),ctx.currentLevel);
}

std::string TermNode::str()const{
  std::stringstream ss;
  ss<<this->getTerm()->str();
  return ss.str();
}


