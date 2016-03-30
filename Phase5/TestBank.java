import static org.junit.Assert.*;
import junit.framework.JUnit4TestAdapter;
import org.junit.Test;
import java.io.*;

public class TestBank {
    public static junit.framework.Test suite(){
       return new JUnit4TestAdapter(TestBank.class);
    }
    /**
    *set up file for testing
    */
    public String Setup_File(String... params)
    {        
        String testFile = "TestFile.txt";
        //check code run once
        PrintWriter current = null;
        try
        {
            current = new PrintWriter(new BufferedWriter(new FileWriter(testFile)));
            for(String s: params)
                current.println(s);
            current.close();
        }
        catch (Exception e){}

        return testFile;
    }



    /**
    * test for main function
    * checking if args < 2
    */
    @Test
    public void Bke_mainless2() {
        File master, current;

        master = new File("MasterBankAccountsFile.bank");
        current = new File("CurrentBankAccounts.bank");
        master.delete();
        current.delete();
        backend.main(new String[]{""});
        assertFalse(master.exists());
        assertFalse(current.exists());
    }


    /**
    * test for main function
    * checking if args > 2
    * also check the while statement with many runs
    * and check interpet.writeoutbankaccount for many
    */
    @Test
    public void Bke_main2() {
        File master, current;

        master = new File("MasterBankAccountsFile.bank");
        current = new File("CurrentBankAccounts.bank");
        master.delete();
        current.delete();

        backend.main(new String[]{"BankAccountTransaction.txt", "Master_Accounts.bank"});
        
        assertTrue(master.exists());
        assertTrue(current.exists());
    }



    /**
    * test for main function
    * check the while statement with 0 runs
    * and check interpet.writeoutbankaccount for many
    */
    @Test
    public void Bke_mainR0() {
        File master, current;
        master = new File("MasterBankAccountsFile.bank");
        current = new File("TestFile.txt");
        master.delete();
        current.delete();

        String testFile = Setup_File();
        backend.main(new String[]{ testFile, "Master_Accounts.bank"});
        
        assertTrue(master.exists());
        assertTrue(current.exists());
    }


    /**
    * test for main function
    * check the while statement with 1 runs
    * and check interpet.writeoutbankaccount for one test
    */
    @Test
    public void Bke_mainR1() {
        File master, current;
        master = new File("MasterBankAccountsFile.bank");
        current = new File("TestFile.txt");
        master.delete();
        current.delete();

        String testFile = Setup_File("10                      00000 00000.00 A ");
        //check code run once
        backend.main(new String[]{ testFile, "Master_Accounts.bank"});
        
        assertTrue(master.exists());
        assertTrue(current.exists());
    }

    /**
    * test for main function
    * check the while statement with 2 runs
    * and check interpet.writeoutbankaccount for two test
    */
    @Test
    public void Bke_mainR2() {
        File master, current;
        master = new File("MasterBankAccountsFile.bank");
        current = new File("TestFile.txt");
        master.delete();
        current.delete();

        String testFile = Setup_File("10                      00000 00000.00 A ", "10                      00000 00000.00 A ");
        //check code run twice
        backend.main(new String[]{ testFile, "Master_Accounts.bank"});
        
        assertTrue(master.exists());
        assertTrue(current.exists());
    }

 /**
    * test the constructor of bankaccount
    */

    @Test
    public void Bnk_Constructor() {
        BankAccount t = new BankAccount("00001 Daljit               A 06666.66 0000 S");
        assertEquals(1, t.getAccountNumber());
        assertEquals("Daljit", t.getAccountName());
        assertEquals(true, t.isActive());
        assertEquals(true, t.isStudent());
        assertEquals((double)6666.66, (double)t.getBalance(), 1e-2);
    }
    
    /**
    * test output for the master bankaccount file
    * check is active is student
    */
    @Test
    public void Bnk_masterfileformatAS() {
        BankAccount t = new BankAccount("00001 Daljit               A 06666.66 0000 S");
        assertEquals("00001 Daljit               A 06666.66 0000 S", t.masterFileFormat());
    }

    /**
    * test output for the master bankaccount file
    * check is active is non-student
    */
    @Test
    public void Bnk_masterfileformatAN() {
        BankAccount t = new BankAccount("00001 Daljit               A 06666.66 0000 N");
        assertEquals("00001 Daljit               A 06666.66 0000 N", t.masterFileFormat());
    }

    /**
    * test output for the master bankaccount file
    * check is deactive is student
    */
    @Test
    public void Bnk_masterfileformatDS() {
        BankAccount t = new BankAccount("00001 Daljit               D 06666.66 0000 S");
        assertEquals("00001 Daljit               D 06666.66 0000 S", t.masterFileFormat());
    }

