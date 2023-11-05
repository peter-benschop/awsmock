FROM jensvogt/aws-mock-base:latest

RUN apt-get update && apt-get -y upgrade && apt-get -y install zip

# Install basics
ARG GH_TOKEN=${GH_TOKEN}
ENV GH_TOKEN=${GH_TOKEN}
#RUN gh auth login

# Create build environment
RUN mkdir -p /usr/src

# Install aws-mock
WORKDIR /usr/src
RUN git clone https://github.com/jensvogt/aws-mock.git && \
    cd /usr/src/aws-mock && \
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr . && \
    cmake --build . --config Release && \
    cmake --install . --prefix /usr &&\
    cp dist/etc/aws-mock.properties /etc

# Supervisord
RUN apt-get update && apt-get install -y supervisor
RUN mkdir -p /var/log/supervisor
RUN mkdir -p /etc/supervisor/conf.d/
COPY supervisord.conf /etc/supervisor/conf.d/supervisord.conf

# AWS CLI v2
WORKDIR /usr/src
RUN curl "https://awscli.amazonaws.com/awscli-exe-linux-x86_64.zip" -o "awscliv2.zip" && \
    unzip awscliv2.zip && \
    ./aws/install --bin-dir /usr/bin --install-dir /usr

# Cleanup
RUN rm -rf /usr/src

# Make dirctories
RUN mkdir -p /tmp/awsmock/data/s3 && \
    mkdir -p /tmp/awsmock/data/lambda && \
    mkdir -p /tmp/awsmock/data/transfer && \
    mkdir -p /tmp/awsmock/data/tmp

RUN aws configure set aws_access_key_id none && \
    aws configure set aws_secret_access_key none && \
    aws configure set default.region eu-central-1 && \
    aws configure set profile.awsmock.region eu-central-1 && \
    aws configure set profile.awsmock.aws_access_key_id none && \
    aws configure set profile.awsmock.aws_secret_access_key none

# Expose ports
EXPOSE 4566 4566
EXPOSE 8081 8081
EXPOSE 27017 27017

VOLUME /var/run/docker.sock /var/run/docker.sock

CMD ["/usr/bin/supervisord", "-c", "/etc/supervisor/conf.d/supervisord.conf"]