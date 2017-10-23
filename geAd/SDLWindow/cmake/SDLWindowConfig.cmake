include(CMakeFindDependencyMacro)
find_dependency(SDL2)
find_dependency(geCore)
include("${CMAKE_CURRENT_LIST_DIR}/SDLWindowTargets.cmake")
