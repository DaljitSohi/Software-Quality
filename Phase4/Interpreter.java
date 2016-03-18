import java.io.*;
import java.util.*;

class Interpreter
{
	ArrayList<BankAccount> bankAccounts = null;

	public Interpreter(String bankaccountfile)
	{
		Scanner fileInput = null;
		try
		{
			//create the scanner with the bankaccount file
			fileInput = new Scanner(new File(bankaccountfile));

			//while there is a new line avaiable, create a bankaccount out of it
			while(fileInput.hasNextLine())
			{
				String line = fileInput.nextLine();
				BankAccount account = new BankAccount(line);

				//add the new account ot the list of bankaccounts
				bankAccounts.add(account);
			}
			fileInput.close();
		}
		catch (Exception e)
		{
			bankAccounts = null;
			//if error reading the master bankaccount file, write out error 
			System.out.println("Error, unable to read in the bank account file");
			try
			{
				fileInput.close();
			}
			catch (Exception e2){}
		}
	}

	public void interpret(Token token)
	{
		if(bankAccounts != null)
		{
			BankAccount account = search(token.getName());
			switch (token.getCommand())
			{
				case 1: //withdrawal
					account = Transaction.Withdrawal(account, token.getMoney());
					break;
				case 2://transfer
					account = Transaction.Transfer(account, token.getMoney());
					break;
				case 3://paybill
					account = Transaction.Paybill(account, token.getMoney(), token.getMisc());
					break;
				case 4://deposit
					account = Transaction.Deposit(account, token.getMoney());
					break;
				case 5://create
					account = Transaction.Create(account, token.getMoney());
					break;
				case 6://delete
					account = Transaction.Delete(account);
					break;
				case 7://disable
					account = Transaction.Disable(account);
					break;
				case 8://changeplan
					account = Transaction.Changeplan(account, token.getMisc());
					break;
				case 9://enable
					account = Transaction.Enable(account);
					break;
				default:
					return;
			}
			account.setTransactionNumber(account.getNumberofTransactions() + 1);
		}
		else
		{
			System.out.println("Error with Bank Account file");
		}
	}


	private BankAccount search(String name)
	{
		return null;
	}

	public void writeOutBankAccounts(String masterbankaccount, String currentbankaccount)
	{
		if(bankAccounts != null)
		{
			PrintWriter master = null, current = null;
			try
			{
				master = new PrintWriter(new BufferedWriter(new FileWriter(masterbankaccount)));
				current = new PrintWriter(new BufferedWriter(new FileWriter(currentbankaccount)));

				for(int cnt = 0; cnt < bankAccounts.size(); cnt++)
				{
					BankAccount account = bankAccounts.get(cnt);
					master.println(account.masterFileFormat());
					current.println(account.currentFileFormat());
				}
				master.close();
				current.close();
			}
			catch (Exception e)
			{
				//if error writing to the master/current bankaccount file, write out error
				System.out.println("Error, unable to write to the master/current bankaccount file");
				try
				{
					master.close();
					current.close();
				}
				catch (Exception e2){}
			}
		}
		else
		{
			System.out.println("Error with Bank Account file");
		}

	}
}