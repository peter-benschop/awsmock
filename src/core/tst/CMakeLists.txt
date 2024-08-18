set(BINARY core_tst)
set(STATIC_LIB awsmockcore)

# Includes
include_directories(../include /usr/local/include)
link_directories(../ /usr/local/lib)

set(SOURCES CryptoTests.cpp FileUtilsTests.cpp DirUtilsTests.cpp StringUtilsTests.cpp ConfigurationTests.cpp RandomUtilsTests.cpp AwsUtilsTests.cpp JsonUtilsTests.cpp
        HttpUtilsTests.cpp SystemUtilsTests.cpp XmlUtilsTests.cpp JwtUtilsTests.cpp main.cpp)

add_executable(${BINARY} ${SOURCES})
target_link_libraries(${BINARY} PUBLIC ${STATIC_LIB} PocoUtil PocoFoundation PocoNet PocoJSON PocoXML PocoZip PocoPrometheus PocoCrypto boost_locale gtest
        pthread ssl crypto z archive tbb)

add_test(NAME ${BINARY} COMMAND ${BINARY})

