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
	
	static public BankAccount Transfer(BankAccount account, float amount, boolean admin)
	{
		/*
		 * 1. check if bank accout is active. 
		 * 		- if not, throw an error message =
		 * 2. check if admin login or standard login
		 * 		- if standard, then transfer amount has to be between ( 0 > and < 1000)
		 * 3. check if student login, or non-student login. 
		 * 		- if non student charge --> $0.10.
		 * 		- if student charge --> $0.05
		 * 
		 */

		//the amount we are transfering from an account.
		float transferAmount = 0.0f;
		if(amount > 0){
			transferAmount = amount;
		}
		else{
			System.out.println("ERROR: transfer amount is less than $0. Transfer amount must be greater than $0.");
		}

		//if the account is Active
		if(account.isActive()){
			//check if its a non-student account
			if(!account.isStudent()){

				//An admin log in. 
				if(admin){

					//set transferAmount equal to the amount to transfer + the charges.  
					// transferAmount = amount + 0.10f;

					float newBalance = account.getBalance() - transferAmount ;
					if(newBalance < 0){
						System.out.println("ERROR");
					}
					else{
						account.setBalance(newBalance);
					}
				}

				//a standard login.
				else{
					//can't transfer more than $1000.00, on standard login.
					if(amount > 1000.00f){
						System.out.println("ERROR: Can not transfer more than $1000, on a standard login.");
					}

					//if amount < 1000.00, transfer the amount.
					else{
						//set transferAmount equal to the amount to transfer + the charges.  
						transferAmount = amount + 0.10f;

						float newBalance = account.getBalance() - transferAmount ;
						if(newBalance < 0){
							System.out.println("ERROR");
						}
						else{
							account.setBalance(newBalance);
						}
					}
				}
			}//end of !isStudent if statement.

			//student account
			else{
				//An admin log in. 
				if(admin){

					//set transferAmount equal to the amount to transfer + the charges.  
					// transferAmount = amount + 0.05f;

					float newBalance = account.getBalance() - transferAmount ;
					if(newBalance < 0){
						System.out.println("ERROR");
					}
					else{
						account.setBalance(newBalance);
					}
				}

				//a standard login.
				else{
					//can't transfer more than $1000.00, on standard login.
					if(amount > 1000.00f){
						System.out.println("ERROR: Can not transfer more than $1000, on a standard login.");
					}

					//if amount < 1000.00, transfer the amount.
					else{
						//set transferAmount equal to the amount to transfer + the charges.  
						transferAmount = amount + 0.05f;

						float newBalance = account.getBalance() - transferAmount ;
						if(newBalance < 0){
							System.out.println("ERROR");
						}
						else{
							account.setBalance(newBalance);
						}
					}
				}
			}
		}//end of isActive if statement.
		else{
			System.out.println("ERROR: Not an active account.");
		}
		return account;
	}
	
	static public BankAccount Withdrawal(BankAccount account, float amount, boolean admin)
	{
		/*
		 * withdrawal > 500 is not acceptable on standard login.
		 * withdrawal has to be multiple of 5.
		 */

		float withdrawalAmount = 0.0f;
		//check if amount is a multiple of 5.
		if(amount % 5 == 0){
			withdrawalAmount = amount;
		}else {
			System.out.println("ERROR: Amount is not a multiple of 5.");
		}

		//if the account is active
		if(account.isActive()){

			//non-student account
			if(!account.isStudent()){

				//admin access
				if(admin){
					// withdrawalAmount = amount + 0.10f;
					float newBalance = account.getBalance() - withdrawalAmount;

					if(newBalance  < 0){
						System.out.println("ERROR: Transaction cancled. After withdrawl the bank balance drops below 0.");
					}
					else{
						account.setBalance(newBalance);
					}

				}//end of acces type -> admin

				//standard access
				else{
					if(withdrawalAmount > 500){
						System.out.println("ERROR: Can not withdraw more than 500, on a standard login.");
					}
					else{

						withdrawalAmount = amount + 0.10f;
						float newBalance = account.getBalance() - withdrawalAmount;

						if(newBalance  < 0){
							System.out.println("ERROR: Transaction cancled. After withdrawl the bank balance drops below 0.");
						}
						else{
							account.setBalance(newBalance);
						}
					}

				}//end of access type -> std

			}//end of non-student account type

			//student account
			else{

				//admin access
				if(admin){
					// withdrawalAmount = amount + 0.05f;
					float newBalance = account.getBalance() - withdrawalAmount;

					if(newBalance  < 0){
						System.out.println("ERROR: Transaction cancled. After withdrawl the bank balance drops below 0.");
					}
					else{
						account.setBalance(newBalance);
					}

				}//end of acces type -> admin

				//standard access
				else{
					if(withdrawalAmount > 500){
						System.out.println("ERROR: Can not withdraw more than 500, on a standard login.");
					}
					else{

						withdrawalAmount = amount + 0.05f;
						float newBalance = account.getBalance() - withdrawalAmount;

						if(newBalance  < 0){
							System.out.println("ERROR: Transaction cancled. After withdrawl the bank balance drops below 0.");
						}
						else{
							account.setBalance(newBalance);
						}

					}

				}//end of access type -> std

			}//end of student account type

		}//end of Active account

		//if the account is not active
		else{
			System.out.println("ERROR: Not an active account.");
		}//end of not active account

		return account;
	}
	
	static public BankAccount Deposit(BankAccount account, float amount, boolean admin)
	{
		
		float depositAmount = 0.0f;
		if(amount > 0){
			depositAmount = amount;
		}
		else{
			System.out.println("ERROR: Deposit amount must be more than $0.");
		}
		
		
		//if the account is active
		if(account.isActive()){

			//non-student account
			if(!account.isStudent()){

				//admin access
				if(admin){
					float newBalance = account.getBalance() + depositAmount;
					account.setBalance(newBalance);
				}//end of acces type -> admin

				//standard access
				else{
					float newBalance = account.getBalance() + depositAmount;
					account.setBalance(newBalance);
				}//end of access type -> std

			}//end of non-student account type

			//student account
			else{
				//admin access
				if(admin){
					float newBalance = account.getBalance() + depositAmount;
					account.setBalance(newBalance);
				}//end of acces type -> admin

				//standard access
				else{
					float newBalance = account.getBalance() + depositAmount;
					account.setBalance(newBalance);
				}//end of access type -> std

			}//end of student account type

		}//end of Active account

		//if the account is not active
		else{
			System.out.println("ERROR: Not an active account.");
		}//end of not active account

		return account;
	}
	
	static public BankAccount Paybill(BankAccount account, float amount, String misc, boolean admin)
	{
		/* Other things to make sure.
		 * 	- bill amount can't bet less than 0. 
		 *  
		 * 
		 * 
		 * 1. check if account is active
		 * 		- if not active, print an error.
		 * 2. check if student or non-student
		 * 		- if nonstudent then apply a change or 0.10, and bill amount has not limit.
		 * 
		 */

		float billAmount = 0.0f;

		//first thing to check is, if the amount is greater than 0.
		if(!(amount > 0)){
			System.out.println("ERROR: amount to pay has to be greater than 0.");
		}
		else{
			billAmount = amount;
		}

		//first check if the account is active.
		if(account.isActive()){
			//account is not a student account.
			if(!account.isStudent()){
				//if an admin login
				if(admin){
					// billAmount += 0.10; //add a change of $0.10 to the billAmount.

					//new account balance. After subtracting the bill
					float newBalance = account.getBalance() - billAmount; 
					if(newBalance < 0){
						System.out.println("ERROR: transactions can not go through. + "
								+ "Account Balance results to $0.00");
					}
					else{
						//set Account balance to (newBalance)
						account.setBalance(newBalance);
					}

				}// end of if for admin login

				//if a standard login
				else{
					//bill amount has to be less than $2000.00
					if(billAmount > 2000.00f){
						System.out.println("ERROR: Bill amount is more than $2000.00");
					}
					//if the bill amount is less than $2000.00
					else{
						billAmount += 0.05; //add a change of $0.05 to the billAmount.
						//set Account balance to (current balance - billAmount)

						//new account balance. After subtracting the bill
						float newBalance = account.getBalance() - billAmount; 
						if(newBalance < 0){
							System.out.println("ERROR: transactions can not go through. + "
									+ "Account Balance results to $0.00");
						}
						else{
							//set Account balance to (newBalance)
							account.setBalance(newBalance);
						}
					}
				}// end of else for standard login
			}//end of if statement for non-student login

			//if the account is a student account.
			else{
				//if an admin login
				if(admin){
					// billAmount += 0.05; //add a change of $0.10 to the billAmount.

					//new account balance. After subtracting the bill
					float newBalance = account.getBalance() - billAmount; 
					if(newBalance < 0){
						System.out.println("ERROR: transactions can not go through. + "
								+ "Account Balance results to $0.00");
					}
					//set Account balance to (newBalance)
					account.setBalance(newBalance);
				}// end of if for admin login

				//if a standard login
				else{
					//bill amount has to be less than $2000.00
					if(billAmount > 2000.00f){
						System.out.println("ERROR: Bill amount is more than $2000.00");
					}
					//if the bill amount is less than $2000.00
					else{
						billAmount += 0.05; //add a change of $0.10 to the billAmount.
						//set Account balance to (current balance - billAmount)

						//new account balance. After subtracting the bill
						float newBalance = account.getBalance() - billAmount; 
						if(newBalance < 0){
							System.out.println("ERROR: transactions can not go through. + "
									+ "Account Balance results to $0.00");
						}
						//set Account balance to (newBalance)
						account.setBalance(newBalance);
					}
				}
			}
		}//end of isActive if statement
		else{
			System.out.println("ERROR: account is not active.");
		}
		return account;
	}
	
	static public BankAccount Changeplan(BankAccount account, String misc)
	{
		account.setStudent(!account.isStudent());
		return account;
	}
}