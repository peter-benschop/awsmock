set(BINARY db_tst)
set(STATIC_LIB awsmockdb)
set(AWS_CRT_SDK aws-crt-cpp aws-c-event-stream aws-c-s3 aws-c-auth aws-c-mqtt aws-c-http aws-c-sdkutils aws-checksums
        aws-c-io aws-c-cal aws-c-common aws-c-compression s2n)

set(SQS_SOURCES SQSDatabaseTests.cpp SQSMemoryDbTests.cpp)
set(SNS_SOURCES SNSDatabaseTests.cpp SNSMemoryDbTests.cpp)
set(S3_SOURCES S3DatabaseTests.cpp S3MemoryDbTests.cpp)
set(MODULE_SOURCES ModuleDatabaseTests.cpp ModuleMemoryDbTests.cpp)
set(LAMBDA_SOURCES LambdaDatabaseTests.cpp LambdaMemoryDbTests.cpp)
set(COGNITO_SOURCES CognitoDatabaseTests.cpp CognitoMemoryDbTests.cpp)
set(SECRETSMANAGER_SOURCES SecretsManagerDatabaseTests.cpp)
set(TRANSFER_SOURCES TransferDatabaseTest.cpp TransferMemoryDbTest.cpp)

# Includes
include_directories(../include ../../core/include ${INC_BSON_CXX} ${INC_MONGO_CXX} /usr/local/include)
link_directories(../ ../../core)

add_executable(${BINARY} DatabaseTests.cpp ${SQS_SOURCES} ${S3_SOURCES} ${SNS_SOURCES} ${MODULE_SOURCES}
        ${LAMBDA_SOURCES} ${TRANSFER_SOURCES} ${COGNITO_SOURCES} ${SECRETSMANAGER_SOURCES} main.cpp)

target_link_libraries(${BINARY} PUBLIC ${STATIC_LIB} awsmockcore ${LIB_BSON_CXX} ${LIB_MONGO_CXX} PocoPrometheus PocoUtil
        PocoFoundation PocoNet PocoJSON PocoZip gtest pthread ssl crypto z archive tbb)

add_test(NAME ${BINARY} COMMAND ${BINARY})
