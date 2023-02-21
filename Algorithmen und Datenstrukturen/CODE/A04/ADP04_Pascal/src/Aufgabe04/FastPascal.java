package code;


/**
 * This class imlpements the Pascal's triangle with binominal-coefficient-method. (Up to 65'th row)
 * 
 * @author Martin
 *
 */
public class FastPascal extends APascal {

	  
	/**
	 * This method gives a int-array of whole numbers with the N'th row of the Pascal's triangle.
	 * 
	 * @param N
	 * @return
	 */
	public int[] calcNRow(int N){
		int[] ergArray = new int[N+1];
		globalCount =0;
		//if(N == 0){
		//	ergArray[0] = 1;
		//} else {
			for(int i = 0; i < N+1; i++){
				//ergArray[i] = binomialCoefficient(N, i);
				ergArray[i] = bc(N, i);
		//	}
		}		
		return ergArray;
	}
	
	/**
	 * n over k 
	 * @param n and k must be whole numbers.
	 */
	private int binomialCoefficient(int n, int k){
		int erg = 0;
		if(k == 0){
			return 1; 
		} else {
			long zaehler = 1;
			long nenner = 1;
			for(int i = 1; i <= k; i++){
				globalCount++;
				zaehler = zaehler * n;
				n--;
			}
			for(int i = 1; i <= k; i++){
				globalCount++;
				nenner = nenner * i;
			}
			erg = (int) (zaehler/nenner);
		}
		return erg;
	}
	
	/**
	 * noch faster
	 *
	 */
	  private int bc(int n, int k){
	    int res = 1; globalCount++;
	    int K=k;
	    K = (2*k > n) ? n-k : k ;  

	    for (int i=1;i <= K; i++){
	      globalCount++;
	      res *= (n-K+i);
	      res /= i;
	    }
	    return res;
	  }
	  
	
	public static void printArr(int[] arr){
	    for (int i=0; arr.length > i; i++){
	      System.err.format("%d ",arr[i]);
	    }
	    System.err.println();
	  }
	
	public static void main(String [] args){
		FastPascal fp = new FastPascal();
		printArr(fp.calcNRow(0));
		printArr(fp.calcNRow(1));
		printArr(fp.calcNRow(2));
		printArr(fp.calcNRow(3));
		printArr(fp.calcNRow(4));
		printArr(fp.calcNRow(5));
		printArr(fp.calcNRow(6));
		printArr(fp.calcNRow(7));
		System.err.println(String.format("%d", globalCount));
	}

}
