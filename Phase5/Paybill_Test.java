import static org.junit.Assert.*;
import org.junit.Test;
import junit.framework.JUnit4TestAdapter;

public class Paybill_Test {

	@Test  
	/* Test for
	 *  - Bill amount < 0.
	 */

	public void BillTest_amountBelowZero(){
		String account = "00001 Daljit               A 06966.61 0002 N";
		BankAccount accountTest = new BankAccount(account);
		BankAccount temp = Transaction.Paybill(accountTest, -1, account, true); //amount = -1, admin = true
		assertNull(temp);
	}


	@Test
	/*
	 * Test for: 
	 * 	- Bill amount > 0
	 *  - Account is active
	 *  - Account type -> Not Student
	 *  - login type Admin
	 *  - new Balance < 0.
	 */
	public void BillTest_amountAboveZero1(){

		String account = "00001 Daljit               A 00966.61 0002 N";
		BankAccount accountTest = new BankAccount(account);
		Transaction.Paybill(accountTest, 1000.10f, account, true); //amount = 1000.10, admin = true
		assertEquals(00966.61f,accountTest.getBalance(), 1e-2);
	}

	@Test
	/*
	 * Test for: 
	 * 	- Bill amount > 0
	 *  - Account is active
	 *  - Account type -> Not Student
	 *  - login type Admin
	 *  - new Balance > 0.
	 */
	public void BillTest_amountAboveZero2(){

		String account = "00001 Daljit               A 00966.61 0002 N";
		BankAccount accountTest = new BankAccount(account);
		Transaction.Paybill(accountTest, 0500.10f, account, true); //amount = 1000.10, admin = true
		assertEquals(00466.51f,accountTest.getBalance(), 1e-2);
	}

	@Test
	/*
	 * Test for: 
	 * 	- Bill amount > 0
	 *  - Account is active
	 *  - Account type -> Not Student
	 *  - login type -> Not-Admin
	 *  - Bill limit violation. 
	 */
	public void BillTest_amountAboveZero3(){

		String account = "00001 Daljit               A 00966.61 0002 N";
		BankAccount accountTest = new BankAccount(account);
		Transaction.Paybill(accountTest, 02001.10f, account, false); //amount = 1000.10, admin = false.
		assertEquals(00966.61f,accountTest.getBalance(), 1e-2);
	}

	@Test
	/*
	 * Test for: 
	 * 	- Bill amount > 0.
	 *  - Account is active.
	 *  - Account type -> Not Student.
	 *  - login type -> Not-Admin.
	 *  - No Bill limit violation.
	 *  - new balance < 0
	 *   
	 */
	public void BillTest_amountAboveZero4(){

		String account = "00001 Daljit               A 00050.00 0002 N";
		BankAccount accountTest = new BankAccount(account);
		Transaction.Paybill(accountTest, 00500.00f, account, false); //amount = 1000.10, admin = false.
		assertEquals(00050.00f,accountTest.getBalance(), 1e-2);
	}

	@Test
	/*
	 * Test for: 
	 * 	- Bill amount > 0.
	 *  - Account is active.
	 *  - Account type -> Not Student.
	 *  - login type -> Not-Admin.
	 *  - No Bill limit violation.
	 *  - new balance > 0.
	 */
	public void BillTest_amountAboveZero5(){

		String account = "00001 Daljit               A 00700.00 0002 N";
		BankAccount accountTest = new BankAccount(account);
		Transaction.Paybill(accountTest, 500.00f, account, false); //amount = 1000.10, admin = false.
		assertEquals(199.90f,accountTest.getBalance(), 1e-2);
	}	

	@Test
	/*
	 * Test for: 
	 * 	- Bill amount > 0
	 *  - Account is active
	 *  - Account type -> Student
	 *  - login type Admin
	 *  - new Balance < 0.
	 */
	public void BillTest_amountAboveZero6(){

		String account = "00001 Daljit               A 00966.61 0002 S";
		BankAccount accountTest = new BankAccount(account);
		Transaction.Paybill(accountTest, 1000.10f, account, true); //amount = 1000.10, admin = true
		assertEquals(966.61f,accountTest.getBalance(), 1e-2);
	}

	@Test
	/*
	 * Test for: 
	 * 	- Bill amount > 0
	 *  - Account is active
	 *  - Account type -> Student
	 *  - login type Admin
	 *  - new Balance > 0.
	 */
	public void BillTest_amountAboveZero7(){

		String account = "00001 Daljit               A 00966.61 0002 S";
		BankAccount accountTest = new BankAccount(account);
		Transaction.Paybill(accountTest, 0500.10f, account, true); //amount = 1000.10, admin = true
		assertEquals(00466.51f,accountTest.getBalance(), 1e-2);
	}

	@Test
	/*
	 * Test for: 
	 * 	- Bill amount > 0
	 *  - Account is active
	 *  - Account type -> Student
	 *  - login type -> Not-Admin
	 *  - Bill limit violation. 
	 */
	public void BillTest_amountAboveZero8(){

		String account = "00001 Daljit               A 00966.61 0002 S";
		BankAccount accountTest = new BankAccount(account);
		Transaction.Paybill(accountTest, 02001.10f, account, false); //amount = 1000.10, admin = false.
		assertEquals(00966.61f,accountTest.getBalance(), 1e-2);
	}

	@Test
	/*
	 * Test for: 
	 * 	- Bill amount > 0.
	 *  - Account is active.
	 *  - Account type -> Student.
	 *  - login type -> Not-Admin.
	 *  - No Bill limit violation.
	 *  - new balance < 0
	 *   
	 */
	public void BillTest_amountAboveZero9(){

		String account = "00001 Daljit               A 00050.00 0002 S";
		BankAccount accountTest = new BankAccount(account);
		Transaction.Paybill(accountTest, 00500.00f, account, false); //amount = 1000.10, admin = false.
		assertEquals(00050.00f,accountTest.getBalance(), 1e-2);
	}

	@Test
	/*
	 * Test for: 
	 * 	- Bill amount > 0.
	 *  - Account is active.
	 *  - Account type -> Student.
	 *  - login type -> Not-Admin.
	 *  - No Bill limit violation.
	 *  - new balance > 0.
	 */
	public void BillTest_amountAboveZero10(){

		String account = "00001 Daljit               A 00700.00 0002 S";
		BankAccount accountTest = new BankAccount(account);
		Transaction.Paybill(accountTest, 500.00f, account, false); //amount = 1000.10, admin = false.
		assertEquals(199.95f,accountTest.getBalance(), 1e-2);
	}	
	
	@Test
	/* Test for: 
	 * 	- Account is not active.
	 */
	public void BillTest_accountNotActive(){
		String account = "00001 Daljit               D 00700.00 0002 S";
		BankAccount accountTest = new BankAccount(account);
		Transaction.Paybill(accountTest, 500.00f, account ,false);
		assertEquals(false, accountTest.isActive());
	}
	
	public static junit.framework.Test suite(){
		return new JUnit4TestAdapter(Paybill_Test.class);
	}
}