#pragma once

#include<geParser/Export.h>
#include<geParser/NodeContext.h>

namespace ge{
  namespace parser{
    class SyntaxNode: public std::enable_shared_from_this<SyntaxNode>{
      public:
        using Parent       = SyntaxNode*;
        using SharedSymbol = std::shared_ptr<Symbol>;
        using Node         = std::shared_ptr<SyntaxNode>;
        using ChildList    = std::vector<Node>;
        using ChildIndex   = ChildList::size_type;
        Parent           parent       ;
        ChildIndex       childInParent;
        SharedSymbol     symbol       ;
        Range<TokenIndex>range        ;
        bool             canWait      ;
        inline SyntaxNode(
            Parent           const& parent       ,
            ChildIndex       const& childInParent,
            Range<TokenIndex>const& range        ,
            SharedSymbol     const& symbol       ,
            bool             const& canWait      );
        virtual ~SyntaxNode();
        virtual void match(NodeContext&ctx)=0;
        inline void parentMatch(NodeContext&ctx);
        inline std::shared_ptr<Nonterm>getNonterm()const;
        inline std::shared_ptr<Term>   getTerm   ()const;
        inline bool isNonterm()const;
        inline bool areWeCurrent(NodeContext&ctx)const;
        virtual std::string str()const = 0;
    };

    inline SyntaxNode::SyntaxNode(
        Parent          const& parent       ,
        ChildIndex      const& childInParent,
        Range<TokenIndex>const& range        ,
        SharedSymbol    const& symbol       ,
        bool            const& canWait      ){
      this->parent        = parent       ;
      this->childInParent = childInParent;
      this->range         = range        ;
      this->symbol        = symbol       ;
      this->canWait       = canWait      ;
    }

    inline SyntaxNode::~SyntaxNode(){
    }


    inline void SyntaxNode::parentMatch(NodeContext&ctx){
      ctx.calledFromChildOrRecheck = true;
      auto p=this->parent;//.lock();
      bool moveLevel = ctx.currentLevel!=0;
      if(moveLevel)ctx.currentLevel--;
      if(p)p->match(ctx);
      if(moveLevel)ctx.currentLevel++;
    }

    inline std::shared_ptr<Nonterm>SyntaxNode::getNonterm()const{
      return std::dynamic_pointer_cast<Nonterm>(this->symbol);
    }

    inline std::shared_ptr<Term>   SyntaxNode::getTerm   ()const{
      return std::dynamic_pointer_cast<Term>(this->symbol);
    }

    inline bool SyntaxNode::isNonterm()const{
      return this->getNonterm()!=nullptr;
    }

    inline bool SyntaxNode::areWeCurrent(NodeContext&ctx)const{
      return this->shared_from_this()==ctx.getNode();
    }
  }
}
