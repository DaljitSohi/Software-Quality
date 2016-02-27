/*****************************
*see's if it is command line or a file
*spilt the data by line's
*gets a token out of the line
*send into the interperter to 
*execute the command
*****************************/
#include "Formatting.h"
#include "Token.h"
#include "FileOutFormat.h"
#include "Interpeter.h"
#include "Transaction.h"

#include <stdio.h>

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>


using namespace std;

/**
*create a token out of the line input and send the token to the interpeter for execution
*line - the text for the input stream
*action - the interpeter for the exection of the commands
*/
void OnCompleteLine(string line, Transaction& action)
{
	Token t = Token(line);
	Interpeter::InterpetToken(t, action);
}

int main(int argc, char** argv)
{
	bool isfile = false;
	istream* input = &cin;
	char c;
	string line;
	string account_file;
	string transaction_file;

	if(argc > 2){

		account_file = argv[1];
		transaction_file = argv[2];
	}
	else
	{
		cout << "" << endl;
		return 1;
	}

	if(argc > 3)
	{
		input = new fstream(argv[3], fstream::in);
		isfile = true;
	}

	Transaction action(transaction_file, account_file);//"BankAccountTransaction.txt", "Current_Accounts.bank");

	while(input->get(c))
	{
		if(c == '\n' || c == '\r')
		{
			if(line.length() == 0)
				continue;

			OnCompleteLine(line, action);
			line = "";
			continue;
		}
		line += c;
	}
	if(line != "")
	{
		OnCompleteLine(line, action);
		line = "";
	}

	if(isfile)
		((fstream*)input)->close();
	return 0;
}