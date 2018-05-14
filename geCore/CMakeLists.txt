set(LIB_NAME geCore)

set(LIB_NAME_UPPER)
string(TOUPPER ${LIB_NAME} LIB_NAME_UPPER)

include(GenerateExportHeader)
include(GNUInstallDirs)

set(HEADER_PATH ${CMAKE_CURRENT_LIST_DIR}/src/geCore)
set(SRC_PATH ${CMAKE_CURRENT_LIST_DIR}/src/geCore)

set(FSA_SOURCES
  ${SRC_PATH}/fsa/Fsa.cpp
  ${SRC_PATH}/fsa/State.cpp
  ${SRC_PATH}/fsa/Transition.cpp
  ${SRC_PATH}/fsa/FusedCallbackData.cpp
  ${SRC_PATH}/fsa/MealyMachine.cpp
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
  ${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}/Export.h
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
  ${SRC_PATH}/Object.cpp
  ${SRC_PATH}/CopyOp.cpp
  ${SRC_PATH}/Dtemplates.cpp
  ${SRC_PATH}/Command.cpp
  ${SRC_PATH}/EnumRegister.cpp
  ${SRC_PATH}/InitAndFinalize.cpp
  ${SRC_PATH}/StandardSemanticsNames.cpp
  ${SRC_PATH}/Text.cpp
  )

  
#########################################
# Target

add_library(${LIB_NAME}
  ${CORE_INCLUDES}
  ${FSA_INCLUDES}
  ${CORE_SOURCES}
  ${FSA_SOURCES}
  )

  
GENERATE_EXPORT_HEADER(${LIB_NAME}
   EXPORT_FILE_NAME "${LIB_NAME}/Export.h"
)

target_link_libraries(${LIB_NAME} ${Internal_deps} ${External_deps} )

target_include_directories(${LIB_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src>
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/${LIB_NAME}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

#########################################
# Install

install(FILES
  ${FSA_INCLUDES}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${LIB_NAME}/fsa
  )

install(FILES
  ${CORE_INCLUDES}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${LIB_NAME}
  )
  
install(TARGETS ${LIB_NAME} EXPORT ${LIB_NAME}Targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )

#########################################
# Export

install(EXPORT ${LIB_NAME}Targets
   FILE ${LIB_NAME}Config.cmake
   DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${LIB_NAME}
)