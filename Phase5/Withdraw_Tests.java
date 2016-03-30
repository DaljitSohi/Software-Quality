import static org.junit.Assert.*;
import org.junit.Test;
import junit.framework.JUnit4TestAdapter;

public class Withdraw_Tests {

	@Test  
	/* Test for
	 *  - Withdraw amount % 0.
	 */

	public void withdrawTest_amountBelowZero(){
		String account = "00001 Daljit               A 06966.61 0002 N";
		BankAccount accountTest = new BankAccount(account);
		BankAccount temp = Transaction.Withdrawal(accountTest, 278.00f, true);
		assertNull(temp);
	}


	@Test
	/*
	 * Test for: 
	 * 	- Withdraw amount > 0
	 *  - Account is active
	 *  - Account type -> Not Student
	 *  - login type Admin
	 *  - new Balance < 0.
	 */
	public void withdrawTest_amountAboveZero1(){

		String account = "00001 Daljit               A 00966.61 0002 N";
		BankAccount accountTest = new BankAccount(account);
		Transaction.Withdrawal(accountTest, 1000.10f, true); //amount = 1000.10, admin = true
		assertEquals(00966.61f,accountTest.getBalance(), 1e-2);
	}

	@Test
	/*
	 * Test for: 
	 * 	- Withdraw amount > 0
	 *  - Account is active
	 *  - Account type -> Not Student
	 *  - login type Admin
	 *  - new Balance > 0.
	 */
	public void withdrawTest_amountAboveZero2(){

		String account = "00001 Daljit               A 00966.61 0002 N";
		BankAccount accountTest = new BankAccount(account);
		Transaction.Withdrawal(accountTest, 0500.00f, true); //amount = 1000.10, admin = true
		assertEquals(00466.61f,accountTest.getBalance(), 1e-2);
	}

	@Test
	/*
	 * Test for: 
	 * 	- Withdraw amount > 0
	 *  - Account is active
	 *  - Account type -> Not Student
	 *  - login type -> Not-Admin
	 *  - Withdraw limit violation. 
	 */
	public void withdrawTest_amountAboveZero3(){

		String account = "00001 Daljit               A 00966.61 0002 N";
		BankAccount accountTest = new BankAccount(account);
		Transaction.Withdrawal(accountTest, 01001.10f, false); //amount = 1000.10, admin = false.
		assertEquals(00966.61f,accountTest.getBalance(), 1e-2);
	}

	@Test
	/*
	 * Test for: 
	 * 	- Withdraw amount > 0.
	 *  - Account is active.
	 *  - Account type -> Not Student.
	 *  - login type -> Not-Admin.
	 *  - No Withdraw limit violation.
	 *  - new balance < 0
	 *   
	 */
	public void withdrawTest_amountAboveZero4(){

		String account = "00001 Daljit               A 00050.00 0002 N";
		BankAccount accountTest = new BankAccount(account);
		Transaction.Withdrawal(accountTest, 00500.00f, false); //amount = 1000.10, admin = false.
		assertEquals(00050.00f,accountTest.getBalance(), 1e-2);
	}

	@Test
	/*
	 * Test for: 
	 * 	- Withdraw amount > 0.
	 *  - Account is active.
	 *  - Account type -> Not Student.
	 *  - login type -> Not-Admin.
	 *  - No Withdraw limit violation.
	 *  - new balance > 0.
	 */
	public void withdrawTest_amountAboveZero5(){

		String account = "00001 Daljit               A 00700.00 0002 N";
		BankAccount accountTest = new BankAccount(account);
		Transaction.Withdrawal(accountTest, 500.00f, false); //amount = 1000.10, admin = false.
		assertEquals(199.90f,accountTest.getBalance(), 1e-2);
	}	

	@Test
	/*
	 * Test for: 
	 * 	- Withdraw amount > 0
	 *  - Account is active
	 *  - Account type -> Student
	 *  - login type Admin
	 *  - new Balance < 0.
	 */
	public void withdrawTest_amountAboveZero6(){

		String account = "00001 Daljit               A 00966.61 0002 S";
		BankAccount accountTest = new BankAccount(account);
		Transaction.Withdrawal(accountTest, 1000.10f, true); //amount = 1000.10, admin = true
		assertEquals(00966.61f,accountTest.getBalance(), 1e-2);
	}

	@Test
	/*
	 * Test for: 
	 * 	- Withdraw amount > 0
	 *  - Account is active
	 *  - Account type -> Student
	 *  - login type Admin
	 *  - new Balance > 0.
	 */
	public void withdrawTest_amountAboveZero7(){

		String account = "00001 Daljit               A 00966.61 0002 S";
		BankAccount accountTest = new BankAccount(account);
		Transaction.Withdrawal(accountTest, 0500.00f, true); //amount = 1000.10, admin = true
		assertEquals(00466.61f,accountTest.getBalance(), 1e-2);
	}

	@Test
	/*
	 * Test for: 
	 * 	- Withdraw amount > 0
	 *  - Account is active
	 *  - Account type -> Student
	 *  - login type -> Not-Admin
	 *  - Withdraw limit violation. 
	 */
	public void withdrawTest_amountAboveZero8(){

		String account = "00001 Daljit               A 00966.61 0002 S";
		BankAccount accountTest = new BankAccount(account);
		Transaction.Withdrawal(accountTest, 01005.10f, false); //amount = 1000.10, admin = false.
		assertEquals(00966.61f,accountTest.getBalance(), 1e-2);
	}

	@Test
	/*
	 * Test for: 
	 * 	- Withdraw amount > 0.
	 *  - Account is active.
	 *  - Account type -> Student.
	 *  - login type -> Not-Admin.
	 *  - No Withdraw limit violation.
	 *  - new balance < 0
	 *   
	 */
	public void withdrawTest_amountAboveZero9(){

		String account = "00001 Daljit               A 00050.00 0002 S";
		BankAccount accountTest = new BankAccount(account);
		Transaction.Withdrawal(accountTest, 00500.00f, false); //amount = 1000.10, admin = false.
		assertEquals(00050.00f,accountTest.getBalance(), 1e-2);
	}

	@Test
	/*
	 * Test for: 
	 * 	- Withdraw amount > 0.
	 *  - Account is active.
	 *  - Account type -> Student.
	 *  - login type -> Not-Admin.
	 *  - No Withdraw limit violation.
	 *  - new balance > 0.
	 */
	public void withdrawTest_amountAboveZero10(){

		String account = "00001 Daljit               A 00700.00 0002 S";
		BankAccount accountTest = new BankAccount(account);
		Transaction.Withdrawal(accountTest, 500.00f, false); //amount = 1000.10, admin = false.
		assertEquals(199.95f,accountTest.getBalance(), 1e-2);
	}	
	
	@Test
	/* Test for: 
	 * 	- Account is not active.
	 */
	public void withdrawTest_accountNotActive(){
		String account = "00001 Daljit               D 00700.00 0002 S";
		BankAccount accountTest = new BankAccount(account);
		Transaction.Withdrawal(accountTest, 500.00f, false);
		assertEquals(false, accountTest.isActive());
	}

	public static junit.framework.Test suite(){
		return new JUnit4TestAdapter(Withdraw_Tests.class);
	}
}