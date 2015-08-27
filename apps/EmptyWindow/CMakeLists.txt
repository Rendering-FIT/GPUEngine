if(NOT SDL2_FOUND OR NOT ANTTWEAKBAR_FOUND)
   return()
endif()


set(APP_NAME EmptyWindow)

project(${APP_NAME})

set(APP_SOURCES
  main.cpp
  )

set(APP_INCLUDES
  )

add_executable(${APP_NAME} ${APP_SOURCES} ${APP_INCLUDES})

include_directories(
  ${GLEW_INCLUDE_DIR} 
  ${OPENGL_INCLUDE_DIR}
  ${SDL2_INCLUDE_DIR}
  ${ANTTWEAKBAR_INCLUDE_DIR}
  )

target_link_libraries(${APP_NAME} 
  geGL
  geUtil
  ${GLEW_LIBRARY} 
  ${OPENGL_LIBRARY}
  ${SDL2_LIBRARY}
  ${ANTTWEAKBAR_LIBRARY}
  ${X11_LIBRARIES}
  )
