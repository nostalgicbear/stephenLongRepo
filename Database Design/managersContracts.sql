#Filters the staff to list only managers with a contract ending before a specified date
# Ordered based on the managers surname
select staff.lastName, staff.firstName , contract.startDate, contract.endDate
from staff join contract on contract.contractID = staff.contract_Identifier
where contract.endDate > 20140101 and staff.position = 'Manager'
order by lastName