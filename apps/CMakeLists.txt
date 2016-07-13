SET(APPS_BUILD_EMPTYWINDOW       ON CACHE BOOL "Build EmptyWindow app.")
SET(APPS_BUILD_TRIANGLERENDERING OFF CACHE BOOL "Build TriangleRendering app.")
SET(APPS_BUILD_GEVIEWERASSIMP    OFF CACHE BOOL "Build geViewerAssimp app.")
SET(APPS_BUILD_GEVIEWEROSG       OFF CACHE BOOL "Build geViewerOSD app.")

if(APPS_BUILD_EMPTYWINDOW)
  add_subdirectory(EmptyWindow)
endif()

add_subdirectory(ShaderTest)
add_subdirectory(VertexArray)

if(APPS_BUILD_TRIANGLERENDERING)
  add_subdirectory(TriangleRendering)
endif()

if(APPS_BUILD_GEVIEWERASSIMP)
  add_subdirectory(geViewerAssimp)
endif()

if(APPS_BUILD_GEVIEWEROSG)
  add_subdirectory(geViewerOSG)
endif()
