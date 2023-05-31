
set(LIBRARY awsmockcore)
set(LIBRARY_STATIC awsmockcore_static)

set(UTILS_SOURCES src/utils/StringUtils.cpp src/utils/FileUtils.cpp src/utils/DirUtils.cpp src/utils/DateTimeUtils.cpp)
set(UTILS_HEADERS include/awsmock/core/StringUtils.h include/awsmock/core/FileUtils.h include/awsmock/core/DirUtils.h
        include/awsmock/core/DateTimeUtils.h)

set(EXCEPTION_SOURCES src/exception/CoreException.cpp src/exception/ServiceException.cpp
        src/exception/ResourceNotFoundException.cpp)
set(EXCEPTION_HEADERS include/awsmock/core/CoreException.h include/awsmock/core/ServiceException.h
        include/awsmock/core/ResourceNotFoundException.h)

set(DTO_SOURCES src/dto/s3/CreateBucketRequest.cpp src/dto/s3/CreateBucketResponse.cpp src/dto/s3/ListAllBucketResponse.cpp
        src/dto/s3/InitiateMultipartUploadResult.cpp src/dto/s3/CompleteMultipartUploadResult.cpp
        src/dto/s3/RestErrorResponse.cpp)
set(DTO_HEADERS include/awsmock/dto/s3/CreateBucketRequest.h include/awsmock/dto/s3/CreateBucketResponse.h
        include/awsmock/dto/s3/ListAllBucketResponse.h include/awsmock/dto/s3/ListAllBucketResponse.h
        include/awsmock/dto/s3/CompleteMultipartUploadResult.h include/awsmock/dto/s3/RestErrorResponse.h)

set(SOURCES src/config/Configuration.cpp src/logging/Logger.cpp src/monitoring/MetricService.cpp
        src/monitoring/MetricSystemCollector.cpp ${UTILS_SOURCES} ${EXCEPTION_SOURCES} ${DTO_SOURCES})
set(HEADERS include/awsmock/core/Configuration.h include/awsmock/core/Logger.h include/awsmock/core/MetricService.h
        include/awsmock/core/MetricSystemCollector.h include/awsmock/core/MetricServiceTimer.h
        include/awsmock/core/MetricDefinition.h ${UTILS_HEADERS} ${EXCEPTION_HEADERS} ${DTO_HEADERS})

# Includes
include_directories(/usr/include /usr/local/include include)

add_library(${LIBRARY} SHARED ${SOURCES})
add_library(${LIBRARY_STATIC} STATIC ${SOURCES})
set_target_properties(${LIBRARY_STATIC} PROPERTIES OUTPUT_NAME ${LIBRARY})

install(TARGETS ${LIBRARY} ${LIBRARY_STATIC} DESTINATION lib/awsmock)
install(FILES ${HEADERS} DESTINATION include/awsmock/core)