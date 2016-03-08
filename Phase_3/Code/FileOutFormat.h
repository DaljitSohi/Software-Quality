/*****************************
*Formats data to ouput in the
*correct manner
*****************************/
#ifndef FILEOUTFORMAT_H
#define FILEOUTFORMAT_H

#include "Formatting.h"

#include <string>

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
		
		//add the command number and a 0 if the number is bellow 0
		if(command >= 10)
			ret += Formatting::IntToString(command) + " ";
		else
			ret += "0"+ Formatting::IntToString(command) + " ";

		//add name to the output string, add " " when string < 20
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

		//add the account number and add extra 0's when number < 5
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

		//add dollar amount to the output string, add 0's where needed, formated to 0.00
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

		//add miscellaneous data at the end of the string
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