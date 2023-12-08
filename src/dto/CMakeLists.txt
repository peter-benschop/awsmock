
set(LIBRARY awsmockdto)
set(LIBRARY_STATIC awsmockdto_static)

set(COMMON_SOURCES src/common/UserAgent.cpp)
set(SQS_SOURCES src/sqs/CreateQueueRequest.cpp src/sqs/CreateQueueResponse.cpp src/sqs/MessageAttribute.cpp
        src/sqs/SendMessageRequest.cpp src/sqs/SendMessageResponse.cpp src/sqs/ListQueueResponse.cpp
        src/sqs/GetQueueAttributesRequest.cpp src/sqs/GetQueueAttributesResponse.cpp
        src/sqs/SetQueueAttributesRequest.cpp src/sqs/GetQueueUrlRequest.cpp src/sqs/RestErrorResponse.cpp
        src/sqs/GetQueueUrlResponse.cpp src/sqs/ReceiveMessageRequest.cpp src/sqs/ReceiveMessageResponse.cpp
        src/sqs/PurgeQueueRequest.cpp src/sqs/DeleteQueueRequest.cpp src/sqs/ChangeMessageVisibilityRequest.cpp
        src/sqs/DeleteMessageRequest.cpp src/sqs/DeleteMessageBatchEntry.cpp src/sqs/DeleteMessageBatchRequest.cpp)
set(SNS_SOURCES src/sns/SqsNotificationRequest.cpp src/sns/SubscribeRequest.cpp src/sns/SubscribeResponse.cpp
        src/sns/UnsubscribeRequest.cpp src/sns/UnsubscribeResponse.cpp)
set(S3_SOURCES src/s3/CreateBucketRequest.cpp src/s3/CreateBucketResponse.cpp src/s3/PutBucketVersioningRequest.cpp
        src/s3/PutObjectRequest.cpp src/s3/GetObjectRequest.cpp src/s3/GetObjectResponse.cpp
        src/s3/DeleteObjectRequest.cpp src/s3/DeleteObjectsRequest.cpp src/s3/DeleteObjectsResponse.cpp
        src/s3/CompleteMultipartUploadResult.cpp src/s3/CopyObjectRequest.cpp src/s3/CopyObjectResponse.cpp
        src/s3/MoveObjectRequest.cpp src/s3/MoveObjectResponse.cpp src/s3/CreateBucketConstraint.cpp
        src/s3/UserIdentity.cpp src/s3/GetMetadataRequest.cpp src/s3/GetMetadataResponse.cpp)
set(DOCKER_SOURCES src/docker/Port.cpp src/docker/Container.cpp src/docker/ListContainerResponse.cpp
        src/docker/CreateContainerRequest.cpp)
set(LAMBDA_SOURCES src/lambda/ListTagsResponse.cpp src/lambda/ListFunctionResponse.cpp src/lambda/DeadLetterConfig.cpp
        src/lambda/Function.cpp src/lambda/InvocationNotification.cpp src/lambda/CreateNotification.cpp
        src/lambda/CreateTagRequest.cpp)
set(COGNITO_SOURCES src/cognito/ListUserPoolRequest.cpp src/cognito/ListUserPoolResponse.cpp
        src/cognito/CreateUserPoolRequest.cpp src/cognito/CreateUserPoolResponse.cpp
        src/cognito/DeleteUserPoolRequest.cpp)
set(MODULE_SOURCES src/module/Module.cpp src/module/GatewayConfig.cpp)

set(SOURCES ${COMMON_SOURCES} ${SQS_SOURCES} ${SNS_SOURCES} ${S3_SOURCES} ${DOCKER_SOURCES} ${LAMBDA_SOURCES}
        ${COGNITO_SOURCES} ${MODULE_SOURCES})

# Includes
include_directories(include ../core/include ../db/include /usr/include /usr/include/mongo /usr/include/bsoncxx/v_noabi
        /usr/include/mongocxx/v_noabi tbb)

add_library(${LIBRARY} SHARED ${SOURCES}
        include/awsmock/dto/lambda/InvocationNotification.h
        include/awsmock/dto/module/Module.h
        src/Module.cpp
        include/awsmock/dto/cognito/ListUserPoolRequest.h
        include/awsmock/dto/common/UserAgent.h
        include/awsmock/dto/sqs/MessageAttributeDataType.h)
add_library(${LIBRARY_STATIC} STATIC ${SOURCES})
set_target_properties(${LIBRARY_STATIC} PROPERTIES OUTPUT_NAME ${LIBRARY})

install(TARGETS ${LIBRARY} DESTINATION lib)
