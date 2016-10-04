#include<geAd/LibraryLoader/LibraryLoader.h>

#include<vector>
#include<map>

using namespace ge::ad;

#ifdef __linux__
#include<dlfcn.h>

class LinuxLibraryLoader: public LibraryLoader{
  public:
    using OpenLibraries = std::vector<void*>;
  protected:
    std::map<std::string,OpenLibraries::size_type>_openLibraries;
    OpenLibraries _vectorOfOpenLibraries;
  public:
    LinuxLibraryLoader(){}
    virtual ~LinuxLibraryLoader(){
      auto ii=this->_openLibraries.begin();
      for(;ii!=this->_openLibraries.end();++ii)
        dlclose(this->_vectorOfOpenLibraries[ii->second]);
    }
    virtual OpenLibraries::size_type load(std::string name){
      if(this->_openLibraries.count(name))return this->_openLibraries[name];
      void*lib=dlopen(name.c_str(),RTLD_LAZY);
      if(!lib){
        std::cerr<<dlerror()<<std::endl;
        return 0;
      }
      this->_vectorOfOpenLibraries.push_back(lib);
      this->_openLibraries[name]=this->_vectorOfOpenLibraries.size()-1;
      return this->_vectorOfOpenLibraries.size()-1;
    }
    void*get(OpenLibraries::size_type i,std::string name){
      if(i>=this->_vectorOfOpenLibraries.size()){
        std::cerr<<"LinuxLibraryLoader::get("<<i<<","<<name<<
          ") is out of range=<0,"<<this->_vectorOfOpenLibraries.size()-1<<">";
        return nullptr;
      }
      void*fce=dlsym(this->_vectorOfOpenLibraries[i],name.c_str());
      if(!fce){
        std::cerr<<dlerror()<<std::endl;
        return nullptr;
      }
      return fce;
    }
};


LibraryLoader*ge::ad::getLoader(){
  return new LinuxLibraryLoader();
}

#else//__linux__

LibraryLoader*ge::ad::getLoader(){
  return nullptr;
}

//TODO Windows - MSVC, MinGW

#endif//__linux__

