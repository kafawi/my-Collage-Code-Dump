package helper;

/**
 * Greetings. Welcome to Transelvania. Thy name me The Count, because I love to
 * count
 * 
 * @author kafa
 *
 */
public class Count {

	/**
	 * all my fingers
	 */
	public static int count;
	
	/**
	 * counting the inner loop of neighbor
	 */
	public static int neighbor;
	
	/**
	 * counting the getweight
	 */
	public static int getweight;

	/**
	 * increment, i love it
	 */
	public static void up() {
		count++;
		
		switch (count) {
		case 1:
			System.out.println("one...");
			break;
		case 2:
			System.out.println("two...");
			break;
		case 3:
			System.out.println("tree, HaHaha");
			break;

		case 9000:
			System.out.println("NainTausend,  HAHAHAHA");
			break;
		}
		
	}

	/**
	 * reset, so we can start over again
	 */
	public static void reset() {
		count = 0;
		getweight=0;
		neighbor=0;
		System.out.println("HAHAHA. Und nochmal von vorn! DONNER");
	}

}
