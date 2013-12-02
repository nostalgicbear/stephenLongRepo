# A list of all players ordered by their position
select player.lastName, player.position, player.club
from player join contract on player.contract_Id = contract.contractID
order by position