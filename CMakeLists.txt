cmake_minimum_required(VERSION 3.5)
project(tkom2)

message(STATUS "start running cmake...")

find_package(Boost 1.54.0 COMPONENTS system filesystem REQUIRED)

if(Boost_FOUND)

    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")

    include_directories(${Boost_INCLUDE_DIRS})

endif()

set(CXX_STANDARD 1y)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

set(SOURCE_FILES src/CppScanner.cpp src/CppScanner.h src/Token.cpp src/Token.h src/Parser.cpp src/Parser.h src/pr/Expression.cpp src/pr/Expression.h src/pr/OrExpression.cpp src/pr/OrExpression.h src/pr/AndExpression.cpp src/pr/AndExpression.h src/pr/CompExpression.cpp src/pr/CompExpression.h src/pr/Operator.cpp src/pr/Operator.h src/pr/Value.cpp src/pr/Value.h src/pr/VariableDeclaration.cpp src/pr/VariableDeclaration.h src/pr/Expressions.cpp src/pr/Expressions.h src/pr/IfExpression.cpp src/pr/IfExpression.h src/pr/FunctionCall.cpp src/pr/FunctionCall.h src/pr/FunctionDeclaration.cpp src/pr/FunctionDeclaration.h src/pr/ForExpression.cpp src/pr/ForExpression.h src/pr/BuildOrStaticExpression.cpp src/pr/BuildOrStaticExpression.h src/pr/VariableStack.cpp src/pr/VariableStack.h src/pr/FunctionStack.cpp src/pr/FunctionStack.h src/GraphNode.cpp src/GraphNode.h)
add_executable(tkom2 src/main.cpp ${SOURCE_FILES})
add_executable(tkomtest test/Tests.cpp ${SOURCE_FILES})

if(Boost_FOUND)

    target_link_libraries(tkomtest boost_unit_test_framework)

endif()



#Setup CMake to run tests
enable_testing()

#Prep ourselves for compiling boost
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
include_directories (${Boost_INCLUDE_DIRS})

#I like to keep test files in a separate source directory called test
file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} test/*.cpp)

#Run through each source
foreach(testSrc ${TEST_SRCS})
    #Extract the filename without an extension (NAME_WE)
    get_filename_component(testName ${testSrc} NAME_WE)

    #Add compile target
    add_executable(${testName} ${testSrc})

    #link to Boost libraries AND your targets and dependencies
    target_link_libraries(${testName} ${Boost_LIBRARIES} [YOUR TARGETS/LIBRARIES])

    #I like to move testing binaries into a testBin directory
    set_target_properties(${testName} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/testBin)

    #Finally add it to test execution -
    #Notice the WORKING_DIRECTORY and COMMAND
    add_test(NAME ${testName}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/testBin
            COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/testBin/${testName} )
endforeach(testSrc)


