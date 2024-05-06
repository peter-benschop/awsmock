set(BINARY dto_tst)
set(STATIC_LIB awsmockdto)

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

if(WIN32)
    include_directories(../include ../../core/include ../../db/include ${AWSMOCK_WIN32_DIR}/poco/include)
    include_directories(${AWSMOCK_WIN32_DIR}/gnuwin32/include)
    include_directories(${AWSMOCK_WIN32_DIR}/plog/include ${AWSMOCK_WIN32_DIR}/openssl/include)
    include_directories(${AWSMOCK_WIN32_DIR}/curl/include ${AWSMOCK_WIN32_DIR}/boost)
    include_directories(${AWSMOCK_WIN32_DIR}/asio/include ${AWSMOCK_WIN32_DIR}/gtest/include)
    include_directories(${AWSMOCK_WIN32_DIR}/mongo-cxx-driver/include/bsoncxx/v_noabi)
    include_directories(${AWSMOCK_WIN32_DIR}/mongo-cxx-driver/include/mongocxx/v_noabi)
    link_directories(../core/Debug ../db/Debug ${AWSMOCK_WIN32_DIR}/poco/lib ${AWSMOCK_WIN32_DIR}/gnuwin32/lib)
    link_directories(${AWSMOCK_WIN32_DIR}/libarchive/lib ${AWSMOCK_WIN32_DIR}/openssl/lib/VC/x64/MD)
    link_directories(${AWSMOCK_WIN32_DIR}/mongo-cxx-driver/lib ${AWSMOCK_WIN32_DIR}/curl/lib)
else()
    include_directories(../include ../../core/include ../../db/include /usr/include/bsoncxx/v_noabi /usr/include/mongocxx/v_noabi)
    link_directories(/usr/lib /usr/lib/x86_64-linux-gnu /usr/local/lib ../../core ../../db ../../dto)
endif ()


add_executable(${BINARY} ${SQS_SOURCES} ${TRANSFER_SOURCES} ${MAIN_SOURCES})
if(WIN32)
    target_link_libraries(${BINARY} PUBLIC ${STATIC_LIB} awsmockcore awsmockdto awsmockdb mongocxx bsoncxx PocoUtil
            PocoNet PocoJSON PocoXML PocoZip PocoPrometheus PocoFoundation gtest ssl crypto z archive curl)
else ()
target_link_libraries(${BINARY} PUBLIC ${STATIC_LIB} awsmockcore awsmockdto awsmockdb mongocxx bsoncxx PocoUtil
        PocoNet PocoJSON PocoXML PocoZip PocoPrometheus PocoFoundation gtest pthread ssl crypto z archive
        curl tbb)
endif ()

add_test(NAME ${BINARY} COMMAND ${BINARY} WORKING_DIRECTORY ${CMAKE_CURRENT_SRC_DIR})
