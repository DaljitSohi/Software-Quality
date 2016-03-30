import java.io.*;
import java.util.*;

class backend
{
	static public void main(String args[])
	{
		//check to make sure there is at least 2 argument for the program
		if(args.length < 2)
		{
			System.out.println("ERROR: please include the Transaction file, and the Master Bank Account file.");
			return;
		}
		
		//variables fo the transaction file and the master bankaccount file
		String transfile = args[0];
		String bankaccountfile = args[1];
		
		//create an interpreter with the bankaccount file and the scanner for input
		Interpreter interpret = new Interpreter(bankaccountfile);
		Scanner fileInput = null;
		
		try
		{
			//create the scanner with the transaction file
			fileInput = new Scanner(new File(transfile));

			//while there is a new line avaiable interpreter it
			while(fileInput.hasNextLine())
			{
				String line = fileInput.nextLine();
				
				//create a token out if the line and feed it to the interpreter
				Token transaction = new Token(line);
				interpret.interpret(transaction);
			}
			fileInput.close();
		}
		catch (Exception e)
		{
			//if error reading the transaction file, write out error and stop program
			System.out.println("ERROR: unable to read in the transaction file");
			System.out.println("ERROR: " + e);
			try
			{
				fileInput.close();
			}
			catch (Exception e2){}
			return;
		}

		// //finish the program by writing out update bank accounts
		interpret.writeOutBankAccounts("MasterBankAccountsFile.bank","CurrentBankAccounts.bank");
	}
}