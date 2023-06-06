
set(LIBRARY awsmockdto)
set(LIBRARY_STATIC awsmockdto_static)

set(S3_SOURCES ./src/dto/s3/ListAllBucketResponse.cpp
        ./src/dto/s3/InitiateMultipartUploadResult.cpp ./src/dto/s3/CompleteMultipartUploadResult.cpp
        ./src/dto/s3/GetMetadataRequest.cpp ./src/dto/s3/GetMetadataResponse.cpp
        )
set(S3_HEADERS ./include/awsmock/dto/s3/CreateBucketRequest.h ./include/awsmock/dto/s3/CreateBucketResponse.h
        ./include/awsmock/dto/s3/ListAllBucketResponse.h ./include/awsmock/dto/s3/ListAllBucketResponse.h
        ./include/awsmock/dto/s3/CompleteMultipartUploadResult.h ./include/awsmock/dto/s3/RestErrorResponse.h
        ./include/awsmock/dto/s3/ListBucketResult.h ./include/awsmock/dto/s3/PutObjectRequest.h
        ./include/awsmock/dto/s3/PutObjectResponse.h include/awsmock/dto/s3/GetMetadataRequest.h
        include/awsmock/dto/s3/GetMetadataResponse.h include/awsmock/dto/s3/GetObjectRequest.h
        include/awsmock/dto/s3/GetObjectResponse.h)

set(SQS_SOURCES  )
set(SQS_HEADERS ./include/awsmock/dto/sqs/CreateQueueRequest.h ./include/awsmock/dto/sqs/CreateQueueResponse.h
        ListQueueResponse.h ./include/awsmock/dto/sqs/ListQueueResponse.h)

set(SOURCES ${S3_SOURCES} ${SQS_SOURCES})
set(HEADERS ${S3_HEADERS} ${SQS_HEADERS})

# Includes
include_directories(include ../core/include ../db/include /usr/include /usr/local/include)

add_library(${LIBRARY} SHARED ${SOURCES})
add_library(${LIBRARY_STATIC} STATIC ${SOURCES})
set_target_properties(${LIBRARY_STATIC} PROPERTIES OUTPUT_NAME ${LIBRARY})

install(TARGETS ${LIBRARY} ${LIBRARY_STATIC} DESTINATION lib)
