package linked;

import itree.IKnoten;

public class LinKnoten implements IKnoten<Integer> {
  
  /**
   * Zeiger auf die Kinder des Knotens
   */
  private LinKnoten rechtesKind = null;

  private LinKnoten linkesKind = null;
  
  /**
   * Daten im Knoten
   */
  private Integer datum = null;
  
  
  private Integer excludeSum;
  
  
  
  public LinKnoten(Integer datum){
    this.datum = datum;
    excludeSum=0;    
  }
  
  public LinKnoten getRechtesKind() {
    return rechtesKind;
  }
  
  public void setRechtesKind(LinKnoten rechtesKind) {
    this.rechtesKind = rechtesKind;
  }

  public LinKnoten getLinkesKind() {
    return linkesKind;
  }

  public void setLinkesKind(LinKnoten linkesKind) {
    this.linkesKind = linkesKind;
  }
  
  @Override
  public int compareTo(IKnoten<Integer> arg0) {
    return datum.compareTo(arg0.getDatum());
  }

  @Override
  public Integer getDatum() {
    return datum;
  }

  @Override
  public Integer getSum() {
    return excludeSum;
  }

  @Override
  public void setDatum(Integer datum) {
    this.datum = datum;  
  }

  @Override
  public void setSum(Integer sum) {
    this.excludeSum = sum;
  }
  
}
