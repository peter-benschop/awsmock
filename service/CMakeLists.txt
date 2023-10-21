
set(LIBRARY awsmocksrv)
set(LIBRARY_STATIC awsmocksrv_static)

set(S3_SOURCES src/S3Server.cpp src/S3Handler.cpp src/S3Service.cpp src/S3Monitoring.cpp)
set(SQS_SOURCES src/SQSServer.cpp src/SQSHandler.cpp src/SQSService.cpp src/SQSMonitoring.cpp)
set(SNS_SOURCES src/SNSServer.cpp src/SNSHandler.cpp src/SNSService.cpp src/SNSMonitoring.cpp)
set(LAMBDA_SOURCES src/LambdaServer.cpp src/LambdaHandler.cpp src/LambdaService.cpp src/LambdaMonitoring.cpp
        src/LambdaCreator.cpp src/LambdaExecutor.cpp)
set(TRANSFER_SOURCES src/TransferServer.cpp src/TransferHandler.cpp src/TransferService.cpp)
set(FTP_SOURCES src/ftpserver/Filesystem.cpp src/ftpserver/FtpSession.cpp src/ftpserver/FtpServer.cpp
        src/ftpserver/FtpServerImpl.cpp src/ftpserver/UserDatabase.cpp)
set(DOCKER_SOURCES src/DockerService.cpp)

set(SOURCES src/AbstractHandler.cpp src/AbstractWorker.cpp ${S3_SOURCES} ${SQS_SOURCES} ${SNS_SOURCES} ${TRANSFER_SOURCES}
        ${FTP_SOURCES} ${LAMBDA_SOURCES} ${DOCKER_SOURCES})

# Test directory
add_subdirectory(tst)

# Includes
include_directories(include ../core/include ../db/include ../dto/include /usr/include /usr/include/bsoncxx/v_noabi
        /usr/include/mongocxx/v_noabi tbb)

add_library(${LIBRARY} SHARED ${SOURCES})
add_library(${LIBRARY_STATIC} STATIC ${SOURCES})

install(TARGETS ${LIBRARY} DESTINATION lib)
