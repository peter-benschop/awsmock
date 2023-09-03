
set(LIBRARY awsmockdb)
set(LIBRARY_STATIC awsmockdb_static)

set(SOURCES src/repository/Database.cpp src/repository/ServiceDatabase.cpp src/repository/S3Database.cpp
        src/repository/SQSDatabase.cpp src/repository/SNSDatabase.cpp src/repository/LambdaDatabase.cpp
        src/repository/TransferDatabase.cpp src/entity/lambda/Tags.cpp src/entity/lambda/Environment.cpp
        src/entity/lambda/EphemeralStorage.cpp src/entity/lambda/Lambda.cpp)

# Test directory
add_subdirectory(tst)

# Includes
include_directories(include ../core/include /usr/include /usr/include/mongo /usr/include/bsoncxx/v_noabi
        /usr/include/mongocxx/v_noabi tbb)

add_library(${LIBRARY} SHARED ${SOURCES})
add_library(${LIBRARY_STATIC} STATIC ${SOURCES})
set_target_properties(${LIBRARY_STATIC} PROPERTIES OUTPUT_NAME ${LIBRARY})

install(TARGETS ${LIBRARY} DESTINATION lib)
