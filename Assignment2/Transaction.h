/*****************************
*execute the commands of the system
*holds all the current bank account
*****************************/
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "Token.h"
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
	string bankTransaction;
	string filename;
	bool admin;
	bool logedin;
	 //more datatypes for current bank account

public:

	Transaction(string file)
	{
		filename = file;
	}	

	void Withdrawal(string* args, int len);
	void Transfer(string* args, int len);
	void Paybill(string* args, int len);
	void Deposit(string* args, int len);
	void Create(string* args, int len);
	void Delete(string* args, int len);
	void Disable(string* args, int len);
	void Changeplan(string* args, int len);
	void Enable(string* args, int len);
	void Login(string* args, int len);
	void Logout();
};

#endif
