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
	int accounts_length;

	BankAccount* currentAccount;

	/**
	*Sorts the bank account by name using radix sort
	*account - pointer to the bank account
	*length - the length of the array of bank accounts
	*index - the postion of the radix sort
	*/

	void Sort(BankAccount*& list, BankAccount*& sorted, int* countBuffer, int length, int index = 19)
	{
		if(index == -1)
			return;
		
		memset(countBuffer, 0, 256 * sizeof(int));
		
		for (int cnt = 0; cnt < length; cnt++)
		{
			char radix = list[cnt].GetName()[index];
			countBuffer[radix]++;
		}
		
		for (int cnt = 1; cnt < 256; cnt++)
		{
			countBuffer[cnt] += countBuffer[cnt - 1];
		}
		
		for (int cnt = length - 1; cnt >= 0; cnt--)
		{
			char radix = list[cnt].GetName()[index];
			sorted[countBuffer[radix] - 1] = list[cnt];
			countBuffer[radix] -= 1;
		}
		
		BankAccount* temp = list;
		list = sorted;
		sorted = temp;
		
		Sort(list, sorted, countBuffer, length, index - 1);
	}

	// void Sort(BankAccount*& account, int length, int index = 19)
	// {
	// 	if(index == -1)
	// 		return;
		
	// 	BankAccount* sorted = new BankAccount[length];
		
	// 	int countBuffer[256];
	// 	memset(countBuffer, 0, 256 * sizeof(int));
		
	// 	for (int cnt = 0; cnt < length; cnt++)
	// 	{
	// 		char radix = account[cnt].GetName()[index];
	// 		countBuffer[radix]++;
	// 	}
		
	// 	for (int cnt = 1; cnt < 256; cnt++)
	// 	{
	// 		countBuffer[cnt] += countBuffer[cnt - 1];
	// 	}
		
	// 	for (int cnt = length - 1; cnt >= 0; cnt--)
	// 	{
	// 		char radix = account[cnt].GetName()[index];
	// 		sorted[countBuffer[radix] - 1] = account[cnt];
	// 		countBuffer[radix] -= 1;
	// 	}
		
	// 	delete [] account;
	// 	account = sorted;
		
	// 	Sort(account, length, index - 1);
	// }

	/**
	*Wraper for binary search of name
	*vaule - name you want to search for
	*return - the binary search result
	*/
	int BinarySearchName(string value)
	{
		return _BinarySearchName(value, 0, accounts_length - 1);
	}

	/**
	*uses binary search to find the account index
	*value - the search value
	*low - binary search low index
	*high - binary search high index
	*return - the index of the bank account, if doesn't exits, return -1
	*/
	int _BinarySearchName(string value, int low, int high)
	{
		if (high < low)
			return -1;
		int middle = (high + low) / 2;
		if (accounts[middle].GetSName().compare(value) == 0)
			return middle;
		else if (accounts[middle].GetSName().compare(value) >= 0)
			return _BinarySearchName(value, low, middle - 1);
		else
			return _BinarySearchName(value, middle + 1, high);
	}


	/**
	*A simple linear search of the account to find on that has a matching account number
	*number - the account search number
	*return - Null if no account with that number, return pointer to account if it exists
	*/
	BankAccount* SearchNumber(int number)
	{
		for(int cnt = 0; cnt < accounts_length; cnt++)
		{
			if(accounts[cnt].GetNumber() == number)
				return &accounts[cnt];
		}
		return NULL;
	}

	/**
	* thanks the frequecy of the account number, and linearly searchs throught the 
	*frequency array to find the next avaiable bank account number
	*return - new unique bank account number, -1 if no more avaiable numbers
	*/
	int SearchForNewNumber()
	{
		int accNum[99999];
		memset(accNum, 0, 99999 * sizeof(int));
		for(int cnt = 0; cnt < accounts_length; cnt++)
			if(!accounts[cnt].IsDeleted())
				accNum[accounts[cnt].GetNumber()]++;
		
		for(int cnt = 1; cnt < 99999; cnt++)
			if(accNum[cnt] < 1)
				return cnt;
		return -1;
	}

	void UpdateTransactions(string trans)
	{
		bankTransactions += trans + "\n";
	}

	/**
	*wraper function to check if a name has a bank account
	*value - the account holder name
	*cmd - the command number of the command that invoked the function
	*return pointer to the bank account if it exisits else return Null
	*/
	BankAccount* GetBankAccount(string value, int cmd)
	{
		int index = BinarySearchName(value);
		if(index < 0 || index >= accounts_length || accounts[index].IsDeleted())
		{
			cout << Formatting::CommandToString(cmd) <<": Invalid Account Holder Name" << endl;	
			return NULL;
		}
		return &accounts[index];
	}

	bool CheckForBankAccount(string value)
	{
		int index = BinarySearchName(value);
		if(index < 0 || index >= accounts_length)
			return false;
		return true;
	}

	float GetTransactionCharge(BankAccount *& User)
	{
		float dec = 0.0f;
		if (admin)
		{	
			return 0.0f;
		}
		else
		{
			if(User->IsStudent())
				dec = 0.05f;
			else
				dec = 0.10f;
		}

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
		bool endoffile = false;
		while(input.get(c))
		{
			if(c == '\n' || c == '\r')
			{
				if(line.length() == 0)
					continue;
				size_t found = line.find("END_OF_FILE");

				if(found != string::npos)
				{
					endoffile = true;
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
		// cout << all << endl;
		accounts_length = len;
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
			// cout << value << endl;
			accounts[cnt] = BankAccount(value);
			// cout << accounts[cnt] << endl;
		}


		BankAccount* sorted = new BankAccount[accounts_length];
		int countBuffer[256];

		Sort(accounts, sorted, countBuffer, accounts_length);

		delete [] sorted;

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