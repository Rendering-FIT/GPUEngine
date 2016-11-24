#pragma once

#include "gui.h"
#include <geRG/RenderingContext.h>
#include <chrono>

class ProfilingContext : public ge::rg::RenderingContext {
public:
  ProfilingContext(int history=300);
	~ProfilingContext();

  virtual void frame();

  void draw();

private:
  void frameStart();
  void frameEnd();
  void timestamp();
  int history;
  static const int timestamps = 6;
  float *data;
  std::vector<std::chrono::high_resolution_clock::time_point> times;
};