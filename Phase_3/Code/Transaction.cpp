#include "Transaction.h"

void Transaction::Withdrawal(string* args, int len, int cmd)
{
	//check for if logged in and if there is the right amount for argumentss
	if(logedin && (len == 2 || len == 3))
	{
		//variable for the current user
		BankAccount* User;
		int argindex = 0;

		//check for admin access
		if(admin)
		{
			//get currect bankaccount if null no account name exits
			User = GetBankAccount(args[argindex++], cmd);
			if(User == NULL)
				return;
		}
		else
		{
			//if standard login, use current acccount
			User = currentAccount;
		}

		//check for inactive
		if(!User->IsActive())
		{
			cout << Formatting::CommandToString(cmd) <<": Invalid Account Access" << endl;	
			return;
		}

		//check if the account number is ok, by get next argument
		int accountNumber = Formatting::StringToInt(args[argindex++]);
		if(User->GetNumber() != accountNumber)
		{
			cout << Formatting::CommandToString(cmd) <<": Invalid Account Number" << endl;
			return;
		}

		//check if amount if correct, getting the last argument
		float amount = Formatting::StringToFloat(args[argindex]);
		if(admin)
		{
			//check if amount is between 0 < amount < 99999
			if(amount < 0.0f || amount > 99999.99f)
			{
				cout << Formatting::CommandToString(cmd) <<": Invalid Input" << endl;
				return;
			}
		}
		else
		{
			//check if amount is between 0 < amount < 500
			if(amount < 0.0f || amount > 500.00f)
			{
				cout << Formatting::CommandToString(cmd) <<": Invalid Input" << endl;
				return;
			}

			//check if amount has already ben take out
			if(withAmount >= 500.0f || withAmount + amount > 500.0f)
			{
				cout << Formatting::CommandToString(cmd) <<": Invalid Input" << endl;
				return;	
			}
			withAmount += amount;
		}

		//check if amount is a withdrawable amount, must be a factor of 5
		float value = ((int)amount) - amount;
		if(value != 0.0f || (((int)amount) % 5) != 0)
		{
			cout << Formatting::CommandToString(cmd) <<": Invalid Input" << endl;
			return;
		}

		//check for if trans action charge is applied
		float dec = GetTransactionCharge(User);
		

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
		//if not logged in
		cout << Formatting::CommandToString(cmd) <<": Invalid Transaction" << endl;	
	}
}

