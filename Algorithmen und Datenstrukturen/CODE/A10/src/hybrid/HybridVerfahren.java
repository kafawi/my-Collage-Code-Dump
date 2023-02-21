package hybrid;

import symm.BlockVerfahren;
import unsymm.RSAVerfahren;

public class HybridVerfahren {

  private RSAVerfahren rsa;
  private BlockVerfahren block;
  
  public HybridVerfahren(){
	  rsa = new RSAVerfahren();
	  rsa.unsymmVerfahren();
	  block = new BlockVerfahren();
  }
  
  /*
  public static void someMethod(){
    int nebenModul = RSAVerfahren.getNebenmodul(PrimGenerator.getPrim(),PrimGenerator.getPrim());
    
    int publicRSAKEY = PublicKey.getPublicKey(nebenModul);
    int privateRSAKey = PrivateKey.getPriKey(publicRSAKEY, nebenModul);
  }
  */
  public int getPublicKey(){
	  return rsa.getPublicKey();
  }
  public int getRsaModul(){
	  return rsa.getRsaModul();
  }
  
  public String decrypt(String kryptS){
	  int[] intKryptArray = block.convertToInt(kryptS);
	  int[] skey = new int[2];
	  skey[0] = crypt2Skey(intKryptArray, 0);
	  skey[1] = crypt2Skey(intKryptArray, 4);
	  intKryptArray[0] = rsa.decrypt(skey[0]);
	  intKryptArray[1] = rsa.decrypt(skey[1]);
	  String clearS = block.decrypt(intKryptArray);
	  return clearS;
  }
  
  private void skey2Crypt(int[] intKryptArray, int start, int skey){
	  int base = BlockVerfahren.MODNUM;
	  intKryptArray[start] = skey / ((int)Math.pow(base, 3));
      intKryptArray[start+1] = (skey % ((int)Math.pow(base, 3)))/ ((int)Math.pow(base, 2));;;
      intKryptArray[start+2] = (skey % ((int)Math.pow(base, 2)))/ base;
	  intKryptArray[start+3] = skey % base;
  }
  private int crypt2Skey(int[] intKryptArray, int start){
	  int skey=0;
	  int base = BlockVerfahren.MODNUM;
	  skey += intKryptArray[start]   * ((int) Math.pow(base, 3));
	  skey += intKryptArray[start+1] * ((int) Math.pow(base, 2));
	  skey += intKryptArray[start+2] * base;
	  skey += intKryptArray[start+3];
	  return skey;
  }
  
  
  public String encrypt(String clearS, int pubKey, int rsaMod){
	  int[] intKryptArray = block.encrypt(clearS);
	  int[] skey = new int[2];
	  skey[0] = rsa.encrypt(intKryptArray[0], pubKey, rsaMod);
	  skey[1] = rsa.encrypt(intKryptArray[1], pubKey, rsaMod);
	  skey2Crypt(intKryptArray, 0, skey[0]);
	  skey2Crypt(intKryptArray, 4, skey[1]);
	  String kryptS = block.convertToString(intKryptArray);
	  return kryptS;
  }
  
  
}
