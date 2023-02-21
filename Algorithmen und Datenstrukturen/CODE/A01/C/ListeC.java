package Aufgabenblatt01.C;

import Aufgabenblatt01.Liste;
import Aufgabenblatt01.Schluessel;

public class ListeC<T> extends Liste<T> {
	
	private KnotenC<T> head;
	
	private KnotenC<T> tail;
	
	private int anzahlElemente = 0;
	
	private final static int NOT_FOUND = -1; 
	
	public ListeC(){
		head = new KnotenC<T>(null, 0);
		tail = new KnotenC<T>(null, 0);
		head.setNext(tail);
		tail.setNext(head);
	}
	
	@Override
	public void insert(int position, T element) 
			throws IndexOutOfBoundsException, IllegalArgumentException
	{
		// EXCEPTION 
		if ((anzahlElemente+1) < position || 1 > position ){
			throw new IndexOutOfBoundsException(); 
		} else if (null == element){
			throw new IllegalArgumentException();
		}
		
		// LOGIC
		KnotenC<T> neuerKnoten = new KnotenC<T>(element);
		// antizipative gedoenst
		KnotenC<T> prev = getNode( position - 1 );
		neuerKnoten.setNext(prev.getNext());
		prev.setNext(neuerKnoten);

		if (neuerKnoten.getNext() == tail){
			tail.setNext(neuerKnoten);
		}
		
		anzahlElemente++;
		
		//AUFWAND INKREMENTIEREN
		statistikZaehler+=7;
		return;
	}

	@Override
	public void delete(int position) 
			throws IndexOutOfBoundsException
	{
		if (anzahlElemente < position || 1 > position ){
			throw new IndexOutOfBoundsException(); 
		} 
		
		KnotenC<T> prev = getNode(position -1 );
		//AUFWAND INKREMENTIEREN
		statistikZaehler+=1;
		
		KnotenC<T> del = prev.getNext();
		prev.setNext(prev.getNext().getNext());
		// loeschen des vorherigen
		del = null;
	
		anzahlElemente--;
		//AUFWAND INKREMENTIEREN
		statistikZaehler+=5;

	}

	@Override
	public void delete(Schluessel schluessel) throws IllegalArgumentException{
		
		if (null == schluessel){
			throw new IllegalArgumentException();
		}
		
		
		KnotenC<T> knoten = head.getNext();
		
		// alten schlüssel retten (optional)
		Schluessel oldTailKey = tail.getSchluessel();
		tail.setSchluessel(schluessel);
		
		//AUFWAND INKREMENTIEREN
		statistikZaehler+=3;
		
		while( !schluessel.equals(knoten.getNext().getSchluessel())){
			knoten = knoten.getNext();
			//AUFWAND INKREMENTIEREN
			statistikZaehler+=2;
		}
		
		// delete this
		if (knoten.getNext() != tail){
			knoten.setNext(knoten.getNext().getNext());
			// gc wird knoten.next loeschen.
			
		}
		//AUFWAND INKREMENTIEREN
		statistikZaehler+=2;
		tail.setSchluessel(oldTailKey);
		anzahlElemente--;
		//AUFWAND INKREMENTIEREN
		statistikZaehler+=3;
		return;
		//int pos = find();
		
		
	}

	@Override
	public int find(Schluessel schluessel) throws IllegalArgumentException{
		
		if (null == schluessel){
			throw new IllegalArgumentException();
		}
		
		int pos = 1;
		KnotenC<T> knoten = head.getNext();
		
		// Stopperelement
		Schluessel oldTailKey = tail.getSchluessel();
		tail.setSchluessel(schluessel);
		
		//AUFWAND INKREMENTIEREN
		statistikZaehler+=4;
		
		
		while(!schluessel.equals(knoten.getSchluessel())){
			knoten = knoten.getNext();
			pos++;
			//AUFWAND INKREMENTIEREN
			statistikZaehler+=3;
		}
		
		if (knoten == tail){
			pos = -1;
		}
		tail.setSchluessel(oldTailKey);
		//AUFWAND INKREMENTIEREN
		statistikZaehler+=3;
		return pos;
	}

	@Override
	public T retrieve(int position) throws IndexOutOfBoundsException {
		
		if (anzahlElemente < position || 1 > position ){
			throw new IndexOutOfBoundsException(); 
		} 
		
		int currentPos = 1;
		KnotenC<T> knoten = head.getNext();
		T elem = null;
		//AUFWAND INKREMENTIEREN
		statistikZaehler+=3;
		
		while( currentPos < position){
			knoten = knoten.getNext();
			currentPos++;
			//AUFWAND INKREMENTIEREN
			statistikZaehler+=3;
		}
		
		if (knoten != tail){
			elem = knoten.getDaten();	
		}
		//AUFWAND INKREMENTIEREN
		statistikZaehler+=1;
		
		return elem;
	}

	@Override
	public void concat(Liste<T> liste) {
		
		if (liste == null ) return ;
		if ( liste.getSize() == 0) return;
		
		if (liste instanceof ListeC<?>){
			ListeC<T> l = (ListeC<T>) liste;
			tail.getNext().setNext(l.getNode(1));
			tail.setNext(l.getNode(l.getSize()));
			tail.getNext().setNext(tail);
			
			//AUFWAND INKREMENTIEREN
			statistikZaehler+=4;
			
		} else {
			for (int pos = 1; liste.getSize() > pos; pos++){
				insert(pos + anzahlElemente, liste.retrieve(pos) );
				//AUFWAND INKREMENTIEREN
				statistikZaehler+=1;
			}
			
		}
		anzahlElemente += liste.getSize();
		//AUFWAND INKREMENTIEREN
		statistikZaehler+=1;
		return;

	}
	@Override
	public int getSize() {
		return anzahlElemente;
	}
	
	public KnotenC<T> getNode(int position) {
		// LOGIK
		KnotenC<T> knoten = head; 
		
		for(int i=0; i<position; i++)
		{
			knoten = knoten.getNext();
		}
		
		return knoten;
	}
	
	
	// minor Testing
	public static void main (String [] args) {
	
		System.out.println("peter");
		
		ListeC<Integer> l = 
		//		new ListeA<Integer>();
		//      new ListeB<Integer>();
		      new ListeC<Integer>();
		
		l.head.setNext(new KnotenC<Integer>(1));
		l.head.getNext().setNext(new KnotenC<Integer>(2));
		l.head.getNext().getNext().setNext(new KnotenC<Integer>(3));
		
		System.out.println(l.head.getNext().getDaten());
		
		System.out.println("" + l.getNode(1).getDaten()
				+ " " + l.getNode(2).getDaten()
				+ " " + l.getNode(3).getDaten());
		
		if (l.getNode(0) == l.head ){
			System.out.println(" head is right ");
		}
		
		
		
	}


}
