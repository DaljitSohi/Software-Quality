class Token
{
	int command;
	String name;
	int number;
	float money;
	String misc;


	public Token(String line)
	{
		command = Integer.parseInt(line.substring(0, 2));
		name = line.substring(3, 23).trim();
		number = Integer.parseInt(line.substring(24, 29));
		money = Float.parseFloat(line.substring(30, 38));
		misc = line.substring(39, 41);
	}
	
	int getCommand()
	{
		return command;
	}

	String getName()
	{
		return name;
	}

	int getNumber()
	{
		return number;
	}

	float getMoney()
	{
		return money;
	}

	String getMisc()
	{
		return misc;
	}
}
