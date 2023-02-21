package unsymm;

import static org.junit.Assert.*;

import org.junit.Test;

import symm.BlockVerfahren;

public class RSATest {

	@Test
	public void test() {
		BlockVerfahren v = new BlockVerfahren(); // needed to get string to Int 
		String clear = "abcdefg";
		int[] clearInt = v.convertToInt(clear);

		RSAVerfahren rsa = new RSAVerfahren();
		rsa.unsymmVerfahren();
		int pubKey = rsa.getPublicKey();
		int rsaMod = rsa.getRsaModul();
		int[] krypt = rsa.encrypt(clearInt, pubKey, rsaMod)	;
		
		int[] dekry = rsa.decrypt(krypt);
		String kryptS = v.convertToString(krypt);
		String dekryS = v.convertToString(dekry);
		
		System.out.println(kryptS);
		//String clear2 = test.decrypt2(unclear);
		System.out.println(dekryS);
		//System.out.println(unkrypt);
		//assertEquals(clear, dekryS);
		assertArrayEquals(clearInt, dekry);
		
		//assertEquals(clear,clear2);
		//assertNotEquals(clear, kryptS);
	}

}
