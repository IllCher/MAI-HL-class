FROM ubuntu:latest

RUN apt-get update &&
apt-get install -y mariadb-server &&
apt-get clean &&
rm -rf /var/lib/apt/lists/*

COPY mydatabase.sql /docker-entrypoint-initdb.d/

EXPOSE 3333

CMD ["mysqld", "--user=root", "--datadir=/var/lib/mysql", "--bind-address=0.0.0.0"]