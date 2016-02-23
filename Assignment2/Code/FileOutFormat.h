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


class OutFormat
{
public:

	/**
	*create a string with the proper format for the bank account transaction file
	*command - the commmand number
	*name - the name of the account holder
	*number - the account holder's number
	*money - the amount involde in the transaction
	*misc - the extra data
	*/
	static string MakeOutput(int command, string name, int anumber, float money, string misc)
	{
		string ret = "";
		
		//add command
		if(command >= 10)
			ret += Formatting::IntToString(command) + " ";
		else
			ret += "0"+ Formatting::IntToString(command) + " ";

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
		string number = Formatting::IntToString(anumber);

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
		string dollar = Formatting::FloatToString(money);

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
		else if(misc.length() ==  BATF_MISC_LEN-1)
		{
			ret += misc + " ";
		}
		else
			ret += misc;

		return ret;
	}
};
#endif