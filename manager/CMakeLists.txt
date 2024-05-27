cmake_minimum_required(VERSION 3.22)
project(awsmockmgr)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(BINARY awsmockmgr)

# Sources
set(SOURCES src/resource/HandlerException.cpp src/resource/AbstractResource.cpp src/resource/factory/Factory.cpp
        src/resource/factory/ModuleFactory.cpp src/resource/handler/ModuleHandler.cpp src/controller/ResourceNotFound.cpp
        src/controller/Router.cpp src/controller/RestService.cpp src/main.cpp)

# External includes
include_directories(./include ../src/core/include ../src/db/include ../src/dto/include ../src/service/include
        ${INC_BSON_CXX} ${INC_MONGO_CXX})

add_executable(${BINARY} ${SOURCES})
add_library(${BINARY}_lib STATIC ${SOURCES})

target_link_libraries(${BINARY} PUBLIC awsmockcore awsmockdto awsmockdb awsmocksrv mongocxx bsoncxx PocoPrometheus
        PocoNet PocoJSON PocoXML PocoZip PocoFoundation PocoUtil pthread crypto ssl z archive curl tbb)

install(TARGETS ${BINARY} DESTINATION bin)
