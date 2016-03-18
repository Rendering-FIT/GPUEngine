set(LIB_NAME geCore)

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

set(FSA_SOURCES
    fsa/fsa.cpp
    fsa/state.cpp
    fsa/transition.cpp
    fsa/fusedCallbackData.cpp
   )

set(FSA_INCLUDES
    ${HEADER_PATH}/fsa/fsa.h
    ${HEADER_PATH}/fsa/state.h
    ${HEADER_PATH}/fsa/transition.h
    ${HEADER_PATH}/fsa/fusedCallbackData.h
   )

set(CORE_INCLUDES
    ${HEADER_PATH}/Export.h
    ${HEADER_PATH}/geCore.h
    ${HEADER_PATH}/Command.h
    ${HEADER_PATH}/CopyOp.h
    ${HEADER_PATH}/dtemplates.h
    ${HEADER_PATH}/EnumRegister.h
    ${HEADER_PATH}/Functor.h
    ${HEADER_PATH}/InitAndFinalize.h
    ${HEADER_PATH}/Object.h
    ${HEADER_PATH}/StandardSemanticsNames.h
    ${HEADER_PATH}/TypeRegister.h
    ${HEADER_PATH}/disjointSet.h
    ${HEADER_PATH}/interpret.h
    ${HEADER_PATH}/statement.h
    ${HEADER_PATH}/function.h
    ${HEADER_PATH}/while.h
    ${HEADER_PATH}/if.h
    ${HEADER_PATH}/body.h
    ${HEADER_PATH}/Namespace.h
    ${HEADER_PATH}/macroFunction.h
    ${HEADER_PATH}/stdFunctions.h
    ${HEADER_PATH}/token.h
    #    ${HEADER_PATH}/lexer.h
    ${HEADER_PATH}/idof.h
    ${HEADER_PATH}/NodeContext.h
    ${HEADER_PATH}/grammar.h
    ${HEADER_PATH}/nonterm.h
    ${HEADER_PATH}/nontermNode.h
    ${HEADER_PATH}/symbol.h
    ${HEADER_PATH}/syntax.h
    ${HEADER_PATH}/syntaxNode.h
    ${HEADER_PATH}/syntaxTree.h
    ${HEADER_PATH}/term.h
    ${HEADER_PATH}/termNode.h
    ${HEADER_PATH}/tokenization.h
    ${HEADER_PATH}/text.h
   )

set(CORE_SOURCES
    Object.cpp
    CopyOp.cpp
    dtemplates.cpp
    Command.cpp
    EnumRegister.cpp
    StandardSemanticsNames.cpp
    TypeRegister.cpp
    statement.cpp
    function.cpp
    while.cpp
    if.cpp
    body.cpp
    Namespace.cpp
    macroFunction.cpp
    stdFunctions.cpp
    token.cpp
    #    lexer.cpp
    grammar.cpp
    nonterm.cpp
    nontermNode.cpp
    syntax.cpp
    termNode.cpp
    tokenization.cpp
    text.cpp
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
