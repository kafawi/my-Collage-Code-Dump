
public class ArrKnoten<T extends Number> 
  implements Comparable<ArrKnoten<T>>{

  private T datum;
  
  private T excludeSum;
  
  
  public ArrKnoten(T datum){
    this.datum = datum;
    excludeSum = null;
  }
  public ArrKnoten(){
    this.datum = null;
    this.excludeSum = null;
  }
  
  
  public void setDatum(T datum){
    this.datum = datum;
  }
  
  public void setSum(T sum){
    this.excludeSum = sum;
  }
  
  public T getDatum(){
    return datum;
  }
  
  public T getSum(){
    return excludeSum;
  }


  @Override
  public int compareTo(ArrKnoten<T> A) {
    return (int) (datum.longValue() - A.getDatum().longValue());
  }
  
}
