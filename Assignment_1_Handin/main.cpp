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
	ofstream file("batf.txt");

	file << makeOutput(10, "", 0, 0, "A ") << endl;
	file << makeOutput(5, "Nick", 10, 4000.00, "  ") << endl;
	file << makeOutput(0, "", 0, 0, "A ") << endl;

	file.close();
	return 0;
}