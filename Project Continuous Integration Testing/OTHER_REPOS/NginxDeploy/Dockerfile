# inherit from the php:7.1-apache image from docker hub
FROM nexus.informatik.haw-hamburg.de/php:7.1-apache
# create data Directory and set permissions
RUN mkdir -p /var/www/html/data
RUN mkdir -p /var/www/html/img/
RUN mkdir -p /var/www/html/bootstrap/
RUN chown -R www-data:www-data /var/www/html/data



RUN apt-get update

RUN apt-get install curl unzip -y
RUN apt-get install libcurl4-openssl-dev pkg-config libssl-dev -y
RUN pecl install mongodb

RUN docker-php-ext-install mbstring
RUN docker-php-ext-enable mongodb
RUN curl --silent --show-error https://getcomposer.org/installer | php
RUN php /var/www/html/composer.phar require mongodb/mongodb m4tthumphrey/php-gitlab-api php-http/guzzle6-adapter
RUN php /var/www/html/composer.phar install
RUN service apache2 restart
# copies your php files
COPY . /var/www/html/
COPY img/ /var/www/html/img/
COPY bootstrap/ /var/www/html/bootstrap/
