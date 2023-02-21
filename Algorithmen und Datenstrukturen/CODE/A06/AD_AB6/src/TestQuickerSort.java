import static org.junit.Assert.*;

import java.util.LinkedList;
import java.util.List;
import java.util.Random;
import java.util.stream.Collectors;

import org.junit.Test;

import algo.Sortobject;


public class TestQuickerSort {

	int basis = 10;
	
	int maxExponent = 5;
	
	@Test
	public void testQuickerSort() {
		
		// Tests f�r N^exponent Listeneintr�ge
		for(int exponent = 1; exponent <= maxExponent; exponent++){
			long N = (int) Math.pow(basis, exponent);
			System.out.println("");
			System.out.println("-------------------------------------------------------------");
			System.out.println(String.format("Test Der Klasse QuickerSort2 mit %d Listeneintraegen:", N));
			
			// Liste erstellen
			List<Sortobject<?>> list = new LinkedList<>();
			List<Long> longList = new Random().longs(N, 700*N, 800*N+1).boxed().collect(Collectors.toList());
			for(Long l : longList){
				list.add(new Sortobject<String>(Long.toString(l), l));
			}
			
			// Testen, ob die Liste durcheinander ist
			boolean istSortiert = true;
			long i = 0;
			do{ 
				if(list.get((int)i).getKey()>list.get((int)i+1).getKey()){
					istSortiert = false;
				}
				i++;
			} while (istSortiert == true && i<N-1);
			assertFalse("Liste ist noch sortiert!", istSortiert);
			//System.out.println(list.toString());
			
			QuickerSort2 qS = new QuickerSort2();
			long timeStart = System.currentTimeMillis(); 
			List<Sortobject<?>> sortedList = qS.quickerSort2(list);
			long timeStopp = System.currentTimeMillis();
			System.out.println(String.format("Aufwand:         %8d", qS.counter));
			System.out.println(String.format("Ben�tigte Zeit : %8d ms", timeStopp - timeStart));
			
			//Testen ob die Liste wieder sortiert ist
			
			boolean istUnsortiert = false;
			
			for(long j = 0; j < sortedList.size()-2; j++){ 
				if(sortedList.get((int)j).getKey()>sortedList.get((int)j+1).getKey()){
					istUnsortiert = true;
					break;
				}
			};
			//System.out.println(sortedList.toString());
			assertFalse("Liste ist nicht sortiert!", istUnsortiert);
		}		
	}
	
}
