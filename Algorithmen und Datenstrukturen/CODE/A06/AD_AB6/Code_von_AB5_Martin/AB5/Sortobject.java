package AB5;

public class Sortobject<T> {

	private T load;
	
	private int key;
	
	private static int keycounter = 0;
	
	public Sortobject( T load) {
		key = keycounter;
		keycounter++;
		this.load = load;
	}

	public T getLoad() {
		return load;
	}

	public void setLoad(T load) {
		this.load = load;
	}

	public int getKey() {
		return key;
	}

	public void setKey(int key) {
		this.key = key;
	}
	
	public void setKeycounter(int i){
		keycounter = 0;
	}
	
	public String toString(){
		return String.format("%5d", key);
	}
}
