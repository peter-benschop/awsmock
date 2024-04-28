cmake_minimum_required(VERSION 3.25)
project(awsmock)

set(BUILD_SHARED_LIBS OFF)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
SET(CMAKE_BUILD_TYPE Release CACHE PATH "" FORCE)
set(CMAKE_INSTALL_PREFIX "/usr" CACHE PATH " ..." FORCE)

# Doxygen
option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen and dot) " ON)

# Current version
file(READ "src/core/include/awsmock/core/Version.h" ver)
string(REGEX MATCH "#define PROJECT_VERSION \"([0-9\.]+)\"" _ ${ver})
set(PROJECT_VERSION ${CMAKE_MATCH_1})
string(TIMESTAMP PROJECT_BUILDDATE "%d-%m-%Y")

# Build message
message("-- Building ${PROJECT_NAME} v${PROJECT_VERSION} type: ${CMAKE_BUILD_TYPE}, install prefix: ${CMAKE_INSTALL_PREFIX}")

# Testing
enable_testing()

add_subdirectory(src/core)
add_subdirectory(src/dto)
add_subdirectory(src/db)
add_subdirectory(src/service)
add_subdirectory(src/manager)
add_subdirectory(src/controller)
add_subdirectory(docs)

install(FILES dist/etc/awsmock.properties DESTINATION /etc)
install(FILES dist/etc/systemd/system/awsmock.service DESTINATION /etc/systemd/system)
install(FILES dist/bin/awslocal DESTINATION ${CMAKE_INSTALL_PREFIX}/bin PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ WORLD_EXECUTE)
