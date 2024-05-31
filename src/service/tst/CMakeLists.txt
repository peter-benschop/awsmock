set(BINARY srv_tst)
set(STATIC_LIB awsmocksrv)
set(AWS_CRT_SDK aws-crt-cpp aws-c-event-stream aws-c-s3 aws-c-auth aws-c-mqtt aws-c-http aws-c-sdkutils aws-checksums
        aws-c-io aws-c-cal aws-c-common aws-c-compression s2n)

set(SQS_SOURCES SQSServiceTests.cpp SQSServerJavaTests.cpp SQSServerCliTest.cpp SQSServerSpringTests.cpp)
set(SNS_SOURCES SNSServiceTests.cpp SNSServerJavaTests.cpp SNSServerCliTest.cpp)
set(S3_SOURCES S3ServiceTests.cpp S3ServerJavaTests.cpp S3ServerCliTest.cpp)
set(LAMBDA_SOURCES LambdaServiceTests.cpp LambdaServerCliTest.cpp)
set(DOCKER_SOURCES DockerServiceTests.cpp)
set(COGNITO_SOURCES CognitoServiceTests.cpp CognitoServerCliTest.cpp CognitoServerJavaTests.cpp)
set(DYNAMODB_SOURCES DynamodbServerJavaTests.cpp DynamoDbServerCliTest.cpp)
set(MAIN_SOURCES main.cpp ModuleServiceTests.cpp)

# Includes
include_directories(../include ../../core/include ../../db/include ../../dto/include ${INC_BSON_CXX} ${INC_MONGO_CXX})
link_directories(../../core ../../db ../../dto ${LIB_BSON_CXX} ${LIB_MONGO_CXX})

add_executable(${BINARY} ${SQS_SOURCES} ${SNS_SOURCES} ${S3_SOURCES} ${DOCKER_SOURCES} ${LAMBDA_SOURCES}
        ${COGNITO_SOURCES} ${DYNAMODB_SOURCES} ${MAIN_SOURCES})
target_link_libraries(${BINARY} PUBLIC ${STATIC_LIB} awsmockcore awsmockdto awsmockdb mongocxx bsoncxx PocoPrometheus
        PocoUtil PocoFoundation PocoNet PocoJSON PocoXML PocoZip gtest pthread ssl crypto z archive tbb)

add_test(NAME ${BINARY} COMMAND ${BINARY} WORKING_DIRECTORY ${CMAKE_CURRENT_SRC_DIR})
