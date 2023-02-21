package algo;
import java.util.List;


public abstract class Sort {
	
	public long moveCount=0;
	
	public long cmpCount=0;
	
	public <T> void swap(int x, int y,
			             List<Sortobject<?>> list)
	{
		
		Sortobject<?> tmp = list.get(x);moveCount++;
		list.set(x, list.get(y));moveCount++;
		list.set(y, tmp);moveCount++;
		
	}
	
	public long compare(long key1, long key2){
		cmpCount++;
		return key1 - key2;
	}

	protected void resetCounter(){
		moveCount=0;
		cmpCount=0;
	}
	
	public long getTotalCount(){
		return cmpCount + moveCount;
	}
	
	public abstract void sort(List<Sortobject<?>> list);

}
