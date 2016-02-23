/*****************************
*data structure for the commandline input of the program
*breaks the line up by spaces, and formats the data
*****************************/
#ifndef TOKEN_H
#define TOKEN_H

#include "Formatting.h"

#include <stdio.h>

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>


using namespace std;

class Token
{
private:
	string command;
	int commandNumber;
	string* args = NULL;
	int args_length;

public:

	Token(string line)
	{
		args_length = 0;
		int arglen = Formatting::CharacterFrequency(' ', line);
		
		if(arglen == 0)
		{
			command = line;
			commandNumber = Formatting::CommandToNumber(command);
		}
		else
		{
			string wanted = " ";
			size_t last = 0;
			size_t found = line.find(wanted);

			//find command
			if(found != string::npos)
			{
				command = line.substr(0, found);
				commandNumber = Formatting::CommandToNumber(command);
			}
			last = found;
			args = new string[arglen];
			args_length = arglen;
			int cnt = 0;
			while((found = line.find(wanted, last+1)) != string::npos)
			{
				args[cnt++] = line.substr(last+1, found - last - 1);
				last = found;
			}
			args[cnt++] = line.substr(last+1, line.length() - last);
		}
	}

	~Token()
	{
		if(args != NULL)
			delete [] args;
	}


	int GetCommandNumber()
	{
		return commandNumber;
	}

	string GetCommandName()
	{
		return command;
	}

	int GetArgumentLength()
	{
		return args_length;
	}

	string* GetArgument()
	{
		return args;
	}
};




#endif