compile:
	g++  Code/*.cpp Code/*.h -o frontend
	
clean:
	rm frontend

testing: compile
	./testing.sh frontend Current_Accounts.bank BankAccountTransaction.txt Tests

login: compile
	./testing.sh frontend Current_Accounts.bank BankAccountTransaction.txt Tests Login

withdrawal:
	./testing.sh frontend Current_Accounts.bank BankAccountTransaction.txt Tests Withdraw

create: compile
	./testing.sh frontend Current_Accounts.bank BankAccountTransaction.txt Tests Create

paybill: compile
	./testing.sh frontend Current_Accounts.bank BankAccountTransaction.txt Tests paybill

transfer: compile
	./testing.sh frontend Current_Accounts.bank BankAccountTransaction.txt Tests Transfer

deposit: compile
	./testing.sh frontend Current_Accounts.bank BankAccountTransaction.txt Tests deposit

disable: compile
	./testing.sh frontend Current_Accounts.bank BankAccountTransaction.txt Tests Disable

enable: compile
	./testing.sh frontend Current_Accounts.bank BankAccountTransaction.txt Tests Enable

changeplan: compile
	./testing.sh frontend Current_Accounts.bank BankAccountTransaction.txt Tests changePlan

delete: compile
	./testing.sh frontend Current_Accounts.bank BankAccountTransaction.txt Tests Delete

logout: compile
	./testing.sh frontend Current_Accounts.bank BankAccountTransaction.txt Tests Logout
	