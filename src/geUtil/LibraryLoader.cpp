#include<geUtil/LibraryLoader.h>

#include<vector>
#include<map>

using namespace ge::util;

#ifdef __linux__
#include<dlfcn.h>

class LinuxLibraryLoader: public LibraryLoader{
  protected:
    std::map<std::string,unsigned>_openLibraries;
    std::vector<void*>_vectorOfOpenLibraries;
  public:
    LinuxLibraryLoader(){}
    virtual ~LinuxLibraryLoader(){
      std::map<std::string,unsigned>::iterator ii=this->_openLibraries.begin();
      for(;ii!=this->_openLibraries.end();++ii)
        dlclose(this->_vectorOfOpenLibraries[ii->second]);
    }
    virtual unsigned load(std::string name){
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
    void*get(unsigned i,std::string name){
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


LibraryLoader*ge::util::getLoader(){
  return new LinuxLibraryLoader();
}

#else//__linux__

LibraryLoader*ge::util::getLoader(){
  return nullptr;
}

//TODO Windows - MSVC, MinGW

#endif//__linux__

