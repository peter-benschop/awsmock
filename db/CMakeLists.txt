
set(LIBRARY awsmockdb)
set(LIBRARY_STATIC awsmockdb_static)

set(SOURCES src/Database.cpp src/S3Database.cpp )
set(HEADERS include/awsmock/db/Database.h include/awsmock/db/S3Database.h)

# Includes
include_directories(/usr/include /usr/local/include include ../core/include)

add_library(${LIBRARY} SHARED ${SOURCES})
add_library(${LIBRARY_STATIC} STATIC ${SOURCES})
set_target_properties(${LIBRARY_STATIC} PROPERTIES OUTPUT_NAME ${LIBRARY})

install(TARGETS ${LIBRARY} ${LIBRARY_STATIC} DESTINATION lib/awsmock)
install(FILES ${HEADERS} DESTINATION include/awsmock/db)