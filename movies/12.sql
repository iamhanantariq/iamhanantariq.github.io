SELECT title FROM movies JOIN stars ON stars.movie_id = movies.id JOIN people ON stars.person_id = people.id
WHERE title IN
(SELECT title FROM movies JOIN stars ON stars.movie_id = movies.id JOIN people ON stars.person_id = people.id WHERE name = "Johnny Depp")
AND name = "Helena Bonham Carter";
