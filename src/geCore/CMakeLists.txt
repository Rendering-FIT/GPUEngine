set(LIB_NAME geCore)

set(LIB_NAME_UPPER)
string(TOUPPER ${LIB_NAME} LIB_NAME_UPPER)

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
  ${HEADER_PATH}/Export.h
  ${HEADER_PATH}/Object.h
  ${HEADER_PATH}/geCore.h
  ${HEADER_PATH}/Command.h
  ${HEADER_PATH}/CopyOp.h
  ${HEADER_PATH}/Defines.h
  ${HEADER_PATH}/Dtemplates.h
  ${HEADER_PATH}/TypeTraits.h
  ${HEADER_PATH}/ValuePrinter.h
  ${HEADER_PATH}/ErrorPrinter.h
  ${HEADER_PATH}/CallStackPrinter.h
  ${HEADER_PATH}/EnumRegister.h
  ${HEADER_PATH}/Functor.h
  ${HEADER_PATH}/InitAndFinalize.h
  ${HEADER_PATH}/StandardSemanticsNames.h
  ${HEADER_PATH}/DisjointSet.h
  ${HEADER_PATH}/idlist.h
  ${HEADER_PATH}/Text.h
  ${HEADER_PATH}/Updatable.h
  )

set(CORE_SOURCES
  Object.cpp
  CopyOp.cpp
  Dtemplates.cpp
  Command.cpp
  EnumRegister.cpp
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


################################################
# Internal_deps - only 'ge' targets goes here (e.g. geCore), it configures this package intra project dependencies and also configures the config file
# External_deps_Export - other than 'ge' packages goes here (e.g. glew), it configures this package extra project dependencies and also configures the config file
# External_libs - external libs or targets to link with
# Internal_inc - additional include directories
# Includes_to_export - includes to be exported from this target to application

set(Internal_deps )
set(External_deps_Export )
set(External_libs )
set(Internal_inc ${GPUEngine_SOURCE_DIR}/include)
set(Includes_to_export ${GPUEngine_SOURCE_DIR}/include)

target_link_libraries(${LIB_NAME} ${Internal_deps} ${External_deps} )

set_target_properties(${LIB_NAME} PROPERTIES
  INCLUDE_DIRECTORIES "${Internal_inc}"
  INTERFACE_INCLUDE_DIRECTORIES "${Includes_to_export}"
  )

install(FILES
  ${FSA_INCLUDES}
  DESTINATION include/${LIB_NAME}/fsa
  )

install(FILES
  ${CORE_INCLUDES}
  DESTINATION include/${LIB_NAME}
  )


install(TARGETS ${LIB_NAME}
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  )

#########################################
#Export

configure_file(
  ../CMake/geConfig.cmake.in
  "${LIB_NAME}Config.cmake"
  @ONLY
  )


configure_file(
  ../CMake/geExport.h.in
  "${GPUEngine_SOURCE_DIR}/include/${LIB_NAME}/Export.h"
  @ONLY
  )

# INSTALL_CM_DIR is defined in master CMakeLists file

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}Config.cmake"
  DESTINATION "${INSTALL_CM_DIR}/${LIB_NAME}"
  )
