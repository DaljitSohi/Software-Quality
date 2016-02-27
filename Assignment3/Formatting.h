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
	static string IntToString(int num)
	{
		stringstream stream;
		stream << num;
		return stream.str();
	}

	static string FloatToString(float num)
	{
		stringstream stream;
		stream << fixed << setprecision(2) << num;
		return stream.str();
	}


	static int StringToInt(string num)
	{
		istringstream buffer(num);
		int value;
		buffer >> value;
		return value;		
	}

	static float StringToFloat(string num)
	{
		istringstream buffer(num);
		float value;
		buffer >> value;
		return value;		
	}


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

	static int CharacterFrequency(char c, string test)
	{
		int ret = 0;
		for(int cnt = 0; cnt < test.length(); cnt++)
		{
			if(test[cnt] == c)
			{
				ret++;
			}
		}
		return ret;
	}
};
#endif // FORMATTING_H