class BankAccount
{
	int number;
	String name;
	boolean active, student;
	float balance;
	int numTransactions;

	public BankAccount(String line)
	{
		number = Integer.parseInt(line.substring(0, 5));
		name = line.substring(6, 26).trim();
		active = ((line.substring(27, 28).compareTo("A") == 0)? true : false);
		balance = Float.parseFloat(line.substring(29, 37));
		numTransactions= Integer.parseInt(line.substring(38, 42));
		student = ((line.substring(43, 44).compareTo("S") == 0)? true : false);
	}

	public BankAccount(int num, String accountName, boolean act, boolean stud, float bal, int numTrans)
	{
		number = num;
		name = accountName;
		active = act;
		balance = bal;
		numTransactions = numTrans;
		student = stud;
	}

	
	int getNumberofTransactions()
	{
		return numTransactions;
	}

	String getAccountName()
	{
		return name;
	}

	int getAccountNumber()
	{
		return number;
	}

	float getBalance()
	{
		return balance;
	}

	boolean isActive()
	{
		return active;
	}

	boolean isStudent()
	{
		return student;
	}


	void setBalance(float value)
	{
		balance = value;
	}

	void setTransactionNumber(int value)
	{
		numTransactions = value;
	}

	void setStudent(boolean value)
	{
		student = value;
	}

	void setActive(boolean value)
	{
		active = value;
	}


	String masterFileFormat()
	{
		String ret = "";

		//set up number
		String temp = "" + number;

		//add "0" to the begging of the number if needed
		String strtemp = "";
		for(int cnt = 0; cnt < 5 - temp.length(); cnt++)
		{
			strtemp += "0"; 
		}
		temp = strtemp + temp;
		ret += temp + " ";

		//set up account holder name
		temp = name;

		//add " " at the end
		int length = 20 - temp.length();
		for(int cnt = 0; cnt < length; cnt++)
		{
			temp += " ";
		}
		
		ret += temp + " ";

		//set up active
		if(active)
			ret += "A ";
		else
			ret += "D ";

		//set up money
		temp = String.format("%.02f", balance);

		
		//add "0" to the begging of the number if needed
		strtemp = "";
		for(int cnt = 0; cnt < 8 - temp.length(); cnt++)
		{
			strtemp += "0"; 
		}
		temp = strtemp + temp;
		
		ret += temp + " ";

		//set up total transactions
		temp = "" + numTransactions;
		
		//add "0" to the begging of the number if needed
		strtemp = "";
		for(int cnt = 0; cnt < 4 - temp.length(); cnt++)
		{
			strtemp += "0"; 
		}
		temp = strtemp + temp;
		
		ret += temp + " ";
		
		//set up active
		if(student)
			ret += "S";
		else
			ret += "N";

		return ret;
	}

	String currentFileFormat()
	{
		String ret = "";

		//set up number
		String temp = "" + number;
		
		//add "0" to the begging of the number if needed
		String strtemp = "";
		for(int cnt = 0; cnt < 5 - temp.length(); cnt++)
		{
			strtemp += "0"; 
		}
		temp = strtemp + temp;
		
		ret += temp + " ";

		//set up account holder name
		temp = name;

		//add " " at the end
		int length = 20 - temp.length();
		for(int cnt = 0; cnt < length; cnt++)
		{
			temp += " ";
		}
	
		ret += temp + " ";

		//set up active
		if(active)
			ret += "A ";
		else
			ret += "D ";

		//set up money
		temp = String.format("%.02f", balance);

		//add "0" to the begging of the number if needed
		strtemp = "";
		for(int cnt = 0; cnt < 8 - temp.length(); cnt++)
		{
			strtemp += "0"; 
		}
		temp = strtemp + temp;
		
		ret += temp + " ";

		//set up active
		if(student)
			ret += "S";
		else
			ret += "N";

		return ret;
	}
}