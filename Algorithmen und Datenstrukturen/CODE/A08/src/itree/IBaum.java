package itree;

import java.util.List;

public abstract class IBaum {
  /*
   * Zähler der Vergleiche
   */
  public int cmpCount;
  
  /**
   * Zähler der bewegungn in 
   */
  public int mvCount;
  
  /**
   * hilfs variable, in der der zwischenwert der summe gesopeichert wird 
   * Wichtig fuer die Berechnung der der ExcludeSum in den Knoten,
   * Wird in einfügen mit hilfe der inOrder berechnet
   */
  protected Integer sum;
  /**
   * Einfügen eines Knotens in den Baum
   * Zuddem berechnung der excludeSum in den Knoten mit der inorder Iteration
   * @param datum 
   *   Fügt ein neues Objekt an die rictige Stelle ein
   * @return Referenz auf das einzufügende Objekt oder 
   *   das Objekt im Bum mit gleichem Schlüssel
   */
  public abstract Integer einfuegen(Integer datum);
  
  /**
   * resets the counts
   */
  public void reset( ){
    mvCount =0;
    cmpCount=0;
  }
  /**
   * get total counts
   * @return sum of move and compare counter 
   */
  public int count(){
    return mvCount +cmpCount;
  }
  /**
   * Ausgabe des Baumes in Order
   */
  public abstract List<Integer> inOrder();
  
  /**
   * Ausgabe des Baumes preOrder
   */
  public abstract List<Integer> preOrder();
  
  /**
   * Ausgabe des Baumes PostOrder
   */
  public abstract List<Integer> postOrder();
  
  /**
   * 
   */
  public abstract Integer getSumBetween(Integer m, Integer M);
  
}
