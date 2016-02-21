/*****************************
*parses a line and adds splits the line according to the spaces
*store the current bank account information for one bankaccount
*****************************/
#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include "Token.h"
#include <stdio.h>
#include <string.h>

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>

using namespace std;

class BankAccount
{
private:
	bool active;
	bool student;
	int number;
	float balance;
	char name[20];


public:

	BankAccount()
	{
		active = student = false;
		number = 0;
		balance = 0.0f;
		strcpy(name, "                    ");
	}

	BankAccount(string line)
	{
		int arglen = Formatting::characterFrequency(' ', line);
		string wanted = " ";
		size_t last = 0;
		string value;
		
		//get number
		value = line.substr(last, 5);
		number = Formatting::stringtoint(value);
		last += 5;

		//get name
		last++;
		strcpy(name,  line.substr(last, 20).c_str());
		size_t found = line.find(" ", last);
		name[found-last] = '\0';
		last += 20;


		//get status
		last++;
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

		//get balance
		last++;
		value = line.substr(last, 8);
		balance = Formatting::stringtofloat(value);
		last += 8;

		//get plan
		last++;
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
	}


	BankAccount(const BankAccount& account)
	{
		active = account.active;
		student = account.student;
		number = account.number;
		balance = account.balance;
		strcpy(name, account.name);
	}


	void Enable()
	{
		active = true;
	}
	
	void Disable()
	{
		active = false;
	}

	bool isActive()
	{
		return active;
	}

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

	bool isStudent()
	{
		return student;
	}

	int getNumber()
	{
		return number;
	}

	float getBalance()
	{
		return balance;
	}

	void setBalance(float amount)
	{
		balance = amount;
	}
	

	char* getName()
	{
		return name;
	}

	string getSName()
	{
		return string(name);
	}


	friend std::ostream& operator<<(std::ostream& os, const BankAccount& t)
	{
	    // write obj to stream
	    os << "Number: " << t.number;
	    os << " Name: " << t.name;
	    os << " Active: " << t.active;
	    os << " Balance: " << t.balance;
	    os << " Plan: " << t.student;
	    return os;
	}

};

#endif
