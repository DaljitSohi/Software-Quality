class Transaction
{
	
	static public BankAccount Enable(BankAccount account)
	{
		account.setActive(true);
		return account;
	}

	static public BankAccount Disable(BankAccount account)
	{
		account.setActive(false);
		return account;
	}
	
	static public BankAccount Create(String name, int number, float amount)
	{
		return new BankAccount(number, name, true, false, amount, 0);
	}
	
	static public BankAccount Transfer(BankAccount account, float amount)
	{
		return account;
	}
	
	static public BankAccount Withdrawal(BankAccount account, float amount)
	{
		return account;
	}
	
	static public BankAccount Deposit(BankAccount account, float amount)
	{
		return account;
	}
	
	static public BankAccount Paybill(BankAccount account, float amount, String misc)
	{
		return account;
	}
	
	static public BankAccount Changeplan(BankAccount account, String misc)
	{
		account.setStudent(!account.isStudent());
		return account;
	}
}