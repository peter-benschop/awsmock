set(BINARY db_tst)
set(STATIC_LIB awsmockdb)

# Includes
include_directories(../include ../../core/include /usr/include)
link_directories(/usr/lib /usr/lib/x86_64-linux-gnu /usr/local/lib ../ ../../core)

add_executable(${BINARY} DatabaseTests.cpp S3DatabaseTests.cpp SQSDatabaseTests.cpp main.cpp)
target_link_libraries(${BINARY} PUBLIC ${STATIC_LIB} awsmockcore PocoUtil PocoFoundation PocoNetSSL PocoNet PocoJSON
        PocoData PocoDataSQLite PocoZip PocoPrometheus gtest ${CMAKE_DL_LIBS} pthread ssl crypto z)

add_test(NAME ${BINARY} COMMAND ${BINARY})