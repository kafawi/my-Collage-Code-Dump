package Aufgabenblatt01;

public class Schluessel {
	
	private static int nummer = 1000;
	private int wert;
	
	public Schluessel(int wert) {
		this.wert = wert;
	}
	
	public Schluessel() {
		nummer++;
		wert = nummer;
	}

	public int getWert() {
		return wert;
	}
	public static void reset(){
		nummer = 1000;
	}
	
	public boolean equals(Schluessel key){
		return ((wert - key.getWert()) == 0 );
	}
	
}
