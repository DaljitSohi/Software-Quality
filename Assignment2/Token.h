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
	int cmdint;
	string* args = NULL;
	int lenargs;

public:

	Token(string line)
	{
		lenargs = 0;
		int arglen = Formatting::characterFrequency(' ', line);
		
		if(arglen == 0)
		{
			command = line;
			cmdint = Formatting::commandToNumber(command);
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
				cmdint = Formatting::commandToNumber(command);
			}
			last = found;
			args = new string[arglen];
			lenargs = arglen;
			int cnt = 0;
			while((found = line.find(wanted, last+1)) != string::npos)
			{
				args[cnt++] = line.substr(last+1, found -last);
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


	int getCommandNumber()
	{
		return cmdint;
	}

	string getCommandName()
	{
		return command;
	}

	int getArgumentLength()
	{
		return lenargs;
	}

	string* getArgument()
	{
		return args;
	}

	friend std::ostream& operator<<(std::ostream& os, const Token& t)
	{
	    // write obj to stream
	    os << "Command: " << t.command << endl;
		for(int cnt = 0; cnt < t.lenargs; cnt++)
		{
			os << "Arg[" << cnt << "]: " << t.args[cnt] << endl;
		}
	    return os;
	}

};



#endif