package unsymm;

import java.math.BigInteger;

public class RSAVerfahren {
    
    int publicKey = 0;
    int privateKey =0;
    int rsaModul = 0;
    
  public void unsymmVerfahren(){
    int p = PrimGenerator.getPrim();
    int q = PrimGenerator.getPrim();
    while (p==q){
    	q = PrimGenerator.getPrim();
    }
    int nebenModul = getNebenmodul(p, q); //phi(N)
    int hauptmodul = getHauptModul(p, q); //N = p*q
    //e ist entweder private  oder public key
    int e = PublicKey.getPublicKey(nebenModul);
    int d = PrivateKey.getPriKey(e, nebenModul);
    publicKey = e;
    privateKey = d;
    rsaModul = hauptmodul;  
  }
  
  public void setPublicKey(int e){
	  publicKey = e;
  }
  public void setPrivateKey(int d){
	  privateKey = d;
  }
  
  public int getRsaModul(){
	  return rsaModul;
  }
  
  public void setRsaModul(int modul){
    this.rsaModul = modul;
  }
  
  public int getPublicKey(){
	  return publicKey;
  }
  
  
  public int encrypt(int intClear, int publicKey, int rsaModul ){
	  return encrypt(new int[] {intClear}, publicKey, rsaModul)[0];
  }
  
  public int[] encrypt(int[] intClearArray, int publicKey, int rsaModul){
    this.publicKey = publicKey;
    this.rsaModul = rsaModul;
	  int len = intClearArray.length;
	  int[] intKryptArray = new int[len];
	  BigInteger bigExpo = BigInteger.valueOf(publicKey);
	  BigInteger bigRsaMod = BigInteger.valueOf(rsaModul);
	  BigInteger bigClearInt; 
	  for (int i =0; i< len; i++){
        bigClearInt = BigInteger.valueOf(intClearArray[i]);
        intKryptArray[i]= bigClearInt.modPow(bigExpo, bigRsaMod).intValue();
	  }
	  return intKryptArray;
  }
  public int decrypt(int intKrypt){
	  return decrypt(new int[] {intKrypt})[0];
  }
  
  public int[] decrypt(int[] intKryptArray){
	  return decrypt(intKryptArray, privateKey, rsaModul);
  }
  
  private int[] decrypt(int[] intKryptArray, int privateKey, int rsaModul){
	  int len = intKryptArray.length;
	  int[] intClearArray = new int[len];
	  BigInteger bigExpo = BigInteger.valueOf(privateKey);
	  BigInteger bigRsaMod = BigInteger.valueOf(rsaModul);
	  BigInteger bigKryptInt;
	  for(int i = 0; i < len; i++){
		  bigKryptInt = BigInteger.valueOf(intKryptArray[i]);
		  intClearArray[i] = bigKryptInt.modPow(bigExpo, bigRsaMod).intValue();
	  }
	  return intClearArray;
  }
  
  
  
  /**
   * Auf welche art soll denn nun potenziert werden hier?
   * soll der String in ein int array umgebaut werden und dann jedes element
   * oder wie?
   * 
   * keine ahnung...
   * ich würde sagen, dass das nicht gemachte werden soll
   * Es ist ja wie in 
   * TODO
   * @param str
   * @return
   */
   public long genereiereZahlAusString(String str){
	 
     return 0l;
   }

  /**
   * Berechnet das Nebenmodul
   * @param p primzahl 1
   * @param q primzahl 2
   * @return nebenmodul
   */
  public static int getNebenmodul(int p, int q){
    return (p-1)*(q-1);
  }
  
  /**
   * Berechnet das Hauptmodul aus zwei Primzahlen
   * N=p*q
   * @param p Primzahl 1
   * @param q Primzahl 2
   * @return Hauptmodul
   */
    public static int getHauptModul(int p, int q){
      return p*q;
    }
}
