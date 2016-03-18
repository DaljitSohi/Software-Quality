import java.io.*;
import java.util.*;

class backend
{
	static public void main(String args[])
	{
		//check to make sure there is at least 2 argument for the program
		if(args.length < 2)
		{
			System.out.println("Error, please include the Transaction file, and the Master Bank Account file.");
			return;
		}
		//variables fo the transaction file and the master bankaccount file
		String transfile = "", bankaccountfile = "";
		
		//if there is 3 or more variables, mutiple transaction files, merge
		//transaction files, and set the trasnactoin aband bank account variables
		if(args.length >= 3)
		{
			//more than one bank account transaction file
			FileWriter mergedFile = null;
			FileReader inFile = null;
			//default name of the merged bankaccount file
			transfile = "MasterBankTransfer.tran";
			try
			{
				//open the merge file
				mergedFile = new FileWriter(transfile);
				
				//feed the data from each transaction file into the merge file
				for(int cnt = 0; cnt < args.length - 1; cnt++)
				{
					inFile = new FileReader(args[cnt]);
					int c;
					//feed data into the merge file
					while((c = inFile.read()) != -1)
						mergedFile.write(c);

					inFile.close();
				}
				//close off the merge file and set the bank account variable
				mergedFile.close();
				bankaccountfile = args[args.length - 1];
			}
			catch (Exception e)
			{
				//if error mergeing files, write out error and stop program
				System.out.println("Error, reading in mutiple files");
				try
				{
					mergedFile.close();
					inFile.close();
				}
				catch (Exception e2){}
				return;
			}
		}
		else
		{
			//with only 2 variable in the args, set the transaction and bankaccount variables
			transfile = args[0];
			bankaccountfile = args[1];
		}

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
			System.out.println("Error, unable to read in the transaction file");
			try
			{
				fileInput.close();
			}
			catch (Exception e2){}
			return;
		}

		//finish the program by writing out update bank accounts
		interpret.writeOutBankAccounts("MasterBankAccountsFile.bank","CurrentBankAccounts.bank");
	}
}