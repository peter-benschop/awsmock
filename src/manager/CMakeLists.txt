set(BINARY awsmockmgr)
set(AWS_CRT_SDK aws-crt-cpp aws-c-event-stream aws-c-s3 aws-c-auth aws-c-mqtt aws-c-http aws-c-sdkutils aws-checksums
        aws-c-io aws-c-cal aws-c-common aws-c-compression s2n)

set(SOURCES src/resource/HandlerException.cpp src/resource/AbstractResource.cpp src/resource/factory/Factory.cpp
        src/resource/factory/ModuleFactory.cpp src/resource/handler/ModuleHandler.cpp src/controller/ResourceNotFound.cpp
        src/controller/Router.cpp src/controller/RestService.cpp src/main.cpp)


# External includes
if (WIN32)
    include_directories(./include ../core/include ../db/include ../dto/include ../service/include ${AWSMOCK_WIN32_DIR}/include)
    link_directories(${AWSMOCK_WIN32_DIR}/lib ../core/${CMAKE_BUILD_TYPE} ../db/${CMAKE_BUILD_TYPE} ../dto/${CMAKE_BUILD_TYPE}
            ../service/${CMAKE_BUILD_TYPE})
else ()
    include_directories(./include ../core/include ../db/include ../dto/include ../service/include /usr/include/bsoncxx/v_noabi /usr/include/mongocxx/v_noabi)
    link_directories(../core ../dto ../db ../service /usr/lib/x86_64-linux-gnu)
endif ()

add_executable(${BINARY} ${SOURCES})
add_library(${BINARY}_lib STATIC ${SOURCES})

if (WIN32)
    target_link_libraries(${BINARY} PUBLIC awsmockcore awsmockdto awsmockdb awsmocksrv
            PocoPrometheusd PocoNet PocoJSON PocoXML PocoZip PocoFoundation PocoUtil libcrypto.lib libssl.lib
            archive.lib libcurl_imp.lib bsoncxx-v_noabi-rhb-x64-v143-md.lib mongocxx-v_noabi-rhb-x64-v143-md.lib)
else ()
    target_link_libraries(${BINARY} PUBLIC awsmockcore awsmockdto awsmockdb awsmocksrv mongocxx bsoncxx PocoPrometheus
            PocoNet PocoJSON PocoXML PocoZip PocoFoundation PocoUtil pthread crypto ssl z archive curl tbb)
endif ()

install(TARGETS ${BINARY} DESTINATION bin)
