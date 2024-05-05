set(BINARY core_tst)
set(STATIC_LIB awsmockcore)

# Includes
include_directories()
if (WIN32)
    include_directories(../include ${AWSMOCK_WIN32_DIR}/poco/include ${AWSMOCK_WIN32_DIR}/gnuwin32/include)
    include_directories(${AWSMOCK_WIN32_DIR}/plog/include ${AWSMOCK_WIN32_DIR}/openssl/include)
    include_directories(${AWSMOCK_WIN32_DIR}/curl/include ${AWSMOCK_WIN32_DIR}/libarchive/include)
    include_directories(${AWSMOCK_WIN32_DIR}/asio/include ${AWSMOCK_WIN32_DIR}/gtest/include)
    link_directories(${AWSMOCK_WIN32_DIR}/poco/lib ${AWSMOCK_WIN32_DIR}/gnuwin32/lib)
    link_directories(${AWSMOCK_WIN32_DIR}/libarchive/lib ${AWSMOCK_WIN32_DIR}/openssl/lib/VC/x64/MD)
    link_directories(${AWSMOCK_WIN32_DIR}/gtest/lib ${AWSMOCK_WIN32_DIR}/curl/lib)
else ()
    include_directories(../include /usr/include)
    link_directories(/usr/lib /usr/lib/x86_64-linux-gnu /usr/local/lib ../)
endif ()

set(SOURCES CryptoTests.cpp FileUtilsTests.cpp DirUtilsTests.cpp StringUtilsTests.cpp ConfigurationTests.cpp
        RandomUtilsTests.cpp AwsUtilsTests.cpp JsonUtilsTests.cpp HttpUtilsTests.cpp SystemUtilsTests.cpp
        XmlUtilsTests.cpp main.cpp)

add_executable(${BINARY} ${SOURCES})
if(WIN32)
    target_link_libraries(${BINARY} PUBLIC ${STATIC_LIB} PocoUtil PocoFoundation PocoNet PocoJSON PocoXML PocoZip
            PocoPrometheus gtest.lib libssl.lib libcrypto.lib archive libcurl_imp.lib)
else ()
    target_link_libraries(${BINARY} PUBLIC ${STATIC_LIB} PocoUtil PocoFoundation PocoNet PocoJSON PocoXML PocoZip
            PocoPrometheus gtest ${CMAKE_DL_LIBS} pthread ssl crypto z archive curl tbb)
endif ()
add_test(NAME ${BINARY} COMMAND ${BINARY})