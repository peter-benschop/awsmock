set(BINARY dto_tst)
set(STATIC_LIB awsmockdto)

#set(SQS_SOURCES SQSServiceTests.cpp SQSServerJavaTests.cpp SQSServerCliTest.cpp)
#set(SNS_SOURCES SNSServiceTests.cpp SNSServerJavaTests.cpp SNSServerCliTest.cpp)
#set(S3_SOURCES S3ServiceTests.cpp S3ServerJavaTests.cpp S3ServerCliTest.cpp)
#set(LAMBDA_SOURCES LambdaServiceTests.cpp LambdaServerCliTest.cpp)
#set(DOCKER_SOURCES DockerServiceTests.cpp)
#set(COGNITO_SOURCES CognitoServiceTests.cpp CognitoServerCliTest.cpp CognitoServerJavaTests.cpp)
set(TRANSFER_SOURCES CreateServerRequestTest.cpp CreateServerResponseTest.cpp)
set(MAIN_SOURCES main.cpp)

# Includes
include_directories(../include ../../core/include ../../db/include /usr/include/bsoncxx/v_noabi /usr/include/mongocxx/v_noabi)
link_directories(/usr/lib /usr/lib/x86_64-linux-gnu /usr/local/lib ../../core ../../db ../../dto)

add_executable(${BINARY} ${TRANSFER_SOURCES} ${MAIN_SOURCES})
target_link_libraries(${BINARY} PUBLIC ${STATIC_LIB} awsmockcore awsmockdto awsmockdb mongocxx bsoncxx PocoUtil
        PocoFoundation PocoNetSSL PocoNet PocoJSON PocoXML PocoZip PocoPrometheus gtest pthread ssl crypto z archive
        curl tbb)

add_test(NAME ${BINARY} COMMAND ${BINARY} WORKING_DIRECTORY ${CMAKE_CURRENT_SRC_DIR})
