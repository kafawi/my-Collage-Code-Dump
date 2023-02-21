import java.util.LinkedList;
import java.util.List;

import algo.Sortobject;

public class QuickerSort2 {

	public long counter = 0;
	
	public List<Sortobject<?>> quickerSort2(List<Sortobject<?>> list){
		List<Sortobject<?>> ergList = new LinkedList<>();
		
		for(Sortobject<?> s : list){
			if(ergList.isEmpty()){
				// Wenn die Liste leer ist, ...
				ergList.add(s);
			} else {
				if(ergList.size() < 20){ 
					int i = 0;
					for(Sortobject<?> so : ergList){
						counter++;
						if(s.getKey() > so.getKey()){
							i++;
						} else {
							break;
						}
					}
					if(i < ergList.size()){
						//  f�ge es an der passenden Stelle ein
						ergList.add(i, s);
					} else {
						// f�ge es hinten an
						ergList.add(s);
					}
				} else {
					// Ann�herung an den Listenplatz
					
					int i = ergList.size()/2;
					int iAlt = i;
					int schritt = i;
					do{
						counter++;
						iAlt = i;
						schritt = schritt/2;
						if(s.getKey() < ergList.get(i).getKey() ){
							i = i-schritt;
						} else {
							i = i+(schritt); 
						}
					} while (Math.abs(i-iAlt) > 10);
					
					if(s.getKey() >= ergList.get(i).getKey()){
						// Wenn das einzusortierende Element >= dem Listenplatz(i) ist, ...
						while(i < ergList.size()){
							counter++;
							if(s.getKey() > ergList.get(i).getKey()){
								i++;
							} else {
								break;
							}
						}
						if(i < ergList.size()){
							//  f�ge es an der passenden Stelle ein
							ergList.add(i, s);
						} else {
							// f�ge es hinten an
							ergList.add(s);
						}
					} else {
						// Wenn das einzusortierende Element < dem Listenplatz(i) ist, ...
						while( i >= 0){
							counter++; 
							if(s.getKey() < ergList.get(i).getKey()){
								i--;
							} else {
								i++;
								break;
							}
						}
						if(i < 0){
							ergList.add(0, s);
						} else {
							ergList.add(i, s);
						}
					}
				}
			} 
		}
		
		
		return ergList;
	}
}
