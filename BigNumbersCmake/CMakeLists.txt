cmake_minimum_required(VERSION 3.6)

project(BigNumbers)

set (SOURCE_EXE main.cpp)
set(SOURCE_LIB BigNumbers.cpp)
add_library(BigNumbers STATIC ${SOURCE_LIB})
add_executable(Numbers ${SOURCE_EXE})

target_link_libraries(Numbers BigNumbers)
