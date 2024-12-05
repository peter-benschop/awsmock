set(BINARY core_tst)
set(STATIC_LIB awsmockcore)

set(SOURCES CryptoTests.cpp FileUtilsTests.cpp DirUtilsTests.cpp StringUtilsTests.cpp ConfigurationTests.cpp RandomUtilsTests.cpp AwsUtilsTests.cpp JsonUtilsTests.cpp
        HttpUtilsTests.cpp SystemUtilsTests.cpp XmlUtilsTests.cpp JwtUtilsTests.cpp main.cpp)

add_executable(${BINARY} ${SOURCES})
target_include_directories(${BINARY} PRIVATE ../include /usr/local/include ${INC_BSON_CXX} ${INC_MONGO_CXX})
target_link_libraries(${BINARY} PUBLIC ${STATIC_LIB} ${LIB_BSON_CXX} ${LIB_MONGO_CXX} PocoUtil PocoFoundation PocoNet PocoJSON PocoXML PocoZip PocoPrometheus
        boost_locale boost_filesystem yaml-cpp gtest pthread ssl crypto z archive)

add_test(NAME ${BINARY} COMMAND ${BINARY})

