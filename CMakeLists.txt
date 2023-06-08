cmake_minimum_required(VERSION 3.18)
project(aws-mock)

set(CMAKE_CXX_STANDARD 20)
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()
set(CMAKE_INSTALL_PREFIX "/usr/local" CACHE STRING " " FORCE)

enable_testing()

add_subdirectory(core)
add_subdirectory(db)
#add_subdirectory(dto)
add_subdirectory(service)
add_subdirectory(worker)
add_subdirectory(awsmock)
