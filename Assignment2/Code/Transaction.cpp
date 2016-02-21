#include "Transaction.h"

void Transaction::Withdrawal(string* args, int len, int cmd)
{
	if(logedin)
	{
		BankAccount* User;
		int argindex = 0;
		//check for admin access
		if(admin)
		{
			User = GetBankAccount(args[argindex++], cmd);
			if(User == NULL)
				return;
		}
		else
		{
			User = currentAccount;
		}

		//check for inactive
		if(!User->isActive())
		{
			cout << Formatting::commandToNumber(cmd) <<": Invalid Account Access" << endl;	
			return;
		}

		//check if the account number is ok
		int accountNumber = Formatting::stringtoint(args[argindex++]);
		if(User->getNumber() != accountNumber)
		{
			cout << Formatting::commandToNumber(cmd) <<": Invalid Account Number" << endl;
			return;
		}

		//check if amount if correct
		float amount = Formatting::stringtofloat(args[argindex]);
		if(admin)
		{
			if(amount < 0.0f || amount > 99999.99f)
			{
				cout << Formatting::commandToNumber(cmd) <<": Invalid Input" << endl;
				return;
			}
		}
		else
		{
			if(amount < 0.0f || amount > 500.00f)
			{
				cout << Formatting::commandToNumber(cmd) <<": Invalid Input" << endl;
				return;
			}
		}

		//check if amount is a withdrawable amount
		float value = ((int)amount) - amount;
		if(value != 0.0f || (((int)amount) % 5) != 0)
		{
			cout << Formatting::commandToNumber(cmd) <<": Invalid Input" << endl;
			return;
		}

		//check for if trans action charge is applied
		float dec = 0.0f;
		if (!admin)
		{
			if(User->isStudent())
				dec = 0.05f;
			else
				dec = 0.10f;
		}

		//remove money if there is enough
		float rem = User->getBalance() - amount - dec;
		if(rem >= 0.0f)
		{
			//enougn money
			User->setBalance(rem);
			updateTransactions(outFormat::makeOutput(cmd, User->getName(), User->getNumber(), amount, "  "));
		}
		else 
		{
			//not enough money
			cout << Formatting::commandToNumber(cmd) <<": Invalid Funds" << endl;
			return;
		}
	}
	else
	{
		cout << Formatting::commandToNumber(cmd) <<": Invalid Transaction" << endl;	
	}
}

void Transaction::Transfer(string* args, int len, int cmd)
{
	if(logedin)
	{
		BankAccount* User;
		BankAccount* ToUser;
		int argindex = 0;
		//check for admin access
		if(admin)
		{
			User = GetBankAccount(args[argindex++], cmd);
			if(User == NULL)
				return;
		}
		else
		{
			User = currentAccount;
		}

		//check for inactive
		if(!User->isActive())
		{
			cout << Formatting::commandToNumber(cmd) <<": Invalid Account Access" << endl;	
			return;
		}

		//check if the account number is ok
		int accountNumber = Formatting::stringtoint(args[argindex++]);
		if(User->getNumber() != accountNumber)
		{
			cout << Formatting::commandToNumber(cmd) <<": Invalid Account Number" << endl;
			return;
		}

		//get second account
		int secondAccountNumber = Formatting::stringtoint(args[argindex++]);
		ToUser = SearchNumber(secondAccountNumber);
		if(ToUser == NULL)
		{
			cout << Formatting::commandToNumber(cmd) <<": Invalid Account Number" << endl;
			return;
		}

		//check for inactive of second account
		if(!User->isActive())
		{
			cout << Formatting::commandToNumber(cmd) <<": Invalid Account Access" << endl;	
			return;
		}

		//check if amount is correct
		float amount = Formatting::stringtofloat(args[argindex]);
		if(admin)
		{
			if(amount < 0.0f || amount > 99999.99f)
			{
				cout << Formatting::commandToNumber(cmd) <<": Invalid Input" << endl;
				return;
			}
		}
		else
		{
			if(amount < 0.0f || amount > 1000.00f)
			{
				cout << Formatting::commandToNumber(cmd) <<": Invalid Input" << endl;
				return;
			}
		}

		//check for if trans action charge is applied
		float dec = 0.0f;
		if (!admin)
		{
			if(User->isStudent())
				dec = 0.05f;
			else
				dec = 0.10f;
		}

		//remove money if there is enough
		float rem = User->getBalance() - amount - dec;
		if(rem >= 0.0f)
		{
			//enougn money
			User->setBalance(rem);
			updateTransactions(outFormat::makeOutput(cmd, User->getName(), User->getNumber(), amount, "  "));
			updateTransactions(outFormat::makeOutput(cmd, ToUser->getName(), ToUser->getNumber(), amount, "  "));
		}
		else 
		{
			//not enough money
			cout << Formatting::commandToNumber(cmd) <<": Invalid Funds" << endl;
			return;
		}
	}
	else
	{
		cout << Formatting::commandToNumber(cmd) <<": Invalid Transaction" << endl;	
	}
}

