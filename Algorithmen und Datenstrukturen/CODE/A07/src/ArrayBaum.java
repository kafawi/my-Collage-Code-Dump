import java.util.ArrayList;
import java.util.List;
/**
 * Binärbaum, der seine Daten in einem Array(List) verwaltet
 * @author kallotti
 *
 * @param <T>
 *   Type der Daten 
 */
public class ArrayBaum<T extends Comparable<T>> implements Baum<T> {

  /**
   * Index der nicht erlaubt ist.
   * Wird zurückgegeben bei Unerreichbarkeit  (NOT FOUND)
   */
  private static final int VOID = 0; 
  
  /**
   * WURZELINDEX
   */
  private static final int ROOT = VOID + 1;
  
  /**
   * Datenkontainer (Arrayersatz)
   * ArrayContainer, welcher uns das Array neu allokiert wenn nötig
   */
  private ArrayContainer<T> array;
  
  /**
   * DefaultKonstruktor mit 63 Platz
   */
  public ArrayBaum(){
    this(0);
  }
  
  /**
   * Konstruktor
   * @param len
   *   Initialgroesse
   */
  public ArrayBaum(int len){
    // erste Stelle 0 ist mit dem Algo nicht machbar (bleibt frei)
    array = new ArrayContainer<T>(len+1);
    array.set(VOID, null);
  }
  
  @Override
  public T einfuegen(T datum) {
    T res = null;
    // the first element ?
    if (getDatum(ROOT) == null){
      array.set(ROOT, datum);
      res = array.get(ROOT);    
    } 
    else 
    {
      res = einfuegen(ROOT,datum);
    }
    
    
    return res;
  }
  
  /**
   * Rekursive version des einfügens
   * @param index
   * @param datum
   * @return
   */
  private T einfuegen(int index, T datum) {
    T res = null;
    if(datum.compareTo(getDatum(index)) == 0 )
    {
      res = getDatum(index);
    }
    else
    { 
      if (datum.compareTo(getDatum(index)) < 0)
      {
        int links = linkesKindIndex(index);
        if(getDatum(links) == null )
        {
          array.set(links, datum);
          res = getDatum(links);
        }
        else 
        {
          res = einfuegen(links,datum);
        }
      }
      else
      {
        int rechts = rechtesKindIndex(index);
        if(getDatum(rechts) == null )
        {
          array.set(rechts, datum);
          res = getDatum(rechts);
        } 
        else 
        {
          res = einfuegen(rechts,datum);
        }
      }
    }
    return res;
  }
  
  @Override
  public T rechtesKind(T wurzel) {
    int wurzelIndex = getIndex(wurzel);
    int kindIndex = rechtesKindIndex(wurzelIndex);
    T kind = getDatum(kindIndex);
    return kind;
  }

  @Override
  public T linkesKind(T wurzel) {
    int wurzelIndex = getIndex(wurzel);
    int kindIndex = linkesKindIndex(wurzelIndex);
    T kind = getDatum(kindIndex);
    return kind;
  }
  
  @Override
  public List<T> inOrder() {
    ArrayList<T> list = new ArrayList<T>();
    inOrder(ROOT, list);
    printList("inOrder", list);
    return list;
  }
  
  /**
   * rekursive version der symmetrischen Reihenfolge eines Baumes
   * @param index
   * @param list Container in der alles abgespeichert wird
   */
  private void inOrder(int index, List<T> list){
    if ( getDatum(index) == null ) return;
    inOrder(linkesKindIndex(index), list);
    list.add(getDatum(index));
    inOrder(rechtesKindIndex(index), list);
  }
  
  @Override
  public List<T> preOrder() {
    ArrayList<T> list = new ArrayList<T>();
    preOrder(ROOT, list);
    printList("preOrder", list);
    return list;
  }
  
  /**
   * rekursive version der preOrder eines Baumes
   * @param index
   * @param list Container in der alles abgespeichert wird
   */
  private void preOrder(int index, List<T> list){
    if ( getDatum(index) == null ) return;
    list.add(getDatum(index));
    preOrder(linkesKindIndex(index), list);
    preOrder(rechtesKindIndex(index), list);  
  }
  
  
  @Override
  public List<T> postOrder() {
    ArrayList<T> list = new ArrayList<T>();
    postOrder(ROOT, list);
    printList("postOrder", list);
    return list;
  }
  
  /**
   * rekursive version der postOrder eines Baumes
   * @param index
   * @param list Container in der alles abgespeichert wird
   */
  private void postOrder(int index, List<T> list){
    if ( getDatum(index) == null ) return;
    postOrder(linkesKindIndex(index), list);
    postOrder(rechtesKindIndex(index), list);  
    list.add(getDatum(index));
  }
 
  //-------------------------------------------------------- hilfsmethoden
  
  /**
   * Gibt Position (Index) des rechten Kindes zurueck
   * @param wurzelIndex
   *   Index des Eltern des Kindes
   * @return Index des rechten Kindes
   */
  private int rechtesKindIndex(int wurzelIndex) { 
    int kindIndex = wurzelIndex > VOID ? 2 * wurzelIndex + 1 : VOID;
    return kindIndex;
  }
  
  /**
   * Gibt Position (Index) des linken Kindes zurueck
   * @param wurzelIndex
   *   Index des Eltern des Kindes
   * @return Index des linken Kindes
   */
  private int linkesKindIndex(int wurzelIndex) {
    int kindIndex = wurzelIndex > VOID ? 2 * wurzelIndex : VOID;
    return kindIndex;
  }
  
  /**
   * Gibt die Position vom Eltern (Vaddern) zuruek.
   * @param kindIndex
   *   Index vom Kind
   * @return Index vom Eltern des Kindes )
   *   Wenn = 0 -> kind war wurzel
   */
  @SuppressWarnings("unused")
  private int elterIndex(int kindIndex)
  {
    return kindIndex / 2; 
  }

  /**
   * Gibt Position (Index) des gesuchten Datums zurueck
   * @param datum
   *   interessantes Datum
   * @return Index des Datums
   */
  private int getIndex(T datum) {
    int index = ROOT; // Baumwurzel
    int compare = -1;
    while (compare != 0 && index <= array.size()) {
      compare = datum.compareTo(getDatum(index));
      if (compare < 0){
        index = linkesKindIndex(index);
      }else{
        index = rechtesKindIndex(index);
      }
    }
    return index;
  }
  
  
  /**
   * Gibt den WErt (das Datum) an der indexstelle zurück
   * @param index 
   *   Position des interessierenden Datums 
   * @return
   *   Datum, an der Stelle index
   */
  private T getDatum(int index){
    return (index > VOID && index < array.size())? array.get(index): null;
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
