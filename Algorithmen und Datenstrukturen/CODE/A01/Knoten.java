package Aufgabenblatt01;
/**
 * Datenhalter f�r den Typ Liste.
 * @author Florian Heuer
 *
 */
public abstract class Knoten<T>{
	
	/**
	 * Generische Daten
	 */
	private final T daten;
	
	/**
	 * Eindeutiger Schluessel
	 */
	private Schluessel schluessel;
	
	public Knoten(T daten) {
		schluessel = new Schluessel();
		this.daten = daten;
	}
	
	//Dummy konstrctor
	public Knoten( T daten, int key) {
		schluessel = new Schluessel(key);
		this.daten = daten;
	}
	

	public T getDaten() {
		return daten;
	}
	
	public void setSchluessel(Schluessel schluessel){
		this.schluessel = schluessel;
	}

	public Schluessel getSchluessel() {
		return schluessel;
	}
	
	
}
