function(add_tests)
  foreach(TARG ${TEST_TARGETS})
    project(${TARG})
    add_executable(${TARG} ${TARG}.cpp)
    target_link_libraries(${TARG} geCore geDE geParser)
  endforeach(TARG)
endfunction(add_tests)

set(TEST_TARGETS 
  typeRegisterTest 
  functionRegisterTest 
  fsaTest
  tokenizationTest
  syntaxTest
  interpretTest
  #  namespaceTest
  statementFactoryTest
  mealyMachineTest
  )
add_tests()

