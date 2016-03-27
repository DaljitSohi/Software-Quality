import java.io.*;
import java.util.*;

class Interpreter
{
	ArrayList<BankAccount> bankAccounts = null;
	boolean admin;
	public Interpreter(String bankaccountfile)
	{
		Scanner fileInput = null;
		bankAccounts = new ArrayList<BankAccount>();
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
			System.out.println("ERROR: unable to read in the bank account file");
			System.out.println("ERROR: " + e);
		
			try
			{
				fileInput.close();
			}
			catch (Exception e2){}
		}
		admin = false;
	}

	public void interpret(Token token)
	{
		if(bankAccounts != null)
		{
			if(token.getCommand() == 0)
			{
				admin = false;
				return;
			}
			if(token.getCommand() == 10)
			{
				if(token.getMisc().compareTo("A ") == 0)
					admin = true;
				return;
			}

			BankAccount account = search(token.getName());
			if(account == null)
			{
				if(token.getCommand() == 5) //create
					bankAccounts.add(Transaction.Create(token.getName(), token.getNumber(), token.getMoney()));
				else
					System.out.println("ERROR: Account doesn't exist");
				return;
			}
			switch (token.getCommand())
			{
				case 1: //withdrawal
					account = Transaction.Withdrawal(account, token.getMoney(), admin);
					break;
				case 2://transfer
					account = Transaction.Transfer(account, token.getMoney(), admin);
					break;
				case 3://paybill
					account = Transaction.Paybill(account, token.getMoney(), token.getMisc(), admin);
					break;
				case 4://deposit
					account = Transaction.Deposit(account, token.getMoney(), admin);
					break;
				case 6://delete
					bankAccounts.remove(account);
					return;
				case 7://disable
					account = Transaction.Disable(account);
					break;
				case 8://changeplan
					account = Transaction.Changeplan(account, token.getMisc());
					break;
				case 9://enable
					account = Transaction.Enable(account);
					break;
			}
			account.setTransactionNumber(account.getNumberofTransactions() + 1);
		}
		else
		{
			System.out.println("ERROR: No Bank Accounts");
		}
	}

	private BankAccount search(String name)
	{
		for(int cnt = 0; cnt < bankAccounts.size(); cnt++)
		{
			if(bankAccounts.get(cnt).getAccountName().compareTo(name) == 0)
				return bankAccounts.get(cnt);
		}
		return null;
	}

	public void writeOutBankAccounts(String masterbankaccount, String currentbankaccount)
	{
		//if no bank accounts don't do anything
		if(bankAccounts != null)
		{
			//set up outstreams for the master and current bank account files
			PrintWriter master = null, current = null;
			try
			{
				//open the files for master/current bank accounts
				master = new PrintWriter(new BufferedWriter(new FileWriter(masterbankaccount)));
				current = new PrintWriter(new BufferedWriter(new FileWriter(currentbankaccount)));
				int cnt;
				//write out to both files in the write format
				for(cnt = 0; cnt < bankAccounts.size() - 1; cnt++)
				{
					BankAccount account = bankAccounts.get(cnt);
					master.println(account.masterFileFormat());
					current.println(account.currentFileFormat());
				}
				//write out the last account so no extra line is used
				BankAccount account = bankAccounts.get(cnt);
				master.print(account.masterFileFormat());
				current.println(account.currentFileFormat());
				current.print("00000 END_OF_FILE          A 00000.00 N");
				
				//close the files
				master.close();
				current.close();
			}
			catch (Exception e)
			{
				//if error writing to the master/current bankaccount file, write out error
				System.out.println("ERROR: unable to write to the master/current bankaccount file");
				try
				{
					//if error close the files
					master.close();
					current.close();
				}
				catch (Exception e2){}
			}
		}
		else
		{
			System.out.println("ERROR: No Bank Accounts");
		}
	}

	public String toString()
	{
		for(int cnt = 0; cnt < bankAccounts.size(); cnt++)
			System.out.println(bankAccounts.get(cnt));
		return "";
	}

}