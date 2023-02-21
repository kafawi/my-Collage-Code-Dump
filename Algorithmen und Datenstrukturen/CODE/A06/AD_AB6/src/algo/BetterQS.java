package algo;

import java.util.List;

public class BetterQS extends RandomQS {

	private int recurStopSize;
	private int stop;

	public BetterQS(int stop) {
		this.stop = stop;
	}

	public BetterQS() {
		this(10);
	}
	
	public void setStop(int stop){
		this.stop=stop;
	}

	@Override
	public void sort(List<Sortobject<?>> list) {
		resetCounter();
		recurStopSize = stop;
		int size = list.size();
		quicksort(0, size - 1, list);
	}

	@Override
	protected void quicksort(int low, int high, List<Sortobject<?>> list) {
		if (recurStopSize < (high - low)) {
			// Conquer
			int part = partition(low, high, list);
			swap(part, high, list); // pivot to his destination
			// Divine
			quicksort(low, part - 1, list);
			quicksort(part + 1, high, list);
		} else {
			insertsort(low, high, list);
		}

	}

	private void insertsort(int low, int high, List<Sortobject<?>> list) {
		for (int i = low + 1; i <= high; ++i) {
			Sortobject<?> tmp = list.get(i);
			moveCount++;
			int j;
			for (j = i - 1; 
			     j >= low && compare(list.get(j).getKey(), tmp.getKey()) > 0;
			     --j) 
			{
				list.set(j + 1, list.get(j));
				moveCount++;
			}
			list.set(j+1, tmp);
			moveCount++;
		}
	}
/*
	private void insertsort(int size, List<Sortobject<?>> list) {
		for (int i = 1; i < size; i++) {
			Sortobject<?> tmp = list.get(i);
			moveCount++;
			int j = i;
			while (j > 0 && compare(list.get(j - 1).getKey(), tmp.getKey()) > 0) {
				list.set(j, list.get(j - 1));
				moveCount++;
				j--;
			}
			list.set(j, tmp);
			moveCount++;

		}

	}
	*/
}
