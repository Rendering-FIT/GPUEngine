SET(APPS_BUILD_EMPTYWINDOW       ON CACHE BOOL "Build EmptyWindow app.")
SET(APPS_BUILD_TRIANGLERENDERING ON CACHE BOOL "Build TriangleRendering app.")
SET(APPS_BUILD_GEVIEWERASSIMP    ON CACHE BOOL "Build geViewerAssimp app.")
SET(APPS_BUILD_GEVIEWEROSG       ON CACHE BOOL "Build geViewerOSD app.")

if(APPS_BUILD_EMPTYWINDOW)
  add_subdirectory(EmptyWindow)
endif()


if(APPS_BUILD_TRIANGLERENDERING)
  add_subdirectory(TriangleRendering)
endif()

if(APPS_BUILD_GEVIEWERASSIMP)
  add_subdirectory(geViewerAssimp)
endif()

if(APPS_BUILD_GEVIEWEROSG)
  add_subdirectory(geViewerOSG)
endif()
