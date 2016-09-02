SET(APPS_BUILD_GEVIEWERASSIMP    OFF CACHE BOOL "Build geViewerAssimp app.")

add_subdirectory(ShaderTest)
add_subdirectory(VertexArray)
add_subdirectory(geViewerOSG)

if(APPS_BUILD_GEVIEWERASSIMP)
  add_subdirectory(geViewerAssimp)
endif()
