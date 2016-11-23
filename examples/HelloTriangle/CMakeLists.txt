set(APP_NAME HelloTriangle)

project(${APP_NAME})

find_package(glm REQUIRED)
find_package(SDL2)

if(NOT SDL2_FOUND OR NOT TARGET geRG OR NOT TARGET SDLWindow)
   return()
endif()

set(APP_SOURCES
  main.cpp
  )

set(APP_INCLUDES
  )

add_executable(${APP_NAME} WIN32 ${APP_SOURCES} ${APP_INCLUDES})

set(Internal_deps geRG geGL geUtil SDLWindow)
set(External_libs glm SDL2)
set(Internal_inc
  ${GPUEngine_SOURCE_DIR}/include
  ${GPUEngine_SOURCE_DIR}
  )

target_link_libraries(${APP_NAME} ${Internal_deps} ${External_libs})
set_target_properties(${APP_NAME} PROPERTIES
  INCLUDE_DIRECTORIES "${Internal_inc}"
  )
set_property(TARGET ${APP_NAME} PROPERTY FOLDER "${examples_folder_name}")
