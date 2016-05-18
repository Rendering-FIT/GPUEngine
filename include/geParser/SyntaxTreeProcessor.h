#pragma once

#include<geParser/Export.h>
#include<geParser/SyntaxTree.h>

namespace ge{
  namespace parser{
    class GEPARSER_EXPORT SyntaxTreeProcessor{
      public:
        using Callback = void(*)(SyntaxNode::Node node,void*data);
        using Key      = std::pair<std::string,std::string>;
        using Value    = std::tuple<Callback,Callback,void*>;
        enum ValueParts{
          PRE  = 0,
          POST = 1,
          DATA = 2,
        };
      protected:
        std::map<Key,Value>_callbacks;
      public:
        void addCallback(
            std::string nonterm           ,
            std::string ruleName          ,
            Callback    pre      = nullptr,
            Callback    post     = nullptr,
            void*       data     = nullptr);
        void operator()(SyntaxNode::Node root)const;
    };
  }
}
