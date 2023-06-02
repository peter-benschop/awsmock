cmake_minimum_required(VERSION 3.18)
project(aws-mock)

set(CMAKE_CXX_STANDARD 20)

enable_testing()

add_subdirectory(core)
add_subdirectory(db)
add_subdirectory(dto)
add_subdirectory(service)
add_subdirectory(awsmock)
