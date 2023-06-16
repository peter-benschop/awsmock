cmake_minimum_required(VERSION 3.18)
project(aws-mock VERSION "0.0.0")

set(CMAKE_CXX_STANDARD 20)
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()
set(CMAKE_INSTALL_PREFIX "/usr/local" CACHE STRING " " FORCE)

# Doxygen
set(doxyfile ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile)
find_package(Doxygen)
option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" ${DOXYGEN_FOUND})

# Version
file(READ "VERSION" ver)
string(REGEX MATCH "version=([0-9]*)\\.([0-9]*)\\.([0-9]*)" _ ${ver})
set(ver_major ${CMAKE_MATCH_1})
set(ver_minor ${CMAKE_MATCH_2})
set(ver_patch ${CMAKE_MATCH_3})
message("version: ${ver_major}.${ver_minor}.${ver_patch}")

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