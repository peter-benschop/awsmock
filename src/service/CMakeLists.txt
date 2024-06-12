
set(LIBRARY awsmocksrv)
set(LIBRARY_STATIC awsmocksrv_static)

set(COMMON_SOURCES src/common/AbstractHandler.cpp src/common/AbstractServer.cpp src/common/AbstractDomainSocket.cpp)
set(S3_SOURCES src/s3/S3Server.cpp src/s3/S3Handler.cpp src/s3/S3Service.cpp src/s3/S3Monitoring.cpp src/s3/S3HashCreator.cpp src/s3/S3Worker.cpp)
set(SQS_SOURCES src/sqs/SQSServer.cpp src/sqs/SQSHandler.cpp src/sqs/SQSService.cpp src/sqs/SQSMonitoring.cpp src/sqs/SQSWorker.cpp)
set(SNS_SOURCES src/sns/SNSServer.cpp src/sns/SNSHandler.cpp src/sns/SNSWorker.cpp src/sns/SNSService.cpp src/sns/SNSMonitoring.cpp)
set(LAMBDA_SOURCES src/lambda/LambdaServer.cpp src/lambda/LambdaHandler.cpp src/lambda/LambdaService.cpp src/lambda/LambdaCreator.cpp src/lambda/LambdaExecutor.cpp
        src/lambda/LambdaMonitoring.cpp)
set(COGNITO_SOURCES src/cognito/CognitoHandler.cpp src/cognito/CognitoHandler.cpp src/cognito/CognitoService.cpp src/cognito/CognitoServer.cpp
        src/cognito/CognitoMonitoring.cpp)
set(TRANSFER_SOURCES src/transfer/TransferServer.cpp src/transfer/TransferHandler.cpp src/transfer/TransferService.cpp src/transfer/TransferMonitoring.cpp)
set(DYNAMODB_SOURCES src/dynamodb/DynamoDbServer.cpp src/dynamodb/DynamoDbHandler.cpp src/dynamodb/DynamoDbService.cpp src/dynamodb/DynamoDbMonitoring.cpp
        src/dynamodb/DynamoDbWorker.cpp)
set(SECRETMANAGER_SOURCES src/secretsmanager/SecretsManagerServer.cpp src/secretsmanager/SecretsManagerHandler.cpp src/secretsmanager/SecretsManagerService.cpp
        src/secretsmanager/SecretsManagerMonitoring.cpp)
set(KMS_SOURCES src/kms/KMSServer.cpp src/kms/KMSHandler.cpp src/kms/KMSWorker.cpp src/kms/KMSService.cpp src/kms/KMSMonitoring.cpp src/kms/KMSCreator.cpp)
set(FTP_SOURCES src/ftpserver/Filesystem.cpp src/ftpserver/FtpSession.cpp src/ftpserver/FtpServer.cpp src/ftpserver/FtpServerImpl.cpp src/ftpserver/UserDatabase.cpp)
set(GATEWAY_SOURCES src/gateway/GatewayServer.cpp src/gateway/GatewaySession.cpp src/gateway/GatewayListener.cpp)
set(DOCKER_SOURCES src/docker/DockerService.cpp)
set(MODULE_SOURCES src/module/ModuleService.cpp)

set(SOURCES ${COMMON_SOURCES} ${S3_SOURCES} ${SQS_SOURCES} ${SNS_SOURCES}
        ${TRANSFER_SOURCES} ${FTP_SOURCES} ${LAMBDA_SOURCES} ${COGNITO_SOURCES} ${DYNAMODB_SOURCES} ${KMS_SOURCES}
        ${SECRETMANAGER_SOURCES} ${DOCKER_SOURCES} ${GATEWAY_SOURCES} ${MODULE_SOURCES})

# Test directory
add_subdirectory(tst)

# Includes
include_directories(./include ../core/include ../db/include ../dto/include ${INC_BSON_CXX} ${INC_MONGO_CXX})

add_library(${LIBRARY} SHARED ${SOURCES})
add_library(${LIBRARY_STATIC} STATIC ${SOURCES})
set_target_properties(${LIBRARY_STATIC} PROPERTIES OUTPUT_NAME ${LIBRARY})

install(TARGETS ${LIBRARY} DESTINATION lib)
