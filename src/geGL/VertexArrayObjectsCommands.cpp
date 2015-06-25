#include<geGL/VertexArrayObjectsCommands.h>

using namespace ge::gl;

GenVertexArrays::GenVertexArrays(
    GLsizei  n,
    GLuint  *arrays){
  this->n      = n;
  this->arrays = arrays;
}
void GenVertexArrays::operator()(){
  glGenVertexArrays(
      this->n,
      this->arrays);
}
DeleteVertexArrays::DeleteVertexArrays(
    GLsizei  n,
    GLuint  *arrays){
  this->n      = n;
  this->arrays = arrays;
}
void DeleteVertexArrays::operator()(){
  glDeleteVertexArrays(
      this->n,
      this->arrays);
}
BindVertexArray::BindVertexArray(GLuint *array){
  this->array = array;
}
void BindVertexArray::operator()(){
  glBindVertexArray(*this->array);
}
CreateVertexArrays::CreateVertexArrays(
    GLsizei  n,
    GLuint  *arrays){
  this->n      = n;
  this->arrays = arrays;
}

void CreateVertexArrays::operator()()
{

}

/*
   void CreateVertexArrays::operator()(){
   glCreateVertexArrays(
   this->n,
   this->arrays);
   }*/
