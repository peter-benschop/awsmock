set(BINARY core_tst)
set(STATIC_LIB awsmockcore)
set(AWS_CRT_SDK aws-crt-cpp aws-c-event-stream aws-c-s3 aws-c-auth aws-c-mqtt aws-c-http aws-c-sdkutils aws-checksums
        aws-c-io aws-c-cal aws-c-common aws-c-compression s2n)

# Includes
include_directories()
if (WIN32)
    include_directories(./include ${AWSMOCK_WIN32_DIR}/include)
    link_directories(${AWSMOCK_WIN32_DIR}/lib)
else ()
    include_directories(../include /usr/include)
    link_directories(/usr/lib /usr/lib/x86_64-linux-gnu /usr/local/lib ../)
endif ()

set(SOURCES CryptoTests.cpp FileUtilsTests.cpp DirUtilsTests.cpp StringUtilsTests.cpp ConfigurationTests.cpp
        RandomUtilsTests.cpp AwsUtilsTests.cpp JsonUtilsTests.cpp HttpUtilsTests.cpp SystemUtilsTests.cpp
        XmlUtilsTests.cpp main.cpp)

add_executable(${BINARY} ${SOURCES})

if (WIN32)
    target_link_libraries(${BINARY} PUBLIC PocoUtil PocoFoundation PocoNet PocoJSON PocoXML PocoZip
            PocoPrometheus gtest.lib libssl.lib libcrypto.lib archive libcurl_imp.lib)
else ()
    target_link_libraries(${BINARY} PUBLIC ${STATIC_LIB} PocoUtil PocoFoundation PocoNet PocoJSON PocoXML PocoZip
            PocoPrometheus gtest pthread ssl crypto z archive curl tbb)

endif ()

add_test(NAME ${BINARY} COMMAND ${BINARY})

