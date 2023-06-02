FROM debian:latest

RUN apt-get update && \
    apt-get install -y locales && \
    rm -rf /var/lib/apt/lists/* && \
	localedef -i en_US -c -f UTF-8 -A /usr/share/locale/locale.alias en_US.UTF-8

RUN apt-get update && \
    apt-get install -y supervisor
RUN mkdir -p /var/log/supervisor
COPY supervisord.conf /etc/supervisor/conf.d/supervisord.conf

ENV LANG en_US.utf8

COPY aws-mock.properties /etc
COPY aws-mock /usr/bin
COPY libs/*.94 /usr/lib
COPY libs/libawsmock* /usr/lib

RUN mkdir -p /tmp/awsmock/data && \
    mkdir -p /tmp/awsmock/data/db && \
    mkdir -p /tmp/awsmock/log

EXPOSE 4567 4567

CMD ["/usr/bin/supervisord"]