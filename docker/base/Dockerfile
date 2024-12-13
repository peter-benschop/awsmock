FROM ubuntu:latest

RUN apt update && apt install -y groff g++ make cmake ccache git python3 zlib1g zlib1g-dev libarchive-dev libasio-dev libgtest-dev libgmock-dev pandoc doxygen  \
    libboost-program-options-dev libboost-filesystem-dev libboost-locale-dev libboost-url-dev libminizip-dev libcurl4-openssl-dev

# Create build environment
RUN mkdir -p /usr/src

# Install Plog logging framework
RUN cd /usr/src && \
    git clone https://github.com/SergiusTheBest/plog.git && \
    cd plog && \
    cmake . && \
    cmake --install .

# Install jwt-cpp
RUN cd /usr/src && \
    git clone https://github.com/jbeder/yaml-cpp && \
    cd yaml-cpp && \
    cmake . && \
    cmake --build . -j16 && \
    cmake --install .

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
    git clone -b releases/stable https://github.com/mongodb/mongo-cxx-driver.git && \
    cd mongo-cxx-driver && \
    cmake -DCMAKE_CXX_STANDARD=20 -DENABLE_UNINSTALL=OFF . && \
    cmake --build . --config Release -j 16 && \
    cmake --install . --prefix /usr/local

# Cleanup
RUN rm -rf /usr/src
