
set(LIBRARY awsmockcore)
set(LIBRARY_STATIC awsmockcore_static)

set(UTILS_SOURCES src/utils/StringUtils.cpp src/utils/FileUtils.cpp src/utils/DirUtils.cpp src/utils/DateTimeUtils.cpp
        src/utils/CryptoUtils.cpp src/utils/AwsUtils.cpp src/utils/SystemUtils.cpp src/utils/CurlUtils.cpp
        src/utils/TarUtils.cpp src/utils/RandomUtils.cpp src/utils/JsonUtils.cpp src/config/Configuration.cpp
        src/utils/TestUtils.cpp src/utils/HttpUtils.cpp src/utils/NumberUtils.cpp src/utils/MemoryMappedFile.cpp
        src/utils/Task.cpp src/utils/XmlUtils.cpp src/utils/Win32Utils.cpp src/utils/Timer.cpp src/utils/TaskPool.cpp)
set(EXCEPTION_SOURCES src/exception/CoreException.cpp src/exception/DatabaseException.cpp src/exception/ServiceException.cpp
        src/exception/InvalidMethodCallException.cpp src/exception/JsonException.cpp src/exception/NotFoundException.cpp
        src/exception/ForbiddenException.cpp src/exception/UnauthorizedException.cpp src/exception/BadRequestException.cpp)
set(LOGGING_SOURCES src/logging/LogStream.cpp)
set(MONITORING_SOURCES src/monitoring/MetricService.cpp src/monitoring/MetricSystemCollector.cpp)

set(SOURCES ${UTILS_SOURCES} ${EXCEPTION_SOURCES} ${LOGGING_SOURCES} ${MONITORING_SOURCES})

# Test directory
add_subdirectory(tst)

# Includes
include_directories(./include)

add_library(${LIBRARY} SHARED ${SOURCES})
add_library(${LIBRARY_STATIC} STATIC ${SOURCES})
set_target_properties(${LIBRARY_STATIC} PROPERTIES OUTPUT_NAME ${LIBRARY})

install(TARGETS ${LIBRARY} DESTINATION lib)
