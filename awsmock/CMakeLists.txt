set(BINARY ${CMAKE_PROJECT_NAME})

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(SOURCES src/config/Configuration.cpp src/resource/HandlerException.cpp src/resource/AbstractResource.cpp
        src/handling/JsonAPIAbstractRelatedResourceBuilder.cpp src/handling/JsonAPIAbstractRootResourceBuilder.cpp
        src/handling/JsonAPIErrorBuilder.cpp src/handling/JsonAPIResourceBuilder.cpp src/resource/factory/Factory.cpp
        src/handling/JsonAPIAbstractResourceBuilder.cpp src/handling/JsonAPIResourceCollectionBuilder.cpp
        src/resource/factory/S3Factory.cpp src/resource/handler/S3Handler.cpp src/resource/factory/SQSFactory.cpp
        src/resource/handler/SQSHandler.cpp src/resource/factory/SNSFactory.cpp src/resource/handler/SNSHandler.cpp
        src/controller/ResourceNotFound.cpp src/controller/Router.cpp src/controller/RestService.cpp src/main.cpp)

include_directories(include ../core/include ../db/include ../dto/include ../service/include)
link_directories(/usr/lib /usr/lib/x86_64-linux-gnu /usr/local/lib ../core ../db ../service)

# External includes
include_directories(/usr/include /usr/local/include)

add_executable(${BINARY} ${SOURCES})

target_link_libraries(${BINARY} PUBLIC awsmockcore awsmockdb awsmocksrv awsmockdto PocoDataPostgreSQL PocoData
        PocoDataSQLite PocoPrometheus PocoNet PocoNetSSL PocoUtil PocoJSON PocoXML PocoZip PocoFoundation pthread
        crypto ssl z)
add_library(${BINARY}_lib STATIC ${SOURCES})

install(TARGETS ${BINARY} DESTINATION bin)
