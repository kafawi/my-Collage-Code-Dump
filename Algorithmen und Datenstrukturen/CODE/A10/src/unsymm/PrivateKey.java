package unsymm;

public class PrivateKey {
  
  public static int getPrivateKey(int publicKey, int nebenModul){
    int d = nebenModul/2;
    int counter =1;
    int flip =1;
    while((publicKey*d) % nebenModul!=1){
      d+=flip*counter;
      if(d>= nebenModul){
        d=nebenModul/2;
        flip =-1;
        counter =1;
      }else if(d<=1){
        break;
      }
    }
    return d;
  }
  
  // BRUTFORCE 
  public static int getPriKey(int publicKey, int nebenModul){
	  int d = 2;
	  int res = 0;
	  do{
		  d++;
		  res = (publicKey * d)% nebenModul;
	  } while (res != 1);
	  return d;
  }

}
