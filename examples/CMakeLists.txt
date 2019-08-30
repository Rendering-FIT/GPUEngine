set(examples_folder_name "examples")

set(examplesList  Simple_QtgeGL
                  Simple_QtgeSG
                  Simple_Animation
)

foreach(example IN LISTS examplesList)
   add_subdirectory(${example})
endforeach()

message(STATUS "Examples configured:")

foreach(example IN LISTS examplesList)
   if(TARGET ${example})
      message(STATUS "   ${example}")
   endif()
endforeach()
