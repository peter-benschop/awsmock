set(BINARY awsmockmgr)

set(SOURCES src/resource/HandlerException.cpp src/resource/AbstractResource.cpp src/resource/factory/Factory.cpp
        src/resource/factory/ModuleFactory.cpp src/resource/handler/ModuleHandler.cpp src/controller/ResourceNotFound.cpp
        src/controller/Router.cpp src/controller/RestService.cpp src/main.cpp)


# External includes
if(WIN32)
    include_directories(./include ../core/include ../db/include ../dto/include ../service/include)
    include_directories(${AWSMOCK_WIN32_DIR}/poco/include ${AWSMOCK_WIN32_DIR}/gnuwin32/include)
    include_directories(${AWSMOCK_WIN32_DIR}/plog/include ${AWSMOCK_WIN32_DIR}/openssl/include)
    include_directories(${AWSMOCK_WIN32_DIR}/curl/include ${AWSMOCK_WIN32_DIR}/boost)
    include_directories(${AWSMOCK_WIN32_DIR}/libarchive/include)
    include_directories(${AWSMOCK_WIN32_DIR}/mongo-cxx-driver/include/bsoncxx/v_noabi)
    include_directories(${AWSMOCK_WIN32_DIR}/mongo-cxx-driver/include/mongocxx/v_noabi)
    link_directories(../core/${CMAKE_BUILD_TYPE} ../db/${CMAKE_BUILD_TYPE} ../dto/${CMAKE_BUILD_TYPE})
    link_directories(${AWSMOCK_WIN32_DIR}/poco/lib ${AWSMOCK_WIN32_DIR}/gnuwin32/lib)
    link_directories(${AWSMOCK_WIN32_DIR}/libarchive/lib ${AWSMOCK_WIN32_DIR}/openssl/lib/VC/x64/MD)
    link_directories(${AWSMOCK_WIN32_DIR}/mongo-cxx-driver/lib ${AWSMOCK_WIN32_DIR}/curl/lib)
else()
    include_directories(./include ../core/include ../db/include ../dto/include ../service/include /usr/include/bsoncxx/v_noabi /usr/include/mongocxx/v_noabi)
    link_directories(../core ../dto ../db ../service)
endif ()

add_executable(${BINARY} ${SOURCES})

if(WIN32)

    target_link_libraries(${BINARY} PUBLIC awsmockcore awsmockdto awsmockdb awsmocksrv mongocxx bsoncxx
            PocoPrometheus PocoNet PocoJSON PocoXML PocoZip PocoFoundation PocoUtil libcrypto.lib libssl.lib
            archive.lib libcurl_imp.lib)
else()
    target_link_libraries(${BINARY} PUBLIC awsmockcore awsmockdto awsmockdb awsmocksrv mongocxx bsoncxx
            PocoPrometheus PocoNet PocoJSON PocoXML PocoZip PocoFoundation PocoUtil pthread crypto ssl z archive
            curl tbb)
endif ()

add_library(${BINARY}_lib STATIC ${SOURCES})

install(TARGETS ${BINARY} DESTINATION bin)
