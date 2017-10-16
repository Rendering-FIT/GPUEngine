include(CMakeFindDependencyMacro)
find_dependency(ErrorPrinter 1.0.0)
find_dependency(MealyMachine 1.0.0)
find_dependency(FSA 1.0.0)

include("${CMAKE_CURRENT_LIST_DIR}/TextTargets.cmake")
