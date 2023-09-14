FROM jensvogt/aws-mock-base:latest

# Install basics
RUN mkdir -p /usr/src

# Install aws-mock
RUN cd /usr/src && \
    git clone https://github.com/jensvogt/aws-mock.git && \
    cd /usr/src/aws-mock && \
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr . && \
    cmake --build . --config Release && \
    cmake --install . --prefix /usr &&\
    cp etc/aws-mock.properties /etc

# Supervisord
RUN apt-get update && apt-get install -y supervisor
RUN mkdir -p /var/log/supervisor
RUN mkdir -p /etc/supervisor/conf.d/
COPY supervisord.conf /etc/supervisor/conf.d/supervisord.conf

# Cleanup
RUN rm -rf /usr/src

# Make dirctories
RUN mkdir -p /tmp/awsmock/data/s3 && \
    mkdir -p /tmp/awsmock/data/lambda && \
    mkdir -p /tmp/awsmock/data/transfer && \
    mkdir -p /tmp/awsmock/data/tmp && \
    mkdir -p /tmp/awsmock/init

# Expose ports
EXPOSE 80 80
EXPOSE 8081 8081
EXPOSE 27017 27017

CMD ["/usr/bin/supervisord", "-c", "/etc/supervisor/conf.d/supervisord.conf"]