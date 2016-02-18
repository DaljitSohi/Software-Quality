#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include "Token.h"
#include <stdio.h>

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>

using namespace std;

class Bankaccount
{
private:
	bool active;
	bool student;
	int number;
	float balance;
	char name[20];


public:

	Bankaccount(string line)
	{
		
	}



	// Transaction(string file)
	// {
	// 	filename = file;
	// }	

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
