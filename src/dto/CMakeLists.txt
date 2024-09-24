
set(LIBRARY awsmockdto)
set(LIBRARY_STATIC awsmockdto_static)

set(COMMON_SOURCES src/common/UserAgent.cpp src/common/S3ClientCommand.cpp src/common/SQSClientCommand.cpp src/common/Services.cpp src/common/Infrastructure.cpp
        src/common/SNSClientCommand.cpp src/common/DynamoDbClientCommand.cpp src/common/SecretsManagerClientCommand.cpp src/common/KMSClientCommand.cpp
        src/common/LambdaClientCommand.cpp src/common/SSMClientCommand.cpp)
set(SQS_SOURCES src/sqs/CreateQueueRequest.cpp src/sqs/CreateQueueResponse.cpp src/sqs/model/MessageAttribute.cpp src/sqs/SendMessageRequest.cpp
        src/sqs/ListQueueResponse.cpp src/sqs/SendMessageRequest.cpp src/sqs/SendMessageResponse.cpp src/sqs/TagQueueRequest.cpp src/sqs/GetQueueUrlRequest.cpp
        src/sqs/GetQueueAttributesRequest.cpp src/sqs/GetQueueAttributesResponse.cpp src/sqs/SetQueueAttributesRequest.cpp src/sqs/SetQueueAttributesResponse.cpp
        src/sqs/RestErrorResponse.cpp src/sqs/GetQueueUrlResponse.cpp src/sqs/ReceiveMessageRequest.cpp src/sqs/ReceiveMessageResponse.cpp src/sqs/PurgeQueueRequest.cpp
        src/sqs/DeleteQueueRequest.cpp src/sqs/ChangeMessageVisibilityRequest.cpp src/sqs/DeleteMessageRequest.cpp src/sqs/DeleteMessageBatchEntry.cpp
        src/sqs/DeleteMessageBatchRequest.cpp src/sqs/SqsCommonRequest.cpp src/sqs/DeleteQueueResponse.cpp src/sqs/DeleteMessageResponse.cpp
        src/sqs/model/EventNotification.cpp src/sqs/model/EventRecord.cpp src/sqs/SendMessageBatchRequest.cpp src/sqs/SendMessageBatchResponse.cpp
        src/sqs/model/MessageEntry.cpp src/sqs/model/MessageSuccessful.cpp src/sqs/model/MessageFailed.cpp)
set(SNS_SOURCES src/sns/SqsNotificationRequest.cpp src/sns/SubscribeRequest.cpp src/sns/SubscribeResponse.cpp src/sns/CreateTopicRequest.cpp
        src/sns/UnsubscribeRequest.cpp src/sns/UnsubscribeResponse.cpp src/sns/CreateTopicResponse.cpp src/sns/DeleteTopicResponse.cpp src/sns/ListTopicsResponse.cpp
        src/sns/PublishRequest.cpp src/sns/PublishResponse.cpp src/sns/TagResourceRequest.cpp src/sns/TagResourceResponse.cpp src/sns/GetTopicAttributesRequest.cpp
        src/sns/GetTopicAttributesResponse.cpp src/sns/ListSubscriptionsByTopicRequest.cpp src/sns/ListSubscriptionsByTopicResponse.cpp src/sns/Subscription.cpp)
