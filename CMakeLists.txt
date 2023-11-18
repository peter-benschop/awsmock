cmake_minimum_required(VERSION 3.18)
project(aws-mock)

# required modules for our task
set(CMAKE_CXX_STANDARD 20)

# Semantic versioning (sv4git)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/dist/etc/")
set(VERSION_UPDATE_FROM_GIT TRUE)
include(GetVersionFromGitTag)
configure_file (src/core/include/awsmock/core/Version.h.in src/core/include/awsmock/core/Version.h)

# Set root install directory
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()
set(CMAKE_INSTALL_PREFIX "/usr" CACHE STRING " " FORCE)
message("-- Building ${PROJECT_NAME} ${${PROJECT_NAME}_VERSION_STRING} type: ${CMAKE_BUILD_TYPE}, install prefix: ${CMAKE_INSTALL_PREFIX}")

# Doxygen
set(doxyfile ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile)
find_package(Doxygen)
option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" ${DOXYGEN_FOUND})

# Testing
enable_testing()

add_subdirectory(src/core)
add_subdirectory(src/dto)
add_subdirectory(src/db)
add_subdirectory(src/manager)
add_subdirectory(src/service)
add_subdirectory(src/controller)

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

# Installation
install(FILES dist/etc/aws-mock.properties DESTINATION /etc)
install(FILES dist/etc/systemd/system/aws-mock.service DESTINATION /etc/systemd/system)
install(FILES dist/bin/awslocal DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
install(FILES docs/man/awsmockctl.1.gz DESTINATION /usr/share/man/man1)

#include(GNUInstallDirs)
#file(ARCHIVE_CREATE OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/docs/man/awsmockctl.1.gz PATHS ${CMAKE_CURRENT_SOURCE_DIR}/docs/man/awsmockctl.1 FORMAT raw COMPRESSION GZip)
#install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/docs/man/awsmockctl.1.gz DESTINATION "${CMAKE_INSTALL_MANDIR}")

# Install gzipped man pages
#add_custom_target(man ALL DEPENDS docs/man/awsmockctl.1)

# compress man page
#add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/docs/man/awsmockctl.1.gz
#        COMMAND gzip -9 --no-name --to-stdout ${CMAKE_CURRENT_SOURCE_DIR}/docs/man/awsmockctl.1 > ${CMAKE_CURRENT_SOURCE_DIR}/docs/man/awsmockctl.1.gz
#        MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/docs/man/awsmockctl.1 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# install compressed man page
#install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/docs/man/awsmockctl.1.gz DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)
