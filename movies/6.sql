SELECT ROUND(AVG(rating), 2) From ratings WHERE id IN (SELECT id FROM movies WHERE year = 2012);