set(S3_SOURCES src/s3/CreateBucketRequest.cpp src/s3/CreateBucketResponse.cpp src/s3/PutBucketVersioningRequest.cpp src/s3/PutObjectRequest.cpp
        src/s3/GetObjectRequest.cpp src/s3/GetObjectResponse.cpp src/s3/DeleteObjectRequest.cpp src/s3/DeleteObjectsRequest.cpp src/s3/DeleteObjectsResponse.cpp
        src/s3/CompleteMultipartUploadResult.cpp src/s3/CopyObjectRequest.cpp src/s3/CopyObjectResponse.cpp src/s3/MoveObjectRequest.cpp src/s3/MoveObjectResponse.cpp
        src/s3/CreateBucketConstraint.cpp src/s3/model/UserIdentity.cpp src/s3/GetMetadataRequest.cpp src/s3/GetMetadataResponse.cpp src/s3/ListAllBucketResponse.cpp
        src/s3/ListBucketRequest.cpp src/s3/ListBucketResponse.cpp src/s3/ListAllBucketResponse.cpp src/s3/DeleteBucketRequest.cpp src/s3/model/Content.cpp
        src/s3/CreateMultipartUploadRequest.cpp src/s3/model/Owner.cpp src/s3/CreateMultipartUploadResult.cpp src/s3/ListObjectVersionsRequest.cpp
        src/s3/ListObjectVersionsResponse.cpp src/s3/PutBucketNotificationRequest.cpp src/s3/model/FilterRule.cpp src/s3/PutBucketNotificationConfigurationRequest.cpp
        src/s3/PutBucketNotificationConfigurationResponse.cpp src/s3/model/QueueConfiguration.cpp src/s3/model/TopicConfiguration.cpp src/s3/mapper/Mapper.cpp
        src/s3/model/LambdaConfiguration.cpp src/s3/PutBucketEncryptionRequest.cpp src/s3/model/ObjectVersion.cpp src/s3/model/RestoreStatus.cpp
        src/s3/model/ObjectVersion.cpp src/s3/model/RestoreStatus.cpp src/s3/model/ObjectVersion.cpp src/s3/model/RestoreStatus.cpp src/s3/UploadPartCopyRequest.cpp
        src/s3/UploadPartCopyResponse.cpp)
set(DOCKER_SOURCES src/docker/model/Port.cpp src/docker/model/Container.cpp src/docker/model/Image.cpp src/docker/ListContainerResponse.cpp src/docker/ListImageResponse.cpp
        src/docker/CreateContainerRequest.cpp src/docker/model/Filters.cpp src/docker/CreateContainerResponse.cpp)
set(LAMBDA_SOURCES src/lambda/ListTagsResponse.cpp src/lambda/ListFunctionResponse.cpp src/lambda/model/Function.cpp src/lambda/model/DeadLetterConfig.cpp
        src/lambda/model/Code.cpp src/lambda/CreateTagRequest.cpp src/lambda/CreateFunctionRequest.cpp src/lambda/CreateFunctionResponse.cpp
        src/lambda/GetFunctionResponse.cpp src/lambda/model/Tags.cpp src/lambda/model/Error.cpp src/lambda/model/Environment.cpp src/lambda/model/UserIdentity.cpp
        src/lambda/mapper/Mapper.cpp src/lambda/model/AccountLimit.cpp src/lambda/model/AccountUsage.cpp src/lambda/AccountSettingsResponse.cpp
        src/lambda/model/Configuration.cpp src/lambda/CreateEventSourceMappingsRequest.cpp src/lambda/CreateEventSourceMappingsResponse.cpp
        src/lambda/ListEventSourceMappingsRequest.cpp src/lambda/ListEventSourceMappingsResponse.cpp src/lambda/model/EventSourceMapping.cpp)
