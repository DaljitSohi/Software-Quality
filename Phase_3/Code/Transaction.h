/*****************************
*execute the commands of the system
*holds all the current bank account
*****************************/
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "BankAccount.h"
#include "Formatting.h"
#include "FileOutFormat.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Transaction
{
private:
	string transactionBuffer;
	string filename;
	bool admin;
	bool logedin;

	BankAccount* accounts = NULL;
	int accounts_length;

	BankAccount* currentAccount;
	float withAmount, payAmount, transferAmount;

	/**
	*Sorts the bank account by name using radix sort
	*list - pointer to the bank account
	*sorted - pointer to the list of going to be sorted charactes
	*length - the length of the array of bank accounts
	*index - the postion of the radix sort
	*/
	void Sort(BankAccount*& list, BankAccount*& sorted, int* countBuffer, int length, int index = 19)
	{
		//stop if index is passed first character
		if(index == -1)
			return;
		
		//clear the count buffer
		memset(countBuffer, 0, 256 * sizeof(int));
		
		//increment the the count buffer, at each position by the account name at a index
		for (int cnt = 0; cnt < length; cnt++)
		{
			char radix = list[cnt].GetName()[index];
			countBuffer[radix]++;
		}
		
		//sum up the countbuffer
		for (int cnt = 1; cnt < 256; cnt++)
		{
			countBuffer[cnt] += countBuffer[cnt - 1];
		}
		
		//in revese order of the array, place the account in sorted order
		for (int cnt = length - 1; cnt >= 0; cnt--)
		{
			char radix = list[cnt].GetName()[index];
			sorted[countBuffer[radix] - 1] = list[cnt];
			countBuffer[radix] -= 1;
		}
		
		//swap the unsorted and sorted list
		BankAccount* temp = list;
		list = sorted;
		sorted = temp;
		
		//calll the sort at one character index higher
		Sort(list, sorted, countBuffer, length, index - 1);
	}

	/**
	*Wraper for binary search of name
	*value - name you want to search for
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
		//check if the search has gone to far
		if (high < low)
			return -1;
		//gets middle of array, checks if the match, if not, call itself at higher or lower.
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
		//for each account number, checks if the bank account number matches 
		for(int cnt = 0; cnt < accounts_length; cnt++)
		{
			if(accounts[cnt].GetNumber() == number)
				return &accounts[cnt];
		}
		return NULL;
	}

	/**
	* takes the frequecy of the account number, and linearly searchs throught the 
	*frequency array to find the next avaiable bank account number
	*return - new unique bank account number, -1 if no more avaiable numbers
	*/
	int SearchForNewNumber()
	{
		//array of the maximum size of accounts
		int accNum[99999];
		//set all values to 0
		memset(accNum, 0, 99999 * sizeof(int));
		//for each account, increase the array at index of the account's number, if that account isn't deleted
		for(int cnt = 0; cnt < accounts_length; cnt++)
			if(!accounts[cnt].IsDeleted())
				accNum[accounts[cnt].GetNumber()]++;

		//starting at 1(because 0 is admin), check each to see if there is an account number free
		for(int cnt = 1; cnt < 99999; cnt++)
			if(accNum[cnt] < 1)
				return cnt;
		//return -1 if no free number
		return -1;
	}
	/**
	*add the banktransaction ouput to a buffer
	*/
	void UpdateTransactions(string trans)
	{
		transactionBuffer += trans + "\n";
	}

	/**
	* wraper for binary search, checking if the name exsits in the bank account database
	*value - the string wanted to search
	*return true if the name exists, false if it doesn't
	*/
	bool CheckForBankAccount(string value)
	{
		//search for the index of the account base on the name
		int index = BinarySearchName(value);
		//no account if, the number is -1 bigger that the number of accounts or the account has been deleted
		if(index < 0 || index >= accounts_length || accounts[index].IsDeleted())
			return false;
		return true;
	}

	/**
	*wraper function to check if a name has a bank account
	*value - the account holder name
	*cmd - the command number of the command that invoked the function
	*return pointer to the bank account if it exisits else return Null
	*/
	BankAccount* GetBankAccount(string name, int cmd)
	{
		//search for the index of the account base on the name
		int index = BinarySearchName(name);
		//no account if, the number is -1 bigger that the number of accounts or the account has been deleted
		if(index < 0 || index >= accounts_length || accounts[index].IsDeleted())
		{
			//wrtie out error, and return nothing
			cout << Formatting::CommandToString(cmd) <<": Invalid Account Holder Name" << endl;	
			return NULL;
		}
		return &accounts[index];		
	}


	/**
	* Check to see if the to deducte a charge to a transaction
	*User - the user making the transaction
	*return the amount of the charge
	*/
	float GetTransactionCharge(BankAccount *& User)
	{
		if (admin)
		{	
			return 0.0f;
		}
		else
		{
			if(User->IsStudent())
				return 0.05f;
			else
				return 0.10f;
		}
	}


public:

	Transaction(string outfile, string infile)
	{
		filename = outfile;

		//open bank account's file
		ifstream input(infile.c_str(), ifstream::in);

		char c;
		string line;
		string all = "";
		int len = 0;
		bool endoffile = false;

		//reads in all of the file
		while(input.get(c))
		{
			//splits the file by line
			if(c == '\n' || c == '\r')
			{
				// do nothing if nothing in the line
				if(line.length() == 0)
					continue;
				//check for END_OF_FILE
				size_t found = line.find("END_OF_FILE");

				//if end of appears stop taking input
				if(found != string::npos)
				{
					endoffile = true;
					break;
				}
				else
				{
					// add input to a variable for after ande split lines by tabs
					all += line + "\t";
					len++;
					line = "";
				}
				continue;
			}
			//add characters to line
			line += c;
		}
		//set the length of the number of accounts, and close the banka accounts file.
		accounts_length = len;
		input.close();

		//create ne bank accountfile
		accounts = new BankAccount[len];
		string value;
		size_t last = 0;
		size_t found = 0;


		//for each banka account create a num instance of the bankaccount class
		for(int cnt = 0; cnt < len; cnt++)
		{
			//find ad retrive the bank account line.
			found = all.find('\t', last);
			value = all.substr(last, found-last);
			
			//account for the tab in the string and create the instance of the bankaccount
			last = found+1;
			accounts[cnt] = BankAccount(value);
		}

		//Radix sorting variables
		BankAccount* sorted = new BankAccount[accounts_length];
		int countBuffer[256];
		//sort the bankaccount by name
		Sort(accounts, sorted, countBuffer, accounts_length);

		//delete the old unsorted array
		delete [] sorted;

		//set admin access and logedin access
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


	/**
	* Each Function Below, the Name of the Funciton corresponds to the
	* Transactoin name.
	* args - the argument for the command
	* len - the length of the arguments
	* cmd - the command number of the function
	* **Note: logout doesn't need any arguments
	*/
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