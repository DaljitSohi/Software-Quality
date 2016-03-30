import static org.junit.Assert.*;
import org.junit.Test;
import junit.framework.JUnit4TestAdapter;

public class TransactionTest {

	@Test //Test the Enable method
	public void enableTest() {

		//BankAccount obj 'account'
		String account = "00001 Daljit               A 06966.61 0002 S";
		BankAccount accountTest = new BankAccount(account); 
		Transaction.Enable(accountTest);//call Enable method on 'account'
		assertEquals(true, accountTest.isActive()); //expected: true, actual: what isActive[BankAccount function] will return.
	}

	@Test //Test the Disable method
	public void disableTest(){
		String account = "00001 Daljit               A 06966.61 0002 S";
		BankAccount accountTest = new BankAccount(account);
		Transaction.Disable(accountTest);
		assertEquals(false, accountTest.isActive());
	}

	@Test //Test create a new account
	public void creatAccountTest()
	{
		//String account = "01234 Daljit-S-S               A 05000.00 0002 S";
		BankAccount accountTest = Transaction.Create("Daljit-S-S", 01234, 05000.00f);
		assertEquals("Daljit-S-S", accountTest.getAccountName());
		assertEquals(01234, accountTest.getAccountNumber());
		assertEquals(05000.00f, accountTest.getBalance(), 1e-2);
	}

	@Test
	/*
	 * Test for: 
	 * 	- Change Non-Student Plan to Student.
	 */
	public void transactionTest_changePlan(){

		String account = "00001 Daljit               D 00700.00 0002 N";
		BankAccount accountTest = new BankAccount(account);
		Transaction.Changeplan(accountTest);
		assertEquals(true, accountTest.isStudent());
	}

	@Test
	/*
	 * Test for:
	 *  - Change Student Plan to Non Student.
	 */
	public void transactionTest_changePlan_toNonStudent(){

		String account = "00001 Daljit               D 00700.00 0002 S";
		BankAccount accountTest = new BankAccount(account);
		Transaction.Changeplan(accountTest);
		assertEquals(false, accountTest.isStudent());
	}

	public static junit.framework.Test suite(){
		return new JUnit4TestAdapter(TransactionTest.class);
	}
}