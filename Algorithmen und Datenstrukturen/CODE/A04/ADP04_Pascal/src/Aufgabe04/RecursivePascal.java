package code;

/**
 * This class implements Pascal's triangle recursive
 * 
 * @author kalle
 *
 */
public class RecursivePascal extends APascal {

  private int[][] arr;

  private int     algo = 0;

  @Override
  public int[] calcNRow(int N) {
    globalCount = 0;
    int[] res = null;
    switch (algo) {
      case 0:
        arr = new int[1][N + 1];
        for (int k = N; k >= 0; k--)
          arr[0][k] = P(N, k);
        res = arr[0];
        break;
      case 1:
        arr = new int[N + 1][N + 1];
        for (int k = N; k >= 0; k--)
          advP(N, k);
        res = arr[N];
        break;
      default:
        System.err.println("choose Algo beween 0 (normal) and 1 (advaced)");
    }
    return res;
  }

  /**
   * P(N,k)= P(N-1, k-1) + P(N-1, k)
   * 
   * The rekusion without allocating the hole Array and store data
   * 
   * @param N
   *          row of triangle
   * @param k
   *          column of triangle
   * @return p(N,k)
   */
  private static int P(int N, int k) {
    globalCount++;
    int res = (N <= 1 || k == 0 || k == N) ? 1
        : (P(N - 1, k - 1) + P(N - 1, k));
    return res;
  }

  /**
   * P(N,k)= P(N-1, k-1) + P(N-1, k)
   * 
   * That is
   * 
   * @param N
   *          row of triangle
   * @param k
   *          column of triangle
   * @return P(N,k)
   */

  private int advP(int N, int k) {
    globalCount++;
    if (arr[N][k] == 0 || k < N) {
      arr[N][k] = (N <= 1 || k == 0 || k == N) ? 1
          : (advP(N - 1, k - 1) + advP(N - 1, k));
    } else {
      arr[N][k] = (N <= 1 || k == 0) ? 1 : (arr[N - 1][k - 1] + arr[N - 1][k]);
    }
    return arr[N][k];
  }

  /**
   * personal test main
   * 
   * @param args
   */
  public static void main(String[] args) {

    APascal p = new RecursivePascal();
    int N = 3;
    for (int k = 0; k <= N; k++) {
      System.err.print(P(N, k));
    }
    System.err.println();
    printArr(p.calcNRow(N));
    System.err.format("%d : %d\n",globalCount, N*N*N*N + N*N*N + N*N + N);
  }

}
