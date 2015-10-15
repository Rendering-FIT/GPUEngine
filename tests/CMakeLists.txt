set(APP_NAME typeRegisterTest)

project(${APP_NAME})

set(APP_SOURCES
  typeRegisterTest.cpp
  )

set(APP_INCLUDES
  )

add_executable(${APP_NAME} ${APP_SOURCES} ${APP_INCLUDES})

include_directories(
  )

target_link_libraries(${APP_NAME}
  geCore
  )
