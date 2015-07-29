#pragma once

#include<memory>
#include<geGL/Export.h>
#include<geCore/Command.h>
#include<GL/glew.h>

namespace ge{
  namespace gl{
    class TextureObject;
    class ProgramObject;

    class BindTextureObject2Unit: public ge::core::Command{
      protected:
        GLenum                        _unit   ;
        std::shared_ptr<TextureObject>_texture;
      public:
        BindTextureObject2Unit(
            std::shared_ptr<TextureObject>const&textureObject,
            GLenum                              unit         );
        virtual void operator()();
        std::shared_ptr<TextureObject>const&getTextureObject();
        void setTextureObject(std::shared_ptr<TextureObject>const&TextureObject);
        GLenum                              getUnit         ();
        void                                setUnit(GLenum unit);
    };

    ge::core::Command*newActiveTexture(ProgramObject*program,std::string samplerName  );
    ge::core::Command*newBindTexture  (TextureObject*texture);
    ge::core::Command*newBindTextureUnit(
        ProgramObject*program    ,
        std::string   samplerName,
        TextureObject*texture    );
  }
}
