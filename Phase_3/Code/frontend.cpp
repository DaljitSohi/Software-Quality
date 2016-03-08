/*****************************
*see's if it is command line or a file
*spilt the data by line's
*gets a token out of the line
*send into the interperter to 
*execute the command
*****************************/
#include "Token.h"
#include "Interpeter.h"
#include "Transaction.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/**
*create a token out of the line input and send the token to the interpeter for execution
*line - the text for the input stream
*action - the interpeter for the exection of the commands
*/
void OnCompleteLine(string line, Transaction& action)
{
	//get token for the input line
	Token t = Token(line);

	//run that token through the interpeter, to be executed
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

	//check to make sure there is a minimum number of arguments
	if(argc > 2){
		//get the account and transaction file names
		account_file = argv[1];
		transaction_file = argv[2];
	}
	else
	{
		//Write out error if there aren't enough command line arguments
		cout << "Not Enough Command line Arguments. Please Include the Bank Account's file and the Bank Transaction File." << endl;
		return 1;
	}

	//check to see if the there is a file or command line input for the input
	if(argc > 3)
	{
		input = new fstream(argv[3], fstream::in);
		isfile = true;
	}

	//create the object at executes the command, and writes ot the transaction file
	Transaction action(transaction_file, account_file);

	//when there is still more output, get next character
	while(input->get(c))
	{
		//for each line, parse that line
		if(c == '\n' || c == '\r')
		{
			//make sure the line isn't empty
			if(line.length() == 0)
				continue;

			//call line to be interpeted and executed, clear line after
			OnCompleteLine(line, action);
			line = "";
			continue;
		}
		line += c;
	}

	//if there is till more characters left in the buffer, run the buffer
	if(line != "")
	{
		OnCompleteLine(line, action);
		line = "";
	}

	//close the file if there was a filled used
	if(isfile)
		((fstream*)input)->close();
	delete input;
	return 0;
}