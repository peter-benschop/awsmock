
set(LIBRARY awsmocksrv)
set(LIBRARY_STATIC awsmocksrv_static)

set(S3_SOURCES src/s3/S3Server.cpp src/s3/S3Handler.cpp src/s3/S3Service.cpp src/s3/S3Monitoring.cpp)
set(SQS_SOURCES src/sqs/SQSServer.cpp src/sqs/SQSHandler.cpp src/sqs/SQSService.cpp src/sqs/SQSMonitoring.cpp)
set(SNS_SOURCES src/sns/SNSServer.cpp src/sns/SNSHandler.cpp src/sns/SNSService.cpp src/sns/SNSMonitoring.cpp)
set(LAMBDA_SOURCES src/lambda/LambdaServer.cpp src/lambda/LambdaHandler.cpp src/lambda/LambdaService.cpp src/lambda/LambdaMonitoring.cpp
        src/lambda/LambdaCreator.cpp src/lambda/LambdaExecutor.cpp)
set(TRANSFER_SOURCES src/transfer/TransferServer.cpp src/transfer/TransferHandler.cpp src/transfer/TransferService.cpp)
set(FTP_SOURCES src/ftpserver/Filesystem.cpp src/ftpserver/FtpSession.cpp src/ftpserver/FtpServer.cpp
        src/ftpserver/FtpServerImpl.cpp src/ftpserver/UserDatabase.cpp)
set(DOCKER_SOURCES src/docker/DockerService.cpp)

set(SOURCES src/common/AbstractHandler.cpp src/common/AbstractWorker.cpp src/common/AbstractServer.cpp ${S3_SOURCES} ${SQS_SOURCES} ${SNS_SOURCES} ${TRANSFER_SOURCES}
        ${FTP_SOURCES} ${LAMBDA_SOURCES} ${DOCKER_SOURCES})

# Test directory
add_subdirectory(tst)

# Includes
include_directories(include ../core/include ../db/include ../dto/include /usr/include /usr/include/bsoncxx/v_noabi
        /usr/include/mongocxx/v_noabi tbb)

add_library(${LIBRARY} SHARED ${SOURCES})
add_library(${LIBRARY_STATIC} STATIC ${SOURCES})

install(TARGETS ${LIBRARY} DESTINATION lib)
