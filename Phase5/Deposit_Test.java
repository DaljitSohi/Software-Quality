import static org.junit.Assert.*;
import org.junit.Test;
import junit.framework.JUnit4TestAdapter;

public class Deposit_Test {

	@Test  
	/* Test for
	 *  - Deposit amount < 0.
	 */

	public void DepositTest_amountBelowZero(){
		String account = "00001 Daljit               A 06966.61 0002 N";
		BankAccount accountTest = new BankAccount(account);
		BankAccount temp = Transaction.Deposit(accountTest, -1, true); //amount = -1, admin = true
		assertNull(temp);
	}

	@Test
	/*
	 * Test for: 
	 * 	- Deposit amount > 0
	 *  - Account is active
	 *  - Account type -> Not Student
	 *  - login type Admin
	 */
	public void DepositTest_amountAboveZero1(){

		String account = "00001 Daljit               A 00966.61 0002 N";
		BankAccount accountTest = new BankAccount(account);
		Transaction.Deposit(accountTest, 1000.00f, true); //amount = 1000.10, admin = true
		assertEquals(01966.61f,accountTest.getBalance(), 1e-2);
	}

	@Test
	/*
	 * Test for: 
	 * 	- Deposit amount > 0
	 *  - Account is active
	 *  - Account type -> Not Student
	 *  - login type -> Not-Admin
	 */
	public void DepositTest_amountAboveZero3(){

		String account = "00001 Daljit               A 00966.61 0002 N";
		BankAccount accountTest = new BankAccount(account);
		Transaction.Deposit(accountTest, 02001.00f, false); //amount = 1000.00, admin = false.
		assertEquals(02967.51f,accountTest.getBalance(), 1e-2);
	}

	@Test
	/*
	 * Test for: 
	 * 	- Deposit amount > 0
	 *  - Account is active
	 *  - Account type -> Student
	 *  - login type Admin
	 */
	public void DepositTest_amountAboveZero6(){

		String account = "00001 Daljit               A 00966.61 0002 S";
		BankAccount accountTest = new BankAccount(account);
		Transaction.Deposit(accountTest, 1000.10f, true); //amount = 1000.10, admin = true
		assertEquals(1966.71f,accountTest.getBalance(), 1e-2);
	}

	@Test
	/*
	 * Test for: 
	 * 	- Deposit amount > 0
	 *  - Account is active
	 *  - Account type -> Student
	 *  - login type -> Not-Admin
	 */  
	public void DepositTest_amountAboveZero8(){

		String account = "00001 Daljit               A 00966.61 0002 S";
		BankAccount accountTest = new BankAccount(account);
		Transaction.Deposit(accountTest, 02001.10f, false); //amount = 1000.10, admin = false.
		assertEquals(2967.66f,accountTest.getBalance(), 1e-2);
	}
	@Test
	/* Test for: 
	 * 	- Account is not active.
	 */
	public void DepositTest_accountNotActive(){
		String account = "00001 Daljit               D 00700.00 0002 S";
		BankAccount accountTest = new BankAccount(account);
		Transaction.Deposit(accountTest, 500.00f, false);
		assertEquals(false, accountTest.isActive());
	}
	
	public static junit.framework.Test suite(){
		return new JUnit4TestAdapter(Deposit_Test.class);
	}
}