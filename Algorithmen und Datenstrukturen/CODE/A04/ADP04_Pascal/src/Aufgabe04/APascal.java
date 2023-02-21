/**
 * 
 */
package code;

/**
 * Interface to realyse different implementations of Pascal's triangle
 * 
 * @author Die Witte Gang
 *
 */
public abstract class APascal {
  
  /**
   * global count to analyse the complexity
   */
  public static long globalCount=0;
  
  /**
   * calculating the Nth Row of Pascal's triangle
   * @param N Row,number of interest
   * @return Nth Row as array
   */
  public abstract int[] calcNRow(int N);
  
  /**
   * Debug pöpis
   * @param arr
   */
  public static void printArr(int[] arr){
    for (int i=0; arr.length > i; i++){
      System.err.print(arr[i]);
    }
    System.err.println();
  }

}
