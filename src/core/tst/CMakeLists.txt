set(BINARY core_tst)
set(STATIC_LIB awsmockcore)

# Includes
include_directories()
include_directories(../include /usr/include)
link_directories(../)

set(SOURCES CryptoTests.cpp FileUtilsTests.cpp DirUtilsTests.cpp StringUtilsTests.cpp ConfigurationTests.cpp
        RandomUtilsTests.cpp AwsUtilsTests.cpp JsonUtilsTests.cpp HttpUtilsTests.cpp SystemUtilsTests.cpp
        XmlUtilsTests.cpp main.cpp)

add_executable(${BINARY} ${SOURCES})
target_link_libraries(${BINARY} PUBLIC ${STATIC_LIB} PocoUtil PocoFoundation PocoNet PocoJSON PocoXML PocoZip
        prometheus-cpp-core prometheus-cpp-pull gtest pthread ssl crypto z archive tbb)

add_test(NAME ${BINARY} COMMAND ${BINARY})

