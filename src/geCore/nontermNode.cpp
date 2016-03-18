#include<geCore/nontermNode.h>
#include<geCore/termNode.h>

using namespace ge::core;

void NontermNode::match(NodeContext&ctx){
  if(this->symbol->range.min()>this->range.length()&&!this->canWait){
    ctx.setStatus(NodeContext::FALSE_STATUS);
    if(ctx.calledFromChildOrRecheck)
      this->parentMatch(ctx);
    return;
  }

  if(!ctx.calledFromChildOrRecheck){
    auto c=this->parent.lock();
    while(c){
      if(c->getNonterm()==this->getNonterm()&&c->range==this->range){
        ctx.setStatus(NodeContext::FALSE_STATUS);
        if(ctx.calledFromChildOrRecheck)
          this->parentMatch(ctx);
        return;
      }
      c=c->parent.lock();
    }
  }

  if(this->symbol->range.max()<this->range.length()){
    ctx.setStatus(NodeContext::FALSE_STATUS);
    if(ctx.calledFromChildOrRecheck)
      this->parentMatch(ctx);
    return;
  }

  if(this->range.empty()){
    ctx.setStatus(NodeContext::WAITING_STATUS);
    ctx.setNode(this->shared_from_this());
    return;
  }

  if(
      !ctx.calledFromChildOrRecheck&&
      !this->symbol->prefixMatch(ctx.getToken().type)){
    ctx.setStatus(NodeContext::FALSE_STATUS);
    if(ctx.calledFromChildOrRecheck)
      this->parentMatch(ctx);
    return;
  }

  auto printStatus=[](NodeContext::Status status,unsigned currentLevel){
#ifndef DEBUG
    return;
#endif
    std::string statusName[3]={"TRUE","WAITING","FALSE"};
    for(unsigned i=0;i<currentLevel;++i)
      std::cout<<"  ";
    std::cout<<statusName[status]<<std::endl;
  };

  bool cfc=ctx.calledFromChildOrRecheck;
  bool cfc2=cfc;
  if(this->areWeCurrent(ctx))
    cfc = true;



  ctx.calledFromChildOrRecheck=false;
  while(true){
    if(!cfc2){
#ifdef DEBUG
      for(unsigned i=0;i<ctx.currentLevel;++i)
        std::cout<<"  ";
      std::cout<<"<"<<this->getNonterm()->name<<"> ->";
      decltype(this->item)counter=0;
      for(auto x:std::get<Nonterm::SYMBOLS>(this->getNonterm()->rightSides[this->side])){
        std::cout<<" ";
        if(counter==this->item)
          std::cout<<"(";
        std::cout<<x.lock()->name;
        if(counter==this->item)
          std::cout<<")";
        counter++;
      }
      std::cout<<" "<<this->range.str()<<" ";
      std::cout<<std::endl;
#endif

      auto n=this->getNonterm();
      auto subsym=n->getSymbol(this->side,this->item);
      std::shared_ptr<SyntaxNode>newNode;
      if(this->divisions.size()!=this->item+1){
        if(this->item+1==n->nofSymbols(this->side))
          this->divisions.push_back(Range<TokenIndex>(ctx.tokenIndex,this->range.max()));
        else
          this->divisions.push_back(Range<TokenIndex>(ctx.tokenIndex,ctx.tokenIndex+subsym->range.min()));
      }
      bool cWait=false;
      if(!this->canWait){
        if(this->range.max()<this->divisions.back().max()+this->getNonterm()->getTail(this->side,this->item).min()){
          if(this->range.max()<this->divisions.back().min()+this->getNonterm()->getTail(this->side,this->item).min())
            this->divisions.back().max()=this->divisions.back().min();
          else
            this->divisions.back().max()=this->range.max()-this->getNonterm()->getTail(this->side,this->item).min();
        }
      }else{
        if(this->range.max()<=this->divisions.back().max()){
          this->divisions.back().max()=this->range.max();
          cWait=this->canWait;
        }
      }
#define USE_DATABASE
#define USE_FAILEDDATABASE
#ifdef USE_DATABASE
      auto ii=ctx.matches.find(NodeContext::DatabaseKey(subsym,this->divisions.back()));
      if(ii!=ctx.matches.end()){
        this->childs.push_back(ii->second);
        auto c=this->lastChild();
        while(c){
          c->canWait = cWait;
          if(c->getNonterm())
            c=std::dynamic_pointer_cast<NontermNode>(c)->lastChild();
          else c=nullptr;
        }
        //TODO set canWait correctly 
        ctx.setStatus(NodeContext::TRUE_STATUS);
        ctx.tokenIndex = ii->second->range.max();
      }else{
#endif
#ifdef USE_FAILEDDATABASE
        auto jj=ctx.failedMatches.find(NodeContext::DatabaseKey(subsym,this->divisions.back()));
        if(jj!=ctx.failedMatches.end()){
          this->childs.push_back(nullptr);
          //TODO set canWait correctly 
          ctx.setStatus(NodeContext::FALSE_STATUS);
          ctx.tokenIndex = jj->second.min();
        }else{
#endif
          if(std::dynamic_pointer_cast<Nonterm>(subsym))
            newNode = std::make_shared<NontermNode>(
                this->shared_from_this(),
                this->childs.size(),
                this->divisions.back(),
                subsym,
                cWait);
          else
            newNode = std::make_shared<TermNode>(
                this->shared_from_this(),
                this->childs.size(),
                this->divisions.back(),
                subsym,
                cWait);
          this->childs.push_back(newNode);
          ctx.currentLevel++;
          this->lastChild()->match(ctx);
          ctx.currentLevel--;
#ifdef USE_FAILEDDATABASE
        }
#endif
#ifdef USE_DATABASE
      }
#endif
    }
    cfc2 = false;
    switch(ctx.getStatus()){
      case NodeContext::TRUE_STATUS:
#ifdef USE_DATABASE
        ctx.matches[NodeContext::DatabaseKey(this->lastChild()->symbol,this->divisions.back())]=this->lastChild();
#endif
        if(this->item+1==this->getNonterm()->nofSymbols(this->side)){
          if(cfc)this->parentMatch(ctx);
          printStatus(ctx.getStatus(),ctx.currentLevel);
          return;
        }
        this->item++;
        break;
      case NodeContext::FALSE_STATUS:
#ifdef USE_FAILEDDATABASE
        if(this->lastChild())
          ctx.failedMatches.insert(NodeContext::DatabaseKey(this->lastChild()->symbol,this->divisions.back()));
#endif
        do{
          if(!this->childs.empty())this->childs.pop_back();
          if(this->divisions.empty())break;
          this->divisions.back().max()++;
          auto len=this->divisions.back().length();
          auto maxLen = this->getNonterm()->getSymbol(this->side,this->item)->range.max();
          if(
              len>maxLen||
              (!this->canWait &&
               this->range.max()<this->divisions.back().max()+this->getNonterm()->getTail(this->side,this->item).min())||
              (this->canWait && 
               this->range.max()<this->divisions.back().max())
            ){
            this->divisions.pop_back();
            if(this->item>0)this->item--;
            continue;
          }
          break;
        }while(true);

        if(this->divisions.empty()){
          ctx.tokenIndex = this->range.min();
          if(this->side+1==this->getNonterm()->rightSides.size()){
            if(cfc)this->parentMatch(ctx);
            printStatus(ctx.getStatus(),ctx.currentLevel);
            return;
          }
          this->side++;
          this->item=0;
        }else ctx.tokenIndex = this->divisions.back().min();
        break;
      case NodeContext::WAITING_STATUS:
        printStatus(ctx.getStatus(),ctx.currentLevel);
        return;
    }
  }
  printStatus(ctx.getStatus(),ctx.currentLevel);
  return;
}

std::string NontermNode::str()const{
  std::stringstream ss;
  ss<<"<"<<this->getNonterm()->name<<">"<<"(";
  for(ChildIndex i=0;i<this->childs.size();++i)
    ss<<this->childs[i]->str();
  ss<<")";
  return ss.str();
}

