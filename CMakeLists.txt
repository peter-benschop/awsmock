cmake_minimum_required(VERSION 3.18)
project(aws-mock)

# required modules for our task
set(CMAKE_CXX_STANDARD 20)

# Doxygen
option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" OFF)

# Semantic versioning (sv4git)
execute_process(COMMAND dist/bin/git-sv cv OUTPUT_VARIABLE CMAKE_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE)
configure_file(src/core/include/awsmock/core/Version.h.in src/core/include/awsmock/core/Version.h)

# Set defaults
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()
if (NOT CMAKE_INSTALL_PREFIX)
    set(CMAKE_INSTALL_PREFIX "/usr" CACHE STRING " " FORCE)
endif ()

message("-- Building ${PROJECT_NAME} ${CMAKE_VERSION} type: ${CMAKE_BUILD_TYPE}, install prefix: ${CMAKE_INSTALL_PREFIX}")

# Testing
enable_testing()

add_subdirectory(src/core)
add_subdirectory(src/dto)
add_subdirectory(src/db)
add_subdirectory(src/manager)
add_subdirectory(src/service)
add_subdirectory(src/controller)

if (BUILD_DOCUMENTATION)
    set(doxyfile ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile)
    find_package(Doxygen)
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
install(FILES dist/bin/awslocal DESTINATION ${CMAKE_INSTALL_PREFIX}/bin PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
        GROUP_EXECUTE GROUP_READ WORLD_EXECUTE)
install(FILES docs/man/awsmockctl.1.gz DESTINATION /usr/share/man/man1 PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ
        WORLD_READ)
install(FILES docs/man/awsmockmgr.1.gz DESTINATION /usr/share/man/man1 PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ
        WORLD_READ)
