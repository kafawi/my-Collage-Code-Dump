package symm;

public class SessionKeyGenerator {

  public static int getSessionKey(){
    return (int) (Math.random()*94+1);
  }
}
