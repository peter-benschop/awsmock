cmake_minimum_required(VERSION 3.18)
project(aws-mock)

set(CMAKE_CXX_STANDARD 20)

#add_executable(aws_mock main.cpp)

add_subdirectory(core)
add_subdirectory(db)
add_subdirectory(awsmock)
#add_subdirectory(tst)
