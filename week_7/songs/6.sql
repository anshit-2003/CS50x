SELECT name FROM SONGS WHERE artist_id IN (SELECT id FROM artists WHERE name IS "Post Malone");