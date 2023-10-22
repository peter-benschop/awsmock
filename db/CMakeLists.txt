
set(LIBRARY awsmockdb)
set(LIBRARY_STATIC awsmockdb_static)

set(SQS_SOURCES src/entity/sqs/MessageAttribute.cpp src/entity/sqs/Message.cpp src/repository/SQSDatabase.cpp)
set(SNS_SOURCES src/repository/SNSDatabase.cpp)
set(S3_SOURCES src/entity/s3/Bucket.cpp src/entity/s3/BucketNotification.cpp src/entity/s3/Object.cpp
        src/repository/S3Database.cpp)
set(LAMBDA_SOURCES src/entity/lambda/Tags.cpp src/entity/lambda/Environment.cpp
        src/entity/lambda/EphemeralStorage.cpp src/entity/lambda/Lambda.cpp src/repository/LambdaDatabase.cpp)
set(TRANSFER_SOURCES src/repository/TransferDatabase.cpp src/entity/transfer/User.cpp src/entity/transfer/Transfer.cpp)
set(SERVICE_SOURCES src/entity/service/Service.cpp src/repository/ServiceDatabase.cpp)

set(SOURCES src/repository/Database.cpp src/utils/TestUtils.cpp ${SQS_SOURCES} ${SNS_SOURCES} ${S3_SOURCES} ${LAMBDA_SOURCES}
        ${TRANSFER_SOURCES} ${SERVICE_SOURCES})

# Test directory
add_subdirectory(tst)

# Includes
include_directories(include ../core/include /usr/include /usr/include/mongo /usr/include/bsoncxx/v_noabi
        /usr/include/mongocxx/v_noabi tbb)

add_library(${LIBRARY} SHARED ${SOURCES}
        include/awsmock/entity/service/Service.h)
add_library(${LIBRARY_STATIC} STATIC ${SOURCES})
set_target_properties(${LIBRARY_STATIC} PROPERTIES OUTPUT_NAME ${LIBRARY})

install(TARGETS ${LIBRARY} DESTINATION lib)