    /**
    * test output for the master bankaccount file
    * check is deactive is non-student
    */
    @Test
    public void Bnk_masterfileformatDN() {
        BankAccount t = new BankAccount("00001 Daljit               D 06666.66 0000 N");
        assertEquals("00001 Daljit               D 06666.66 0000 N", t.masterFileFormat());
    }



    /**
    * test output for the Current bankaccount file
    * check is active is student
    */
    @Test
    public void Bnk_currentfileformatAS() {
        BankAccount t = new BankAccount("00001 Daljit               A 06666.66 0000 S");
        assertEquals("00001 Daljit               A 06666.66 S", t.currentFileFormat());
    }

    /**
    * test output for the Current bankaccount file
    * check is active is non-student
    */
    @Test
    public void Bnk_currentfileformatAN() {
        BankAccount t = new BankAccount("00001 Daljit               A 06666.66 0000 N");
        assertEquals("00001 Daljit               A 06666.66 N", t.currentFileFormat());
    }

    /**
    * test output for the Current bankaccount file
    * check is deactive is student
    */
    @Test
    public void Bnk_currentfileformatDS() {
        BankAccount t = new BankAccount("00001 Daljit               D 06666.66 0000 S");
        assertEquals("00001 Daljit               D 06666.66 S", t.currentFileFormat());
    }

    /**
    * test output for the Current bankaccount file
    * check is deactive is non-student
    */
    @Test
    public void Bnk_currentfileformatDN() {
        BankAccount t = new BankAccount("00001 Daljit               D 06666.66 0000 N");
        assertEquals("00001 Daljit               D 06666.66 N", t.currentFileFormat());
    }

    /**
    * test the constructor of Token
    */
    @Test
    public void Tkn_Constructor() {
        Token t = new Token("08 Sam-c                00019 00000.00 NP");
        assertEquals(8, t.getCommand());
        assertEquals("Sam-c", t.getName());
        assertEquals(19, t.getNumber());
        assertEquals(0.0f, t.getMoney(), 1e-2);
        assertEquals("NP", t.getMisc());           
    }

    /**
    * test the constructor of Interpeter
    *test for bad file name
    */
    @Test
    public void Int_ConstructorBadFile() {

        //test bad file, aka 0 time run on for statement
        Interpreter interpret = new Interpreter("temp");
        assertNull(interpret.bankAccounts);
    }

    /**
    * test the constructor of Interpeter
    *test for 0 time run while statement
    */
    @Test
    public void Int_ConstructorR0() {

        String testFile = Setup_File();
        Interpreter interpret = new Interpreter(testFile);
        assertEquals(interpret.bankAccounts.size(), 0);
    }


    /**
    * test the constructor of Interpeter
    * test for 1 time run while statement
    */
    @Test
    public void Int_ConstructorR1() {

        String testFile = Setup_File("00001 Daljit               A 06666.66 0000 S");
        //check code run once
        Interpreter interpret = new Interpreter(testFile);
        assertEquals(interpret.bankAccounts.size(), 1);
    }

    /**
    * test the constructor of Interpeter
    * test for 2 time run while statement
    */
    @Test
    public void Int_ConstructorR2() {

        String testFile = Setup_File("00001 Daljit               A 06666.66 0000 S", "00002 Daljit               A 06666.66 0000 S");
        //check code run twice
        Interpreter interpret = new Interpreter(testFile);
        assertEquals(interpret.bankAccounts.size(), 2);
    }

    /**
    * test the constructor of Interpeter
    * test for many time run while statement
    */
    @Test
    public void Int_ConstructorRmany() {

        String testFile = Setup_File("00001 Daljit               A 06666.66 0000 S", "00002 Daljit               A 06666.66 0000 S", "00003 Daljit               A 06666.66 0000 S");
        //check code run many times
        Interpreter interpret = new Interpreter(testFile);
        assertEquals(interpret.bankAccounts.size(), 3);
    }

    /**
    *   test search with null bankaccount 
    */
    @Test
    public void Int_SearchBadFile() {

        //test bad file, aka 0 time run on for statement
        Interpreter interpret = new Interpreter("temp");
        assertNull(interpret.search("matt"));
    }

    /**
    *   test search with 0 bankaccounts
    */
    @Test
    public void Int_searchR0() {

        String testFile = Setup_File();
        Interpreter interpret = new Interpreter(testFile);
        assertNull(interpret.search("Matt"));
    }


    /**
    * test the search of Interpeter
    * test for 1 time run for statement
    */
    @Test
    public void Int_searchR1() {

        String testFile = Setup_File("00001 Daljit               A 06666.66 0000 S");
        //check code run once
        Interpreter interpret = new Interpreter(testFile);
        assertEquals("Daljit", interpret.search("Daljit").getAccountName());
    }

