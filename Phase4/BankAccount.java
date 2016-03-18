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

	public String toString()
	{
		String ret = "";

		ret += number + ", " + name + ", " +active + ", " + student + ", " +balance + ", " +numTransactions;
		return ret;
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
		return active;
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
		return "";
	}

	String currentFileFormat()
	{
		return "";
	}
}
