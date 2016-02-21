
compile:
	g++  Code/*.cpp Code/*.h -o frontend

run: onetest

regularrun: compile
	clear
	./frontend Tests/Create/create_admin_only/test.txt
	
clean:
	rm frontend

one3test: compile
	./oneTest.sh frontend BankAccountTransaction.txt Tests/changePlan/ad-np-A
	cat Tests/changePlan/ad-np-A/*

one2test: compile
	./oneTest.sh frontend BankAccountTransaction.txt Tests/Transfer/standard_transfer_fivehund
	cat Tests/Transfer/standard_transfer_fivehund/*


onetest: compile
	./oneTest.sh frontend BankAccountTransaction.txt Tests/Create/create_admin_only
	cat Tests/Create/create_admin_only/*

localtext: compile
	./frontend test.tst

testing: compile
	./testing.sh frontend BankAccountTransaction.txt Tests

login: compile
	./testing.sh frontend BankAccountTransaction.txt Tests Login

login2:
	./testing.sh frontend BankAccountTransaction.txt Tests Login

withdrawal: compile
	./testing.sh frontend BankAccountTransaction.txt Tests Withdraw

create: compile
	./testing.sh frontend BankAccountTransaction.txt Tests Create

paybill: compile
	./testing.sh frontend BankAccountTransaction.txt Tests paybill

transfer: compile
	./testing.sh frontend BankAccountTransaction.txt Tests Transfer

deposit: compile
	./testing.sh frontend BankAccountTransaction.txt Tests deposit

disable: compile
	./testing.sh frontend BankAccountTransaction.txt Tests Disable

enable: compile
	./testing.sh frontend BankAccountTransaction.txt Tests Enable

changeplan: compile
	./testing.sh frontend BankAccountTransaction.txt Tests changePlan