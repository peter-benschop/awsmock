cmake_minimum_required(VERSION 3.18)
project(aws-mock)

set(CMAKE_CXX_STANDARD 20)
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()
set(CMAKE_INSTALL_PREFIX "/usr/local" CACHE STRING " " FORCE)

set(doxyfile ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile)
find_package(Doxygen)
option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" ${DOXYGEN_FOUND})

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