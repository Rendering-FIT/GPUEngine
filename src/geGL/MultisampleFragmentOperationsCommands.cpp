#include <geGL/MultisampleFragmentOperationsCommands.h>

namespace ge
{
  namespace gl
  {
    SampleCoverage::SampleCoverage(GLfloat value,GLboolean invert){
      this->value  = value;
      this->invert = invert;
    }
    void SampleCoverage::apply(){
      glSampleCoverage(this->value,this->invert);
    }

    SampleMaski::SampleMaski(GLuint maskNumber,GLbitfield mask){
      this->maskNumber = maskNumber;
      this->mask       = mask;
    }

    void SampleMaski::apply(){
      glSampleMaski(this->maskNumber,this->mask);
    }
  }//ogl
}//ge


