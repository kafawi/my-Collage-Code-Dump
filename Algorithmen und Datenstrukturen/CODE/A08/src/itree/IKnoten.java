package itree;

public interface IKnoten<T> extends Comparable<IKnoten<T>>{
  
  public T getDatum();
  
  public T getSum();
  
  public void setDatum(T datum);
  
  public void setSum(T sum);

}
