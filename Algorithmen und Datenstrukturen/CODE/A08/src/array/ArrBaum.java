package array;

import java.util.ArrayList;
import java.util.List;

import itree.IBaum;

public class ArrBaum extends IBaum {

  /**
   * Index der nicht erlaubt ist. Wird zurückgegeben bei Unerreichbarkeit (NOT
   * FOUND)
   */
  private static final int VOID = 0;

  /**
   * WURZELINDEX
   */
  private static final int ROOT = VOID + 1;

  /**
   * Datenkontainer (Arrayersatz) ArrayContainer, welcher uns das Array neu
   * allokiert wenn nötig
   */
  private ArrContainer     array;

  // ------------------------------------------------------------ KONSTRUKTOREN
  /**
   * DefaultKonstruktor mit 63 Platz
   */
  public ArrBaum() {
    this(100000000);
  }

  /**
   * Konstruktor
   * 
   * @param len
   *          Initialgroesse
   */
  public ArrBaum(int len) {
    // erste Stelle 0 ist mit dem Algo nicht machbar (bleibt frei)
    array = new ArrContainer(len + 1);
    // array.set(VOID, null);
  }

  // ---------------------------------------------------------------- EinfUEgen
  @Override
  public Integer einfuegen(Integer datum) {
    Integer res = null;
    // the first element ?
    cmpCount++;
    if (array.get(ROOT) == null) {
      array.set(ROOT, datum);
      mvCount++;
      res = array.get(ROOT).getDatum();
    } else {
      res = einfuegen(ROOT, datum);
    }
    // calulate exclude sum
    sum = 0;
    calcExcludeSum(ROOT);

    return res;
  }

  /**
   * Rekursive version des einfügens
   * 
   * @param index
   *   Startindex der Suche im Array des Baumes
   * @param datum
   *   Datum, was eingefügt werden soll
   * @return
   *   Das Element in dem Baum welches == datum ist
   */
  private Integer einfuegen(int index, Integer datum) {
    Integer res = null;
    Integer tmp = array.get(index).getDatum();
    cmpCount++;
    if (datum.compareTo(tmp) == 0) {
      res = array.get(index).getDatum();
    } else {
      if (datum.compareTo(tmp) < 0) {
        int links = linkesKindIndex(index);
        cmpCount++;
        if (array.get(links) == null) {
          array.set(links, datum);
          mvCount++;
          res = array.get(links).getDatum();
        } else {
          res = einfuegen(links, datum);
        }
      } else {
        int rechts = rechtesKindIndex(index);
        cmpCount++;
        if (array.get(rechts) == null) {
          array.set(rechts, datum);
          mvCount++;
          res = array.get(rechts).getDatum();
        } else {
          res = einfuegen(rechts, datum);
        }
      }
    }
    return res;
  }

  /**
   * calculates the excludet sum of all nodes in inorder
   * 
   * @param index
   *          start index (nessessary for recur)
   */
  private void calcExcludeSum(int index) {
    if (array.get(index) == null)
      return;
    calcExcludeSum(linkesKindIndex(index));
    array.get(index).setSum(sum);
    sum += array.get(index).getDatum();
    calcExcludeSum(rechtesKindIndex(index));
  }

  // --------------------------------------------------------------------- ORDER
  // --
  @Override
  public List<Integer> inOrder() {
    ArrayList<Integer> list = new ArrayList<Integer>();
    inOrder(ROOT, list);
    printList("inOrder", list);
    return list;
  }

  /**
   * rekursive version der symmetrischen Reihenfolge eines Baumes
   * 
   * @param index
   * @param list
   *          Container in der alles abgespeichert wird
   */
  private void inOrder(int index, List<Integer> list) {
    if (array.get(index) == null)
      return;
    inOrder(linkesKindIndex(index), list);
    list.add(array.get(index).getDatum());
    inOrder(rechtesKindIndex(index), list);
  }

  @Override
  public List<Integer> preOrder() {
    ArrayList<Integer> list = new ArrayList<Integer>();
    preOrder(ROOT, list);
    printList("preOrder", list);
    return list;
  }

  /**
   * rekursive version der preOrder eines Baumes
   * 
   * @param index
   * @param list
   *          Container in der alles abgespeichert wird
   */
  private void preOrder(int index, List<Integer> list) {
    if (array.get(index) == null)
      return;
    list.add(array.get(index).getDatum());
    preOrder(linkesKindIndex(index), list);
    preOrder(rechtesKindIndex(index), list);
  }

  @Override
  public List<Integer> postOrder() {
    ArrayList<Integer> list = new ArrayList<Integer>();
    postOrder(ROOT, list);
    printList("postOrder", list);
    return list;
  }

