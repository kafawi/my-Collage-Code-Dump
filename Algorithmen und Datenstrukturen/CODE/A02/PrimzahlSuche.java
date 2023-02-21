/**
 * 
 */
package Aufgabenblatt02;

/**
 * @author 	Florian Heuer, 
 * 			Karl-Fabian Witte, 
 * 			Alexander Mendel
 *
 */
public class PrimzahlSuche {

	/**
	 * 
	 */
	public static long zaehlerLangsam = 0;
	
	/**
	 * 
	 */
	public static long zaehlerSchnell = 0;
	
	/**
	 * 
	 */
	public static long zaehlerSieb = 0;
	
	/**
	 * 
	 */
	public static long zaehlerEinzeln = 0;
	
	/**
	 * 
	 */
	public static final int KMAX = 5;
	
	
	
	
	
	
	
	/**
	 * 
	 */
	public static boolean[] langsam(int n){

		boolean[] feld = new boolean[n];
		
		//fülle array
		for(int i=0 ; i < n ; i++){
			feld[i] = true;
		}
		
		for ( int i = 2; i < n; i++){
			
			//AUFWAND INKREMENTIEREN
			zaehlerLangsam++;
			
			for ( int j = 2; j < n; j++){
				
				//AUFWAND INKREMENTIEREN
				zaehlerLangsam++;
				
				if ( (i%j == 0) && (j!=i) ){
					feld[i] = false;
				}
			}
		}
		
		return feld;
	}
	
	/**
	 * 
	 */
	public static boolean[] schnell( int n){
		
		boolean[] feld = new boolean[n];
		
		//fülle array
		for(int i=0 ; i < n ; i++){
			feld[i] = true;
		}
		
		for ( int i = 2; i < n; i++){
			
			//AUFWAND INKREMENTIEREN
			zaehlerSchnell++;
			
			for ( int j = 2; j < i; j++){
				
				//AUFWAND INKREMENTIEREN
				zaehlerSchnell++;
				
				if ( i%j == 0 ){
					feld[i] = false;
				}
			}
		}
		
		return feld;
	}
	
	/**
	 * 
	 */
	public static boolean[] sieb( int n ){
		
		boolean[] feld = new boolean[n];
		
		//fülle array
		for(int i=0 ; i < n ; i++){
			feld[i] = true;
		}
			
		for(int i=2 ; i < (int)Math.sqrt(n) ; i++){
			
			//AUFWAND INKREMENTIEREN
			zaehlerSieb++;
				
				if ( feld[i] == true ){
					for (int j = 2 ; i*j < n ; j++){
						
						//AUFWAND INKREMENTIEREN
						zaehlerSieb++;
						
						feld[i*j] = false;
					}
				}
		}
		
		return feld;
	}
	
	/**
	 * 
	 */
	public static boolean einzeln(int zahl){
		for (int j = 2 ; j < zahl ; j++){
			
			//AUFWAND INKREMENTIEREN
			zaehlerEinzeln++;
			
			if(zahl%j==0){
				return false;
			}
		}
		return true;
	}
	
	/**
	 * Hauptprogramm
	 * 
	 * @param args
	 */
	public static void main(String[] args) {
		
		
		
		for(int k=1; k<=KMAX; k++){
			int n = (int) Math.pow(10, k);
			
			System.out.println("----K="+k+"----");
			
			PrimzahlSuche.langsam( n );
			System.out.println("Langsame Suche: " + PrimzahlSuche.zaehlerLangsam);
			
			PrimzahlSuche.schnell( n );
			System.out.println("Schnelle Suche: " + PrimzahlSuche.zaehlerSchnell);
			
			PrimzahlSuche.sieb( n );
			System.out.println("Sieb Suche: " + PrimzahlSuche.zaehlerSieb);
			
			for(int i=2; i<n; i++){
				PrimzahlSuche.einzeln( i );
			}
			System.out.println("Einzelne Suche: " + PrimzahlSuche.zaehlerEinzeln + "\n");
		}
		


		
	}

}
