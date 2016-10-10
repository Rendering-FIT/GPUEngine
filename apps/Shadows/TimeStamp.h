#pragma once

#include<functional>
#include<geGL/geGL.h>
#include<string>

class TimeStamp: public ge::gl::Context{
  public:
    TimeStamp(std::function<void(std::vector<std::string>const&,std::vector<float>const&)>const&printer = [](std::vector<std::string>const&names,std::vector<float>const&times){
        for(size_t i=0;i<names.size();++i)std::cout<<names[i]<<": "<<times[i]<<std::endl;});
    ~TimeStamp();
    void setPrinter(std::function<void(std::vector<std::string>const&,std::vector<float>const&)>const&printer);
    void begin();
    void stamp(std::string const&name);
    void end(std::string const&name);
  protected:
    std::function<void(std::vector<std::string>const&,std::vector<float>const&)>_printer = nullptr;
    void _createQuery(std::string const&name);
    size_t _currentStamp = 0;
    GLuint _beginQuery;
    std::vector<GLuint>_queries;
    std::vector<float>_times;
    std::vector<std::string>_names;
};