void Transaction::Paybill(string* args, int len, int cmd)
{
	if(logedin)
	{
		BankAccount* User;
		int argindex = 0;
		//check for admin access
		if(admin)
		{
			User = GetBankAccount(args[argindex++], cmd);
			if(User == NULL)
				return;
		}
		else
		{
			User = currentAccount;
		}

		//check for inactive
		if(!User->isActive())
		{
			cout << Formatting::commandToNumber(cmd) <<": Invalid Account Access" << endl;	
			return;
		}

		//check if the account number is ok
		int accountNumber = Formatting::stringtoint(args[argindex++]);
		if(User->getNumber() != accountNumber)
		{
			cout << Formatting::commandToNumber(cmd) <<": Invalid Account Number" << endl;
			return;
		}

		//extract company and check if it is a good company name
		string Company = args[argindex++];
		if(Company.compare("EC") != 0 && Company.compare("CQ") != 0 && Company.compare("TV") != 0)
		{
			cout << Formatting::commandToNumber(cmd) <<": Invalid Company Name" << endl;
			return;
		}

		//check if amount if correct
		float amount = Formatting::stringtofloat(args[argindex]);
		if(admin)
		{
			if(amount < 0.0f || amount > 99999.99f)
			{
				cout << Formatting::commandToNumber(cmd) <<": Invalid Input" << endl;
				return;
			}
		}
		else
		{
			if(amount < 0.0f || amount > 2000.00f)
			{
				cout << Formatting::commandToNumber(cmd) <<": Invalid Input" << endl;
				return;
			}
		}

		//check for if trans action charge is applied
		float dec = 0.0f;
		if (!admin)
		{
			if(User->isStudent())
				dec = 0.05f;
			else
				dec = 0.10f;
		}

		//remove money if there is enough
		float rem = User->getBalance() - amount - dec;
		if(rem >= 0.0f)
		{
			//enougn money
			User->setBalance(rem);
			updateTransactions(outFormat::makeOutput(cmd, User->getName(), User->getNumber(), amount, Company));
		}
		else 
		{
			//not enough money
			cout << Formatting::commandToNumber(cmd) <<": Invalid Funds" << endl;
			return;
		}
	}
	else
	{
		cout << Formatting::commandToNumber(cmd) <<": Invalid Transaction" << endl;	
	}
}

void Transaction::Deposit(string* args, int len, int cmd)
{
	if(logedin)
	{
		BankAccount* User;
		int argindex = 0;
		//check for admin access
		if(admin)
		{
			User = GetBankAccount(args[argindex++], cmd);
			if(User == NULL)
				return;
		}
		else
		{
			User = currentAccount;
		}

		//check for inactive
		if(!User->isActive())
		{
			cout << Formatting::commandToNumber(cmd) <<": Invalid Account Access" << endl;	
			return;
		}

		//check if the account number is ok
		int accountNumber = Formatting::stringtoint(args[argindex++]);
		if(User->getNumber() != accountNumber)
		{
			cout << Formatting::commandToNumber(cmd) <<": Invalid Account Number" << endl;
			return;
		}

		//check if amount if correct
		float amount = Formatting::stringtofloat(args[argindex]);
		if(amount < 0.0f || amount > 99999.99f)
		{
			cout << Formatting::commandToNumber(cmd) <<": Invalid Input" << endl;
			return;
		}


		//check for if trans action charge is applied
		float dec = 0.0f;
		if (!admin)
		{
			if(User->isStudent())
				dec = 0.05f;
			else
				dec = 0.10f;
		}

		User->setBalance(User->getBalance() - dec);
		updateTransactions(outFormat::makeOutput(cmd, User->getName(), User->getNumber(), amount, "  "));		
	}
	else
	{
		cout << Formatting::commandToNumber(cmd) <<": Invalid Transaction" << endl;	
	}
}

void Transaction::Create(string* args, int len, int cmd)
{
	if(logedin)
	{
		if(admin)
		{


		}
		else
		{
			cout << Formatting::commandToNumber(cmd) <<": Invalid Access" << endl;	
		}
	}
	else
	{
		cout << Formatting::commandToNumber(cmd) <<": Invalid Transaction" << endl;	
	}
}

void Transaction::Delete(string* args, int len, int cmd)
{
	if(logedin)
	{
		if(admin)
		{


		}
		else
		{
			cout << Formatting::commandToNumber(cmd) <<": Invalid Access" << endl;	
		}
	}
	else
	{
		cout << Formatting::commandToNumber(cmd) <<": Invalid Transaction" << endl;	
	}
}

