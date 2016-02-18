#ifndef INTERPETER_H
#define INTERPRTER_H

#include "Token.h"
#include "Transaction.h"

#include <stdio.h>

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>


using namespace std;

class Interpeter
{
public:
	static void InterpetToken(Token& t, Transaction& record);
};

#endif