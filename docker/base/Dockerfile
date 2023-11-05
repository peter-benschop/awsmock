FROM debian:bookworm-slim

# Install basics
RUN apt-get update && apt-get -y install build-essential cmake git openssl libssl-dev supervisor libarchive-dev \
    zlib1g-dev wget libarchive13 libz1 libcurl4-openssl-dev libtbb-dev libasio-dev gnupg curl gh libsystemd.dev zip
RUN mkdir -p /usr/src

# Install google test
RUN mkdir -p /usr/src && \
    cd /usr/src && \
    git clone https://github.com/google/googletest.git && \
    cd googletest && \
    cmake -DBUILD_SHARED_LIBS=ON . &&\
    make install

# Install Poco framework
RUN cd /usr/src && \
    git clone -b master https://github.com/pocoproject/poco.git && \
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

# Install mongo-c-driver
RUN cd /usr/src && \
    git clone -b releases/v3.8 https://github.com/mongodb/mongo-cxx-driver.git && \
    cd mongo-cxx-driver && \
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_CXX_STANDARD=17 . && \
    make install

# Install libssl 1.1
RUN wget http://security.debian.org/debian-security/pool/updates/main/o/openssl/libssl1.1_1.1.1n-0+deb11u5_amd64.deb && \
    dpkg -i libssl1.1_1.1.1n-0+deb11u5_amd64.deb && \
    rm libssl1.1_1.1.1n-0+deb11u5_amd64.deb

# Install MongoDB
RUN apt-get install gnupg2 -y && \
    curl -fsSL https://pgp.mongodb.com/server-7.0.asc | gpg -o /usr/share/keyrings/mongodb-server-7.0.gpg --dearmor && \
    echo "deb [ signed-by=/usr/share/keyrings/mongodb-server-7.0.gpg ] http://repo.mongodb.org/apt/debian bullseye/mongodb-org/7.0 main" | tee /etc/apt/sources.list.d/mongodb-org-7.0.list && \
    apt-get update && \
    apt-get install -y mongodb-org
RUN mkdir -p /data/db

# Start MongoDB
COPY ../mongod.conf /etc/mongod.conf
RUN mkdir -p /var/log/mongodb && \
    mkdir -p /var/lib/mongodb

RUN rm -rf /usr/src
