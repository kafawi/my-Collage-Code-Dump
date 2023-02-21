package AB5;
/**
 * Martin Witte 2285586
 */
import java.util.Collections;
import java.util.List;

/**
 * Diese Klasse Sortiert eine Liste mit dem Quicksortvervahren
 * 
 * @author Martin
 *
 */
public class Quicksort {
	
	public long counter = 0;
	
	private List<Sortobject<? extends Comparable<?>>> list;
	
	/**
	 * Verschiedene Verfahren zum Finden des Pivotelementes
	 * 
	 * @author Martin
	 *
	 */
	public enum pivotart {FIRST, LAST, MIDIAN, MIDDLE, RANDOM};
	
	/**
	 * Hauptfunktion, wird von der Testklasse aufgerufen, ruft sich selbst auf
	 * @param list Zu sortierende Liste
	 * @param indexLinks Anfangsindex des zu sortierenden Intervalls
	 * @param indexRechts Endindex des zu sortierenden Intervalls
	 * @param art Art der Pivotelementsuche
	 * @return Gibt die Liste sortiert zurück
	 */
	public List<Sortobject<? extends Comparable<?>>> sort(List<Sortobject<? extends Comparable<?>>> list , int indexLinks, int indexRechts, pivotart art){
		this.list = list;
		int index = this.listeTeilen(indexLinks, indexRechts, art);
		if(indexLinks < index-1){
			this.sort(list, indexLinks, indexRechts, art);
		}
		if(index < indexRechts){
			this.sort(list, index, indexRechts, art);
		}
		
		return list;
	}
	
	/**
	 * Diese Methode wird von der sort() aufgerufen um die Listenteile(globale Liste) zu Sortieren
	 * @param indexLinks
	 * @param indexRechts
	 * @param art
	 * @return gibt den Index des Pivotelementes
	 */
	public int listeTeilen(int indexLinks, int indexRechts, pivotart art){
		int i;
		int j;
		int pivotIndex;
		Sortobject<? extends Comparable<?>> pivotElement;
		
		switch (art) {
			case FIRST:
				pivotElement = this.pivotFirstElement(indexLinks, indexRechts);
				break;
			case MIDDLE:
				pivotElement = this.pivotMiddleElement(indexLinks, indexRechts);
				break;
			case LAST:
				pivotElement = this.pivotLastElement(indexLinks, indexRechts);
				break;
			case MIDIAN:
				pivotElement = this.pivotMeridianelement(indexLinks, indexRechts);
				break;
			case RANDOM:
				pivotElement = this.pivotRandomElement(indexLinks, indexRechts);
				break;
			default:
				throw new IllegalArgumentException("Falsche Pivotelement-bestimmung");
		}
		
		pivotIndex = list.indexOf(pivotElement);
		i = indexLinks;
		j = indexRechts;
		
		while (i <= j){
			while(list.get(i).getKey() < pivotIndex){
				i++;
				counter++;
			}
			
			while(list.get(j).getKey() > pivotIndex){
				j--;
				counter++;
			}
			
			if(i <= j){
				Collections.swap(list, i, j);
				i++;
				j--;
			}
			counter++;
			
		}
		return i;
	}
	
	
	private Sortobject<? extends Comparable<?>> pivotFirstElement( int indexLinks, int indexRechts){
		return list.get(indexLinks);
	}
	
	private Sortobject<? extends Comparable<?>> pivotLastElement( int indexLinks, int indexRechts){
		return list.get(indexRechts);
	}
	
	private Sortobject<? extends Comparable<?>> pivotMiddleElement( int indexLinks, int indexRechts){
		return list.get(indexRechts/2);
	}
	
	private Sortobject<? extends Comparable<?>> pivotMeridianelement( int indexLinks, int indexRechts){
		int a = list.get(indexLinks).getKey();
		int b = list.get(indexRechts/2).getKey();
		int c = list.get(indexRechts).getKey();
		if((a<b && a>c) || (a>b && a<c)){
			return list.get(a);
		} else if((b<a && b>c) || (b>a && b<c)){
			return list.get(a);
		} else {
			return list.get(a);
		}
	}
	
	private Sortobject<? extends Comparable<?>> pivotRandomElement(int indexLinks, int indexRechts){
		return list.get((int) (indexLinks+(Math.random()*(indexRechts-indexLinks))));
	}
	
	public static void main(String[] args) {
		Quicksort qs = new Quicksort();
		TestQuicksort tq = new TestQuicksort();
		List<Sortobject<? extends Comparable<?>>> listA = tq.createUnSortedList(10);
		qs.sort(listA,0, listA.size()-1, pivotart.FIRST);
	}

}
