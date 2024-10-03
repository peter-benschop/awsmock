set(BINARY dto_tst)
set(STATIC_LIB awsmockdto)
set(AWS_CRT_SDK aws-crt-cpp aws-c-event-stream aws-c-s3 aws-c-auth aws-c-mqtt aws-c-http aws-c-sdkutils aws-checksums
        aws-c-io aws-c-cal aws-c-common aws-c-compression s2n)

set(SQS_SOURCES sqs/MessageAttributeTest.cpp)
#set(SNS_SOURCES SNSServiceTests.cpp SNSServerJavaTests.cpp SNSServerCliTest.cpp)
#set(S3_SOURCES S3ServiceTests.cpp S3ServerJavaTests.cpp S3ServerCliTest.cpp)
#set(LAMBDA_SOURCES LambdaServiceTests.cpp LambdaServerCliTest.cpp)
#set(DOCKER_SOURCES DockerServiceTests.cpp)
#set(COGNITO_SOURCES CognitoServiceTests.cpp CognitoServerCliTest.cpp CognitoServerJavaTests.cpp)
set(TRANSFER_SOURCES transfer/CreateServerRequestTest.cpp transfer/CreateServerResponseTest.cpp
        transfer/CreateUserRequestTest.cpp transfer/CreateServerResponseTest.cpp)
set(MAIN_SOURCES main.cpp)

# Includes

include_directories(../include ../../core/include ../../db/include ${INC_BSON_CXX} ${INC_MONGO_CXX} /usr/local/include)
link_directories(../../core ../../db ../../dto)


add_executable(${BINARY} ${SQS_SOURCES} ${TRANSFER_SOURCES} ${MAIN_SOURCES})
target_link_libraries(${BINARY} PUBLIC ${STATIC_LIB} awsmockcore awsmockdto awsmockdb mongocxx bsoncxx PocoPrometheus PocoUtil PocoNet PocoJSON PocoXML PocoZip
        PocoFoundation gtest pthread ssl crypto z archive tbb curl)

add_test(NAME ${BINARY} COMMAND ${BINARY} WORKING_DIRECTORY ${CMAKE_CURRENT_SRC_DIR})
