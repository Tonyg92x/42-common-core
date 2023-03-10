#!/bin/bash

set -euo pipefail

echo "start of wordpress install script"

#   Waiting for mariadb to be online
if [ "$1" = "php-fpm7.3" ]; then

    for i in {0..30}; do
        if mariadb -hmariadb -u$DATABASE_USERNAME -p$DATABASE_PASSWORD --database=$DATABASE_NAME <<<'SELECT 1;' &>/dev/null; then
            break
        fi
        sleep 2
    done

    if [ "$i" = 30 ]; then
        echo "Can't connect to database"
        exit 1
    fi

    if [ ! -f "/var/www/html/wp-config.php" ]; then

        unzip wordpress-6.0.3.zip
        rm wordpress-6.0.3.zip
        mv wordpress//* html/
        rm -rf wordpress

        #   Configuring WordPress
        echo "Starting to configure WordPress"

        wp config create --allow-root \
            --dbname=$DATABASE_NAME \
            --dbuser=$DATABASE_USERNAME \
            --dbpass=$DATABASE_PASSWORD \
            --dbhost=mariadb \
            --dbcharset="utf8" \
            --dbcollate="utf8_general_ci" \
            --path="/var/www/html"

        #   Install WordPress

        echo "Starting to install WordPress"

        wp core install --allow-root \
            --title="Wordpress" \
            --admin_name="${DATABASE_USERNAME}" \
            --admin_password="${DATABASE_PASSWORD}" \
            --admin_email="${DATABASE_EMAIL}" \
            --skip-email \
            --url="${DOMAIN_NAME}" \
            --path="/var/www/html"

        #   Creating the user for WordPress

        echo "Creating a user for WordPress"

        wp user create --allow-root \
            $WP_USERNAME \
            $WP_EMAIL \
            --role=author \
            --user_pass=$WP_PASSWORD \
            --path="/var/www/html"
    fi
fi
echo "Congragulation, WordPress is ready!"

exec "$@"
