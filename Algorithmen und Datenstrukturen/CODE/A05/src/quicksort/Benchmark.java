package quicksort;

import quicksort.Quicksort.Pivot;

public class Benchmark {

	private static int maxExp = 7;

	public static void main(String[] args) {
		doBenchmarktest();
	}

	private static void doBenchmarktest() {

		Quicksort test = new Quicksort();
		System.out.println("Quicksorttest");

		for (int i = 1; i <= maxExp; i++) {

			int arrayR[] = new int[(int) Math.pow(10, i)];

			if (i < 8) {
				int arrayFO[] = new int[(int) Math.pow(10, i)];
				int arrayBO[] = new int[(int) Math.pow(10, i)];

				for (int ordered = 0; ordered < arrayFO.length; ordered++) {
					arrayFO[ordered] = ordered + 1;
				}

				int b = 0;
				for (int reverseordered = arrayBO.length - 1; reverseordered >= 0; reverseordered--) {
					arrayBO[b] = reverseordered + 1;
					b++;
				}

				int arrayFOA[] = new int[(int) Math.pow(10, i)];
				int arrayFOE[] = new int[(int) Math.pow(10, i)];
				int arrayFOR[] = new int[(int) Math.pow(10, i)];
				int arrayFOM[] = new int[(int) Math.pow(10, i)];

				System.arraycopy(arrayFO, 0, arrayFOA, 0, arrayR.length);
				System.arraycopy(arrayFO, 0, arrayFOE, 0, arrayR.length);
				System.arraycopy(arrayFO, 0, arrayFOR, 0, arrayR.length);
				System.arraycopy(arrayFO, 0, arrayFOM, 0, arrayR.length);

				int arrayBOA[] = new int[(int) Math.pow(10, i)];
				int arrayBOE[] = new int[(int) Math.pow(10, i)];
				int arrayBOR[] = new int[(int) Math.pow(10, i)];
				int arrayBOM[] = new int[(int) Math.pow(10, i)];

				System.arraycopy(arrayBO, 0, arrayBOA, 0, arrayR.length);
				System.arraycopy(arrayBO, 0, arrayBOE, 0, arrayR.length);
				System.arraycopy(arrayBO, 0, arrayBOR, 0, arrayR.length);
				System.arraycopy(arrayBO, 0, arrayBOM, 0, arrayR.length);

				// #########################################
				//System.out.print("Qs: FORWARDSORDERED ANFANG: ");
//				test.quickSort(arrayFOA, Pivot.ANFANG);
//				System.out.println(test.getCounter());
//				test.setCounter(0);

//				System.out.print("Qs: FORWARDSORDERED ENDE: ");
//				test.quickSort(arrayFOE, Pivot.ENDE);
//				System.out.println(test.getCounter());
//				test.setCounter(0);

//				System.out.print("Qs: FORWARDSORDERED RANDOM: ");
//				test.quickSort(arrayFOR, Pivot.RANDOM);
//				System.out.println(test.getCounter());
//				test.setCounter(0);
//
//				System.out.print("Qs: FORWARDSORDERED MEDIAN: ");
//				test.quickSort(arrayFOM, Pivot.MEDIAN);
//				System.out.println(test.getCounter());
//				test.setCounter(0);
//
//				// #########################################
//				System.out.print("Qs: REVERSEORDERED ANFANG: ");
//				test.quickSort(arrayBOA, Pivot.ANFANG);
//				System.out.println(test.getCounter());
//				test.setCounter(0);

//				System.out.print("Qs: REVERSEORDERED ENDE: ");
//				test.quickSort(arrayBOE, Pivot.ENDE);
//				System.out.println(test.getCounter());
//				test.setCounter(0);

//				// System.out.print("Array unsortiert: ");
//				// for (int a = 0; a < arrayBOR.length; a++) {
//				// System.out.print(arrayBOR[a] + ", ");
//				// }
//				// System.out.println();
//				System.out.print("Qs: REVERSEORDERED RANDOM: ");
//				test.quickSort(arrayBOR, Pivot.RANDOM);
//				System.out.println(test.getCounter());
//				test.setCounter(0);
//				//
//				// System.out.print("Array sortiert: ");
//				// for (int a = 0; a < arrayBOR.length; a++) {
//				// System.out.print(arrayBOR[a] + ", ");
//				// }
//				// System.out.println();
//
//				System.out.print("Qs: REVERSEORDERED MEDIAN: ");
//				test.quickSort(arrayBOM, Pivot.MEDIAN);
//				System.out.println(test.getCounter());
//				test.setCounter(0);

			}
			// System.out.println("Arraysize: " + array1.length);

			for (int j = 0; j < arrayR.length; j++)
				arrayR[j] = (int) (Math.random() * Math.pow(10, i) + 525);

			int arrayRA[] = new int[(int) Math.pow(10, i)];
			int arrayRE[] = new int[(int) Math.pow(10, i)];
			int arrayRR[] = new int[(int) Math.pow(10, i)];
			int arrayRM[] = new int[(int) Math.pow(10, i)];

			System.arraycopy(arrayR, 0, arrayRA, 0, arrayR.length);
			System.arraycopy(arrayR, 0, arrayRE, 0, arrayR.length);
			System.arraycopy(arrayR, 0, arrayRR, 0, arrayR.length);
			System.arraycopy(arrayR, 0, arrayRM, 0, arrayR.length);
//
//			System.out.print("Qs: Randomarray ANFANG: ");
//			test.quickSort(arrayRA, Pivot.ANFANG);
//			System.out.println(test.getCounter());
//			test.setCounter(0);
//
//			System.out.print("Qs: Randomarray ENDE: ");
//			test.quickSort(arrayRE, Pivot.ENDE);
//			System.out.println(test.getCounter());
//			test.setCounter(0);
//
//			System.out.print("Qs: Randomarray RANDOM: ");
//			test.quickSort(arrayRR, Pivot.RANDOM);
//			System.out.println(test.getCounter());
//			test.setCounter(0);
//
//			System.out.print("Qs: Randomarray MEDIAN: ");
			test.quickSort(arrayRM, Pivot.MEDIAN);
			System.out.println(test.getCounter());
			test.setCounter(0);
//
			// System.out.println("Counter hat den Wert: " +
			// test.getCounter());

			// test.setCounter(0);
		}
	}
}
