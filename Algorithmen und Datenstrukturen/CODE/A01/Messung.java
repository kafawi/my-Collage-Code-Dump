package Aufgabenblatt01;

import Aufgabenblatt01.A.ListeA;
import Aufgabenblatt01.B.ListeB;

public class Messung {

	public static final int K_MAX = 4;
	
	public static void fuelleListe(Liste<Integer> liste, int k, boolean randomPosition ){
		
		for (int i=1; i <= Math.pow(10, k); i++ ){
			
			int pos = 1;
			
			if(randomPosition){
				//zufällige einfüge position
				pos = (int) (Math.random()*i) + 1;
			}
			
			liste.insert(pos, i);
		}
	}
	
	public static void fuelleListe(Liste<Integer> liste, int k ){
		fuelleListe(liste, k, false);
	}
	
	public static void main(String[] args) {
	
		
		//insert
		for (int k = 1; k <= K_MAX; k++) {
			Liste<Integer> liste = new ListeB<Integer>(); 
			
			Messung.fuelleListe( liste, k, true );
			
			System.out.println("Insert(K="+k+"): " + liste.statistikZaehler);
		}

	
		//delete pos
		for (int k = 1; k <= K_MAX; k++) {
			Liste<Integer> liste = new ListeB<Integer>();
			
			Messung.fuelleListe(liste, k);
			liste.statistikZaehler = 0;
			
			//lösche zufällige Einträge
			for(int i=0; i<Math.pow(10, k); i++){
				int pos = (int) (1 + Math.random()*(Math.pow(10, k)-i));
				liste.delete(pos);
			}
			
			System.out.println("Delete(pos)(K="+k+"): " + liste.statistikZaehler);
		}
		
		//delete key
		for (int k = 1; k <= K_MAX; k++) {
			Liste<Integer> liste = new ListeB<Integer>();
			
			Messung.fuelleListe(liste, k);
			liste.statistikZaehler = 0;
			
			//lösche zufällige Einträge
			for(int i=0; i<Math.pow(10, k); i++){
				int wert = (int) (1001 + Math.random()*(Math.pow(10, k)-i));
				
				liste.delete( new Schluessel(wert) );
			}
			
			System.out.println("Delete(key)(K="+k+"): " + liste.statistikZaehler);
		}

		//find
		for (int k = 1; k <= K_MAX; k++) {
			Liste<Integer> liste = new ListeB<Integer>();
			
			Messung.fuelleListe(liste, k);
			liste.statistikZaehler = 0;
			
			//finde zufällige Einträge
			for(int i=0; i<Math.pow(10, k); i++){
				int wert = (int) (1001 + Math.random() * Math.pow(10, k) );
				
				liste.find( new Schluessel(wert) );
			}
			
			System.out.println("Find(K="+k+"): " + liste.statistikZaehler);
		}
		
		//retrieve
		for (int k = 1; k <= K_MAX; k++) {
			Liste<Integer> liste = new ListeB<Integer>();
			
			Messung.fuelleListe(liste, k);
			liste.statistikZaehler = 0;
			
			//hole zufällige Einträge
			for(int i=0; i<Math.pow(10, k); i++){
				int pos = (int) (1 + Math.random() * Math.pow(10, k) );
				
				liste.retrieve(pos);
			}
			
			System.out.println("Retrieve(K="+k+"): " + liste.statistikZaehler);
		}
		
		//concat
		for (int k = 1; k <= K_MAX; k++) {
			Liste<Integer> liste  = new ListeB<Integer>();
			Liste<Integer> liste2 = new ListeB<Integer>();
			
			Messung.fuelleListe(liste, k);
			Messung.fuelleListe(liste2, 2); //100 Elemente
			liste.statistikZaehler = 0;
			
			//verbinde Liste
			liste.concat(liste2);
			
			System.out.println("Concat(K="+k+"): " + liste.statistikZaehler);
		}
	}

}
