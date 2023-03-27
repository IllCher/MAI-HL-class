CREATE DATABASE mydatabase;

USE mydatabase;

CREATE TABLE users (
  id INT NOT NULL AUTO_INCREMENT,
  username VARCHAR(50) NOT NULL,
  password VARCHAR(50) NOT NULL,
  PRIMARY KEY (id)
);

CREATE TABLE walls (
  id INT NOT NULL AUTO_INCREMENT,
  user_id INT NOT NULL,
  message TEXT NOT NULL,
  created_at TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (id),
  FOREIGN KEY (user_id) REFERENCES users(id)
);

CREATE TABLE messages (
  id INT NOT NULL AUTO_INCREMENT,
  sender_id INT NOT NULL,
  receiver_id INT NOT NULL,
  message TEXT NOT NULL,
  created_at TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (id),
  FOREIGN KEY (sender_id) REFERENCES users(id),
  FOREIGN KEY (receiver_id) REFERENCES users(id)
);

USE mydatabase;

INSERT INTO users (username, password)
VALUES ('user1', 'password1'), ('user2', 'password2');

INSERT INTO walls (user_id, message)
VALUES (1, 'Hello world!'), (2, 'How are you doing?');

INSERT INTO messages (sender_id, receiver_id, message)
VALUES (1, 2, 'Hey!'), (2, 1, 'I\'m good, thanks!');
