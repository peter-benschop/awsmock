
set(LIBRARY awsmockcore)
set(LIBRARY_STATIC awsmockcore_static)

set(UTILS_SOURCES src/utils/StringUtils.cpp src/utils/FileUtils.cpp src/utils/DirUtils.cpp src/utils/DateTimeUtils.cpp
        src/utils/CryptoUtils.cpp src/utils/DirectoryWatcher.cpp src/logging/LibriJsonFormatter.cpp)
set(UTILS_HEADERS include/awsmock/core/StringUtils.h include/awsmock/core/FileUtils.h include/awsmock/core/DirUtils.h
        include/awsmock/core/DateTimeUtils.h include/awsmock/core/CryptoUtils.h include/awsmock/core/JsonLogFormatter.h
        include/awsmock/core/DirectoryWatcher.h)

set(EXCEPTION_SOURCES src/exception/CoreException.cpp src/exception/DatabaseException.cpp
        src/exception/ServiceException.cpp src/exception/ResourceNotFoundException.cpp)
set(EXCEPTION_HEADERS include/awsmock/core/CoreException.h include/awsmock/core/DatabaseException.h
        include/awsmock/core/ServiceException.h include/awsmock/core/ResourceNotFoundException.h)

set(SOURCES src/config/Configuration.cpp src/logging/Logger.cpp src/monitoring/MetricService.cpp
        src/monitoring/MetricSystemCollector.cpp ${UTILS_SOURCES} ${EXCEPTION_SOURCES})
set(HEADERS include/awsmock/core/Configuration.h include/awsmock/core/Logger.h include/awsmock/core/MetricService.h
        include/awsmock/core/MetricSystemCollector.h include/awsmock/core/MetricServiceTimer.h
        include/awsmock/core/MetricDefinition.h ${UTILS_HEADERS} ${EXCEPTION_HEADERS} )

# Test directory
add_subdirectory(tst)

# Includes
include_directories(/usr/include /usr/local/include include)

add_library(${LIBRARY} SHARED ${SOURCES})
add_library(${LIBRARY_STATIC} STATIC ${SOURCES})
set_target_properties(${LIBRARY_STATIC} PROPERTIES OUTPUT_NAME ${LIBRARY})

install(TARGETS ${LIBRARY} ${LIBRARY_STATIC} DESTINATION lib)
