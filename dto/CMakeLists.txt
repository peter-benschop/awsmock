
set(LIBRARY awsmockdto)
set(LIBRARY_STATIC awsmockdto_static)

set(SOURCES ./src/dto/s3/CreateBucketRequest.cpp ./src/dto/s3/CreateBucketResponse.cpp ./src/dto/s3/ListAllBucketResponse.cpp
        ./src/dto/s3/InitiateMultipartUploadResult.cpp ./src/dto/s3/CompleteMultipartUploadResult.cpp
        ./src/dto/s3/RestErrorResponse.cpp ./src/dto/s3/ListBucketResult.cpp ./src/dto/s3/PutObjectRequest.cpp
        ./src/dto/s3/PutObjectResponse.cpp)
set(HEADERS ./include/awsmock/dto/s3/CreateBucketRequest.h ./include/awsmock/dto/s3/CreateBucketResponse.h
        ./include/awsmock/dto/s3/ListAllBucketResponse.h ./include/awsmock/dto/s3/ListAllBucketResponse.h
        ./include/awsmock/dto/s3/CompleteMultipartUploadResult.h ./include/awsmock/dto/s3/RestErrorResponse.h
        ./include/awsmock/dto/s3/ListBucketResult.h ./include/awsmock/dto/s3/PutObjectRequest.h
        ./include/awsmock/dto/s3/PutObjectResponse.h)

# Includes
include_directories(include ../core/include ../db/include /usr/include /usr/local/include)

add_library(${LIBRARY} SHARED ${SOURCES})
add_library(${LIBRARY_STATIC} STATIC ${SOURCES})
set_target_properties(${LIBRARY_STATIC} PROPERTIES OUTPUT_NAME ${LIBRARY})

install(TARGETS ${LIBRARY} ${LIBRARY_STATIC} DESTINATION lib/awsmock)
install(FILES ${HEADERS} DESTINATION include/awsmock/dto)