void Transaction::Transfer(string* args, int len, int cmd)
{
	//check for if logged in and if there is the right amount for argumentss
	if(logedin && (len == 4 || len == 3))
	{
	
		//variable for the current user
		BankAccount* User;
		BankAccount* ToUser;
		int argindex = 0;

		//check for admin access
		if(admin)
		{
			//get currect bankaccount if null no account name exits
			User = GetBankAccount(args[argindex++], cmd);
			if(User == NULL)
				return;
		}
		else
		{
			//if standard login, use current acccount
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
			if(amount <= 0.0f || amount > 99999.99f)
			{
				cout << Formatting::CommandToString(cmd) <<": Invalid Input" << endl;
				return;
			}
		}
		else
		{
			if(amount <= 0.0f || amount > 1000.00f)
			{
				cout << Formatting::CommandToString(cmd) <<": Invalid Input" << endl;
				return;
			}


			//check if amount has already ben take out
			if(transferAmount >= 1000.0f || transferAmount + amount > 1000.0f)
			{
				cout << Formatting::CommandToString(cmd) <<": Invalid Input" << endl;
				return;	
			}
			transferAmount += amount;
		}

		//check for if trans action charge is applied
		float dec = GetTransactionCharge(User);
		
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
	//check for if logged in and if there is the right amount for argumentss
	if(logedin && (len == 4 || len == 3))
	{
		BankAccount* User;
		int argindex = 0;
		//check for admin access
		if(admin)
		{
			//get currect bankaccount if null no account name exits
			User = GetBankAccount(args[argindex++], cmd);
			if(User == NULL)
				return;
		}
		else
		{
			//if standard login, use current acccount
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

			//check if amount has already ben take out
			if(payAmount >= 2000.0f || payAmount + amount > 2000.0f)
			{
				cout << Formatting::CommandToString(cmd) <<": Invalid Input" << endl;
				return;	
			}
			payAmount += amount;
		}

		//check for if trans action charge is applied
		float dec = GetTransactionCharge(User);

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
	//check for if logged in and if there is the right amount for argumentss
	if(logedin && (len == 2 || len == 3))
	{
		BankAccount* User;
		int argindex = 0;
		//check for admin access
		if(admin)
		{

			//get currect bankaccount if null no account name exits
			User = GetBankAccount(args[argindex++], cmd);
			if(User == NULL)
				return;
		}
		else
		{
			//if standard login, use current acccount
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
		if(amount <= 0.0f || amount > 99999.99f)
		{
			cout << Formatting::CommandToString(cmd) <<": Invalid Input" << endl;
			return;
		}


		//check for if trans action charge is applied
		float dec = GetTransactionCharge(User);

		//set the new balace and write the output
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
	//check for if logged in and if there is the right amount for argumentss
	if(logedin && len == 2)
	{
		if(admin)
		{	
			//admin only
			int argindex = 0;	
			string name = args[argindex++];
			
			//check if doesn't exits
			if(!CheckForBankAccount(name))
			{	
				//name must be less than 20, it shorteds it if it is above 20
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

				//Search for avaliable number, if none avaliable, error out
				int accountNumber = SearchForNewNumber();
				if(accountNumber <= 0)
				{
					cout << Formatting::CommandToString(cmd) <<": Invalid Transaction" << endl;
					return;
				}

				//write the output
				UpdateTransactions(OutFormat::MakeOutput(cmd, name, accountNumber, amount, "  "));
			}
			else
			{
				cout << Formatting::CommandToString(cmd) <<": Invalid Access" << endl;
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
	//check for if logged in and if there is the right amount for argumentss
	if(logedin && len == 2)
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

			//set the account to deleted and write the value out
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
	//check for if logged in and if there is the right amount for argumentss
	if(logedin && len == 2)
	{
		if(admin)
		{
			//admin only
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

			//disable the user and write the command
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
	//check for if logged in and if there is the right amount for argumentss
	if(logedin &&  len == 2 )
	{
		if(admin)
		{
			//admin only
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

			//write out the success of the command
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
	//check for if logged in and if there is the right amount for argumentss
	if(logedin && len == 2)
	{
		if(admin)
		{
			//admin only
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

			//enable the account and write the success of the command
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
	//check for if logged in and if there is the right amount for argumentss
	if(logedin &&  len > 0)
	{
		cout << Formatting::CommandToString(cmd) <<": Invalid Transaction" << endl;
	}
	else if(args[0].compare("standard") == 0)
	{
		//for standard account login
		if(len > 2)
		{
			//make sure of only standard and a name, no extra data
			cout << Formatting::CommandToString(cmd) <<": Invalid Transaction" << endl;	
		}
		else
		{
			//get the firs agument for the name
			string value = args[1];

			//check for account, if null don't log in
			currentAccount = GetBankAccount(value, cmd);
			if(currentAccount == NULL)
			{
				cout << Formatting::CommandToString(cmd) <<": Invalid Account Holder Name" << endl;			
				return;
			}

			//set login and admin, the write out the command
			withAmount = payAmount = transferAmount = 0.0f;
			logedin = true;
			admin = false;
			UpdateTransactions(OutFormat::MakeOutput(cmd, currentAccount->GetName(), currentAccount->GetNumber(), 0.0f, "S"));
		}
	}
	else if(args[0].compare("admin") == 0)
	{
		//for admin login
		if(len > 1)
		{
			//make sure only "admin" on the line, no extra data
			cout << Formatting::CommandToString(cmd) <<": Invalid Transaction" << endl;	
		}
		else
		{
			//set account, login, admin, the write the command
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
	//check for if logged in
	if(logedin)
	{
		//write out the respective logout
		if(admin)
		{
			UpdateTransactions(OutFormat::MakeOutput(0, "", 0, 0.0f, "A"));	
		}
		else
		{
			UpdateTransactions(OutFormat::MakeOutput(0, currentAccount->GetName(), currentAccount->GetNumber(), 0.0f, "S"));
		}
		//get ride of the current bankaccount
		currentAccount = NULL;
		
		//wrtie the currect transaction to the file
		ofstream out(filename.c_str(), fstream::app);
		out << transactionBuffer;
		out.close();

		//clear the transaciton buffer and logout
		transactionBuffer = "";
		logedin = false;
		admin = false;
	}
	else
	{
		cout << "logout: Invalid Transaction" << endl;
	}
}