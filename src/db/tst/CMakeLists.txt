set(BINARY db_tst)
set(STATIC_LIB awsmockdb)

set(SQS_SOURCES SQSDatabaseTests.cpp SQSMemoryDbTests.cpp)

# Includes
include_directories(../include ../../core/include /usr/include /usr/include/bsoncxx/v_noabi /usr/include/mongocxx/v_noabi)
link_directories(/usr/lib /usr/lib/x86_64-linux-gnu /usr/local/lib ../ ../../core)

add_executable(${BINARY} DatabaseTests.cpp ${SQS_SOURCES} S3DatabaseTests.cpp  SNSDatabaseTests.cpp
        LambdaDatabaseTests.cpp TransferDatabaseTest.cpp ModuleDatabaseTests.cpp main.cpp)
target_link_libraries(${BINARY} PUBLIC ${STATIC_LIB} awsmockcore mongocxx bsoncxx PocoUtil PocoFoundation PocoNetSSL
        PocoNet PocoJSON PocoZip PocoPrometheus gtest ${CMAKE_DL_LIBS} pthread ssl crypto z archive curl tbb)

add_test(NAME ${BINARY} COMMAND ${BINARY})