#include "ProfilingContext.h"

#include <iostream>

using namespace ge::rg;
using namespace std;

ProfilingContext::ProfilingContext(int history){
  this->history = history;
  data = new float[history*(timestamps-1)];
  fill(data, data + history*(timestamps - 1), 0.0f);
}

ProfilingContext::~ProfilingContext(){
}

void ProfilingContext::frame(){
  frameStart();
  timestamp();
  // update progressStamp (monotonically increasing number wrapping on overflow)
  incrementProgressStamp();
  timestamp();
  // clear screen
  gl.glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // compute transformation matrices
  evaluateTransformationGraph();

  timestamp();

  // prepare internal structures for rendering
  stateSetStorage()->map(BufferStorageAccess::WRITE);
  setupRendering();
  stateSetStorage()->unmap();

  timestamp();

  // fill indirect buffer with draw commands
  processDrawCommands();
  fenceSyncGpuComputation();

  timestamp();
  
  // render scene
  render();

  timestamp();
  frameEnd();

  // check for OpenGL errors
  unsigned e = gl.glGetError();
  if (e != GL_NO_ERROR)
    cout << "OpenGL error " << e << " detected after the frame rendering" << endl;
}

void ProfilingContext::draw(){
  ImGui::Begin("geRG profiling");

  const string str[] = {
    "incrementProgressStamp()",
    "evaluateTransformationGraph()",
    "setupRendering()",
    "processDrawCommands()",
    "render()"
  };

  for (int i = 0; i < timestamps - 1; i++) {
    float top = data[i*history];
    for (int h = 0; h < history; h++) {
      top = (std::max)(top, data[i*history + h]);
    }

    top = ceilf(top / 20.0f) * 20.0f;

    ImGui::TextUnformatted(str[i].c_str());
    ImGui::SameLine(220); ImGui::TextUnformatted((to_string(data[i*history])+" ms").c_str());
    ImGui::SameLine(340); ImGui::PlotLines("", &data[i*history], history, 0, 0, 0, top, ImVec2(300, 40));
  }



  ImGui::End();
}

void ProfilingContext::frameStart(){
  times.clear();
}

void ProfilingContext::frameEnd(){
  // shift data
  for (int h = history - 1; h > 0; h--) {
    for (int t = 0; t < timestamps-1; ++t) {
      data[t*history + h] = data[t*history + h-1];
    }
  }
  // write new values
  for (int i = 0; i < timestamps - 1; i++) {
    data[i*history] = 1e-6f*float(std::chrono::duration_cast<std::chrono::nanoseconds>(times[i + 1] - times[i]).count());
  }
}

void ProfilingContext::timestamp(){
  gl.glFinish();
  times.push_back(std::chrono::high_resolution_clock::now());
}
