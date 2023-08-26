FROM debian:bookworm-slim AS build

# Install basics
RUN apt-get update && apt-get -y install build-essential cmake git openssl libssl-dev supervisor libarchive-dev \
    zlib1g-dev wget libarchive13 libz1 libcurl4-openssl-dev
RUN mkdir -p /usr/src

# Install google test
RUN mkdir -p /usr/src && \
    cd /usr/src && \
    git clone https://github.com/google/googletest.git && \
    cd /usr/src/googletest && \
    cmake -DBUILD_SHARED_LIBS=ON . &&\
    make && \
    make install

# Install Poco libraries
RUN cd /usr/src && \
    git clone -b master https://github.com/pocoproject/poco.git && \
    cd /usr/src/poco && \
    cmake -DENABLE_PAGECOMPILER=OFF -DENABLE_DATA_SQLITE=OFF -DENABLE_REDIS=OFF -DENABLE_DATA_POSTGRESQL=OFF -DENABLE_DATA_MYSQL=OFF \
    -DENABLE_NETSSL=ON -DENABLE_MONGODB=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr . && \
    make && \
    make install

# Install mongo-c-driver
RUN cd /usr/src && \
    git clone -b r1.24 https://github.com/mongodb/mongo-c-driver.git && \
    cd /usr/src/mongo-c-driver && \
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr . && \
    make && \
    make install

# Install mongo-c-driver
RUN cd /usr/src && \
    git clone -b releases/v3.8 https://github.com/mongodb/mongo-cxx-driver.git && \
    cd /usr/src/mongo-cxx-driver && \
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr . && \
    make && \
    make install

# Install fineftp
RUN cd /usr/src && \
    git clone https://github.com/eclipse-ecal/fineftp-server.git && \
    cd /usr/src/finedtp-server && \
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr . && \
    sed -i 's/add_library (${PROJECT_NAME}/add_library (${PROJECT_NAME} SHARED/g' fineftp-server/CMakeLists.txt \
    make && \
    make install

# Install sv4git
RUN cd /usr/src && \
    wget https://github.com/bvieira/sv4git/releases/download/v2.9.0/git-sv_2.9.0_linux_amd64.tar.gz && \
    tar -xzf git-sv_2.9.0_linux_amd64.tar.gz && \
    cp git-sv /usr/bin && chmod 755 /usr/bin/git-sv

# Install aws-mock
RUN cd /usr/src && \
    git clone https://github.com/jensvogt/aws-mock.git && \
    cd /usr/src/aws-mock && \
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr . && \
    cmake --build . --config Release && \
    cmake --install . --prefix /usr

FROM debian:bookworm-slim

# Dependencies
RUN apt-get update && apt-get -y install libarchive13 libcurl4

# AwsMock
COPY --from=build /usr/src/aws-mock/etc/aws-mock.properties /etc
COPY --from=build /usr/bin/aws-mock /usr/bin
COPY --from=build /usr/lib/libawsmock* /usr/lib

# Poco libraries
COPY --from=build /usr/lib/libPocoFoundation.so.94 /usr/lib
RUN ln -s /usr/lib/libPocoFoundation.so.94 /usr/lib/libPocoFoundation.so
COPY --from=build /usr/lib/libPocoUtil.so.94 /usr/lib
RUN ln -s /usr/lib/libPocoUtil.so.94 /usr/lib/libPocoUtil.so
COPY --from=build /usr/lib/libPocoNet.so.94 /usr/lib
RUN ln -s /usr/lib/libPocoNet.so.94 /usr/lib/libPocoNet.so
COPY --from=build /usr/lib/libPocoXML.so.94 /usr/lib
RUN ln -s /usr/lib/libPocoXML.so.94 /usr/lib/libPocoXML.so
COPY --from=build /usr/lib/libPocoJSON.so.94 /usr/lib
RUN ln -s /usr/lib/libPocoJSON.so.94 /usr/lib/libPocoJSON.so
COPY --from=build /usr/lib/libPocoZip.so.94 /usr/lib
RUN ln -s /usr/lib/libPocoZip.so.94 /usr/lib/libPocoZip.so
COPY --from=build /usr/lib/libPocoCrypto.so.94 /usr/lib
RUN ln -s /usr/lib/libPocoCrypto.so.94 /usr/lib/libPocoCrypto.so
COPY --from=build /usr/lib/libPocoPrometheus.so.94 /usr/lib
RUN ln -s /usr/lib/libPocoPrometheus.so.94 /usr/lib/libPocoPrometheus.so

# Mongo libraries
COPY --from=build /usr/lib/x86_64-linux-gnu/libmongoc-1.0.so /usr/lib/x86_64-linux-gnu/
RUN ln -s /usr/lib/x86_64-linux-gnu/libmongoc-1.0.so /usr/lib/x86_64-linux-gnu/libmongoc-1.0.so.0
RUN ln -s  /usr/lib/x86_64-linux-gnu/libmongoc-1.0.so.0 /usr/lib/x86_64-linux-gnu/libmongoc-1.0.so.0.0.0
COPY --from=build /usr/lib/x86_64-linux-gnu/libmongocxx.so.3.8.1-pre /usr/lib/x86_64-linux-gnu/
RUN ln -s /usr/lib/x86_64-linux-gnu/libmongocxx.so.3.8.1-pre /usr/lib/x86_64-linux-gnu/libmongocxx.so._noabi
RUN ln -s /usr/lib/x86_64-linux-gnu/libmongocxx.so._noabi /usr/lib/x86_64-linux-gnu/libmongocxx.so
COPY --from=build /usr/lib/x86_64-linux-gnu/libbson-1.0.so /usr/lib/x86_64-linux-gnu/
RUN ln -s /usr/lib/x86_64-linux-gnu/libbson-1.0.so /usr/lib/x86_64-linux-gnu/libbson-1.0.so.0
RUN ln -s /usr/lib/x86_64-linux-gnu/libbson-1.0.so.0 /usr/lib/x86_64-linux-gnu/libbson-1.0.so.0.0.0
COPY --from=build /usr/lib/x86_64-linux-gnu/libbsoncxx.so.3.8.1-pre /usr/lib/x86_64-linux-gnu/
RUN ln -s /usr/lib/x86_64-linux-gnu/libbsoncxx.so.3.8.1-pre /usr/lib/x86_64-linux-gnu/libbsoncxx.so._noabi
RUN ln -s  /usr/lib/x86_64-linux-gnu/libbsoncxx.so._noabi /usr/lib/x86_64-linux-gnu/libbsoncxx.so

# Supervisord
RUN apt-get update && apt-get install -y supervisor
RUN mkdir -p /var/log/supervisor
COPY supervisord.conf /etc/supervisor/conf.d/supervisord.conf

# Make dirctories
RUN mkdir -p /tmp/awsmock/data/s3 && \
    mkdir -p /tmp/awsmock/data/sqs && \
    mkdir -p /tmp/awsmock/data/lambda && \
    mkdir -p /tmp/awsmock/init

# Add properties

# Expose ports
EXPOSE 4567 4567

# Cleanup
RUN rm -rf /usr/src

CMD ["/usr/bin/supervisord"]