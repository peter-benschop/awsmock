
set(LIBRARY awsmockcore)
set(LIBRARY_STATIC awsmockcore_static)

set(DTO_SOURCES src/dto/CreateBucketRequest.cpp src/dto/CreateBucketResponse.cpp)
set(DTO_HEADERS src/dto/CreateBucketRequest.cpp src/dto/CreateBucketResponse.cpp)

set(SOURCES src/utils/StringUtils.cpp src/utils/FileUtils.cpp src/utils/DirUtils.cpp src/exception/CoreException.cpp
        src/exception/ServiceException.cpp src/exception/ResourceNotFoundException.cpp src/config/Configuration.cpp
        src/logging/Logger.cpp src/monitoring/MetricService.cpp src/monitoring/MetricSystemCollector.cpp ${DTO_SOURCES})
set(HEADERS include/awsmock/core/StringUtils.h include/awsmock/core/FileUtils.h include/awsmock/core/DirUtils.h
        include/awsmock/core/CoreException.h include/awsmock/core/ServiceException.h
        include/awsmock/core/ResourceNotFoundException.h include/awsmock/core/Configuration.h include/awsmock/core/Logger.h
        include/awsmock/core/MetricService.h include/awsmock/core/MetricSystemCollector.h include/awsmock/core/MetricServiceTimer.h
        include/awsmock/core/MetricDefinition.h ${DTO_HEADERS})

# Includes
include_directories(/usr/include /usr/local/include include)

add_library(${LIBRARY} SHARED ${SOURCES})
add_library(${LIBRARY_STATIC} STATIC ${SOURCES})
set_target_properties(${LIBRARY_STATIC} PROPERTIES OUTPUT_NAME ${LIBRARY})

install(TARGETS ${LIBRARY} ${LIBRARY_STATIC} DESTINATION lib/awsmock)
install(FILES ${HEADERS} DESTINATION include/awsmock/core)