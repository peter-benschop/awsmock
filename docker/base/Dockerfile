FROM alpine:latest

RUN apk update && apk add groff g++ make cmake ccache openssl-dev git python3 aws-cli linux-headers  \
    libarchive libarchive-dev github-cli asio-dev gtest-dev pandoc icu-libs doxygen boost-program_options \
    boost-filesystem boost-thread boost-url minizip curl curl-dev minizip-dev plog plog-dev yaml-cpp yaml-cpp-dev

# Create build environment
RUN mkdir -p /usr/src

# Install jwt-cpp
RUN cd /usr/src && \
    git clone https://github.com/Thalhammer/jwt-cpp.git && \
    cd jwt-cpp && \
    cmake . && \
    cmake --install .

# Prometheus-CPP
RUN cd /usr/src && \
    git clone --recursive https://github.com/jupp0r/prometheus-cpp && \
    cd prometheus-cpp && \
    cmake . && \
    cmake --build . -j16 && \
    cmake --install .

# Install mongo-cxx-driver
RUN cd /usr/src && \
    git clone https://github.com/mongodb/mongo-cxx-driver.git && \
    cd mongo-cxx-driver && \
    cmake -DCMAKE_CXX_STANDARD=20 -DENABLE_UNINSTALL=OFF . && \
    cmake --build . --config Release -j 16 && \
    cmake --install . --prefix /usr/local

# Cleanup
RUN rm -rf /usr/src
