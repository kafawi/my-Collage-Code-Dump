package unsymm;
/**
 * Euklidischer Algorithmus
 * @author peter
 *
 */
public class Euklid {
  public static int ggt(int a, int b){
    if(b==0)return a;
    else return ggt(b, a%b);
  }
}
