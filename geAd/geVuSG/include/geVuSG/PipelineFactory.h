#pragma once

#include <geVu/geVu.h>

#include <geVuSG/geVuSGClasses.h>
#include <geSG/Mesh.h>
#include <geSG/Material.h>


class ge::vusg::PipelineFactory {
protected:
  ge::vu::DeviceContextShared deviceContext;
public:
  PipelineFactory(ge::vu::DeviceContextShared &deviceContext);
  ~PipelineFactory() {}

  ge::vu::Pipeline fromMeshMaterial(
    std::shared_ptr<ge::sg::Mesh> mesh,
    std::shared_ptr<ge::sg::Material> material);
};