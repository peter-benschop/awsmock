set(BINARY awsmockmgr)

set(SOURCES src/resource/HandlerException.cpp src/resource/AbstractResource.cpp src/resource/factory/Factory.cpp
        src/resource/factory/ModuleFactory.cpp src/resource/handler/ModuleHandler.cpp src/controller/ResourceNotFound.cpp
        src/controller/Router.cpp src/controller/RestService.cpp src/main.cpp)

include_directories(./include ../core/include ../db/include ../dto/include ../service/include
        /usr/include/bsoncxx/v_noabi /usr/include/mongocxx/v_noabi)
link_directories(../core ../dto ../db ../service)

# External includes
include_directories(/usr/include)

add_executable(${BINARY} ${SOURCES})

target_link_libraries(${BINARY} PUBLIC awsmockcore awsmockdto awsmockdb awsmocksrv mongocxx bsoncxx
        PocoPrometheus PocoNet PocoJSON PocoXML PocoZip PocoFoundation PocoUtil pthread crypto ssl z archive
        curl tbb)
add_library(${BINARY}_lib STATIC ${SOURCES})

install(TARGETS ${BINARY} DESTINATION bin)
