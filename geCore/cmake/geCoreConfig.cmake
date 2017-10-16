#include(CMakeFindDependencyMacro)
#find_dependency(DisjointSet 1.0.0)
#find_dependency(ErrorPrinter 1.0.0)
#find_dependency(FSA 1.0.0)
#find_dependency(MealyMachine 1.0.0)
#find_dependency(PrettyFunctionName 1.0.0)
#find_dependency(Text 1.0.0)
#find_dependency(ValuePrinter 1.0.0)


#get_filename_component(SELF_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
#include("${SELF_DIR}/Text/TextConfig.cmake"                            )
#include("${SELF_DIR}/FSA/FSAConfig.cmake"                              )
#include("${SELF_DIR}/MealyMachine/MealyMachineConfig.cmake"            )
#include("${SELF_DIR}/ErrorPrinter/ErrorPrinterConfig.cmake"            )
#include("${SELF_DIR}/PrettyFunctionName/PrettyFunctionNameConfig.cmake")
#include("${SELF_DIR}/ValuePrinter/ValuePrinterConfig.cmake"            )
#include("${SELF_DIR}/DisjointSet/DisjointSetConfig.cmake"              )

include("${CMAKE_CURRENT_LIST_DIR}/geCoreTargets.cmake")

