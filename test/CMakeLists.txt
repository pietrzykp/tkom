cmake_minimum_required(VERSION 2.8.7)
project(my_first_test)
enable_testing()

# indicates the location of the boost installation tree.
# hard-coded for our simple example.
set(BOOST_INCLUDE_DIRS $boost_installation_prefix/include)

# creates the executable
add_executable(test_executable test_file.cpp)
# indicates the include paths
target_include_directories(test_executable PRIVATE ${BOOST_INCLUDE_DIRS})

# declares a test with our executable
add_test(NAME test1 COMMAND test_executable)
