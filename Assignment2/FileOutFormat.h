/*****************************
*Formats data to ouput in the
*correct manner
*****************************/
#ifndef FILEOUTFORMAT_H
#define FILEOUTFORMAT_H

#include "Formatting.h"

#include <string>
#include <iostream>

using namespace std;

//bank account transcaction file constants
#define BATF_NAME_LEN 20
#define BATF_ACC_NUM_LEN 5
#define BATF_MONEY_LEN 8
#define BATF_MISC_LEN 2


class outFormat
{
public:
	static string makeOutput(int command, string name, int anumber, float money, string misc)
	{
		string ret = "";
		
		//add command
		if(command >= 10)
			ret += Formatting::inttostring(command) + " ";
		else
			ret += "0"+ Formatting::inttostring(command) + " ";

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
		string number = Formatting::inttostring(anumber);

		if(number.length() < BATF_ACC_NUM_LEN)
		{
			cout << BATF_ACC_NUM_LEN - number.length() << " " << number.length() << endl;
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
		string dollar = Formatting::floattostring(money);

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


};
#endif