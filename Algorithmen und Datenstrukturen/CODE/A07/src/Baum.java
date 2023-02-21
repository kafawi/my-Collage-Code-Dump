import java.util.List;

/**
 * Binärbaum Interface
 * 
 * @author peter und söhne e.V.
 *
 * @param <T>
 *   Type des Binärbaumes
 */
public interface Baum<T extends Comparable<T> > {
  /**
   * Einfügen eines Knotens in den Baum
   * @param datum 
   *   Fügt ein neues Objekt an die rictige Stelle ein
   * @return Referenz auf das einzufügende Objekt oder 
   *   das Objekt im Bum mit gleichem Schlüssel
   */
  public T einfuegen(T datum);
  
  /**
   * Ausgabe des rechten Kindes eines Wurzelknotens
   * @param wurzel
   *   Das Eltern des Kindes
   * @return rechtes Kind
   */
  public T rechtesKind(T wurzel);
  
  /**
   * Ausgabe des linken Kindes eines Wurzelknotens
   * @param wurzel
   *   Das Eltern des Kindes
   * @return linkes Kind
   */
  public T linkesKind(T wurzel);
  
  /**
   * Ausgabe des Baumes in Order
   */
  public List<T> inOrder();
  
  /**
   * Ausgabe des Baumes preOrder
   */
  public List<T> preOrder();
  
  /**
   * Ausgabe des Baumes PostOrder
   */
  public List<T> postOrder();
  


}
