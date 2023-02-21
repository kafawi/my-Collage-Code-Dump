package array;

import itree.IKnoten;
//import itree.IBaum;


public class ArrKnoten implements IKnoten<Integer> {
  
  
  private Integer datum;
  
  private Integer excludeSum;
  
  public ArrKnoten(Integer datum){
    this.datum = datum;
    excludeSum=0;    
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
