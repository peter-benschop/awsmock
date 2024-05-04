set(BINARY awsmockmgr)

set(SOURCES src/resource/HandlerException.cpp src/resource/AbstractResource.cpp src/resource/factory/Factory.cpp
        src/resource/factory/ModuleFactory.cpp src/resource/handler/ModuleHandler.cpp src/controller/ResourceNotFound.cpp
        src/controller/Router.cpp src/controller/RestService.cpp src/main.cpp)

include_directories(./include ../core/include ../db/include ../dto/include ../service/include
        /usr/include/bsoncxx/v_noabi /usr/include/mongocxx/v_noabi)
link_directories(../core ../dto ../db ../service)

# External includes
if(WIN32)
    include_directories(.\\include ..\\core\\include "C:\\Program Files (x86)\\Poco\\include" "C:\\Program Files (x86)\\GnuWin32\\include")
    include_directories("C:\\Program Files (x86)\\plog\\include" "C:\\Program Files\\OpenSSL-Win64\\include")
    include_directories("C:\\Program Files (x86)\\curl\\include" "D:\\work\\boost_1_82_0")
    include_directories("C:\\Program Files (x86)\\mongo-cxx-driver\\include\\bsoncxx\\v_noabi")
    include_directories("C:\\Program Files (x86)\\mongo-cxx-driver\\include\\mongocxx\\v_noabi")
else()
    include_directories(include ../core/include /usr/include /usr/include/mongo /usr/include/bsoncxx/v_noabi /usr/include/mongocxx/v_noabi)
endif ()

add_executable(${BINARY} ${SOURCES})

target_link_libraries(${BINARY} PUBLIC awsmockcore awsmockdto awsmockdb awsmocksrv mongocxx bsoncxx
        PocoPrometheus PocoNet PocoJSON PocoXML PocoZip PocoFoundation PocoUtil pthread crypto ssl z archive
        curl tbb)
add_library(${BINARY}_lib STATIC ${SOURCES})

install(TARGETS ${BINARY} DESTINATION bin)
