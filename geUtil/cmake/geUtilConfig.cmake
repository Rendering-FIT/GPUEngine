include(CMakeFindDependencyMacro)
find_dependency(glm)
find_dependency(geCore 1.0.0)

include("${CMAKE_CURRENT_LIST_DIR}/geUtilTargets.cmake")
