package algo;

import java.util.List;

public class Keysort extends Sort {
	
	private Sortobject<?>[] helpArr;
	private final int FAKTOR = 2; 
	private final int INCLUD_START = 700;
	private final int EXCLUD_END = 801;

	
	
	
	
	@Override
	public void sort(List<Sortobject<?>> list) {
		resetCounter();
		cmpCount=0;
		moveCount=0;
		int arrLen = (EXCLUD_END - INCLUD_START) * FAKTOR * list.size();
		helpArr = new Sortobject<?>[arrLen];
		fillHelperArr(list);
		setList(list);
	}
	
	private void fillHelperArr(List<Sortobject<?>> list)
	{
		long key;
		int pos;
		int len = list.size();
		long offset = (INCLUD_START*len);
		for (Sortobject<?> so : list)
		{
			key = so.getKey();
			pos = (int)((key - offset)*FAKTOR);
			cmpCount++;
			while ( null != helpArr[pos]){
		        cmpCount++;
				pos++;
			}
			helpArr[pos]=so; moveCount++;
		}
	}
	
	private void setList(List<Sortobject<?>> list)
	{
		int len = list.size();
		list.clear();
		int pos = 0;
		for (int i = 0; pos < len; i++){
			cmpCount++;
			if ( helpArr[i] != null ){
				list.add(helpArr[i]);  moveCount++;
				pos++;

			}
		}
	}
	
}
