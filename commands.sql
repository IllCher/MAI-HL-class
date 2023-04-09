CREATE DATABASE stud;
use stud;
show tables;

create table Chat
(
    id          int auto_increment
        primary key,
    receiver_id int(100)                              null,
    sender_id   int(100)                              null,
    message     varchar(1000) collate utf8_unicode_ci null
);

create index ri
    on Chat (receiver_id);

create index si
    on Chat (sender_id);

create table User
(
    id         int auto_increment
        primary key,
    first_name varchar(256) collate utf8_unicode_ci not null,
    last_name  varchar(256) collate utf8_unicode_ci not null,
    email      varchar(256) collate utf8_unicode_ci null,
    birth_date varchar(10) collate utf8_unicode_ci  null,
    login      varchar(10) collate utf8_unicode_ci  null,
    password   varchar(10) collate utf8_unicode_ci  null
);

create index fn
    on User (first_name);

create index ln
    on User (last_name);

create table Wall
(
    id            int auto_increment
        primary key,
    name          varchar(256) collate utf8_unicode_ci  not null,
    login         varchar(256) collate utf8_unicode_ci  not null,
    description   varchar(256) collate utf8_unicode_ci  null,
    data          varchar(1000) collate utf8_unicode_ci null,
    creation_date varchar(10) collate utf8_unicode_ci   null,
    comments      longtext collate utf8_unicode_ci      null
);




