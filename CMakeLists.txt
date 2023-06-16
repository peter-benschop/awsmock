cmake_minimum_required(VERSION 3.18)

# Version (https://github.com/azatuni/sem-ver-sh)
include_directories(${PROJECT_BINARY_DIR}/core/)
file(READ "VERSION" ver)
string(REGEX MATCH "version=([0-9]*)\\.([0-9]*)\\.([0-9]*)" _ ${ver})
set(CPACK_PACKAGE_VERSION_MAJOR ${CMAKE_MATCH_1})
set(CPACK_PACKAGE_VERSION_MINOR ${CMAKE_MATCH_2})
set(CPACK_PACKAGE_VERSION_PATCH ${CMAKE_MATCH_3})
message("version: ${CMAKE_MATCH_1}.${CMAKE_MATCH_2}.${CMAKE_MATCH_3} type: ${CMAKE_BUILD_TYPE}")

project(aws-mock VERSION "${CMAKE_MATCH_1}.${CMAKE_MATCH_2}.${CMAKE_MATCH_3}")
configure_file (core/include/awsmock/core/Version.h.in core/include/awsmock/core/Version.h)

set(CMAKE_CXX_STANDARD 20)
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()
set(CMAKE_INSTALL_PREFIX "/usr/local" CACHE STRING " " FORCE)

# Doxygen
set(doxyfile ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile)
find_package(Doxygen)
option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" ${DOXYGEN_FOUND})

# Testing
enable_testing()

add_subdirectory(core)
add_subdirectory(db)
add_subdirectory(service)
add_subdirectory(worker)
add_subdirectory(awsmock)

if (BUILD_DOCUMENTATION)
    if (NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif ()
    add_custom_target(
            docs
            COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
endif ()