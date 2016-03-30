compile:
	clear
	javac -cp junit-4.10.jar *.java

run: compile
	java backend BankAccountTransaction.txt Master_Accounts.bank
clean:
	rm *.class 
	rm MasterBankAccountsFile.bank CurrentBankAccounts.bank

test: compile
	java -cp junit-4.10.jar:. org.junit.runner.JUnitCore AllTests
