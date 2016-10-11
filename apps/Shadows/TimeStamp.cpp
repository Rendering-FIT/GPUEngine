#include"TimeStamp.h"

TimeStamp::TimeStamp(std::function<void(std::vector<std::string>const&,std::vector<float>const&)>const&printer):_printer(printer){
  assert(this!=nullptr);
  this->_currentStamp = 0;
  glCreateQueries(GL_TIMESTAMP,1,&this->_beginQuery);
}

TimeStamp::~TimeStamp(){
  assert(this!=nullptr);
  glDeleteQueries((GLsizei)this->_queries.size(),this->_queries.data());
  glDeleteQueries(1,&this->_beginQuery);
}

void TimeStamp::setPrinter(std::function<void(std::vector<std::string>const&,std::vector<float>const&)>const&printer){
  assert(this!=nullptr);
  this->_printer = printer;
}

void TimeStamp::_createQuery(std::string const&name){
  assert(this!=nullptr);
  assert(this->_queries.size()<1000);
  if(this->_currentStamp<this->_queries.size())return;
  GLuint q;
  glCreateQueries(GL_TIMESTAMP,1,&q);
  this->_queries.push_back(q);
  this->_names.push_back(name);
  this->_times.push_back(0.f);
}

void TimeStamp::begin(){
  glQueryCounter(this->_beginQuery,GL_TIMESTAMP);
  this->_currentStamp = 0;
}

void TimeStamp::stamp(std::string const&name){
  this->_createQuery(name);
  glQueryCounter(this->_queries.at(this->_currentStamp),GL_TIMESTAMP);
  this->_currentStamp++;
}

void TimeStamp::end(std::string const&name){
  this->_createQuery(name);
  glQueryCounter(this->_queries.at(this->_currentStamp),GL_TIMESTAMP);
  GLuint64 beginTime = 0;
  glGetQueryObjectui64v(this->_beginQuery,GL_QUERY_RESULT,&beginTime);
  GLuint64 lastTime = 0;
  for(size_t i=0;i<this->_queries.size();++i){
    GLuint64 time = 0;
    glGetQueryObjectui64v(this->_queries[i], GL_QUERY_RESULT, &time);
    if(i==0)this->_times[i]=float(time-beginTime)*1e-9f;
    else this->_times[i]=float(time-lastTime)*1e-9f;
    lastTime = time;
  }
  if(this->_printer)this->_printer(this->_names,this->_times);
  this->_currentStamp = 0;
}

