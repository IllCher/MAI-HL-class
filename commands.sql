CREATE DATABASE stud;
use stud;
show tables;
CREATE TABLE IF NOT EXISTS `User` (`id` INT NOT NULL AUTO_INCREMENT,
`first_name` VARCHAR(256) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
`last_name` VARCHAR(256) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
`email` VARCHAR(256) CHARACTER SET utf8 COLLATE utf8_unicode_ci NULL,
`birth_date` VARCHAR(10) CHARACTER SET utf8 COLLATE utf8_unicode_ci NULL,
`login` VARCHAR(10) CHARACTER SET utf8 COLLATE utf8_unicode_ci NULL,
`password` VARCHAR(10) CHARACTER SET utf8 COLLATE utf8_unicode_ci NULL,
PRIMARY KEY (`id`),KEY `fn` (`first_name`),KEY `ln` (`last_name`));

describe User;

INSERT INTO User (first_name, last_name, email, birth_date, login, password) VALUES ('John', 'Doe', 'Joe@gmail.com', '01.03.2023', 'CoolBoy', 'hehehehe');

CREATE TABLE IF NOT EXISTS `Chat` (`id` INT NOT NULL AUTO_INCREMENT,
`receiver_id` INT(100) ,
`sender_id` INT(100),
`message` VARCHAR(1000) CHARACTER SET utf8 COLLATE utf8_unicode_ci NULL,
PRIMARY KEY (`id`),KEY `ri` (`receiver_id`),KEY `si` (`sender_id`));

describe Chat;

INSERT INTO Chat (receiver_id, sender_id, message) VALUES ('1', '1', 'ggggggggggg');

CREATE TABLE IF NOT EXISTS `Wall` (`id` INT NOT NULL AUTO_INCREMENT,
`name` VARCHAR(256) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
`login` VARCHAR(256) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
`description` VARCHAR(256) CHARACTER SET utf8 COLLATE utf8_unicode_ci NULL,
`data` VARCHAR(1000) CHARACTER SET utf8 COLLATE utf8_unicode_ci NULL,
`creation_date` VARCHAR(10) CHARACTER SET utf8 COLLATE utf8_unicode_ci NULL,
`comments` VARCHAR(1000) CHARACTER SET utf8 COLLATE utf8_unicode_ci NULL,
PRIMARY KEY (`id`));

describe Wall;

INSERT INTO Wall (name, login, description, data, creation_date, comments) VALUES ('Jo32hn', 'CoolBoy', 'Jfddssd', 'uyuytutyutyuty', '11.05.2023', 'ppppppyytr');