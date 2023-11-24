FROM alpine:latest

RUN apk update && apk add groff g++ make cmake ccache openssl-dev git gdb curl curl-dev wget python3 aws-cli  \
    linux-headers libarchive-dev github-cli gtest-dev libtbb libtbb-dev asio-dev elogind-dev

# Install basics
ARG GH_TOKEN=${GH_TOKEN}
ENV GH_TOKEN=${GH_TOKEN}
#RUN gh auth login

# Create build environment
RUN mkdir -p /usr/src

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

# Install mongo-cxx-driver
RUN cd /usr/src && \
    git clone -b releases/v3.8 https://github.com/mongodb/mongo-cxx-driver.git && \
    cd mongo-cxx-driver && \
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_CXX_STANDARD=17 . && \
    make install

# Install aws-mock
WORKDIR /usr/src
RUN git clone https://github.com/jensvogt/aws-mock.git && \
    cd /usr/src/aws-mock && \
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr . && \
    cmake --build . --config Release && \
    cmake --install . --prefix /usr

# Cleanup
RUN rm -rf /usr/src
RUN apk del gcc g++ cmake make linux_headers curl-dev openssl-dev libarchive-dev gtest-dev libtbb-dev asio-dev \
    elogind-dev

# Make dirctories
RUN mkdir -p /tmp/awsmock/data/s3 && \
    mkdir -p /tmp/awsmock/data/lambda && \
    mkdir -p /tmp/awsmock/data/transfer && \
    mkdir -p /tmp/awsmock/data/tmp

RUN /usr/bin/aws configure set aws_access_key_id none && \
    /usr/bin/aws configure set aws_secret_access_key none && \
    /usr/bin/aws configure set default.region eu-central-1 && \
    /usr/bin/aws configure set profile.awsmock.region eu-central-1 && \
    /usr/bin/aws configure set profile.awsmock.aws_access_key_id none && \
    /usr/bin/aws configure set profile.awsmock.aws_secret_access_key none

# Expose ports
EXPOSE 4566 4566
EXPOSE 4567 4567
EXPOSE 8081 8081

VOLUME /var/run/docker.sock /var/run/docker.sock

CMD ["/usr/bin/awsmockmgr"]