set(COGNITO_SOURCES src/cognito/ListUserPoolRequest.cpp src/cognito/ListUserPoolResponse.cpp src/cognito/model/Group.cpp src/cognito/CreateGroupRequest.cpp
        src/cognito/CreateUserPoolRequest.cpp src/cognito/CreateUserPoolResponse.cpp src/cognito/model/UserAttribute.cpp src/cognito/DeleteUserPoolRequest.cpp
        src/cognito/AdminCreateUserRequest.cpp src/common/CognitoClientCommand.cpp src/cognito/AdminCreateUserResponse.cpp src/cognito/AdminDeleteUserRequest.cpp
        src/cognito/ListUsersRequest.cpp src/cognito/ListUsersResponse.cpp src/cognito/model/LambdaConfig.cpp src/cognito/model/CustomEmailSender.cpp src/cognito/model/UserPool.cpp
        src/cognito/model/CustomSmsSender.cpp src/cognito/PreTokenGenerationConfig.cpp src/cognito/mapper/Mapper.cpp src/cognito/DeleteGroupRequest.cpp
        src/cognito/CreateUserPoolDomainRequest.cpp src/cognito/CreateUserPoolDomainResponse.cpp src/cognito/CreateGroupResponse.cpp src/cognito/ListGroupRequest.cpp
        src/cognito/ListGroupsResponse.cpp src/cognito/model/UserPoolClient.cpp src/cognito/AdminAddUserToGroupRequest.cpp src/cognito/CreateUserPoolClientRequest.cpp
        src/cognito/CreateUserPoolClientResponse.cpp src/cognito/DescribeUserPoolRequest.cpp src/cognito/DescribeUserPoolResponse.cpp src/cognito/model/User.cpp
        src/cognito/ListUsersInGroupRequest.cpp src/cognito/ListUsersInGroupResponse.cpp src/cognito/model/UserContextData.cpp src/cognito/InitiateAuthRequest.cpp
        src/cognito/model/AuthenticationResult.cpp src/cognito/InitiateAuthRequest.cpp src/cognito/InitiateAuthResponse.cpp src/cognito/SignUpRequest.cpp
        src/cognito/SignUpResponse.cpp src/cognito/ListUserPoolClientsRequest.cpp src/cognito/ListUserPoolClientsResponse.cpp src/cognito/DeleteUserPoolClientRequest.cpp
        src/cognito/DescribeUserPoolClientRequest.cpp src/cognito/DescribeUserPoolClientResponse.cpp src/cognito/UpdateUserPoolRequest.cpp
        src/cognito/UpdateUserPoolClientRequest.cpp src/cognito/model/TokenValidityUnits.cpp src/cognito/UpdateUserPoolDomainRequest.cpp
        src/cognito/AdminConfirmUserRequest.cpp src/cognito/UpdateUserPoolDomainResponse.cpp src/cognito/DescribeUserPoolDomainRequest.cpp
        src/cognito/DescribeUserPoolDomainResponse.cpp src/cognito/model/ValidationData.cpp src/cognito/AdminRemoveUserFromGroupRequest.cpp
        src/cognito/AdminEnableUserRequest.cpp src/cognito/AdminDisableUserRequest.cpp src/cognito/ResponseToAuthChallengeRequest.cpp
        src/cognito/ResponseToAuthChallengeResponse.cpp)
set(TRANSFER_SOURCES src/transfer/model/Tag.cpp src/transfer/CreateServerRequest.cpp src/transfer/CreateServerResponse.cpp src/transfer/ListUsersRequest.cpp
        src/transfer/ListUsersResponse.cpp src/transfer/CreateUserRequest.cpp src/transfer/CreateUserResponse.cpp src/transfer/DeleteServerRequest.cpp
        src/transfer/IdentityProviderDetails.cpp src/transfer/ListServerRequest.cpp src/transfer/ListServerResponse.cpp src/transfer/model/Server.cpp
        src/transfer/StartServerRequest.cpp src/transfer/StopServerRequest.cpp src/transfer/model/User.cpp src/transfer/mapper/Mapper.cpp)
set(DYNAMODB_SOURCES src/dynamodb/CreateTableRequest.cpp src/dynamodb/CreateTableResponse.cpp src/dynamodb/DeleteTableRequest.cpp src/dynamodb/DeleteTableResponse.cpp
        src/dynamodb/model/ProvisionedThroughput.cpp src/dynamodb/ListTableRequest.cpp src/dynamodb/ListTableRequest.cpp src/dynamodb/ListTableResponse.cpp
        src/dynamodb/GetItemRequest.cpp src/dynamodb/GetItemResponse.cpp src/dynamodb/PutItemRequest.cpp src/dynamodb/PutItemResponse.cpp src/dynamodb/QueryRequest.cpp
        src/dynamodb/QueryResponse.cpp src/dynamodb/DeleteItemRequest.cpp src/dynamodb/DeleteItemResponse.cpp src/dynamodb/model/AttributeValue.cpp
        src/dynamodb/DescribeTableRequest.cpp src/dynamodb/DescribeTableResponse.cpp src/dynamodb/ScanRequest.cpp src/dynamodb/ScanResponse.cpp src/dynamodb/model/Key.cpp
        src/dynamodb/mapper/Mapper.cpp)
