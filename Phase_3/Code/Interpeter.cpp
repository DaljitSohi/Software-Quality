#include "Interpeter.h"


void Interpeter::InterpetToken(Token& t, Transaction& record)
{
	//catch any unwanted errors
	try{
		//call the command, according to the command number
		switch(t.GetCommandNumber())
		{
			case 1: // withdrawal
				record.Withdrawal(t.GetArgument(), t.GetArgumentLength(), t.GetCommandNumber());
				break;
			case 2: // transfer
				record.Transfer(t.GetArgument(), t.GetArgumentLength(), t.GetCommandNumber());
				break;
			case 3: // paybill
				record.Paybill(t.GetArgument(), t.GetArgumentLength(), t.GetCommandNumber());
				break;
			case 4: // deposit
				record.Deposit(t.GetArgument(), t.GetArgumentLength(), t.GetCommandNumber());
				break;
			case 5: // create
				record.Create(t.GetArgument(), t.GetArgumentLength(), t.GetCommandNumber());
				break;
			case 6: // delete
				record.Delete(t.GetArgument(), t.GetArgumentLength(), t.GetCommandNumber());
				break;
			case 7: // disable
				record.Disable(t.GetArgument(), t.GetArgumentLength(), t.GetCommandNumber());
				break;
			case 8: // changeplan
				record.Changeplan(t.GetArgument(), t.GetArgumentLength(), t.GetCommandNumber());
				break;
			case 9: // enable 
				record.Enable(t.GetArgument(), t.GetArgumentLength(), t.GetCommandNumber());
				break;
			case 10: // login
				record.Login(t.GetArgument(), t.GetArgumentLength(), t.GetCommandNumber());
				break;
			case 0: //logout
				record.Logout();
				break;
			default:
				cout << t.GetCommandName() << ": Invalid Transaction" << endl;
				break;
		}
	}
	catch (...)
	{
		cout << t.GetCommandName() << ": Invalid Transaction" << endl;
	}
}