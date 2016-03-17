#pragma once

#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<memory>
#include<sstream>
#include<cstring>
#include<geCore/dtemplates.h>
#include<geCore/Export.h>
#include<geCore/syntaxTree.h>

namespace ge{
  namespace core{

    class GECORE_EXPORT Syntax{
      public:
        NodeContext ctx;
        SyntaxNode::Node st_root=nullptr;
        std::string start;
        std::map<std::string,std::shared_ptr<Symbol>>name2Nonterm;
        std::map<TermType   ,std::shared_ptr<Symbol>>name2Term   ;

        std::shared_ptr<SyntaxNode>root = nullptr;
        std::shared_ptr<SyntaxNode>currentNode = nullptr;

        std::shared_ptr<Symbol>const&_addNonterm(std::string    name);
        std::shared_ptr<Symbol>const&_addTerm   (TermType const&type);

        std::map<TermType,std::string>_termNames;

        using Callback = void(*)(SyntaxNode::Node node,void*data);
        using Key      = std::pair<std::shared_ptr<Nonterm>,NontermNode::SideIndex>;
        using Value    = std::tuple<Callback,Callback,void*>;
        std::map<Key,Value>_callbacks;
        Range<TermIndex> _range;
      public:
        Syntax(std::string start);
        ~Syntax();
        void processTree(std::shared_ptr<SyntaxNode>const&root);
        void runStart();
        NodeContext::Status runContinue();
        SyntaxNode::Node getSyntaxTree()const;
        void registerTermName(TermType term,std::string name);

        template<typename...>
          void addTerm();
        template<typename...ARGS>
          void addTerm(TermType const&term,ARGS...args);

        void addRule(
            std::string nonterm,
            std::vector<std::weak_ptr<Symbol>>side);

        template<typename...>
          void addSymbol2Side(
              std::vector<std::weak_ptr<Symbol>>&side);
        template<typename...ARGS>
          void addSymbol2Side(
              std::vector<std::weak_ptr<Symbol>>&side,
              std::string sym,
              ARGS...args);
        template<typename...ARGS>
          void addSymbol2Side(
              std::vector<std::weak_ptr<Symbol>>&side,
              TermType sym,
              ARGS...args);
        template<typename...ARGS>
          void addSymbol2Side(
              std::vector<std::weak_ptr<Symbol>>&,
              Callback,ARGS...);

        template<typename...ARGS>
          void getCallback(Value&value,TermType,ARGS...);
        template<typename...ARGS>
          void getCallback(Value&value,std::string,ARGS...);
        template<typename...>
          void getCallback(Value&);
        template<typename...ARGS>
          void getCallback(Value&value,Callback,ARGS...);

        void createCallback(Value&value,Callback pre=nullptr,Callback post=nullptr,void*data=nullptr);

        void addCallback(std::string name,NontermNode::SideIndex side,Callback pre=nullptr,Callback post=nullptr,void*data=nullptr);


        template<typename...ARGS>
          void addRule(std::string nonterm,ARGS...args);

        void computeLengths();
        std::string str()const;
    };

    template<typename...>
      void Syntax::addTerm(){
      }

    template<typename...ARGS>
      void Syntax::addTerm(TermType const&term,ARGS...args){
        this->ctx.addTerm(term);
        this->addTerm(args...);
      }

    template<typename...>
      void Syntax::addSymbol2Side(
          std::vector<std::weak_ptr<Symbol>>&){
      }

    template<typename...ARGS>
      void Syntax::addSymbol2Side(
          std::vector<std::weak_ptr<Symbol>>&side,
          std::string sym,
          ARGS...args){
        side.push_back(this->_addNonterm(sym));
        this->addSymbol2Side(side,args...);
      }

    template<typename...ARGS>
      void Syntax::addSymbol2Side(
          std::vector<std::weak_ptr<Symbol>>&side,
          TermType sym,
          ARGS...args){
        side.push_back(this->_addTerm(sym));
        this->addSymbol2Side(side,args...);
      }

    template<typename...ARGS>
      void Syntax::addSymbol2Side(
          std::vector<std::weak_ptr<Symbol>>&,
          Callback,ARGS...){
      }

    template<typename...ARGS>
      void Syntax::getCallback(Value&value,TermType,ARGS...args){
        this->getCallback(value,args...);
      }

    template<typename...ARGS>
      void Syntax::getCallback(Value&value,std::string,ARGS...args){
        this->getCallback(value,args...);
      }

    template<typename...>
      void Syntax::getCallback(Value&){
      }

    template<typename...ARGS>
      void Syntax::getCallback(Value&value,Callback a,ARGS...args){
        this->createCallback(value,a,args...);
      }

    template<typename...ARGS>
      void Syntax::addRule(std::string nonterm,ARGS...args){
        std::vector<std::weak_ptr<Symbol>>side;
        this->addSymbol2Side(side,args...);
        auto n=this->_addNonterm(nonterm);
        auto ptr=std::dynamic_pointer_cast<Nonterm>(n);
        auto sideIndex = ptr->addSide(side);
        Value v;
        this->getCallback(v,args...);
        //if(std::get<2>(v))std::cout<<"insert callback to: "<<nonterm<<" side: "<<sideIndex<<std::endl;
        this->addCallback(nonterm,sideIndex,std::get<0>(v),std::get<1>(v),std::get<2>(v));
      }

  }
}
