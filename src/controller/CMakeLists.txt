set(BINARY awsmockctl)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(SOURCES src/Configuration.cpp src/Controller.cpp src/main.cpp)

# Check systemd
find_library(SYSTEMD NAMES systemd HINTS /usr/lib/x86_64-linux-gnu)

include_directories(include /usr/include/bsoncxx/v_noabi /usr/include/mongocxx/v_noabi ../core/include ../dto/include
        ../db/include)
link_directories(/usr/lib /usr/lib/x86_64-linux-gnu /usr/local/lib ../core)

add_executable(${BINARY} ${SOURCES})

if(SYSTEMD)
    # systemd available
    add_definitions(-DHAS_SYSTEMD)
    target_link_libraries(${BINARY} PUBLIC awsmockcore awsmockdb awsmockdto mongocxx bsoncxx PocoPrometheus PocoNet
            PocoJSON PocoXML PocoZip PocoFoundation PocoUtil pthread crypto ssl z archive curl tbb systemd)
else()
    # systemd not available
    target_link_libraries(${BINARY} PUBLIC awsmockcore awsmockdb awsmockdto mongocxx bsoncxx PocoPrometheus PocoNet
            PocoJSON PocoXML PocoZip PocoFoundation PocoUtil pthread crypto ssl z archive curl tbb)
endif()

add_library(${BINARY}_lib STATIC ${SOURCES})

install(TARGETS ${BINARY} DESTINATION bin)
