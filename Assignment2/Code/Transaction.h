/*****************************
*execute the commands of the system
*holds all the current bank account
*****************************/
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "Token.h"
#include "BankAccount.h"
#include "FileOutFormat.h"
#include <stdio.h>

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>


using namespace std;

class Transaction
{
private:
	string bankTransactions;
	string filename;
	bool admin;
	bool logedin;
	//more datatypes for current bank account
	BankAccount* accounts = NULL;
	int accountslen;

	BankAccount* currentAccount;

	void Sort(BankAccount*& account, int length, int index = 19)
	{
		if(index == -1)
			return;

		BankAccount* sorted = new BankAccount[length];
		
		int countBuffer[256];
		memset(countBuffer, 0, 256 * sizeof(int));

		for (int cnt = 0; cnt < length; cnt++)
		{ 
			char radix = account[cnt].getName()[index];
			countBuffer[radix]++;
		}

		for (int cnt = 1; cnt < 256; cnt++)
		{
			countBuffer[cnt] += countBuffer[cnt - 1];
		}

		for (int cnt = length - 1; cnt >= 0; cnt--)
		{
			char radix = account[cnt].getName()[index];
			sorted[countBuffer[radix] - 1] = account[cnt];
			countBuffer[radix] -= 1;
			
		}

		delete [] account;
		account = sorted;

		Sort(account, length, index - 1);
	}

	int binarySearchName(string value)
	{
		return _binarySearchName(value, 0, accountslen - 1);
	}

	int _binarySearchName(string value, int low, int high)
	{
		if (high < low)
			return -1;
		int middle = (high + low) / 2;
		if (accounts[middle].getSName().compare(value) == 0)
			return middle;
		else if (accounts[middle].getSName().compare(value) >= 0)
			return _binarySearchName(value, low, middle - 1);
		else
			return _binarySearchName(value, middle + 1, high);
	}

	void updateTransactions(string trans)
	{
		bankTransactions += trans + "\n";
	}

	BankAccount* GetBankAccount(string value, int cmd)
	{
		int index = binarySearchName(value);
		if(index < 0 || index >= accountslen)
		{
			cout << Formatting::commandToNumber(cmd) <<": Invalid Account Holder Name" << endl;	
			return NULL;
		}
		return &accounts[index];
	}

public:

	Transaction(string outfile, string infile)
	{
		filename = outfile;

		ifstream input(infile.c_str(), ifstream::in);

		char c;
		string line;
		
		string all = "";
		int len = 0;
		while(input.get(c))
		{
			if(c == '\n' || c == '\r')
			{
				if(line.length() == 0)
					continue;
				size_t found = line.find("END_OF_FILE");

				if(found != string::npos)
				{
					break;
				}
				else
				{
					all += line + "\t";
					len++;
					line = "";
				}
				continue;
			}
			line += c;
		}
		accountslen = len;
		input.close();

		accounts = new BankAccount[len];
		string value;
		size_t last = 0;
		size_t found = 0;

		for(int cnt = 0; cnt < len; cnt++)
		{
			found = all.find('\t', last);
			value = all.substr(last, found-last);
			
			last = found+1;
			accounts[cnt] = BankAccount(value);
		}
		Sort(accounts, accountslen);

		admin = false;
		logedin = false;
	}

	~Transaction()
	{
		if(accounts != NULL)
			delete [] accounts;
		// cout << "Deleted" << endl;
		currentAccount = NULL;
	}

	void Withdrawal(string* args, int len, int cmd);
	void Transfer(string* args, int len, int cmd);
	void Paybill(string* args, int len, int cmd);
	void Deposit(string* args, int len, int cmd);
	void Create(string* args, int len, int cmd);
	void Delete(string* args, int len, int cmd);
	void Disable(string* args, int len, int cmd);
	void Changeplan(string* args, int len, int cmd);
	void Enable(string* args, int len, int cmd);
	void Login(string* args, int len, int cmd);
	void Logout();
};

#endif
//00000 END_OF_FILE          A 00000.00 N