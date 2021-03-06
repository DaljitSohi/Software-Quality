/*****************************
*data structure for the commandline input of the program
*breaks the line up by spaces, and formats the data
*****************************/
#ifndef TOKEN_H
#define TOKEN_H

#include "Formatting.h"
#include <string>

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
		//get the number of aguments by finding the number of " " there are in the string
		args_length = 0;
		int arglen = Formatting::CharacterFrequency(' ', line);
		
		//if no spaces, the there is only one word, that is a command		
		if(arglen == 0)
		{
			command = line;
			commandNumber = Formatting::CommandToNumber(command);
		}
		else
		{
			//2 or more word in string
			//get the location of ther first " "
			string wanted = " ";
			size_t last = 0;
			size_t found = line.find(wanted);

			//find command buy getting every thing before the first space
			if(found != string::npos)
			{
				command = line.substr(0, found);
				commandNumber = Formatting::CommandToNumber(command);
			}

			//make args the size of the number of arguments
			last = found;
			args = new string[arglen];
			args_length = arglen;
			int cnt = 0;
			//while there are still " " in the line passed the last one found
			while((found = line.find(wanted, last+1)) != string::npos)
			{
				//add argument to args, and increace the index of last space
				args[cnt++] = line.substr(last+1, found - last - 1);
				last = found;
			}
			//there can be one last argument between the last space and the new line, add this argument
			args[cnt++] = line.substr(last+1, line.length() - last);
		}
	}

	~Token()
	{
		//delete args only if it isn't null
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