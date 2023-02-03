SELECT movies.title FROM people
JOIN stars ON people.id = stars.person_id
JOIN ratings ON movies.id = ratings.movie_id
JOIN movies ON stars.movie_id = movies.id
WHERE name = "Chadwick Boseman"
ORDER BY rating DESC LIMIT 5;