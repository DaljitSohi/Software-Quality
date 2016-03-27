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
		String ret = "";

		//set up number
		String temp = "" + number;
		if(temp.length() > 5)
		{
			//if number > 5 the take last 5 numbers
			temp = temp.substring(temp.length() -6, temp.length()-1);
		}
		else
		{
			//add "0" to the begging of the number if needed
			String strtemp = "";
			for(int cnt = 0; cnt < 5 - temp.length(); cnt++)
			{
				strtemp += "0"; 
			}
			temp = strtemp + temp;
		}
		ret += temp + " ";

		//set up account holder name
		temp = name;
		if(temp.length() > 20)
		{
			//if name > 20, trunacte to the first 20
			temp = temp.substring(0, 20);
		}
		else
		{
			//add " " at the end
			int length = 20 - temp.length();
			for(int cnt = 0; cnt < length; cnt++)
			{
				temp += " ";
			}
		}
		ret += temp + " ";

		//set up active
		if(active)
			ret += "A ";
		else
			ret += "D ";

		//set up money
		temp = String.format("%.02f", balance);

		if(temp.length() > 8)
		{
			//if number > 8 the take last 8 numbers
			temp = temp.substring(temp.length() -9, temp.length()-1);
		}
		else
		{
			//add "0" to the begging of the number if needed
			String strtemp = "";
			for(int cnt = 0; cnt < 8 - temp.length(); cnt++)
			{
				strtemp += "0"; 
			}
			temp = strtemp + temp;
		}
		ret += temp + " ";

		//set up total transactions
		temp = "" + numTransactions;
		if(temp.length() > 4)
		{
			//if number > 4 the take last 4 numbers
			temp = temp.substring(temp.length() -5, temp.length()-1);
		}
		else
		{
			//add "0" to the begging of the number if needed
			String strtemp = "";
			for(int cnt = 0; cnt < 4 - temp.length(); cnt++)
			{
				strtemp += "0"; 
			}
			temp = strtemp + temp;
		}
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
		if(temp.length() > 5)
		{
			//if number > 5 the take last 5 numbers
			temp = temp.substring(temp.length() -6, temp.length()-1);
		}
		else
		{
			//add "0" to the begging of the number if needed
			String strtemp = "";
			for(int cnt = 0; cnt < 5 - temp.length(); cnt++)
			{
				strtemp += "0"; 
			}
			temp = strtemp + temp;
		}
		ret += temp + " ";

		//set up account holder name
		temp = name;
		if(temp.length() > 20)
		{
			//if name > 20, trunacte to the first 20
			temp = temp.substring(0, 20);
		}
		else
		{
			//add " " at the end
			int length = 20 - temp.length();
			for(int cnt = 0; cnt < length; cnt++)
			{
				temp += " ";
			}
		}
		ret += temp + " ";

		//set up active
		if(active)
			ret += "A ";
		else
			ret += "D ";

		//set up money
		temp = String.format("%.02f", balance);

		if(temp.length() > 8)
		{
			//if number > 8 the take last 8 numbers
			temp = temp.substring(temp.length() -9, temp.length()-1);
		}
		else
		{
			//add "0" to the begging of the number if needed
			String strtemp = "";
			for(int cnt = 0; cnt < 8 - temp.length(); cnt++)
			{
				strtemp += "0"; 
			}
			temp = strtemp + temp;
		}
		ret += temp + " ";

		//set up active
		if(student)
			ret += "S";
		else
			ret += "N";

		return ret;
	}
}