package quicksort;

public class Quicksort {

	private long counter = 0;
	
	enum Pivot {
		ANFANG, ENDE, RANDOM, MEDIAN
	};
	
	public int median(int links, int rechts, int mitte) {
		if (links > rechts ^ links > mitte) 
			return links;
		
		if (rechts > links ^ rechts > mitte)
			return rechts;
		
		return mitte;
		
	}
	
	public int pivotElement (int array[], int links, int rechts, Pivot pivotModus) {
		int auswahl;
		switch (pivotModus) {
		case ANFANG:
			auswahl = array[links];
			break;
		case ENDE:
			auswahl = array[rechts];
			break;
		case RANDOM:
			auswahl = array[(int) (Math.random() * (rechts - links)+links)];
			
			//auswahl = array[(int) (Math.random() * array.length)];
			
			break;
		case MEDIAN:
			auswahl = median(array[links], array[rechts], array[(links + rechts)/2]);
			if (auswahl == array[links]) {
				setCounter(getCounter() + 1);
				swap(array, links, ((links+rechts) /2));
			}
			if (auswahl == array[rechts]) {
				setCounter(getCounter() + 1);
				swap(array, rechts, ((links+rechts) /2));
			}
			break;
		default:
			auswahl = array[(links+rechts)/2];
		}
		return auswahl;
	}
	
	public void quickSort(int array[], Pivot pivotModus) throws IndexOutOfBoundsException {
		if (array.length <= 1) {
			throw new IndexOutOfBoundsException("Array nicht geeignet für Sortierung.");
		}
		int links = 0;
		int rechts = (array.length - 1);
		sort(array, links, rechts, pivotModus);
	}
	
	
	public void swap(int array[], int links, int rechts) {
		setCounter(getCounter() + 1);
		int linkesElement = array[links];
		array[links] = array[rechts];
		array[rechts] = linkesElement;
	}
	
	public void sort(int array[], int links, int rechts, Pivot pivotModus) {
		int linkePosition = links;
		int rechtePosition = rechts;
		int pivot = pivotElement(array, links, rechts, pivotModus);
		
		while (linkePosition < rechtePosition) {
			setCounter(getCounter() + 1);
			while (array[linkePosition] < pivot) {
				setCounter(getCounter() + 1);
				linkePosition++;
			}
			while (array[rechtePosition] > pivot) {
				setCounter(getCounter() + 1);
				rechtePosition--;
			}
			if (linkePosition <= rechtePosition) {
				setCounter(getCounter() + 1);
				swap(array, linkePosition, rechtePosition);
				linkePosition++;
				rechtePosition--;
			}
		}
		
		if (linkePosition < rechts) {
			setCounter(getCounter() + 1);
			sort(array, linkePosition, rechts, pivotModus);
		}
		if (rechtePosition > links) {
			setCounter(getCounter() + 1);
			sort(array, links, rechtePosition, pivotModus);
		}	
	}
	

	public long getCounter() {
		return counter;
	}

	public void setCounter(long counter) {
		this.counter = counter;
	}
	
}
