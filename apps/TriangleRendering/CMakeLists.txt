if(NOT SDL2_FOUND OR NOT ANTTWEAKBAR_FOUND)
   return()
endif()


set(APP_NAME TriangleRendering)

project(${APP_NAME})

set(APP_SOURCES
  main.cpp
  )

set(APP_INCLUDES
  )

add_executable(${APP_NAME} ${APP_SOURCES} ${APP_INCLUDES})

include_directories(
  ${GLEW_INCLUDE_PATH} 
  ${OPENGL_INCLUDE_PATH} 
  ${SDL2_INCLUDE_PATH} 
  ${ANTTWEAKBAR_INCLUDE_PATH}
  )

target_link_libraries(${APP_NAME} 
  geSG
  geGL
  geUtil
  ${GLEW_LIBRARY} 
  ${OPENGL_LIBRARY}
  ${SDL2_LIBRARY}
  ${ANTTWEAKBAR_LIBRARY}
  ${X11_LIBRARIES}
  )
