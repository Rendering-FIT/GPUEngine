#include<geCore/syntax.h>

using namespace ge::core;

Syntax::Syntax(std::string start){
  this->start = start;
}

Syntax::~Syntax(){
  this->st_root=nullptr;
}

SyntaxNode::Node Syntax::getSyntaxTree()const{
  return this->st_root;
}

void Syntax::registerTermName(TermType term,std::string name){
  this->_termNames[term]=name;
}

void Syntax::processTree(std::shared_ptr<SyntaxNode>const&root){
  if(!root->isNonterm())return;
  auto n = std::dynamic_pointer_cast<NontermNode>(root);
  //std::cout<<n->symbol->name<<" side: "<<n->side<<std::endl;
  auto v=this->_callbacks[Key(n->getNonterm(),n->getNonterm()->getOriginalIndex(n->side))];
  if(std::get<0>(v))std::get<0>(v)(root,std::get<2>(v));
  for(auto x:n->childs)
    this->processTree(x);
  if(std::get<1>(v))std::get<1>(v)(root,std::get<2>(v));
}

void Syntax::runStart(){
  this->ctx.terms.clear();
  this->_range.min() = 0;
  this->_range.max() = 0;//std::min(this->name2Nonterm[this->start]->minLength,this);
  std::shared_ptr<SyntaxNode>emptyNode=nullptr;
  this->st_root = std::make_shared<NontermNode>(emptyNode,0,this->_range,this->name2Nonterm[this->start],true);
  this->ctx.setNode(this->st_root);
  this->ctx.setStatus(NodeContext::WAITING);
  this->ctx.calledFromChildOrRecheck = false;
  this->ctx.termIndex = 0;
  this->ctx.virtualEnd = this->_range.max();
  this->ctx.currentLevel = 0;
}

NodeContext::Status Syntax::runContinue(){
  if(this->ctx.terms.size()<this->name2Nonterm[this->start]->range.min())
    return NodeContext::WAITING;

  TermIndex newEnd;
  if(this->_range.max()<this->name2Nonterm[this->start]->range.min())
    newEnd = this->name2Nonterm[this->start]->range.min();
  else
    newEnd = this->_range.max()+1;

  if(newEnd>this->ctx.terms.size())
    return NodeContext::WAITING;


  do{
    //std::cout<<"######################################################"<<std::endl;
    //std::cout<<"newEnd: "<<newEnd<<std::endl;
    auto node = this->ctx.getNode();
    while(node){
      node->range.max() = newEnd;
      node = node->parent.lock();
    }
    this->_range.max() = newEnd;
    this->ctx.getNode()->match(this->ctx);
    if(this->ctx.getStatus()==NodeContext::WAITING){
      if(this->_range.max()>=this->ctx.terms.size())
        return NodeContext::WAITING;
      newEnd = this->_range.max()+1;
      if(newEnd>=this->name2Nonterm[this->start]->range.max())
        return NodeContext::FALSE;
    }else return this->ctx.getStatus();
  }while(true);
}


std::shared_ptr<Symbol>const&Syntax::_addNonterm(std::string name){
  auto ii=this->name2Nonterm.find(name);
  if(ii!=this->name2Nonterm.end())
    return ii->second;
  return this->name2Nonterm[name]=std::make_shared<Nonterm>(name);
}

std::shared_ptr<Symbol>const& Syntax::_addTerm(TermType const&type){
  auto ii=this->name2Term.find(type);
  if(ii!=this->name2Term.end())
    return ii->second;
  auto jj=this->_termNames.find(type);
  if(jj!=this->_termNames.end())
    return this->name2Term[type]=std::make_shared<Term>(type,jj->second);
  return this->name2Term[type]=std::make_shared<Term>(type);
}

void Syntax::addRule(
    std::string nonterm,
    std::vector<std::weak_ptr<Symbol>>side){
  auto n=this->_addNonterm(nonterm);
  auto ptr=std::dynamic_pointer_cast<Nonterm>(n);
  ptr->addSide(side);
}

void Syntax::createCallback(Value&value,Callback pre,Callback post,void*data){
  std::get<0>(value)=pre ;
  std::get<1>(value)=post;
  std::get<2>(value)=data;
}

void Syntax::addCallback(std::string name,NontermNode::SideIndex side,Callback pre,Callback post,void*data){
  auto v=Value(pre,post,data);
  auto k=Key(std::dynamic_pointer_cast<Nonterm>(this->name2Nonterm[name]),side);
  this->_callbacks[k]=v;
}

std::string Syntax::str()const{
  std::stringstream ss;
  for(auto x:this->name2Nonterm){
    ss<<x.second->range.str();
    for(auto y:std::dynamic_pointer_cast<Nonterm>(x.second)->prefixes){
      ss<<" "<<this->name2Term.find(y)->second->name;
    }
    ss<<std::endl;
    ss<<x.second->str();
  }
  return ss.str();
}

void Syntax::computeLengths(){
  std::set<std::shared_ptr<Nonterm>>allNonterms;
  for(auto x:this->name2Nonterm)
    allNonterms.insert(std::dynamic_pointer_cast<Nonterm>(x.second));

  prepareNonterms(allNonterms);
}

