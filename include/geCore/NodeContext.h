#pragma once

#include<vector>
#include<memory>
#include<map>
#include<set>
#include<geCore/grammar.h>

namespace ge{
  namespace core{
    class SyntaxNode;
    class NodeContext{
      public:
        using Node      = std::shared_ptr<SyntaxNode>;
        enum Status{TRUE=0,WAITING=1,FALSE=2};
        //DEF_ENUM(Status,TRUE,WAITING,FALSE);

        Status     status                  ;
        bool       calledFromChildOrRecheck;
        TermList   terms                   ;
        TermIndex  termIndex               ;
        TermIndex  virtualEnd              ;
        Node       currentNode             ;
        unsigned   currentLevel            ;
        unsigned   maxLevel                ;

        class DatabaseKey: public std::pair<std::shared_ptr<Symbol>,Range<TermIndex>>{
          public:
            DatabaseKey():std::pair<std::shared_ptr<Symbol>,Range<TermIndex>>(){}
            DatabaseKey(std::shared_ptr<Symbol>const&sym,Range<TermIndex>const&range):std::pair<std::shared_ptr<Symbol>,Range<TermIndex>>(sym,range){}

            bool operator<(const DatabaseKey&other)const{
              if(this->first<other.first)return true;
              if(this->first>other.first)return false;
              return this->second<other.second;
            }
        };
        //using DatabaseKey = std::pair<std::shared_ptr<Symbol>,Range<TermIndex>>;
        std::map<DatabaseKey,std::shared_ptr<SyntaxNode>>matches;
        std::set<DatabaseKey>failedMatches;
        inline NodeContext(Node const&currentNode = nullptr);
        inline void setNode(Node const&currentNode = nullptr);
        inline Node const&getNode()const;
        inline void addTerm(TermType const&term);
        inline bool end()const;
        inline TermType const&getTerm()const;
        inline void next();
        inline void setStatus(Status status);
        inline Status getStatus()const;
    };

    NodeContext::NodeContext(NodeContext::Node const&currentNode){
      this->currentNode              = currentNode;
      this->termIndex                = 0          ;
      this->virtualEnd               = 0          ;
      this->calledFromChildOrRecheck = false      ;
    }

    void NodeContext::setNode(NodeContext::Node const&currentNode){
      this->currentNode = currentNode;
    }

    NodeContext::Node const&NodeContext::getNode()const{
      return this->currentNode;
    }

    void NodeContext::addTerm(TermType const&term){
      this->terms.push_back(term);
    }

    bool NodeContext::end()const{
      return this->termIndex>=this->terms.size();
    }

    TermType const&NodeContext::getTerm()const{
      return this->terms[this->termIndex];
    }

    void NodeContext::next(){
      this->termIndex++;
    }

    void NodeContext::setStatus(Status status){
      this->status = status;
    }

    NodeContext::Status NodeContext::getStatus()const{
      return this->status;
    }
  }
}

