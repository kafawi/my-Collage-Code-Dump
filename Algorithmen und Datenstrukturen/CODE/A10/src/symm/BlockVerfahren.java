package symm;

public class BlockVerfahren {
	public static final int MODNUM = 95;
	public static final int OFFSET = 8;

	
	
	public String encrypt2(String msg){
		int[] intKryptArray = encrypt(msg);
		return convertToString(intKryptArray);
	}
	public int[] encrypt(String msg) {
		int[] intClearArray = convertToInt(msg);
		int skey0 = SessionKeyGenerator.getSessionKey();
		int skey1 = SessionKeyGenerator.getSessionKey();
		while (skey1 == skey0) {
			skey1 = SessionKeyGenerator.getSessionKey();
		}
		int[] intKryptArray = new int[intClearArray.length + 8];
		intKryptArray[0] = skey0;
		intKryptArray[1] = skey1;
		for (int i = 0; i < intClearArray.length; i++) {
			if (i % 2 == 0) {
				intKryptArray[i + OFFSET] = (intClearArray[i] + skey0) % MODNUM;
			} else {
				intKryptArray[i + OFFSET] = (intClearArray[i] + skey1) % MODNUM;
			}
		}
		return intKryptArray;
	}

	public String decrypt2(String msg){
		int[] intKryptArray = convertToInt(msg);
		return decrypt(intKryptArray);
	}
	
	public String decrypt(int[] intKryptArray) {
		int msgLen = intKryptArray.length - OFFSET;
		int[] intClearArray = new int[msgLen];
		int skey0 = intKryptArray[0];
		int skey1 = intKryptArray[1];

		for (int i = 0; i < msgLen; i++) {
			if (i % 2 == 0) {
				intClearArray[i] = (intKryptArray[i + OFFSET] + (MODNUM - skey0)) % MODNUM;
			} else {
				intClearArray[i] = (intKryptArray[i + OFFSET] + (MODNUM - skey1)) % MODNUM;
			}
		}
		return convertToString(intClearArray);
	}

	public static final int INT2CHAR = 32;

	public int[] convertToInt(String str) {	
		char[] cArr = str.toCharArray();
		int[] temp = new int[cArr.length];
		for (int i =0; i < temp.length; i++){
			temp[i]= (int)(cArr[i] - INT2CHAR);
		}
		return temp;
	}

	public String convertToString(int[] intClearArray) {
		char[] charClearArray = new char[intClearArray.length];
		for (int i = 0; i < intClearArray.length; i++) {
			charClearArray[i] = (char) (intClearArray[i] + INT2CHAR);
		}
		return String.valueOf(charClearArray);
	}
}