set(SECRETSMANAGER_SOURCES src/secretsmanager/CreateSecretRequest.cpp src/secretsmanager/CreateSecretResponse.cpp src/secretsmanager/DeleteSecretRequest.cpp
        src/secretsmanager/DeleteSecretResponse.cpp src/secretsmanager/DescribeSecretRequest.cpp src/secretsmanager/DescribeSecretResponse.cpp
        src/secretsmanager/GetSecretValueRequest.cpp src/secretsmanager/GetSecretValueResponse.cpp src/secretsmanager/ReplicationStatus.cpp
        src/secretsmanager/VersionIdsToStages.cpp src/secretsmanager/UpdateSecretRequest.cpp src/secretsmanager/UpdateSecretResponse.cpp src/secretsmanager/SecretTags.cpp
        src/secretsmanager/RotateSecretRequest.cpp src/secretsmanager/Filter.cpp src/secretsmanager/RotateSecretResponse.cpp src/secretsmanager/RotationRules.cpp
        src/secretsmanager/Secret.cpp src/secretsmanager/ListSecretsRequest.cpp src/secretsmanager/ListSecretsResponse.cpp)
set(KMS_SOURCES src/kms/CreateKeyRequest.cpp src/kms/CreateKeyResponse.cpp src/kms/Key.cpp src/kms/ListKey.cpp src/kms/ScheduleKeyDeletionRequest.cpp
        src/kms/ScheduleKeyDeletionResponse.cpp src/kms/ListKeysRequest.cpp src/kms/ListKeysResponse.cpp src/kms/DescribeKeyRequest.cpp src/kms/DescribeKeyResponse.cpp
        src/kms/EncryptRequest.cpp src/kms/EncryptResponse.cpp src/kms/DecryptRequest.cpp src/kms/DecryptResponse.cpp
        src/kms/DescribeKeyRequest.cpp src/kms/DescribeKeyResponse.cpp)
set(SSM_SOURCES src/ssm/mapper/Mapper.cpp src/ssm/PutParameterRequest.cpp src/ssm/PutParameterResponse.cpp src/ssm/model/Parameter.cpp src/ssm/GetParameterRequest.cpp
        src/ssm/GetParameterResponse.cpp src/ssm/DeleteParameterRequest.cpp src/ssm/model/ParameterFilter.cpp src/ssm/DescribeParametersRequest.cpp
        src/ssm/DescribeParametersResponse.cpp)
set(MODULE_SOURCES src/module/Module.cpp src/module/GatewayConfig.cpp src/module/mapper/Mapper.cpp)

set(SOURCES ${COMMON_SOURCES} ${SQS_SOURCES} ${SNS_SOURCES} ${S3_SOURCES} ${DOCKER_SOURCES} ${LAMBDA_SOURCES} ${COGNITO_SOURCES} ${TRANSFER_SOURCES} ${DYNAMODB_SOURCES}
        ${SECRETSMANAGER_SOURCES} ${KMS_SOURCES} ${SSM_SOURCES} ${MODULE_SOURCES})

# Test directory
add_subdirectory(tst)

# Includes
include_directories(include ../core/include ../db/include ${INC_BSON_CXX} ${INC_MONGO_CXX} /usr/local/include)

add_library(${LIBRARY} SHARED ${SOURCES}
        include/awsmock/dto/ssm/model/Parameter.h
        include/awsmock/dto/sqs/model/MessageFailed.h)

add_library(${LIBRARY_STATIC} STATIC ${SOURCES})
set_target_properties(${LIBRARY_STATIC} PROPERTIES OUTPUT_NAME ${LIBRARY})

install(TARGETS ${LIBRARY} DESTINATION lib)
