package AB5;

import static org.junit.Assert.*;

import java.util.Collections;
import java.util.LinkedList;
import java.util.List;

import org.junit.Test;


public class TestQuicksort {
	
	private int faktor = 10;

	@Test
	public void testListSort() {
		for(int i = 0; i<3; i++){
			 int listsize = (int) (faktor * Math.pow(10, i));
			System.out.println(String.format("Aufwand für %d Elemente pro Liste:", listsize));
			for(Quicksort.pivotart pivotart : Quicksort.pivotart.values()){
				List<Sortobject<? extends Comparable<?>>> unSortedList = this.createUnSortedList(listsize);
				Quicksort qs = new Quicksort();
				List<Sortobject<? extends Comparable<?>>> sortedList = qs.sort(unSortedList, 0, unSortedList.size()-1, Quicksort.pivotart.FIRST);
				for( int j = 0; j < sortedList.size()-2; j++){
					assertTrue( "Liste ist nicht richtig sortiert!", sortedList.get(j).getKey() < sortedList.get(j+1).getKey());
				}
				System.out.println(String.format("Suchverfahren %6s :   %d",pivotart, qs.counter ));
				//this.printList(sortedList, pivotart);
			}
		}
		
	}
	
	public List<Sortobject<? extends Comparable<?>>> createSortedList(int size){
		List<Sortobject<? extends Comparable<?>>> list = new LinkedList<>();
		for(int i = 0; i< size; i++){
			list.add(new Sortobject<String>(String.format("Element %d", i)));
		}
		new Sortobject<>(null).setKeycounter(0);
		return list;
	}
	
	private List<Sortobject<? extends Comparable<?>>> unSort( List<Sortobject<? extends Comparable<?>>> list){
		Collections.shuffle(list);
		return list;
	}
	
	public List<Sortobject<? extends Comparable<?>>> createUnSortedList(int size){
		return unSort(createSortedList(size));
	}
	
	private void printList(List<Sortobject<? extends Comparable<?>>> list, Quicksort.pivotart art){
		this.printList(list, (String.format("Art der Pivotbestimmung: %s", art)));
	}
	
	public void printList(List<Sortobject<? extends Comparable<?>>> list, String s){
		System.out.println(s);
		for(Sortobject<?> obj:list){
			System.out.print(obj.toString());
		}
		System.out.println("");
	}
	
	

}
