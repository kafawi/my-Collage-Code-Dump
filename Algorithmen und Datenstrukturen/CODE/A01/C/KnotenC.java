package Aufgabenblatt01.C;

import Aufgabenblatt01.Knoten;

public class KnotenC<T> extends Knoten<T> {
	// -------------------------------------- ATTRIBUTS
	private KnotenC<T> next;
	
	// -------------------------------------- CONSTRUCTOR
	public KnotenC(T daten) {
		super(daten);
	}
	
	public KnotenC(T daten, int key) {
		super(daten, key);
	}
	
	// ------------------------------------- GETTER
	public KnotenC<T> getNext(){
		return next;
	}
	
	// ------------------------------------- SETTER
	public void setNext(KnotenC<T> next){
		this.next = next;
	}
	
}
