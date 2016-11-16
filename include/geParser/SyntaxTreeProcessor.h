#pragma once

#include<functional>
#include<geParser/Export.h>
#include<geParser/SyntaxTree.h>

namespace ge{
  namespace parser{
    class GEPARSER_EXPORT SyntaxTreeProcessor{
      public:
        using Callback = std::function<void(SyntaxNode::Node)>;
        using Key      = std::pair<std::string,std::string>;
        using Value    = std::tuple<Callback,Callback>;
        enum ValueParts{
          PRE  = 0,
          POST = 1,
        };
      protected:
        std::map<Key,Value>_callbacks;
      public:
        void addCallback(
            std::string nonterm           ,
            std::string ruleName          ,
            Callback    pre      = nullptr,
            Callback    post     = nullptr);
        void operator()(SyntaxNode::Node root)const;
    };
  }
}
