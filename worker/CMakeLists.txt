
set(LIBRARY awsmockwrk)
set(LIBRARY_STATIC awsmockwrk_static)

#src/worker/S3Worker.cpp src/worker/S3Monitoring.cpp

set(WORKER_SOURCES )
set(FTP_SOURCES src/ftpserver/Filesystem.cpp src/ftpserver/FtpSession.cpp src/ftpserver/FtpServer.cpp
        src/ftpserver/FtpServerImpl.cpp src/ftpserver/UserDatabase.cpp)

set(SOURCES ${WORKER_SOURCES} ${FTP_SOURCES})

# Includes
include_directories(include ../core/include ../db/include ../dto/include ../service/include
        /usr/include/bsoncxx/v_noabi /usr/include/mongocxx/v_noabi /usr/include /usr/local/include)

add_library(${LIBRARY} SHARED ${SOURCES})
add_library(${LIBRARY_STATIC} STATIC ${SOURCES})
set_target_properties(${LIBRARY_STATIC} PROPERTIES OUTPUT_NAME ${LIBRARY})

install(TARGETS ${LIBRARY} DESTINATION lib)
