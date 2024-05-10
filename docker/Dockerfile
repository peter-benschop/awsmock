FROM jensvogt/aws-mock-base:latest as build

# Create build environment
RUN mkdir -p /usr/src

# Install aws-mock
WORKDIR /usr/src
RUN git clone https://github.com/jensvogt/awsmock.git && \
    cd /usr/src/awsmock && \
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr . && \
    cmake --build . --config Release -j 16 && \
    cmake --install . --prefix /usr

# Cleanup
RUN rm -rf /usr/src

FROM alpine:latest

RUN apk update && apk add aws-cli

# Make dirctories
RUN mkdir -p /tmp/awsmock/data/s3 && \
    mkdir -p /tmp/awsmock/data/lambda && \
    mkdir -p /tmp/awsmock/data/transfer && \
    mkdir -p /tmp/awsmock/data/tmp

# Runtime

COPY --from=build /usr/lib/libstdc++.so.6 /usr/lib/
COPY --from=build /usr/lib/libgcc_s.so.1 /usr/lib/
COPY --from=build /usr/lib/libicuuc.so.74 /usr/lib/
COPY --from=build /usr/lib/libcurl.so.4 /usr/lib/
COPY --from=build /usr/lib/libarchive.so.13 /usr/lib/
COPY --from=build /usr/lib/libzstd.so.1 /usr/lib/
COPY --from=build /usr/lib/libexpat.so.1 /usr/lib/
COPY --from=build /usr/lib/liblzma.so.5 /usr/lib/
COPY --from=build /usr/lib/liblz4.so.1 /usr/lib/
COPY --from=build /usr/lib/libbz2.so.1 /usr/lib/
COPY --from=build /usr/lib/libcares.so.2 /usr/lib/
COPY --from=build /usr/lib/libnghttp2.so.14 /usr/lib/
COPY --from=build /usr/lib/libidn2.so.0 /usr/lib/
COPY --from=build /usr/lib/libbrotlidec.so.1 /usr/lib/
COPY --from=build /usr/lib/libicudata.so.74 /usr/lib/
COPY --from=build /usr/lib/libunistring.so.5 /usr/lib/
COPY --from=build /usr/lib/libbrotlicommon.so.1 /usr/lib/
COPY --from=build /lib/libacl.so.1.1.2301 /lib/
RUN ln -s /lib/libacl.so.1.1.2301 /lib/libacl.so.1

# Install poco
COPY --from=build /usr/lib/libPocoPrometheus.so.103 /usr/lib/
COPY --from=build /usr/lib/libPocoNet.so.103 /usr/lib/
COPY --from=build /usr/lib/libPocoJSON.so.103 /usr/lib/
COPY --from=build /usr/lib/libPocoXML.so.103 /usr/lib/
COPY --from=build /usr/lib/libPocoZip.so.103 /usr/lib/
COPY --from=build /usr/lib/libPocoUtil.so.103 /usr/lib/
COPY --from=build /usr/lib/libPocoFoundation.so.103 /usr/lib/
RUN ln -s /usr/lib/libPocoPrometheus.so.103 /usr/lib/libPocoPrometheus.so
RUN ln -s /usr/lib/libPocoNet.so.103 /usr/lib/libPocoNet.so
RUN ln -s /usr/lib/libPocoJSON.so.103 /usr/lib/libPocoJSON.so
RUN ln -s /usr/lib/libPocoXML.so.103 /usr/lib/libPocoXML.so
RUN ln -s /usr/lib/libPocoZip.so.103 /usr/lib/libPocoZip.so
RUN ln -s /usr/lib/libPocoUtil.so.103 /usr/lib/libPocoUtil.so
RUN ln -s /usr/lib/libPocoFoundation.so.103 /usr/lib/libPocoFoundation.so

# Install Mongo C/C++ driver
COPY --from=build /usr/lib/libbson-1.0.so.0.0.0 /usr/lib/
RUN ln -s /usr/lib/libbson-1.0.so.0.0.0 /usr/lib/libbson-1.0.so.0
RUN ln -s /usr/lib/libbson-1.0.so.0 /usr/lib/libbson-1.0.so
COPY --from=build /usr/lib/libmongoc-1.0.so.0.0.0 /usr/lib/
RUN ln -s /usr/lib/libmongoc-1.0.so.0.0.0 /usr/lib/libmongoc-1.0.so.0
RUN ln -s /usr/lib/libmongoc-1.0.so.0 /usr/lib/libmongoc-1.0.so
COPY --from=build /usr/lib/libmongocxx.so.3.10.2-pre /usr/lib/
RUN ln -s /usr/lib/libmongocxx.so.3.10.2-pre /usr/lib/libmongocxx.so._noabi
COPY --from=build /usr/lib/libbsoncxx.so.3.10.2-pre /usr/lib/
RUN ln -s /usr/lib/libbsoncxx.so.3.10.2-pre /usr/lib/libbsoncxx.so._noabi
RUN ln -s /usr/lib/libbsoncxx.so._noabi /usr/lib/libbsoncxx.so

# Install aws-mock
COPY --from=build /usr/bin/aws /usr/bin/
COPY --from=build /usr/bin/awsmockmgr /usr/bin/
COPY --from=build /usr/bin/awsmockctl /usr/bin/
COPY --from=build /usr/lib/libawsmock* /usr/lib/
COPY --from=build /etc/awsmock.properties /etc/
COPY --from=build /usr/bin/awslocal /usr/bin/
COPY --from=build /etc/awsmock.properties /etc

# Configure awslocal
RUN aws configure set aws_access_key_id none && \
    aws configure set aws_secret_access_key none && \
    aws configure set default.region eu-central-1 && \
    aws configure set profile.awsmock.region eu-central-1 && \
    aws configure set profile.awsmock.aws_access_key_id none && \
    aws configure set profile.awsmock.aws_secret_access_key none

# Expose ports
EXPOSE 4566 4566
EXPOSE 4567 4567
EXPOSE 8081 8081

VOLUME /var/run/docker.sock /var/run/docker.sock

ENV AWSMOCK_MONGODB_ACTIVE=false

CMD ["/usr/bin/awsmockmgr"]
