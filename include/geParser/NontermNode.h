#pragma once

#include<geParser/Export.h>
#include<geParser/NodeContext.h>
#include<geParser/SyntaxNode.h>

namespace ge{
  namespace parser{
    class GEPARSER_EXPORT NontermNode: public SyntaxNode{
      public:
        using SideIndex = Nonterm::SideIndex;
        using SymbolIndex = Nonterm::SymbolIndex;
        SideIndex   side;
        SymbolIndex item;
        ChildList childs;
        std::vector<Range<TokenIndex>>divisions;
        inline NontermNode(
            Parent           const& parent       ,
            ChildIndex       const& childInParent,
            Range<TokenIndex>const& range        ,
            SharedSymbol     const& symbol       ,
            bool             const& canWait      );
        inline virtual ~NontermNode();
        inline Node const&lastChild()const;
        virtual void match(NodeContext&ctx);
        virtual std::string str()const;
    };

    inline NontermNode::NontermNode(
        Parent           const& parent       ,
        ChildIndex       const& childInParent,
        Range<TokenIndex>const& range        ,
        SharedSymbol     const& symbol       ,
        bool             const& canWait      ):
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
      return this->childs.back();
    }
  }
}
