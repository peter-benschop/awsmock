
set(LIBRARY awsmockdto)
set(LIBRARY_STATIC awsmockdto_static)

set(SQS_SOURCES src/sqs/MessageAttribute.cpp src/sqs/SendMessageRequest.cpp src/sqs/SendMessageResponse.cpp
        src/sqs/ListQueueResponse.cpp)
set(DOCKER_SOURCES src/docker/Port.cpp src/docker/Container.cpp src/docker/ListContainerResponse.cpp)
set(LAMBDA_SOURCES src/lambda/ListTagsResponse.cpp src/lambda/ListFunctionResponse.cpp src/lambda/DeadLetterConfig.cpp
        src/lambda/Function.cpp)

set(SOURCES ${SQS_SOURCES} ${DOCKER_SOURCES} ${LAMBDA_SOURCES})

# Includes
include_directories(include ../core/include ../db/include /usr/include /usr/include/mongo /usr/include/bsoncxx/v_noabi
        /usr/include/mongocxx/v_noabi tbb)

add_library(${LIBRARY} SHARED ${SOURCES})
add_library(${LIBRARY_STATIC} STATIC ${SOURCES})
set_target_properties(${LIBRARY_STATIC} PROPERTIES OUTPUT_NAME ${LIBRARY})

install(TARGETS ${LIBRARY} DESTINATION lib)
