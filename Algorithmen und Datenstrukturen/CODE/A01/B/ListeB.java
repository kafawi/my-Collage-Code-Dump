/**
 * 
 */
package Aufgabenblatt01.B;

import Aufgabenblatt01.Knoten;
import Aufgabenblatt01.Liste;
import Aufgabenblatt01.Schluessel;

/**
 * Listenimplementierung B
 * 
 * @author Florian Heuer
 *
 */
public class ListeB<T> extends Liste<T> {

	private KnotenB<T> head;
	
	private int anzahlElemente = 0;
	
	/* (non-Javadoc)
	 * @see Aufgabenblatt01.Liste#insert(int, Aufgabenblatt01.Knoten)
	 */
	@Override
	public void insert(int position, T element) {
		
		//pr�fe auf unkorrekte werte
		if(!(position > 0 && position <= (anzahlElemente+1))){
			throw new IndexOutOfBoundsException();
		}
		
		KnotenB<T> neuerKnoten = new KnotenB<T>(element);
		KnotenB<T> alterKnoten = getNode(position);
		KnotenB<T> vorKnoten   = null;
		
		if( (position-1)> 0){
			vorKnoten   = getNode(position-1);
		}
		
		//AUFWAND INKREMENTIEREN
		statistikZaehler+=3;
		
		//erstes Element
		if( vorKnoten == null){
			neuerKnoten.setPrev( null );
			head = neuerKnoten;
			
			//AUFWAND INKREMENTIEREN
			statistikZaehler+=2;
		}
		
		//AUFWAND INKREMENTIEREN
		statistikZaehler++;
		
		//setze Referrenzen um
		neuerKnoten.setNext( alterKnoten );
		neuerKnoten.setPrev(vorKnoten);
		
		//AUFWAND INKREMENTIEREN
		statistikZaehler+=2;
		
		//vorheriger Knoten kann null sein
		try {
			vorKnoten.setNext(neuerKnoten);
		} catch (Exception e) {
			// TODO: handle exception
		}

		//alter Knoten kann ebenfalls null sein
		try {
			alterKnoten.setPrev(neuerKnoten);
		} catch (Exception e) {
			
		}
		
		anzahlElemente++;
		
		//AUFWAND INKREMENTIEREN
		statistikZaehler+=3;
		
	}

	/* (non-Javadoc)
	 * @see Aufgabenblatt01.Liste#delete(int)
	 */
	@Override
	public void delete(int position) {
		
		//pr�fe auf invlide Eingabe f�r position
		if(!(position > 0 && position <= anzahlElemente )){
			throw new IndexOutOfBoundsException();
		}
		
		KnotenB<T> knoten 		= getNode(position);
		KnotenB<T> vorKnoten	= (KnotenB<T>) knoten.getPrev();
		KnotenB<T> nachKnoten	= (KnotenB<T>) knoten.getNext();
		
		//AUFWAND INKREMENTIEREN
		statistikZaehler+=3;
		
		try {
			vorKnoten.setNext(nachKnoten);
		} catch (Exception e) {
			
		}
		
		try {
			nachKnoten.setPrev(vorKnoten);
		} catch (Exception e) {
			// TODO: handle exception
		}
		
		anzahlElemente--;
		
		//AUFWAND INKREMENTIEREN
		statistikZaehler+=3;
	}

	/* (non-Javadoc)
	 * @see Aufgabenblatt01.Liste#delete(java.lang.Integer)
	 */
	@Override
	public void delete(Schluessel schluessel) {
		int position = find(schluessel);
		if(position > 0){
			delete(position);
		}
		
		//AUFWAND INKREMENTIEREN
		statistikZaehler+=2;
	}

	/* (non-Javadoc)
	 * @see Aufgabenblatt01.Liste#find(int)
	 */
	@Override
	public int find(Schluessel schluessel) {
		
		KnotenB<T> knoten 	= head;
		int position 		= 0;
		int zaehler 		= 0;
		
		//AUFWAND INKREMENTIEREN
		statistikZaehler+=3;
		
		while(knoten != null){
			zaehler++;
			if( schluessel.getWert() == knoten.getSchluessel().getWert() ){
				position = zaehler;
			}
			
			knoten = (KnotenB<T>) knoten.getNext();
			
			//AUFWAND INKREMENTIEREN
			statistikZaehler+=2;
		}
		
		return position;
	}

	/* (non-Javadoc)
	 * @see Aufgabenblatt01.Liste#retrieve(int)
	 */
	@Override
	public T retrieve(int position) {
		return (T) getNode(position).getDaten();
	}
	
	/* (non-Javadoc)
	 * @see Aufgabenblatt01.Liste#concat(Aufgabenblatt01.Liste)
	 */
	@Override
	public void concat(Liste<T> liste) {
		
		//finde ende von liste
		KnotenB<T> letzterKnoten = getNode(anzahlElemente);
		KnotenB<T> ersterKnoten  = ((ListeB) liste).getHead();
		
		//AUFWAND INKREMENTIEREN
		statistikZaehler+=2;
		
		try {
			letzterKnoten.setNext(ersterKnoten);
		} catch (NullPointerException e) {
			// leere Liste
		}
		
		try {
			ersterKnoten.setPrev(letzterKnoten);
		} catch (NullPointerException e) {
			// leere Liste
		}
		
		//AUFWAND INKREMENTIEREN
		statistikZaehler+=2;
		
	}
	
	/**
	 * Helfer Funktion, die den Knoten zur Position liefert.
	 * @param position
	 * @return
	 */
	private KnotenB<T> getNode(int position) {
		
		if(position<=0){
			throw new IllegalArgumentException("Keine 0 erlaubt");
		}
		
		KnotenB<T> knoten = head;
		
		//AUFWAND INKREMENTIEREN
		statistikZaehler++;
		
		try {
			for(int i=1; i<position; i++){
				knoten = (KnotenB<T>) knoten.getNext();
				
				//AUFWAND INKREMENTIEREN
				statistikZaehler++;
			}
		} catch (Exception e) {
			knoten = null;
		}

		
		return knoten;
	}
	
	public KnotenB<T> getHead() {
		return head;
	}
	
	
	
	
	public static void main(String[] args) {
		
		Liste<Integer> liste = new ListeB<Integer>();

		liste.insert(1, 1);
		liste.insert(2, 2);
		liste.insert(3, 3);
		
		liste.insert(2, 4);
		
		liste.delete(2);
		
		liste.insert(1, 4);
		liste.insert(1, 5);
		liste.insert(1, 6);
		liste.insert(1, 7);
		liste.insert(1, 8);
		liste.insert(1, 9);
		liste.insert(1, 10);
		
		liste.find(new Schluessel(1001));
		
		System.out.println("finish!");
	}


	@Override
	public int getSize() {
		return anzahlElemente;
	}

}
