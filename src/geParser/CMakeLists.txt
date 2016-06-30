set(LIB_NAME geParser)

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

set(PARSER_INCLUDES
  ${HEADER_PATH}/Export.h
  ${HEADER_PATH}/Token.h
  ${HEADER_PATH}/NodeContext.h
  ${HEADER_PATH}/Grammar.h
  ${HEADER_PATH}/Nonterm.h
  ${HEADER_PATH}/NontermNode.h
  ${HEADER_PATH}/Symbol.h
  ${HEADER_PATH}/Syntax.h
  ${HEADER_PATH}/SyntaxNode.h
  ${HEADER_PATH}/SyntaxTree.h
  ${HEADER_PATH}/SyntaxTreeProcessor.h
  ${HEADER_PATH}/Term.h
  ${HEADER_PATH}/TermNode.h
  ${HEADER_PATH}/Tokenization.h
  )

set(PARSER_SOURCES
  Grammar.cpp
  Nonterm.cpp
  NontermNode.cpp
  Syntax.cpp
  SyntaxTreeProcessor.cpp
  TermNode.cpp
  Tokenization.cpp
  )

add_library(${LIB_NAME}
  ${GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC}
  ${PARSER_INCLUDES}
  ${PARSER_SOURCES}
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
  ${PARSER_INCLUDES}
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
