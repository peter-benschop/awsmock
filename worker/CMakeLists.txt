
set(LIBRARY awsmockwrk)
set(LIBRARY_STATIC awsmockwrk_static)

set(SOURCES src/S3Worker.cpp )
set(HEADERS include/awsmock/worker/S3Worker.h)

# Includes
include_directories(include ../core/include ../db/include ../dto/include ../service/include /usr/include /usr/local/include)

add_library(${LIBRARY} SHARED ${SOURCES})
add_library(${LIBRARY_STATIC} STATIC ${SOURCES})
set_target_properties(${LIBRARY_STATIC} PROPERTIES OUTPUT_NAME ${LIBRARY})

install(TARGETS ${LIBRARY} ${LIBRARY_STATIC} DESTINATION lib/awsmock)
#install(FILES ${HEADERS} DESTINATION include/awsmock/service)