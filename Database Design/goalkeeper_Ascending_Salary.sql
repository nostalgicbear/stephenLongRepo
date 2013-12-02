#Filters the staff to list only managers with a contract ending before a specified date
# Ordered based on the managers surname
select player.lastName, player.position, player.club, contract.salary
from player join contract on player.contract_Id = contract.contractID
where player.position = 'Goalkeeper'
order by salary