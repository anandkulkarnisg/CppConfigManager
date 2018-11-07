cmake_minimum_required(VERSION 2.8.4)
project(CppConfigManager)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g -Wall")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -lxerces-c")

# Generate shared library libCppConfigManager.so file.
ADD_LIBRARY(CppConfigManager SHARED CppXMLConfigReader.cpp XMLConfig.cpp)

# Add test Examples below.

add_executable(XMLConfigExample.out XMLConfigExample.cpp)
add_executable(ConfigReaderExample.out ConfigReaderExample.cpp)
add_executable(OtherStuff.out OtherStuff.cpp)
add_executable(SampleTest.out SampleTest.cpp)

target_link_libraries(XMLConfigExample.out CppConfigManager xerces-c)
target_link_libraries(ConfigReaderExample.out CppConfigManager xerces-c)
target_link_libraries(OtherStuff.out CppConfigManager xerces-c)
target_link_libraries(SampleTest.out CppConfigManager xerces-c)
