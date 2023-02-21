

public class Datensatz<T> implements Comparable<Datensatz<T>> {

	private int key;

	private T daten;

	public Datensatz(int key, T daten) {
		this.key = key;
		this.daten = daten;
	}

	public int getKey() {
		return key;
	}

	public T getDaten() {
		return daten;
	}

	@Override
	public int compareTo(Datensatz<T> o) {
		return this.key - o.getKey();
	}
}
