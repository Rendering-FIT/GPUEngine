#pragma once

#include "geVuSG/Export.h"

#include <memory>

#define geVuSG_class(x) class GEVUSG_EXPORT x; typedef std::shared_ptr<x> x##Shared; typedef std::weak_ptr<x> x##Weak;

namespace ge {
	namespace vusg {
    geVuSG_class(PhongTechnique);
    geVuSG_class(SceneManager);
    geVuSG_class(Drawable);
    geVuSG_class(DrawListEntry);
    geVuSG_class(PipelineFactory);
    geVuSG_class(AttribArray);
	};
};

