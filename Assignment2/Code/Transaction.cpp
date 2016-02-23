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
		if(!User->IsActive())
		{
			cout << Formatting::CommandToString(cmd) <<": Invalid Account Access" << endl;	
			return;
		}

		//check if the account number is ok
		int accountNumber = Formatting::StringToInt(args[argindex++]);
		if(User->GetNumber() != accountNumber)
		{
			cout << Formatting::CommandToString(cmd) <<": Invalid Account Number" << endl;
			return;
		}

		//check if amount if correct
		float amount = Formatting::StringToFloat(args[argindex]);
		if(admin)
		{
			if(amount < 0.0f || amount > 99999.99f)
			{
				cout << Formatting::CommandToString(cmd) <<": Invalid Input" << endl;
				return;
			}
		}
		else
		{
			if(amount < 0.0f || amount > 500.00f)
			{
				cout << Formatting::CommandToString(cmd) <<": Invalid Input" << endl;
				return;
			}
		}

		//check if amount is a withdrawable amount
		float value = ((int)amount) - amount;
		if(value != 0.0f || (((int)amount) % 5) != 0)
		{
			cout << Formatting::CommandToString(cmd) <<": Invalid Input" << endl;
			return;
		}

		//check for if trans action charge is applied
		float dec = 0.0f;
		if (!admin)
		{
			if(User->IsStudent())
				dec = 0.05f;
			else
				dec = 0.10f;
		}

		//remove money if there is enough
		float rem = User->GetBalance() - amount - dec;
		if(rem >= 0.0f)
		{
			//enougn money
			User->SetBalance(rem);
			UpdateTransactions(OutFormat::MakeOutput(cmd, User->GetName(), User->GetNumber(), amount, "  "));
		}
		else 
		{
			//not enough money
			cout << Formatting::CommandToString(cmd) <<": Invalid Funds" << endl;
			return;
		}
	}
	else
	{
		cout << Formatting::CommandToString(cmd) <<": Invalid Transaction" << endl;	
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
		if(!User->IsActive())
		{
			cout << Formatting::CommandToString(cmd) <<": Invalid Account Access" << endl;	
			return;
		}

		//check if the account number is ok
		int accountNumber = Formatting::StringToInt(args[argindex++]);
		if(User->GetNumber() != accountNumber)
		{
			cout << Formatting::CommandToString(cmd) <<": Invalid Account Number" << endl;
			return;
		}

		//get second account
		int secondAccountNumber = Formatting::StringToInt(args[argindex++]);
		ToUser = SearchNumber(secondAccountNumber);
		if(ToUser == NULL)
		{
			cout << Formatting::CommandToString(cmd) <<": Invalid Account Number" << endl;
			return;
		}

		//check for inactive of second account
		if(!User->IsActive())
		{
			cout << Formatting::CommandToString(cmd) <<": Invalid Account Access" << endl;	
			return;
		}

		//check if amount is correct
		float amount = Formatting::StringToFloat(args[argindex]);
		if(admin)
		{
			if(amount < 0.0f || amount > 99999.99f)
			{
				cout << Formatting::CommandToString(cmd) <<": Invalid Input" << endl;
				return;
			}
		}
		else
		{
			if(amount < 0.0f || amount > 1000.00f)
			{
				cout << Formatting::CommandToString(cmd) <<": Invalid Input" << endl;
				return;
			}
		}

		//check for if trans action charge is applied
		float dec = 0.0f;
		if (!admin)
		{
			if(User->IsStudent())
				dec = 0.05f;
			else
				dec = 0.10f;
		}

		//remove money if there is enough
		float rem = User->GetBalance() - amount - dec;
		if(rem >= 0.0f)
		{
			//enougn money
			User->SetBalance(rem);
			UpdateTransactions(OutFormat::MakeOutput(cmd, User->GetName(), User->GetNumber(), amount, "  "));
			UpdateTransactions(OutFormat::MakeOutput(cmd, ToUser->GetName(), ToUser->GetNumber(), amount, "  "));
		}
		else 
		{
			//not enough money
			cout << Formatting::CommandToString(cmd) <<": Invalid Funds" << endl;
			return;
		}
	}
	else
	{
		cout << Formatting::CommandToString(cmd) <<": Invalid Transaction" << endl;	
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
		if(!User->IsActive())
		{
			cout << Formatting::CommandToString(cmd) <<": Invalid Account Access" << endl;	
			return;
		}

		//check if the account number is ok
		int accountNumber = Formatting::StringToInt(args[argindex++]);
		if(User->GetNumber() != accountNumber)
		{
			cout << Formatting::CommandToString(cmd) <<": Invalid Account Number" << endl;
			return;
		}

		//extract company and check if it is a good company name
		string Company = args[argindex++];
		if(Company.compare("EC") != 0 && Company.compare("CQ") != 0 && Company.compare("TV") != 0)
		{
			cout << Formatting::CommandToString(cmd) <<": Invalid Company Name" << endl;
			return;
		}

		//check if amount if correct
		float amount = Formatting::StringToFloat(args[argindex]);
		if(admin)
		{
			if(amount < 0.0f || amount > 99999.99f)
			{
				cout << Formatting::CommandToString(cmd) <<": Invalid Input" << endl;
				return;
			}
		}
		else
		{
			if(amount < 0.0f || amount > 2000.00f)
			{
				cout << Formatting::CommandToString(cmd) <<": Invalid Input" << endl;
				return;
			}
		}

		//check for if trans action charge is applied
		float dec = 0.0f;
		if (!admin)
		{
			if(User->IsStudent())
				dec = 0.05f;
			else
				dec = 0.10f;
		}

		//remove money if there is enough
		float rem = User->GetBalance() - amount - dec;
		if(rem >= 0.0f)
		{
			//enougn money
			User->SetBalance(rem);
			UpdateTransactions(OutFormat::MakeOutput(cmd, User->GetName(), User->GetNumber(), amount, Company));
		}
		else 
		{
			//not enough money
			cout << Formatting::CommandToString(cmd) <<": Invalid Funds" << endl;
			return;
		}
	}
	else
	{
		cout << Formatting::CommandToString(cmd) <<": Invalid Transaction" << endl;	
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
		if(!User->IsActive())
		{
			cout << Formatting::CommandToString(cmd) <<": Invalid Account Access" << endl;	
			return;
		}

		//check if the account number is ok
		int accountNumber = Formatting::StringToInt(args[argindex++]);
		if(User->GetNumber() != accountNumber)
		{
			cout << Formatting::CommandToString(cmd) <<": Invalid Account Number" << endl;
			return;
		}

		//check if amount if correct
		float amount = Formatting::StringToFloat(args[argindex]);
		if(amount < 0.0f || amount > 99999.99f)
		{
			cout << Formatting::CommandToString(cmd) <<": Invalid Input" << endl;
			return;
		}


		//check for if trans action charge is applied
		float dec = 0.0f;
		if (!admin)
		{
			if(User->IsStudent())
				dec = 0.05f;
			else
				dec = 0.10f;
		}

		User->SetBalance(User->GetBalance() - dec);
		UpdateTransactions(OutFormat::MakeOutput(cmd, User->GetName(), User->GetNumber(), amount, "  "));		
	}
	else
	{
		cout << Formatting::CommandToString(cmd) <<": Invalid Transaction" << endl;	
	}
}

