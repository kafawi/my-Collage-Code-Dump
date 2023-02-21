/**
 * 
 */
package Aufgabenblatt01.B;

import Aufgabenblatt01.Knoten;

/**
 * @author Florian Heuer
 *
 */
public class KnotenB<T> extends Knoten<T> {

	private Knoten<T> prev;
	
	private Knoten<T> next;

	public KnotenB(T daten) {
		super(daten);
	}
	
	public Knoten<T> getPrev() {
		return prev;
	}

	public void setPrev(Knoten<T> prev) {
		this.prev = prev;
	}

	public Knoten<T> getNext() {
		return next;
	}

	public void setNext(Knoten<T> next) {
		this.next = next;
	}
	
	
	
}