void Transaction::Disable(string* args, int len, int cmd)
{
	if(logedin)
	{
		if(admin)
		{
			BankAccount* User;
			int argindex = 0;
			//check for admin access
			User = GetBankAccount(args[argindex++], cmd);
			if(User == NULL)
				return;
			
			//check for inactive
			if(!User->isActive())
			{
				cout << Formatting::commandToNumber(cmd) <<": Invalid Account Access" << endl;	
				return;
			}

			//check if the account number is ok
			int accountNumber = Formatting::stringtoint(args[argindex++]);
			if(User->getNumber() != accountNumber)
			{
				cout << Formatting::commandToNumber(cmd) <<": Invalid Account Number" << endl;
				return;
			}

			User->Disable();
			updateTransactions(outFormat::makeOutput(cmd, User->getName(), User->getNumber(), 0, "  "));
		}
		else
		{
			cout << Formatting::commandToNumber(cmd) <<": Invalid Access" << endl;	
		}
	}
	else
	{
		cout << Formatting::commandToNumber(cmd) <<": Invalid Transaction" << endl;	
	}
}

void Transaction::Changeplan(string* args, int len, int cmd)
{
	if(logedin)
	{
		if(admin)
		{
			BankAccount* User;
			int argindex = 0;
			//check for admin access
			User = GetBankAccount(args[argindex++], cmd);
			if(User == NULL)
				return;
			
			//check for inactive
			if(!User->isActive())
			{
				cout << Formatting::commandToNumber(cmd) <<": Invalid Account Access" << endl;	
				return;
			}

			//check if the account number is ok
			int accountNumber = Formatting::stringtoint(args[argindex++]);
			if(User->getNumber() != accountNumber)
			{
				cout << Formatting::commandToNumber(cmd) <<": Invalid Account Number" << endl;
				return;
			}
			
			updateTransactions(outFormat::makeOutput(cmd, User->getName(), User->getNumber(), 0, User->ChangePlan()));
		}
		else
		{
			cout << Formatting::commandToNumber(cmd) <<": Invalid Access" << endl;	
			return;
		}
	}
	else
	{
		cout << Formatting::commandToNumber(cmd) <<": Invalid Transaction" << endl;	
		return;
	}
}

void Transaction::Enable(string* args, int len, int cmd)
{
	if(logedin)
	{
		if(admin)
		{
			BankAccount* User;
			int argindex = 0;
			//check for admin access
			User = GetBankAccount(args[argindex++], cmd);
			if(User == NULL)
				return;
			
			//check for inactive
			if(!User->isActive())
			{
				cout << Formatting::commandToNumber(cmd) <<": Invalid Account Access" << endl;	
				return;
			}

			//check if the account number is ok
			int accountNumber = Formatting::stringtoint(args[argindex++]);
			if(User->getNumber() != accountNumber)
			{
				cout << Formatting::commandToNumber(cmd) <<": Invalid Account Number" << endl;
				return;
			}

			User->Enable();
			updateTransactions(outFormat::makeOutput(cmd, User->getName(), User->getNumber(), 0, "  "));

		}
		else
		{
			cout << Formatting::commandToNumber(cmd) <<": Invalid Access" << endl;	
		}
	}
	else
	{
		cout << Formatting::commandToNumber(cmd) <<": Invalid Transaction" << endl;	
	}
}

void Transaction::Login(string* args, int len, int cmd)
{
	// cout << args[0].compare("standard") << " " << args[0] << " " << len << endl ;
	if(logedin)
	{
		cout << Formatting::commandToNumber(cmd) <<": Invalid Transaction" << endl;
	}
	else if(args[0].compare("standard") == 0)
	{
		// cout << "test" << endl;
		if(len > 2)
		{
			cout << Formatting::commandToNumber(cmd) <<": Invalid Transaction" << endl;	
		}
		else
		{
			string value = args[1];

			currentAccount = GetBankAccount(value, cmd);

			if(currentAccount == NULL)
			{
				return;
			}
			logedin = true;
			updateTransactions(outFormat::makeOutput(cmd, currentAccount->getName(), currentAccount->getNumber(), 0.0f, "S"));
		}
	}
	else if(args[0].compare("admin") == 0)
	{
		// cout << "test2" << len << endl;
		if(len > 1)
		{
			cout << Formatting::commandToNumber(cmd) <<": Invalid Transaction" << endl;	
		}
		else
		{
			currentAccount = NULL;
			logedin = true;
			admin = true;
			updateTransactions(outFormat::makeOutput(cmd, "", 0, 0.0f, "A"));
		}
		
	}
	else
	{
		cout << Formatting::commandToNumber(cmd) <<": Invalid Transaction" << endl;	
	}
}

void Transaction::Logout()
{
	if(logedin)
	{
		if(admin)
		{
			updateTransactions(outFormat::makeOutput(0, "", 0, 0.0f, "A"));	
		}
		else
		{
			updateTransactions(outFormat::makeOutput(0, currentAccount->getName(), currentAccount->getNumber(), 0.0f, "S"));
		}
		currentAccount = NULL;
		
		ofstream out(filename.c_str(), fstream::app);
		out << bankTransactions;
		out.close();
		bankTransactions = "";
		
		logedin = false;
	}
	else
	{
		cout << "logout: Invalid Transaction" << endl;
	}
}
