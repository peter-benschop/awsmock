
set(LIBRARY awsmockdto)
set(LIBRARY_STATIC awsmockdto_static)

set(S3_SOURCES ./src/dto/s3/ListAllBucketResponse.cpp
        ./src/dto/s3/InitiateMultipartUploadResult.cpp ./src/dto/s3/CompleteMultipartUploadResult.cpp
        ./src/dto/s3/GetMetadataRequest.cpp ./src/dto/s3/GetMetadataResponse.cpp)

set(SOURCES ${S3_SOURCES})

# Includes
include_directories(include ../core/include ../db/include /usr/include /usr/local/include)

add_library(${LIBRARY} SHARED ${SOURCES})
add_library(${LIBRARY_STATIC} STATIC ${SOURCES})
set_target_properties(${LIBRARY_STATIC} PROPERTIES OUTPUT_NAME ${LIBRARY})

install(TARGETS ${LIBRARY} ${LIBRARY_STATIC} DESTINATION lib)
