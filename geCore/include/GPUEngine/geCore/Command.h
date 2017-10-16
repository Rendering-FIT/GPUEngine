#pragma once

#include<vector>
#include<memory>

#include<GPUEngine/geCore/gecore_export.h>
#include<GPUEngine/geCore/Functor.h>

namespace ge{
  namespace core{
    class GECORE_EXPORT Command : public Functor{
      public:
        virtual void operator()(){};
        virtual ~Command(){};
    };

    class GECORE_EXPORT CommandList: public std::vector<Command*>, public Command{
      public:
        CommandList();
        virtual ~CommandList();
        virtual void operator()()override;
    };

    class GECORE_EXPORT SharedCommandList: public std::vector<std::shared_ptr<Command>>, public Command{
      public:
        SharedCommandList();
        virtual ~SharedCommandList();
        virtual void operator()()override;
    };

  }
}
