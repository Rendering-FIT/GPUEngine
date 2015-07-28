#pragma once

#include<memory>
#include<geGL/Export.h>
#include<geCore/Command.h>
#include<GL/glew.h>

namespace ge{
  namespace gl{
    class TextureObject;

    class BindTextureObject2Unit{
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

  }
}
