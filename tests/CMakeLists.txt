function(add_tests apps libs)
  foreach(TARG ${apps})
    project(${TARG})
    add_executable(${TARG} ${TARG}.cpp)
    target_link_libraries(${TARG} ${libs})
    set_target_properties(${TARG} PROPERTIES FOLDER "Tests")
  endforeach(TARG)
endfunction(add_tests)

add_tests("fsaTest;mealyMachineTest;idlistTest" "geCore")

if(GPUENGINE_BUILD_GESG)
add_tests("animationTest" "geSG")
endif()