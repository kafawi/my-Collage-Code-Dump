package hybrid;

import static org.junit.Assert.*;

import org.junit.Test;

public class TestVerfahren {

	
	@Test
	  public void testCrypt(){
		HybridVerfahren test = new HybridVerfahren();
		int pubKey = test.getPublicKey();
		int rsaMod = test.getRsaModul();
		String clear = "geile Verschluesselung";
		String unclear = test.encrypt(clear, pubKey, rsaMod);
		String unkrypt = test.decrypt(unclear);
		System.out.println(clear);
		System.out.println(unclear);
		System.out.println(unkrypt);
		assertEquals(clear, unkrypt);
		assertNotEquals(clear,unclear);	
	  }
	
	
	
	
	
	
	
}
