package algo;
import java.util.List;

public class RandomQS extends Sort {

	@Override
	public void sort(List<Sortobject<?>> list) {
		resetCounter();
		int size = list.size();
		quicksort(0,size-1,list);
	}
	
	protected void quicksort(int low, int high, 
			               List<Sortobject<?>> list)
	{
		if ( low < high ){
			// Conquer
			int part = partition(low, high, list);
			swap(part, high, list); // pivot to his destination
			// Divine 
			quicksort(low, part - 1, list);
			quicksort(part + 1, high, list);
		}
	}
	
	protected int partition(int low, int high, 
			             List<Sortobject<?>> list) 
	{
		int i=low;
		int j=high-1;	
		
		int iPivot = getPivotIndex(low, high);
		
	    if (high != iPivot) {
	    	swap(iPivot, high, list);
	    }
	    
	    Sortobject<?> pivot = list.get(high); 

	    while (true) {
	      while (0 > compare(list.get(i).getKey(), pivot.getKey())) 
	      {
	        i++;
	      }
	      while ( 0 <= compare(list.get(j).getKey(), pivot.getKey()) ) {
	        if( j <= low ) break;  // pseudo Stop element
	        j--;
	      }
	      if (i >= j) {
	        break;
	      }
	      swap(i, j, list);
	    }   
	    return i;
	  }
	
	
	protected int getPivotIndex(int low, int high)
	{
		return (int) (low+(Math.random()*(high-low)));
	}

}
