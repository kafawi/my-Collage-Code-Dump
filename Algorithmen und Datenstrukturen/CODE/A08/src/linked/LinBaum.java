package linked;

import java.util.ArrayList;
import java.util.List;

import itree.IBaum;

public class LinBaum extends IBaum {

  private LinKnoten     wurzelknoten = null;
  /**
   * List benötigt für Ausgabe in den unterschiedlichen Reihenfolgen
   */
  private List<Integer> list;

  /**
   * Default Konstruktor
   */
  public LinBaum() {
    wurzelknoten = null;
  }

  /**
   * Konstruktor mit datum in Wurzelknoten
   * 
   * @param datum
   *          Inhalt des wurzelknotens
   */
  public LinBaum(Integer datum) {
    wurzelknoten = new LinKnoten(datum);
  }

  @Override
  public Integer einfuegen(Integer datum) {
    LinKnoten k = new LinKnoten(datum);
    if (wurzelknoten == null) {
      wurzelknoten = k;
    } else {
      fuegeAmEndeEin(wurzelknoten, k);
    }
 // calulate exclude sum
    sum = 0;
    calcExcludeSum(wurzelknoten);
    
    return datum;
  }

  
  /**
   * calculates the excludet sum of all nodes in inorder
   * 
   * @param k
   *          start Knoten (nessessary for recur)
   */
  private void calcExcludeSum(LinKnoten k) {
    if (k == null) return;
    calcExcludeSum(k.getLinkesKind());
    k.setSum(sum);
    sum += k.getDatum();
    calcExcludeSum(k.getRechtesKind());
  }

  /**
   * Rekursives Einfügen
   * 
   * @param wurzel
   *          aktuelle position
   * @param neuK
   *          neu einzufügender Knoten
   */
  private void fuegeAmEndeEin(LinKnoten wurzel, LinKnoten neuK) {

    if (wurzel.getDatum().compareTo(neuK.getDatum()) > 0) {
      if (wurzel.getLinkesKind() == null) {
        wurzel.setLinkesKind(neuK);

        return;
      } else {
        fuegeAmEndeEin(wurzel.getLinkesKind(), neuK);
      }

    } else {
      if (wurzel.getRechtesKind() == null) {
        wurzel.setRechtesKind(neuK);

      } else {
        fuegeAmEndeEin(wurzel.getRechtesKind(), neuK);
      }
    }

  }
 // ------------------------------------------------------------------ Orders
  @Override
  public List<Integer> inOrder() {
    list = new ArrayList<Integer>();
    inOrder(wurzelknoten);
    printList("preOrder", list);
    return list;
  }

  @Override
  public List<Integer> preOrder() {
    list = new ArrayList<Integer>();
    preOrder(wurzelknoten);
    printList("preOrder", list);
    return list;
  }

  @Override
  public List<Integer> postOrder() {
    list = new ArrayList<Integer>();
    postOrder(wurzelknoten);
    printList("preOrder", list);
    return list;
  }
//
  
  /**
   * Rekursiver InOrder
   * @param root aktueller Knoten
   */
  private void inOrder(LinKnoten root){
    if(root!=null){
      inOrder(root.getLinkesKind());
      list.add(root.getDatum());
      
      inOrder(root.getRechtesKind());
    }
  }
  /**
   * Rekursiver PreOrder
   * @param root aktueller Knoten
   */
  private void preOrder(LinKnoten root){
    if(root!=null){
      list.add(root.getDatum());
      preOrder(root.getLinkesKind());
      preOrder(root.getRechtesKind());
    }
  }
  /**
   * Rekursiver postOrder
   * @param root aktueller Knoten
   */
  private void postOrder(LinKnoten root){
    if(root!=null){
      postOrder(root.getLinkesKind());
      postOrder(root.getRechtesKind());
      list.add(root.getDatum());
    }
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
  //_------------------------------------------------------------ Sum Between
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
    if (wurzelknoten != null) {
      LinKnoten am = getKnotenMin(min);
      LinKnoten aM = getKnotenMax(max);
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
   private LinKnoten getKnotenMin(Integer m) {
     LinKnoten am = null;
     LinKnoten lastGt = wurzelknoten;
     LinKnoten tmp = wurzelknoten;
     while (am == null) {
       cmpCount++;
       int cmp = m.compareTo(tmp.getDatum());
       if (cmp == 0) {
         mvCount++;
         am = tmp;
       } else {
         if (cmp < 0) {
           mvCount++;
           lastGt = tmp;
           cmpCount++;
           if (tmp.getLinkesKind() == null) {
             mvCount++;
             am = lastGt;
           } else {            
             tmp = tmp.getLinkesKind();
           }
         } else if (cmp > 0) {
           cmpCount++;
           if (tmp.getRechtesKind() == null) {
             mvCount++;
             am = lastGt;
           } else {
             tmp = tmp.getRechtesKind();
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
   private LinKnoten getKnotenMax(Integer M) {
     LinKnoten aM = null;
     LinKnoten lastLt = wurzelknoten;
     LinKnoten tmp = wurzelknoten;
     while (aM == null) {
       cmpCount++;
       int cmp = M.compareTo(tmp.getDatum());
       if (cmp == 0) {
         mvCount++;
         aM = tmp;
       } else {
         if (cmp < 0) {
           cmpCount++;
           if (tmp.getLinkesKind() == null) {
             mvCount++;
             aM = lastLt;
           } else {
             tmp = tmp.getLinkesKind();
           }
         } else if (cmp > 0) {
           mvCount++;
           lastLt = tmp;
           cmpCount++;
           if (tmp.getRechtesKind() == null) {
             mvCount++;
             aM = lastLt;
           } else { 
             tmp = tmp.getRechtesKind();
           }
         }
       }
     }
     return aM;
   }
  
  

}
