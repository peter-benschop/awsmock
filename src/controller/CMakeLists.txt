set(BINARY awsmockctl)
set(AWS_CRT_SDK aws-crt-cpp aws-c-event-stream aws-c-s3 aws-c-auth aws-c-mqtt aws-c-http aws-c-sdkutils aws-checksums
        aws-c-io aws-c-cal aws-c-common aws-c-compression s2n)

set(SOURCES src/Controller.cpp src/main.cpp)

include_directories(include ../core/include ../dto/include ../db/include ${INC_BSON_CXX} ${INC_MONGO_CXX} /usr/local/include)
link_directories(../core)

add_executable(${BINARY} ${SOURCES})

# Check systemd
find_library(SYSTEMD NAMES systemd HINTS /usr/lib/x86_64-linux-gnu)
if (SYSTEMD)
    # systemd available
    add_definitions(-DHAS_SYSTEMD)
    target_link_libraries(${BINARY} PUBLIC awsmockcore awsmockdto awsmockdb mongocxx bsoncxx boost_program_options boost_thread boost_filesystem boost_url yaml-cpp
            pthread crypto ssl z archive systemd)
else ()
    # systemd not available
    target_link_libraries(${BINARY} PUBLIC awsmockcore awsmockdto awsmockdb mongocxx bsoncxx boost_program_options boost_filesystem boost_thread boost_url yaml-cpp
            pthread crypto ssl z archive)
endif ()

add_library(${BINARY}_lib STATIC ${SOURCES})

install(TARGETS ${BINARY} DESTINATION bin)
