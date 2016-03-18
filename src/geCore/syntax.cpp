#include<geCore/syntax.h>
#include<cctype>

using namespace ge::core;

Syntax::Syntax(std::string start){
  this->start = start;
}

Syntax::Syntax(std::string start,std::shared_ptr<Tokenization>const&tokenization){
  this->start = start;
  this->_tokenization = tokenization;
}

Syntax::Syntax(std::string lexSource,std::string synSource){
  this->_tokenization = std::make_shared<Tokenization>();
  this->_tokenization->load(lexSource);
  auto syn=std::make_shared<Tokenization>("START");
  syn->addTransition("START"   ," \t"   ,"SPACE"                   );
  syn->addTransition("START"   ,"\r\n"  ,"LINE-END"                );
  syn->addTransition("START"   ,FSA::els,"STRING"  ,""        ,"b" );
  syn->addTransition("START"   ,FSA::eof,"END"                     );

  syn->addTransition("SPACE"   ," \t"   ,"SPACE"                   );
  syn->addTransition("SPACE"   ,"\r\n"  ,"LINE-END"                );
  syn->addTransition("SPACE"   ,FSA::els,"STRING"  ,""        ,"b" );
  syn->addTransition("SPACE"   ,FSA::eof,"END"                     );

  syn->addTransition("LINE-END"," \t"   ,"SPACE"   ,"line-end"     );
  syn->addTransition("LINE-END","\r\n"  ,"LINE-END"                );
  syn->addTransition("LINE-END",FSA::els,"STRING"  ,"line-end","b" );
  syn->addTransition("LINE-END",FSA::eof,"END"                     );

  syn->addTransition("STRING"  ," \t"   ,"SPACE"   ,"value"   ,"e" );
  syn->addTransition("STRING"  ,"\r\n"  ,"LINE-END","value"   ,"eg");
  syn->addTransition("STRING"  ,FSA::els,"STRING"                  );
  syn->addTransition("STRING"  ,FSA::eof,"END"     ,"value"   ,"e" );
  syn->begin();
  syn->parse(synSource);
  syn->end();
  
  bool firstRule = true;
  std::vector<std::string>params;
  while(!syn->empty()){
    auto t=syn->getToken();
    if(syn->tokenName(t.type)=="value"){
      params.push_back(t.rawData);
      continue;
    }
    if(syn->tokenName(t.type)=="line-end"){
      if(params.size()>=3){
        if(firstRule){
          this->start = params[1];
          std::cout<<"#########################"<<this->start<<std::endl;
          firstRule = false;
        }
        this->addRule(params);
      }
      params.clear();
    }
  }
  if(params.size()>=3){
    if(firstRule){
      this->start = params[1];
      firstRule = false;
    }
    this->addRule(params);
  }
  params.clear();

  this->computeLengths();

}

void Syntax::addRule(std::vector<std::string>params){
  if(params.size()<3){
    std::cerr<<"ERROR: Syntax::addRule(";
    bool first=true;
    for(auto x:params){
      if(first)first=false;
      else std::cerr<<",";
      std::cerr<<x;
    }
    std::cerr<<") - rule length has to be at least 3 - ";
    std::cerr<<"rule name, nonterm name, right side symbols"<<std::endl;
    return;
  }
  std::vector<std::weak_ptr<Symbol>>side;
  bool first=true;
  bool second=true;
  for(auto x:params){
    if(first)first=false;
    else if(second)second=false;
    else{
      if(std::isupper(x[0]))side.push_back(this->_addNonterm(x));
      else side.push_back(this->_addTerm(this->_tokenization->tokenType(x)));
    }
  }
  auto n=this->_addNonterm(params[1]);
  auto ptr=std::dynamic_pointer_cast<Nonterm>(n);
  ptr->addSide(side,params[0]);
}

Syntax::~Syntax(){
  this->st_root=nullptr;
}

void Syntax::begin(){
  this->runStart();
  this->_tokenization->begin();
}

std::pair<NodeContext::Status,SyntaxNode::Node>Syntax::parse(std::string data){
  this->_tokenization->parse(data);
  do{
    if(this->_tokenization->empty())break;
    this->addToken(this->_tokenization->getToken());
  }while(true);
  auto status = this->runContinue();
  std::pair<NodeContext::Status,SyntaxNode::Node>result;
  result.first = status;
  result.second = nullptr;
  if(status==NodeContext::TRUE){
    result.second = this->st_root;
  }
  if(status!=NodeContext::WAITING){
    this->ctx.matches.clear();
    this->ctx.failedMatches.clear();
    this->runStart();
    if(status==NodeContext::FALSE)
      std::cerr<<"syntax error"<<std::endl;
  }
  return result;
}

void Syntax::end(){
  this->_tokenization->end();
}

SyntaxNode::Node Syntax::getSyntaxTree()const{
  return this->st_root;
}

void Syntax::runStart(){
  this->ctx.tokens.clear();
  this->_range.min() = 0;
  this->_range.max() = 0;//std::min(this->name2Nonterm[this->start]->minLength,this);
  std::shared_ptr<SyntaxNode>emptyNode=nullptr;
  this->st_root = std::make_shared<NontermNode>(emptyNode,0,this->_range,this->name2Nonterm[this->start],true);
  this->ctx.setNode(this->st_root);
  this->ctx.setStatus(NodeContext::WAITING);
  this->ctx.calledFromChildOrRecheck = false;
  this->ctx.tokenIndex = 0;
  this->ctx.virtualEnd = this->_range.max();
  this->ctx.currentLevel = 0;
}

NodeContext::Status Syntax::runContinue(){
  if(this->ctx.tokens.size()<this->name2Nonterm[this->start]->range.min())
    return NodeContext::WAITING;

  TokenIndex newEnd;
  if(this->_range.max()<this->name2Nonterm[this->start]->range.min())
    newEnd = this->name2Nonterm[this->start]->range.min();
  else
    newEnd = this->_range.max()+1;

  if(newEnd>this->ctx.tokens.size())
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
      if(this->_range.max()>=this->ctx.tokens.size())
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

std::shared_ptr<Symbol>const& Syntax::_addTerm(Token::Type const&type){
  auto ii=this->name2Term.find(type);
  if(ii!=this->name2Term.end())
    return ii->second;
  return this->name2Term[type]=std::make_shared<Term>(type,this->_tokenization->tokenName(type));
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

