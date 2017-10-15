include(CMakeFindDependencyMacro)
find_dependency(PrettyFunctionName 1.0.0)
find_dependency(ValuePrinter 1.0.0)

include("${CMAKE_CURRENT_LIST_DIR}/ErrorPrinterTargets.cmake")
