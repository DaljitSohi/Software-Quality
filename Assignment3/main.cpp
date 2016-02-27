#include "Formatting.h"

#include <string>
#include <iostream>
using namespace std;

#define BATF_NAME_LEN 20
#define BATF_ACC_NUM_LEN 5
#define BATF_MONEY_LEN 8
#define BATF_MISC_LEN 2


static string MakeOutput(int anumber, string name, string active, float money, string plan)
	{
		string ret = "";
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


		//add miscellaneous
		ret += active;
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
		ret += plan;

		return ret;
	}






int main()
{

	for(int cnt = 27; cnt < 100000; cnt++)
	{
		cout << MakeOutput(cnt, "Temp-" + Formatting::IntToString(cnt) ,"A", 1000.0f,"N") <<endl;
	}


	return 0;
}