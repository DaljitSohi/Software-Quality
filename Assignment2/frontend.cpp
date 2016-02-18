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

void OnCompleteLine(string line, Transaction& action)
{
	Token t = Token(line);
	// cout << t;
	Interpeter::InterpetToken(t, action);
}



int main(int argc, char** argv)
{
	bool isfile = false;
	istream* input = &cin;
	char c;
	string line;
	Transaction action("BankAccountTransaction.txt");

	if(argc > 1){
		input = new fstream(argv[1], fstream::in);
		isfile = true;
	}

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