    /**
    * test the search of Interpeter
    * test for 2 time run for statement
    */
    @Test
    public void Int_searchR2() {

        String testFile = Setup_File("00001 Daljit-              A 06666.66 0000 S", "00002 Daljit               A 06666.66 0000 S");
        //check code run twice
        Interpreter interpret = new Interpreter(testFile);
        assertEquals("Daljit", interpret.search("Daljit").getAccountName());
    }

    /**
    * test the search of Interpeter
    * test for many time run for statement
    */
    @Test
    public void Int_searchRmany() {

        String testFile = Setup_File("00001 Daljit1              A 06666.66 0000 S", "00002 Daljit2              A 06666.66 0000 S", "00003 Daljit               A 06666.66 0000 S");
        //check code run many times
        Interpreter interpret = new Interpreter(testFile);
        assertEquals("Daljit", interpret.search("Daljit").getAccountName());
    }

  /**
    * test for interpet function
    * checking if bankaccount is null
    */
    @Test
    public void Int_InterpetBadFile() {

        //test bad file, aka 0 time run on for statement
        Token t = new Token("08 Sam-c                00019 00000.00 NP");
        Interpreter interpret = new Interpreter("temp");
        assertNull(interpret.interpret(t));
    }

    /**
    * test for interpet function
    * checking if token is 0
    */
    @Test
    public void Int_InterpetLogout() {

        //test bad file, aka 0 time run on for statement
        Token t = new Token("00                      00000 00000.00 A ");
        Interpreter interpret = new Interpreter("Master_Accounts.bank");
        assertNull(interpret.interpret(t));
    }

    /**
    * test for interpet function
    * checking if token is 10 and is not 0
    * admin login
    */
    @Test
    public void Int_Interpetloginadmin() {

        Token t = new Token("10                      00000 00000.00 A ");
        Interpreter interpret = new Interpreter("Master_Accounts.bank");
        assertNull(interpret.interpret(t));
    }

    /**
    * test for interpet function
    * checking if token is 10 
    * standard login and not admin
    */
    @Test
    public void Int_Interpetloginstandard() {

        //test bad file, aka 0 time run on for statement
        Token t = new Token("10 Daljit               00001 00000.00 S ");
        Interpreter interpret = new Interpreter("Master_Accounts.bank");
        assertNull(interpret.interpret(t));
    }

    /**
    * test for interpet function
    * checking if name doesnt exist and token is 5
    * check create
    */
    @Test
    public void Int_Interpetcreate() {

        //test bad file, aka 0 time run on for statement
        Token t = new Token("05 Kyle                 00010 04000.00   ");
        Interpreter interpret = new Interpreter("Master_Accounts.bank");
        BankAccount b = interpret.interpret(t);
        assertEquals("Kyle", b.getAccountName());
        assertEquals(10, b.getAccountNumber());
        assertEquals(4000.00, b.getBalance(), 1e-2);
    }

    /**
    * test for interpet function
    * checking if name doesnt exist and token is 5
    * check create where no possible new number
    */
    @Test
    public void Int_InterpetcreateNoNew() {

        Token t = new Token("05 Kyle                 00010 04000.00   ");
        Interpreter interpret = new Interpreter("Master_Account_Full.bank");
        BankAccount b = interpret.interpret(t);
        assertNull(b);
    }

    /**
    * test for interpet function
    * checking if name doesnt exist and not create function
    */
    @Test
    public void Int_InterpetWrongname() {

        Token t = new Token("06 Daljiteeeeeee        00001 00000.00 S ");
        Interpreter interpret = new Interpreter("Master_Accounts.bank");
        assertNull(interpret.interpret(t));
    }



    /**
    * test for interpet function
    * checking if name exists and command is 1
    * check withdrawal
    */
    @Test
    public void Int_Interpetwithdrawal() {
        Token t = new Token("01 Matt                 00009 00400.00   ");
        Interpreter interpret = new Interpreter("Master_Accounts.bank");
        BankAccount b = interpret.interpret(t);
        assertEquals(10000.00f-400.00f - 0.05f, b.getBalance(), 1e-2);
    }

    /**
    * test for interpet function
    * checking if command is 2
    * check transfer, give money
    */
    @Test
    public void Int_Interpettransfergive() {
        Token t = new Token("02 Neil                 00004 00500.00   ");
        Interpreter interpret = new Interpreter("Master_Accounts.bank");
        BankAccount b = interpret.interpret(t);
        assertEquals(20000.00f-500.00f - 0.10f, b.getBalance(), 1e-2);
        assertEquals(1, b.getNumberofTransactions());
    }

