# Selects all players (first + last names) where contract ends before 1/1/2014
select player.firstName, player.lastName , contract.endDate
from player join contract on contract.contractID = player.contract_Id
where contract.endDate < 20150101
order by endDate