#pragma once

#include<geCore/NodeContext.h>
#include<geCore/syntaxNode.h>

namespace ge{
  namespace core{
    class NontermNode: public SyntaxNode{
      public:
        using SideIndex = Nonterm::SideIndex;
        using SymbolIndex = Nonterm::SymbolIndex;
        SideIndex   side;
        SymbolIndex item;
        ChildList childs;
        std::vector<Range<TermIndex>>divisions;
        inline NontermNode(
            Parent          const& parent       ,
            ChildIndex      const& childInParent,
            Range<TermIndex>const& range        ,
            SharedSymbol    const& symbol       ,
            bool            const& canWait      );
        inline virtual ~NontermNode();
        inline Node const&lastChild()const;
        virtual void match(NodeContext&ctx);
        virtual std::string str()const;
    };

    inline NontermNode::NontermNode(
        Parent          const& parent       ,
        ChildIndex      const& childInParent,
        Range<TermIndex>const& range        ,
        SharedSymbol    const& symbol       ,
        bool            const& canWait      ):
      SyntaxNode(
          parent       ,
          childInParent,
          range        ,
          symbol       ,
          canWait      ){
        this->side = 0;
        this->item = 0;
      }

    inline NontermNode::~NontermNode(){
    }

    inline NontermNode::Node const&NontermNode::lastChild()const{
      return this->childs[this->childs.size()-1];
    }
  }
}
