package algo;

//import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Mergesort extends Sort {
	
	private Sortobject<?>[] arr;
    private Sortobject<?>[] tmp;



	@Override
	public void sort(List<Sortobject<?>> list) {
	    resetCounter();
	    int len = list.size();
	    arr = new Sortobject<?>[len];
	    list.toArray(arr);
	    tmp = new Sortobject<?>[len];
	    list.toArray(tmp);
	    System.err.println(""+222);
	    mergesort(0, len-1);
	    list.clear();
	    list.addAll(Arrays.asList(arr));
	}
	
	private void mergesort(int low, int high){
		if (low < high) {
            // Get the index of the element which is in the middle
            int middle = low + (high - low) / 2;
            // Sort the left side of the array
            mergesort(low, middle);
            // Sort the right side of the array
            mergesort(middle + 1, high);
            // Combine them both
            merge(low, middle, high);
        }
	}
	private void merge(int low, int middle, int high) {

        // Copy both parts into the helper array
        //for (int i = low; i <= high; i++) {
        //    helper[i] = numbers[i];
        //}

        int i = low;
        int j = middle + 1;
        int k = low;
        // Copy the smallest values from either the left or the right side back
        // to the original array
        while (i <= middle && j <= high) {
            if (compare(tmp[i].getKey(), arr[j].getKey()) <= 0) {
                arr[k] = tmp[i]; moveCount++;
                i++;
            } else {
                tmp[k] = arr[j]; moveCount++;
                j++;
            }
            // Copy the rest of the left side of the array into the target array
            while (i <= middle) {
                arr[k] = tmp[i];
                k++;
                i++;
            }

        }
	}
		
}