set(LIB_NAME geCore)

set(Upstream_VERSION 1.0.0)

set(LIB_NAME_UPPER)
string(TOUPPER ${LIB_NAME} LIB_NAME_UPPER)

set(LIB_NAME_LOWER)
string(TOLOWER ${LIB_NAME} LIB_NAME_LOWER)


if(GPUENGINE_DYNAMIC_LINKAGE)
   set(GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC "SHARED")
   add_definitions(-D"${LIB_NAME_UPPER}"_LIBRARY)
else()
   set(GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC "STATIC")
   add_definitions(-DGE_LIBRARY_STATIC)
endif()

set(HEADER_PATH ${GPUEngine_SOURCE_DIR}/include/${LIB_NAME})

set(FSA_SOURCES
  fsa/Fsa.cpp
  fsa/State.cpp
  fsa/Transition.cpp
  fsa/FusedCallbackData.cpp
  fsa/MealyMachine.cpp
  )

set(FSA_INCLUDES
  ${HEADER_PATH}/fsa/Fsa.h
  ${HEADER_PATH}/fsa/State.h
  ${HEADER_PATH}/fsa/Transition.h
  ${HEADER_PATH}/fsa/FusedCallbackData.h
  ${HEADER_PATH}/fsa/MealyMachine.h
  ${HEADER_PATH}/fsa/TransitionChooser.h
  ${HEADER_PATH}/fsa/MapTransitionChooser.h
  )

set(CORE_INCLUDES
  ${HEADER_PATH}/geCore.h
  ${HEADER_PATH}/CallStackPrinter.h
  ${HEADER_PATH}/Command.h
  ${HEADER_PATH}/CopyOp.h
  ${HEADER_PATH}/Defines.h
  ${HEADER_PATH}/DisjointSet.h
  ${HEADER_PATH}/Dtemplates.h
  ${HEADER_PATH}/EnumRegister.h
  ${HEADER_PATH}/ErrorPrinter.h
  ${HEADER_PATH}/Functor.h
  ${HEADER_PATH}/idlist.h
  ${HEADER_PATH}/InitAndFinalize.h
  ${HEADER_PATH}/Interval.h
  ${HEADER_PATH}/KeyPoint.h
  ${HEADER_PATH}/Object.h
  ${HEADER_PATH}/StandardSemanticsNames.h
  ${HEADER_PATH}/Text.h
  ${HEADER_PATH}/TypeTraits.h
  ${HEADER_PATH}/Updatable.h
  ${HEADER_PATH}/ValuePrinter.h
  )

set(CORE_SOURCES
  Object.cpp
  CopyOp.cpp
  Dtemplates.cpp
  Command.cpp
  EnumRegister.cpp
  InitAndFinalize.cpp
  StandardSemanticsNames.cpp
  Text.cpp
  )

add_library(${LIB_NAME}
  ${GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC}
  ${CORE_INCLUDES}
  ${FSA_INCLUDES}
  ${CORE_SOURCES}
  ${FSA_SOURCES}
  )
add_library(${LIB_NAME}::${LIB_NAME} ALIAS ${LIB_NAME})

include(GenerateExportHeader)

generate_export_header(${LIB_NAME})
set_property(TARGET ${LIB_NAME} APPEND PROPERTY
  COMPATIBLE_INTERFACE_STRING ${LIB_NAME}_MAJOR_VERSION
  )

target_include_directories(${LIB_NAME} PUBLIC  
  $<BUILD_INTERFACE:${GPUEngine_BINARY_DIR}/include/>  
  $<BUILD_INTERFACE:${GPUEngine_BINARY_DIR}/src/>  
  $<BUILD_INTERFACE:${GPUEngine_SOURCE_DIR}/include/>  
  $<INSTALL_INTERFACE:include/> 
)

install(TARGETS ${LIB_NAME} EXPORT ${LIB_NAME}Targets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
  )
install(FILES
  ${FSA_INCLUDES}
  DESTINATION include/${LIB_NAME}/fsa
  )
install(FILES
  ${CORE_INCLUDES}
  DESTINATION include/${LIB_NAME}
  )
install(
  FILES
  "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME_LOWER}_export.h"
  DESTINATION
  include/${LIB_NAME}
  COMPONENT
  Devel
  )

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}/${LIB_NAME}ConfigVersion.cmake"
  VERSION ${Upstream_VERSION}
  COMPATIBILITY AnyNewerVersion
  )

export(EXPORT ${LIB_NAME}Targets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}/${LIB_NAME}Targets.cmake"
  NAMESPACE ${LIB_NAME}::
  )
configure_file(cmake/${LIB_NAME}Config.cmake
  "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}/${LIB_NAME}Config.cmake"
  COPYONLY
  )

set(ConfigPackageLocation lib/cmake/${LIB_NAME})
install(EXPORT ${LIB_NAME}Targets
  FILE
  ${LIB_NAME}Targets.cmake
  NAMESPACE
  ${LIB_NAME}::
  DESTINATION
  ${ConfigPackageLocation}
  )
install(
  FILES
  cmake/${LIB_NAME}Config.cmake
  "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}/${LIB_NAME}ConfigVersion.cmake"
  DESTINATION
  ${ConfigPackageLocation}
  COMPONENT
  Devel
  )

