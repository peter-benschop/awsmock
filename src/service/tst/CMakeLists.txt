set(BINARY srv_tst)
set(STATIC_LIB awsmocksrv)

set(SOURCES SQSServiceTests.cpp SQSServerJavaTests.cpp SQSServerCliTest.cpp SNSServiceTests.cpp S3ServiceTests.cpp
        S3ServerXmlTests.cpp S3ServerJsonTests.cpp DockerServiceTests.cpp main.cpp)

# Includes
include_directories(../include ../../core/include ../../db/include ../../dto/include /usr/include
        /usr/include/bsoncxx/v_noabi /usr/include/mongocxx/v_noabi)
link_directories(/usr/lib /usr/lib/x86_64-linux-gnu /usr/local/lib ../../core ../../db ../../dto)

add_executable(${BINARY} ${SOURCES})
target_link_libraries(${BINARY} PUBLIC ${STATIC_LIB} awsmockcore awsmockdto awsmockdb mongocxx bsoncxx PocoUtil
        PocoFoundation PocoNetSSL PocoNet PocoJSON PocoXML PocoZip PocoPrometheus gtest pthread ssl crypto z archive
        curl tbb)

add_test(NAME ${BINARY} COMMAND ${BINARY})
