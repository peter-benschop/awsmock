set(BINARY srv_tst)
set(STATIC_LIB awsmocksrv)

# Includes
include_directories(../include ../../core/include ../../db/include ../../dto/include /usr/include)
link_directories(/usr/lib /usr/lib/x86_64-linux-gnu /usr/local/lib ../ ../../core ../ ../../db ../ ../../dto)

add_executable(${BINARY} SQSServiceTests.cpp S3ServiceTests.cpp main.cpp)
target_link_libraries(${BINARY} PUBLIC ${STATIC_LIB} awsmockcore awsmockdb PocoUtil PocoFoundation PocoNetSSL
        PocoNet PocoJSON PocoXML PocoData PocoDataSQLite PocoZip PocoPrometheus gtest ${CMAKE_DL_LIBS} pthread ssl
        crypto z archive)

add_test(NAME ${BINARY} COMMAND ${BINARY})