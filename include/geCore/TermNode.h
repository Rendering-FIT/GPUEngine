#pragma once

#include<geCore/Export.h>
#include<geCore/NodeContext.h>
#include<geCore/SyntaxNode.h>

namespace ge{
  namespace core{
    class GECORE_EXPORT TermNode: public SyntaxNode{
      public:
        Token token;
        TermNode(
            Parent           const& parent       ,
            ChildIndex       const& childInParent,
            Range<TokenIndex>const& range        ,
            SharedSymbol     const& symbol       ,
            bool             const& canWait      );
        virtual ~TermNode();
        virtual void match(NodeContext&ctx);
        virtual std::string str()const;
    };

    inline TermNode::TermNode(
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
      }

    inline TermNode::~TermNode(){
    }
  }
}
