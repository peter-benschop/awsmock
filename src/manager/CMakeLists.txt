set(BINARY awsmockmgr)

set(SOURCES src/server/Manager.cpp src/server/Monitoring.cpp src/main.cpp)

# External includes
include_directories(./include ../core/include ../db/include ../dto/include ../service/include ${INC_BSON_CXX} ${INC_MONGO_CXX} /usr/local/include)
link_directories(../core ../dto ../db ../service)

add_executable(${BINARY} ${SOURCES})
add_library(${BINARY}_lib STATIC ${SOURCES})

target_link_libraries(${BINARY} PUBLIC awsmocksrv awsmockdto awsmockdb awsmockcore mongocxx bsoncxx PocoPrometheus PocoNet PocoJSON PocoXML PocoZip PocoFoundation
        PocoUtil boost_program_options boost_filesystem boost_thread pthread crypto ssl z archive tbb curl yaml-cpp)

install(TARGETS ${BINARY} DESTINATION bin)