  /**
   * rekursive version der postOrder eines Baumes
   * 
   * @param index
   * @param list
   *          Container in der alles abgespeichert wird
   */
  private void postOrder(int index, List<Integer> list) {
    if (array.get(index) == null)
      return;
    postOrder(linkesKindIndex(index), list);
    postOrder(rechtesKindIndex(index), list);
    list.add(array.get(index).getDatum());
  }

  /**
   * Druckt eine Liste auf die Konsole
   * 
   * @param name
   * @param list
   */
  private void printList(String name, List<Integer> list) {
    System.out.format("%10s:", name);
    for (Integer el : list) {
      System.out.format(" %4s", el);
    }
    System.out.println();
  }

  // ----------------------------------------------------------------- SUM
  // BETWEEN
  @Override
  public Integer getSumBetween(Integer m, Integer M) {
    // reset counters
    reset();
    // start
    Integer sumBetween = 0;
    Integer min;
    Integer max;
    if (m.compareTo(M) < 0) {
      min = m;
      max = M;
    } else {
      min = M;
      max = m;
    }
    cmpCount++;
    if (array.get(ROOT) != null) {
      ArrKnoten am = getKnotenMin(min);
      ArrKnoten aM = getKnotenMax(max);
      if (aM != null || am != null) {
        mvCount++;
        sumBetween = aM.getSum() + aM.getDatum() - am.getSum();
      }
    }
    return sumBetween;
  }
 /**
  * Gibt den Knoten zurück der den kleinsten WErt groesser gleich des Arguments
  * @param m 
  *   Untere Grenze
  * @return
  *   Knoten der den kleinsten Wert größer gleich m hat
  */
  private ArrKnoten getKnotenMin(Integer m) {
    int index = ROOT;
    ArrKnoten am = null;
    ArrKnoten lastGt = array.get(ROOT);
    while (am == null) {
      cmpCount++;
      int cmp = m.compareTo(array.get(index).getDatum());
      if (cmp == 0) {
        mvCount++;
        am = array.get(index);
      } else {
        if (cmp < 0) {
          int links = linkesKindIndex(index);
          mvCount++;
          lastGt = array.get(index);
          cmpCount++;
          if (array.get(links) == null) {
            mvCount++;
            am = lastGt;
          } else {            
            index = links;
          }
        } else if (cmp > 0) {
          int rechts = rechtesKindIndex(index);
          cmpCount++;
          if (array.get(rechts) == null) {
            mvCount++;
            am = lastGt;
          } else {
            index = rechts;
          }
        }
      }
    }
    return am;
  }
  
  /**
   * Gibt den Knoten zurück der den groessten WErt kleiner gleich des Arguments
   * @param m 
   *   Untere Grenze
   * @return
   *   Knoten der den kleinsten Wert größer gleich m hat
   */
  private ArrKnoten getKnotenMax(Integer M) {
    int index = ROOT;
    ArrKnoten aM = null;
    ArrKnoten lastLt = array.get(ROOT);
    while (aM == null) {
      cmpCount++;
      int cmp = M.compareTo(array.get(index).getDatum());
      if (cmp == 0) {
        mvCount++;
        aM = array.get(index);
      } else {
        if (cmp < 0) {
          int links = linkesKindIndex(index);
          cmpCount++;
          if (array.get(links) == null) {
            mvCount++;
            aM = lastLt;
          } else {
            index = links;
          }
        } else if (cmp > 0) {
          int rechts = rechtesKindIndex(index);
          mvCount++;
          lastLt = array.get(index);
          cmpCount++;
          if (array.get(rechts) == null) {
            mvCount++;
            aM = lastLt;
          } else { 
            index = rechts;
          }
        }
      }
    }
    return aM;
  }

  // ------------------------------------------------------------------ Helpers
  /**
   * Gibt Position (Index) des rechten Kindes zurueck
   * 
   * @param wurzelIndex
   *          Index des Eltern des Kindes
   * @return Index des rechten Kindes
   */
  private int rechtesKindIndex(int wurzelIndex) {
    int kindIndex = wurzelIndex > VOID ? 2 * wurzelIndex + 1 : VOID;
    return kindIndex;
  }

  /**
   * Gibt Position (Index) des linken Kindes zurueck
   * 
   * @param wurzelIndex
   *          Index des Eltern des Kindes
   * @return Index des linken Kindes
   */
  private int linkesKindIndex(int wurzelIndex) {
    int kindIndex = wurzelIndex > VOID ? 2 * wurzelIndex : VOID;
    return kindIndex;
  }
}
