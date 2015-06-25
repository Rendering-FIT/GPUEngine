#include <geGL/OcclusionQueriesCommands.h>

using namespace ge::gl;

BeginQuery::BeginQuery(GLenum target,GLuint id){
  this->target = target;
  this->id     = id;
}
void BeginQuery::operator()(){
  glBeginQuery(this->target,this->id);
}
EndQuery::EndQuery(GLenum target){
  this->target = target;
}
void EndQuery::operator()(){
  glEndQuery(this->target);
}
