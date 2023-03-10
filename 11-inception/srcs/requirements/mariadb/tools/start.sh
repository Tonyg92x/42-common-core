#!/bin/bash

set -euo pipefail

if [ "$1" = 'mysqld' ]; then
    # Set the datadir
    sed -Ei "/^datadir/c datadir                 = $DATABASE_DIR" /etc/mysql/mariadb.conf.d/50-server.cnf
    if [ ! -f "$DATABASE_DIR/initdb.sql" ]; then
        chown -R mysql:mysql $DATABASE_DIR
        mysql_install_db --user=mysql --datadir=$DATABASE_DIR --rpm --skip-test-db > /dev/null
        cat > "$DATABASE_DIR/initdb.sql" <<EOF
CREATE DATABASE IF NOT EXISTS $DATABASE_NAME CHARACTER SET utf8 COLLATE utf8_general_ci;
CREATE USER IF NOT EXISTS '$DATABASE_USERNAME'@'%' IDENTIFIED BY '$DATABASE_PASSWORD';
GRANT ALL PRIVILEGES ON $DATABASE_NAME.* TO '$DATABASE_USERNAME'@'%';
ALTER USER 'root'@'localhost' IDENTIFIED BY '$DATABASE_ROOTPASSWORD';
FLUSH PRIVILEGES;
EOF
fi
    mysqld --skip-networking &
        for i in {0..30}; do
            if mariadb -u root -proot --database=mysql <<<'SELECT 1;' &> /dev/null; then
                break
            fi
            sleep 1
        done
        if [ "$i" = 30 ]; then
            echo "Error on server start up"
            exit 1
        fi
        echo "Starting mariadb"
        mariadb -u root -proot < "$DATABASE_DIR/initdb.sql" && killall mysqld
    fi

exec "$@"
