/*****************************
*interperts token, calls the appropriate transaction
*****************************/
#ifndef INTERPETER_H
#define INTERPRTER_H

#include "Token.h"
#include "Transaction.h"

using namespace std;

class Interpeter
{
public:
	/**
	*Interpets the token form line input and calls the proper transaction for execution
	*/
	static void InterpetToken(Token& t, Transaction& record);
};

#endif