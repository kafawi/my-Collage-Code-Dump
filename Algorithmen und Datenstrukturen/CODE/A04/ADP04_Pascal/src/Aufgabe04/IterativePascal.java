package code;

/**
 * This class implements Pascal's triangle iterative
 * 
 * @author Kalle
 *
 */
public class IterativePascal extends APascal {

  @Override
  public int[] calcNRow(int N) {
    // reset global count
    globalCount = 0;

    int[][] arr = new int[2][N + 1];
    arr[0][0] = 1;
    globalCount++;

    for (int i = 1; i <= N; i++) {
      int n = i % 2;
      int nMinus1 = (i - 1) % 2;
      for (int k = 0; i >= k; k++) {
        globalCount++;
        if (k == 0)
          arr[n][k] = 1;
        else
          arr[n][k] = arr[nMinus1][k - 1] + arr[nMinus1][k];
      }
    }
    return arr[N % 2];
  }

  public static void main(String[] args) {

    APascal p = new IterativePascal();
    p.calcNRow(5);
    System.err.println(globalCount);
  }

}
