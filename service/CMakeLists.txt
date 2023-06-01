
set(LIBRARY awsmocksrv)
set(LIBRARY_STATIC awsmocksrv_static)

set(SOURCES src/S3Service.cpp src/SQSService.cpp)
set(HEADERS include/awsmock/service/S3Service.h include/awsmock/service/SQSService.h)

# Includes
include_directories(include ../core/include ../db/include ../dto/include /usr/include /usr/local/include)

add_library(${LIBRARY} SHARED ${SOURCES})
add_library(${LIBRARY_STATIC} STATIC ${SOURCES})
set_target_properties(${LIBRARY_STATIC} PROPERTIES OUTPUT_NAME ${LIBRARY})

install(TARGETS ${LIBRARY} ${LIBRARY_STATIC} DESTINATION lib/awsmock)
#install(FILES ${HEADERS} DESTINATION include/awsmock/service)