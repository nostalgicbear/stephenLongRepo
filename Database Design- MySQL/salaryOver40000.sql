select player.lastName, contract.salary 
from player join contract on contract.contractID = player.contract_Id
where contract.salary > 40000
ORDER by lastName