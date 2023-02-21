package quicksort;

import static org.junit.Assert.*;

import org.junit.Assert;
import org.junit.Test;

//import aufgabenblatt1.UnvalidActionException;
import quicksort.Quicksort.Pivot;

public class TestQuicksort {

	
	@Test
	public void testQuicksort() {
		int[] array = { 1, 14, 18, 3, 4, 19, 2 };
		Quicksort test = new Quicksort();
		test.quickSort(array, Pivot.ENDE);
		
		assertEquals(1, array[0]);
		assertEquals(2, array[1]);
		assertEquals(3, array[2]);
		assertEquals(4, array[3]);
		assertEquals(14, array[4]);
		assertEquals(18, array[5]);
		assertEquals(19, array[6]);
		// Test Array von 0 oder 1 Element
		int[] noSortArray = {1};
		try {
			test.quickSort(noSortArray, Pivot.ANFANG);
			Assert.assertTrue("Fehler: Es wurde keine Exception geworfen!", false);

		} catch (IndexOutOfBoundsException e) {
			e.getMessage();
		}
	}
}
