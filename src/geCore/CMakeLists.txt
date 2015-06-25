IF   (DYNAMIC_GPUENGINE)
    SET(GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC "SHARED")
    ADD_DEFINITIONS(-DGECORE_LIBRARY)
ELSE ()
    SET(GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC "STATIC")
    ADD_DEFINITIONS(-DGE_LIBRARY_STATIC)
ENDIF()

set(LIB_NAME geCore)

set(HEADER_PATH ${GPUEngine_SOURCE_DIR}/include/${LIB_NAME})
set(CORE_INCLUDES
    ${HEADER_PATH}/geCore.h
    ${HEADER_PATH}/Command.h
    ${HEADER_PATH}/CopyOp.h
    ${HEADER_PATH}/dtemplates.h
    ${HEADER_PATH}/Export.h
    ${HEADER_PATH}/Functor.h
    ${HEADER_PATH}/InitAndFinalize.h
    ${HEADER_PATH}/Object.h
  )

set(CORE_SOURCES
    Object.cpp
    CopyOp.cpp
    dtemplates.cpp
    Command.cpp
  )

ADD_LIBRARY(${LIB_NAME}
    ${GPUENGINE_USER_DEFINED_DYNAMIC_OR_STATIC}
    ${CORE_INCLUDES}
    ${CORE_SOURCES}
  )

set_target_properties(${LIB_NAME} PROPERTIES
	INTERFACE_INCLUDE_DIRECTORIES "${GPUEngine_SOURCE_DIR}/include"
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
   geCoreConfig.cmake.in
   geCoreConfig.cmake
   @ONLY
)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/geCoreConfig.cmake"
   DESTINATION "${INSTALL_CM_DIR}/geCore"
   )