    /**
    * test for interpet function
    * checking if command is 2
    * check transfer, recieve money
    */
    @Test
    public void Int_Interpettransferrecieve() {
        //check with 2 tokens to show give and revieve
        Token t = new Token("02 Neil                 00004 00500.00   ");
        Token t2 = new Token("02 Sean                 00005 00500.00   ");
        Interpreter interpret = new Interpreter("Master_Accounts.bank");
        interpret.interpret(t);
        BankAccount b = interpret.interpret(t2);
        assertEquals(5000.00f+ 500f, b.getBalance(), 1e-2);
    }

    /**
    * test for interpet function
    * checking if command is 3
    * check paybill
    */
    @Test
    public void Int_Interpetpaybill() {
        Token t = new Token("03 Matt                 00009 00500.00 TV");
        Interpreter interpret = new Interpreter("Master_Accounts.bank");
        BankAccount b = interpret.interpret(t);
        assertEquals(10000.00f-500.00f-0.05f, b.getBalance(), 1e-2);
        assertEquals(1, b.getNumberofTransactions());
    }

    /**
    * test for interpet function
    * checking if command is 4
    * check deposit
    */
    @Test
    public void Int_Interpetdeposit() {
        Token t = new Token("04 Matt                 00009 00400.00   ");
        Interpreter interpret = new Interpreter("Master_Accounts.bank");
        BankAccount b = interpret.interpret(t);
        assertEquals(10000.00f+400.00f-0.05f, b.getBalance(), 1e-2);
        assertEquals(1, b.getNumberofTransactions());
    }

    /**
    * test for interpet function
    * checking if command is 6
    * check delete
    */
    @Test
    public void Int_Interpetdelete() {
        Token t = new Token("06 Matt                 00009 00000.00   ");
        Interpreter interpret = new Interpreter("Master_Accounts.bank");
        int size = interpret.bankAccounts.size();
        BankAccount b = interpret.interpret(t);
        assertNull(b);
        assertEquals(size-1, interpret.bankAccounts.size());
    }

    /**
    * test for interpet function
    * checking if command is 7
    * check disable
    */
    @Test
    public void Int_Interpetdisable() {
        Token t = new Token("07 Matt                 00009 00000.00   ");
        Interpreter interpret = new Interpreter("Master_Accounts.bank");
        BankAccount b = interpret.interpret(t);
        assertEquals(false, b.isActive());
    }

    /**
    * test for interpet function
    * checking if command is 9
    * check enable
    */
    @Test
    public void Int_Interpetenable() {
        Token t = new Token("09 Matt                 00009 00000.00   ");
        Interpreter interpret = new Interpreter("Master_Accounts.bank");
        BankAccount b = interpret.interpret(t);
        assertEquals(true, b.isActive());
    }

    /**
    * test for interpet function
    * checking if command is 8
    * check changeplan
    */
    @Test
    public void Int_Interpetchangeplan() {
        Token t = new Token("08 Matt                 00009 00000.00 NP");
        Interpreter interpret = new Interpreter("Master_Accounts.bank");
        BankAccount b = interpret.interpret(t);
        assertEquals(false, b.isStudent()); 
    }

    /**
    * test the get new number of Interpeter
    *test for 0 time run while statement
    */
    @Test
    public void Int_getnewnumberR0() {

        String testFile = Setup_File();
        Interpreter interpret = new Interpreter(testFile);
        int num = interpret.getNewNumber();
        assertEquals(1, num);
    }


    /**
    * test the get new number of Interpeter
    * test for 1 time run for statement
    */
    @Test
    public void Int_getnewnumberR1() {

        String testFile = Setup_File("00001 Daljit               A 06666.66 0000 S");
        //check code run once
        Interpreter interpret = new Interpreter(testFile);
        int num = interpret.getNewNumber();
        assertEquals(2, num);
    }

    /**
    * test the get new number of Interpeter
    * test for 2 time run for statement
    */
    @Test
    public void Int_getnewnumberR2() {

        String testFile = Setup_File("00001 Daljit               A 06666.66 0000 S", "00002 Daljit               A 06666.66 0000 S");
        //check code run twice
        Interpreter interpret = new Interpreter(testFile);
        int num = interpret.getNewNumber();
        assertEquals(3, num);
    }

    /**
    * test the get new number of Interpeter
    * test for many time run for statement
    */
    @Test
    public void Int_getnewnumberRmany() {

        String testFile = Setup_File("00001 Daljit               A 06666.66 0000 S", "00002 Daljit               A 06666.66 0000 S", "00003 Daljit               A 06666.66 0000 S");
        //check code run many times
        Interpreter interpret = new Interpreter(testFile);
        int num = interpret.getNewNumber();
        assertEquals(4, num);
    }
}