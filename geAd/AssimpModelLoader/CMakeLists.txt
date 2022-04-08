project(AssimpModelLoader)

include(GNUInstallDirs)

################################################
# PACKAGES

find_package(glm)
find_package(ste)
find_package(GPUEngine COMPONENTS geSG)
find_package(assimp)

foreach(dep glm ste geSG assimp::assimp)
    if(NOT TARGET ${dep})
        return()
    endif()
endforeach()

set(public_headers 
    src/AssimpModelLoader.h
)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} 
    PRIVATE
        ${public_headers}
        src/UnicodeIOStream.h
        src/UnicodeIOSystem.h    
    PRIVATE
        src/AssimpModelLoader.cpp
        src/UnicodeIOStream.cpp
        src/$<IF:${WIN32},UnicodeIOSystem_win32.cpp,UnicodeIOSystem_other.cpp>  
)

################################################
# External_libs - external libs or targets to link with

set(External_libs ste glm assimp::assimp)
if(UNIX)
  set(External_libs ${External_libs} dl)
endif()


target_link_libraries(${PROJECT_NAME} geSG ${External_libs})

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

#set(PROJECT_NAME_UPPER)
string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPER)
target_compile_definitions(${PROJECT_NAME}
   PRIVATE "${PROJECT_NAME_UPPER}_EXPORT=__declspec(dllexport)"
   INTERFACE "${PROJECT_NAME_UPPER}_EXPORT=__declspec(dllimport)"
)
set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER ${addons_folder_name})
#########################################
# Install


install(FILES
   ${public_headers}
   DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/geAd/${PROJECT_NAME}
)

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )


#########################################
#Export

install(EXPORT ${PROJECT_NAME}Targets
   DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/geAd
)

#export(EXPORT ${PROJECT_NAME}Targets) #error https://stackoverflow.com/questions/5378528/install-export-problem-for-shared-lib-with-dependencies

set(Dependencies geSG glm assimp)

configure_file(
   ../geAd.cmake.in
   "${PROJECT_NAME}Config.cmake"
   @ONLY
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/geAd
        )
