set(BINARY core_tst)
set(STATIC_LIB awsmockcore)

# Includes
include_directories(../include /usr/include)
link_directories(/usr/lib /usr/lib/x86_64-linux-gnu /usr/local/lib ../)

add_executable(${BINARY} CryptoTests.cpp FileUtilsTests.cpp DirUtilsTests.cpp StringUtilsTests.cpp ConfigurationTests.cpp
        DirectoryWatcherTests.cpp RandomUtilsTests.cpp AwsUtilsTests.cpp JsonUtilsTests.cpp main.cpp)
target_link_libraries(${BINARY} PUBLIC ${STATIC_LIB} PocoData PocoUtil PocoFoundation PocoNetSSL PocoNet
        PocoJSON PocoZip PocoPrometheus gtest ${CMAKE_DL_LIBS} pthread ssl crypto z archive curl)

add_test(NAME ${BINARY} COMMAND ${BINARY})