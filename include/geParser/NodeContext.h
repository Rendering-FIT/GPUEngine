#pragma once

#include<vector>
#include<memory>
#include<map>
#include<set>
#include<geParser/Grammar.h>

namespace ge{
  namespace parser{
    class SyntaxNode;
    class NodeContext{
      public:
        using Node      = std::shared_ptr<SyntaxNode>;
        enum Status{TRUE_STATUS=0,WAITING_STATUS=1,FALSE_STATUS=2};
        //DEF_ENUM(Status,TRUE,WAITING,FALSE);

        Status     status                  ;
        bool       calledFromChildOrRecheck;
        TokenList  tokens                  ;
        TokenIndex tokenIndex              ;
        TokenIndex virtualEnd              ;
        Node       currentNode             ;
        unsigned   currentLevel            ;
        unsigned   maxLevel                ;

        class DatabaseKey: public std::pair<std::shared_ptr<Symbol>,Range<TokenIndex>>{
          public:
            DatabaseKey():std::pair<std::shared_ptr<Symbol>,Range<TokenIndex>>(){}
            DatabaseKey(std::shared_ptr<Symbol>const&sym,Range<TokenIndex>const&range):std::pair<std::shared_ptr<Symbol>,Range<TokenIndex>>(sym,range){}

            bool operator<(const DatabaseKey&other)const{
              if(this->first<other.first)return true;
              if(this->first>other.first)return false;
              return this->second<other.second;
            }
        };
        //using DatabaseKey = std::pair<std::shared_ptr<Symbol>,Range<TokenIndex>>;
        std::map<DatabaseKey,std::shared_ptr<SyntaxNode>>matches;
        std::set<DatabaseKey>failedMatches;
        inline NodeContext(Node const&currentNode = nullptr);
        inline void setNode(Node const&currentNode = nullptr);
        inline Node const&getNode()const;
        inline void addToken(Token const&term);
        inline bool end()const;
        inline Token const&getToken()const;
        inline void next();
        inline void setStatus(Status status);
        inline Status getStatus()const;
    };

    NodeContext::NodeContext(NodeContext::Node const&currentNode){
      this->currentNode              = currentNode;
      this->tokenIndex               = 0          ;
      this->virtualEnd               = 0          ;
      this->calledFromChildOrRecheck = false      ;
    }

    void NodeContext::setNode(NodeContext::Node const&currentNode){
      this->currentNode = currentNode;
    }

    NodeContext::Node const&NodeContext::getNode()const{
      return this->currentNode;
    }

    void NodeContext::addToken(Token const&token){
      this->tokens.push_back(token);
    }

    bool NodeContext::end()const{
      return this->tokenIndex>=this->tokens.size();
    }

    Token const&NodeContext::getToken()const{
      return this->tokens[this->tokenIndex];
    }

    void NodeContext::next(){
      this->tokenIndex++;
    }

    void NodeContext::setStatus(Status status){
      this->status = status;
    }

    NodeContext::Status NodeContext::getStatus()const{
      return this->status;
    }
  }
}

