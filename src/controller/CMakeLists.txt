set(BINARY awsmockctl)
set(AWS_CRT_SDK aws-crt-cpp aws-c-event-stream aws-c-s3 aws-c-auth aws-c-mqtt aws-c-http aws-c-sdkutils aws-checksums
        aws-c-io aws-c-cal aws-c-common aws-c-compression s2n)

set(SOURCES src/Configuration.cpp src/Controller.cpp src/main.cpp)

include_directories(include ../core/include ../dto/include ../db/include /usr/include /usr/include/mongo)
include_directories(/usr/include/bsoncxx/v_noabi /usr/include/mongocxx/v_noabi)
link_directories(/usr/lib /usr/lib/x86_64-linux-gnu /usr/local/lib ../core)

add_executable(${BINARY} ${SOURCES})

# Check systemd
find_library(SYSTEMD NAMES systemd HINTS /usr/lib/x86_64-linux-gnu)
if (SYSTEMD)
    # systemd available
    add_definitions(-DHAS_SYSTEMD)
    target_link_libraries(${BINARY} PUBLIC awsmockcore awsmockdto awsmockdb mongocxx bsoncxx PocoPrometheus PocoNet
            PocoJSON PocoXML PocoZip PocoFoundation PocoUtil pthread crypto ssl z archive curl tbb systemd)
else ()
    # systemd not available
    target_link_libraries(${BINARY} PUBLIC awsmockcore awsmockdto awsmockdb mongocxx bsoncxx PocoPrometheus PocoNet
            PocoJSON PocoXML PocoZip PocoFoundation PocoUtil pthread crypto ssl z archive curl tbb)
endif ()

add_library(${BINARY}_lib STATIC ${SOURCES})

install(TARGETS ${BINARY} DESTINATION bin)
