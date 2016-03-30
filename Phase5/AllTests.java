import org.junit.runner.RunWith;
import org.junit.runners.Suite;
import org.junit.runners.Suite.SuiteClasses;

@RunWith(Suite.class)
@SuiteClasses({ Deposit_Test.class, Paybill_Test.class, TransactionTest.class, Transfer_TestClass.class,
		Withdraw_Tests.class, TestBank.class })
public class AllTests {

}