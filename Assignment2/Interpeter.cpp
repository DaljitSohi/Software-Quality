#include "Interpeter.h"


void Interpeter::InterpetToken(Token& t, Transaction& record)
{
	try{
		switch(t.getCommandNumber())
		{
			case 1: // withdrawal
				record.Withdrawal(t.getArgument(), t.getArgumentLength());
				break;
			case 2: // transfer
				record.Transfer(t.getArgument(), t.getArgumentLength());
				break;
			case 3: // paybill
				record.Paybill(t.getArgument(), t.getArgumentLength());
				break;
			case 4: // deposit
				record.Deposit(t.getArgument(), t.getArgumentLength());
				break;
			case 5: // create
				record.Create(t.getArgument(), t.getArgumentLength());
				break;
			case 6: // delete
				record.Delete(t.getArgument(), t.getArgumentLength());
				break;
			case 7: // disable
				record.Disable(t.getArgument(), t.getArgumentLength());
				break;
			case 8: // changeplan
				record.Changeplan(t.getArgument(), t.getArgumentLength());
				break;
			case 9: // enable 
				record.Enable(t.getArgument(), t.getArgumentLength());
				break;
			case 10: // login
				record.Login(t.getArgument(), t.getArgumentLength());
				break;
			case 0: //logout
				record.Logout();
				break;
			default:
				cout << t.getCommandName() << ": Invalid Transaction" << endl;
				break;
		}
	}
	catch (...)
	{
		cout << t.getCommandName() << ": Invalid Transaction" << endl;
	}
}