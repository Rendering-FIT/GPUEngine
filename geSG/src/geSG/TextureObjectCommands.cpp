#include <TextureObjectCommands.h>
#include <geGL/TextureObject.h>

using namespace ge::gl;


ge::gl::ActiveTexture::ActiveTexture( GLenum texUnit)
   : textureUnit(texUnit)
{

}

void ge::gl::ActiveTexture::operator()()
{
   glActiveTexture(textureUnit);
}

ge::gl::BindTexture::BindTexture(std::shared_ptr<TextureObject>& texObject, GLenum texUnit)
   : textureObject(texObject)
   , textureUnit(texUnit)
{

}

void ge::gl::BindTexture::operator()()
{
   textureObject->bind(textureUnit);
}
