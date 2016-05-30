function(add_tests)
  foreach(TARG ${TEST_TARGETS})
    project(${TARG})
    add_executable(${TARG} ${TARG}.cpp)
    target_link_libraries(${TARG} geCore)
  endforeach(TARG)
endfunction(add_tests)

set(TEST_TARGETS
  typeRegisterTest
  functionRegisterTest
  fsaTest
  tokenizationTest
  syntaxTest
  interpretTest
  namespaceTest
  statementFactoryTest
  mealyMachineTest
  idlistTest
  )
add_tests()


set(TARG geRG_test)
project(${TARG})
add_executable(${TARG} ${TARG}.cpp)
target_link_libraries(${TARG} geCore)

set(Internal_deps geRG WindowObject)
set(Internal_inc
  ${GPUEngine_SOURCE_DIR}/include
  ${GPUEngine_SOURCE_DIR}
  )

target_link_libraries(${TARG} ${Internal_deps} ${External_libs})
set_target_properties(${TARG} PROPERTIES
  INCLUDE_DIRECTORIES "${Internal_inc}"
  )


#set(TYPEREGISTERTEST_NAME typeRegisterTest)
#project(${TYPEREGISTERTEST_NAME})
#set(TYPEREGISTERTEST_SOURCES typeRegisterTest.cpp)
#add_executable(${TYPEREGISTERTEST_NAME} ${TYPEREGISTERTEST_SOURCES})
#target_link_libraries(${TYPEREGISTERTEST_NAME} geCore)
#
#set(FUNCTIONREGISTERTEST_NAME functionRegisterTest)
#project(${FUNCTIONREGISTERTEST_NAME})
#set(FUNCTIONREGISTERTEST_SOURCES functionRegisterTest.cpp)
#add_executable(${FUNCTIONREGISTERTEST_NAME} ${FUNCTIONREGISTERTEST_SOURCES})
#target_link_libraries(${FUNCTIONREGISTERTEST_NAME} geCore)
#
#
#set(FSA_NAME fsaTest)
#project(${FSA_NAME})
#set(FSA_SOURCES fsaTest.cpp)
#add_executable(${FSA_NAME} ${FSA_SOURCES})
#target_link_libraries(${FSA_NAME} geCore)
#
#set(TOKENIZATION_NAME tokenizationTest)
#project(${TOKENIZATION_NAME})
#set(TOKENIZATION_SOURCES tokenizationTest.cpp)
#add_executable(${TOKENIZATION_NAME} ${TOKENIZATION_SOURCES})
#target_link_libraries(${TOKENIZATION_NAME} geCore)
#
#set(SYNTAX_NAME syntaxTest)
#project(${SYNTAX_NAME})
#set(SYNTAX_SOURCES syntaxTest.cpp)
#add_executable(${SYNTAX_NAME} ${SYNTAX_SOURCES})
#target_link_libraries(${SYNTAX_NAME} geCore)
#
#set(INTERPRET_NAME interpretTest)
#project(${INTERPRET_NAME})
#set(INTERPRET_SOURCES interpretTest.cpp)
#add_executable(${INTERPRET_NAME} ${INTERPRET_SOURCES})
#target_link_libraries(${INTERPRET_NAME} geCore)
#
#set(NAMESPACE_NAME namespaceTest)
#project(${NAMESPACE_NAME})
#set(NAMESPACE_SOURCES namespaceTest.cpp)
#add_executable(${NAMESPACE_NAME} ${NAMESPACE_SOURCES})
#target_link_libraries(${NAMESPACE_NAME} geCore)
#
#set(STATEMENTFACTORY_NAME statementFactoryTest)
#project(${STATEMENTFACTORY_NAME})
#set(STATEMENTFACTORY_SOURCES statementFactoryTest.cpp)
#add_executable(${STATEMENTFACTORY_NAME} ${STATEMENTFACTORY_SOURCES})
#target_link_libraries(${STATEMENTFACTORY_NAME} geCore)
