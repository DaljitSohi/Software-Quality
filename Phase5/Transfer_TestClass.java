import static org.junit.Assert.*;
import org.junit.Test;
import junit.framework.JUnit4TestAdapter;

public class Transfer_TestClass {
	
	@Test 
	/*
	 * Test for:
	 * 	- when transfer is true.
	 */
	public void transferIsTrue(){
		
		String account = "00001 Daljit               A 06966.61 0002 N";
		BankAccount accountTest = new BankAccount(account);
		BankAccount temp = Transaction.Transfer(accountTest, 10.00f, true, true); //amount = -1, admin = true
		assertEquals(6976.61, temp.getBalance(), 1e-2);
		
	}

	@Test  
	/* Test for
	 *  - Transfer amount < 0.
	 */

	public void transferTest_amountBelowZero(){
		String account = "00001 Daljit               A 06966.61 0002 N";
		BankAccount accountTest = new BankAccount(account);
		BankAccount temp = Transaction.Transfer(accountTest, -1, true, false); //amount = -1, admin = true
		assertNull(temp);
	}


	@Test
	/*
	 * Test for: 
	 * 	- Transfer amount > 0
	 *  - Account is active
	 *  - Account type -> Not Student
	 *  - login type Admin
	 *  - new Balance < 0.
	 */
	public void transferTest_amountAboveZero1(){

		String account = "00001 Daljit               A 00966.61 0002 N";
		BankAccount accountTest = new BankAccount(account);
		Transaction.Transfer(accountTest, 1000.10f, true, false); //amount = 1000.10, admin = true
		assertEquals(00966.61f,accountTest.getBalance(), 1e-2);
	}

	@Test
	/*
	 * Test for: 
	 * 	- Transfer amount > 0
	 *  - Account is active
	 *  - Account type -> Not Student
	 *  - login type Admin
	 *  - new Balance > 0.
	 */
	public void transferTest_amountAboveZero2(){

		String account = "00001 Daljit               A 00966.61 0002 N";
		BankAccount accountTest = new BankAccount(account);
		Transaction.Transfer(accountTest, 0500.10f, true, false); //amount = 1000.10, admin = true
		assertEquals(00466.51f,accountTest.getBalance(), 1e-2);
	}

	@Test
	/*
	 * Test for: 
	 * 	- Transfer amount > 0
	 *  - Account is active
	 *  - Account type -> Not Student
	 *  - login type -> Not-Admin
	 *  - Transfer limit violation. 
	 */
	public void transferTest_amountAboveZero3(){

		String account = "00001 Daljit               A 00966.61 0002 N";
		BankAccount accountTest = new BankAccount(account);
		Transaction.Transfer(accountTest, 01001.10f, false, false); //amount = 1000.10, admin = false.
		assertEquals(00966.61f,accountTest.getBalance(), 1e-2);
	}

	@Test
	/*
	 * Test for: 
	 * 	- Transfer amount > 0.
	 *  - Account is active.
	 *  - Account type -> Not Student.
	 *  - login type -> Not-Admin.
	 *  - No transfer limit violation.
	 *  - new balance < 0
	 *   
	 */
	public void transferTest_amountAboveZero4(){

		String account = "00001 Daljit               A 00050.00 0002 N";
		BankAccount accountTest = new BankAccount(account);
		Transaction.Transfer(accountTest, 00500.00f, false, false); //amount = 1000.10, admin = false.
		assertEquals(00050.00f,accountTest.getBalance(), 1e-2);
	}

	@Test
	/*
	 * Test for: 
	 * 	- Transfer amount > 0.
	 *  - Account is active.
	 *  - Account type -> Not Student.
	 *  - login type -> Not-Admin.
	 *  - No transfer limit violation.
	 *  - new balance > 0.
	 */
	public void transferTest_amountAboveZero5(){

		String account = "00001 Daljit               A 00700.00 0002 N";
		BankAccount accountTest = new BankAccount(account);
		Transaction.Transfer(accountTest, 500.00f, false, false); //amount = 1000.10, admin = false.
		assertEquals(199.90f,accountTest.getBalance(), 1e-2);
	}	

	@Test
	/*
	 * Test for: 
	 * 	- Transfer amount > 0
	 *  - Account is active
	 *  - Account type -> Student
	 *  - login type Admin
	 *  - new Balance < 0.
	 */
	public void transferTest_amountAboveZero6(){

		String account = "00001 Daljit               A 00966.61 0002 S";
		BankAccount accountTest = new BankAccount(account);
		Transaction.Transfer(accountTest, 1000.10f, true, false); //amount = 1000.10, admin = true
		assertEquals(00966.61f,accountTest.getBalance(), 1e-2);
	}

	@Test
	/*
	 * Test for: 
	 * 	- Transfer amount > 0
	 *  - Account is active
	 *  - Account type -> Student
	 *  - login type Admin
	 *  - new Balance > 0.
	 */
	public void transferTest_amountAboveZero7(){

		String account = "00001 Daljit               A 00966.61 0002 S";
		BankAccount accountTest = new BankAccount(account);
		Transaction.Transfer(accountTest, 0500.10f, true, false); //amount = 1000.10, admin = true
		assertEquals(00466.51f,accountTest.getBalance(), 1e-2);
	}

	@Test
	/*
	 * Test for: 
	 * 	- Transfer amount > 0
	 *  - Account is active
	 *  - Account type -> Student
	 *  - login type -> Not-Admin
	 *  - Transfer limit violation. 
	 */
	public void transferTest_amountAboveZero8(){

		String account = "00001 Daljit               A 00966.61 0002 S";
		BankAccount accountTest = new BankAccount(account);
		Transaction.Transfer(accountTest, 01001.10f, false, false); //amount = 1000.10, admin = false.
		assertEquals(00966.61f,accountTest.getBalance(), 1e-2);
	}

	@Test
	/*
	 * Test for: 
	 * 	- Transfer amount > 0.
	 *  - Account is active.
	 *  - Account type -> Student.
	 *  - login type -> Not-Admin.
	 *  - No transfer limit violation.
	 *  - new balance < 0
	 *   
	 */
	public void transferTest_amountAboveZero9(){

		String account = "00001 Daljit               A 00050.00 0002 S";
		BankAccount accountTest = new BankAccount(account);
		Transaction.Transfer(accountTest, 00500.00f, false, false); //amount = 1000.10, admin = false.
		assertEquals(00050.00f,accountTest.getBalance(), 1e-2);
	}

	@Test
	/*
	 * Test for: 
	 * 	- Transfer amount > 0.
	 *  - Account is active.
	 *  - Account type -> Student.
	 *  - login type -> Not-Admin.
	 *  - No transfer limit violation.
	 *  - new balance > 0.
	 */
	public void transferTest_amountAboveZero10(){

		String account = "00001 Daljit               A 00700.00 0002 S";
		BankAccount accountTest = new BankAccount(account);
		Transaction.Transfer(accountTest, 500.00f, false, false); //amount = 1000.10, admin = false.
		assertEquals(199.95f,accountTest.getBalance(), 1e-2);
	}	

	@Test
	/* Test for: 
	 * 	- Account is not active.
	 */
	public void transferTest_accountNotActive(){
		String account = "00001 Daljit               D 00700.00 0002 S";
		BankAccount accountTest = new BankAccount(account);
		Transaction.Transfer(accountTest, 500.00f, false, false);
		assertEquals(false, accountTest.isActive());
	}

	public static junit.framework.Test suite(){
		return new JUnit4TestAdapter(Transfer_TestClass.class);
	}
}
