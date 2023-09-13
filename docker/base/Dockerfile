FROM debian:bookworm-slim

# Install basics
RUN apt-get update && apt-get -y install build-essential cmake git openssl libssl-dev supervisor libarchive-dev \
    zlib1g-dev wget libarchive13 libz1 libcurl4-openssl-dev libtbb-dev
RUN mkdir -p /usr/src

# Install google test
RUN mkdir -p /usr/src && \
    cd /usr/src && \
    git clone https://github.com/google/googletest.git && \
    cd googletest && \
    cmake -DBUILD_SHARED_LIBS=ON . &&\
    make && \
    make install

# Install Poco libraries
RUN cd /usr/src && \
    git clone -b master https://github.com/pocoproject/poco.git && \
    cd poco && \
    cmake -DENABLE_PAGECOMPILER=OFF -DENABLE_DATA_SQLITE=OFF -DENABLE_REDIS=OFF -DENABLE_DATA_POSTGRESQL=OFF -DENABLE_DATA_MYSQL=OFF \
    -DENABLE_NETSSL=ON -DENABLE_MONGODB=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr . && \
    make && \
    make install

# Install mongo-c-driver
RUN cd /usr/src && \
    git clone -b r1.24 https://github.com/mongodb/mongo-c-driver.git && \
    cd mongo-c-driver && \
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr . && \
    make && \
    make install

# Install mongo-c-driver
RUN cd /usr/src && \
    git clone -b releases/v3.8 https://github.com/mongodb/mongo-cxx-driver.git && \
    cd mongo-cxx-driver && \
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_CXX_STANDARD=17 . && \
    make && \
    make install
