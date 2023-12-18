FROM alpine:latest

RUN apk update && apk add groff g++ make cmake ccache openssl-dev git curl curl-dev python3 aws-cli linux-headers  \
    libarchive libarchive-dev github-cli libtbb libtbb-dev asio-dev gtest-dev pandoc icu-libs

# Create build environment
RUN mkdir -p /usr/src

# Install Poco framework
RUN cd /usr/src && \
    git clone -b devel https://github.com/pocoproject/poco.git && \
    cd poco && \
    cmake -DENABLE_PAGECOMPILER=OFF -DENABLE_DATA_SQLITE=OFF -DENABLE_REDIS=OFF -DENABLE_DATA_POSTGRESQL=OFF  \
    -DENABLE_DATA_MYSQL=OFF -DENABLE_NETSSL=ON -DENABLE_MONGODB=OFF -DENABLE_JWT=OFF -DENABLE_DATA=OFF  \
    -DENABLE_ACTIVERECORD=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr . && \
    make install

# Install mongo-c-driver
RUN cd /usr/src && \
    git clone -b r1.24 https://github.com/mongodb/mongo-c-driver.git && \
    cd mongo-c-driver && \
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr . && \
    make install

# Install mongo-cxx-driver
RUN cd /usr/src && \
    git clone -b releases/v3.8 https://github.com/mongodb/mongo-cxx-driver.git && \
    cd mongo-cxx-driver && \
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_CXX_STANDARD=17 . && \
    make install

# Cleanup
RUN rm -rf /usr/src
