set(BINARY srv_tst)
set(STATIC_LIB awsmocksrv)

# Includes
include_directories(../include ../../core/include ../../db/include ../../dto/include /usr/include
        /usr/include/bsoncxx/v_noabi /usr/include/mongocxx/v_noabi)
link_directories(/usr/lib /usr/lib/x86_64-linux-gnu /usr/local/lib ../ ../../core ../ ../../db ../ ../../dto)

add_executable(${BINARY} SQSServiceTests.cpp S3ServiceTests.cpp DockerServiceTests.cpp main.cpp)
target_link_libraries(${BINARY} PUBLIC ${STATIC_LIB} awsmockcore awsmockdb mongocxx bsoncxx PocoUtil PocoFoundation
        PocoNetSSL PocoNet PocoJSON PocoXML PocoZip PocoPrometheus gtest pthread ssl crypto z archive curl)

add_test(NAME ${BINARY} COMMAND ${BINARY})