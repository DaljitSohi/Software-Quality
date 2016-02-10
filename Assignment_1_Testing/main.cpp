#include <stdio.h>

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>


using namespace std;

//bank account transcaction file constants
#define BATF_NAME_LEN 20
#define BATF_ACC_NUM_LEN 5
#define BATF_MONEY_LEN 8
#define BATF_MISC_LEN 2





struct Input
{
	string command;
	int cmdint;
	string* args;
	int lenargs;
};

int characterFrequency(char c, string test)
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


int commandToNumber(string command)
{
	if(command.compare("withdrawal") == 0)
	{
		return 1;
	}
	else if(command.compare("transfer") == 0)
	{
		return 2;
	}
	else if(command.compare("paybill") == 0)
	{
		return 3;
	}
	else if(command.compare("deposit") == 0)
	{
		return 4;
	}
	else if(command.compare("create") == 0)
	{
		return 5;
	}
	else if(command.compare("delete") == 0)
	{
		return 6;
	}
	else if(command.compare("disable") == 0)
	{
		return 7;
	}
	else if(command.compare("changeplan") == 0)
	{
		return 8;
	}
	else if(command.compare("enable") == 0)
	{
		return 9;
	}
	else if(command.compare("login") == 0)
	{
		return 10;
	}
	return 0;
}

string inttostring(int num)
{
	stringstream stream;
	stream << num;
	return stream.str();
}


string floattostring(float num)
{
	stringstream stream;
	stream << fixed << setprecision(2) << num;
	return stream.str();
}



Input* makeInput(string input)
{
	Input* out = new Input;
	string wanted = " ";
	size_t last = 0;
	size_t found = input.find(wanted);
	int arglen = characterFrequency(' ', input);

	//find command
	if(found != string::npos)
	{
		out->command = input.substr(0, found);
		out->cmdint = commandToNumber(out->command);
	}
	else
		return NULL;//error in length
	last = found;

	out->args = new string[arglen];
	out->lenargs = arglen;
	int cnt = 0;
	while((found = input.find(wanted, last+1)) != string::npos)
	{
		out->args[cnt++] = input.substr(last+1, found -last);
		last = found;
	}
	out->args[cnt++] = input.substr(last+1, input.length() - last);

	return out;
}

string makeOutput(int command, string name, int anumber, float money, string misc)
{
	string ret = "";
	
	//add command
	if(command >= 10)
		ret += inttostring(command) + " ";
	else
		ret += "0"+ inttostring(command) + " ";

	//add name
	int len = BATF_NAME_LEN - name.length();
	if(len >= 0)
	{
		ret += name;
		for(int cnt = 0; cnt < len; cnt++)
		{
			ret += " ";
		}
	}
	else
	{
		ret += name.substr(0,BATF_NAME_LEN);
	}
	ret += " ";

	//add accountnumbers
	string number = inttostring(anumber);

	if(number.length() < BATF_ACC_NUM_LEN)
	{
		for(int cnt = 0; cnt < BATF_ACC_NUM_LEN - number.length(); cnt++)
			ret += "0";
		ret += number;
	}
	else
	{
		ret += number.substr(number.length() - BATF_ACC_NUM_LEN, BATF_ACC_NUM_LEN);
	}
	ret += " ";

	//add dollar amount
	string dollar = floattostring(money);

	if(dollar.length() < BATF_MONEY_LEN)
	{
		for(int cnt = 0; cnt < BATF_MONEY_LEN - dollar.length(); cnt++)
			ret += "0";
		ret += dollar;
	}
	else
	{
		ret += dollar.substr(dollar.length() - BATF_MONEY_LEN, BATF_MONEY_LEN);
	}
	ret += " ";

	//add miscellaneous
	if(misc.length() > BATF_MISC_LEN)
	{
		ret += misc.substr(number.length() - BATF_MISC_LEN, BATF_MISC_LEN);	
	}
	else
		ret += misc;

	return ret;
}




int main(int argc, char** argv)
{
	// cout << argv[1] << endl;
	// cout << "login: Invalid Transcaction" << endl;
	ofstream file("batf.txt");
	//10                      00000 00000.00 A
	//05 Nick                 00010 04000.00  
	//00                      00000 00000.00 A 
	file << makeOutput(10, "", 0, 0, "A ") << endl;
	file << makeOutput(5, "Nick", 10, 4000.00, "  ") << endl;
	file << makeOutput(0, "", 0, 0, "A ") << endl;

	file.close();
	return 0;
}