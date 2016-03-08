/*****************************
*parses a line and adds splits the line according to the spaces
*store the current bank account information for one bankaccount
*****************************/
#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include "Token.h"
#include <string.h>
#include <string>

using namespace std;

class BankAccount
{
private:
	bool active;
	bool student;
	bool deleted;
	int number;
	float balance;
	char name[20];


public:

	BankAccount()
	{
		//set defult values for a bankaccount
		active = student = deleted = false;
		number = 0;
		balance = 0.0f;
		strcpy(name, "                    ");
	}

	BankAccount(string line)
	{
		string wanted = " ";
		size_t last = 0;
		string value;
		
		//get number in the first 5 character
		value = line.substr(last, 5);
		number = Formatting::StringToInt(value);
		last += 5;

		//get name in the next 20 characters
		last++; // accout for space
		strcpy(name,  line.substr(last, 20).c_str());
		size_t found = line.find(" ", last);
		name[found-last] = '\0';
		last += 20;


		//get status in the next character
		last++; // accout for space
		value = line.substr(last, 1);
		if(value.compare("A") == 0)
		{
			active = true;
		}
		else
		{
			active = false;
		}
		last++;

		//get balance in the next 8 charaters
		last++; // accout for space
		value = line.substr(last, 8);
		balance = Formatting::StringToFloat(value);
		last += 8;

		//get plan in the last character
		last++; // accout for space
		value = line.substr(last, 1);
		if(value.compare("S") == 0)
		{
			student = true;
		}
		else
		{
			student = false;
		}
		last++;

		deleted = false;
	}


	BankAccount(const BankAccount& account)
	{
		active = account.active;
		student = account.student;
		number = account.number;
		balance = account.balance;
		strcpy(name, account.name);
		deleted = account.deleted;
	}


	void Enable()
	{
		active = true;
	}
	
	void Disable()
	{
		active = false;
	}

	/**
	*checks if the bank account is both active and not deat
	*/
	bool IsActive()
	{
		return (active && !deleted);
	}

	bool IsDeleted()
	{
		return deleted;
	}

	void DeleteAccount()
	{
		deleted = true;
		// cout << "deleted" << endl;
	}

	/**
	*change the plan for student to nonstudent and vice versa
	*return - the misc data for the type of plan
	*/
	string ChangePlan()
	{
		if (student)
		{
			student = false;
			return "NP";
		}
		else
		{
			student = true;
			return "SP";

		}
	}

	bool IsStudent()
	{
		return student;
	}

	int GetNumber()
	{
		return number;
	}

	float GetBalance()
	{
		return balance;
	}

	void SetBalance(float amount)
	{
		balance = amount;
	}
	

	char* GetName()
	{
		return name;
	}

	string GetSName()
	{
		return string(name);
	}
};

#endif
