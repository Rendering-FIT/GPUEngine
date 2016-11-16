#include<geParser/SyntaxTreeProcessor.h>

using namespace ge::parser;

void SyntaxTreeProcessor::addCallback(
    std::string nonterm ,
    std::string ruleName,
    Callback    pre     ,
    Callback    post    ){
  this->_callbacks[Key(nonterm,ruleName)]=Value(pre,post);
}

void SyntaxTreeProcessor::operator()(SyntaxNode::Node root)const{
  if(!root->isNonterm())return;
  auto n = std::dynamic_pointer_cast<NontermNode>(root);
  auto key = Key(n->getNonterm()->name,n->getNonterm()->getRuleName(n->side));
  auto ii = this->_callbacks.find(key);
  bool hasCallback = ii!=this->_callbacks.end();

  if(!hasCallback){
    key = Key(n->getNonterm()->name,"");
    ii = this->_callbacks.find(key);
    hasCallback = ii!=this->_callbacks.end();
  }

  if(hasCallback&&std::get<PRE>(ii->second))std::get<PRE>(ii->second)(root);
  for(auto x:n->childs)
    this->operator()(x);
  if(hasCallback&&std::get<POST>(ii->second))std::get<POST>(ii->second)(root);
}

