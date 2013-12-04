# Calculates the average team age for Newcastle United. A statistic that is commonly used in football
SELECT AVG(age) as average_Team_Age from player
where player.club = 'Newcastle United'