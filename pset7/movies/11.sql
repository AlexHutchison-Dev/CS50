SELECT DISTINCT title
From people join stars ON people.id = stars.person_id
JOIN ratings ON ratings.movie_id= stars.movie_id
JOIN movies ON movies.id = stars.movie_id
Where name = "Chadwick Boseman"
ORDER BY "rating" DESC LIMIT 5;
