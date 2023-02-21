import java.util.ArrayList;
import java.util.List;

/**
 * Binärbaum, der seine Daten über Knoten und pointer verwaltet
 * 
 * @author peter
 *
 * @param <T>
 *   Type der Daten
 */
public class PointerBaum<T extends Comparable<T> > implements Baum<T>{

  private Knoten<T> wurzelknoten = null;
  /**
   * List benötigt für Ausgabe in den unterschiedlichen Reihenfolgen
   */
  private List<T> list;
  
  /**
   * Default Konstruktor
   */
  public PointerBaum (){
    setWurzelknoten(null);
  }

  /**
   * Konstruktor mit datum in Wurzelknoten
   * @param datum Inhalt des wurzelknotens
   */
  public PointerBaum (T datum){
    setWurzelknoten(new Knoten<T>(datum));
  }
/**
 * Fügt ein Element ein
 */
  @Override
  public T einfuegen(T datum) {
   Knoten<T> k = new Knoten<T>(datum);
   if (wurzelknoten == null){
     wurzelknoten = k;
   }
   else
   {
     fuegeAmEndeEin(wurzelknoten, k);
   }
    return datum;
  }
/**
 * Rekursives Einfügen 
 * @param wurzel aktuelle position
 * @param neuK neu einzufügender Knoten
 */
  private void fuegeAmEndeEin(Knoten<T> wurzel, Knoten<T> neuK) {
   
  if(wurzel.getData().compareTo(neuK.getData()) > 0 ){
    if(wurzel.getLinkesKind() == null){
      wurzel.setLinkesKind(neuK);
     
      return;
    }else{
      fuegeAmEndeEin(wurzel.getLinkesKind(), neuK);
    }
    
  }else{
    if(wurzel.getRechtesKind() == null){
      wurzel.setRechtesKind(neuK);

    }else{
      fuegeAmEndeEin(wurzel.getRechtesKind(), neuK);
    }
  }
        
  }

/**
 * Gibt das datum des rechten Kindes eines Wurzelknotens zurück
 */
  @Override
  public T rechtesKind(T wurzel) {
   Knoten<T> k=findeWurzel(wurzel);
   return k.getRechtesKind().getData();
  }

/**
 * Findet ein Datum im Baum
 * @param datum gesuchtes Datum
 * @return Knoten mit dem gesuchten Datum
 */
  private Knoten<T> findeWurzel(T datum) {
    Knoten<T> k = new Knoten<T>(datum);
    if(!k.getData().equals(datum)){
      k=findeWurzel(k.getLinkesKind().getData());
      k=findeWurzel(k.getRechtesKind().getData());
    }
    return k;
    
    
  }
  /**
   * Gibt das datum des linken Kindes eines Wurzelknotens zurück
   */

  @Override
  public T linkesKind(T wurzel) {
    Knoten<T> k=findeWurzel(wurzel);
    return k.getLinkesKind().getData();
  }
/**
 * InOrder Ausgabe des Baumes
 */
  @Override
  public List<T> inOrder() {
    list = new ArrayList<T>();
    inOrder(wurzelknoten);
    printList("inOrder", list);
    return list;
  }


  

/**
 * preOrder Ausgabe des Baumes
 */

  @Override
  public List<T> preOrder() {
    list = new ArrayList<T>();
    preOrder(wurzelknoten);
    printList("preOrder", list);
    return list;
  }
/**
 * postOrder Ausgabe des Baumes
 */
  @Override
  public List<T> postOrder() {
    list = new ArrayList<T>();
    postOrder(wurzelknoten);
    printList("postOrder", list);
    return list;
  }
/**
 * Getter für die Baumwurzel
 * @return wurzelknoten
 */
  public Knoten<T> getWurzelknoten() {
    return wurzelknoten;
  }
/**
 * Setter für den Wurzelknoten
 * @param wurzelknoten
 */
  private void setWurzelknoten(Knoten<T> wurzelknoten) {
    this.wurzelknoten = wurzelknoten;
  }
  /**
   * Rekursiver InOrder
   * @param root aktueller Knoten
   */
  private void inOrder(Knoten<T> root){
    if(root!=null){
      inOrder(root.getLinkesKind());
      list.add(root.getData());
      
      inOrder(root.getRechtesKind());
    }
  }
  /**
   * Rekursiver PreOrder
   * @param root aktueller Knoten
   */
  private void preOrder(Knoten<T> root){
    if(root!=null){
      list.add(root.getData());
      preOrder(root.getLinkesKind());
      preOrder(root.getRechtesKind());
    }
  }
  /**
   * Rekursiver postOrder
   * @param root aktueller Knoten
   */
  private void postOrder(Knoten<T> root){
    if(root!=null){
      postOrder(root.getLinkesKind());
      postOrder(root.getRechtesKind());
      list.add(root.getData());
    }
  }
  
  /**
   * Druckt eine Liste auf die Konsole
   * @param name
   * @param list
   */
  private void printList(String name, List<T> list){
    System.out.format("%10s:", name );
    for (T el: list){
      System.out.format( " %4s", el );
    }
    System.out.println();
  }
  
}