void Transaction::Create(string* args, int len, int cmd)
{
	if(logedin)
	{
		if(admin)
		{
			int argindex = 0;	
			string name = args[argindex++];
			//check if doesn't exits
			if(!CheckForBankAccount(name))
			{	
				if(name.length() > 20)
				{
					name = name.substr(0, 20);
					cout << Formatting::CommandToString(cmd) <<": Shortened Character Amount" << endl;
				}
				
				//check if amount if correct
				float amount = Formatting::StringToFloat(args[argindex]);
				if(amount < 0.0f || amount > 99999.99f)
				{
					cout << Formatting::CommandToString(cmd) <<": Invalid Input" << endl;
					return;
				}

				int accountNumber = SearchForNewNumber();
				if(accountNumber <= 0)
				{
					return;
				}

				UpdateTransactions(OutFormat::MakeOutput(cmd, name, accountNumber, amount, "  "));
			}
			else
			{
				cout << Formatting::CommandToString(cmd) <<": Invalid AccessB" << endl;
				return;
			}
		}
		else
		{
			cout << Formatting::CommandToString(cmd) <<": Invalid Access" << endl;	
			return;
		}
	}
	else
	{
		cout << Formatting::CommandToString(cmd) <<": Invalid Transaction" << endl;	
	}
}

