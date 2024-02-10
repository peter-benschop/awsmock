
set(LIBRARY awsmockdto)
set(LIBRARY_STATIC awsmockdto_static)

set(COMMON_SOURCES src/common/UserAgent.cpp src/common/Infrastructure.cpp src/common/Services.cpp)
set(SQS_SOURCES src/sqs/CreateQueueRequest.cpp src/sqs/CreateQueueResponse.cpp src/sqs/MessageAttribute.cpp
        src/sqs/SendMessageRequest.cpp src/sqs/SendMessageResponse.cpp src/sqs/ListQueueResponse.cpp
        src/sqs/GetQueueAttributesRequest.cpp src/sqs/GetQueueAttributesResponse.cpp src/sqs/TagQueueRequest.cpp
        src/sqs/SetQueueAttributesRequest.cpp src/sqs/GetQueueUrlRequest.cpp src/sqs/RestErrorResponse.cpp
        src/sqs/GetQueueUrlResponse.cpp src/sqs/ReceiveMessageRequest.cpp src/sqs/ReceiveMessageResponse.cpp
        src/sqs/PurgeQueueRequest.cpp src/sqs/DeleteQueueRequest.cpp src/sqs/ChangeMessageVisibilityRequest.cpp
        src/sqs/DeleteMessageRequest.cpp src/sqs/DeleteMessageBatchEntry.cpp src/sqs/DeleteMessageBatchRequest.cpp
        src/sqs/SqsCommonRequest.cpp)
set(SNS_SOURCES src/sns/SqsNotificationRequest.cpp src/sns/SubscribeRequest.cpp src/sns/SubscribeResponse.cpp
        src/sns/UnsubscribeRequest.cpp src/sns/UnsubscribeResponse.cpp src/sns/CreateTopicRequest.cpp
        src/sns/CreateTopicResponse.cpp src/sns/DeleteTopicResponse.cpp src/sns/ListTopicsResponse.cpp
        src/sns/PublishRequest.cpp src/sns/PublishResponse.cpp src/sns/TagResourceRequest.cpp
        src/sns/TagResourceResponse.cpp src/sns/GetTopicAttributesRequest.cpp src/sns/GetTopicAttributesResponse.cpp
        src/sns/ListSubscriptionsByTopicRequest.cpp src/sns/ListSubscriptionsByTopicResponse.cpp src/sns/Subscription.cpp)
set(S3_SOURCES src/s3/CreateBucketRequest.cpp src/s3/CreateBucketResponse.cpp src/s3/PutBucketVersioningRequest.cpp
        src/s3/PutObjectRequest.cpp src/s3/GetObjectRequest.cpp src/s3/GetObjectResponse.cpp
        src/s3/DeleteObjectRequest.cpp src/s3/DeleteObjectsRequest.cpp src/s3/DeleteObjectsResponse.cpp
        src/s3/CompleteMultipartUploadResult.cpp src/s3/CopyObjectRequest.cpp src/s3/CopyObjectResponse.cpp
        src/s3/MoveObjectRequest.cpp src/s3/MoveObjectResponse.cpp src/s3/CreateBucketConstraint.cpp
        src/s3/UserIdentity.cpp src/s3/GetMetadataRequest.cpp src/s3/GetMetadataResponse.cpp
        src/s3/ListAllBucketResponse.cpp src/s3/ListBucketRequest.cpp src/s3/ListAllBucketResponse.cpp
        src/s3/Owner.cpp src/s3/Content.cpp)
set(DOCKER_SOURCES src/docker/Port.cpp src/docker/Container.cpp src/docker/ListContainerResponse.cpp
        src/docker/CreateContainerRequest.cpp src/docker/Filters.cpp)
set(LAMBDA_SOURCES src/lambda/ListTagsResponse.cpp src/lambda/ListFunctionResponse.cpp src/lambda/DeadLetterConfig.cpp
        src/lambda/Function.cpp src/lambda/InvocationNotification.cpp src/lambda/CreateNotification.cpp
        src/lambda/CreateTagRequest.cpp)
set(COGNITO_SOURCES src/cognito/ListUserPoolRequest.cpp src/cognito/ListUserPoolResponse.cpp
        src/cognito/CreateUserPoolRequest.cpp src/cognito/CreateUserPoolResponse.cpp src/cognito/UserAttribute.cpp
        src/cognito/DeleteUserPoolRequest.cpp src/cognito/AdminCreateUserRequest.cpp
        src/cognito/AdminCreateUserResponse.cpp src/cognito/AdminDeleteUserRequest.cpp src/cognito/ListUsersRequest.cpp
        src/cognito/ListUsersResponse.cpp)
set(TRANSFER_SOURCES src/transfer/Tag.cpp src/transfer/CreateServerRequest.cpp src/transfer/CreateServerResponse.cpp
        src/transfer/CreateUserRequest.cpp src/transfer/CreateUserResponse.cpp src/transfer/DeleteServerRequest.cpp
        src/transfer/IdentityProviderDetails.cpp src/transfer/ListServerRequest.cpp src/transfer/ListServerResponse.cpp
        src/transfer/Server.cpp src/transfer/StartServerRequest.cpp src/transfer/StopServerRequest.cpp)
set(DYNAMODB_SOURCES src/dynamodb/CreateTableRequest.cpp src/dynamodb/CreateTableResponse.cpp
        src/dynamodb/DeleteTableRequest.cpp src/dynamodb/DeleteTableResponse.cpp src/dynamodb/ProvisionedThroughput.cpp
        src/dynamodb/ListTableRequest.cpp src/dynamodb/ListTableRequest.cpp src/dynamodb/ListTableResponse.cpp
        src/dynamodb/GetItemRequest.cpp src/dynamodb/GetItemResponse.cpp src/dynamodb/PutItemRequest.cpp
        src/dynamodb/PutItemResponse.cpp src/dynamodb/QueryRequest.cpp src/dynamodb/QueryResponse.cpp
        src/dynamodb/DeleteItemRequest.cpp src/dynamodb/DeleteItemResponse.cpp src/dynamodb/AttributeValue.cpp)
set(MODULE_SOURCES src/module/Module.cpp src/module/GatewayConfig.cpp)

set(SOURCES ${COMMON_SOURCES} ${SQS_SOURCES} ${SNS_SOURCES} ${S3_SOURCES} ${DOCKER_SOURCES} ${LAMBDA_SOURCES}
        ${COGNITO_SOURCES} ${TRANSFER_SOURCES} ${DYNAMODB_SOURCES} ${MODULE_SOURCES})

# Test directory
add_subdirectory(tst)

# Includes
include_directories(include ../core/include ../db/include /usr/include/mongo /usr/include/bsoncxx/v_noabi
        /usr/include/mongocxx/v_noabi)

add_library(${LIBRARY} SHARED ${SOURCES}
        include/awsmock/dto/s3/Content.h
        include/awsmock/dto/dynamodb/TableStatus.h
        include/awsmock/dto/dynamodb/AttributeValue.h
        src/docker/Filters.cpp
        include/awsmock/dto/docker/Filters.h)
add_library(${LIBRARY_STATIC} STATIC ${SOURCES})
set_target_properties(${LIBRARY_STATIC} PROPERTIES OUTPUT_NAME ${LIBRARY})

install(TARGETS ${LIBRARY} DESTINATION lib)
install(TARGETS ${LIBRARY_STATIC} DESTINATION lib)
