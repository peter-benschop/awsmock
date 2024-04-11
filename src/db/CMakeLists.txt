
set(LIBRARY awsmockdb)
set(LIBRARY_STATIC awsmockdb_static)

set(SQS_SOURCES src/entity/sqs/MessageAttribute.cpp src/entity/sqs/Message.cpp src/repository/SQSDatabase.cpp
        src/memorydb/SQSMemoryDb.cpp src/entity/sqs/Queue.cpp src/entity/sqs/QueueAttribute.cpp
        src/entity/sqs/RedrivePolicy.cpp)
set(SNS_SOURCES src/entity/sns/MessageAttribute.cpp src/entity/sns/Message.cpp src/entity/sns/Topic.cpp
        src/entity/sns/TopicAttribute.cpp src/entity/sns/Subscription.cpp src/repository/SNSDatabase.cpp
        src/memorydb/SNSMemoryDb.cpp)
set(S3_SOURCES src/entity/s3/Bucket.cpp src/entity/s3/BucketNotification.cpp src/entity/s3/Object.cpp
        src/repository/S3Database.cpp src/memorydb/S3MemoryDb.cpp)
set(LAMBDA_SOURCES src/entity/lambda/Tags.cpp src/entity/lambda/Environment.cpp src/entity/lambda/Lambda.cpp
        src/entity/lambda/EphemeralStorage.cpp src/repository/LambdaDatabase.cpp src/memorydb/LambdaMemoryDb.cpp)
set(TRANSFER_SOURCES src/repository/TransferDatabase.cpp src/entity/transfer/User.cpp src/entity/transfer/Transfer.cpp
        src/memorydb/TransferMemoryDb.cpp)
set(COGNITO_SOURCES src/entity/cognito/UserPool.cpp src/entity/cognito/User.cpp src/memorydb/CognitoMemoryDb.cpp
        src/repository/CognitoDatabase.cpp)
set(DYNAMODB_SOURCES src/entity/dynamodb/Item.cpp src/entity/dynamodb/Table.cpp src/entity/dynamodb/AttributeValue.cpp
        src/repository/DynamoDbDatabase.cpp src/memorydb/DynamoDbMemoryDb.cpp)
set(SECRETSMANAGER_SOURCES src/entity/secretsmanager/Secret.cpp src/entity/secretsmanager/RotationRules.cpp
        src/repository/SecretsManagerDatabase.cpp src/memorydb/SecretsManagerMemoryDb.cpp)
set(MODULE_SOURCES src/entity/module/Module.cpp src/repository/ModuleDatabase.cpp src/memorydb/ModuleMemoryDb.cpp)

set(SOURCES src/repository/Database.cpp src/utils/TestUtils.cpp ${SQS_SOURCES} ${SNS_SOURCES} ${S3_SOURCES}
        ${LAMBDA_SOURCES} ${TRANSFER_SOURCES} ${COGNITO_SOURCES} ${DYNAMODB_SOURCES} ${MODULE_SOURCES}
        ${SECRETSMANAGER_SOURCES})

# Test directory
add_subdirectory(tst)

# Includes
include_directories(include ../core/include /usr/include /usr/include/mongo /usr/include/bsoncxx/v_noabi
        /usr/include/mongocxx/v_noabi)

add_library(${LIBRARY} SHARED ${SOURCES}
        include/awsmock/memorydb/SQSMemoryDb.h
        include/awsmock/entity/cognito/UserPool.h
        include/awsmock/entity/cognito/UserStatus.h
        include/awsmock/entity/cognito/UserAttribute.h
        include/awsmock/entity/sqs/QueueAttribute.h
        include/awsmock/entity/sqs/RedrivePolicy.h
        ../dto/include/awsmock/dto/transfer/IdentityProviderDetails.h)
add_library(${LIBRARY_STATIC} STATIC ${SOURCES})
set_target_properties(${LIBRARY_STATIC} PROPERTIES OUTPUT_NAME ${LIBRARY})

install(TARGETS ${LIBRARY} DESTINATION lib)
install(TARGETS ${LIBRARY_STATIC} DESTINATION lib)
