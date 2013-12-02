SELECT firstName, lastName, club FROM player
UNION
SELECT firstName, lastName, club FROM staff
order by lastName