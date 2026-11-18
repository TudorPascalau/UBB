CREATE TABLE users (
    id BIGINT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
    first_name VARCHAR NOT NULL,
    last_name VARCHAR NOT NULL
);

CREATE TABLE friendships (
    id1 BIGINT REFERENCES users(id) ON DELETE CASCADE,
    id2 BIGINT REFERENCES users(id) ON DELETE CASCADE,
    friends_from TIMESTAMP NOT NULL,
    PRIMARY KEY (id1, id2),
    CHECK (id1 < id2)
);

SELECT * FROM users;

SELECT * FROM friendships;
