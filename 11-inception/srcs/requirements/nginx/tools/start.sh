#!/bin/bash

set -euo pipefail

#   Creating TLS 1.2 -> 1.3 certificate for https secure connection
mkdir /etc/nginx/ssl

cd /etc/nginx/ssl

openssl req -x509 -sha256 -days 3650 -nodes -newkey rsa:2048 -subj "/CN=$DOMAIN_NAME/C=CA/ST=Quebec/L=Quebec City/O=42 Network/OU=42 Quebec" -keyout rootCA.key -out rootCA.crt

openssl genrsa -out $CERT_KEY 2048

echo "
[ req ]
default_bits = 2048
prompt = no
default_md = sha256
req_extensions = req_ext
distinguished_name = dn
[ dn ]
C = CA
ST = Quebec
L = Quebec City
O = 42 Network
OU = 42 Quebec
CN = $DOMAIN_NAME
[ req_ext ]
subjectAltName = @alt_names
[ alt_names ]
DNS.1 = $DOMAIN_NAME
" > csr.conf

openssl req -new -key $CERT_KEY -out server.csr -config csr.conf

echo "
authorityKeyIdentifier=keyid,issuer
basicConstraints=CA:FALSE
keyUsage = digitalSignature, nonRepudiation, keyEncipherment, dataEncipherment
subjectAltName = @alt_names
[alt_names]
DNS.1 = $DOMAIN_NAME
" > cert.conf

openssl x509 -req -in server.csr -CA rootCA.crt -CAkey rootCA.key -CAcreateserial -out $CERT_CRT -days 365 -sha256 -extfile cert.conf

# Configuring nginx

if [ "$1" = "nginx" ]; then
    echo "
    server {
        listen  443 ssl;
        listen  [::]:443 ssl;

        server_name $DOMAIN_NAME;

        ssl_certificate     /etc/nginx/ssl/$CERT_CRT;
        ssl_certificate_key /etc/nginx/ssl/$CERT_KEY;
        ssl_protocols       TLSv1.2 TLSv1.3;
        
        root    /var/www/html;
        index   index.php;

        location / {
            autoindex   on;
            try_files   \$uri \$uri/ =404;
        }
        location ~ \.php$ {
            fastcgi_split_path_info ^(.+\.php)(/.+)$;
            fastcgi_pass            wordpress:9000;
            fastcgi_index           index.php;
            include                 fastcgi_params;
            fastcgi_param           SCRIPT_FILENAME \$document_root\$fastcgi_script_name;
            fastcgi_param           PATH_INFO \$fastcgi_path_info;
        }
    }
    " >> /etc/nginx/conf.d/default.conf
fi

cat /etc/hosts

exec "$@"

