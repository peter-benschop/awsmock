FROM jensvogt/aws-mock-base:latest

# Install aws-mock
WORKDIR /usr/src
RUN git clone https://github.com/jensvogt/aws-mock.git && \
    cd /usr/src/aws-mock && \
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr . && \
    cmake --build . --config Release && \
    cmake --install . --prefix /usr

# Cleanup
RUN apk del gcc g++ cmake ccache make linux-headers curl-dev openssl-dev libarchive-dev gtest-dev libtbb-dev asio-dev \
    gtest-dev
RUN rm -rf /usr/src

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

CMD ["/usr/bin/bash"]
