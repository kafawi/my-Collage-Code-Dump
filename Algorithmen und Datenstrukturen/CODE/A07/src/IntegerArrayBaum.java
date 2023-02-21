import java.util.List;


public class IntegerArrayBaum implements Baum<Integer> {
  
  /**
   * Index der nicht erlaubt ist.
   * Wird zurückgegeben bei Unerreichbarkeit  (NOT FOUND)
   */
  private static final int VOID = 0; 
  
  /**
   * WURZELINDEX
   */
  private static final int ROOT = VOID + 1;
  
  private static Integer sum =0;

  private ArrayContainer<ArrKnoten<Integer>> array;

  
  
  /**
   * DefaultKonstruktor mit 63 Platz
   */
  public IntegerArrayBaum(){
    this(0);
  }
  
  /**
   * Konstruktor
   * @param len
   *   Initialgroesse
   */
  public IntegerArrayBaum(int len){
    // erste Stelle 0 ist mit dem Algo nicht machbar (bleibt frei)
    array = new ArrayContainer<ArrKnoten<Integer>>(len+1);
    array.set(VOID, null);
  }
  
  
  @Override
  public Integer einfuegen(Integer datum) {
    Integer res = null;
    // the first element ?
    if (getDatum(ROOT) == null){
      ArrKnoten<Integer> knoten = new ArrKnoten<Integer>(datum);
      array.set(ROOT, knoten);
      res = array.get(ROOT).getDatum();    
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
  private Integer einfuegen(int index, Integer datum) {
    Integer res = null;
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
          array.set(links, new ArrKnoten<Integer>(datum));
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
          array.set(rechts, new ArrKnoten<Integer>(datum));
          res = getDatum(rechts);
        } 
        else 
        {
          res = einfuegen(rechts,datum);
        }
      }
    }
    if (res != datum){
      inOrderSumFill();
    }
    return res;
  }
  
  
  @Override
  public Integer rechtesKind(Integer wurzel) {
    // TODO Auto-generated method stub
    return null;
  }

  @Override
  public Integer linkesKind(Integer wurzel) {
    // TODO Auto-generated method stub
    return null;
  }

  @Override
  public List<Integer> inOrder() {
    // TODO Auto-generated method stub
    return null;
  }

  @Override
  public List<Integer> preOrder() {
    // TODO Auto-generated method stub
    return null;
  }

  @Override
  public List<Integer> postOrder() {
    // TODO Auto-generated method stub
    return null;
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
  
  private ArrKnoten<Integer> linkenKindKnoten(int index){
    return getKnoten(linkesKindIndex(index));
  }
  
  private ArrKnoten<Integer> rechtenKindKnoten(int index){
    return getKnoten(rechtesKindIndex(index));
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
  private int getIndex(Integer datum) {
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
  private Integer getDatum(int index){
    return (index > VOID && index < array.size())?
            array.get(index).getDatum(): null;
  }
  
  
  /**
   * Gibt den WErt (das Datum) an der indexstelle zurück
   * @param index 
   *   Position des interessierenden Datums 
   * @return
   *   Datum, an der Stelle index
   */
  private ArrKnoten<Integer> getKnoten(int index){
    return (index > VOID && index < array.size())?
            array.get(index): null;
  }
  /**
   * Druckt eine Liste auf die Konsole
   * @param name
   * @param list
   */
  private void printList(String name, List<Integer> list){
    System.out.format("%10s:", name );
    for (Integer el: list){
      System.out.format( " %4s", el );
    }
    System.out.println();
  }
  
  private void inOrderSumFill(){
    sum = 0;
    inOrderSumFillRecur(ROOT);
  }
  private void inOrderSumFillRecur(int index){
    if ( getKnoten(index) == null ) return;
    inOrderSumFillRecur(linkesKindIndex(index));
    ArrKnoten<Integer> knoten = getKnoten(index);
    knoten.setSum(sum);
    sum+= knoten.getDatum();
    inOrderSumFillRecur(rechtesKindIndex(index));
  }
  
  private Integer getSum(Integer min, Integer max){
    return null;  
  }
  
  private ArrKnoten<Integer> getMaxKnoten(int index, Integer max){
    if (getKnoten(index) == null ){
      return null;
    }
    int cmp = max.compareTo(getDatum(index));
    if (cmp == 0 ){
      return getKnoten(index);
    }
    if (cmp < 0 ){
     
    } else if (cmp > 0 ){
    }
    return null;
  }
  
  
  /*
   *  if (getKnoten(rechtesKindIndex(index)) == null){
        return getKnoten(index);
      } else {
        return getMaxKnoten(linkesKindIndex(index), max);
      }
   */
  /**
   * a_m  >= min
   * @param index
   * @param min
   * @return
   */
  private ArrKnoten<Integer> getMinKnoten(int index, Integer min){
    if (getKnoten(index) == null ){
      return null;
    }
    
    int cmp = min.compareTo(getDatum(index));
    if (cmp == 0 ){
      return getKnoten(index);
    }
    if( linkenKindKnoten(index) != null) {
      
    }
    if (rechtenKindKnoten(index) != null) {
      
    }
    //int leftCmp = min.compareTo(getDatum(linkesKindIndex(index)));
    if (cmp < 0 ){
      // do somthing
    } else if (cmp > 0 ){
      // do somthing
    }
    return null;
  }
  

  
}
