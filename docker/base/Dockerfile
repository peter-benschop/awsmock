FROM alpine:latest

RUN apk update && apk add groff g++ make cmake ccache openssl-dev git curl curl-dev python3 aws-cli linux-headers  \
    libarchive libarchive-dev github-cli libtbb libtbb-dev asio-dev gtest-dev pandoc icu-libs doxygen

# Create build environment
RUN mkdir -p /usr/src

# Install Plog logging framework
RUN cd /usr/src && \
    git clone https://github.com/SergiusTheBest/plog.git && \
    cd plog && \
    cmake . && \
    cmake --install .

# Install Poco framework
RUN cd /usr/src && \
    git clone https://github.com/pocoproject/poco.git && \
    cd poco && \
    cmake -DENABLE_PAGECOMPILER=OFF -DENABLE_DATA_SQLITE=OFF -DENABLE_REDIS=OFF -DENABLE_DATA_POSTGRESQL=OFF  \
    -DENABLE_DATA_MYSQL=OFF -DENABLE_NETSSL=ON -DENABLE_MONGODB=OFF -DENABLE_JWT=OFF -DENABLE_DATA=OFF  \
    -DENABLE_ACTIVERECORD=OFF . && \
    cmake --build . --config Release -j 16 && \
    cmake --install .

# Install mongo-cxx-driver
RUN cd /usr/src && \
    git clone https://github.com/mongodb/mongo-cxx-driver.git && \
    cd mongo-cxx-driver && \
    cmake -DCMAKE_CXX_STANDARD=17 . && \
    cmake --build . --config Release -j 16 && \
    cmake --install .

# Cleanup
RUN rm -rf /usr/src
