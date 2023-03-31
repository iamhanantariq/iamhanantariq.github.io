Select distinct name from people JOIN stars ON stars.person_id = people.id
where movie_id in (SELECT movie_id FROM stars JOIN people ON stars.person_id = people.id
where person_id in (SELECT id from people where name = "Kevin Bacon" and birth = 1958)) and not name = "Kevin Bacon";
