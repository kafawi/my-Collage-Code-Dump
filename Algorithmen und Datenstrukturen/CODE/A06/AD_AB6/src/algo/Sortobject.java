package algo;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.function.Supplier;
import java.util.stream.Collectors;
import java.util.stream.LongStream;

public class Sortobject<T>  {

	private T load;
	
	private long key;
	
	public Sortobject(T load, long key) {
		this.key = key;
		this.load = load;
	}

	public T getLoad() {
		return load;
	}

	public void setLoad(T load) {
		this.load = load;
	}

	public long getKey() {
		return key;
	}
	
	public String toString(){
		return String.format("%5d", key);
	}
	
	
	public static List<Sortobject<?>> getRandomList(long N, 
			                                        long minKey, 
			                                        long maxKey)
	{
		long[] keys = new Random().longs(N, minKey, maxKey).toArray();
		ArrayList<Sortobject<?>> list = new ArrayList<Sortobject<?>>();
		for(int i=0; i < N; i++){
			list.add(new Sortobject<String>(Long.toString(keys[i]), keys[i]));
		}
		return list;	
	}
}