void Transaction::Delete(string* args, int len, int cmd)
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
			if(!User->IsActive())
			{
				cout << Formatting::CommandToString(cmd) <<": Invalid Account Access" << endl;	
				return;
			}

			//check if the account number is ok
			int accountNumber = Formatting::StringToInt(args[argindex++]);
			if(User->GetNumber() != accountNumber)
			{
				cout << Formatting::CommandToString(cmd) <<": Invalid Account Number" << endl;
				return;
			}

			User->DeleteAccount();
			UpdateTransactions(OutFormat::MakeOutput(cmd, User->GetName(), User->GetNumber(), 0, "  "));
		}
		else
		{
			cout << Formatting::CommandToString(cmd) <<": Invalid Access" << endl;	
		}
	}
	else
	{
		cout << Formatting::CommandToString(cmd) <<": Invalid Transaction" << endl;	
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
			if(!User->IsActive())
			{
				cout << Formatting::CommandToString(cmd) <<": Invalid Account Access" << endl;	
				return;
			}

			//check if the account number is ok
			int accountNumber = Formatting::StringToInt(args[argindex++]);
			if(User->GetNumber() != accountNumber)
			{
				cout << Formatting::CommandToString(cmd) <<": Invalid Account Number" << endl;
				return;
			}

			User->Disable();
			UpdateTransactions(OutFormat::MakeOutput(cmd, User->GetName(), User->GetNumber(), 0, "  "));
		}
		else
		{
			cout << Formatting::CommandToString(cmd) <<": Invalid Access" << endl;	
		}
	}
	else
	{
		cout << Formatting::CommandToString(cmd) <<": Invalid Transaction" << endl;	
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
			if(!User->IsActive())
			{
				cout << Formatting::CommandToString(cmd) <<": Invalid Account Access" << endl;	
				return;
			}

			//check if the account number is ok
			int accountNumber = Formatting::StringToInt(args[argindex++]);
			if(User->GetNumber() != accountNumber)
			{
				cout << Formatting::CommandToString(cmd) <<": Invalid Account Number" << endl;
				return;
			}

			UpdateTransactions(OutFormat::MakeOutput(cmd, User->GetName(), User->GetNumber(), 0, User->ChangePlan()));
		}
		else
		{
			cout << Formatting::CommandToString(cmd) <<": Invalid Access" << endl;	
			return;
		}
	}
	else
	{
		cout << Formatting::CommandToString(cmd) <<": Invalid Transaction" << endl;	
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
			if(!User->IsActive())
			{
				cout << Formatting::CommandToString(cmd) <<": Invalid Account Access" << endl;	
				return;
			}

			//check if the account number is ok
			int accountNumber = Formatting::StringToInt(args[argindex++]);
			if(User->GetNumber() != accountNumber)
			{
				cout << Formatting::CommandToString(cmd) <<": Invalid Account Number" << endl;
				return;
			}

			User->Enable();
			UpdateTransactions(OutFormat::MakeOutput(cmd, User->GetName(), User->GetNumber(), 0, "  "));

		}
		else
		{
			cout << Formatting::CommandToString(cmd) <<": Invalid Access" << endl;	
		}
	}
	else
	{
		cout << Formatting::CommandToString(cmd) <<": Invalid Transaction" << endl;	
	}
}

void Transaction::Login(string* args, int len, int cmd)
{
	// cout << args[0].compare("standard") << " " << args[0] << " " << len << endl ;
	if(logedin)
	{
		cout << Formatting::CommandToString(cmd) <<": Invalid Transaction" << endl;
	}
	else if(args[0].compare("standard") == 0)
	{
		// cout << "test" << endl;
		if(len > 2)
		{
			cout << Formatting::CommandToString(cmd) <<": Invalid Transaction" << endl;	
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
			admin = false;
			UpdateTransactions(OutFormat::MakeOutput(cmd, currentAccount->GetName(), currentAccount->GetNumber(), 0.0f, "S"));
		}
	}
	else if(args[0].compare("admin") == 0)
	{
		// cout << "test2" << len << endl;
		if(len > 1)
		{
			cout << Formatting::CommandToString(cmd) <<": Invalid Transaction" << endl;	
		}
		else
		{
			currentAccount = NULL;
			logedin = true;
			admin = true;
			UpdateTransactions(OutFormat::MakeOutput(cmd, "", 0, 0.0f, "A"));
		}
		
	}
	else
	{
		cout << Formatting::CommandToString(cmd) <<": Invalid Transaction" << endl;	
	}
}

void Transaction::Logout()
{
	if(logedin)
	{
		if(admin)
		{
			UpdateTransactions(OutFormat::MakeOutput(0, "", 0, 0.0f, "A"));	
		}
		else
		{
			UpdateTransactions(OutFormat::MakeOutput(0, currentAccount->GetName(), currentAccount->GetNumber(), 0.0f, "S"));
		}
		currentAccount = NULL;
		
		ofstream out(filename.c_str(), fstream::app);
		out << bankTransactions;
		out.close();
		bankTransactions = "";
		
		logedin = false;
		admin = false;
	}
	else
	{
		cout << "logout: Invalid Transaction" << endl;
	}
}