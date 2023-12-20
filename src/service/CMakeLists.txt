
set(LIBRARY awsmocksrv)
set(LIBRARY_STATIC awsmocksrv_static)

set(S3_SOURCES src/s3/S3Server.cpp src/s3/S3Handler.cpp src/s3/S3CliHandler.cpp src/s3/S3CppHandler.cpp
        src/s3/S3Java2Handler.cpp src/s3/S3Service.cpp src/s3/S3Monitoring.cpp)
set(SQS_SOURCES src/sqs/SQSServer.cpp src/sqs/SQSHandler.cpp src/sqs/SQSCliHandler.cpp src/sqs/SQSCppHandler.cpp
        src/sqs/SQSJava2Handler.cpp src/sqs/SQSService.cpp src/sqs/SQSMonitoring.cpp)
set(SNS_SOURCES src/sns/SNSServer.cpp src/sns/SNSHandler.cpp src/sns/SNSCliHandler.cpp src/sns/SNSJava2Handler.cpp
        src/sns/SNSCppHandler.cpp src/sns/SNSService.cpp src/sns/SNSMonitoring.cpp)
set(LAMBDA_SOURCES src/lambda/LambdaServer.cpp src/lambda/LambdaHandler.cpp src/lambda/LambdaService.cpp
        src/lambda/LambdaMonitoring.cpp src/lambda/LambdaCreator.cpp src/lambda/LambdaExecutor.cpp)
set(COGNITO_SOURCES src/cognito/CognitoHandler.cpp src/cognito/CognitoHandler.cpp src/cognito/CognitoCliHandler.cpp
        src/cognito/CognitoJava2Handler.cpp src/cognito/CognitoService.cpp src/cognito/CognitoServer.cpp
        src/cognito/CognitoMonitoring.cpp)
set(TRANSFER_SOURCES src/transfer/TransferServer.cpp src/transfer/TransferHandler.cpp src/transfer/TransferService.cpp)
set(DYNAMODB_SOURCES src/dynamodb/DynamoDbServer.cpp src/dynamodb/DynamoDbHandler.cpp src/dynamodb/DynamoDbService.cpp)
set(FTP_SOURCES src/ftpserver/Filesystem.cpp src/ftpserver/FtpSession.cpp src/ftpserver/FtpServer.cpp
        src/ftpserver/FtpServerImpl.cpp src/ftpserver/UserDatabase.cpp)
set(GATEWAY_SOURCES src/gateway/GatewayServer.cpp src/gateway/GatewayRouter.cpp src/gateway/GatewayHandler.cpp)
set(DOCKER_SOURCES src/docker/DockerService.cpp)
set(MODULE_SOURCES src/module/ModuleService.cpp)

set(SOURCES src/common/AbstractHandler.cpp src/common/AbstractWorker.cpp src/common/AbstractServer.cpp ${S3_SOURCES}
        ${SQS_SOURCES} ${SNS_SOURCES} ${TRANSFER_SOURCES} ${FTP_SOURCES} ${LAMBDA_SOURCES} ${COGNITO_SOURCES}
        ${DYNAMODB_SOURCES} ${DOCKER_SOURCES} ${GATEWAY_SOURCES} ${MODULE_SOURCES})

# Test directory
add_subdirectory(tst)

# Includes
include_directories(include ../core/include ../db/include ../dto/include /usr/include /usr/include/bsoncxx/v_noabi
        /usr/include/mongocxx/v_noabi tbb)

add_library(${LIBRARY} SHARED ${SOURCES}
        src/gateway/GatewayRouter.cpp)
add_library(${LIBRARY_STATIC} STATIC ${SOURCES})

install(TARGETS ${LIBRARY} DESTINATION lib)
