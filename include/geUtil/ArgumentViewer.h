#pragma once

#include<iostream>
#include<vector>
#include<memory>
#include<geUtil/Export.h>

namespace ge{
  namespace util{
    class ArgumentViewerImpl;
    class ArgumentViewer;
  }
}

class GEUTIL_EXPORT ge::util::ArgumentViewer{
  public:
    ArgumentViewer(int argc,char*argv[]);
    ~ArgumentViewer();
    std::string getApplicationName()const;
    size_t      getNofArguments()const;
    std::string getArgument(size_t const&index)const;
    bool                    isPresent(std::string const&argument                                           )const;
    float                   getf32   (std::string const&argument   ,float                   const&def = 0.f)const;
    double                  getf64   (std::string const&argument   ,double                  const&def = 0. )const;
    int32_t                 geti32   (std::string const&argument   ,int32_t                 const&def = 0  )const;
    int64_t                 geti64   (std::string const&argument   ,int64_t                 const&def = 0  )const;
    uint32_t                getu32   (std::string const&argument   ,uint32_t                const&def = 0  )const;
    uint64_t                getu64   (std::string const&argument   ,uint64_t                const&def = 0  )const;
    std::string             gets     (std::string const&argument   ,std::string             const&def = "" )const;
    std::vector<float   >   getf32v  (std::string const&argument   ,std::vector<float   >   const&def = {} )const;
    std::vector<double  >   getf64v  (std::string const&argument   ,std::vector<double  >   const&def = {} )const;
    std::vector<int32_t >   geti32v  (std::string const&argument   ,std::vector<int32_t >   const&def = {} )const;
    std::vector<int64_t >   geti64v  (std::string const&argument   ,std::vector<int64_t >   const&def = {} )const;
    std::vector<uint32_t>   getu32v  (std::string const&argument   ,std::vector<uint32_t>   const&def = {} )const;
    std::vector<uint64_t>   getu64v  (std::string const&argument   ,std::vector<uint64_t>   const&def = {} )const;
    std::vector<std::string>getsv    (std::string const&contextName,std::vector<std::string>const&def = {} )const;
    std::shared_ptr<ArgumentViewer>getContext(std::string const&name);
    bool validate()const;
    std::string toStr()const;
  protected:
    std::unique_ptr<ArgumentViewerImpl>_impl;
    friend class ArgumentViewerImpl;
};
