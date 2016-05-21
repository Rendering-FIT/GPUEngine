set(LIB_NAME geDE)

set(LIB_NAME_UPPER)
string(TOUPPER ${LIB_NAME} LIB_NAME_UPPER)

if(GPUENGINE_DYNAMIC)
   set(GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC "SHARED")
   add_definitions(-D"${LIB_NAME_UPPER}"_LIBRARY)
else()
   set(GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC "STATIC")
   add_definitions(-DGE_LIBRARY_STATIC)
endif()

set(HEADER_PATH ${GPUEngine_SOURCE_DIR}/include/${LIB_NAME})

set(DE_INCLUDES
  ${HEADER_PATH}/Export.h
  ${HEADER_PATH}/TypeRegister.h
  ${HEADER_PATH}/Resource.h
  ${HEADER_PATH}/AtomicResource.h
  ${HEADER_PATH}/CompositeResource.h
  ${HEADER_PATH}/Interpret.h
  ${HEADER_PATH}/Statement.h
  ${HEADER_PATH}/Function.h
  ${HEADER_PATH}/AtomicFunction.h
  ${HEADER_PATH}/RegisterBasicFunction.h
  ${HEADER_PATH}/While.h
  ${HEADER_PATH}/If.h
  ${HEADER_PATH}/Body.h
  ${HEADER_PATH}/BodyFactory.h
  ${HEADER_PATH}/IfFactory.h
  ${HEADER_PATH}/WhileFactory.h
  ${HEADER_PATH}/VariableRegister.h
  ${HEADER_PATH}/ObjectFactory.h
  ${HEADER_PATH}/ResourceFactory.h
  ${HEADER_PATH}/StatementFactory.h
  ${HEADER_PATH}/BodyFactory.h
  ${HEADER_PATH}/CompositeFunction.h
  ${HEADER_PATH}/FunctionFactory.h
  ${HEADER_PATH}/FactoryOfFunctionFactory.h
  ${HEADER_PATH}/CompositeFunctionFactory.h
  ${HEADER_PATH}/FunctionNodeFactory.h
  ${HEADER_PATH}/StdFunctions.h
  ${HEADER_PATH}/StdNumericFunctions.h
  ${HEADER_PATH}/StdRelationalFunctions.h
  ${HEADER_PATH}/StdIntegerFunctions.h
  ${HEADER_PATH}/StdCastFunctions.h
  ${HEADER_PATH}/FunctionRegister.h
  ${HEADER_PATH}/NameRegister.h
  ${HEADER_PATH}/geDE.h
  )

set(DE_SOURCES
  TypeRegister.cpp
  AtomicResource.cpp
  CompositeResource.cpp
  Function.cpp
  AtomicFunction.cpp
  While.cpp
  If.cpp
  WhileFactory.cpp
  VariableRegister.cpp
  ResourceFactory.cpp
  StatementFactory.cpp
  CompositeFunction.cpp
  FunctionFactory.cpp
  CompositeFunctionFactory.cpp
  FunctionNodeFactory.cpp
  StdFunctions.cpp
  StdNumericFunctions.cpp
  StdRelationalFunctions.cpp
  StdIntegerFunctions.cpp
  StdCastFunctions.cpp
  FunctionRegister.cpp
  NameRegister.cpp
  )

add_library(${LIB_NAME}
  ${GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC}
  ${DE_INCLUDES}
  ${DE_SOURCES}
  )


################################################
# Internal_deps - only 'ge' targets goes here (e.g. geCore), it configures this package intra project dependencies and also configures the config file
# External_deps_Export - other than 'ge' packages goes here (e.g. glew), it configures this package extra project dependencies and also configures the config file
# External_libs - external libs or targets to link with
# Internal_inc - additional include directories
# Includes_to_export - includes to be exported from this target to application

set(Internal_deps geCore)
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
  ${DE_INCLUDES}
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
