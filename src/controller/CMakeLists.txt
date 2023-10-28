set(BINARY awsmockctl)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(SOURCES src/Configuration.cpp src/Controller.cpp src/main.cpp)

include_directories(include /usr/include/bsoncxx/v_noabi /usr/include/mongocxx/v_noabi ../core/include ../dto/include
        ../db/include)
link_directories(/usr/lib /usr/lib/x86_64-linux-gnu /usr/local/lib ../core)

add_executable(${BINARY} ${SOURCES})

target_link_libraries(${BINARY} PUBLIC awsmockcore awsmockdb awsmockdto mongocxx bsoncxx PocoPrometheus PocoNet PocoJSON
        PocoXML PocoZip PocoFoundation PocoUtil pthread crypto ssl z archive curl tbb systemd)
add_library(${BINARY}_lib STATIC ${SOURCES})

install(TARGETS ${BINARY} DESTINATION bin)
