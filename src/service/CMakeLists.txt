
set(LIBRARY awsmocksrv)
set(LIBRARY_STATIC awsmocksrv_static)

set(S3_SOURCES src/s3/S3Server.cpp src/s3/S3Handler.cpp src/s3/S3CmdHandler.cpp src/s3/S3Service.cpp
        src/s3/S3Monitoring.cpp)
set(SQS_SOURCES src/sqs/SQSServer.cpp src/sqs/SQSHandler.cpp src/sqs/SQSCmdHandler.cpp src/sqs/SQSService.cpp
        src/sqs/SQSMonitoring.cpp src/sqs/SQSWorker.cpp)
set(SNS_SOURCES src/sns/SNSServer.cpp src/sns/SNSHandler.cpp src/sns/SNSCmdHandler.cpp src/sns/SNSWorker.cpp
        src/sns/SNSService.cpp src/sns/SNSMonitoring.cpp)
set(LAMBDA_SOURCES src/lambda/LambdaServer.cpp src/lambda/LambdaHandler.cpp src/lambda/LambdaService.cpp
        src/lambda/LambdaCreator.cpp src/lambda/LambdaExecutor.cpp src/lambda/LambdaMonitoring.cpp)
set(COGNITO_SOURCES src/cognito/CognitoHandler.cpp src/cognito/CognitoHandler.cpp
        src/cognito/CognitoService.cpp src/cognito/CognitoServer.cpp
        src/cognito/CognitoMonitoring.cpp src/cognito/CognitoCmdHandler.cpp)
set(TRANSFER_SOURCES src/transfer/TransferServer.cpp src/transfer/TransferHandler.cpp src/transfer/TransferService.cpp
        src/transfer/TransferMonitoring.cpp)
set(DYNAMODB_SOURCES src/dynamodb/DynamoDbServer.cpp src/dynamodb/DynamoDbHandler.cpp src/dynamodb/DynamoDbService.cpp
        src/dynamodb/DynamoDbCmdHandler.cpp src/dynamodb/DynamoDbMonitoring.cpp src/dynamodb/DynamoDbWorker.cpp)
set(SECRETMANAGER_SOURCES src/secretsmanager/SecretsManagerServer.cpp src/secretsmanager/SecretsManagerHandler.cpp
        src/secretsmanager/SecretsManagerCmdHandler.cpp src/secretsmanager/SecretsManagerService.cpp
        src/secretsmanager/SecretsManagerMonitoring.cpp)
set(KMS_SOURCES src/kms/KMSServer.cpp src/kms/KMSHandler.cpp src/kms/KMSCmdHandler.cpp src/kms/KMSWorker.cpp
        src/kms/KMSService.cpp src/kms/KMSMonitoring.cpp src/kms/KMSCreator.cpp)
set(FTP_SOURCES src/ftpserver/Filesystem.cpp src/ftpserver/FtpSession.cpp src/ftpserver/FtpServer.cpp
        src/ftpserver/FtpServerImpl.cpp src/ftpserver/UserDatabase.cpp)
set(GATEWAY_SOURCES src/gateway/GatewayServer.cpp src/gateway/GatewayRouter.cpp src/gateway/GatewayHandler.cpp)
set(DOCKER_SOURCES src/docker/DockerService.cpp)
set(MODULE_SOURCES src/common/ModuleService.cpp)

set(SOURCES src/common/AbstractHandler.cpp src/common/AbstractServer.cpp ${S3_SOURCES}
        ${SQS_SOURCES} ${SNS_SOURCES} ${TRANSFER_SOURCES} ${FTP_SOURCES} ${LAMBDA_SOURCES} ${COGNITO_SOURCES}
        ${DYNAMODB_SOURCES} ${SECRETMANAGER_SOURCES} ${KMS_SOURCES} ${DOCKER_SOURCES} ${GATEWAY_SOURCES} ${MODULE_SOURCES})

# Test directory
if (NOT WIN32)
    add_subdirectory(tst)
endif ()

# Includes
if (WIN32)
    include_directories(./include ../core/include ../db/include ../dto/include ${AWSMOCK_WIN32_DIR}/include)
    link_directories(${AWSMOCK_WIN32_DIR}/lib ../core/${CMAKE_BUILD_TYPE} ../db/${CMAKE_BUILD_TYPE} ../dto/${CMAKE_BUILD_TYPE})
else ()
    include_directories(include ../core/include ../db/include ../dto/include)
    include_directories(/usr/include /usr/include/mongo /usr/include/bsoncxx/v_noabi /usr/include/mongocxx/v_noabi)
endif ()

add_library(${LIBRARY} SHARED ${SOURCES}
        include/awsmock/service/s3/S3HashCreator.h
        src/s3/S3HashCreator.cpp
)
add_library(${LIBRARY_STATIC} STATIC ${SOURCES})
set_target_properties(${LIBRARY_STATIC} PROPERTIES OUTPUT_NAME ${LIBRARY})

if (WIN32)
    target_link_libraries(${LIBRARY} awsmockcore.lib awsmockdb.lib awsmockdto.lib libssl.lib libcrypto.lib
            libcurl_imp.lib archive.lib bson-1.0.lib bsoncxx-v_noabi-rhb-x64-v143-md.lib
            mongocxx-v_noabi-rhb-x64-v143-md.lib)
endif ()

install(TARGETS ${LIBRARY} DESTINATION lib)
