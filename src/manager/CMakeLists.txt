set(BINARY awsmockmgr)

set(SOURCES src/resource/HandlerException.cpp src/resource/AbstractResource.cpp src/resource/factory/Factory.cpp
        src/resource/factory/ModuleFactory.cpp src/resource/handler/ModuleHandler.cpp src/controller/ResourceNotFound.cpp
        src/controller/Router.cpp src/controller/RestService.cpp src/main.cpp)


# External includes
if(WIN32)
    include_directories(./include ../core/include ../db/include ../dto/include ../service/include ${AWSMOCK_WIN32_DIR}/include)
    link_directories(${AWSMOCK_WIN32_DIR}/lib ../core/${CMAKE_BUILD_TYPE} ../db/${CMAKE_BUILD_TYPE} ../dto/${CMAKE_BUILD_TYPE}
            ../service/${CMAKE_BUILD_TYPE})
else()
    include_directories(./include ../core/include ../db/include ../dto/include ../service/include /usr/include/bsoncxx/v_noabi /usr/include/mongocxx/v_noabi)
    link_directories(../core ../dto ../db ../service)
endif ()

add_executable(${BINARY} ${SOURCES})

if(WIN32)
    target_link_libraries(${BINARY} PUBLIC awsmockcore awsmockdto awsmockdb awsmocksrv
            PocoPrometheus PocoNet PocoJSON PocoXML PocoZip PocoFoundation PocoUtil libcrypto.lib libssl.lib
            archive.lib libcurl_imp.lib bsoncxx-v_noabi-rhb-x64-v143-md.lib mongocxx-v_noabi-rhb-x64-v143-md.lib)
else()
    target_link_libraries(${BINARY} PUBLIC awsmockcore awsmockdto awsmockdb awsmocksrv mongocxx bsoncxx PocoPrometheus
            PocoNet PocoJSON PocoXML PocoZip PocoFoundation PocoUtil pthread crypto ssl z archive curl tbb)
endif ()

add_library(${BINARY}_lib STATIC ${SOURCES})

install(TARGETS ${BINARY} DESTINATION bin)
