package symm;

import static org.junit.Assert.*;

import org.junit.Test;

public class VerfahrenTest {

  @Test
  public void testConvertToInt() {
    BlockVerfahren test = new BlockVerfahren();
    int[] t = test.convertToInt("Alles ist rot");
    for(int i =0; i<t.length; i++){
      System.out.println(t[i]);
    }
    int[] abc = test.convertToInt("abc");
    for(int i =0; i<abc.length; i++){
      System.out.println(abc[i]);
    }
    int[] abcShould = {65,66,67};
    assertArrayEquals(abcShould, abc);
  }
  
  @Test
  public void testCrypt(){
	BlockVerfahren test = new BlockVerfahren();
	String clear = "geile Verschluesselung";
	System.out.println(clear);
	String unclear = test.encrypt2(clear);
	int[] krypt = test.encrypt(clear);
	String unkrypt = test.decrypt(krypt);
	System.out.println(unclear);
	String clear2 = test.decrypt2(unclear);
	System.out.println(clear2);
	System.out.println(unkrypt);
	assertEquals(clear, unkrypt);
	assertEquals(clear,clear2);
	assertNotEquals(clear,unclear);	
  }

}
