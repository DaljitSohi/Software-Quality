/*****************************
*formats int to string, float to string
*convert command number to command string, and vice versa 
*****************************/
#ifndef FORMATTING_H
#define FORMATTING_H

#include <string>
#include <sstream>
#include <iomanip>

#define LOGOUT 0
#define WITHDRAWAL 1
#define TRANSFER 2
#define PAYBILL 3
#define DEPOSIT 4
#define CREATE 5
#define DELETE 6
#define DISABLE 7
#define CHANGEPLAN 8
#define ENABLE 9
#define LOGIN 10


using namespace std;

class Formatting
{
public:
	/**
	* Converts a Interger to a string
	* num - the number to convert
	* return the string form of the number
	*/
	static string IntToString(int num)
	{
		stringstream stream;
		stream << num;
		return stream.str();
	}

	/**
	* Converts a float to a string, have only two numbers after the decimal
	* num - the number to convert
	* return the string form of the number
	*/
	static string FloatToString(float num)
	{
		stringstream stream;
		stream << fixed << setprecision(2) << num;
		return stream.str();
	}


	/**
	* Converts a string to an integer
	* num - the string of the number
	* return the integer form of the number
	*/
	static int StringToInt(string num)
	{
		istringstream buffer(num);
		int value;
		buffer >> value;
		return value;		
	}

	
	/**
	* Converts a string to an float
	* num - the string of the number
	* return the float form of the number
	*/
	static float StringToFloat(string num)
	{
		istringstream buffer(num);
		float value;
		buffer >> value;
		return value;		
	}


	/**
	* Convert the string command into the corresponding number value
	* command - the string command to be converted
	* return the number for the command, -1 if not a command
	*/
	static int CommandToNumber(string command)
	{
		if(command.compare("withdrawal") == 0)
		{
			return WITHDRAWAL;
		}
		else if(command.compare("transfer") == 0)
		{
			return TRANSFER;
		}
		else if(command.compare("paybill") == 0)
		{
			return PAYBILL;
		}
		else if(command.compare("deposit") == 0)
		{
			return DEPOSIT;
		}
		else if(command.compare("create") == 0)
		{
			return CREATE;
		}
		else if(command.compare("delete") == 0)
		{
			return DELETE;
		}
		else if(command.compare("disable") == 0)
		{
			return DISABLE;
		}
		else if(command.compare("changeplan") == 0)
		{
			return CHANGEPLAN;
		}
		else if(command.compare("enable") == 0)
		{
			return ENABLE;
		}
		else if(command.compare("login") == 0)
		{
			return LOGIN;
		}
		else if(command.compare("logout") == 0)
		{
			return LOGOUT;
		}
		return -1;
	}


	/**
	* Convert the command number into its string name
	* command - the command number to be converted
	* return the command name in string form, "not a command" return it command number is off
	*/
	static string CommandToString(int command)
	{
		switch(command)
		{
			case WITHDRAWAL:
				return "withdrawal";
				break; 
			case TRANSFER:
				return "transfer";
				break; 
			case PAYBILL:
				return "paybill";
				break; 
			case DEPOSIT:
				return "deposit";
				break; 
			case CREATE:
				return "create";
				break; 
			case DELETE:
				return "delete";
				break; 
			case DISABLE:
				return "disable";
				break; 
			case CHANGEPLAN:
				return "changeplan";
				break; 
			case ENABLE:
				return "enable";
				break; 
			case LOGIN:
				return "login";
				break; 
			case LOGOUT:
				return "logout";
				break; 
			default:
				return "Not a Command";
				break;
		}
	}

	/**
	* Return the occurrences of a specific
	* c - the character to check for
	* text - the string to look through 
	* return the number for times c appears in the text
	*/
	static int CharacterFrequency(char character, string text)
	{
		int ret = 0;
		for(int cnt = 0; cnt < text.length(); cnt++)
		{
			if(text[cnt] == character)
			{
				ret++;
			}
		}
		return ret;
	}
};
#endif // FORMATTING_H