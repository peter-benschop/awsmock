FROM debian:latest

# Install basics
RUN apt-get update && apt-get -y install build-essential cmake git openssl libssl-dev supervisor libiodbc2 libiodbc2-dev libpq-dev libpqxx-dev && \
    mkdir -p /usr/src

# Install Poco libraries \
RUN cd /usr/src && \
    git clone -b master https://github.com/pocoproject/poco.git && \
    cd /usr/src/poco && \
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr . && \
    make && \
    make install

# Install aws-mock \
RUN cd /usr/src && \
    git clone https://github.com/jensvogt/aws-mock.git && \
    cd /usr/src/aws-mock && \
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr . && \
    make && \
    make install

# Supervisord
RUN apt-get update && \
    apt-get install -y supervisor
RUN mkdir -p /var/log/supervisor
COPY supervisord.conf /etc/supervisor/conf.d/supervisord.conf

COPY aws-mock.properties /etc
COPY aws-mock /usr/bin
COPY libs/*.94 /usr/lib
COPY libs/libawsmock* /usr/lib

RUN mkdir -p /tmp/awsmock/data && \
    mkdir -p /tmp/awsmock/data/db && \
    mkdir -p /tmp/awsmock/log

EXPOSE 4567 4567

CMD ["/usr/bin/supervisord"]