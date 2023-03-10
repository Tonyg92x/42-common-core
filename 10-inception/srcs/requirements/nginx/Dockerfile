FROM debian:buster

WORKDIR /tmp

COPY tools/*    ./

RUN apt-get update && apt-get upgrade -y;\
    apt-get install -y nginx openssl;\
    apt-get clean autoclean && apt-get autoremove --yes

ARG DOMAIN_NAME
ARG CERT_CRT
ARG CERT_KEY

ENV DOMAIN_NAME=$DOMAIN_NAME
ENV CERT_CRT=$CERT_CRT
ENV CERT_KEY=$CERT_KEY

ENTRYPOINT ["./start.sh"]

CMD [ "nginx", "-g", "daemon off;" ]

#   Documentation
EXPOSE 443
